#ifndef GDB_HIP_RUNTIME_H
#define GDB_HIP_RUNTIME_H

/* Header wrapping hip_runtime.h, fixing some things.  */

/* The HIP-provided malloc is broken (see comments around
   __HIP_ENABLE_DEVICE_MALLOC__), so we provide our own very simple
   malloc/free.  */

/* hip_runtime.h includes stdlib.h, so include it ourselves before
   malloc renamed, so that we get the __host__ version declared.  Also
   include <malloc.h>, because some testcases include it.  */

#include <stdlib.h>
#include <malloc.h>

#define malloc broken_hip_malloc
#define free broken_hip_free

#include "hip/hip_runtime.h"

#undef malloc
#undef free

/* stdlib.h only declares the __host__ versions.  Declare them for the
   device.  */
extern "C" __device__ void *malloc (size_t size)
  __attribute__ ((malloc));
extern "C" __device__ void *calloc (size_t nmemb, size_t size)
  __attribute__ ((malloc));
extern "C" __device__ void free (void *ptr);

/* Declare some more standard functions used by tests that are missing
   on the device.  Defined in hip-driver.cc.  */

extern "C" __device__ int atoi (const char *nptr);

extern "C" __device__ void exit (int);

extern "C" __device__ int puts (const char *s);

extern "C" __device__ size_t strlen (const char *s);

extern "C" __device__ char *strdup (const char *s);

#endif
