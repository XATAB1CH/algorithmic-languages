#include <iostream>
#include <fstream>
#include <string>
#include <limits> 
#include <sstream>

#include "structures.h"

using std::cout;
using std::cin;
using std::string;

short int startMenu(Pipeline& my_pipeline, CS& my_cs);
void Clear();
void addPipeline(Pipeline& my_pipline);
void addCS(CS& my_cs);
void saveFile(const string fileName, const Pipeline& new_pipeline, const CS& new_cs);
void showObjects(Pipeline& my_pipeline, CS& my_cs);
void getFromFile(const string filename, Pipeline& my_pipeline, CS& my_cs);
void editPipeline(Pipeline& my_pipeline);
void editCS(CS& my_cs);
void menu();

void menu()
{
	Pipeline my_pipeline;
	CS my_cs;

	startMenu(my_pipeline, my_cs);
};

short int startMenu(Pipeline& my_pipeline, CS& my_cs)
{
	while (true) {

		// вывод меню
		cout << "~~~\n";
		cout << "Menu\n" << "Select menu item\n";
		cout << "1 - add pipeline\n";
		cout << "2 - add CS\n";
		cout << "3 - view all objects\n";
		cout << "4 - edit pipe\n";
		cout << "5 - edit CS\n";
		cout << "6 - save in file\n";
		cout << "7 - download from file\n";
		cout << "0 - exit\n";
		cout << "~~~\n";

		// выбор меню
		unsigned short int menu_choice;
		cin >> menu_choice;

		// если неверный выбор меню
		while ((menu_choice < 0 || menu_choice > 7)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "" << "Select correct item from menu:\n";
		};

		Clear();
		switch (menu_choice)
		{
			case 1: addPipeline(my_pipeline); break;
			case 2: addCS(my_cs); break;
			case 3: showObjects(my_pipeline, my_cs); break;
			case 4: editPipeline(my_pipeline); break;
			case 5: editCS(my_cs); break;
			case 6: saveFile("save.txt", my_pipeline, my_cs); break;
			case 7: getFromFile("load.txt", my_pipeline, my_cs); break;
			case 0: return 0;
		}
	}

	return 0;
};

// функция очистки (https://stackoverflow.com/questions/6486289/how-can-i-clear-console)
void Clear()
{
	
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || (__APPLE__)
	system("clear");
#endif
}

// если нет трубы - добавляем новую, если есть - заменяем на новую
void addPipeline(Pipeline& my_pipeline)
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

	cout << "Enter the pipeline's kilometer sign: ";
	std::getline(cin, my_pipeline.kilometer_sign);

	cout << "Enter the pipeline's length (meters): ";
	while (!(cin >> my_pipeline.length_of_pipe) || my_pipeline.length_of_pipe < 1) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n
		cout << "Error. Enter a valid length: ";
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

	cout << "Enter the pipeline's diameter (millimeters): ";
	while (!(cin >> my_pipeline.diameter) || my_pipeline.diameter < 1) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

		cout << "Error. Enter a valid diameter: ";
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "Is it working or under repair?\nEnter '1' if it is working, '0' if it is under repair: ";
	while (!(cin >> my_pipeline.repair_indicator)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

		cout << "Error. Please enter '1' for working or '0' for under repair: ";
	}

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

	cout << "ok!" << std::endl;
};

// если нет станции - добавляем новую, если есть - заменяем на новую
void addCS(CS& my_cs)
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

	cout << "Enter the name of your cs: ";
	std::getline(cin, my_cs.name);

	cout << "Enter the number of workshops of cs: ";
	while (!(cin >> my_cs.number_of_workshops) || my_cs.number_of_workshops < 1) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

		cout << "Error. Please enter a valid number of workshops: ";
	};
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

	cout << "Enter the workshops in work: ";
	while (!(cin >> my_cs.workshops_in_work) || my_cs.workshops_in_work > my_cs.number_of_workshops || my_cs.workshops_in_work < 1) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n
		
		cout << "Error. Please enter a valid number: ";
	};
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

	cout << "Enter the efficiency (0-100): ";
	while (!(cin >> my_cs.efficiency) || my_cs.efficiency > 100 || my_cs.efficiency < 0) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

		cout << "Error. Please enter efficiency (1-100): ";
	};

	
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

	cout << "ok!" << std::endl;
};

void showObjects(Pipeline& my_pipeline, CS& my_cs)
{
	if (my_pipeline.kilometer_sign != "") {
		cout << "Pipeline:\n";
		cout 
			<< "kilometer sign: " << my_pipeline.kilometer_sign 
			<< "\nlength of pipe: " << my_pipeline.length_of_pipe 
			<< "\ndiameter: " << my_pipeline.diameter 
			<< "\nrepair indicator: " << my_pipeline.repair_indicator 
			<< "\n~~~" << std::endl;
	} else {
		cout << "There's no pipeline. Add a new one or get it from file.\n~~~\n"; 
	};

	if (my_cs.name != "") {
		cout << "CS:\n";
		cout 
			<< "name: " << my_cs.name 
			<< "\nnumber of workshops: " << my_cs.number_of_workshops 
			<< "\nworkshops in work: " << my_cs.workshops_in_work 
			<< "\nefficiency: " << my_cs.efficiency 
			<< std::endl;
	} else {
		cout << "There's no CS. Add a new one or get it from file.\n"; 
	};
};

