#include "Matrix.hpp"

//testing operation == and !=

int main()
{
    Matrix a(5, 4);
    Matrix b(5, 4);
    Matrix c(5, 4);
    for(size_t i = 0; i < 5; ++i)
        for(size_t j = 0; j < 4; ++j){
            a[i][j] = 1;
            b[i][j] = 3;
            c[i][j] = 1;
        }
    if((a == c) && (a != b))
        std::cout << "operations == and != work GOOD!" << std::endl;
    else
        std::cout << "operations == and != ARE NOT OK!" << std::endl;
    return 0;
}