#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <string>

class TokenParser {
    std::vector<uint64_t> digit_list;
    std::vector<std::string> string_list;
    std::function<void(const uint64_t& digit)> DigitCallback;
    std::function<void(const std::string& str)> StringCallback;
    std::function<void()> StartCallback;
    std::function<void()> FinishCallback;
public:
    TokenParser();
    void SetStartCallback(std::function<void()> a);
    void SetDigitCallback(std::function<void(const uint64_t& digit)> a);
    void SetStringCallback(std::function<void(const std::string& str)> a);
    void SetFinishCallback(std::function<void()> a);
    void Parsing();
    size_t DigitAmount();
    size_t StringAmount();
};
