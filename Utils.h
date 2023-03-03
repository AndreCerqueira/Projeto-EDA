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
	#define IS_CONFIRMED 1
	#define IS_CANCELED 2


	// Signatures
	int Confirmar();
	int SelectById(int n);
	void GetDate(char* date);
	float Percentage(int nums, int totalNum);
	float Average(int* nums, int n);

#endif
