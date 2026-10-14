#include "Exception.h"
#include <iostream>

Exception::Exception() : message_("Неизвестная ошибка") {
    std::cout << "[Exception] Вызван конструктор по умолчанию\n";
}

Exception::Exception(const std::string& message) : message_(message) {
    std::cout << "[Exception] Вызван конструктор с параметрами\n";
}

Exception::Exception(const Exception& other) : message_(other.message_) {
    std::cout << "[Exception] Вызван конструктор копирования\n";
}

Exception::~Exception() {
    std::cout << "[Exception] Вызван деструктор\n";
}

std::string Exception::getMessage() const {
    return message_;
}

void Exception::setMessage(const std::string& message) {
    message_ = message;
}