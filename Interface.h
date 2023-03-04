#ifndef DA_PROJECT1_INTERFACE_H
#define DA_PROJECT1_INTERFACE_H


using namespace std;
class Interface {

public:
    //Data d_;

    //void setData(Data d){d_ = d;}

    Interface();
    void welcomePage();
    void mainMenu();
    void readFiles();


    void full();
    void costs();
    void subgraph();

    void exitProgram() const;
    void lastPage() const;
    void credits() const;

};



#endif //DA_PROJECT1_INTERFACE_H
