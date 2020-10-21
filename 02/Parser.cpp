#include "Parser.hpp"

TokenParser::TokenParser(){
    DigitCallback = [](const uint64_t& a) { std::cout << "digit" << std::endl; };
    StringCallback = [](const std::string& a) { std::cout << "string" << std::endl; };
    StartCallback = []() {std::cout << "Start of parsing" << std::endl; };
    FinishCallback = []() {std::cout << "End of parsing" << std::endl; };
}

void TokenParser::SetStartCallback(std::function<void()> a) { StartCallback = a; };

void TokenParser::SetDigitCallback(std::function<void(const uint64_t& digit)> a) { DigitCallback = a; };

void TokenParser::SetStringCallback(std::function<void(const std::string& str)> a) { StringCallback = a; };

void TokenParser::SetFinishCallback(std::function<void()> a) { FinishCallback = a; };

void TokenParser::Parsing() {
    StartCallback();
    std::string token;
    uint64_t digit;
    size_t num;
    while (!std::cin.eof()) {
        std::cin >> token;
        num = 0;
        try {
            if (token[0] == '+' || token[0] == '-')
                throw std::invalid_argument("It's a string!");
            digit = std::stoull(token, &num);
            if (num == token.size())
            {
                digit_list.push_back(digit);
                DigitCallback(digit);
                continue;
            }
            else
                throw std::invalid_argument("It's a string!");
        }
        catch (std::invalid_argument& e) {}
        catch (...) {}
        string_list.push_back(token);
        StringCallback(token);
    }
    FinishCallback();
}

size_t TokenParser::DigitAmount() { return digit_list.size(); }

size_t TokenParser::StringAmount() { return string_list.size(); }