#include <iostream>
#include <vector>
#include "include/tokens.hpp"

void clear(){
    system("clear");
}

void exit(){

}

int addition(int a, int b){
    return a+b;
}

float addition(float a, float b){
    return a+b;
}

int subtraction(int a, int b){
    return a-b;
}

float subtraction(float a, float b){
    return a-b;
}

int multiplication(int a, int b){
    return a*b;
}

float multiplication(float a, float b){
    return a*b;
}

int division(int a, int b){
    return a/b;
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

void evaluate(std::vector<token *> parsed_tokens){
    std::vector<token *> aux;
    bool end_instruction = false;
}