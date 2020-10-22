#include "Parser.hpp"

using namespace std;

int main()
{
    TokenParser a;
    a.SetDigitCallback( [&a](const uint64_t x) { GetMasLog(a).push_back("it's_digit"); } );
    vector<string> true_log = { string("Start of parsing"), string("it's_digit"), string("string"), string("string"), string("string"),
    string("string"), string("string"), string("string"), string("End of parsing") };
    a.Parsing();
    if(a.GetLog() == true_log)
        cout << "Setting digit callback works well!" << endl;
    else
        cout << "There is an error in setting callback function!" << endl;
    return 0;
}