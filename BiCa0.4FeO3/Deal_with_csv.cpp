#include <fstream>
#include <iostream>
#include <sstream>
#include <numbers>
#include <filesystem>
#include <iterator>
#include <string>
#include <cmath>
#include <vector>


double eps1(double freq, double absz, double phasez, double S, double d)
{
    double eps_0 = 8.85e-12;
    return -(d * std::sin(phasez)) / (2 * std::numbers::pi * freq * eps_0 * S * absz);
}

double eps2(double freq, double absz, double phasez, double S, double d)
{
    double eps_0 = 8.85e-12;
    return (d * std::cos(phasez)) / (2 * std::numbers::pi * freq * eps_0 * S * absz);
}

int main()
{
    std::filesystem::path file_with_paths_to_the_data{"data.csv"};
    std::ifstream paths_to_the_files(file_with_paths_to_the_data.string());

    std::filesystem::path file;
    std::string file_name;

    std::string line; 

    while(std::getline(paths_to_the_files, file_name))
    {

        file = file_name;

        // In    input_temp_file     12 rows with raw data. Frequency, absz, phasez. Delimiter ';'. First 3 columns are extra
        // need to be deleted
        std::ifstream input_temp_file(file.parent_path() / "temp.txt");

        std::vector< std::vector < double > > vector_of_data(12, std::vector< double >{});

        ///////////////////////////////////////////////////////////
        //      vector_of_data[0, 3, 6, 9]  - |z| (absz)         //
        //      vector_of_data[1, 4, 7, 10]  - f (frequency)     //
        //      vector_of_data[1, 4, 7, 10]  - phasez            //
        ///////////////////////////////////////////////////////////


        for(std::size_t k = 0; std::getline(input_temp_file, line); k++)
        {
            std::size_t last_letter = 0;
            for(auto i = 0U; i < line.size(); i++)
            {                
                if(line[i] == ';')
                    line[i] = '\n';
                if(line[i] >= 'a' && line[i] <= 'z' && line[i + 1] == ';')
                {
                    last_letter = i;
                }
            }
            line.erase(0, last_letter + 2);

            std::stringstream ss;
            ss << line;
            
            double temp_num;
            while(ss >> temp_num)
            {
                vector_of_data[k].push_back(temp_num);
            }
            
        }

        input_temp_file.close();

        // d - thickness
        // S - area      
        double d = 80e-6;
        double S = 1.815e-5;

        // eps_from_freq    containst eps' and eps'' with respect to frequence
        std::vector< std::vector < double > > eps_from_freq;

        // to choose the closest to needed frequence (avg_1 and avg_2) point
        std::size_t closest_1, closest_2;
        double avg_1, avg_2;

        // iterate over the chanks
        for(auto j = 1U; j < 12U; j += 3)
        {
            closest_1 = 0;
            closest_2 = 0;
            
            switch (j) {
                case 1U:
                    // 1st chank gives 10 Hz and 100 Hz
                    avg_1 = 10.0;
                    avg_2 = 100.0;
                    break;
                case 4U:
                    // 2nd chank gives 10^3 Hz and 10^4 Hz
                    avg_1 = 1000.0;
                    avg_2 = 10000.0;
                    break;
                case 7U:
                    // 3rd chank gives 10^5 Hz
                    avg_1 = 100000.0;
                    avg_2 = 300000.0;
                    break;
                case 10U:
                    // 4th chank gives 10^6 Hz
                    avg_1 = 500000.0;
                    avg_2 = 700000.0;
                    break;
            }

            // iterate over the frequencies to choose the closest one
            for(auto i = 0U; i < vector_of_data[j].size(); i++)
            {        
                if(fabs(vector_of_data[j][i] - avg_1) < fabs(vector_of_data[j][closest_1] - avg_1))
                    closest_1 = i;
                
                if(avg_2 > 0.0 && fabs(vector_of_data[j][i] - avg_2) < fabs(vector_of_data[j][closest_2] - avg_2))
                    closest_2 = i;
            }

            eps_from_freq.push_back( {vector_of_data[j][closest_1],
                eps1(vector_of_data[j][closest_1], vector_of_data[j - 1][closest_1], vector_of_data[j + 1][closest_1], S, d),
                eps2(vector_of_data[j][closest_1], vector_of_data[j - 1][closest_1], vector_of_data[j + 1][closest_1], S, d) }); 
            
            if(avg_2 > 0.0)
                eps_from_freq.push_back( {vector_of_data[j][closest_2],
                    eps1(vector_of_data[j][closest_2], vector_of_data[j - 1][closest_2], vector_of_data[j + 1][closest_2], S, d),
                    eps2(vector_of_data[j][closest_2], vector_of_data[j - 1][closest_2], vector_of_data[j + 1][closest_2], S, d) }); 
        }
        
        // data/BiCa40FeO3 06.12.21_11 18 21 06.12.21_11 19 03_000
        std::string time;
        for(auto c  = 16; c < 51; c++)
            time.push_back(file.parent_path().string()[c]);
        
        time[8] = ' ';
        time[26] = ' ';
        time[11] = ':';
        time[14] = ':';
        time[17] = ',';
        time[29] = ':';
        time[32] = ':';

        std::ofstream out("BiCa0.4FeO3_12_12_21_update_on_higher_frequences_test.csv", std::ios::app);
        
        out << time << ",";
        
        for(auto & s : eps_from_freq)
        {
            for(auto & l : s)
            {
                out << l << ",";
            }
        }
        out << '\n';
    }

    return 0;
}