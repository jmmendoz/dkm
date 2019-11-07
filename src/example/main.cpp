#include "../../include/dkm.hpp"
#include "../../include/dkm_parallel.hpp"
#include "../../include/dkm_utils.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

#ifdef __clang__
#pragma clang diagnostic ignored "-Wmissing-braces"
#endif


std::tuple<int, std::string, std::string, int, int, int> readargs(int argc, char* argv[]) 
{ 
    int counter;

    //defaults
    int k = 1;
    string infilename = "eggs.csv";
    string outfilename = "default.csv";
    int capacity1 = -1;
    int capacity2 = -1;
    int capacity3 = -1;

    printf("Program Name Is: %s",argv[0]); 
    if(argc==1) 
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name"); 
    if(argc>=2) 
    { 
        printf("\nNumber Of Arguments Passed: %d",argc); 
        printf("\n----Following Are The Command Line Arguments Passed----"); 
        for(counter=0;counter<argc;counter++){ 
            printf("\nargv[%d]: %s",counter,argv[counter]);
            if(counter==1){
            	string s = argv[counter];
            	k = std::stoi(s);
            }
            else if(counter==2){
            	infilename = argv[2];
            }
            else if(counter==3){
            	outfilename = argv[3];
            }
            else if(counter==4){
            	string s = argv[counter];
            	capacity1 = std::stoi(s);
            }
            else if(counter==5){
            	string s = argv[counter];
            	capacity2 = std::stoi(s);
            }
            else if(counter==6){
            	string s = argv[counter];
            	capacity3 = std::stoi(s);
            }
        }
    }
    cout << endl;
    return std::make_tuple(k, infilename, outfilename, capacity1, capacity2, capacity3); 
} 


int main(int argc, char* argv[]) {
	auto params = readargs(argc, argv);
	int k = std::get<0>(params);
	const std::string& path = std::get<1>(params);
	string outfilename = std::get<2>(params);
	// int cap1 = std::get<3>(params);
	// int cap2 = std::get<4>(params);
	// int cap3 = std::get<5>(params);
	
	auto data = dkm::load_capacitated_csv<double, 2>(path);
	auto capacities = dkm::load_csv_capacities<int, 2>(path);
	//std::vector<std::array<float, 2>> data{{1.f, 1.f}, {2.f, 2.f}, {1200.f, 1200.f}, {2.f, 2.f}};
	auto cluster_data = dkm::kmeans_lloyd(data, k);
	int *capacitySums = new int[k];
	memset(capacitySums, 0, sizeof *capacitySums);


	ofstream outfile;
	outfile.open(outfilename, ios::out);

	int i = 0;
	for (const auto& point : data) {
		std::stringstream value;
		auto label = std::get<1>(cluster_data)[i];
		auto cap1 = capacities[i][0];
		capacitySums[label] += cap1;
		value << "Point," << point[0] << "," << point[1] << "," << label << "," << cap1;
		outfile << value.str() << std::endl;
		i++;
	}
	i=0;
	for (const auto& mean : std::get<0>(cluster_data)) {
		outfile << "Mean," << mean[0] << "," << mean[1] << "," << capacitySums[i] << std::endl;
		i++;
	}
	std::cout << "Done, result written to " << outfilename << std::endl;
	// std::cout << "\tLabel:";
	// for (const auto& label : std::get<1>(cluster_data)) {
	// 	std::cout << std::setw(14) << label;
	// }
	// std::cout << std::endl;
}


