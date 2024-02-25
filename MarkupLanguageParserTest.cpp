#include "MarkupLanguageParser.h"
#include <cassert>
#include <iostream>

int main() {
	std::string input = R"(<root hello="world" disabled test a="b">
	<person>
		<name>John Doe</name>
		<age>30</age>
	</person>
	<person>
		<name>Jane Smith</name>
		<age>25</age>
	</person>
</root>
<root></root>)";

	auto roots = NSMarkupLanguageParser::Parse(input);
	assert(roots.size() == 2);
	
	auto current = roots[0];
	assert(current->tagName == "root");
	assert(current->attributes["hello"] == "world");
	assert(current->attributes["disabled"].empty());
	assert(current->attributes["test"].empty());
	assert(current->attributes["a"] == "b");
	assert(current->children.size() == 2);

	current = current->children[0];
	assert(current->tagName == "person");
	assert(current->children.size() == 2);

	current = current->children[0];
	assert(current->tagName == "name");
	assert(current->textContent == "John Doe");

	current = current->parent.lock();
	assert(current != nullptr);
	assert(current->tagName == "person");
	assert(current->children.size() == 2);

	current = current->children[1];
	assert(current->tagName == "age");
	assert(current->textContent == "30");

	current = current->parent.lock();
	assert(current != nullptr);
	assert(current->tagName == "person");
	assert(current->children.size() == 2);

	current = current->parent.lock();
	assert(current != nullptr);
	assert(current->tagName == "root");
	assert(current->children.size() == 2);

	current = current->children[1];
	assert(current->tagName == "person");
	assert(current->children.size() == 2);

	current = current->children[0];
	assert(current->tagName == "name");
	assert(current->textContent == "Jane Smith");

	current = current->parent.lock();
	assert(current != nullptr);
	assert(current->tagName == "person");
	assert(current->children.size() == 2);

	current = current->children[1];
	assert(current->tagName == "age");
	assert(current->textContent == "25");

	current = roots[1];
	assert(current->tagName == "root");
	assert(current->children.size() == 0);
	assert(current->textContent.empty());

	std::cout << "PASS" << std::endl;
}
