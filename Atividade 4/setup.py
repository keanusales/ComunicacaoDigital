from setuptools import setup, Extension

module = Extension("crc", ["crc.c"])

setup(
  name = "crc", version = "1.0",
  ext_modules = [module]
)