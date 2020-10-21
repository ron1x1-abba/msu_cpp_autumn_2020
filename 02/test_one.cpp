#include "Parser.hpp"

int main()
{
    TokenParser a;
    a.Parsing();
    std::cout << "Amount of digit tokens : " << a.DigitAmount() << std::endl;
    std::cout << "Amount of string tokens : " << a.StringAmount() << std::endl;
    return 0;
}