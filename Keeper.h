#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"
#include "Exception.h"
#include <string>

class Keeper {
private:
    Base** data_;
    int size_;

public:
    Keeper();
    Keeper(int initialSize);
    Keeper(const Keeper& other);
    ~Keeper();

    int getSize() const;

    void add(Base* element);
    void remove(int index);
    void clear();

    void printAll() const;
    void editElement(int index);

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    // Перегрузка операторов
    Keeper& operator=(const Keeper& other);
    Base* operator[](int index) const;
};

#endif // KEEPER_H