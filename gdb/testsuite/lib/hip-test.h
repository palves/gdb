#ifndef GDB_HIP_TEST_H
#define GDB_HIP_TEST_H

#include "gdb-hip-runtime.h"

/* The hip compiler defines this as a built-in, which conflicts with
   testcases defining it themselves.  */
#undef _GNU_SOURCE

/* Avoid having to write explicit __device__ in all functions
   throughout.  */
#pragma clang force_cuda_host_device begin

/* The above only works for functions.  Global variables must still
   normally be tagged with __device__.  We address that with our
   plugin.  */
#pragma force_cuda_device_globals

/* Pull in the gdb_hip_test_main declarations.  */
#include "hip-test-main.h"

/* Rewire the test's "main" to the function that the kernel calls.
   The real "main" is the host's main.  */
#define main gdb_hip_test_main

#endif
