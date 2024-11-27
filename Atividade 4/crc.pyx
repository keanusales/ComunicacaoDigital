# cython: binding = False, initializedcheck = False
# cython: boundscheck = False, wraparound = False
# cython: language_level = 3, cdivision = True
# distutils: extra_compile_args = /FAu

cdef extern from "crc.h" nogil:
  ctypedef unsigned uint64
  uint64 __encoder__"encoder"(uint64, uint64)
  uint64 __decoder__"decoder"(uint64, uint64)

def encoder(uint64 data, uint64 gen):
  if gen > data:
    raise ValueError("Gen is greater than data!")
  return __encoder__(data, gen)

def decoder(uint64 data, uint64 gen):
  if gen > data:
    raise ValueError("Gen is greater than data!")
  return __decoder__(data, gen)