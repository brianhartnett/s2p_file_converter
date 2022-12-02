#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

using namespace std;


int create_s2p_file()
{
	FILE* fp;
	char buffer[1024];
	char part_number[20];
	char* token;
	char divider[130] = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

	
	//fp = fopen("test.csv", "r");
	//if (fp==NULL)
	//{
	//	return -1;
	//}

	////Pull header data from csv data file and store in local variables.
	//fgets(buffer, sizeof(buffer), fp);
	//token = strtok(buffer, ",");
	//token = strtok(NULL, ",");
	//strcpy(part_number, token);
	//fclose(fp);

	//Populate header info into new s2p file
	fp = fopen("DVRF00232.s2p", "w");
	//if (fp==NULL)
	//{
	//	return -1;
	//}
	fprintf(fp, "%s\n", divider);
	fclose(fp);

	return 0;
}