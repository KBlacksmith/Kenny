#include <vector>
#include <map>
#include <iostream>
#include "include/tokens.hpp"
std::vector<token *> parse(std::vector<token *> tokens){
    std::vector<token *> op_stack;
    std::vector<token *> postfix_stack;
    std::map<char, int> hierarchy = {{'^', 3}, {'*', 2}, {'/', 2}, {'+', 1}, {'-', 1}, {'(', 0}};
    //token * prev = NULL;
    for(auto t: tokens){
        /*
        std::cout << "\nOP STACK: ";
        for(auto aux: op_stack){
            std::cout << aux->value << ", ";
        }
        std::cout << "\nPOSTFIX STACK: ";
        for(auto aux: postfix_stack){
            std::cout << aux->value << ", ";
        }c
        */
        if(t->type.compare("NUM") == 0){
            postfix_stack.push_back(t);
        }
        else{
            if(t->value.compare("(") == 0){
                op_stack.push_back(t);
            }
            else if(t->value.compare(")") == 0){
                while (!op_stack.empty())
                {
                    if(op_stack.back()->value.compare("(") != 0){
                        postfix_stack.push_back(op_stack.back());
                        op_stack.pop_back();
                    }
                    else
                        break;
                }
                if(!op_stack.empty())
                    op_stack.pop_back();
                else{
                    std::cout << "Misiing '('\n";
                    return {};
                }   
            }
            else if(op_stack.empty()){
                op_stack.push_back(t);
            }
            else if(hierarchy[t->value.at(0)] > hierarchy[op_stack.back()->value.at(0)]){
                op_stack.push_back(t);
            }
            else{
                while (!op_stack.empty())
                {
                    if(op_stack.back()->value.compare("(") != 0){
                        if(hierarchy[t->value.at(0)] <= hierarchy[op_stack.back()->value.at(0)]){
                            postfix_stack.push_back(op_stack.back());
                            op_stack.pop_back();
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        std::cout << "Missing ')'\n";
                        return {};
                    }
                }
                op_stack.push_back(t);
            }
        }
    }
    /*
    */
    while (!op_stack.empty())
    {
        if(op_stack.back()->value.compare("(") != 0){
            postfix_stack.push_back(op_stack.back());
            op_stack.pop_back();
        }
        else{
            std::cout << "Missing ')'\n";
        }
    }
    
    return postfix_stack;
}