#include "Matrix.hpp"

//testing operator[][]

int main()
{
    Matrix a(5, 4);
    int x = a[4][3];
    a[2][3] = 3;
    int y = a[2][3];
    if((x == 0) && (y == 3))
        std::cout << "operator[][] is OK!" << std::endl;
    else
        std::cout << "operator[][] is NOT OK!" << std::endl;
    return 0;
}