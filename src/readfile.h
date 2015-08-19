
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <silk/silk.h>
#include <silk/skipset.h>
#include <silk/utils.h>
#include <iostream>

#include "data.h"

extern "C"{
#include <bgpdump_lib.h>
}

using namespace std;

void ReadBGPFile(BGPDATA BGP,string file,std::ofstream &outFile );
void process(BGPDUMP_ENTRY *my_entry, BGPDATA BGP,std::ofstream &outFile);
void show_prefixes(int count,struct prefix *prefix,BGPDATA BGP,BGPDUMP_ENTRY *entry,std::ofstream &outFile);
void show_prefixes6(int count,struct prefix *prefix,BGPDATA BGP,BGPDUMP_ENTRY *entry,std::ofstream &outFile);
int ValidateSet(char *cidr, BGPDATA BGP);
int ValidatePath(char *path, BGPDATA BGP);
void print_entry(char *cidr, BGPDUMP_ENTRY *entry,std::ofstream &outFile);
char *print_asn(as_t asn);
