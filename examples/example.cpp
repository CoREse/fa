/* File: example.cpp
 * Author: CRE
 * Last Edited: Wed Sep 27 17:08:04 2017
 */

#include "../fa.h"
#include <stdio.h>

int main ()
{
	fa hg38;
	try
	{
	hg38.readBases("/data/bio/fa/hg38.fa");
	}
	catch (int e)
	{
		if (e==NO_SUCH_FILE)
		{
			fprintf(stderr, "can't read that fa file!");
		}
		else if (e==LINE_TOO_LARGE)
		{
			fprintf(stderr, "the file has very large lines, are you sure it is a fa file?");
		}
	}

	return 0;
}
