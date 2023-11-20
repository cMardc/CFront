#!/bin/bash
emcc main.c -o main.js -s EXPORTED_FUNCTIONS='["_malloc", "_free"]' -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap", "getValue", "UTF8ToString", "allocate", "setValue"]'  -sALLOW_MEMORY_GROWTH
python3 -mhttp.server 8081
