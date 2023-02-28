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
// Armazenamento/leitura dos dados em ficheiro de texto (valores de simula��o) e bin�rios (preservar dados);
void ArmazenarDados();

void LerDados();

// Inser��o de novos dados (cliente/gestor/meio de mobilidade el�trica);
void InserirMeioMobilidade();

// Remo��o de determinados dados (cliente/gestor/meio de mobilidade el�trica);
void RemoverMeioMobilidade();

// Altera��o de determinados dados (cliente/gestor/meio de mobilidade el�trica);
void AlterarMeioMobilidade();

// Registo do aluguer de um determinado meio de mobilidade el�trica;
void RegistarAluguer();

// Listagem dos meios de mobilidade el�trica por ordem decrescente de autonomia;
void ListarMeiosMobilidadeAutonomia();

// Listagem dos meios de mobilidade el�trica existentes numa localiza��o com determinado geoc�digo.
void ListarMeiosMobilidadeLocalizacao();
 */