#include "Matrix.hpp"

//testing GetRows() and GetColumns()

int main()
{
    Matrix a(5, 4);
    if((a.GetRows() == 5) && (a.GetColumns() == 4))
        std::cout << "Getting amount of rows and columns works OK" << std::endl;
    else
        std::cout << "There is an error in getting rows and columns" << std::endl;
    return 0;
}