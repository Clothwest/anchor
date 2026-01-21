# Anchor

**Anchor** is a zero-dependency command-line argument parser built with **C11** standards and full **C++** compatibility.

It aims to provide a robust, context-driven foundation for building complex command-line interfaces.

## Features

* **Zero Dependencies**: No external libraries required; relies solely on the C standard library.
* **C++ Compatible**: Full **C++** compatibility.
* **Context-Driven**: All parsing state is encapsulated in a context object, avoiding global state.

## Integration

Link `Anchor` as a static library and add `include/` to **both** your and Anchor's include path.

If you use **Premake**, you can simply include the project:

```lua
include "path/to/Anchor"
project "YourApp"
    includedirs { "path/to/Anchor/include" }
    links { "Anchor" }
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
