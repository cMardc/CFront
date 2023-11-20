#ifdef EMSCRIPTEN

#include <stdio.h>
#include "../inc/frontend.h"

EMSCRIPTEN_KEEPALIVE void addNavbar(const char* title, const char* link, const char* linkName);

EMSCRIPTEN_KEEPALIVE
int main() {
  setIcon("icon.svg");
  addNavbar("CFront", "#", "Home");
  addHTML(
    "<div id='center'>"
    " <img src='icon2x.svg'></img>"
    "<p id='text'>This web page is made with C using FrontC!</p>"
    "</div>"
  );
  addCSS(
    "#center {"
    " margin: auto;"
    " width: 30%;"
    " padding: 10px;"
    "}"
    ""
    "body {"
    " background-color: #444444;"
    "}"
    ""
    "#text {"
    " color: #CCCCCC;"
    " font-size: 30px;"
    "}"
  );
}

void addNavbar(const char* title, const char* link, const char* linkName) {
  const char* titlePrefix = "<li id='navbar-title'>";
  const char* titleSuffix = "</li>";
  size_t totalSize = strlen(titlePrefix) + strlen(title) + strlen(titleSuffix) + 1; // +1 for '\0'
  char* titleElement = (char*)malloc(totalSize);
  if (titleElement == NULL) {
    fprintf(stderr, "Couldn't allocate memory.\n");
    return;
  }
  strcpy(titleElement, titlePrefix);
  strcat(titleElement, title);
  strcat(titleElement, titleSuffix);
  const char* linkPrefix = "<li><a id='navbar-link' href='";
  const char* linkMiddle = "'>";
  const char* linkSuffix = "</a></li>";
  size_t totalLinkSize = strlen(linkPrefix) + strlen(link) + strlen(linkMiddle) + strlen(linkName) + strlen(linkSuffix) + 1; // +1 for '\0'
  char* linkElement = (char*)malloc(totalLinkSize);
  if (linkElement == NULL) {
    fprintf(stderr, "Couldn't allocate memory.\n");
    return;
  }
  strcpy(linkElement, linkPrefix);
  strcat(linkElement, link);
  strcat(linkElement, linkMiddle);
  strcat(linkElement, linkName);
  strcat(linkElement, linkSuffix);

  addHTML("<ul id='navbar'></ul>");
  appendChild("navbar", titleElement);
  appendChild("navbar", linkElement);

  addCSS(
    "#navbar {"
    " list-style-type: none;"
    " margin: 0;"
    " padding: 0;"
    " overflow: hidden;"
    " background-color: #333;"
    "}"
    ""
    "#navbar-title, #navbar-link {"
    " float: left;"
    " display: block;"
    " color: white;"
    " text-align: center;"
    " padding: 14px 16px;"
    " text-decoration: none;"
    "}"
    ""
    "#navbar-link:hover {"
    " background-color: #111;"
    "}"
  );


}


#else
#error "This file needs to be ran using emscripten."
#endif
