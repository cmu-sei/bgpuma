#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <map>


using namespace std;

typedef map<string,int> StringIntMap;

vector<string> split(string &s, char delim);
string join(StringIntMap & vec, const string & sep);
string join(const vector<string> & vec,const string & sep);
int RandomInt(int low, int high);
