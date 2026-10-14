#include "Base.h"

Base::Base() {
    std::cout << "[Base] Вызван конструктор по умолчанию\n";
}

Base::Base(const Base& other) {
    std::cout << "[Base] Вызван конструктор копирования\n";
}

Base::~Base() {
    std::cout << "[Base] Вызван виртуальный деструктор\n";
}