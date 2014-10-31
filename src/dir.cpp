#include "dir.h"

int isDirectory(string pathname) 
{
	struct stat sb;

	if (stat(pathname.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		return 1;
	}
	else {
		return 0;
	}
}
