#include "gdb-hip-runtime.h"

/* Pull in the gdb_hip_test_main declarations.  */
#include "hip-test-main.h"

#include <unistd.h>

/* The test kernel's entry point.  Call the testcase's main, which has
   been renamed to "gdb_hip_test_main" by hip-test.h, included by all
   testcases.  */

static __global__ void
kernel (int *res, int argc, char **argv, char **envp)
{
  /* See comments in hip-test-main.h.  gdb_hip_test_main is weak -- we
     call the version that is defined by the testcase.  */
  if (static_cast<int (&)(int, char **, char **)>(gdb_hip_test_main))
    *res = gdb_hip_test_main (argc, argv, envp);
  else if (static_cast<int (&)(int, char **)>(gdb_hip_test_main))
    *res = gdb_hip_test_main (argc, argv);
  else
    *res = gdb_hip_test_main ();
}

#define CHECK(cmd)					\
  do							\
    {							\
      hipError_t error = cmd;				\
      if (error != hipSuccess)				\
	{						\
	  fprintf(stderr, "error: '%s'(%d) at %s:%d\n",	\
		  hipGetErrorString (error), error,	\
		  __FILE__, __LINE__);			\
	  exit (EXIT_FAILURE);				\
	}						\
    } while (0)

/* Clone an array of pointers in ARGV style to the device.  Return the
   pointer to the device array.  */

static char **
copy_argv_device (int argc, char **argv)
{
  char **argv_d;
  CHECK (hipMalloc (&argv_d, sizeof (char *) * argc));

  for (int i = 0; i < argc; i++)
    {
      char *arg_d;
      if (argv[i] != nullptr)
	{
	  size_t size = strlen (argv[i]) + 1;
	  CHECK (hipMalloc (&arg_d, size));
	  CHECK (hipMemcpy (arg_d, argv[i], size, hipMemcpyHostToDevice));
	}
      else
	arg_d = nullptr;
      CHECK (hipMemcpy (&argv_d[i], &arg_d, sizeof (char *), hipMemcpyHostToDevice));
    }
  return argv_d;
}

int
main (int argc, char **argv, char **envp)
{
  int deviceId;
  CHECK (hipGetDevice (&deviceId));
  hipDeviceProp_t props;
  CHECK (hipGetDeviceProperties (&props, deviceId));
  printf("info: running on device #%d %s\n", deviceId, props.name);

  printf("info: copy Host2Device\n");

  int exitcode_h;
  int *exitcode_d;
  CHECK (hipMalloc (&exitcode_d, sizeof (int)));

  char **argv_d = copy_argv_device (argc, argv);

  /* Count ENVP entries.  */
  int envc;
  for (envc = 0; envp[envc] != nullptr; envc++)
    ;

  /* One extra for the NULL terminator.  */
  char **envp_d = copy_argv_device (envc + 1, envp);

  printf ("info: launch kernel\n");
  const unsigned blocks = 1;
  const unsigned threadsPerBlock = 1;

  hipLaunchKernelGGL (kernel, dim3 (blocks), dim3 (threadsPerBlock), 0, 0,
		      exitcode_d, argc, argv_d, envp_d);

  printf("info: copy Device2Host\n");
  CHECK (hipMemcpy (&exitcode_h, exitcode_d, sizeof (int), hipMemcpyDeviceToHost));

  /* Wait until kernel finishes.  */
  hipDeviceSynchronize ();

  return exitcode_h;
}

/* Implement some standard functions used by tests, that are missing
   on the device.  */

int __device__
atoi (const char *nptr)
{
  int res = 0;
  for (int i = 0; nptr[i] != '\0'; i++)
    res = res * 10 + nptr[i] - '0';

  return res;
}

int __device__
puts (const char *s)
{
  printf ("%s", s);
  return 0;
}

static __device__ uint64_t
align_up (uint64_t v, int n)
{
  return (v + n - 1) & -n;
}

