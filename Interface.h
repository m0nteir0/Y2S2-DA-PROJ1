#ifndef DA_PROJECT1_INTERFACE_H
#define DA_PROJECT1_INTERFACE_H

#include "Data.h"

using namespace std;

class Interface {

private:
    Data d_;

public:

    Interface();
    void welcomePage();
    void mainMenu();
    bool readFiles();


    bool full();
    bool costs();
    bool subgraph();

    bool disableSegments();
    bool subgraphAnalyze();

    bool credits() const;

};



#endif //DA_PROJECT1_INTERFACE_H
