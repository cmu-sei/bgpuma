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

string join(StringIntMap & vec, const string & sep)
{
	if (vec.size() == 0) return "";
	string tmp = "";
	StringIntMap::iterator it;

	for (it = vec.begin(); it != vec.end(); it++) {
		if (tmp.empty()) {
			tmp = it->first;
			continue;
		}
		tmp = tmp+sep+it->first;
	}

	return tmp;
}

string join(const vector<string> & vec,const string & sep)
{
        if(vec.size()==0)
                return "";
        string tmp;
        tmp=vec[0];
        for(unsigned int i=1;i<vec.size();i++)
        {
                tmp=tmp+sep+vec[i];
        }
        return tmp;
}



int RandomInt(int low, int high)
{
        return (random()%(high-low+1))+low;
}

