#include "Matrix.hpp"

//testing operator=

int main()
{
    Matrix a(5, 4);
    for(size_t i = 0; i < 5; ++i)
        for(size_t j = 0; j < 4; ++j)
            a[i][j] = 1;
    Matrix b(2, 2);
    b = a;
    if(b == a)
        std::cout << "operator= is OK!" << std::endl;
    else
        std::cout << "operator= is NOT OK!" << std::endl;
    return 0;
}