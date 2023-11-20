# CFront installation
## Tools

Before installing `CFront` you'll need a few tools to be installed:
- Text editor
- Web browser 
- Emscripten
- git
- python3 and Simple HTTP Server Module

You can use any text editor of your choice, it doesn't matter. That also applies to web browser.

### Emscripten
`Emscripten` is a `C to WASM compiler`. To run `C programming language` on web and create a JavaScript code out of it. `CFront` framework is also based on `emscripten`.  To install `emscripten` see [emscripten installation page](https://emscripten.org/docs/getting_started/downloads.html).

### Git
`Git` is a open-source version controlling system. `Git` also allows you to copy other's repositories like `CFront`. To install git refer to it's [documentation](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git). 

### Python3 and Simple HTTP Server 
`python3` is an interpreter for `python programming language`. And `Simple HTTP Server` module let's you to create a local HTTP server using `python`. This is for opening Web page you've made. If you open HTML file with `file:///` starting, the browser will not let you use linkings like `<link>` and `<script src="...">`
Here's installation of [python3](https://www.python.org/downloads/) and [Simple HTTP Server](https://www.digitalocean.com/community/tutorials/python-simplehttpserver-http-server).

## Installing

### Cloning repository
To install `CFront` run these commands on your terminal:
```bash
git clone https://github.com/cMardc/CFront.git
cd CFront
```
After this you've successfully installed `CFront` on you system.

### Testing
After you've installed `CFront` your directory will probably look like this:
```
$ ls
build  compile.sh  docs  examples  inc	LICENSE.md  public  README.md  src
```
Let's breakdown the directories:

| Directory | Meaning                                            |
|-----------|----------------------------------------------------|
| build     | This will contain WASM binaries and JS code        |
| docs      | contains documentation files                       |
| examples  | This directory has examples for `Cfront` framework |
| inc       | Contains `frontend.h` header file                  |
| src       | Contains `main.c` file                             |

Let's run the example with `compile.sh` file:
```bash
bash compile.sh
Serving HTTP on 0.0.0.0 port 8081 (http://0.0.0.0:8081/) ...
```
if we go to `http://0.0.0.0:8081/public`, we'll see a web page created with `src/main.c` file.
You can also run examples in `/examples/` to see more.

Thanks for installing!

