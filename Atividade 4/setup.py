from setuptools import setup, Extension

module = Extension("crc", ["crcpy.c"])

setup(
  name = "crc", version = "1.0",
  ext_modules = [module]
)