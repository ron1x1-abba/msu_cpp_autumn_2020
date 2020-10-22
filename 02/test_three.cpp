#include "Parser.hpp"

using namespace std;

int main()
{
    TokenParser a;
    a.SetFinishCallback( [&a]() { GetMasLog(a).push_back("Finish!") ;});
    vector<string> true_log = { string("Start of parsing"), string("digit"), string("string"), string("string"), string("string"),
    string("string"), string("string"), string("string"), string("Finish!") };
    a.Parsing();
    if(a.GetLog() == true_log)
        cout << "Changing finish callback function works good!" << endl;
    else
        cout << "Changing finish callback function works bad!" << endl;
    return 0;
}