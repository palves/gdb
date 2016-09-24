#ifndef MEM_BARRIER_H
#define MEM_BARRIER_H
#if defined (__i386__) || defined (__amd64__)
#define MEM_BARRIER() asm volatile ("" : : : "memory")
#else
/* This is safe but might be suboptimal, depending on arch. */
#define MEM_BARRIER() __sync_synchronize()
#endif
#endif
