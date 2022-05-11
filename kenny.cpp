#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include "include/lexer.hpp"
#include "include/parser.hpp"
#include "include/evaluator.hpp"


void trimmer(std::string * input){
	int start = 0, end = input->length();
	while (input->substr(start, end).starts_with(" "))
	{
		start++;
		end--;
	}
	while (input->substr(start, end-start).ends_with(" "))
	{
		end--;
	}
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
			trimmer(&input);
			if(!input.empty()){
				//evaluate(parse(lexer(&input)));
				for(auto t: lexer(&input)){
					std::cout << "[" << t->type << ", " << t->value << "], ";
				}
				std::cout << std::endl;
				for(auto t: parse(lexer(&input))){
					std::cout << t->value << " ";
				}
			}
			std::cout << "\nbasic > ";
		}
		std::cout << "Oh my God, You Killed Kenny! You Bastard!\n";
	}
		break;
	case 2: 
	{
		/*
		if(std::regex_match(std::string(argv[1]), std::regex("[a-zA-Z][_a-zA-Z0-9]*[.]ken"))){
			//std::string file_name = argv[1];
			std::ifstream ken_file(std::string(argv[1]).data());
			while (getline(ken_file, input))
			{
				for(token * t: lexer(&input)){
					std::cout << "[" << t->type << ", " << t->value << "], ";
				}
			}
			std::cout << '\n';
		}
		*/
	}
	break;
	default:
		std::cout << "Too many arguments\n";
		break;
	}
	return 0;
}
