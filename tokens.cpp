#include <string>
struct token
{
	std::string type;
	std::string value;
};

token * tokenize(std::string type, std::string value){
	token * new_token = new token;
	new_token->type.assign(type);
	new_token->value.assign(value);
	return new_token;
}