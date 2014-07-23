#include "readasnfile.h"


void ReadASNFile(BGPDATA &BGP) 
{
	ifstream inFile;
	string line;
	inFile.open(BGP.asnfile.data());
	while (getline(inFile,line,'\n')) {
		BGP.ASNList[line] = 1;
	}
	inFile.close();
	return;	

}

