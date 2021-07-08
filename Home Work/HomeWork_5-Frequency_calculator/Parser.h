#ifndef HW5_PARSER_H
#define HW5_PARSER_H

#include <vector>
#include "Counter.h"

class Parser {
public:
    Parser(); // c'tor
    ~Parser(); // d'tor
    void menu(); // Run all the program
    bool intNameExist(string name); //Check if  name Exist in the inList
    bool stringNameExist(string name);//Check if  name Exist in the stringList


    ///Exception Class///
    class ExceptionAlreadyExist { };
    class ExceptionNoCounterByName {
    public:
        string name;
        explicit ExceptionNoCounterByName(const string& name) : name(name){}

    };
    class ExceptionUnknowCMD {
        public:
        string name;
        explicit ExceptionUnknowCMD(const string& name) : name(name){}

    };
    class ExceptionNoFile {};
    class ExceptionMissingFileName {};
    class ExceptionMissingCountName {};




private:
    vector<Counter<int> > intList;
    vector<Counter<string> > stringList;

    Counter<int> &getFromIntListByName(string name); // get the Counter<int>
    Counter<string> &getFromStringListByName(string name); // Get the Counter<string>
};

#endif //HW5_PARSER_H
