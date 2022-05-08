#include <vector>
#include <map>
#include <iostream>
#include "include/tokens.hpp"
std::vector<token *> parse(std::vector<token *> tokens){
    std::vector<token *> op_stack;
    std::vector<token *> postfix_stack;
    int h = 5;
    std::map<char, int> hierarchy = {{'+', 2}, {'-', 2}, {'*', 3}, {'/', 3}, /*{'%', 3},*/ {'^', 4}, {'(', 1}, {'=', 0}};
    std::map<std::string, int> functions = {{"print", h}, {"str", h}, {"exit", h}, {"clear", h}};
    token * prev = NULL;
    for(auto t: tokens){
        /*
        std::cout << "\nOP STACK: ";
        for(auto op: op_stack){
            std::cout << op->value << " ";
        }
        std::cout << "\nPOSTFIX: ";
        for(auto p: postfix_stack){
            std::cout << p->value << " ";
        }
        */
        if(t->type.compare("(") == 0){
            t->hierarchy = 1;
            op_stack.push_back(t);
        }
        else if(t->type.compare(")") == 0){
            while (!op_stack.empty())
            {
                if(op_stack.back()->type.compare("(") == 0){
                    //op_stack.pop_back();
                    break;
                }
                else{
                    postfix_stack.push_back(op_stack.back());
                    op_stack.pop_back();
                }
            }
            if(!op_stack.empty()){
                //postfix_stack.push_back(op_stack.back());
                //t->hierarchy = 1;
                //postfix_stack.push_back(t);
                op_stack.pop_back();
            }
            else{
                std::cout << "Missing '('";
                return {};
            }
            
        }
        else if(t->type.compare("NUM") == 0 || t->type.compare("STR")==0){
            postfix_stack.push_back(t);
        }
        else if(t->type.compare("SYMBOL") == 0){
            if(functions.contains(t->value)){
                t->type = "FUNCTION";
                t->hierarchy = h;
                op_stack.push_back(t);
            }
            else{
                postfix_stack.push_back(t);
            }
        }
        else if(t->type.compare("OPERATOR")==0){
            t->hierarchy = hierarchy[t->value.at(0)];
            if(prev==NULL){
                postfix_stack.push_back(tokenize("NUM", "0"));
                op_stack.push_back(t);
            }
            else{
                if(prev->type.compare("OPERATOR")==0){
                    if(t->value.compare("-")==0){
                        if(prev->value.compare("+")==0){
                            postfix_stack.push_back(tokenize("NUM", "0"));
                            op_stack.push_back(t);
                        }
                        else if(prev->value.compare("-")==0){
                            op_stack.back()->value = "+";
                        }
                        else if(prev->value.compare("*")==0 || prev->value.compare("/")==0){
                            postfix_stack.push_back(tokenize("NUM", "-1"));
                            postfix_stack.push_back(tokenize("OPERATOR", "*"));
                        }
                        else if(prev->value.compare("^")==0){
                            postfix_stack.push_back(tokenize("NUM", "0"));
                            op_stack.push_back(t);
                        }
                    }
                    else{
                        std::cout << "Error: Incorrect use of operator '" << t->value << "'";
                        return {};
                    }
                }
                else if(prev->type.compare("(")==0){
                    postfix_stack.push_back(tokenize("NUM", "0"));
                    op_stack.push_back(t);
                }
                else{
                    while (!op_stack.empty())
                    {
                        if(t->hierarchy > op_stack.back()->hierarchy){
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
        }
        else if(t->type.compare("=")==0){
            op_stack.push_back(t);
        }
        else if(t->type.compare(";") == 0){
            t->hierarchy = -1;
            while (!op_stack.empty())
            {
                if(op_stack.back()->type.compare("(")!=0){
                    postfix_stack.push_back(op_stack.back());
                    op_stack.pop_back();
                }
                else{
                    std::cout << "Missing ')'";
                    return {};
                }
            }
            postfix_stack.push_back(t);
            prev = NULL;
            continue;
        }
        prev = t;
    }
    while (!op_stack.empty())
    {
        if(op_stack.back()->type.compare("(")!=0){
            postfix_stack.push_back(op_stack.back());
            op_stack.pop_back();
        }
        else{
            std::cout << "Missing ')'";
            return {};
        }
    }
    if(postfix_stack.back()->type.compare(";")!=0){
        std::cout << "Missing ';'";
        return {};
    }
    return postfix_stack;
}