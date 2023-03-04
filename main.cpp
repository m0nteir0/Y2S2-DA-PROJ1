#include <iostream>
#include "Interface.h"

int main() {
    std::cout << "Hello, World!" << std::endl;


    Interface iFace = Interface();
    try {
        iFace.welcomePage();
    }
    catch (int exit) {
        return 0;
    }

    return 0;
}
