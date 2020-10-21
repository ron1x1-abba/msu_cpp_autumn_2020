#include "Parser.hpp"

int main()
{
    TokenParser a;
    a.SetDigitCallback( [](uint64_t x) {std::cout << "digit " << x << std::endl; } );
    a.SetStringCallback( [](std::string x) {std::cout << "string " << x << std::endl; } );
    a.SetStartCallback( []() {std::cout << "Start!" << std::endl; } );
    a.SetFinishCallback( []() {std::cout << "Finish!" << std::endl; });
    a.Parsing();
    std::cout << "Amount of digit tokens : " << a.DigitAmount() << std::endl;
    std::cout << "Amount of string tokens : " << a.StringAmount() << std::endl;
    return 0;
}