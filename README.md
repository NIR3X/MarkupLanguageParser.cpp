# MarkupLanguageParser.cpp - Simple C++ Parser for Markup Language

This repository contains a simple markup language parser implemented in C++. It provides functionality to parse markup language input and construct a tree-like structure representing the parsed elements.

## Features

* Parses markup language input into a tree-like structure.
* Supports parsing of tags, attributes, and text content.
* Provides an easy-to-use interface for parsing markup language.

## Installation

To use this package, you can clone the repository and compile it using a C++ compiler:

```bash
git clone https://github.com/NIR3X/MarkupLanguageParser.cpp
cd MarkupLanguageParser.cpp
make
```

## Usage

To use the markup language parser, include the `MarkupLanguageParser.h` header file in your C++ project. Then, call the `Parse` function, passing the markup language input as a string. This function will return a vector of shared pointers to `CElement` objects, representing the root elements of the parsed tree.

```cpp

#include "MarkupLanguageParser.h"
#include <iostream>

int main() {
	std::string input = "<root><person><name>John Doe</name><age>30</age></person></root>";
	
	auto roots = NSMarkupLanguageParser::Parse(input);
	
	// Process parsed elements...
	
	return 0;
}
```

## License

[![GNU AGPLv3 Image](https://www.gnu.org/graphics/agplv3-155x51.png)](https://www.gnu.org/licenses/agpl-3.0.html)

This program is Free Software: You can use, study share and improve it at your
will. Specifically you can redistribute and/or modify it under the terms of the
[GNU Affero General Public License](https://www.gnu.org/licenses/agpl-3.0.html) as
published by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
