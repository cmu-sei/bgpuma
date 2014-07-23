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
		cout << "No worky \n";
		cout << date << "\n";
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
