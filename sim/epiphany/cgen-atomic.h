#ifndef CGEN_ATOMIC_H
#define CGEN_ATOMIC_H
#include <assert.h>

#define SPIN_LOCK(ptr) \
  do\
    {\
      volatile typeof(ptr) vol_ptr = ptr; \
      while (__sync_lock_test_and_set(vol_ptr, 1)) while (*vol_ptr); \
    } \
  while (0)

#define SPIN_RELEASE(ptr) \
  do \
    { \
      volatile typeof(ptr) vol_ptr = ptr; \
      __sync_lock_release(vol_ptr); \
    } \
  while (0)

#define _OP_REG_ATOMIC(Op, Regno, Val)\
do\
  {\
    volatile USI *ptr;\
\
    assert (0 <= Regno && Regno < H_REG_NUM_REGS);\
\
    ptr = &(CPU (h_all_registers)[Regno]);\
    __sync_fetch_and_##Op(ptr, Val);\
  }\
while (0)

#define ADD_REG_ATOMIC(Regno, Val) _OP_REG_ATOMIC(add, Regno, Val)
#define SUB_REG_ATOMIC(Regno, Val) _OP_REG_ATOMIC(sub, Regno, Val)
#define OR_REG_ATOMIC(Regno, Val) _OP_REG_ATOMIC(or, Regno, Val)
#define AND_REG_ATOMIC(Regno, Val) _OP_REG_ATOMIC(and, Regno, Val)
#define XOR_REG_ATOMIC(Regno, Val) _OP_REG_ATOMIC(xor, Regno, Val)

#define SET_REG_BIT_ATOMIC(regno, bit, val)\
do\
  {\
    volatile USI *ptr;\
\
    assert (0 <= regno && regno < H_REG_NUM_REGS);\
    assert (0 <= bit && bit < 32);\
\
    ptr = &(CPU (h_all_registers)[regno]);\
    if (val)\
      __sync_fetch_and_or(ptr, (1ULL << bit));\
    else\
      __sync_fetch_and_and(ptr, ~(1ULL << bit));\
  }\
while (0)

#endif

