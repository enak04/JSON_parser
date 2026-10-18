#pragma once

#include <string>
#include <vector>

enum class TokenType{
    PUNCT,
    STRING,
    NUMBER,
    TRUE_LITERAL,
    FALSE_LITERAL,
    NULL_LITERAL,
    END_OF_FILE
};

struct Token{
    TokenType type;
    std::string value;
};

std::vector<Token> tokenize(const std::string& source);

