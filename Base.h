#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>

class Base {
public:
    Base();
    Base(const Base& other);
    virtual ~Base();

    virtual void print() const = 0;
    virtual void edit() = 0;
    virtual void saveToFile(std::ofstream& out) const = 0;
    virtual void loadFromFile(std::ifstream& in) = 0;
    virtual Base* clone() const = 0;
};

#endif // BASE_H