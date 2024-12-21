#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

#include "cs.h"
#include "pipeline.h"
#include "line.h"
#include "utils.h"

using std::cin;
using std::cout;

class Line;

int main()
{
    // Перенаправление потока в файл logs.txt
    std::ofstream logfile("logs.txt");
    redirect_output_wrapper redirector(std::cerr);
    redirector.redirect(logfile);

    std::unordered_map<int, Pipeline> pipelineMap;
    std::unordered_map<int, CS> csMap;
    Line line;

    short int menu_choice = -1;

    while (true)
    {   
        cout << "--------------------------------------------------------------------\n";
        cout << "Menu\n" << "Select menu item\n";
        cout << "1 - Add pipeline\n";
        cout << "2 - Add CS\n";
        cout << "3 - View all objects\n";
        cout << "4 - Save\n";
        cout << "5 - Load\n";
        cout << "6 - Filter pipelineMap by name\n";
        cout << "7 - Filter pipelineMap by repair status\n";
        cout << "8 - Filter cs by name\n";
        cout << "9 - Filter cs by % of working\n";
        cout << "10 - Delete pipe\n";
        cout << "11 - Delete cs\n";
        cout << "12 - Check connections\n";
        cout << "13 - Create connection\n";
        cout << "14 - Topolog sort\n";
        cout << "0 - Exit\n";
        cout << "--------------------------------------------------------------------\n";

        menu_choice = read_input<short int>("Select menu item: ", 0, 14);
        switch (menu_choice)
        {
        case 1: cin >> pipelineMap; break;
        case 2: cin >> csMap; break;
        case 3: cout << pipelineMap; cout << csMap; break;
        case 4: {
            if (csMap.size() != 0 || pipelineMap.size() != 0)
            {
                std::ofstream outfile("data.txt");
                outfile << csMap; 
                outfile << pipelineMap; 
                line.save_connections(outfile); 
                outfile.close(); 
                cout << "saved in file\n";
            }
            else { 
                cout << "you don't have pipelineMap or cs\n"; 
            } 
            break;
        }
        case 5: {
            std::ifstream outfile("data.txt");
            outfile >> csMap;
            outfile.clear(); 
            outfile.seekg(0, std::ios::beg); 
            outfile >> pipelineMap; outfile.clear(); 
            outfile.seekg(0, std::ios::beg); 
            line.load_connections(outfile, pipelineMap, csMap);  
            outfile.close(); 
            break;
        }
        case 6: filter_pipes_by_name(pipelineMap); break;
        case 7: filter_pipes_by_repair(pipelineMap); break;
        case 8: filter_cs_by_name(csMap); break;
        case 9: filter_cs_by_work_percentage(csMap); break;
        case 10: { 
            cout << pipelineMap; 
            int ch = read_input<int>("Enter ID of pipe: ", 0, pipelineMap.size() - 1); 
            line.delete_pipe(ch, pipelineMap); 
            pipelineMap.erase(ch); 
            break; 
        }
        case 11: { 
            cout << csMap; 
            int ch = read_input<int>("Enter ID of cs: ", 0, csMap.size() - 1); 
            line.delete_cs(ch, csMap); 
            csMap.erase(ch); 
            break; 
        }
        case 12: { 
            line.check_connection(pipelineMap, csMap); 
            break; 
        }
        case 13: { 
            line.create_connection(pipelineMap, csMap); 
            break; 
        }
        case 14: { 
            line.topologicalSort(pipelineMap, csMap); 
            break; 
        }
        case 0: logfile.close(); return 0;
        }
    }

    return 0;
}
