#include <vector>
#include <map>
#include <iostream>
#include "include/tokens.hpp"
std::vector<token *> parse(std::vector<token *> tokens){
    std::vector<token *> op_stack;
    std::vector<token *> postfix_stack;
    //token * aux;
    std::map<char, int> hierarchy = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}, {'(', 0}};
    for(auto t: tokens){
        if(t->type.compare("(") == 0){
            op_stack.push_back(t);
        }
        else if(t->type.compare(")") == 0){
            while (!op_stack.empty())
            {
                if(op_stack.back()->type.compare("(") == 0){
                    op_stack.pop_back();
                    break;
                }
                else{
                    postfix_stack.push_back(op_stack.back());
                    op_stack.pop_back();
                }
            }
            
        }
        else if(t->type.compare("NUM") == 0){
            postfix_stack.push_back(t);
        }
        else{
            while (!op_stack.empty())
            {
                if(hierarchy[t->value.at(0)] > hierarchy[op_stack.back()->value.at(0)]){
                    op_stack.push_back(t);
                    break;
                }
                else{
                    postfix_stack.push_back(op_stack.back());
                    op_stack.pop_back();
                }
            }
            if(op_stack.empty()){
                op_stack.push_back(t);
            }
        }
    }
    while (!op_stack.empty())
    {
        postfix_stack.push_back(op_stack.back());
        op_stack.pop_back();
    }
    
    return postfix_stack;
}