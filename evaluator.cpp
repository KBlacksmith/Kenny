#include <iostream>
#include <vector>
#include "include/tokens.hpp"

/*
void clear(){
    system("clear");
}

void exit(){

}

float division(float a, float b){
    return a/b;
}

int modulus(int a, int b){
    return a%b;
}

float pow(float a, float b){
    float m = 1;
    for(int i = 0; i < b; i++){
        for(int i = 0; i < b; i++){
            if(b>0)
                m *= a;
            else
                m/=a;
        }
    }
    return m;
}

std::string str(){
    return "";
}
*/

std::string plus(float a, float b){
    return std::to_string(a+b);
}

std::string minus(float a, float b){
    return std::to_string(a-b);
}

std::string multiply(float a, float b){
    return std::to_string(a*b);
}

std::string divide(float a, float b){
    return std::to_string(a/b);
}

std::string power(float a, float b){
    float p = 1;
    if(b>0){
        for(int i = 0; i<b; i++){
            p *= a;
        }
    }
    else{
        for(int i = 0; i<-b; i++){
            p/=a;
        }
    }
    return std::to_string(p);
}

void evaluate(std::vector<token *> parsed_tokens){
    std::vector<token *> aux;
    std::vector<token *> temp;
    token * helper;
    int pos = 0;
    while (pos < parsed_tokens.size())
    {
        for(auto t: parsed_tokens){
            std::cout << t->value << " ";
        }
        std::cout << std::endl;
        if(parsed_tokens.at(pos)->type.compare("OPERATOR")==0){
            if(pos>=2){
                if(parsed_tokens.at(pos-1)->type.compare("NUM")==0){
                    if(parsed_tokens.at(pos-2)->type.compare("NUM")==0){
                        if(parsed_tokens.at(pos)->value.compare("+")==0){
                            helper = tokenize("NUM", plus(std::stof(parsed_tokens.at(pos-2)->value), std::stof(parsed_tokens.at(pos-1)->value)));
                        }
                        else if(parsed_tokens.at(pos)->value.compare("-")==0){
                            helper = tokenize("NUM", minus(std::stof(parsed_tokens.at(pos-2)->value), std::stof(parsed_tokens.at(pos-1)->value)));
                        }
                        else if(parsed_tokens.at(pos)->value.compare("*")==0){
                            helper = tokenize("NUM", multiply(std::stof(parsed_tokens.at(pos-2)->value), std::stof(parsed_tokens.at(pos-1)->value)));
                        }
                        else if(parsed_tokens.at(pos)->value.compare("/")==0){
                            helper = tokenize("NUM", divide(std::stof(parsed_tokens.at(pos-2)->value), std::stof(parsed_tokens.at(pos-1)->value)));
                        }
                        /*
                        else if(parsed_tokens.at(pos)->value.compare("%")==0){

                        }
                        */
                        else if(parsed_tokens.at(pos)->value.compare("^")==0){
                            helper = tokenize("NUM", power(std::stof(parsed_tokens.at(pos-2)->value), std::stof(parsed_tokens.at(pos-1)->value)));
                        }
                        parsed_tokens.insert(parsed_tokens.begin()+pos-2, helper);
                        for(int i = 0; i<3; i++){
                            helper = parsed_tokens.at(pos-1);
                            parsed_tokens.erase(parsed_tokens.begin()+pos-1);
                            delete helper;
                        }
                        pos-=2;
                        continue;
                    }
                }
            }
        }
        pos++;
    }
    return;
}