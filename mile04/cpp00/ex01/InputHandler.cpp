#include "main.hpp"

static bool isAllowed(char c, InputType type)
{
	unsigned char uc = static_cast<unsigned char>(c);

	if (type == NUMERIC)
		return (std::isdigit(uc) || std::isspace(uc));
	if (type == ALPHA)
		return (std::isalnum(uc) || std::isspace(uc));
	return (std::isalnum(uc) || std::isspace(uc));
}

std::string getInput(size_t len, InputType type)
{
	std::string input;
	if (!std::getline(std::cin, input))
	{
		std::cin.clear();
		clearerr(stdin);
	}
	
	if (input.empty() || input.length() > len)
		return ("");
	for (size_t i = 0; i < input.length(); i++)
	{
		if (!isAllowed(input[i], type))
			return ("");
	}

	return (input);
}

