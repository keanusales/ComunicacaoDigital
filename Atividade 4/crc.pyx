# cython: binding = False, initializedcheck = False
# cython: boundscheck = False, wraparound = False
# cython: language_level = 3, cdivision = True

cdef extern from "crc.h" nogil:
  ctypedef unsigned uint64
  ctypedef unsigned uint8
  uint8 __order__"order"(uint64)
  uint64 __transfer__"transfer"(uint64, uint64)
  uint64 __receiver__"receiver"(uint64, uint64)

def order(uint64 data):
  return __order__(data)

def transfer(uint64 data, uint64 gen):
  return __transfer__(data, gen)

def receiver(uint64 data, uint64 gen):
  return __receiver__(data, gen)