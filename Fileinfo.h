#pragma once

typedef struct Fileinfo {
	char filename[80];
	char description[80];
	char part_number[20];
	char equipment[50];
	char date_tested[20];
	char temp_tested[10];
} Fileinfo;

typedef struct FreqPoint {
	float freq;
	float s11_mag;
	float s11_phase;
	float s21_mag;
	float s21_phase;
	float s12_mag;
	float s12_phase;
	float s22_mag;
	float s22_phase;
} FreqPoint;
