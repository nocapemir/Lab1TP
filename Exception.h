#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

class Exception {
private:
    std::string message_;

public:
    Exception();
    Exception(const std::string& message);
    Exception(const Exception& other);
    ~Exception();

    std::string getMessage() const;
    void setMessage(const std::string& message);
};

#endif // EXCEPTION_H