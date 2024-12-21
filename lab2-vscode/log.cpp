#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>

#include "structures.h"
#include <string>
#include <chrono>

// Функция логирования строки
void logString(const std::string str) {

    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

    std::ofstream logFile("log.txt", std::ios_base::app);
    if (logFile.is_open()) {
        std::time_t t = std::chrono::system_clock::to_time_t(start);
        std::tm* ptm = std::localtime(&t);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%d.%m.%y %H:%M:%S", ptm);
        std::string time_str(buffer);
        logFile << "[" << time_str << "] " << str << std::endl;
        logFile.close();
    }
}

void logPipe(Pipeline pipe) {
    std::ofstream logFile("log.txt", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << ">>>\n"
        << pipe.name << "\n"
        << std::to_string(pipe.length) << "\n"
        << std::to_string(pipe.diameter) << "\n"
        << std::to_string(pipe.inRepair) << "\n"
        << ">>>" << std::endl;
    }

    logFile.close();
}

void logCS(CS Station) {
    std::ofstream logFile("log.txt", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << ">>>\n"
        << Station.name << "\n"
        << Station.workshops << "\n"
        << Station.workingWorkshops << "\n"
        << Station.efficiency << "\n"
        << ">>>" << std::endl;
    }

    logFile.close();
}