void editPipeline(Pipeline& my_pipeline)
{
	if (my_pipeline.kilometer_sign != "") {
		cout << "Pipeline:\n";
		cout 
			<< "kilometer sign: " << my_pipeline.kilometer_sign 
			<< "\nlength of pipe: " << my_pipeline.length_of_pipe 
			<< "\ndiameter: " << my_pipeline.diameter 
			<< "\nrepair indicator: " << my_pipeline.repair_indicator << std::endl;

		cout << "Is it working or under repair?\nEnter '1' if it is working, '0' if it is under repair: ";
		while (!(cin >> my_pipeline.repair_indicator)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

			cout << "Error. Please enter '1' for working or '0' for under repair: ";
		}
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

		cout << "ok!" << std::endl;
	} else {
		cout << "There's no pipeline. Add a new one or get it from file.\n"; 
	};

	Clear();
}

void editCS(CS& my_cs)
{
	if (my_cs.name != "") {
		cout << "CS:\n";
		cout << "name: " << my_cs.name << "\nnumber of workshops: " << my_cs.number_of_workshops << "\nworkshops in work: " << my_cs.workshops_in_work << "\nefficiency: " << my_cs.efficiency << std::endl;
		cout << "Enter the workshops in work: ";
		while (!(cin >> my_cs.workshops_in_work) || my_cs.workshops_in_work > my_cs.number_of_workshops || my_cs.workshops_in_work < 0) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n
			cout << "Error. Please enter a valid number: ";
		};
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем все вводы до \n

		cout << "ok!" << std::endl;
	} else {
		cout << "There's no CS. Add a new one or get it from file.\n"; 
	};
}

void getFromFile(const std::string filename, Pipeline& my_pipeline, CS& my_cs)
{
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return;
	}

	if (file.peek() == std::ifstream::traits_type::eof()) {
		std::cerr << "Error: File " << filename << " is empty." << std::endl;
		file.close();
		return;
	}

	std::string line;
	bool pipelineIsLoaded = false;
	bool CsIsLoaded = false;

	while (std::getline(file, line)) {
		if (line == "@pipeline@") {
			std::getline(file, my_pipeline.kilometer_sign);
			if (my_pipeline.kilometer_sign.empty()) {
				std::cerr << "Error: Invalid pipeline's kilometer sign in file." << std::endl;
				continue;
			}

			if (!(file >> my_pipeline.length_of_pipe) || my_pipeline.length_of_pipe <= 0) {
				std::cerr << "Error: Invalid pipeline's length in file." << std::endl;
				continue;
			}

			if (!(file >> my_pipeline.diameter) || my_pipeline.diameter <= 0) {
				std::cerr << "Error: Invalid pipeline's diameter in file." << std::endl;
				continue;
			}

			if (!(file >> my_pipeline.repair_indicator) || (my_pipeline.repair_indicator != 0 && my_pipeline.repair_indicator != 1)) {
				std::cerr << "Error: Invalid pipeline's repair indicator in file. Must be 0 or 1." << std::endl;
				continue;
			}

			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			pipelineIsLoaded = true;
		}


		else if (line == "@cs@") {
			std::getline(file, my_cs.name);
			if (my_cs.name.empty()) {
				std::cerr << "Error: Invalid CS's name in file." << std::endl;
				continue;
			}

			if (!(file >> my_cs.number_of_workshops) || my_cs.number_of_workshops <= 0) {
				std::cerr << "Error: Invalid CS's number of workshops in file." << std::endl;
				continue;
			}

			if (!(file >> my_cs.workshops_in_work) || my_cs.workshops_in_work < 0 || my_cs.workshops_in_work > my_cs.number_of_workshops) {
				std::cerr << "Error: Invalid CS's number of workshops in work in file." << std::endl;
				continue;
			}

			if (!(file >> my_cs.efficiency) || my_cs.efficiency < 0 || my_cs.efficiency > 100) {
				std::cerr << "Error: Invalid CS's efficiency in file. Must be between 0 and 100." << std::endl;
				continue;
			}

			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			CsIsLoaded = true;
		}

	}

	file.close();

	if (!pipelineIsLoaded)
	{
		my_pipeline.kilometer_sign;
		my_pipeline.length_of_pipe;
		my_pipeline.diameter;
		my_pipeline.repair_indicator;
	}

	if (!CsIsLoaded)
	{
		my_cs.name;
		my_cs.number_of_workshops;
		my_cs.workshops_in_work;
		my_cs.efficiency;
	}

	if (!pipelineIsLoaded && !CsIsLoaded) {
		std::cerr << "Error: No valid pipeline's or CS's data found in the file." << std::endl;
	}
}


void saveFile(const std::string fileName, const Pipeline& my_pipeline, const CS& my_cs)
{
	if (my_pipeline.kilometer_sign != "" || my_cs.name != "")
	{
		std::ofstream out(fileName);

		if (my_pipeline.kilometer_sign != "default") {
			out << "@pipeline@" << '\n'
				<< my_pipeline.kilometer_sign << '\n'
				<< my_pipeline.length_of_pipe << '\n'
				<< my_pipeline.diameter << '\n'
				<< my_pipeline.repair_indicator << '\n';
		}

		if (my_cs.name != "default") {
			out << "@cs@" << '\n'
				<< my_cs.name << '\n'
				<< my_cs.number_of_workshops << '\n'
				<< my_cs.workshops_in_work << '\n'
				<< my_cs.efficiency << '\n';
		}

		out.close();
	}
	else { 
		cout << "Add CS or pipeline.\n"; 
	}
}