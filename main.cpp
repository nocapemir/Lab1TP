#include <iostream>
#include <string>
#include <clocale>

#include "Keeper.h"
#include "FamilyMember.h"
#include "Exception.h"

int readInt(const std::string& prompt) {
    std::cout << prompt;
    int value;
    if (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw Exception("Ошибка ввода: ожидалось целое число!");
    }
    std::cin.ignore(10000, '\n');
    return value;
}

void createMemberInteractive(Keeper& keeper) {
    std::cout << "\n.  Добавление нового члена семьи\n";
    std::cout << "1. Создать с вводом всех параметров\n";
    std::cout << "2. Создать пустую запись\n";
    int mode = readInt("Выберите способ создания: ");

    if (mode == 2) {
        Base* member = new FamilyMember();
        keeper.add(member);
        std::cout << "Член семьи по умолчанию добавлен. Вы можете отредактировать его из меню.\n";
        return;
    } else if (mode != 1) {
        throw Exception("Ошибка: Выбран неверный способ создания!");
    }

    std::string fullName, motherName, fatherName, spouseName, birthDate, deathDate;

    std::cout << "Введите ФИО члена семьи: ";
    std::getline(std::cin, fullName);
    if (fullName.empty()) {
        throw Exception("Ошибка: ФИО не может быть пустым!");
    }

    std::cout << "Введите ФИО матери (Enter, если неизвестно): ";
    std::getline(std::cin, motherName);
    if (motherName.empty()) motherName = "Нет данных";

    std::cout << "Введите ФИО отца (Enter, если неизвестно): ";
    std::getline(std::cin, fatherName);
    if (fatherName.empty()) fatherName = "Нет данных";

    std::cout << "Введите ФИО супруга/супруги (Enter, если нет): ";
    std::getline(std::cin, spouseName);
    if (spouseName.empty()) spouseName = "Нет";

    std::cout << "Введите дату рождения (Пример: 15.05.1965): ";
    std::getline(std::cin, birthDate);
    if (birthDate.empty()) {
        throw Exception("Ошибка: Дата рождения обязательна для ввода!");
    }

    std::cout << "Введите дату смерти (Enter, если человек жив): ";
    std::getline(std::cin, deathDate);
    if (deathDate.empty()) deathDate = "Нет (жив/жива)";

    int age = readInt("Введите возраст (полных лет): ");

    FamilyMember* member = new FamilyMember(
        fullName, motherName, fatherName, spouseName, birthDate, deathDate, age
    );

    try {
        int childrenCount = readInt("Введите количество детей: ");
        if (childrenCount < 0) {
            throw Exception("Ошибка: Количество детей не может быть отрицательным!");
        }
        for (int i = 0; i < childrenCount; ++i) {
            std::string childName;
            std::cout << "Введите ФИО ребенка #" << i + 1 << ": ";
            std::getline(std::cin, childName);
            member->addChild(childName);
        }
        keeper.add(member);
        std::cout << "Член семьи успешно добавлен в фамильное дерево!\n";
    } catch (...) {
        delete member;
        throw;
    }
}

void findMemberByName(const Keeper& keeper) {
    if (keeper.getSize() == 0) {
        throw Exception("Фамильное дерево пусто, поиск невозможен!");
    }
    std::string query;
    std::cout << "Введите ФИО (или часть ФИО) для поиска: ";
    std::getline(std::cin, query);
    if (query.empty()) {
        throw Exception("Ошибка: Поисковый запрос не может быть пустым!");
    }

    bool found = false;
    for (int i = 0; i < keeper.getSize(); ++i) {
        FamilyMember* member = dynamic_cast<FamilyMember*>(keeper[i]);
        if (member != nullptr && member->getFullName().find(query) != std::string::npos) {
            std::cout << "\nНайдена запись #" << i + 1 << ":\n";
            member->print();
            found = true;
        }
    }
    if (!found) {
        std::cout << "Члены семьи с именем '" << query << "' не найдены.\n";
    }
}

void demonstrateCopyConstructor(const Keeper& keeper) {
    if (keeper.getSize() == 0) {
        throw Exception("Добавьте хотя бы один объект перед проверкой копирования!");
    }
    std::cout << "\nДемонстрация конструктора копирования Keeper\n";
    Keeper copyKeeper(keeper);
    std::cout << "Копия контейнера успешно создана. Содержимое копии:\n";
    copyKeeper.printAll();
    std::cout << "Выход из блока демонстрации\n";
}

void printMenu() {
    std::cout << "1. Добавить члена семьи\n";
    std::cout << "2. Удалить члена семьи по номеру\n";
    std::cout << "3. Редактировать данные члена семьи\n";
    std::cout << "4. Вывести все фамильное дерево на экран\n";
    std::cout << "5. Найти члена семьи по ФИО\n";
    std::cout << "6. Сохранить фамильное дерево в файл\n";
    std::cout << "7. Загрузить фамильное дерево из файла\n";
    std::cout << "8. Продемонстрировать работу конструктора копирования\n";
    std::cout << "9. Очистить все дерево\n";
    std::cout << "0. Выход из программы\n";
}

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    Keeper familyTree;
    bool running = true;

    while (running) {
        printMenu();
        try {
            int choice = readInt("Выберите действие: ");
            switch (choice) {
                case 1:
                    createMemberInteractive(familyTree);
                    break;
                case 2: {
                    familyTree.printAll();
                    int index = readInt("Введите номер записи для удаления: ");
                    familyTree.remove(index - 1);
                    std::cout << "Запись успешно удалена.\n";
                    break;
                }
                case 3: {
                    familyTree.printAll();
                    int index = readInt("Введите номер записи для редактирования: ");
                    familyTree.editElement(index - 1);
                    std::cout << "Запись успешно обновлена.\n";
                    break;
                }
                case 4:
                    familyTree.printAll();
                    break;
                case 5:
                    findMemberByName(familyTree);
                    break;
                case 6: {
                    std::string filename;
                    std::cout << "Введите имя файла для сохранения (например, tree.txt): ";
                    std::getline(std::cin, filename);
                    familyTree.saveToFile(filename);
                    break;
                }
                case 7: {
                    std::string filename;
                    std::cout << "Введите имя файла для загрузки (например, tree.txt): ";
                    std::getline(std::cin, filename);
                    familyTree.loadFromFile(filename);
                    break;
                }
                case 8:
                    demonstrateCopyConstructor(familyTree);
                    break;
                case 9:
                    familyTree.clear();
                    std::cout << "Фамильное дерево полностью очищено.\n";
                    break;
                case 0:
                    running = false;
                    std::cout << "Завершение работы программы...\n";
                    break;
                default:
                    throw Exception("Ошибка: Неизвестный пункт меню!");
            }
        } catch (const Exception& ex) {
            std::cout << "\n[ИСКЛЮЧЕНИЕ] " << ex.getMessage() << "\n";
        }
    }

    return 0;
}