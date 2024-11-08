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
    double length = 0;
    double diameter = 0;
    bool inRepair = 0;

    // Чтение данных с консоли и создаение объекта
    void getInfo() {
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
        if (length == 0) {
            std::cout << "There is no pipe" << std::endl;
        } else {
            std::cout 
                << "Pipe: " << ", Length: " << length 
                << ", Diameter: " << diameter 
                << ", In repair: " << (inRepair ? "Yes" : "No") << "\n";
        }
    }

    // Редактирование состояния ремонта трубы
    void toggleRepairStatus() {
        if (length == 0) {
            std::cout << "There is no pipe" << std::endl;
        } else {
            inRepair = !inRepair;
        }
    }
};

struct CS {
    int workshops = 0;
    int workingWorkshops = 0;
    double efficiency = 0.00;

    // Чтение данных КС с консоли
    void getInfo() {
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
        while (!(std::cin >> efficiency) || efficiency <= 0 || efficiency > 100) {
            std::cout << "Invalid input. Please enter number between 1 and 100: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Вывод данных КС
    void showInfo() const {
        if (workshops == 0) {
            std::cout << "There is no CS" << std::endl;
        } else {
            std::cout << "CS: " << ", Workshops: " << workshops 
                  << ", Working: " << workingWorkshops 
                  << ", Efficiency: " << efficiency << "\n";
        }
    }

    void editWorkingWorkshops() {
        if (workshops == 0) {
            std::cout << "There is no CS" << std::endl;
        } else {
            std::cout << "Enter new number of working workshops: ";
            while (!(std::cin >> workingWorkshops) || workingWorkshops < 0 || workingWorkshops > workshops) {
                std::cout << "Invalid input. Please enter a valid integer between 0 and " << workshops << ": ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

    }
};

#endif /* STRUCTURES_H_ */