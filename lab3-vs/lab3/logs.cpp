#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>

#include "cs.h"
#include "pipeline.h"
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

void logPipe(Pipeline Pipe) {
    std::ofstream logFile("log.txt", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << ">>>\n"
            << Pipe << "\n"
            << ">>>" << std::endl;
    }

    logFile.close();
}

void logCS(CS Station) {
    std::ofstream logFile("log.txt", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << ">>>\n"
            << Station << "\n"
            << ">>>" << std::endl;
    }

    logFile.close();
}
