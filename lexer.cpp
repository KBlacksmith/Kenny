#include <string>
#include <vector>
#include <map>
#include <regex>
#include <iostream>

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

std::string getString(char quote, std::string sub){
	std::string word;
	int p = 0;
	word.push_back(sub.at(p));
	p++;
	while (p < sub.length())
	{
		word.push_back(sub.at(p));
		if(sub.at(p)==quote){
			return word;
		}
		p++;
	}
	std::cout << "Error: a string ran off the program";
	return "";
}

std::string getNumber(std::string sub){
	std::string num;
	int p = 0;
	num.push_back(sub.at(p));
	p++;
	while (p<sub.length()){
		if(std::regex_match(sub.substr(p, 1), std::regex("[.]|[0-9]"))){
			num.push_back(sub.at(p));
			p++;
		}
		else
			return num;
	}
	return num;
}

std::string getSymbol(std::string sub){
	std::string symbol;
	int p = 0;
	symbol.push_back(sub.at(p));
	p++;
	while (p<sub.length())
	{
		if(std::regex_match(sub.substr(p, 1), std::regex("[_a-zA-Z0-9]"))){
			symbol.push_back(sub.at(p));
			p++;
		}
		else
			return symbol;
	}
	return symbol;
}

std::vector<token *> lexer(std::string *input){
	//input->push_back('\0');
	std::vector<token *> tokens;
	std::string word = "";
	int pos = 0;
	int len = input->length();
	bool failed = false;
	while (pos < len)
	{
		if(std::string(" \n").find(input->at(pos))!=std::string::npos)
		{
			pos++;
		}
		else if(std::string("+-*/").find(input->at(pos))!=std::string::npos){
			word.push_back(input->at(pos));
			tokens.push_back(tokenize("OPERATOR", word));
			word = "";
			pos++;
		}
		else if(std::string("(){},;=:").find(input->at(pos))!=std::string::npos)
		{
			word.push_back(input->at(pos));
			tokens.push_back(tokenize(word, ""));
			word = "";
			pos++;
		}
		else if(std::string("'\"").find(input->at(pos))!=std::string::npos){
			word = getString(input->at(pos), input->substr(pos));
			if(word.compare("")){
				tokens.push_back(tokenize("STR", word));
				pos+=word.length();
				word = "";
			}
			else
				return {};
		}
		else if(std::string(".0123456789").find(input->at(pos))!=std::string::npos){
			word = getNumber(input->substr(pos));
			tokens.push_back(tokenize("NUM", word));
			pos += word.length();
			word = "";
		}
		else if(std::regex_match(input->substr(pos, 1), std::regex("[_a-zA-Z]"))){
			word = getSymbol(input->substr(pos));
			tokens.push_back(tokenize("SYMBOL", word));
			pos += word.length();
			word = "";
		}
		else if(input->at(pos)=='\t'){
			std::cout << "Tabs are not allowed";
			return {};
		}
		else{
			std::cout << "Unexpected '" << input->at(pos) << "' character";
			return {};
		}
	}
	
	return tokens;
}