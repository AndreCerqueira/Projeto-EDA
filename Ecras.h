/*****************************************************************//**
 * \file   Ecras.h
 * \brief  Cabeçalho das Funções que geram os ecrãs da aplicação
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/
#pragma once

#ifndef ECRAS_H_
#define ECRAS_H_

	 // include
	#include <locale.h>
	#include <stdio.h>
	#include "Gestor.h"
	#include "Utils.h"


	void MostrarLoginMenu();

	void MostrarMenuPrincipal(int* op);

#endif