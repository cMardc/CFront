#ifdef EMSCRIPTEN

#include <stdio.h>
#include <math.h>
#include "../../inc/frontend.h"

char** tasks;
size_t capacity = 3;


EMSCRIPTEN_KEEPALIVE void onAdd();
EMSCRIPTEN_KEEPALIVE void render();
EMSCRIPTEN_KEEPALIVE void onRemove(int value);



EMSCRIPTEN_KEEPALIVE
int main() {
  tasks = (char**)malloc(3 * sizeof(char *));
  if (tasks == NULL) {
    fprintf(stderr, "Failed to allocate memory.\n");
  }
  setTitle("TODO App");


  addHTML(
    "<h1>Tasks</h1>"
    "<ul id='tasks'>"
    "</ul>"
    "<button id='addBtn'>+</button><input id='textInput' type='text' placeholder='Task name...'></input>"
  );
  addCSS("h5 { display: inline; }");
  addListener("addBtn", "onAdd", "click");
}


EMSCRIPTEN_KEEPALIVE
void onAdd() {
  char* taskName = getPropertyById("textInput", "value");

  tasks = (char**)realloc(tasks, (capacity + 1) * sizeof(char *));
  if (tasks == NULL) {
    fprintf(stderr, "Failed to allocate memory.\n");
    return;
  }

  tasks[capacity] = strdup(taskName); // Allocate memory for the new task and copy the task name
  capacity++;

  render();
}

EMSCRIPTEN_KEEPALIVE
void render() {
  char* currentTask = tasks[capacity - 1];
  int id = capacity - 1;
  char* idStr = (char*)malloc((int)((ceil(log10(id))+2)*sizeof(char)));
  sprintf(idStr, "%d", id);
  const char* taskPrefix = "<li><button class='removeBTN' id='";
  const char* taskMiddle1 = "' onclick='Module._onRemove(";
  const char* taskMiddle2 = ")'>-</button><h5>";
  const char* taskSuffix = "</h5></li>";
  size_t totalSize = strlen(taskPrefix) + strlen(currentTask) + strlen(taskSuffix) + strlen(idStr) + strlen(idStr) + strlen(taskMiddle1) + strlen(taskMiddle2) + 1; // +1 for '\0'
  char* taskHTML = (char*)malloc(totalSize);
  strcpy(taskHTML, taskPrefix);
  strcat(taskHTML, idStr);
  strcat(taskHTML, taskMiddle1);
  strcat(taskHTML, idStr);
  strcat(taskHTML, taskMiddle2);
  strcat(taskHTML, currentTask);
  strcat(taskHTML, taskSuffix);
  appendChild("tasks", taskHTML);
}

EMSCRIPTEN_KEEPALIVE
void onRemove(int id) {
  char* value = (char*)malloc((int)((ceil(log10(id))+2)*sizeof(char)));
  sprintf(value, "%d", id);
  EM_ASM_({
    var id = UTF8ToString($0);     
    var elementToRemove = document.getElementById(id);
    if (elementToRemove) {
      var parent = elementToRemove.parentNode;
      parent.parentNode.removeChild(parent);
    }
    }, value);
}
#else 
#error "Please execute using emcc"
#endif
