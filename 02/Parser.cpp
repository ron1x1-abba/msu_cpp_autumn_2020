#include "Parser.hpp"

TokenParser::TokenParser(){
    DigitCallback = [this](const uint64_t a) { GetLog().push_back("digit"); };
    StringCallback = [this](const std::string& a) { GetLog().push_back("string"); };
    StartCallback = [this]() { GetLog().push_back("Start of parsing"); };
    FinishCallback = [this]() { GetLog().push_back("End of parsing"); };
}

void TokenParser::SetStartCallback(std::function<void()> a) { StartCallback = a; };

void TokenParser::SetDigitCallback(std::function<void(const uint64_t digit)> a) { DigitCallback = a; };

void TokenParser::SetStringCallback(std::function<void(const std::string& str)> a) { StringCallback = a; };

void TokenParser::SetFinishCallback(std::function<void()> a) { FinishCallback = a; };

void TokenParser::Parsing() {
    StartCallback();
    std::string token;
    uint64_t digit;
    while (!std::cin.eof()) {
        std::cin >> token;
        if(!token.empty() && (token.find_first_not_of("0123456789") == token.npos)){
            digit = std::stoull(token);
            digit_list.push_back(digit);
            DigitCallback(digit);
            continue;
        }
        string_list.push_back(token);
        StringCallback(token);
    }
    FinishCallback();
}

size_t TokenParser::DigitAmount() { return digit_list.size(); }

size_t TokenParser::StringAmount() { return string_list.size(); }

std::vector<uint64_t>& TokenParser::GetDigits() { return digit_list; }

std::vector<std::string>& TokenParser::GetStrings() { return string_list; }

std::vector<std::string>& TokenParser::GetLog() { return log_list; }

std::vector<std::string>& GetMasLog(TokenParser& b) { return b.GetLog(); }