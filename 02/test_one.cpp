#include "Parser.hpp"

using namespace std;

int main()
{
    TokenParser a;
    a.Parsing();
    std::vector<std::string> true_log = { string("Start of parsing"), string("digit"), string("string"), string("string"), string("string"),
    string("string"), string("string"), string("string"), string("End of parsing") };
    if(a.GetLog() == true_log)
        std::cout << "Parsing works OK!" << std::endl;
    else
        std::cout << "Smth bad with Parsing!" << std::endl;
    return 0;
}