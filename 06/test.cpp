#include "Format.hpp"
#include <cassert>

int main() {
    bool caught = false;
    auto text = format("{0}", 2);
    assert(text == "2");

    try {
        text = format("{0", 2);
    }
    catch (const FormatError& e) {
        caught = true;
    }
    assert(caught == true);
    assert(text == "2");
    caught = false;

    try {
        text = format("0}", 2);
    }
    catch (const FormatError& e) {
        caught = true;
    }
    assert(caught == true);
    assert(text == "2");
    caught = false;

    try {
        text = format("{1}", 2);
    }
    catch (const FormatError& e) {
        caught = true;
    }
    assert(caught == true);
    assert(text == "2");
    caught = false;

    try {
        text = format("{{0}}", 2);
    }
    catch (const FormatError& e) {
        caught = true;
    }
    assert(caught == true);
    assert(text == "2");
    caught = false;

    text = format("{}", 2);
    assert(text == "2");

    text = format("");
    assert(text == "");

    text = format("0", 2);
    assert(text == "0");

    text = format("{1} + {1} = {0}", 2, "one", "one");
    assert(text == "one + one = 2");
    std::cout << "DONE" << std::endl;
    return 0;
}