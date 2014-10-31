#include <string>
#include <map>
#include <vector>
#include <silk/skipset.h>
#include <fstream>
#include <iostream>

using namespace std;

typedef map<string, int>  MapString;
#ifndef _BGPDATA
#define _BGPDATA
struct BGPDATA {
	int verbose;
	int or_flag;
	skipset_t *ipset;
	MapString ASNList;
	vector<string> dir;
	string startdate;
	string enddate;
	vector<string> bgpfile;
	string setfile;
	string asnfile;
	string outfile;
	string file;
};

#endif

void Initialize(BGPDATA &BGP);
