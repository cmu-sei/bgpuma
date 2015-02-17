
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <silk/silk.h>
#include <silk/utils.h>
#include <silk/skipset.h>

using namespace std;

void ReadFile(string filename,skipset_t **ipset);
