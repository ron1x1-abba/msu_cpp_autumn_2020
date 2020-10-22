#include "Parser.hpp"

using namespace std;

int main()
{
    TokenParser a;
    a.SetStringCallback( [&a](const std::string &x) { GetMasLog(a).push_back("It's_string"); } );
    vector<string> true_log = { string("Start of parsing"), string("digit"), string("It's_string"), string("It's_string"), string("It's_string"),
    string("It's_string"), string("It's_string"), string("It's_string"), string("End of parsing") };
    a.Parsing();
    if(a.GetLog() == true_log)
        cout << "Setting string callback function is OK!" << endl;
    else
        cout << "Setting string callback function is NOT OK!" << endl;
    return 0;
}