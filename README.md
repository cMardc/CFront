# CFront
## What is CFront?
CFront is an open-source framework to use `C programming language` in web development.
This is made possible with `emscripten WASM compiler`.
### Installation
To install CFront and use it you need these programs/tools to be installed:
- Text editor
- Web browser (except internet explorer)
- Emscripten
- git
- python3 and SimpleHTTPServer

After this you just have to run
```bash
git clone https://github.com/cMardc/CFront.git
cd CFront
```

See more at [Installation.md](docs/Installation.md).

### Usage
The installed directory `CFront` will probably look like this:
``` bash
$ ls
build  compile.sh  docs  examples  inc	public	src
```
The needed header file will be located at `CFront/inc/frontend.h`.
With this file included you can easily use `C` in `Web development`.

See more at [Usage.md](docs/Usage.md).


## Documentation
### `docs` folder
This framework has been clearly documented in `docs` folder. Every function, it's parameters, return values, purposes and notes have been written there as a `markdown` file.
### Issues and contributions
`CFront` framework is still in development and there might still be bugs in the code. If you find any of them please [open an issue](https://docs.github.com/en/issues/tracking-your-work-with-issues/creating-an-issue).
If you want to upgrade our framework and help us you can [contribute](https://docs.github.com/en/get-started/quickstart/contributing-to-projects) to do this.
Please follow these rules when contributing:
- Write framework code on a single header file: `/inc/frontend.h`.
- Document your code clearly with tags like `brief`, `param`, `return` and `note`.
- If you added a new feature, please add an example on `/examples/` to view it.
- Always test code before pushing it.

## Credits
This library has been made by `cMard` under [MIT License](LICENSE.md).
Happy coding! 👋

