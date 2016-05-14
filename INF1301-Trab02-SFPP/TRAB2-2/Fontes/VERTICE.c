/***************************************************************************
*  $MCI M�dulo de implementa��o: VER  Vertice
*
*  Arquivo gerado:              VERTICE.c
*  Letras identificadoras:      VER
*
*  Projeto: INF 1301 Trabalho 2
*  Gestor:  DI/PUC-Rio
*  Autores: SF - Stephanie Fay
			PP - Pedro Paulo
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor      Data        Observa��es
*     0.5      sf&pp    3/out/2013 in�cio desenvolvimento
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
*  Fun��o: VER  &Cria Vertice
*
****************************************************************************/

VER_tppVertice VER_CriarVertice ( int id ) {
	VER_tppVertice vertice = (VER_tppVertice) malloc (sizeof(VER_tppVertice));
	vertice->id = id;
	return vertice;
}/* Fim fun��o: VER  &Criar vertice */

/***************************************************************************
*
*  Fun��o: VER  &Inserir Valor
*
****************************************************************************/

VER_tpCondRet * VER_InserirValor ( VER_tppVertice vertice, char * nome ) {
	vertice->nome = nome;
	return VER_CondRetOK;
}/* Fim fun��o: VER  &Inserir Valor */

/***************************************************************************
*
*  Fun��o: VER  &Destruir Vertice
*
****************************************************************************/

void * VER_DestroiVertice (VER_tppVertice Vertice) {
	free (Vertice);
}/* Fim fun��o: VER  &Destruir Vertice */

/***************************************************************************
*
*  Fun��o: VER  &Obter Valor
*
****************************************************************************/

VER_tpCondRet * VER_ObterValor (VER_tppVertice Vertice, char * valor) {
	valor = Vertice->nome;
	return VER_CondRetOK;
}/* Fim fun��o: VER  &Obter Valor */

/***************************************************************************
*
*  Fun��o: VER  &Obter ID
*
****************************************************************************/

int VER_ObterID (VER_tppVertice Vertice) {
	return Vertice->id;
}/* Fim fun��o: VER  &Obter ID */

/********** Fim do m�dulo de implementa��o: VER Vertice **********/