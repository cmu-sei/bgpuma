#include "readfiles.h"

void ProcessFiles(BGPDATA BGP, std::ofstream &outFile)
{
	ifstream inFile;
        string line;

	inFile.open(BGP.file.data());
        if (!inFile) {
                cerr << "Couldn't open file " << BGP.file << "\n";
                exit(1);
        }
        while (getline(inFile,line,'\n')) {
		ReadBGPFile(BGP, line, outFile);
        }
        inFile.close();
        return;
}
