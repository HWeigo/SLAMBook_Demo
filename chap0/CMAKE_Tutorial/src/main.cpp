#include <iostream>

int main(int argc, char **argv)
{
    std::cout << "Hi, this repotory is used to test CMAKE." << std::endl;

#ifdef ENABLE_DEBUG
    std::cout << "Use ADD_DEFINITIONS in CMAKE to set define." << std::endl;
#endif    

    std::cout<< "Input number: " << argc-1 << std::endl;
    std::cout<< argv[1] << std::endl;

    return 0;
}