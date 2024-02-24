#include "MarkupLanguageParser.h"
#include <cassert>
#include <iostream>

int main() {
	std::string input = R"(<root hello="world">
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
	assert(current->TagName == "root");
	assert(current->Attributes["hello"] == "world");
	assert(current->Children.size() == 2);

	current = current->Children[0];
	assert(current->TagName == "person");
	assert(current->Children.size() == 2);

	current = current->Children[0];
	assert(current->TagName == "name");
	assert(current->TextContent == "John Doe");

	current = current->Parent.lock();
	assert(current != nullptr);
	assert(current->TagName == "person");
	assert(current->Children.size() == 2);

	current = current->Children[1];
	assert(current->TagName == "age");
	assert(current->TextContent == "30");

	current = current->Parent.lock();
	assert(current != nullptr);
	assert(current->TagName == "person");
	assert(current->Children.size() == 2);

	current = current->Parent.lock();
	assert(current != nullptr);
	assert(current->TagName == "root");
	assert(current->Children.size() == 2);

	current = current->Children[1];
	assert(current->TagName == "person");
	assert(current->Children.size() == 2);

	current = current->Children[0];
	assert(current->TagName == "name");
	assert(current->TextContent == "Jane Smith");

	current = current->Parent.lock();
	assert(current != nullptr);
	assert(current->TagName == "person");
	assert(current->Children.size() == 2);

	current = current->Children[1];
	assert(current->TagName == "age");
	assert(current->TextContent == "25");

	current = roots[1];
	assert(current->TagName == "root");
	assert(current->Children.size() == 0);
	assert(current->TextContent.empty());

	std::cout << "PASS" << std::endl;
}
