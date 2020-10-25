#include "Matrix.hpp"

//testing operator[][] border control

int main()
{
    Matrix a(5, 4);
    try{
        a[7][7] = 2;
    }
    catch(std::out_of_range& e){
        if(e.what() == std::string("Out of range!"))
            std::cout << "Border control in operator[][] works OK!" << std::endl;
        else
            std::cout << "Border control in operator[][] is BAD!" << std::endl;
    }
    return 0;
}