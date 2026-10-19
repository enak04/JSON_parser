#include <bits/stdc++.h>

#include "tokenizer.cpp"

// TODO (json-tokenize): implement per the lesson description.

int main() {
    std::string line;

    while(std::getline(std::cin, line)){
        if(line.empty()){
            continue;
        }

        try{
            auto tokens = tokenize(line);
        
            for(const auto& token : tokens){

                switch(token.type){
                    case TokenType::PUNCT:
                        std::cout << "PUNCT " << token.value << std::endl;
                        break;
                    case TokenType::STRING:
                        std::cout << "STRING " << token.value << std::endl;
                        break;
                    case TokenType::NUMBER:
                        std::cout << "NUMBER " << token.value << std::endl;
                        break;
                    case TokenType::TRUE_LITERAL:
                        std::cout << "TRUE true" << std::endl;
                        break;
                    case TokenType::FALSE_LITERAL:
                        std::cout << "FALSE false" << std::endl;
                        break;
                    case TokenType::NULL_LITERAL:
                        std::cout << "NULL null" << std::endl;
                        break;
                    case TokenType::END_OF_FILE:
                        std::cout << "EOF" << std::endl;
                        break;
                }
            }
        } catch(const std::exception& e){
            std::cout << "ERR " << e.what() << std::endl;
        }
    }
}
