#include "cs.h"
#include "line.h"

#include <iostream>
#include <fstream>
#include "utils.h"

using std::cin;
using std::cout;

class Line;

int Line::MaxIDCS = 0;

CS::CS()
{
    id = Line::MaxIDCS++;
}

std::istream& operator >> (std::istream& in, std::unordered_map<int, CS>& css) {
    CS cs;

    cs.name = read_input<std::string>("Enter name CS: ");
    cs.workshops = read_input<int>("Enter number of workshops: ", 0);
    cs.workingWorkshops = read_input<int>("Enter workshops in work: ", 0, cs.workshops);
    cs.efficiency = read_input<int>("Enter efficiency (0-100): ", 0, 100);

    css.insert({ cs.GetID(), cs });
    return in;
}

std::ostream& operator << (std::ostream& out, const std::unordered_map<int, CS>& css)
{
    if (css.size() == 0) { cout << "you have not cs\n"; return out; }
    for (const auto& cs : css) {
        out << cs.second;
    }
    return out;
};

std::ostream& operator << (std::ostream& out, const CS& cs)
{
    out << "\nID: " << cs.id
        << "\nCS name: " << cs.name
        << "\nCS number of workshops: " << cs.workshops
        << "\nCS workshops in work: " << cs.workingWorkshops
        << "\nThe CS attribute: " << cs.efficiency << std::endl;
    return out;
};

void change_workshops_in_work(CS& cs, int& new_workingWorkshops)
{
    if (new_workingWorkshops <= cs.workshops)
    {
        cs.workingWorkshops = new_workingWorkshops;
        return;
    }
    else
    {
        cout << "Error CS id=" << cs.id << " have " << cs.workshops << " workshops";
        return;
    }
}
std::ofstream& operator << (std::ofstream& out, const std::unordered_map<int, CS>& css)
{
    for (const auto& cs : css) {
        out << cs.second;
    }
    return out;
}

std::ofstream& operator << (std::ofstream& out, const CS& cs)
{
    out << "@cs@" << "\n"
        << cs.name << "\n"
        << cs.workshops << "\n"
        << cs.workingWorkshops << "\n"
        << cs.efficiency << "\n";
    return out;
};


std::ifstream& operator >> (std::ifstream& in, std::unordered_map<int, CS>& css) {
    std::string line;
    while (std::getline(in, line)) {
        if (line == "@cs@") {
            CS cs;

            if (!std::getline(in, cs.name) || cs.name.empty()) {
                cout << "Error pipe in file\n";
                continue;
            }

            if (!(in >> cs.workshops) || cs.workshops <= 0) {
                cout << "Error pipe in file\n";
                in.clear(); in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (!(in >> cs.workingWorkshops) || cs.workingWorkshops < 0 || cs.workingWorkshops > cs.workshops) {
                cout << "Error pipe in file\n";
                in.clear(); in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (!(in >> cs.efficiency) || cs.efficiency < 0 || cs.efficiency > 100) {
                cout << "Error pipe in file\n";
                in.clear(); in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            css.insert({ cs.GetID(), cs });
            //std::cerr << "2\n" << cs.name << std::endl << cs.workshops << std::endl << cs.workingWorkshops << std::endl << cs.efficiency << std::endl;
        }
    }
    return in;
}

void filter_cs_by_name(std::unordered_map<int, CS>& cs)
{
    std::string name = read_input<std::string>("Enter the name of the cs to filter: ");
    std::vector<int> ids;
    bool flag = false;


    for (const auto& p : cs) {
        if (p.second.name.find(name) != std::string::npos) {
            cout << p.second;
            ids.push_back(p.second.id);
            flag = true;
        }
    }

    if (!flag) { cout << "You don't have cs with name: " << name << std::endl; return; }

    int ch = read_input<int>("0 - menu:\n1 - chenge cs\n", 0, 1);

    if (ch == 0) { return; }
    ch = read_input<int>("Enter number of workshops in work ", 0);

    for (const auto& id : ids)
    {
        change_workshops_in_work(cs[id], ch);
    }
}

void filter_cs_by_work_percentage(std::unordered_map<int, CS>& cs)
{
    int percentage = read_input<int>("Enter the work percentage to filter (0-100): ", 0, 100);
    int choice = read_input<int>("Choose option: 1 - More, 2 - Less, 3 - =", 1, 3);
    bool flag = false;

    std::vector<int> ids;
    for (const auto& p : cs) {
        int current_percentage = (p.second.workingWorkshops * 100) / p.second.workshops;
        if ((choice == 1 && current_percentage > percentage) ||
            (choice == 2 && current_percentage < percentage) ||
            (choice == 3 && current_percentage == percentage))
        {
            cout << p.second;
            ids.push_back(p.second.id);
        }
    }

    if (!flag)
    {
        if (choice == 1) { cout << "You don't have cs with % of working > then: " << percentage << std::endl; }
        else if (choice == 2) { cout << "You don't have cs with % of working < then: " << percentage << std::endl; }
        else { cout << "You don't have cs with % of working = " << percentage << std::endl; }
        return;
    }


    int ch = read_input<int>("0 - menu\n1 - edit CS\n", 0, 1);

    if (ch == 0) return;

    ch = read_input<int>("Enter number of workshops in work ", 0);

    for (const auto& id : ids)
    {
        change_workshops_in_work(cs[id], ch);
    }
}
