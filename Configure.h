/*
 * Configure.h
 *
 * Author: Zex <top_zlynch@yahoo.com>
 */

#include <sstream>
#include <map>
#include <fstream>
#include <stdlib.h>

#define INVALID_DOUBLE 9999.99

struct SortById
{
	std::string name_;

	SortById() {}

	SortById(std::string name)
	: name_(name)
	{}

	bool operator() (const std::string &a, const std::string &b)
	{
		std::istringstream is_a(a.substr(0, a.find_first_of(" ")));
		std::istringstream is_b(b.substr(0, b.find_first_of(" ")));
	
		int id_a, id_b;

		is_a >> id_a;
		is_b >> id_b;
	
		return (id_a < id_b);
	}
};

typedef std::map<std::string, double> ValueMap;
typedef std::map<std::string, std::string, SortById> ValueMapStr;

class Configure
{
	std::string conf_path_;
	std::ofstream ofs_;
	std::ifstream ifs_;
public:

	Configure(std::string path)
	: conf_path_(path)
	{
	}

	~Configure()
	{
	}
	
	void SaveConfigGroup(ValueMap vals);
	void SaveConfigHeader(std::string head);
	ValueMap ReadConfig();

};
