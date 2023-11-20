# CFront Usage

## How it works 

This library is actually very basic to use and understand. Basically it uses another library called `emscripten` which is based on `WASM`.

Our browsers nowadays support 2 native languages for frontend development.
- JavaScript
- Web assembly

`Web assembly` is a very low level language based on `assembly,` it's like coding in `binary`, but with a little bit of text.

So this means any programming language that can be compiled to `web assembly` can also be used in web development. And this is what `emscripten` does.

`Emscripten` compiles `C/C++` code into `Web assembly`.
[More about emscripten](https://emscripten.org/)

# Tutorial

### Printing and logging
Let's start with basic ones. printing things. Printing to `stdout`, is same as `console.log` .
```c
/* main.c */
#include <stdio.h>
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
int main() {
	printf("Hello, World!\n");
}
```
Let's also have an HTML file, we'll use the same HTML for all the tutorial.
```html
<!-- index.html -->
<html>
	<head>
		<script src='main.js'></script>
	</head>
	<body>
	</body>
</html>
```

Let's compile the code:
```bash
emcc main.c -o main.js
```
When we open the terminal by pressing `F12` on browser:
```
📋 Hello, World! 
```
As you see, we can easily output thing using `printf`.
The macro `EMSCRIPTEN_KEEPALIVE` is for transforming C function into JS code.
<hr>
Let's also have a look at how to show errors:

``` c
/* main.c */
#include <stdio.h>
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
int main() {
	fprintf(stderr, "ERROR: This tutorial is too good!\n");
}

```
When we compile and run this:
```
🚫 ERROR: This tutorial is too good!
```
<hr>
This time we're going to look at warnings. There's no `stdwarn` or any other known file to store warnings. so we can't use `fprintf`, instead we're going to use custom `printWarn`:

```c
/* main.c */
#include <stdio.h>
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
int main() {
	printWarn("WARNING: Markdown is a bit weird.");
}
```
Let's look at terminal this time:
```
❗ WARNING: Markdown is a bit weird.
```
<hr>

## Changing HTML page

### setTitle
It's really important to change content's of web page, logging data is not useful like that.
Let's try to change title of web page. We can achieve it by using `setTitle` function.
```c
/* main.c */
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
int main() {
	setTitle("CFront!");
}
```

As you can see we've successfully changed our web page's title.

<hr>

###  addHTML
This is great. Now let's look at how we can interact with HTML code, using C.
For this we'll use `addHTML` function.

```c
/* main.c */
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
int main() {
	setTitle("CFront!");
	addHTML(
		"<h1>Hello, Web!</h1>"
		"<p>This function is great!</p>"
	);
}
```

As you see, `<body>` tag of our HTML page has been changed:

```html
<html>
	<body>
		<h1>Hello, Web!<h1>
		<p>This function is great!</p>
	</body>
</html>
```

<hr>

Using HTML on C feels awesome, This easily allows you to add dynamic HTML elements.
Leet's look at a very great example:

```c
/* main.c */
#include <stdlib.h>
#include <string.h>
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
void addCard(const char* title, const char* url, const char* imageURL) {
	size_t totalSize = strlen(title) + strlen(url) + strlen(imageURL) + 1;
	// +1 for null terminator

	char* htmlElement = (char*)malloc(totalSize);
	snprintf(htmlElement, 
			"%s%s%s%s%s%s", 
			"<div><p>",
			title,
			"</p><a href='",
			url,
			"'><image src='",
			imageURL,
			"'></image></div>"
	);
	addHTML(htmlElement);
}

EMSCRIPTEN_KEEPALIVE
int main() {
	addCard("Card1", "https://cards.com/1/", "/assets/cards1.png");
	addCard("Card2", "https://cards.com/2/", "/assets/cards2.png");
	addCard("Card3", "https://cards.com/3/", "/assets/cards3.png");
}

```

Here if we actually had `/assets/` and `https://cards.com`, this web page was going to display multiple instances of a card. It's like a placeholder that some values can be changed.

<hr>

### addCSS
Having HTML was good, what about CSS? We have that too! It's called `addCSS`.

```c
/* main.c */
#include <stdio.h>
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
int main() {
	addHTML("<h1>Hello, CSS!</h1>");
	addCSS(
		"h1 {"
		"	color: red;"
		"}"
	);
}
```
Now this styles are going to be added in `<head>` of HTML:

```html
<html>
	<head>
		<style>
			h1 {
				color: red;
			}
		</style>
	</head>
	<body>
		<h1>Hello, CSS!</h1>
		<!-- This will be red -->
	</body>
</html>
```

<hr>

### executeJS

as similiar to HTML and CSS, we also have a function for JavaScript. It's `executeJS`.

```c
/* main.c */
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
int main() {
	executeJS("console.log('Hello, JS!')");
	// same as `printf("Hello, JS!");`
}
```

After opening the web page, the output will be:

```
📋 Hello, JS! 
```


<hr>


### setIcon
We might also want to change icon of our webPage, it's easy: `setIcon`.

```c
/* main.c */
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
int main() {
	setIcon("favicon.ico");
}
```

<hr>

### addListener

Let's say we've a button. and when it's pressed we want to print a message.
We can achieve this with `addListener` function.

```c
/* main.c */
#include <stdio.h>
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
void onPress() {
	printf("Button is pressed!\n");
}

EMSCRIPTEN_KEEPALIVE
int main() {
	addHTML("<button id='btn'>Click!</button>");
	addListener("btn", "onPress", "click");
}
```

As you see this function takes three parameters:
- ID of button
- Name of function
- Event to listen


❗ Reminder: pass function's name as a `string` (`char*`) to `addListener`, not the function itself.

<hr>

### getPropertyById
Let's say we have a `<input type='text'>`, and a `<button>Submit</button>`. When user presses `submit`, we want to print the value of `input`. `getPropertyById` can help us do this. It needs two arguments. `ID` of element, and name of `property` both as `char*`.

```c
/* main.c */
#include <stdio.h>
#include <frontend.h>


EMSCRIPTEN_KEEPALIVE
void onPress() {
	printf(getPropertyById("inp", "value"));
}

EMSCRIPTEN_KEEPALIVE
int main() {
	addHTML(
		"<button id='btn'>Submit</button>"
		"<input type='text' id='inp'></input>"
	);
	addListener("btn", "onPress", "click");
}
```

<hr>

### createElement
This function's like `addHTML` but it adds a child to another parent element with an ID.
It get's three parameters:
- Parent element's ID
- Tag of element
- ID of child element

Let's look at an example

```c
/* main.c */
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
int main() {
	addHTML("<div id='elements'></div>");
	createElement("elements", "p", "element");
}
```

<hr>

### changeByID
This function allows you to change a property of an element. It get's 3 parameters:
- ID of element
- property to change
- new value of property

let's look at an example:

```c
/* main.c */
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
void addElement(const char* value, const char* newID) {
	createElement("elements", "h5", newID);
	changeById(newID, "value", value);
}

EMSCRIPTEN_KEEPALIVE
int main() {
	addHTML("<div id='elements'></div>");
	addElement("firstOne", "el1");
	addElement("secondOne", "el2");
	addElement("thirdOne", "el3");
}
```

As you see, this code allows us to create multiple elements on an HTML `<div>`.

<hr>

### changeByClass
We can also change element's property that has the same class with `changeByClass` function.
It also takes 3 arguments:
- className to look for
- property to change
- new value for property

let's see an example:
```c
/* main.c */
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
int main() {
	addHTML(
		"<div id='container'>"
		"	<button class='btn'>first</button>"
		"	<button class='btn'>second</button>"
		"	<button class='btn'>third</button>"
		"</div>"
	);
	changeByClass("btn", "style.color", "blue");
}
```

This example is going to make all button's text blue.

<hr>

### appendChild

like `createElement` function, this function also creates a new child element, but this one takes `innerHTML`  and add it to the parent.

```c
/* main.c */
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
int main() {
	addHTML("<div id='container'></div>");
	appendChild("container", "<button class='btn'>first</button>");
	appendChild("container", "<button class='btn'>second</button>");
	appendChild("container", "<button class='btn'>third</button>");
}
```

<hr>

### removeChild
This just removes an element from web page. It only takes `ID` of element to delete as argument.

```c
/* main.c */
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
int main() {
	addHTML("<div id='container'></div>");
	appendChild("container", "<button id='btn1'>first</button>");
	appendChild("container", "<button id='btn2'>second</button>");
	appendChild("container", "<button id='btn3'>third</button>");
	removeChild("btn3");
}
```

At this web page, there'll only be two buttons.

<hr>

### loadExternalScript

This function loads another JS file, and when it finishes loading, it executes another function.
It takes 2 parameters:
- Path to .js file
- function's name to execute

❗ Reminder: pass function's name as a `string` (`char*`) to `addListener`, not the function itself.

```js
/* file.js */
console.log('Hello, World!\n')
```

```c
/* main.c */
#include <frontend.h>

EMSCRIPTEN_KEEPALIVE
void onLoad() {
	printf("File loaded.\n");
}

EMSCRIPTEN_KEEPALIVE
int main() {
	loadExternalScript("file.js", "onLoad");
}
```

After running this and looking at terminal you'll see:

```
📋 Hello, World!
📋 File loaded. 
```


# Conclusion

Remember that this framework is still in development, and there might be bugs.
Feel free to contribute and open issues.
### Happy coding!


