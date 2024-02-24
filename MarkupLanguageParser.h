#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace NSMarkupLanguageParser {
	class CElement {
	public:
		std::string TagName, TextContent;
		std::unordered_map<std::string, std::string> Attributes;
		std::weak_ptr<CElement> Parent;
		std::vector<std::shared_ptr<CElement>> Children;

		CElement(
			const std::string& tagName,
			const std::unordered_map<std::string, std::string>& attributes,
			const std::shared_ptr<CElement>& parent = nullptr
		);
	};

	enum class EState {
		Default,
		ParsingTagName,
		ParsingAttributeName,
		ParsingAttributeValue,
		ParsingAttributeValue2,
	};

	std::vector<std::shared_ptr<CElement>> Parse(const std::string& input);
}
