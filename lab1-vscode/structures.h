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
    std::string name = "";
    double length = 0;
    double diameter = 0;
    bool inRepair = 0;

    // Чтение данных с консоли и создаение объекта
    void getInfo() {
        std::cout << "Enter pipe name: ";
        while (!(std::cin >> name) || name.empty() || (std::cin.peek() != '\n')) {
            std::cout << "Invalid input. Please enter a non-empty string: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Enter pipe length: ";
        while (!(std::cin >> length) || length <= 0 || (std::cin.peek() != '\n')) {
            std::cout << "Invalid input. Please enter a positive number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Enter pipe diameter: ";
        while (!(std::cin >> diameter) || diameter <= 0 || (std::cin.peek() != '\n')) {
            std::cout << "Invalid input. Please enter a positive number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Is pipe in repair? (Enter 1 if yes, 0 if no): ";
        while (!(std::cin >> inRepair) || inRepair < 0 || inRepair > 1 || (std::cin.peek() != '\n')) {
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
                << "Pipe: " << name << ", Length: " << length 
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
            std::cout << "Pipeline changed successfully.\n";
        }
    }
};

struct CS {
    std::string name = "";
    int workshops = 0;
    int workingWorkshops = 0;
    double efficiency = 0.00;

    // Чтение данных КС с консоли
    void getInfo() {
        std::cout << "Enter a cs name: ";
        while (!(std::cin >> name) || name.empty() || (std::cin.peek() != '\n')) {
            std::cout << "Invalid input. Please enter a non-empty string: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Enter number of workshops: ";
        while (!(std::cin >> workshops) || workshops <= 0 || (std::cin.peek() != '\n')) {
            std::cout << "Invalid input. Please enter a positive integer: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Enter number of working workshops: ";
        while (!(std::cin >> workingWorkshops) || workingWorkshops < 0 || workingWorkshops > workshops || (std::cin.peek() != '\n')) {
            std::cout << "Invalid input. Please enter a valid integer between 0 and " << workshops << ": ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Enter efficiency: ";
        while (!(std::cin >> efficiency) || efficiency <= 0 || efficiency > 100 || (std::cin.peek() != '\n')) {
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
            std::cout << "CS: " << name << ", Workshops: " << workshops 
                  << ", Working: " << workingWorkshops 
                  << ", Efficiency: " << efficiency << "\n";
        }
    }

    void editWorkingWorkshops() {
        if (workshops == 0) {
            std::cout << "There is no CS" << std::endl;
        } else {
            std::cout << "Enter new number of working workshops: ";
            while (!(std::cin >> workingWorkshops) || workingWorkshops < 0 || workingWorkshops > workshops || (std::cin.peek() != '\n')) {
                std::cout << "Invalid input. Please enter a valid integer between 0 and " << workshops << ": ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "CS changed successfully.\n";
        }

    }
};

#endif /* STRUCTURES_H_ */