#include "main.h"

int main (int argc, char* argv[])
{
	int option_index = 0;
	BGPDATA BGP;
	Initialize(BGP);
	int help = 0;
	while (1) {
                static struct option long_options[] = {
			{"verbose", no_argument, &BGP.verbose, 1},
			{"or", no_argument, &BGP.or_flag, 1},
			{"help", no_argument, &help, 1},
                        {"cidrfile",required_argument,0, 'a'},
                        {"update",required_argument,0, 'b'},
                        {"dir",required_argument,0, 'c'},
			{"startdate",required_argument,0,'d'},
			{"enddate",required_argument,0,'e'},
			{"asnfile",required_argument,0,'f'},
			{"outfile",required_argument,0,'g'},
			{"file",required_argument,0,'h'},
                        {0, 0, 0, 0}
                };
                int c = getopt_long(argc, argv, "", long_options,&option_index);
                if (c == -1) break;
                switch(c) {
			case 0:
				break;
			case 'a':
				BGP.setfile = optarg;
				break;
			case 'b':
				BGP.bgpfile.push_back(optarg);
				break;
			case 'c':
				BGP.dir.push_back(optarg);
				break;
			case 'd':
				BGP.startdate = optarg;
				break;
			case 'e':
				BGP.enddate = optarg;
				break;
			case 'f':
				BGP.asnfile = optarg;
				break;
			case 'g':
				BGP.outfile = optarg;
				break;
			case 'h':
				BGP.file = optarg;
				break;
			default :
				print_help();
				exit(1);
		}
	}
	if (help) { 
		print_help();
		exit(1);
	}

	std::ofstream myFile;

	if(!BGP.outfile.empty()) {
		myFile.open(BGP.outfile.c_str(), std::ios::out);
	}

	std::ofstream &outFile = (BGP.outfile.empty() ? (std::ofstream&)cout : myFile);

	if (!BGP.setfile.empty()) {
		skipset_t *ipset = NULL;
		ReadFile(BGP.setfile,&ipset);
		BGP.ipset = ipset;
	}
	if (!BGP.asnfile.empty()) {
		ReadASNFile(BGP);
	}
	if (BGP.bgpfile.size() > 0) {
		vector<string>::iterator it;
		for (it = BGP.bgpfile.begin(); it != BGP.bgpfile.end(); it++) {
			ReadBGPFile(BGP,*it,outFile);
		}
		if (!BGP.outfile.empty()) {
			outFile.close();
		}
		exit(1);
	}
	if (!BGP.file.empty()) {
		ProcessFiles(BGP,outFile);
		exit(1);
	}
	if (BGP.startdate.empty() || BGP.enddate.empty() || BGP.dir.empty()) {
		print_help();
		exit(1);
	}
	Traverse(BGP,BGP.startdate,outFile);
	if (BGP.enddate.compare(BGP.startdate) == 0) { exit(1); }
	string nextdate = NextDate(BGP.startdate);
	while (nextdate.compare(BGP.enddate) != 0) {
		Traverse(BGP,nextdate,outFile);
		nextdate = NextDate(nextdate);
	}
	Traverse(BGP,BGP.enddate,outFile);
	if (!BGP.outfile.empty()) {
		outFile.close();
	}

}

void print_help()
{
	cout << "Usage: \n";
	cout << "--verbose           Prints extra output\n";
	cout << "--cidrfile=FILE     File containing the CIDR blocks to look for\n";
	cout << "--asnfile=FILE      File containing the Autonomous System Numbers to look for\n";
	cout << "--or                By default, if both --cidrfile and --asnfile are given, \n                    bgpuma looks for matches that satisfy both lists. \n                    This flag turns that match into an or.\n";
	cout << "--update=FILE       The BGP Update file that is searched\n";
	cout << "--startdate=YYYYMMDD\n";
	cout << "--enddate=YYYYMMDD  The startdate and enddate flags go together.\n                    This gives a date range to search the BGP Update files.\n                    See the README for more information about the required \n                    directory stucture\n";
	cout << "--dir=DIR           The directory containing the Update files used in the date\n                    range examination\n";
	cout << "--outfile=FILE      The output file for the results.  By default\n                    it goes to standard out.\n";
	cout << "--file=FILE         A file containing a list of files to search in\n";
}
