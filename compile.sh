#!/bin/bash

emcc src/main.c -o build/main.js -s 'EXPORTED_RUNTIME_METHODS=["ccall"]'
python3 -mhttp.server 8081

