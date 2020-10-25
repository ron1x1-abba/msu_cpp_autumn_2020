#include "Matrix.hpp"

//testing *=

int main()
{
    Matrix a(5, 4);
    Matrix b(5, 4);
    for(size_t i = 0; i < 5; ++i)
        for(size_t j = 0; j < 4; ++j){
            a[i][j] = 1;
            b[i][j] = 3;
        }
    if((a*=3) == b)
        std::cout << "operation *= works GOOD!" << std::endl;
    else
        std::cout << "operation *= IS NOT OK!" << std::endl;
    return 0;
}