/*
Copyright 2015 Carnegie Mellon University

This material is based upon work funded and supported by Department of Homeland Security under Contract No. FA8721-05-C-0003 with Carnegie Mellon University for the operation of the Software Engineering Institute, a federally funded research and development center sponsored by the United States Department of Defense.

Any opinions, findings and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of Department of Homeland Security or the United States Department of Defense.

NO WARRANTY. THIS CARNEGIE MELLON UNIVERSITY AND SOFTWARE ENGINEERING INSTITUTE MATERIAL IS FURNISHED ON AN AS-IS BASIS. CARNEGIE MELLON UNIVERSITY MAKES NO WARRANTIES OF ANY KIND, EITHER EXPRESSED OR IMPLIED, AS TO ANY MATTER INCLUDING, BUT NOT LIMITED TO, WARRANTY OF FITNESS FOR PURPOSE OR MERCHANTABILITY, EXCLUSIVITY, OR RESULTS OBTAINED FROM USE OF THE MATERIAL. CARNEGIE MELLON UNIVERSITY DOES NOT MAKE ANY WARRANTY OF ANY KIND WITH RESPECT TO FREEDOM FROM PATENT, TRADEMARK, OR COPYRIGHT INFRINGEMENT.

This material has been approved for public release and unlimited distribution.

CERT® is a registered mark of Carnegie Mellon University.
*/
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
