#include "c:/cprogrammingcourse/master/src/dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "Fileinfo.h"
#include "pch.h"



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

void add_file_and_description(char* file, char* desc, struct Fileinfo* header)
{
	strcpy(header[0].filename, file);
	strcpy(header[0].description, desc);
}



int s2p_get_data(struct Fileinfo* header, struct FreqPoint* point)
{
	FILE* fp;
	char buffer[1024];
	
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
		sscanf(buffer, "%f, %f, %f, %f, %f, %f, %f, %f, %f", &point[i].freq, &point[i].s11_mag, &point[i].s11_phase, &point[i].s22_mag, &point[i].s22_phase, &point[i].s21_mag, &point[i].s21_phase, &point[i].s12_mag, &point[i].s12_phase);
		// printf(buffer,"%e %2.6f %3.6f %2.6f %3.6f %2.6f %3.6f %2.6f %3.6f\n",point[i].freq, point[i].s11_mag, point[i].s11_phase,point[i].s12_mag, point[i].s12_phase,point[i].s21_mag, point[i].s21_phase,point[i].s22_mag, point[i].s22_phase);
	}
	
	fclose(fp);

error:
	return -1;	
}


int s2p_create_file(struct Fileinfo* header, struct FreqPoint* point)
{

	FILE* fp;
	char divider[130] = "!";
	char part_num[13];

//Populate header info into new s2p file
	strcpy(part_num, header[0].part_number);
	strcat(part_num, ".s2p");
	fp = fopen(part_num, "w");
	check(fp!=NULL, "File did not open.");
	
	for (size_t i = 0; i < 118; i++)
	{
		strcat(divider, "-");
	}
	fprintf(fp, "%s\n", divider);
	fprintf(fp, "! Sunlord Microwave (www.sunlordmicrowave.com)\n");
	fprintf(fp, "! Part Number: %s\n", header[0].part_number);
	fprintf(fp, "! Description: %s\n", header[0].description);
	fprintf(fp, "! Tested on: %s\n", header[0].equipment);
	fprintf(fp, "! Test date: %s\n", header[0].date_tested);
	fprintf(fp, "! Test temperature: %s\n", header[0].temp_tested);
	fprintf(fp, "%s\n", divider);
	fprintf(fp,"[Version] 2.0\n");
	fprintf(fp,"# GHz S DB R 50\n");
	fprintf(fp,"[Number of Ports] 2\n");
	fprintf(fp,"[Two-Port Data Order] 21_12\n");
	fprintf(fp,"[Number of Frequencies] 201\n");
	fprintf(fp,"[Network data]\n");
	fprintf(fp, "%s\n", divider);
	fprintf(fp," %10s %10s %10s %8s %10s %10s %10s %10s %10s\n", "!Freq(GHz)", "S11 Mag", "S11 Phas", "S21 Mag", "S21 Phas", "S12 Mag", "S12 Phas", "S22 Mag", "S22 Phas");

	for (int i = 0; i < 201; i++)
	{
		fprintf(fp,"%e %2.6f %3.6f %2.6f %3.6f %2.6f %3.6f %2.6f %3.6f\n",point[i].freq, point[i].s11_mag, point[i].s11_phase,point[i].s21_mag, point[i].s21_phase, point[i].s12_mag, point[i].s12_phase, point[i].s22_mag, point[i].s22_phase);
	}
	fprintf(fp,"[End]\n");

fclose(fp);

error:
	return -1;

	return 0;
}
