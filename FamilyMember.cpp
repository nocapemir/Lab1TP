#include "FamilyMember.h"
#include <iostream>

FamilyMember::FamilyMember()
    : Base(),
      fullName_("Неизвестно"),
      motherName_("Нет данных"),
      fatherName_("Нет данных"),
      spouseName_("Нет"),
      children_(nullptr),
      childrenCount_(0),
      birthDate_("01.01.1970"),
      deathDate_("Нет (жив/жива)"),
      age_(0) {
    std::cout << "[FamilyMember] Вызван конструктор по умолчанию для: " << fullName_ << "\n";
}

FamilyMember::FamilyMember(const std::string& fullName, const std::string& motherName,
                           const std::string& fatherName, const std::string& spouseName,
                           const std::string& birthDate, const std::string& deathDate, int age)
    : Base(),
      fullName_(fullName),
      motherName_(motherName),
      fatherName_(fatherName),
      spouseName_(spouseName),
      children_(nullptr),
      childrenCount_(0),
      birthDate_(birthDate),
      deathDate_(deathDate),
      age_(0) {
    std::cout << "[FamilyMember] Вызван конструктор с параметрами для: " << fullName_ << "\n";
    setAge(age);
}

FamilyMember::FamilyMember(const FamilyMember& other)
    : Base(other),
      fullName_(other.fullName_),
      motherName_(other.motherName_),
      fatherName_(other.fatherName_),
      spouseName_(other.spouseName_),
      children_(nullptr),
      childrenCount_(other.childrenCount_),
      birthDate_(other.birthDate_),
      deathDate_(other.deathDate_),
      age_(other.age_) {
    std::cout << "[FamilyMember] Вызван конструктор копирования для: " << fullName_ << "\n";
    if (childrenCount_ > 0) {
        children_ = new std::string[childrenCount_];
        for (int i = 0; i < childrenCount_; ++i) {
            children_[i] = other.children_[i];
        }
    }
}

FamilyMember::~FamilyMember() {
    std::cout << "[FamilyMember] Вызван деструктор для: " << fullName_ << "\n";
    delete[] children_;
    children_ = nullptr;
}

void FamilyMember::setFullName(const std::string& fullName) {
    if (fullName.empty()) {
        throw Exception("ФИО не может быть пустым");
    }
    fullName_ = fullName;
}

std::string FamilyMember::getFullName() const {
    return fullName_;
}

void FamilyMember::setMotherName(const std::string& motherName) {
    motherName_ = motherName.empty() ? "Нет данных" : motherName;
}

std::string FamilyMember::getMotherName() const {
    return motherName_;
}

void FamilyMember::setFatherName(const std::string& fatherName) {
    fatherName_ = fatherName.empty() ? "Нет данных" : fatherName;
}

std::string FamilyMember::getFatherName() const {
    return fatherName_;
}

void FamilyMember::setSpouseName(const std::string& spouseName) {
    spouseName_ = spouseName.empty() ? "Нет" : spouseName;
}

std::string FamilyMember::getSpouseName() const {
    return spouseName_;
}

void FamilyMember::setBirthDate(const std::string& birthDate) {
    if (birthDate.empty()) {
        throw Exception("Дата рождения не может быть пустой");
    }
    birthDate_ = birthDate;
}

std::string FamilyMember::getBirthDate() const {
    return birthDate_;
}

void FamilyMember::setDeathDate(const std::string& deathDate) {
    deathDate_ = deathDate.empty() ? "Нет" : deathDate;
}

std::string FamilyMember::getDeathDate() const {
    return deathDate_;
}

void FamilyMember::setAge(int age) {
    if (age < 0 || age > 150) {
        throw Exception("Некорректный возраст (можно ввести от 0 до 150 лет)");
    }
    age_ = age;
}

int FamilyMember::getAge() const {
    return age_;
}

int FamilyMember::getChildrenCount() const {
    return childrenCount_;
}

std::string FamilyMember::getChild(int index) const {
    if (index < 0 || index >= childrenCount_) {
        throw Exception("Индекс ребенка выходит за границы списка");
    }
    return children_[index];
}

void FamilyMember::addChild(const std::string& childName) {
    if (childName.empty()) {
        throw Exception("Имя ребенка не может быть пустым");
    }
    std::string* newChildren = new std::string[childrenCount_ + 1];
    for (int i = 0; i < childrenCount_; ++i) {
        newChildren[i] = children_[i];
    }
    newChildren[childrenCount_] = childName;
    delete[] children_;
    children_ = newChildren;
    ++childrenCount_;
}

void FamilyMember::removeChild(int index) {
    if (index < 0 || index >= childrenCount_) {
        throw Exception("Неверный индекс для удаления ребенка");
    }
    if (childrenCount_ == 1) {
        delete[] children_;
        children_ = nullptr;
        childrenCount_ = 0;
        return;
    }
    std::string* newChildren = new std::string[childrenCount_ - 1];
    for (int i = 0, j = 0; i < childrenCount_; ++i) {
        if (i != index) {
            newChildren[j++] = children_[i];
        }
    }
    delete[] children_;
    children_ = newChildren;
    --childrenCount_;
}

void FamilyMember::clearChildren() {
    delete[] children_;
    children_ = nullptr;
    childrenCount_ = 0;
}

void FamilyMember::print() const {
    std::cout << *this;
}

