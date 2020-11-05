#include "BigInt.hpp"
#include <cassert>
#include <sstream>

std::string toString(const BigInt& a){
    std::stringstream s;
    s << a;
    return s.str();
}

void check(const BigInt& actual, const char* expected){
    assert(toString(actual) == std::string(expected));
}

int main(){
    BigInt x = 55;
    check(x, "55");
    std::cout << "contructor from int works OK" << std::endl;
    BigInt y = x;
    check(y, "55");
    std::cout << "copy constructor works OK" << std::endl;
    check(BigInt(std::string("-10")), "-10");
    std::cout << "string constructor works OK" << std::endl;
    BigInt f(10);
    BigInt g(std::move(f));
    check(g, "10");
    std::cout << "moving constructor works OK" << std::endl;
    BigInt d, e(10);
    d = std::move(e);
    check(d, "10");
    std::cout << "moving operator works OK" << std::endl;
    BigInt z(0);
    assert(x == x);
    assert(x == y);
    std::cout << "operator== works OK" << std::endl;
    assert(x != z);
    std::cout << "operator!= works OK" << std::endl;
    assert(x < 100);
    assert(!(x < x));
    std::cout << "operator< works OK" << std::endl;
    assert(x > 50);
    std::cout << "operator> works OK" << std::endl;
    assert(x <= 55);
    assert(x <= x);
    std::cout << "operator<= works OK" << std::endl;
    assert(x >= x);
    std::cout << "operator>= works OK" << std::endl;
    assert(BigInt(0) == -BigInt(0));
    assert(-x < 0);
    std::cout << "unary operator- works OK" << std::endl;
    check(BigInt(10) - BigInt(10), "0");
    check(BigInt(-10) - BigInt(10), "-20");
    check(BigInt(10) - BigInt(-10), "20");
    check(BigInt(-10) - BigInt(-10), "0");
    std::cout << "operator- works OK" << std::endl;
    check(BigInt(10) + BigInt(10), "20");
    check(BigInt(-10) + BigInt(10), "0");
    check(BigInt(-10) + 10, "0");
    check(BigInt(-10) + (-10), "-20");
    std::cout << "operator+ works OK" << std::endl;
    check(BigInt(10) * BigInt(10), "100");
    check(BigInt(-10) * BigInt(10), "-100");
    check(BigInt(10) * 0, "0");
    check(BigInt(-10) * BigInt(-10), "100");
    std::cout << "operator* works OK" << std::endl;
    std::cout << "\nDone\n";
    return 0;
}