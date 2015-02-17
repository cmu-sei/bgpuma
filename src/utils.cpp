#include "utils.h"
vector<string> split(string &s, char delim)
{
	stringstream ss(s);
	string item;
	vector<string> elems;

	while(std::getline(ss, item, delim)) {
		if (item.empty()) continue;
		elems.push_back(item);
	}
	return elems;
}