void FamilyMember::edit() {
    std::cout << "\n.       Редактирование данных члена семьи: " << fullName_ << "\n";
    std::cout << "1. Изменить ФИО\n";
    std::cout << "2. Изменить ФИО матери\n";
    std::cout << "3. Изменить ФИО отца\n";
    std::cout << "4. Изменить ФИО супруга(и)\n";
    std::cout << "5. Изменить дату рождения\n";
    std::cout << "6. Изменить дату смерти\n";
    std::cout << "7. Изменить возраст\n";
    std::cout << "8. Добавить ребенка\n";
    std::cout << "9. Удалить ребенка\n";
    std::cout << "0. Отмена\n";
    std::cout << "Ваш выбор: ";

    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw Exception("Введено не число");
    }
    std::cin.ignore(10000, '\n');

    std::string inputStr;
    int inputInt;

    switch (choice) {
        case 1:
            std::cout << "Введите новое ФИО: ";
            std::getline(std::cin, inputStr);
            setFullName(inputStr);
            break;
        case 2:
            std::cout << "Введите ФИО матери: ";
            std::getline(std::cin, inputStr);
            setMotherName(inputStr);
            break;
        case 3:
            std::cout << "Введите ФИО отца: ";
            std::getline(std::cin, inputStr);
            setFatherName(inputStr);
            break;
        case 4:
            std::cout << "Введите ФИО супруга(и): ";
            std::getline(std::cin, inputStr);
            setSpouseName(inputStr);
            break;
        case 5:
            std::cout << "Введите дату рождения: ";
            std::getline(std::cin, inputStr);
            setBirthDate(inputStr);
            break;
        case 6:
            std::cout << "Введите дату смерти (или 'Нет'): ";
            std::getline(std::cin, inputStr);
            setDeathDate(inputStr);
            break;
        case 7:
            std::cout << "Введите возраст: ";
            if (!(std::cin >> inputInt)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                throw Exception("Возраст должен быть целым числом");
            }
            std::cin.ignore(10000, '\n');
            setAge(inputInt);
            break;
        case 8:
            std::cout << "Введите ФИО ребенка: ";
            std::getline(std::cin, inputStr);
            addChild(inputStr);
            break;
        case 9:
            if (childrenCount_ == 0) {
                throw Exception("У данного члена семьи нет записанных детей");
            }
            for (int i = 0; i < childrenCount_; ++i) {
                std::cout << i + 1 << ". " << children_[i] << "\n";
            }
            std::cout << "Введите номер ребенка для удаления: ";
            if (!(std::cin >> inputInt)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                throw Exception("Введено не число");
            }
            std::cin.ignore(10000, '\n');
            removeChild(inputInt - 1);
            break;
        case 0:
            break;
        default:
            throw Exception("Неверный пункт меню редактирования");
    }
}

void FamilyMember::saveToFile(std::ofstream& out) const {
    out << fullName_ << "\n"
        << motherName_ << "\n"
        << fatherName_ << "\n"
        << spouseName_ << "\n"
        << birthDate_ << "\n"
        << deathDate_ << "\n"
        << age_ << "\n"
        << childrenCount_ << "\n";
    for (int i = 0; i < childrenCount_; ++i) {
        out << children_[i] << "\n";
    }
}

void FamilyMember::loadFromFile(std::ifstream& in) {
    std::getline(in, fullName_);
    std::getline(in, motherName_);
    std::getline(in, fatherName_);
    std::getline(in, spouseName_);
    std::getline(in, birthDate_);
    std::getline(in, deathDate_);
    in >> age_;
    int count = 0;
    in >> count;
    in.ignore(10000, '\n');

    clearChildren();
    for (int i = 0; i < count; ++i) {
        std::string child;
        std::getline(in, child);
        addChild(child);
    }
}

Base* FamilyMember::clone() const {
    return new FamilyMember(*this);
}

FamilyMember& FamilyMember::operator=(const FamilyMember& other) {
    std::cout << "[FamilyMember] Вызван оператор присваивания\n";
    if (this == &other) {
        return *this;
    }
    fullName_ = other.fullName_;
    motherName_ = other.motherName_;
    fatherName_ = other.fatherName_;
    spouseName_ = other.spouseName_;
    birthDate_ = other.birthDate_;
    deathDate_ = other.deathDate_;
    age_ = other.age_;

    delete[] children_;
    childrenCount_ = other.childrenCount_;
    if (childrenCount_ > 0) {
        children_ = new std::string[childrenCount_];
        for (int i = 0; i < childrenCount_; ++i) {
            children_[i] = other.children_[i];
        }
    } else {
        children_ = nullptr;
    }
    return *this;
}

bool FamilyMember::operator==(const FamilyMember& other) const {
    return (fullName_ == other.fullName_ && birthDate_ == other.birthDate_);
}

std::ostream& operator<<(std::ostream& os, const FamilyMember& member) {
    os << "ФИО:           " << member.fullName_ << "\n"
       << "Мать:          " << member.motherName_ << "\n"
       << "Отец:          " << member.fatherName_ << "\n"
       << "Супруг(а):     " << member.spouseName_ << "\n"
       << "Дата рождения: " << member.birthDate_ << "\n"
       << "Дата смерти:   " << member.deathDate_ << "\n"
       << "Возраст:       " << member.age_ << " лет\n"
       << "Дети (" << member.childrenCount_ << "):      ";
    if (member.childrenCount_ == 0) {
        os << "Нет\n";
    } else {
        os << "\n";
        for (int i = 0; i < member.childrenCount_; ++i) {
            os << "  - " << member.children_[i] << "\n";
        }
    }
    return os;
}