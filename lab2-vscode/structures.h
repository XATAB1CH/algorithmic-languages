#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <string>

std::ostream& operator << (std::ostream& out, const Pipeline& pipe)
{
    out << "\nID: " << pipe.id
        << "\nPipe name: " << pipe.name
        << "\nPipe length: " << pipe.length
        << "\nPipe diameter: " << pipe.diameter
        << "\nThe pipe attribute: " << pipe.inRepair << std::endl;
    return out;
};



struct Pipeline
{
    int id;
    std::string name;
    double length;
    double diameter;
    bool inRepair;

    // Вывод данных трубы
    void showInfo(std::ostream& os = std::cout) const {
        os << "Pipeline ID: " << id << "\n"
           << "Name: " << name << "\n"
           << "Length: " << length << " km\n"
           << "Diameter: " << diameter << " m\n"
           << "In Repair: " << (inRepair ? "Yes" : "No") << "\n";
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

    // Вывод данных КС
    void showInfo() const {
        std::cout << "Index: " << id << ", CS: " << name << ", Workshops: " << workshops 
                  << ", Working: " << workingWorkshops 
                  << ", Efficiency: " << efficiency << "\n";
    }

    void editWorkingWorkshops() {
            std::cout << "Enter new number of working workshops: ";
            while (!(std::cin >> workingWorkshops) || workingWorkshops < 0 || workingWorkshops > workshops) {
                std::cout << "Invalid input. Please enter a valid integer between 0 and " << workshops << ": ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
};

#endif /* STRUCTURES_H_ */