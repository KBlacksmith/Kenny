#include <iostream>
#include <string>
#include <regex>
#include "include/lexer.hpp"
#include "include/parser.hpp"


void trimmer(std::string * input){
	int start = 0, end = input->length();
	while (input->substr(start, end).starts_with(" "))
	{
		//std::cout << "'" << input->substr(start, end) << "'\n";
		start++;
		end--;
	}
	while (input->substr(start, end-start).ends_with(" "))
	{
		//std::cout << "'" << input->substr(start, end-start) << "'\n";
		end--;
	}
	//std::cout << "'" << input->substr(start, end-start) << "'\n";
	
}

int main(int argc, char * argv[]){
	std::string input = "";
	switch (argc)
	{
	case 1:
	{
		std::cout << "basic > ";
		while (getline(std::cin, input))
		{	
			if(!input.empty()){
				std::cout << "TOKENS: ";
				for(token * t: lexer(&input)){
					std::cout << "[" << t->type << ", " << t->value << "], ";
				}
				std::cout << '\n';
				std::cout << "PARSER: ";
				for(token *p: parse(lexer(&input))){
					std::cout << p->value << " ";
				}
				std::cout << '\n';
			}
			std::cout << "basic > ";
		}
	}
		break;
	
	default:
		std::cout << "Too many arguments\n";
		break;
	}
	std::cout << "Oh my God, You Killed Kenny! You Bastard!\n";
	return 0;
}
