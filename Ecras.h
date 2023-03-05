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

	#include <locale.h>
	#include <stdio.h>
	#include "MeioMobilidade.h"
	#include "Cliente.h"
	#include "Gestor.h"
	#include "Utils.h"


	void MostrarMenuLogin();
	void MostrarMenuPrincipal(int* op);
	void CarregarDadosIniciais(Cliente* ultimoCliente, MeioMobilidade* ultimoMeio, Gestor* ultimoGestor);
	
	void MostrarMenuAdicionarCliente(Cliente** ultimoCliente);
	void MostrarMenuEditarCliente(Cliente* ultimoCliente);
	void MostrarMenuRemoverCliente(Cliente* ultimoCliente);
	void MostrarMenuListaClientes(Cliente* ultimoCliente);
	
	void MostrarMenuAdicionarMeioMobilidade(MeioMobilidade** ultimoMeio);
	void MostrarMenuEditarMeioMobilidade(MeioMobilidade* ultimoMeio);
	void MostrarMenuRemoverMeioMobilidade(MeioMobilidade* ultimoMeio);
	void MostrarMenuListaMeiosMobilidade(MeioMobilidade* ultimoMeio);
	
	void MostrarMenuAdicionarGestor(Gestor** ultimoGestor);
	void MostrarMenuEditarGestor(Gestor* ultimoGestor);
	void MostrarMenuRemoverGestor(Gestor* ultimoGestor);
	void MostrarMenuListaGestores(Gestor* ultimoGestor);

#endif