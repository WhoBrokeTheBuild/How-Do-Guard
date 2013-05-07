
#include "functions.h"

void die( int errorLevel /* = 0 */ )
{
	system("PAUSE");
	exit(errorLevel);
}

void init_utils( void )
{
	srand((unsigned int)now());
}

int rand( int min, int max )
{
	return min + (rand() % (max - min + 1));
}

time_t now( void )
{
	return time((time_t*)0);
}

void delay( int millis )
{

}

string basename( string fullPath )
{
	int lastDir;
	bool hasSubDir = false;

	int i;
	for (i = 0; unsigned(i) < fullPath.size(); ++i)
	{
		if (fullPath[i] == '/' || fullPath[i] == '\\')
		{
			hasSubDir = true;
			lastDir = i;
		}
	}

	if (!hasSubDir) 
		return fullPath;

	int start = (lastDir + 1);
	string newBasename;

	int basenameLength = fullPath.size() - start;
	for (i = 0; i < basenameLength; ++i)
	{
		newBasename += fullPath[start];
		start++;
	}

	return newBasename;
}

float deg_to_rad( float deg )
{
	return (float)((deg * PI) / 180.0);
}

float rad_to_deg( float rad )
{
	return (float)((rad * 180.0) / PI);
}