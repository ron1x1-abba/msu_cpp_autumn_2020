#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <type_traits>
#include <stdexcept>

class FormatError : public std::exception {
    size_t pos;
    std::string err;
public:
    FormatError(const std::string& str, size_t p) : pos(p), err(str) {}
    ~FormatError() = default;
    FormatError() = default;
    FormatError(const FormatError& a) : pos(a.pos), err(a.err) {}

    bool operator==(const FormatError& a) {
        if((a.err == err) && (pos == a.pos))
            return true;
        else
            return false;
    }

    FormatError& operator=(const FormatError& a) {
        if((*this) == a)
            return (*this);
        ;
    }

    size_t get_pos() const { return pos; }

    const char* what() const noexcept {
        return err.c_str();
    }
};

template<class T>
std::string toStr(const T& obj) {
    std::stringstream ss;
    ss << obj;
    return ss.str();
}

template<typename... ArgsT>
std::string format(const std::string& s, ArgsT... args) {
    if(s.empty())
        return s;
    std::vector<std::string> arguments = {toStr(std::forward<ArgsT>(args))...};
    char c;
    std::string out;
    size_t start;
    for(size_t i = 0; i < s.size(); ++i) {
        c = s[i];
        if (c == '{') {
            start = i;
            std::string val;
            c = s[++i];
            while((c != '}') && (i != s.size() - 1)) {
                if(std::isdigit(c)) {
                    val += c;
                }
                else
                    throw FormatError("incorrect usage of {}", i);
                c = s[++i];
            }
            if(c == '}') {
                if (val.empty()) {
                    out += arguments[0];
                    continue;
                }
                else {
                    size_t num;
                    try {
                        num = std::stoul(val);
                    }
                    catch (const std::logic_error& e) {
                        std::cout << e.what() << std::endl;
                        return s;
                    }
                    if(num > arguments.size() - 1)
                        throw FormatError("value inside brackets is more than amount of params!", start);
                    else {
                        out += arguments[num];
                        continue;
                    }
                }
            }
            else {
                throw FormatError("incorrect usage of {}. Expected '}' in the end!", i);
            }
        }
        else if (c == '}') {
            throw FormatError("'}' is outside of the context of usage", i);
        }
        out += c;
    }
    return out;
}

std::string format(const std::string& s) {
    return s;
}