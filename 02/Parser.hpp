#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <string>

class TokenParser {
    std::vector<uint64_t> digit_list;
    std::vector<std::string> string_list;
    std::function<void(const uint64_t& digit)> DigitCallback = [](const uint64_t& a) {std::cout << "digit" << std::endl; };
    std::function<void(const std::string& str)> StringCallback = [](const std::string& a) {std::cout << "string" << std::endl; };
    std::function<void()> StartCallback = []() {std::cout << "Start of parsing" << std::endl; };
    std::function<void()> FinishCallback = []() {std::cout << "End of parsing" << std::endl; };
public:
    void SetStartCallback(std::function<void()> a) { StartCallback = a; };
    void SetDigitCallback(std::function<void(const uint64_t& digit)> a) { DigitCallback = a; };
    void SetStringCallback(std::function<void(const std::string& str)> a) { StringCallback = a; };
    void SetFinishCallback(std::function<void()> a) { FinishCallback = a; };
    void Parsing();
};

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
