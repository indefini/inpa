#!/bin/sh

module_path=$(pkg-config --variable=modules ecore-imf)
module_arch=$(pkg-config --variable=module_arch ecore-imf)
rootmodule=$module_path/inpa/$module_arch/
mkdir -p $rootmodule
cp target/debug/libmodule.so $rootmodule/module.so

