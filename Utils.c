/*****************************************************************//**
 * \file   Utils.c
 * \brief  "Utilis" ? uma biblioteca composta por varias fun??es utilizados v?rias vezes no decorrer de um programa em c.
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
	Esta fun?ao ? responsavel por retornar um valor (1 ou 2). Representando Confirmar ou Cancelar uma opera??o.
*/
int Confirmar()
{
	// Variaveis
	int valor = -1;

	// Mostrar condi??o de sa?da do ciclo
	puts("");
	puts("Opera??o Concluida! Deseja Confirmar?");
	puts("[1] > Confirmar | [2] > Cancelar");
	printf(" > ");

	// Garantir a escolha de uma op??o valida
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
	printf("\n   > M?s: ");
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
