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

	#include <locale.h>
	#include <stdio.h>
	#include "MeioMobilidade.h"
	#include "Cliente.h"
	#include "Gestor.h"
	#include "Utils.h"


	void MostrarMenuLogin();
	void MostrarMenuPrincipal(int* op);
	void CarregarDadosIniciais(ClienteLista** ultimoCliente, MeioMobilidade** ultimoMeio, GestorLista** ultimoGestor);
	
	void MostrarMenuAdicionarCliente(ClienteLista** ultimoCliente);
	void MostrarMenuEditarCliente(ClienteLista* ultimoCliente);
	void MostrarMenuRemoverCliente(ClienteLista* ultimoCliente);
	void MostrarMenuListaClientes(ClienteLista* ultimoCliente);
	
	void MostrarMenuAdicionarMeioMobilidade(MeioMobilidade* ultimoMeio);
	void MostrarMenuEditarMeioMobilidade(MeioMobilidade* ultimoMeio);
	void MostrarMenuRemoverMeioMobilidade(MeioMobilidade* ultimoMeio);
	void MostrarMenuListaMeiosMobilidade(MeioMobilidade* ultimoMeio);
	
	void MostrarMenuAdicionarGestor(GestorLista** ultimoGestor);
	void MostrarMenuEditarGestor(GestorLista* ultimoGestor);
	void MostrarMenuRemoverGestor(GestorLista* ultimoGestor);
	void MostrarMenuListaGestores(GestorLista* ultimoGestor);

#endif