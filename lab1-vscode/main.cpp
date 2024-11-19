#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "structures.h"

// Очистить консоль 
void clear() {
    #if defined _WIN32
        system("cls");
    #endif
}

// Сохранить информацию в файл
void saveToFile(Pipeline Pipeline, CS Station, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << Pipeline.name << " " << Pipeline.length << " " << Pipeline.diameter << " " << Pipeline.inRepair << "\n";
        file << Station.name << " " << Station.workshops << " " << Station.workingWorkshops << " " << Station.efficiency << "\n";
        std::cout << "Data saved successfully.\n";
    } else {
        std::cerr << "Error opening file for saving.\n";
    }
    file.close();
}

// Загрузить информацию из файла
void loadFromFile(Pipeline& Pipeline, CS& Station, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> Pipeline.name >> Pipeline.length >> Pipeline.diameter >> Pipeline.inRepair;
        file >> Station.name >> Station.workshops >> Station.workingWorkshops >> Station.efficiency;
        std::cout << "Data loaded successfully.\n";
    } else {
        std::cerr << "Error opening file for loading.\n";
    }
    file.close();
}

// Главное меню
void menu() {
    Pipeline Pipe;
    CS Station;
    int choice;

    while (true) {
        std::cout << "\n1. Add pipeline\n2. Add CS\n3. View all objects\n4. Edit Pipeline\n5. Edit CS\n6. Save\n7. Load\n0. Exit\n";
        std::cout << "Select an option: ";
        while (!(std::cin >> choice) || choice < 0 || choice > 7 || isdigit(choice) || (std::cin.peek() != '\n')) {
            std::cout << "Invalid choice. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        clear();
        switch (choice) {
            case 1: {
                Pipe.getInfo();
                break;
            }
            case 2: {
                Station.getInfo();
                clear();
                break;
            }
            case 3: {
                std::cout << "Pipelines:\n";
                Pipe.showInfo();
                std::cout << "~~~" << std::endl;
                std::cout << "Compressor Stations:\n";
                Station.showInfo();
                break;
            }
            case 4: {
                Pipe.toggleRepairStatus();
                break;
            }
            case 5: {
                Station.editWorkingWorkshops();
                break;
            }
            case 6:
                saveToFile(Pipe, Station, "data.txt");
                break;
            case 7:
                loadFromFile(Pipe, Station, "data.txt");
                break;
            case 0:
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}