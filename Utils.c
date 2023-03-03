/*****************************************************************//**
 * \file   Utils.c
 * \brief  "Utilis" é uma biblioteca composta por varias funções utilizados várias vezes no decorrer de um programa em c.
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/


// Includes
#include "Utils.h"


char* GetFullPath(char* path)
{
	char fullPath[100];
	strcpy_s(fullPath, sizeof(fullPath), __FILE__);
	char* p = strrchr(fullPath, '\\');
	*p = '\0';
	strcat_s(fullPath, sizeof(fullPath), "\\");
	strcat_s(fullPath, sizeof(fullPath), path);
	return fullPath;
}


// GenerateUID
void GenerateUID(char* uid)
{
	const char* charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	const int charsetLen = 62;

	srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

	int i;
	for (i = 0; i < UID_LENGHT; i++) {
		uid[i] = charset[rand() % charsetLen];
	}

	// Define os caracteres de separação na posição correta do UID
	uid[8] = '-';
	uid[13] = '-';
	uid[18] = '-';
	uid[23] = '-';

	// Adiciona o caractere nulo no final da string
	uid[UID_LENGHT] = '\0';
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
	This function is responsible for returning an index from a given array, or a negative number if user wants to Cancel.
	@n = array quantity
*/
int SelectById(int n)
{
	// Variables
	int id;

	// Insert ID, and ensure that is valid
	printf("Para Voltar insira um ID negativo.\n");
	printf("Insira um ID: ");
	do
		scanf_s("%d", &id);
	while (id >= n);

	return id;
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
