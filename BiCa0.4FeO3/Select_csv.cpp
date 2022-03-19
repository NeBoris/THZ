#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>


std::string readFile(const std::string& fileName) {
    std::ifstream f(fileName);
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

int main()
{

    std::fstream logger("process.txt", std::ios::out);

    //////////////////////////////////
    logger << "Filling Data.csv\n";
    std::cout << "Filling Data.csv\n";

    std::filesystem::path data{"data"};

    std::filesystem::path file_path;

    std::ofstream output_csv{"data.csv"};
 
    for(auto const& dir_entry: std::filesystem::directory_iterator{data})
    {
        file_path = dir_entry.path() / "dev3980_imps_0_sample_00000.csv";
        output_csv << file_path.string() << '\n';
    }
    output_csv.close();

    logger << "Data.csv is filled\n";
    std::cout << "Data.csv is filled\n";

    //////////////////////////////////

    std::filesystem::path file_with_paths_to_the_data{"data.csv"};
    std::ifstream paths_to_the_files(file_with_paths_to_the_data.string());

    std::filesystem::path file;
    std::string file_name;

    std::regex freq(R"([\d|;|.]+;frequency;[\d|;|.]+)");
    std::regex absz(R"([\d|;|.]+;absz;[\d|;|.|-|+|e|е]+)");
    std::regex phase(R"([\d|;|.]*;phasez;[^[:space:]]+)");
    std::stringstream temp;

    std::size_t counter = 1;

    while(std::getline(paths_to_the_files, file_name))
    {
        logger << counter << '\n';
        std::cout << counter << '\n';
        file = file_name;  

        std::string line = readFile(file.string());    

            std::ifstream input_data_file(file.string());
            std::ofstream output_temp_file(file.parent_path() / "temp.txt");
             
            std::smatch sm;
            for(int i = 0; i <= 3; i++)
            {
                std::regex_search(line, sm, absz);
                line = sm.suffix();
                output_temp_file << sm.str() << '\n';
                std::regex_search(line, sm, freq);
                line = sm.suffix();
                output_temp_file << sm.str() << '\n';
                std::regex_search(line, sm, phase);
                line = sm.suffix();
                output_temp_file << sm.str() << '\n';
            }
            
            input_data_file.close();
            output_temp_file.close();

            counter++;
    }

    paths_to_the_files.close();


    //////////////////////////////////
    logger.close();

    return 0;
}