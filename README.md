#Kenny

Package: kenny
Created with Kenneth's Project Manager

Kenny Reserved words: 
* clear
* exit

LEXER TOKENS:
* SYMBOL
* NUMBER
* STRING
* OPERATOR
* SPECIAL

PARSER: 
   * EXPRESSION TYPES:
        * ASSIGNMENT: 
            FIRST -> SYMBOL
            SECOND -> '='
        * OPERATIONS: 
            MATH: 
                FIRST -> NUM
                SECOND -> SYMBOL
            CONCAT: 
                IF FIRST->STRING: 
                    SECOND->STRING OR NUM
                ELSE IF FIRST -> NUM: 
                    SECOND -> STRING
        * FUNCTION CALLS
        * FUNCTION DEFINITIONS