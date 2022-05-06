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
                SECOND -> OPERATOR
            CONCAT: 
                IF -> STRING
                SECOND -> PLUS
        * FUNCTION CALLS
        * FUNCTION DEFINITIONS