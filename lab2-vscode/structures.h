#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>


#include <string>

struct Pipeline
{
    int id;
    std::string name;
    double length;
    double diameter;
    bool inRepair;

    // Чтение данных с консоли и создаение объекта
    void getInfo() {
        std::cout << "Enter pipe name: ";
        std::cin >> name;
        std::cout << "Enter pipe length: ";
        while (!(std::cin >> length) || length <= 0) {
            std::cout << "Invalid input. Please enter a positive number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Enter pipe diameter: ";
        while (!(std::cin >> diameter) || diameter <= 0) {
            std::cout << "Invalid input. Please enter a positive number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Is pipe in repair? (Enter 1 if yes, 0 if no): ";
        while (!(std::cin >> inRepair) || inRepair < 0 || inRepair > 1 ) {
            std::cout << "Invalid input. Please enter 1 or 0: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Вывод данных трубы
    void showInfo() const {
        std::cout << "Pipe: " << name << ", Id: " << id << ", Length: " << length 
                  << ", Diameter: " << diameter 
                  << ", In repair: " << (inRepair ? "Yes" : "No") << "\n";
    }

    // Редактирование состояния ремонта трубы
    void toggleRepairStatus() {
        inRepair = !inRepair;
    }
};

struct CS {
    int id;
    std::string name;
    int workshops;
    int workingWorkshops;
    double efficiency;

    // Чтение данных КС с консоли
    void getInfo() {
        std::cout << "Enter CS name: ";
        std::cin >> name;
        std::cout << "Enter number of workshops: ";
        while (!(std::cin >> workshops) || workshops <= 0) {
            std::cout << "Invalid input. Please enter a positive integer: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Enter number of working workshops: ";
        while (!(std::cin >> workingWorkshops) || workingWorkshops < 0 || workingWorkshops > workshops) {
            std::cout << "Invalid input. Please enter a valid integer between 0 and " << workshops << ": ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Enter efficiency: ";
        while (!(std::cin >> efficiency) || efficiency < 0) {
            std::cout << "Invalid input. Please enter a non-negative number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Вывод данных КС
    void showInfo() const {
        std::cout << "CS: " << name << ", Id: " << id << ", Workshops: " << workshops 
                  << ", Working: " << workingWorkshops 
                  << ", Efficiency: " << efficiency << "\n";
    }

    // Запуск цеха
    void startWorkshop() {
        if (workingWorkshops < workshops) {
            workingWorkshops++;
            std::cout << "One workshop started.\n";
        } else {
            std::cout << "All workshops are already working.\n";
        }
    }

    // Остановка цеха
    void stopWorkshop() {
        if (workingWorkshops > 0) {
            workingWorkshops--;
            std::cout << "One workshop stopped.\n";
        } else {
            std::cout << "No workshops are currently working.\n";
        }
    }
};

#endif /* STRUCTURES_H_ */