/***************************************************************************
*  $MCI Módulo de implementação: VER  Vertice
*
*  Arquivo gerado:              VERTICE.c
*  Letras identificadoras:      VER
*
*  Projeto: INF 1301 Trabalho 2
*  Gestor:  DI/PUC-Rio
*  Autores: SF - Stephanie Fay
			PP - Pedro Paulo
*
*  $HA Histórico de evolução:
*     Versão  Autor      Data        Observações
*     0.5      sf&pp    3/out/2013 início desenvolvimento
*     1.0      sf&pp   10/out/2013 fim do desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "VERTICE.H"

typedef struct tpVertice {
	char * nome;
	int id;
} tpVertice;

/***************************************************************************
*
*  Função: VER  &Cria Vertice
*
****************************************************************************/

VER_tppVertice VER_CriarVertice ( int id ) {
	VER_tppVertice vertice = (VER_tppVertice) malloc (sizeof(VER_tppVertice));
	vertice->id = id;
	return vertice;
}/* Fim função: VER  &Criar vertice */

/***************************************************************************
*
*  Função: VER  &Inserir Valor
*
****************************************************************************/

VER_tpCondRet * VER_InserirValor ( VER_tppVertice vertice, char * nome ) {
	vertice->nome = nome;
	return VER_CondRetOK;
}/* Fim função: VER  &Inserir Valor */

/***************************************************************************
*
*  Função: VER  &Destruir Vertice
*
****************************************************************************/

void * VER_DestroiVertice (VER_tppVertice Vertice) {
	free (Vertice);
}/* Fim função: VER  &Destruir Vertice */

/***************************************************************************
*
*  Função: VER  &Obter Valor
*
****************************************************************************/

VER_tpCondRet * VER_ObterValor (VER_tppVertice Vertice, char * valor) {
	valor = Vertice->nome;
	return VER_CondRetOK;
}/* Fim função: VER  &Obter Valor */

/***************************************************************************
*
*  Função: VER  &Obter ID
*
****************************************************************************/

int VER_ObterID (VER_tppVertice Vertice) {
	return Vertice->id;
}/* Fim função: VER  &Obter ID */

/********** Fim do módulo de implementação: VER Vertice **********/