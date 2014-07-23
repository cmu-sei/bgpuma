#include <iostream>
#include <fstream>
#include <getopt.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <map>
#include <algorithm>
#include <sstream>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <silk/silk.h>
#include <silk/utils.h>
#include <silk/skipset.h>

#include "createset.h"
#include "readfile.h"
#include "readfiles.h"
#include "readdir.h"
#include "data.h"
#include "readasnfile.h"

using namespace std;

void print_help();
