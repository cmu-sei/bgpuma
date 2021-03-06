/*
Copyright 2015 Carnegie Mellon University

This material is based upon work funded and supported by Department of Homeland Security under Contract No. FA8721-05-C-0003 with Carnegie Mellon University for the operation of the Software Engineering Institute, a federally funded research and development center sponsored by the United States Department of Defense.

Any opinions, findings and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of Department of Homeland Security or the United States Department of Defense.

NO WARRANTY. THIS CARNEGIE MELLON UNIVERSITY AND SOFTWARE ENGINEERING INSTITUTE MATERIAL IS FURNISHED ON AN AS-IS BASIS. CARNEGIE MELLON UNIVERSITY MAKES NO WARRANTIES OF ANY KIND, EITHER EXPRESSED OR IMPLIED, AS TO ANY MATTER INCLUDING, BUT NOT LIMITED TO, WARRANTY OF FITNESS FOR PURPOSE OR MERCHANTABILITY, EXCLUSIVITY, OR RESULTS OBTAINED FROM USE OF THE MATERIAL. CARNEGIE MELLON UNIVERSITY DOES NOT MAKE ANY WARRANTY OF ANY KIND WITH RESPECT TO FREEDOM FROM PATENT, TRADEMARK, OR COPYRIGHT INFRINGEMENT.

This material has been approved for public release and unlimited distribution.

CERT® is a registered mark of Carnegie Mellon University.
*/
#include "readdir.h"

bool substrcmp(std::string const & a, std::string const & b)
{
        string asub = a.substr(a.length()-17);
        string bsub = b.substr(b.length()-17);
        
    return  asub.compare(bsub) < 0;
}

StringVector GetFiles(string dir)
{
	DIR *DH;
	struct dirent *ent;
	StringVector files;
	
	string last = dir.substr(dir.length(),-1);
	if (last.compare("/") != 0) {
		dir += "/";
	}
	if ((DH = opendir (dir.c_str())) != NULL) {
		while ((ent = readdir(DH)) != NULL) {
			string fname;
			fname = ent->d_name;
			files.push_back(dir+fname);
		}
	}

	return files;
}

StringVector GetFiles(string dir,string pattern)
{
	DIR *DH;
	struct dirent *ent;
	StringVector files;
	
	char end[] = "/";
	int len = strlen(dir.c_str());
	const char *last = &dir[len];
	if (strcmp(last,end) != 0) {
		dir += "/";
	}

	string dot = ".";
	if ((DH = opendir (dir.c_str())) != NULL) {
		while ((ent = readdir(DH)) != NULL) {
			string fname;
			fname = ent->d_name;
			if (fname.compare(0,1,dot) == 0) continue;
			std::size_t found = fname.find(pattern);
			if (found!=std::string::npos)
				files.push_back(dir+fname);
		}
	}

	return files;
}


void Traverse(BGPDATA BGP,  string pattern, std::ofstream &outFile )
{
	StringVector FileNames;
	string Year = getYear(pattern);
	string Month = getMonth(pattern);
	vector<string>::iterator it, dit;

	if (BGP.verbose) {
		cerr << "Building list of files...\n";
	}
	for (dit = BGP.dir.begin(); dit != BGP.dir.end(); dit++) {
		StringVector Directories;
		Directories = GetFiles(*dit);
		for (it = Directories.begin(); it != Directories.end(); it++) {
			string dirname = *it+"/bgpdata/"+Year+"."+Month+"/UPDATES";
			if (!skDirExists(dirname.c_str())) { 
				dirname = *it+"/"+Year+"."+Month+"/";
				if (!skDirExists(dirname.c_str())) continue;
			}
			StringVector files;
			files = GetFiles(dirname,pattern);
			FileNames.insert(FileNames.end(),files.begin(), files.end());
		}
	}
	
	sort(FileNames.begin(), FileNames.end(), substrcmp);
	string meta = "meta";
	string update = "updates";
	for (std::vector<string>::iterator it = FileNames.begin() ; it != FileNames.end(); ++it)  {
		string tmp = *it;
		if (tmp.find(meta) != std::string::npos) continue;
		if (tmp.find(update) == std::string::npos) continue;
                ReadBGPFile(BGP,*it,outFile);
        }
}
