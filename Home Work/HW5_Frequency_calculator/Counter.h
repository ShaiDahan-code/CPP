#ifndef HW5_COUNTER_H
#define HW5_COUNTER_H
#include <map>
#include <list>
#include <iostream>
#include <sstream>
#include <typeinfo>

using namespace std;

template <class T>
class Counter {
private:
    map<T,int> myMap;
    string name;

public:
    explicit Counter(string name); // c'tro
    Counter(T value,string name);
    Counter(const Counter& c); // copy c'tor
    Counter& operator=(Counter& other);

    ~Counter();

    void add(T value); // add a T to the Map
    T most_common(); //
    void clear();
    int operator [](T value);
    void add_from_stream(istream &input); // Add from istream to the myMap
    void print_to_stream(ostream & output); // print to ostream with myMap
    void print_most_common(ostream & output); // print the most command with ostream
    const string &getName() const; // Get the Name

    ///Exception Class///
    class ExceptionEmptyCount {};
    class ExceptionErrorWhileInput {};

};
template<class T>
Counter<T>::Counter(string name) {
    this->name=name;
}
template<class T>
Counter<T>::Counter(T value,string name) {
    myMap.insert(pair<T, int>(value, 1));
    this->name=name;
}

template<class T>
Counter<T>::Counter(const Counter &c) {
    this->name = c.name;
    this->myMap = c.myMap;
}

template<class T>
Counter<T>& Counter<T>::operator=(Counter<T> &other) {
    if(this == &other){
        return *this;
    }
    this->name = other.name;
    this->myMap = other.myMap;
    return *this;
}



template<class T>
void Counter<T>::clear() {
    myMap.clear();
}

template<class T>
void Counter<T>::add(T value) {
    myMap[value]++;
}

template<class T>
int Counter<T>::operator[](T value) {
    return myMap[value];
}

template<class T>
Counter<T>::~Counter() {

}

template<class T>
void Counter<T>::add_from_stream(std::istream &input) {

    T t;
    while (input >> t){
        if(input.fail()){
            throw ExceptionErrorWhileInput();
        }
        else {
            add(t);
        }
    }
    if(!input.eof()){
        throw ExceptionErrorWhileInput();
    }
}

template<class T>
void Counter<T>::print_to_stream(ostream &output) {
    typename map<T,int>::iterator it;
    output << "counter " << name <<" = { ";
    for (it =myMap.begin(); it!=myMap.end(); ++it)
        output << it->first << ":" << it->second << " ";
    output << "}"<<endl;
}

template<class T>
void Counter<T>::print_most_common(ostream &output) {
    if (myMap.empty()) {
        throw ExceptionEmptyCount();
    }

    typename map<T,int>::iterator it;
    T t = myMap.begin()->first;
    for (it =myMap.begin(); it!=myMap.end(); ++it)
        if(myMap[t] < it->second) {
            t = it->first;
        }
    output <<"most common element for counter " << name << " is "<< t <<":"<<myMap[t] <<endl;
}

template<class T>
T Counter<T>::most_common() {
    if (myMap.empty()) {
        throw ExceptionEmptyCount();
    }

    T t = myMap.begin()->first;
    typename map<T,int>::iterator it;
    for (it =myMap.begin(); it!=myMap.end(); ++it)
        if(myMap[t] < it->second) {
            t = it->first;
        }
    for (it =myMap.begin(); it!=myMap.end(); ++it)
        if(myMap[t] == it->second) {
            if(t > it->first)
                t = it->first;
        }
    return t;
}

template<class T>
const string &Counter<T>::getName() const {
    return name;
}




#endif //HW5_COUNTER_H
