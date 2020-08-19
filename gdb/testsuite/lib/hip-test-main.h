/* The driver doesn't know which overload is used by each testcase.
   To address that, we make each possible overload weak, and then the
   driver checks which one was actually defined.  Declaring/defining
   all overloads as extern "C" doesn't work, it fails to link.  */
int __device__ __attribute__((weak)) gdb_hip_test_main (int argc, char **argv, char **envp);
int __device__ __attribute__((weak)) gdb_hip_test_main (int argc, char **argv);
int __device__ __attribute__((weak)) gdb_hip_test_main ();
