#include "Parser.hpp"

using namespace std;

int main()
{
    TokenParser a;
    vector<string> true_log = { string("Start!"), string("digit"), string("string"), string("string"), string("string"),
    string("string"), string("string"), string("string"), string("End of parsing") };
    a.SetStartCallback( [&a]() { GetMasLog(a).push_back("Start!"); } );
    a.Parsing();
    if(a.GetLog() == true_log)
        cout << "Changing start callback function works fine!" << endl;
    else
        cout << "Smth happened while changing start callback function!" << endl;
    return 0;
}