/*
Copyright 2015 Carnegie Mellon University

This material is based upon work funded and supported by Department of Homeland Security under Contract No. FA8721-05-C-0003 with Carnegie Mellon University for the operation of the Software Engineering Institute, a federally funded research and development center sponsored by the United States Department of Defense.

Any opinions, findings and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of Department of Homeland Security or the United States Department of Defense.

NO WARRANTY. THIS CARNEGIE MELLON UNIVERSITY AND SOFTWARE ENGINEERING INSTITUTE MATERIAL IS FURNISHED ON AN AS-IS BASIS. CARNEGIE MELLON UNIVERSITY MAKES NO WARRANTIES OF ANY KIND, EITHER EXPRESSED OR IMPLIED, AS TO ANY MATTER INCLUDING, BUT NOT LIMITED TO, WARRANTY OF FITNESS FOR PURPOSE OR MERCHANTABILITY, EXCLUSIVITY, OR RESULTS OBTAINED FROM USE OF THE MATERIAL. CARNEGIE MELLON UNIVERSITY DOES NOT MAKE ANY WARRANTY OF ANY KIND WITH RESPECT TO FREEDOM FROM PATENT, TRADEMARK, OR COPYRIGHT INFRINGEMENT.

This material has been approved for public release and unlimited distribution.

CERT® is a registered mark of Carnegie Mellon University.
*/
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
