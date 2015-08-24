/*
Copyright 2015 Carnegie Mellon University

This material is based upon work funded and supported by Department of Homeland Security under Contract No. FA8721-05-C-0003 with Carnegie Mellon University for the operation of the Software Engineering Institute, a federally funded research and development center sponsored by the United States Department of Defense.

Any opinions, findings and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of Department of Homeland Security or the United States Department of Defense.

NO WARRANTY. THIS CARNEGIE MELLON UNIVERSITY AND SOFTWARE ENGINEERING INSTITUTE MATERIAL IS FURNISHED ON AN AS-IS BASIS. CARNEGIE MELLON UNIVERSITY MAKES NO WARRANTIES OF ANY KIND, EITHER EXPRESSED OR IMPLIED, AS TO ANY MATTER INCLUDING, BUT NOT LIMITED TO, WARRANTY OF FITNESS FOR PURPOSE OR MERCHANTABILITY, EXCLUSIVITY, OR RESULTS OBTAINED FROM USE OF THE MATERIAL. CARNEGIE MELLON UNIVERSITY DOES NOT MAKE ANY WARRANTY OF ANY KIND WITH RESPECT TO FREEDOM FROM PATENT, TRADEMARK, OR COPYRIGHT INFRINGEMENT.

This material has been approved for public release and unlimited distribution.

CERT® is a registered mark of Carnegie Mellon University.
*/
#include "dates.h"

string NextDate( string date ) 
{
	string time = " 00:00:01";
	string datetime = date+time;
	struct tm tm;
	time_t epoch;
	if ( strptime(datetime.c_str(), "%Y%m%d %H:%M:%S", &tm) != NULL ) {
		epoch = mktime(&tm);
	}
	else  {
		cout << "Can not parse:  " << date << "\n";
		exit(-1);
	}

	epoch += 86401;
	struct tm *nextday;
	nextday  = localtime(&epoch);
	char buffer[16];
	strftime(buffer, 16, "%Y%m%d", nextday);
	string tmp = buffer;
	return tmp.substr(0, 8);
}

string getYear( string date)
{
	return date.substr(0,4);
}

string getMonth( string date)
{
	return date.substr(4,2);
}
