#ifdef EMSCRIPTEN

#include <stdio.h>
#include <math.h>
#include "../../inc/frontend.h"

int number = 0;
EMSCRIPTEN_KEEPALIVE void change() {
  if (number != 0) {
    printf("%d\n", number); 
    char* str = (char*)malloc((int)((ceil(log10(abs(number)))+2)*sizeof(char)));
    sprintf(str, "%d", number);
    changeById("number", "innerHTML", str);
    return;
  }
  changeById("number", "innerHTML", "0"); 
}

EMSCRIPTEN_KEEPALIVE void onPlus()  { number++; change(); }
EMSCRIPTEN_KEEPALIVE void onMinus() { number--; change(); }
EMSCRIPTEN_KEEPALIVE void onReset() { number=0; change(); }


EMSCRIPTEN_KEEPALIVE
int main() {
  setTitle("Counter");
  addHTML(
    "<p id='number'></p>"
    "<button id='btnPlus'>+</button>"
    "<button id='btnMinus'>-</button>"
    "<button id='btnReset'>R</button>"
  ); 
  changeById("number", "innerHTML", "0");   
  addCSS(
    "html, body {"
    " height: 100%;"
    "}"
    ""
    "html {"
    " display: table;"
    " margin: auto;"
    "}"
    ""
    "body {"
    " display: table-cell;"
    " vertical-align: middle;"
    "}"
    ""
    "button {"
    " border-style: solid;"
    " border-color: blue;"
    " border-radius: 5px;"
    " transition-delay: all 1s;"
    " margin: 20px;"
    " margin-left: 40px;"
    " margin-right: 40px;"
    " transform: scale(1.5);"
    "}"
    ""
    "button:hover {"
    " border-color: #CCCCCC;"
    " transform: scale(3);"
    "}"
    ""
    "p {"
    " font-size: 50px;"
    "}"
  );
  addListener("btnPlus", "onPlus", "click");
  addListener("btnMinus", "onMinus", "click");
  addListener("btnReset", "onReset", "click");
}


#else
#error "Please execute using emcc"
#endif
