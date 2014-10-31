#include "createset.h"

void ReadFile(string filename,skipset_t **ipset) 
{
	ifstream inFile;
        string line;
	skipaddr_t out_val;
        uint32_t   out_cidr;

	skIPSetCreate(ipset, 1);

	inFile.open(filename.data());
	if (!inFile) {
                cerr << "Couldn't open file " << filename << "\n";
                exit(1);
        }
        while (getline(inFile,line,'\n')) {
		skStringParseCIDR(&out_val,&out_cidr,line.c_str());	
		skIPSetInsertAddress(*ipset, &out_val, out_cidr);
	}
	inFile.close();
	return;
}
