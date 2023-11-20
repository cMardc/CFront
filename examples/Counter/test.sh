#!/bin/bash
emcc main.c -o main.js  -s 'EXPORTED_RUNTIME_METHODS=["ccall"]' -s EXPORTED_FUNCTIONS="['_malloc','_free']"
python3 -mhttp.server 8081
