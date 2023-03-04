/*****************************************************************//**
 * \file   Utils.h
 * \brief  "Utilis" é uma biblioteca composta por varias funções utilizados várias vezes no decorrer de um programa em c.
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

#pragma once

#ifndef UTILS_H_
#define UTILS_H_

	// Includes
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <time.h>


	// Constants
	#define MAX_SIZE 1024
	#define UID_LENGHT 36
	#define IS_CONFIRMED 1
	#define IS_CANCELED 2


	// Enums
	typedef enum { false, true } bool;


	// Signatures
	void GetFullPath(const char* path, char* fullPath);
	void GenerateUID(char* uid);
	int Confirmar();
	int SelectById(int n);
	void GetDate(char* date);
	float Percentage(int nums, int totalNum);
	float Average(int* nums, int n);

#endif
