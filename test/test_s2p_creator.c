
#include "Fileinfo.h"
#include "s2p_creator.h"
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


void iterate_fgets_local(int qty, char* buffer, FILE* fp)
{
	for (int i = 0; i < qty; i++)
	{
		fgets(buffer, 1024, fp);
	}
}

 int main(void) {

    FILE* fp;
    struct Fileinfo header[1];
    struct FreqPoint point[202];
    struct FreqPoint test_point[4];
    char buffer[1024];
	char filename[20] = "./test.csv";
	char description[80] = "desc";
    int num = 0;
    bool test_result = true;
    char* token;

    //Add selected file name & inputted description to struct header.
    strcpy(header[0].filename, filename);
	strcpy(header[0].description, description);

    //Test add_file_and_description function is working OK
    if(!strcmp(header[0].description,description) && !strcmp(header[0].filename,filename)){
        printf("add_file_and_description function works OK.\n");
    }

    //Pull data from source file
    s2p_get_data(header, point);

    //Test s2p_get_data function is working OK
    if(!strcmp(header[0].part_number,"DVRF00242") && !strcmp(header[0].equipment,"E5071C") && !strcmp(header[0].date_tested,"6/22/2022")&& !strcmp(header[0].temp_tested,"-40C")){
        printf("s2p_get_data function for header info works OK.\n");
    }

    //Test pulling data is working OK
    srand (time(NULL)); //Seed rand function
    fp = fopen(header[0].filename, "r");
	for (int i = 0; i < 3; i++)
	{
		int random_num = rand() % 40 + 21; //random numbers between 21 and 60
        num = num + random_num;
		iterate_fgets_local(random_num, buffer, fp);
        sscanf(buffer, "%f, %f, %f, %f, %f, %f, %f, %f, %f", &test_point[i].freq, &test_point[i].s11_mag, &test_point[i].s11_phase, &test_point[i].s22_mag, &test_point[i].s22_phase, &test_point[i].s21_mag, &test_point[i].s21_phase, &test_point[i].s12_mag, &test_point[i].s12_phase);
		// printf("i is %d, Freq is %f, s11 mag is %f\n", i,test_point[i].freq,test_point[i].s11_mag);
        // printf("counter is %d, Freq is %f, s11 mag is %f\n", num, point[num-21].freq,point[num-21].s11_mag);
        if(test_point[i].freq != point[num-21].freq || test_point[i].s11_mag != point[num-21].s11_mag || test_point[i].s22_phase != point[num-21].s22_phase)
        {
            printf("Data does not match!\n");
            test_result = false;
        }
	} 
    if(test_result==true)
    {
        printf("s2p_get_data function data point transfer from original to struct works OK.\n");
    }

    fclose(fp);

    s2p_create_file(header, point);

    //Test s2p_create_file function is working OK
    fp = fopen("DVRF00242.s2p", "r");

    //Check part number in s2p file is correct
    iterate_fgets_local(3, buffer, fp);
    token = strtok(buffer, ":");
    token = strtok(NULL, " ");
    if(strncmp(token,"DVRF00242",9) != 0)
    {
        printf("Part number does not match.\n");
    }

    //Check description in s2p file is correct
    iterate_fgets_local(1, buffer, fp);
    token = strtok(buffer, ":");
    token = strtok(NULL, " ");
    if(strncmp(token,"desc",4) != 0)
    {
        printf("Description does not match.\n");
    }

    //Check equipment in s2p file is correct
    iterate_fgets_local(1, buffer, fp);
    token = strtok(buffer, ":");
    token = strtok(NULL, " ");
    if(strncmp(token,"E5071C",6) != 0)
    {
        printf("Equipment does not match.\n");
    }

    //Check date in s2p file is correct
    iterate_fgets_local(1, buffer, fp);
    token = strtok(buffer, ":");
    token = strtok(NULL, " ");
    if(strncmp(token,"6/22/2022",9) != 0)
    {
        printf("Date does not match.\n");
    }

    //Check temp in s2p file is correct
    iterate_fgets_local(1, buffer, fp);
    token = strtok(buffer, ":");
    token = strtok(NULL, " ");
    if(strncmp(token,"-40C",4) != 0)
    {
        printf("Temp does not match.\n");
    }

    //Check data is correct
    iterate_fgets_local(10, buffer, fp);
    srand (time(NULL)); //Seed rand function
    test_result=true;
    num = 0;
	for (int i = 0; i < 3; i++)
	{
		int random_num = rand() % 39+1; //random numbers between 1 and 40
        num = num + random_num;
		iterate_fgets_local(random_num, buffer, fp);
        sscanf(buffer, "%f %f %f %f %f %f %f %f %f", &test_point[i].freq, &test_point[i].s11_mag, &test_point[i].s11_phase,&test_point[i].s21_mag, &test_point[i].s21_phase, &test_point[i].s12_mag, &test_point[i].s12_phase, &test_point[i].s22_mag, &test_point[i].s22_phase);
        // printf("Checked line %d\n", num);
        // printf("original:%e %2.6f %3.6f %2.6f %3.6f %2.6f %3.6f %2.6f %3.6f\n",point[num].freq, point[num].s11_mag, point[num].s11_phase,point[num].s21_mag, point[num].s21_phase, point[num].s12_mag, point[num].s12_phase, point[num].s22_mag, point[num].s22_phase);
        // printf("new read:%e %2.6f %3.6f %2.6f %3.6f %2.6f %3.6f %2.6f %3.6f\n",test_point[i].freq, test_point[i].s11_mag, test_point[i].s11_phase,test_point[i].s21_mag, test_point[i].s21_phase, test_point[i].s12_mag, test_point[i].s12_phase, test_point[i].s22_mag, test_point[i].s22_phase);
        
        if(test_point[i].freq != point[num].freq)
        {
            printf("Freq Data does not match!\n");
            test_result = false;
        }
            if(test_point[i].s11_mag != point[num].s11_mag)
        {
            printf("S11 Mag Data does not match!\n");
            // printf("Original: %f\n",point[num].s11_mag);
            // printf("New read: %f\n",test_point[i].s11_mag);
            test_result = false;
        }
            if(round(100000*test_point[i].s22_phase) != round(100000*point[num].s22_phase))
        {
            printf("S22 Phase Data does not match!\n");
            // printf("Original: %5.9f\n",round(100000*point[num].s22_phase));
            // printf("New read: %5.9f\n",round(100000*test_point[i].s22_phase));
            test_result = false;
        }
	} 
    if(test_result==true)
    {
        printf("s2p_create_file function data transfer from struct to s2p file works OK.\n");
    }

    fclose(fp);

    
 }


    

