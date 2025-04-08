#pragma once

#include <Python.h>

typedef unsigned long long uint64;
typedef unsigned char uint8;

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

static PyObject* py_encoder(PyObject* self, PyObject* args) {
  uint64 data, gen;
  if (!PyArg_ParseTuple(args, "KK", &data, &gen)) return NULL;
  uint64 result = encoder(data, gen);
  return PyLong_FromUnsignedLongLong(result);
}

static PyObject* py_decoder(PyObject* self, PyObject* args) {
  uint64 data, gen;
  if (!PyArg_ParseTuple(args, "KK", &data, &gen)) return NULL;
  uint64 result = decoder(data, gen);
  return PyLong_FromUnsignedLongLong(result);
}

static PyMethodDef CRCMethods[] = {
  {"encoder", py_encoder, METH_VARARGS, NULL},
  {"decoder", py_decoder, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef crcModule = {
  PyModuleDef_HEAD_INIT, "crc", NULL, -1, CRCMethods
};

PyMODINIT_FUNC PyInit_crc() {
  return PyModule_Create(&crcModule);
}