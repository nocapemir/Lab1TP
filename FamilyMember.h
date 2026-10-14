#ifndef FAMILYMEMBER_H
#define FAMILYMEMBER_H

#include "Base.h"
#include "Exception.h"
#include <string>

class FamilyMember : public Base {
private:
    std::string fullName_;
    std::string motherName_;
    std::string fatherName_;
    std::string spouseName_;
    std::string* children_;
    int childrenCount_;
    std::string birthDate_;
    std::string deathDate_;
    int age_;

public:
    FamilyMember();
    FamilyMember(const std::string& fullName, const std::string& motherName,
                 const std::string& fatherName, const std::string& spouseName,
                 const std::string& birthDate, const std::string& deathDate, int age);
    FamilyMember(const FamilyMember& other);
    ~FamilyMember() override;

    // Методы set и get
    void setFullName(const std::string& fullName);
    std::string getFullName() const;

    void setMotherName(const std::string& motherName);
    std::string getMotherName() const;

    void setFatherName(const std::string& fatherName);
    std::string getFatherName() const;

    void setSpouseName(const std::string& spouseName);
    std::string getSpouseName() const;

    void setBirthDate(const std::string& birthDate);
    std::string getBirthDate() const;

    void setDeathDate(const std::string& deathDate);
    std::string getDeathDate() const;

    void setAge(int age);
    int getAge() const;

    int getChildrenCount() const;
    std::string getChild(int index) const;
    void addChild(const std::string& childName);
    void removeChild(int index);
    void clearChildren();

    // Переопределение виртуальных методов Base
    void print() const override;
    void edit() override;
    void saveToFile(std::ofstream& out) const override;
    void loadFromFile(std::ifstream& in) override;
    Base* clone() const override;

    // Перегрузка операторов
    FamilyMember& operator=(const FamilyMember& other);
    bool operator==(const FamilyMember& other) const;
    friend std::ostream& operator<<(std::ostream& os, const FamilyMember& member);
};

#endif // FAMILYMEMBER_H
