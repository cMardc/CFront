#ifndef _FRONTEND_H_
#define _FRONTEND_H_

#ifdef EMSCRIPTEN

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten.h>
#include <string.h>


/*
 * @brief: change the title of HTML document
 * @param: title - new title of document
*/ 
void setTitle(const char* title) {
  //document.title = 'Put the new title here';
  char JScommand[] = "document.title = \'";
  char ending[] = "\';";
  strcat(JScommand, title);
  strcat(JScommand, ending);
  emscripten_run_script(JScommand);
}

/*
 * @brief: add new stylesheet to HTML document
 * @param: CSSCode - styles to be inserted
 */
void addCSS(const char* CSSCode) {
  const char* JSprefix = "var styleSheet = document.createElement(\'style\'); styleSheet.innerText = \'";
  const char* JSsuffix = "\'; document.head.appendChild(styleSheet);";
  size_t totalLength = strlen(JSprefix) + strlen(CSSCode) + strlen(JSsuffix) + 1; // +1 for the null terminator
  char* JScommand = (char*)malloc(totalLength);
  if (JScommand != NULL) {
    strcpy(JScommand, JSprefix);
    strcat(JScommand, CSSCode);
    strcat(JScommand, JSsuffix);
    emscripten_run_script(JScommand);
    free(JScommand);
  } else {
    printf("Failed to allocate memory!\n");
  }
}

char* replaceQuotes(const char *str) {
    int len = strlen(str);
    char *modifiedStr = (char *)malloc((len + 1) * sizeof(char));

    if (modifiedStr == NULL) {
      printf("error\n");  
    }

    int i, j;
    for (i = 0, j = 0; i < len; ++i) {
        if (str[i] == '\'') {
            modifiedStr[j++] = '\"';
        } else {
            modifiedStr[j++] = str[i];
        }
    }

    modifiedStr[j] = '\0'; // Null-terminate the modified string
    return modifiedStr;
}

/*
 * @brief: add HTML content to the document
 * @param: HTMLCode - HTML content to be inserted
 */
void addHTML(const char* HTMLCode_) {
  char* HTMLCode = replaceQuotes(HTMLCode_);
  const char* JSprefix = "var tempDiv = document.createElement(\'div\'); tempDiv.innerHTML = \'";
  const char* JSsuffix = "\'; while (tempDiv.firstChild) { document.body.appendChild(tempDiv.firstChild); }";
  size_t totalLength = strlen(JSprefix) + strlen(HTMLCode) + strlen(JSsuffix) + 1; // +1 for the null terminator
  char* JScommand = (char*)malloc(totalLength);
  if (JScommand != NULL) {
    strcpy(JScommand, JSprefix);
    strcat(JScommand, HTMLCode);
    strcat(JScommand, JSsuffix);
    emscripten_run_script(JScommand);
    free(JScommand);
  } else {
    printf("Failed to allocate memory!\n");
  }
}

/*
 * @brief: Execute inline Javascript commands
 * @param: JSCode - Javascript code to run
 * @note: Unlike addHTML and addCSS, this function does not add <script> to DOM. Instead it executes it on WASM
*/
void executeJS(const char* JSCode) {
  emscripten_run_script(JSCode);
}

/*
 * @brief: print a warning to console
 * @param: errorLog - message to warn
 * @note: please don't include any newline characters ('\n')
 */
void printWarn(const char* errorLog) {
  const char* JSprefix = "console.warn(\'";
  const char* JSsuffix = "\')";
  size_t totalLength = strlen(JSprefix) + strlen(errorLog) + strlen(JSsuffix) + 1; // +1 for the null terminator
  char* JScommand = (char*)malloc(totalLength);
  if (JScommand != NULL) {
    strcpy(JScommand, JSprefix);
    strcat(JScommand, errorLog);
    strcat(JScommand, JSsuffix);
    emscripten_run_script(JScommand);
    free(JScommand);
  } else {
    printf("Failed to allocate memory!\n");
  }
}

/*
 * @brief: Change property of element that has id to value
 * @param: id - ID of elements to be changed
 * @param: property - Property to be changed
 * @param: value - Set value of property
*/
void changeById(const char* id, const char* property, const char* value) {
  // document.getElementById(\'[id]\').property = value;
  const char* JSprefix = "document.getElementById(\'";
  const char* JSmiddle = "\').";
  const char* JSmiddle2 = " = \'";
  const char* JSsuffix = "\';";
  size_t totalLength = strlen(JSprefix) + strlen(JSmiddle) + strlen(JSmiddle2) + strlen(JSsuffix) + strlen(id) + strlen(property) + strlen(value) + 1; // +1 for null terminator
  char* JScommand = (char*)malloc(totalLength);
  if (JScommand != NULL) {
    strcpy(JScommand, JSprefix);
    strcat(JScommand, id);
    strcat(JScommand, JSmiddle);
    strcat(JScommand, property);
    strcat(JScommand, JSmiddle2);
    strcat(JScommand, value);
    strcat(JScommand, JSsuffix);
    emscripten_run_script(JScommand);
    free(JScommand);
  } else {
    printf("Failed to allocate memory!\n");
  }
}