/* A very simple and stupid malloc implementation that is not thread
   safe and never frees any memory.  This is sufficient for our needs
   since we only run single-threaded programs.  */

/* Is 16 sufficient?  */
#define MALLOC_ALIGN 16

/* The malloc buffer, and the pointer to the current position where
   we'll return memory from.

   Note that Initializing MALLOC_HEAD to point to MALLOC_BUF doesn't
   work...  Fails with:

     LLVM ERROR: Unsupported expression in static initializer: addrspacecast (i8 addrspace(1)* getelementptr inbounds ([65536 x i8], [65536 x i8] addrspace(1)* @_ZL10malloc_buf, i64 0, i64 0) to i8*)
     PLEASE submit a bug report to https://bugs.llvm.org/ and include the crash backtrace.
     Stack dump:
     0.      Program arguments: /opt/rocm-3.7.0-3236/llvm/bin/llc /tmp/break0-36d75a-gfx906-optimized-e48970.bc -O0 -mtriple=amdgcn-amd-amdhsa -mcpu=gfx906 -filetype=obj -o /tmp/break0-36d75a-gfx906-2a4e27.o
     1.      Running pass 'CallGraph Pass Manager' on module '/tmp/break0-36d75a-gfx906-optimized-e48970.bc'.
*/
static __device__ unsigned char malloc_buf[0x10000] __attribute__ ((aligned (MALLOC_ALIGN)));
static __device__ unsigned char *malloc_head;

void *__device__
malloc (size_t size)
{
  /* We do this here because it can't be done on initialization.  */
  if (malloc_head == 0)
    malloc_head = malloc_buf;

  size = align_up (size, MALLOC_ALIGN);

  assert (malloc_head + size > malloc_head
	  && malloc_head + size < malloc_buf + sizeof (malloc_buf));

  void *ret = malloc_head;
  malloc_head += size;
  return ret;
}

void __device__
free (void *ptr)
{
}

void *__device__
calloc (size_t nmemb, size_t size)
{
  void *res = malloc (nmemb * size);
  memset (res, 0, nmemb * size);
  return res;
}

size_t __device__
strlen (const char *s)
{
  const char *end = s;
  while (*end++ != '\0')
    ;
  return end - s;
}

char * __device__
strdup (const char *s)
{
  size_t size = strlen (s) + 1;
  char *ns = (char *) malloc (size);
  memcpy (ns, s, size);
  return ns;
}

/* There's no way to exit a kernel.  Can't lonjmp, can't throw.  All
   we can do is abort/trap.  Most exit calls in the testsuite are in
   error paths, so it isn't that big of a deal.  */

void __device__
exit (int code)
{
  __threadfence ();
  /* "Causes dispatch to be terminated and its associated queue put
     into the error state."  */
  asm ("s_trap 0x02;");
}

/* CLOCKS_PER_SEC is far from real.  Multiply by a factor that gives a
   close enough result in practice.  Tested with a simple program that
   calls sleep(10), and then doing "time ./a.out" until a close enough
   number came out.  This will need obviously tuning on different
   systems...  */
static constexpr uint64_t clocks_factor = 2000;

static void __device__
sleep_clocks (uint64_t clocks)
{
  uint64_t start = clock64 ();
  for (;;)
    {
      uint64_t now = clock64 ();
      uint64_t elapsed = (now > start
			  ? now - start
			  : now + (0xffffffffffffffff - start));
      if (elapsed >= clocks)
	return;
    }
}

extern "C" int __device__
usleep (useconds_t usec)
{
  uint64_t clocks = clocks_factor * CLOCKS_PER_SEC * usec / 1000000;

  sleep_clocks (clocks);
  return 0;
}

extern "C" unsigned int __device__
sleep (unsigned int seconds)
{
  uint64_t clocks = clocks_factor * CLOCKS_PER_SEC * seconds;

  sleep_clocks (clocks);
  return 0;
}
