#include "Keeper.h"
#include "FamilyMember.h"
#include <iostream>
#include <fstream>

Keeper::Keeper() : data_(nullptr), size_(0) {
    std::cout << "[Keeper] Вызван конструктор по умолчанию\n";
}

Keeper::Keeper(int initialSize) : data_(nullptr), size_(0) {
    std::cout << "[Keeper] Вызван конструктор с параметрами\n";
    if (initialSize < 0) {
        throw Exception("Размер контейнера не может быть отрицательным");
    }
    if (initialSize > 0) {
        data_ = new Base*[initialSize];
        size_ = initialSize;
        for (int i = 0; i < size_; ++i) {
            data_[i] = new FamilyMember();
        }
    }
}

Keeper::Keeper(const Keeper& other) : data_(nullptr), size_(other.size_) {
    std::cout << "[Keeper] Вызван конструктор копирования\n";
    if (size_ > 0) {
        data_ = new Base*[size_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i]->clone();
        }
    }
}

Keeper::~Keeper() {
    std::cout << "[Keeper] Вызван деструктор\n";
    clear();
}

int Keeper::getSize() const {
    return size_;
}

void Keeper::add(Base* element) {
    if (element == nullptr) {
        throw Exception("Попытка добавить пустой указатель в Keeper");
    }
    Base** newData = new Base*[size_ + 1];
    for (int i = 0; i < size_; ++i) {
        newData[i] = data_[i];
    }
    newData[size_] = element;
    delete[] data_;
    data_ = newData;
    ++size_;
}

void Keeper::remove(int index) {
    if (size_ == 0) {
        throw Exception("Фамильное дерево пусто, удаление невозможно");
    }
    if (index < 0 || index >= size_) {
        throw Exception("Некорректный индекс для удаления");
    }

    delete data_[index];

    if (size_ == 1) {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        return;
    }

    Base** newData = new Base*[size_ - 1];
    for (int i = 0, j = 0; i < size_; ++i) {
        if (i != index) {
            newData[j++] = data_[i];
        }
    }
    delete[] data_;
    data_ = newData;
    --size_;
}

void Keeper::clear() {
    for (int i = 0; i < size_; ++i) {
        delete data_[i];
    }
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
}

void Keeper::printAll() const {
    if (size_ == 0) {
        throw Exception("Фамильное дерево пусто");
    }
    std::cout << "\n.            ФАМИЛЬНОЕ ДЕРЕВО\n";
    for (int i = 0; i < size_; ++i) {
        std::cout << "Запись #" << i + 1 << ":\n";
        data_[i]->print();
    }
}

void Keeper::editElement(int index) {
    if (size_ == 0) {
        throw Exception("Фамильное дерево пусто");
    }
    if (index < 0 || index >= size_) {
        throw Exception("Некорректный индекс для редактирования");
    }
    data_[index]->edit();
}

void Keeper::saveToFile(const std::string& filename) const {
    if (filename.empty()) {
        throw Exception("Имя файла не может быть пустым");
    }
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw Exception("Не удалось открыть файл для записи: " + filename);
    }

    out << size_ << "\n";
    for (int i = 0; i < size_; ++i) {
        data_[i]->saveToFile(out);
    }
    out.close();
    std::cout << "Данные успешно сохранены в файл '" << filename << "' (записей: " << size_ << ").\n";
}

void Keeper::loadFromFile(const std::string& filename) {
    if (filename.empty()) {
        throw Exception("Имя файла не может быть пустым");
    }
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw Exception("Не удалось открыть файл для чтения: " + filename);
    }

    int count = 0;
    if (!(in >> count) || count < 0) {
        in.close();
        throw Exception("Некорректный формат файла или файл поврежден");
    }
    in.ignore(10000, '\n');

    clear();
    for (int i = 0; i < count; ++i) {
        Base* member = new FamilyMember();
        member->loadFromFile(in);
        add(member);
    }
    in.close();
    std::cout << "Данные успешно загружены из файла '" << filename << "' (записей: " << size_ << ").\n";
}

Keeper& Keeper::operator=(const Keeper& other) {
    std::cout << "[Keeper] Вызван оператор присваивания\n";
    if (this == &other) {
        return *this;
    }
    clear();
    size_ = other.size_;
    if (size_ > 0) {
        data_ = new Base*[size_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i]->clone();
        }
    }
    return *this;
}

Base* Keeper::operator[](int index) const {
    if (index < 0 || index >= size_) {
        throw Exception("Выход за границы массива в операторе []!");
    }
    return data_[index];
}