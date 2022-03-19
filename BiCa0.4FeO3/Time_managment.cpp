#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iterator>
#include <sstream>

int main()
{
	std::vector< std::pair< double, double > >time_temperature;
	std::ifstream input("BiCa0.4FeO3_cooling_modified.csv");

	std::string temp_str;
	std::stringstream ss;

	std::pair< double, double > temp_pair;

	while(getline(input, temp_str))
	{
		ss.clear();
		for(auto& c : temp_str)
		{
			if(c == ';')
				c = ' ';
		}

		ss << temp_str;
		
		ss >> temp_pair.first >> temp_pair.second;

		
		time_temperature.push_back(temp_pair);
	}

	input.close();

	std::ifstream main_input_file("BiCa0.4FeO3_12_12_21_update_on_higher_frequences_repaired.csv");
	std::ofstream main_output_file("BiCa0.4FeO3_12_12_21_update_on_higher_frequences_repaired_ready.csv");

	double temp_number;
	
	for(auto& c : time_temperature)
		std::cout << c.first << " " << c.second << std::endl;

	std::size_t k = 0u;

	std::size_t flag = 1u;
	while(getline(main_input_file, temp_str))
	{
		double closest_time = 0.0;
		double closest_temperature = 0.0;
	
		ss.clear();

		for(k = 0u; temp_str[k] != ';'; k++);

		auto it = temp_str.begin();
		std::advance(it, k);

		std::string str;
		for(auto i = 0; i < k; i++)
			str.push_back(temp_str[i]);
		
		ss << str << " ";
		ss >> temp_number;
		if(flag == 1u)
		{
			std::cout << str << std::endl;
			std::cout << *it << std::endl;
			std::cout << temp_number;
			flag = 2u;
		}
		for(auto& c : time_temperature)
		{
			if(fabs(temp_number - c.first) < fabs(temp_number - closest_time))
			{
				closest_time = c.first;
				closest_temperature = c.second;
			}
		}

		main_output_file << closest_temperature << std::string(it, temp_str.end()) << '\n';
	}

	return 0;
		
}