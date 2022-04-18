#include "lib.h"

#include <iostream>

int main(int , char**)
{
    std::cout << "Version: " << helper::GetAppVersion() << std::endl;
    std::cout << "Hello, World!" << std::endl;
    
    return 0;
}