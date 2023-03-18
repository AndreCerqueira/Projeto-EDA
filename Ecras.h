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
	void CarregarDadosIniciais(ClienteLista** primeiroCliente, MeioMobilidadeLista** primeiroMeio, GestorLista** primeiroGestor);
	
	void MostrarMenuAdicionarCliente(ClienteLista** primeiroCliente);
	void MostrarMenuEditarCliente(ClienteLista* primeiroCliente);
	void MostrarMenuRemoverCliente(ClienteLista* primeiroCliente);
	void MostrarMenuListaClientes(ClienteLista* primeiroCliente);
	
	void MostrarMenuAdicionarMeioMobilidade(MeioMobilidadeLista** primeiroMeio);
	void MostrarMenuEditarMeioMobilidade(MeioMobilidadeLista* primeiroMeio);
	void MostrarMenuRemoverMeioMobilidade(MeioMobilidadeLista* primeiroMeio);
	void MostrarMenuAlugarMeioMobilidade(MeioMobilidadeLista* primeiroMeio, ClienteLista* primeiroCliente);
	void MostrarMenuListaMeiosMobilidade(MeioMobilidadeLista* primeiroMeio, ClienteLista* primeiroCliente);
	void MostrarMenuListaMeiosMobilidadePorAutonomia(MeioMobilidadeLista* primeiroMeio, ClienteLista* primeiroCliente);
	void MostrarMenuListaMeiosMobilidadeLocalizacao(MeioMobilidadeLista* primeiroMeio, ClienteLista* primeiroCliente);
	
	void MostrarMenuAdicionarGestor(GestorLista** primeiroGestor);
	void MostrarMenuEditarGestor(GestorLista* primeiroGestor);
	void MostrarMenuRemoverGestor(GestorLista* primeiroGestor);
	void MostrarMenuListaGestores(GestorLista* primeiroGestor);

#endif