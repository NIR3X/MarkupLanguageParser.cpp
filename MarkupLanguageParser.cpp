#include "MarkupLanguageParser.h"

using namespace NSMarkupLanguageParser;

NSMarkupLanguageParser::CElement::CElement(
	const std::string& tagName,
	const std::unordered_map<std::string, std::string>& attributes,
	const std::shared_ptr<CElement>& parent
) : TagName(tagName), TextContent({}), Attributes(attributes), Parent(parent), Children({}) {
}

std::vector<std::shared_ptr<CElement>> NSMarkupLanguageParser::Parse(const std::string& input) {
	size_t inputLen = input.length();
	std::vector<std::shared_ptr<CElement>> roots = {};
	std::shared_ptr<CElement> root = nullptr, current = nullptr;

	EState state = EState::Default;
	std::string tagName, textContent, attributeName, attributeValue;
	std::unordered_map<std::string, std::string> attributes = {};
	
	auto openTagParsed = [&] {
		if (current) {
			auto newElement = std::make_shared<CElement>(tagName, attributes, current);
			current->Children.push_back(newElement);
			current = newElement;
		} else {
			root = std::make_shared<CElement>(tagName, attributes);
			roots.push_back(root);
			current = root;
		}
		attributes = {};
	};
	auto closeTagParsed = [&] {
		current = current->Parent.lock();
		attributes = {};
	};
	auto attributeValueParsed = [&] {
		attributes[attributeName] = attributeValue;
	};

	for (size_t i = 0; i < inputLen; ++i) {
		char c = input[i];
		switch (state) {
		case EState::ParsingTagName:
			switch (c) {
			case '>':
				if (tagName.starts_with('/')) {
					closeTagParsed();
				} else {
					openTagParsed();
				}
				state = EState::Default;
				continue;
			case ' ':
			case '\t':
			case '\r':
			case '\n':
				attributeName = {};
				state = EState::ParsingAttributeName;
				continue;
			}
			tagName += c;
			break;
		case EState::ParsingAttributeName:
			switch (c) {
			case '>':
				if (tagName.starts_with('/')) {
					closeTagParsed();
				} else {
					openTagParsed();
				}
				state = EState::Default;
				continue;
			case '=':
				state = EState::ParsingAttributeValue;
				continue;
			case ' ':
			case '\t':
			case '\r':
			case '\n':
				continue;
			}
			attributeName += c;
			break;
		case EState::ParsingAttributeValue:
			if (c == '"') {
				attributeValue = {};
				state = EState::ParsingAttributeValue2;
				continue;
			}
			break;
		case EState::ParsingAttributeValue2:
			if (c == '"') {
				attributeValueParsed();
				state = EState::ParsingAttributeName;
				continue;
			}
			attributeValue += c;
			break;
		default:
			if (c == '<') {
				if (current) {
					current->TextContent += textContent;
				}
				tagName = {};
				textContent = {};
				state = EState::ParsingTagName;
			} else {
				textContent += c;
			}
		}
	}

	return roots;
}
