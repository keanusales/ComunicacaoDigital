#include <Python.h>

typedef unsigned char uint8;
typedef unsigned long long uint64;
typedef uint64 (*crcfunc)(uint64, uint64);

uint8 order(uint64 data) {
  uint8 bits = 0;
  while (data >>= 1) bits++;
  return bits;
}

uint64 encoder(uint64 data, uint64 gen) {
  uint8 ordata = order(data);
  uint8 ordgen = order(gen);
  uint8 sumord = ordata + ordgen;
  uint64 send = data << ordgen;
  uint64 rest = send;
  for (uint8 i = 0; i <= ordata; i++)
    if (rest & (1ull << (sumord - i)))
      rest ^= gen << (ordata - i);
  return send ^ rest;
}

uint64 decoder(uint64 data, uint64 gen) {
  uint8 ordata = order(data);
  uint8 subord = ordata - order(gen);
  for (uint8 i = 0; i <= subord; i++)
    if (data & (1ull << (ordata - i)))
      data ^= gen << (subord - i);
  return data;
}

PyObject* applyfunc(crcfunc func, PyObject* args) {
  PyObject *odata, *ogen;
  if (!PyArg_UnpackTuple(args, 0, 2, 2, &odata, &ogen)) return NULL;
  uint64 data = PyLong_AsUnsignedLongLong(odata);
  uint64 gen = PyLong_AsUnsignedLongLong(ogen);
  if (PyErr_Occurred()) return NULL;
  return PyLong_FromUnsignedLongLong(func(data, gen));
}

static PyObject* py_encoder(PyObject* self, PyObject* args) {
  return applyfunc(encoder, args);
}

static PyObject* py_decoder(PyObject* self, PyObject* args) {
  return applyfunc(decoder, args);
}

static PyMethodDef CRCMethods[] = {
  {"encoder", py_encoder, METH_VARARGS},
  {"decoder", py_decoder, METH_VARARGS},
  {NULL, NULL}
};

static PyModuleDef crcModule = {
  .m_base = PyModuleDef_HEAD_INIT,
  .m_methods = CRCMethods,
  .m_name = "crc",
  .m_size = -1,
};

PyMODINIT_FUNC PyInit_crc() {
  return PyModule_Create(&crcModule);
}