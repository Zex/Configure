/*
 * Configure.cpp
 *
 * Author: Zex <top_zlynch@yahoo.com>
 */

#include <iomanip>
#include "Configure.h"

void Configure::SaveConfigGroup(ValueMap vals)
{
    ofs_.open(conf_path_.c_str(), std::ios::app|std::ios::out);

    for (ValueMap::iterator it = vals.begin(); it != vals.end(); it++)
    {
		std::string title = it->first;
		if (title.empty()) continue;

//		title = title.substr(title.find_first_of(" ")+1);
		ofs_ << title << ": " << it->second << '\n';
	}

	ofs_ << '\n';
	ofs_.close();
}

void Configure::SaveConfigHeader(std::string head)
{
    ofs_.open(conf_path_.c_str(), std::ios::out);
    ofs_ << head << "\n";
    ofs_.close();
}

ValueMap Configure::ReadConfig()
{
	ValueMap vals;
	vals.clear();

    std::ifstream ifs_(conf_path_.c_str(), std::ios::in);
    std::string line;

	while(std::getline(ifs_, line))
	{
        std::string name = line.substr(0, line.find_first_of(":"));
        if (name.empty() || name == line) continue;

		std::string buf(line.substr(line.find_first_of(":")+1));
		std::istringstream ss(buf.substr(buf.find_first_of("-0123456789")));

		double value;
		ss >> value;
        vals[name] = value;
	}

    ifs_.close();

	return vals;
}


// ---------------------test------------------
//#include <fstream>
//#include <vector>
//#include <iostream>
//
//void save_conf()
//{
//	std::ofstream ofs("aaa.file", std::ios::out);
//	ofs << "####### aaa.file ########" << '\n';
//	ofs.close();
//}
//
//void save_item(int i, int end)
//{
//	std::ofstream ofs("aaa.file", std::ios::app);
//
//	for (; i < end; i++)
//	ofs << "value" << i << ": " << 100.322+i << '\n';
//
//	ofs << '\n';
//	
//	ofs.close();
//}
//
//int main()
//{
//	save_conf();
//	save_item(1, 10);
//	save_item(20, 30);
//
//	std::vector<double> values;
//	for(double i = 0.30; i < 0.43; i+=0.01)
//	{
//		values.push_back(100+i);
//		std::cout << 100+i << '\n';
//	}
//
//	std::cout << '\n';	
//	double* val = &values.at(3);
//	std::cout << *val << '\n';
//
//	return 0;
//}
//
//#include "11002-702/include/fw3d/display/Configure.h"
//#include <iostream>
//
//int main()
//{
//	Configure conf("aaa.file");
//	ValueMap vals;
//	conf.ReadConfig(vals);
//
//	for (ValueMap::iterator it = vals.begin(); it != vals.end(); it++)
//		std::cout << it->first << ": " << it->second << '\n';
//
//	conf.SaveConfigHeader("######## header again ##########");
//
//	conf.SaveConfigGroup(vals);
//	conf.SaveConfigGroup(vals);
//
//	return 0;
//}
// --------------------end-test------------------
