#include <iostream>
#include "StringParser.h"



int main()
{
    std::string stringToParse{};
    std::cout << "Introduce a string with written numbers: " << "\n";
    std::getline(std::cin, stringToParse);
    StringParser stringParsed(stringToParse);
    std::cout << stringToParse << " : " << stringParsed.getStringWithNumbers() << "\n";
    return 0;
}
