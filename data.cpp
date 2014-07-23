#include "data.h"

void Initialize(BGPDATA &BGP) 
{
	BGP.or_flag = 0;
	BGP.verbose = 0;
	BGP.startdate = "";
	BGP.enddate = "";
	BGP.setfile = "";
	BGP.asnfile = "";
	BGP.outfile = "";
	BGP.file = "";
	BGP.ipset = NULL;
}