/*
 * @brief: Change property of all elements that have a class to a value
 * @param: className - className of elements to be changed
 * @param: property - Property to be changed
 * @param: value - Set value of property
*/
void changeByClass(const char* className, const char* property, const char* value) {
  const char* JSprefix = "var elements = document.getElementsByClassName(\'";
  const char* JSmiddle = "\'); for(var i=0; i<elements.length; i++) { elements[i].";
  const char* JSmiddle2 = " = \'";
  const char* JSsuffix = "\'; }";
  size_t totalLength = strlen(JSprefix) + strlen(JSmiddle) + strlen(JSmiddle2) + strlen(JSsuffix) + strlen(className) + strlen(property) + strlen(value) + 1; // +1 for null terminator
  char* JScommand = (char*)malloc(totalLength);
  if (JScommand != NULL) {
    strcpy(JScommand, JSprefix);
    strcat(JScommand, className);
    strcat(JScommand, JSmiddle);
    strcat(JScommand, property);
    strcat(JScommand, JSmiddle2);
    strcat(JScommand, value);
    strcat(JScommand, JSsuffix);
    emscripten_run_script(JScommand);
    free(JScommand);
  } else {
    printf("Failed to allocate memory!\n");
  }
}

/*
 * @brief: Add an event listener to a button with given ID
 * @param: id - ID of button to be listened
 * @param: funcName - function's name to execute when button is pressed
 * @param: action - action to be listened for
*/
void addListener(const char *id, const char *funcName, const char *action) {
  EM_ASM_({
    var buttonId = UTF8ToString($0); // Convert C string to JavaScript string
    var button = document.getElementById(buttonId);  
    button.addEventListener(UTF8ToString($1), function() { 
      Module.ccall(UTF8ToString($2), 'void', [], []); // Call the C function with no arguments
    });

    button.addEventListener(UTF8ToString($1), function(event) {
      event.preventDefault();
    });
    }, id, action, funcName);
}



/* 
 * @brief: Function to append a child element to a parent element
 * @param: parentId - ID of parent HTML element
 * @param: childHtml - child HTML element's innerHTML
*/
void appendChild(const char* parentId, const char* childHtml) {
    // Get parent element
    EM_ASM({
      var parentId = UTF8ToString($0);
      var parent = document.getElementById(parentId);
      if (parent) {
        // Create a temporary container element
        var container = document.createElement('div');
        container.innerHTML = UTF8ToString($1);

        // Append the child element to the parent
        parent.appendChild(container.firstChild);
      }
    }, parentId, childHtml);
}

/* 
 * @brief: Function to remove a child element from its parent
 * @param: childId - ID of child element to remove
*/
void removeChild(const char* childId) {
    // Get the child element
    EM_ASM({
      var childId = UTF8ToString($0);
      var child = document.getElementById(childId);
      if (child && child.parentNode) {
        // Remove the child element from its parent
        child.parentNode.removeChild(child);
      }
    }, childId);
}

/*
 * @brief: Function to create a new HTML element
 * @param: parentId - ID of parent HTML element
 * @param: elementType - Tag of child element
 * @param: elementId - ID of child element
*/
void createElement(const char* parentId, const char* elementType, const char* elementId) {
    // Get parent element
    EM_ASM({
      var parentId = UTF8ToString($0);
      var parent = document.getElementById(parentId);
      if (parent) {
        // Create a new element
        var newElement = document.createElement(UTF8ToString($1));
        newElement.id = UTF8ToString($2);

        // Append the new element to the parent
        parent.appendChild(newElement);
      }
    }, parentId, elementType, elementId);
}

/*
 * @brief: Dynamically load an external JavaScript file
 * @param: scriptUrl - URL of the external JavaScript file
 * @param: callback - Name of callback function to execute once the script is loaded
 */
void loadExternalScript(const char* scriptUrl, const char* callback) {
  EM_ASM_({
    var script = document.createElement('script');
    script.src = UTF8ToString($0);
    script.onload = function() {
      Module.ccall(UTF8ToString($1), 'v', [], []);
    };
    document.head.appendChild(script);
  }, scriptUrl, callback);
}

/*
 * @brief: Set icon for HTML page
 * @param: path - path to icon
 * @note: path must be selected by HTML file, not C file
*/
void setIcon(const char* path) {
  const char* linkJS = "var link = document.querySelector(\"link[rel~=\'icon\']\");"
                       "if (!link) {"
                       "  link = document.createElement('link');"
                       "  link.rel = 'icon';"
                       "  document.head.appendChild(link);"
                       "}"
                       "link.href = \'";
  const char* suffixJS = "\';";
  size_t totalSize = strlen(linkJS) + strlen(path) + strlen(suffixJS);
  char* JScommand = (char*)malloc(totalSize);
  if (JScommand != NULL) {
    strcpy(JScommand, linkJS);
    strcat(JScommand, path);
    strcat(JScommand, suffixJS);
    emscripten_run_script(JScommand);
    free(JScommand);
  } else {
    fprintf(stderr, "Couldn't allocate memory.\n");
  }
}

/*
 * @brief: Get a property if an element
 * @param: id - ID of HTML element to get element
 * @param: property - property to get value of
 * @return: It's going to return HTML element's property's value as string
*/
char* getPropertyById(const char* id, const char* property) {
  const char* scriptTemplate = "var element = document.getElementById('%s');"
                                "element ? element['%s'] : null;";
  int scriptSize = snprintf(NULL, 0, scriptTemplate, id, property) + 1;
  char* script = (char*)malloc(scriptSize);
  snprintf(script, scriptSize, scriptTemplate, id, property);
  char* result = emscripten_run_script_string(script);
  free(script);
  return result;
}

#else 
#error "This file needs to be ran using emscripten."
#endif
#endif
