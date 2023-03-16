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
	void CarregarDadosIniciais(ClienteLista** ultimoCliente, MeioMobilidadeLista** ultimoMeio, GestorLista** ultimoGestor);
	
	void MostrarMenuAdicionarCliente(ClienteLista** ultimoCliente);
	void MostrarMenuEditarCliente(ClienteLista* ultimoCliente);
	void MostrarMenuRemoverCliente(ClienteLista* ultimoCliente);
	void MostrarMenuListaClientes(ClienteLista* ultimoCliente);
	
	void MostrarMenuAdicionarMeioMobilidade(MeioMobilidadeLista** ultimoMeio);
	void MostrarMenuEditarMeioMobilidade(MeioMobilidadeLista* ultimoMeio);
	void MostrarMenuRemoverMeioMobilidade(MeioMobilidadeLista* ultimoMeio);
	void MostrarMenuListaMeiosMobilidade(MeioMobilidadeLista* ultimoMeio);
	
	void MostrarMenuAdicionarGestor(GestorLista** ultimoGestor);
	void MostrarMenuEditarGestor(GestorLista* ultimoGestor);
	void MostrarMenuRemoverGestor(GestorLista* ultimoGestor);
	void MostrarMenuListaGestores(GestorLista* ultimoGestor);

#endif