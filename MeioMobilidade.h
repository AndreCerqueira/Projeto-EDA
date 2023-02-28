#pragma once

// Constants
#define HARDDATA_FILE_NAME "MeiosMobilidade.txt"
#define SAVE_FILE_NAME "MeiosMobilidade.dat"

typedef struct {
	char tipo[20];
	char id[20];
	float carga_bateria;
	float custo_aluguer;
	char localizacao[20];
} MeioMobilidade;

/*
// Armazenamento/leitura dos dados em ficheiro de texto (valores de simulação) e binários (preservar dados);
void ArmazenarDados();

void LerDados();

// Inserção de novos dados (cliente/gestor/meio de mobilidade elétrica);
void InserirMeioMobilidade();

// Remoção de determinados dados (cliente/gestor/meio de mobilidade elétrica);
void RemoverMeioMobilidade();

// Alteração de determinados dados (cliente/gestor/meio de mobilidade elétrica);
void AlterarMeioMobilidade();

// Registo do aluguer de um determinado meio de mobilidade elétrica;
void RegistarAluguer();

// Listagem dos meios de mobilidade elétrica por ordem decrescente de autonomia;
void ListarMeiosMobilidadeAutonomia();

// Listagem dos meios de mobilidade elétrica existentes numa localização com determinado geocódigo.
void ListarMeiosMobilidadeLocalizacao();
 */