#include <dirent.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <unistd.h>

using namespace std;

#include "readfile.h"
#include "dates.h"
#include "data.h"

typedef vector<string> StringVector;

bool substrcmp(std::string const & a, std::string const & b);
StringVector GetFiles(string dir);
StringVector GetFiles(string dir,string pattern);
void Traverse(BGPDATA BGP, string pattern,std::ofstream &outFile );
