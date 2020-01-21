# FSM Tokenizer

This is a tokenizer for a compiler that takes well-formed C++ and splits it into gramatical tokens such as
identifiers, keywords, symbols, etc.

To run the program:
1. Download the source code as a zip file
2. Extract the zip file
3. In a terminal run "./make"
4. In a terminal run "./tokenize parserClasses.cpp"

There are other test cases that can be run.  These test cases are found in the testCases folder
1. In a terminal run "./tokenize ./testCases/stressTestA.cpp"

Here is an example of output
1. In a terminal run ./tokenize ./testCases/helloworld.cpp 

The following lines are output from tokenizing a hello world program in C++

Opening input file: ./testCases/helloworld.cpp  
    Token 1: #  
    Token 2: include  
    Token 3: <iostream>  
    Token 4: \n  
    Token 5: int  
    Token 6: main  
    Token 7: (  
    Token 8: )  
    Token 9: \n  
    Token 10: {  
    Token 11: \n  
    Token 12: std  
    Token 13: ::  
    Token 14: cout  
    Token 15: <<  
    Token 16: "Hello, World!"  
    Token 17: ;  
    Token 18: \n  
    Token 19: return  
    Token 20: 0  
    Token 21: ;  
    Token 22: \n  
    Token 23: }  
    Token 24: \n  
    Token 25: \n  
    Number of tokens processed: 25  


