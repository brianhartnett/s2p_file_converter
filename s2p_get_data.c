
#include "c:/cprogrammingcourse/master/src/dbg.h"
#include "pch.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "Fileinfo.h"

#include "s2p_get_data.h"




#define _CRT_SECURE_NO_WARNINGS



//#define NDEBUG
char* iterate_strtok(int qty, char* buffer)
{
	char* token = strtok(buffer, ",");
	for (int i = 0; i < qty; i++)
	{
		token = strtok(NULL, ",");
	}	
return token;
}

void iterate_fgets(int qty, char* buffer, FILE* fp)
{
	for (int i = 0; i < qty; i++)
	{
		fgets(buffer, 1024, fp);
	}
}	


int s2p_get_data(struct Fileinfo* header, struct FreqPoint* point)
{
	FILE* fp;
	char buffer[1024];
	int scan_arguements = 0;
	

	fp = fopen(header[0].filename, "r");
	check(fp!=NULL, "File did not open.");



//Pull header data from csv data file and store in local variables.
	iterate_fgets(1, buffer, fp);
	strcpy(header[0].part_number,iterate_strtok(1, buffer));

//Get equipment info
	iterate_fgets(6, buffer, fp);
	strcpy(header[0].equipment,iterate_strtok(3, buffer));

//Get date tested info	
	iterate_fgets(2, buffer, fp);
	strcpy(header[0].date_tested,iterate_strtok(1, buffer));

//Get temperature of test
	iterate_fgets(2, buffer, fp);
	strcpy(header[0].temp_tested,iterate_strtok(1, buffer));

//Get freq data
	iterate_fgets(9, buffer, fp);
	for (int i = 0; i < 201; i++)
	{
		fgets(buffer, sizeof(buffer), fp);
		scan_arguements = sscanf(buffer, "%f, %f, %f, %f, %f, %f, %f, %f, %f", &point[i].freq, &point[i].s11_mag, &point[i].s11_phase, &point[i].s22_mag, &point[i].s22_phase, &point[i].s21_mag, &point[i].s21_phase, &point[i].s12_mag, &point[i].s12_phase);
		check(scan_arguements != 0, "Scan not working.");
	}
	
	fclose(fp);

error:
	return -1;	
}


