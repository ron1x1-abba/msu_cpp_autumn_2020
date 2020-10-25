#include "Matrix.hpp"

//testing summing of matrices

int main()
{
    Matrix a(5, 4);
    Matrix b(5, 4);
    Matrix c(5, 4);
    for(size_t i = 0; i < 5; ++i)
        for(size_t j = 0; j < 4; ++j){
            a[i][j] = 1;
            b[i][j] = 2;
            c[i][j] = 1;
        }
    if((a + c) == b)
        std::cout << "summing of matrices works OK!" << std::endl;
    else
        std::cout << "summing of matrices has smth WRONG!" << std::endl;
    return 0;
}