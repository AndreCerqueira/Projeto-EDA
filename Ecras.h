/*****************************************************************//**
 * \file   Ecras.h
 * \brief  Cabe�alho das Fun��es que geram os ecr�s da aplica��o
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
	#include "MeioMobilidade.h"
	#include "Cliente.h"
	#include "Gestor.h"
	#include "Utils.h"


	void MostrarMenuLogin();
	void MostrarMenuPrincipal(int* op);
	
	void MostrarMenuAdicionarCliente();
	void MostrarMenuEditarCliente();
	void MostrarMenuRemoverCliente();
	void MostrarMenuListaClientes(Cliente* clientes);
	
	void MostrarMenuAdicionarMeioMobilidade();
	void MostrarMenuEditarMeioMobilidade();
	void MostrarMenuRemoverMeioMobilidade();
	void MostrarMenuListaMeiosMobilidade();
	
	void MostrarMenuAdicionarGestor();
	void MostrarMenuEditarGestor();
	void MostrarMenuRemoverGestor();
	void MostrarMenuListaGestores();

#endif