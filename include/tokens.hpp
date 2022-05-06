#include <string>
struct token
{
	std::string type;
	std::string value;
	int hierarchy;
};


token * tokenize(std::string type, std::string value);