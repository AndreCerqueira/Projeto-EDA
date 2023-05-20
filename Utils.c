/*****************************************************************//**
 * \file   Utils.c
 * \brief  "Utilis" é uma biblioteca composta por varias funções utilizados várias vezes no decorrer de um programa em c.
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/


// Includes
#include "Utils.h"


#define MAX_PATH_LENGTH 100
#pragma warning(disable : 4996)
void GetFullPath(const char* path, char* fullPath)
{
	strcpy(fullPath, __FILE__);
	char* p = strrchr(fullPath, '\\');
	*p = '\0';
	strcat(fullPath, "\\");
	strcat(fullPath, path);
}


/*
	Esta funçao é responsavel por retornar um valor (1 ou 2). Representando Confirmar ou Cancelar uma operação.
*/
int Confirmar()
{
	// Variaveis
	int valor = -1;

	// Mostrar condição de saída do ciclo
	puts("");
	puts("Operação Concluida! Deseja Confirmar?");
	puts("[1] > Confirmar | [2] > Cancelar");
	printf(" > ");

	// Garantir a escolha de uma opção valida
	while (valor != 1 && valor != 2)
		scanf_s("%d", &valor);

	return valor;
}


/*
	This procedure is responsible for returning a date by pointer. Having to insert the Day, Month and Year.
	@date = date text to be returned
*/
void GetDate(char* date)
{
	// Variables
	int day, month, year;

	// Insert Date
	printf("Insira a data:");
	printf("\n   > Dia: ");
	scanf_s("%d", &day);
	printf("\n   > Mês: ");
	scanf_s("%d", &month);
	printf("\n   > Ano: ");
	scanf_s("%d", &year);

	// Convert to time_t struct
	struct tm timeinfo = { 0 };
	timeinfo.tm_year = year - 1900;  // Year is number of years since 1900
	timeinfo.tm_mon = month - 1;     // Month is 0-based index
	timeinfo.tm_mday = day;

	// Format date string
	strftime(date, 11, "%d/%m/%Y", &timeinfo);
}

// read a data char* 2021-04-08T00:00:00Z by parameter and return by reference the year, month and day, and hour, minute and second
void GetDateAndTime(char* date, int* year, int* month, int* day, int* hour, int* minute, int* second)
{
	// Variables
	char* token;
	char* next_token;
	char* dateCopy = (char*)malloc(strlen(date) + 1);
	strcpy(dateCopy, date);

	// Get year
	token = strtok_s(dateCopy, "-", &next_token);
	*year = atoi(token);

	// Get month
	token = strtok_s(NULL, "-", &next_token);
	*month = atoi(token);

	// Get day
	token = strtok_s(NULL, "T", &next_token);
	*day = atoi(token);

	// Get hour
	token = strtok_s(NULL, ":", &next_token);
	*hour = atoi(token);

	// Get minute
	token = strtok_s(NULL, ":", &next_token);
	*minute = atoi(token);

	// Get second
	token = strtok_s(NULL, "Z", &next_token);
	*second = atoi(token);

	// Free memory
	free(dateCopy);
}


// check witch date "2021-04-08T00:00:00Z" between two is the most recent
int CompareDate(char* date1, char* date2)
{
	// Variables
	int year1, month1, day1, hour1, minute1, second1;
	int year2, month2, day2, hour2, minute2, second2;

	// Get date and time
	GetDateAndTime(date1, &year1, &month1, &day1, &hour1, &minute1, &second1);
	GetDateAndTime(date2, &year2, &month2, &day2, &hour2, &minute2, &second2);

	// Compare year
	if (year1 > year2)
		return 1;
	else if (year1 < year2)
		return 2;

	// Compare month
	if (month1 > month2)
		return 1;
	else if (month1 < month2)
		return 2;

	// Compare day
	if (day1 > day2)
		return 1;
	else if (day1 < day2)
		return 2;

	// Compare hour
	if (hour1 > hour2)
		return 1;
	else if (hour1 < hour2)
		return 2;

	// Compare minute
	if (minute1 > minute2)
		return 1;
	else if (minute1 < minute2)
		return 2;

	// Compare second
	if (second1 > second2)
		return 1;
	else if (second1 < second2)
		return 2;

	// Return 0 if equal
	return 0;
}


// get current date like "2021-04-08T00:00:00Z"
void GetCurrentDate(char* date)
{
	// Variables
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	// Format date string
	sprintf(date, "%d-%02d-%02dT%02d:%02d:%02dZ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}


/*
	Function to calculate the positive cases average returning the percentage
	@nums = number of elements counted
	@n = total number of elements
*/
float Percentage(int nums, int n)
{
	// Variables
	float result;

	// Calculate percentage
	result = (nums * 100) / (float)n;

	// Return result
	return result;
}


/*
	Function to calculate a average based on the result of questions returing the average
	@nums = list with integer numbers
	@totalNum = quantity of numbers
*/
float Average(int* nums, int n)
{
	// Variables
	int i, sum = 0;
	float result;

	for (i = 0; i < n; i++)
	{
		sum += nums[i];
	}

	// Calculate the average
	result = sum / (float)n;

	// Return the average
	return result;
}
