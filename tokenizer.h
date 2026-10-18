#pragma once

#include <cctype>
#include <stdexcept>
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

inline std::vector<Token> tokenize(const std::string& source) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < source.size()) {
        char c = source[i];

        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            i++;
            continue;
        }

        if (std::string("{}[],:").find(c) != std::string::npos) {
            tokens.push_back({TokenType::PUNCT, std::string(1, c)});
            i++;
            continue;
        }

        if (c == '"') {
            i++;
            std::string value;

            while (i < source.size() && source[i] != '"') {
                if (source[i] == '\\') {
                    i++;

                    if (i >= source.size()) {
                        throw std::runtime_error("unterminated string");
                    }

                    switch (source[i]) {
                        case 'n': value += '\n'; break;
                        case 't': value += '\t'; break;
                        case 'r': value += '\r'; break;
                        case '"': value += '"'; break;
                        case '\\': value += '\\'; break;
                        case 'b': value += '\b'; break;
                        case 'f': value += '\f'; break;
                        case '/': value += '/'; break;
                        default:
                            throw std::runtime_error("invalid escape");
                    }
                } else {
                    value += source[i];
                }

                i++;
            }

            if (i >= source.size()) {
                throw std::runtime_error("unterminated string");
            }

            i++;
            tokens.push_back({TokenType::STRING, value});
            continue;
        }

        if (c == '-' || std::isdigit(static_cast<unsigned char>(c))) {
            size_t start = i;

            if (source[i] == '-') {
                i++;
            }

            while (i < source.size() &&
                   std::isdigit(static_cast<unsigned char>(source[i]))) {
                i++;
            }

            if (i < source.size() && source[i] == '.') {
                i++;

                while (i < source.size() &&
                       std::isdigit(static_cast<unsigned char>(source[i]))) {
                    i++;
                }
            }

            if (i < source.size() &&
                (source[i] == 'e' || source[i] == 'E')) {
                i++;

                if (i < source.size() &&
                    (source[i] == '+' || source[i] == '-')) {
                    i++;
                }

                while (i < source.size() &&
                       std::isdigit(static_cast<unsigned char>(source[i]))) {
                    i++;
                }
            }

            tokens.push_back({
                TokenType::NUMBER,
                source.substr(start, i - start)
            });
            continue;
        }

        if (source.compare(i, 4, "true") == 0) {
            tokens.push_back({TokenType::TRUE_LITERAL, "true"});
            i += 4;
            continue;
        }

        if (source.compare(i, 5, "false") == 0) {
            tokens.push_back({TokenType::FALSE_LITERAL, "false"});
            i += 5;
            continue;
        }

        if (source.compare(i, 4, "null") == 0) {
            tokens.push_back({TokenType::NULL_LITERAL, "null"});
            i += 4;
            continue;
        }

        throw std::runtime_error(
            "unexpected character '" + std::string(1, c) +
            "' at position " + std::to_string(i)
        );
    }

    tokens.push_back({TokenType::END_OF_FILE, ""});
    return tokens;
}
