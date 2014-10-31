#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <silk/silk.h>
#include <silk/utils.h>
#include <silk/skipset.h>

#include "utils.h"

using namespace std;


int main(int argc, char **argv)
{
	string iparg;
	static skipset_t *ipset;
        /* get command line argument */
	iparg = argv[1];
	
	skipaddr_t out_val;
	uint32_t   out_cidr;
	skStringParseCIDR(&out_val,&out_cidr,iparg.c_str());
	skIPSetCreate(&ipset, 1);
}
