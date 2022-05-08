#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include "include/tokens.hpp"

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
	bool floating = false;
	while (p < sub.length())
	{
		if(std::regex_match(sub.substr(p, 1), std::regex("[.]|[0-9]"))){
			if(sub.at(p)=='.' && floating){
				return num;
			}
			else if(sub.at(p)=='.'){
				floating = true;
			}
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
		else if(std::string("+-*/^").find(input->at(pos))!=std::string::npos){//To add %
			word.push_back(input->at(pos));
			tokens.push_back(tokenize("OPERATOR", word));
			word = "";
			pos++;
		}
		else if(std::string("(){},;=:").find(input->at(pos))!=std::string::npos)
		{
			word.push_back(input->at(pos));
			tokens.push_back(tokenize(word, word));
			word = "";
			pos++;
		}
		else if(std::string("'\"").find(input->at(pos))!=std::string::npos){
			word = getString(input->at(pos), input->substr(pos));
			if(word.compare("")!=0){
				tokens.push_back(tokenize("STR", word.substr(1, word.length()-2)));
				pos+=word.length();
				word = "";
			}
			else
				return {};
		}
		else if(std::string("0123456789").find(input->at(pos))!=std::string::npos){
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
			std::cout << "Error: Tabs are not allowed";
			return {};
		}
		else{
			std::cout << "Error: ";
			for(int i = 0; i<=pos; i++){
				std::cout << input->at(i);
			}
			std::cout << "\n";
			for(int i = 0; i<pos+7; i++){
				std::cout << " ";
			}
			std::cout << "^\n";
			std::cout << "Unexpected '" << input->at(pos) << "' character";
			return {};
		}
	}
	
	return tokens;
}