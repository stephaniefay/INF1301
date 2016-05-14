/**************************************************************
Matriz generica

Arquivo gerado:			MATRIZ.C

Projeto: INF1301
Autores: Stephanie, Marcos Rubio e Thiago

Histórico de evolução:
	Versão	Data		Observação
	1		13/05/2013	Inicio e termino da codificação do modulo

*****************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "LISTA.H"
#include   "PILHA.H"

#define MATRIZ_OWN
#include "MATRIZ.h"
#undef MATRIZ_OWN

/****************************************

Função: Cria lista matriz (tabela)

******************************************/

LIS_tppLista criarTab(int x, int y) {
	int i;

	LIS_tppLista Tab = LIS_CriarLista(0);
	if (Tab == NULL)
		return NULL;

	while ( x > 0) {
		LIS_tppLista Col = LIS_CriarLista(0);
		LIS_InserirElementoApos(Tab, Col);
		
		for (i = y; i > 0; i--) {
			PtoTopo * Pilha = criaTopo();
			LIS_InserirElementoApos(Col, Pilha);
		}
		x--;
	}
	return Tab;
}

/*********************************************************

Função: Acha coordenada e retorna a coordenada encontrada

*********************************************************/

LIS_tppLista achaCoor( LIS_tppLista Tab, int x, int y) {

	LIS_tppLista Col;

	LIS_AvancarElementoCorrente(Tab, x);
	Col = (LIS_tppLista) LIS_ObterValor(Tab);
	LIS_AvancarElementoCorrente(Col, y);

	return Col;
}

/***********************************************************

Função: Insere um valor (generico) na coordenada passada

**************************************************************/

void pushCoor(LIS_tppLista Tab, int x, int y, void * valor) {
	
	LIS_tppLista Col;
	PtoTopo* p;

	Col = achaCoor(Tab, x, y);
	p = (PtoTopo*) LIS_ObterValor(Col);
	insere(p, valor);

	IrInicioLista(Tab);
}

/*******************************************************

Função: Retira um valor (generico) de uma coordenada
Obs: Destroi o valor, não o retorna.

*********************************************************/

void popCoor(LIS_tppLista Tab, int x, int y) {
	
	LIS_tppLista Col;
	PtoTopo* p;

	Col = achaCoor(Tab, x, y);
	p = (PtoTopo*) LIS_ObterValor(Col);
	retira(p);

	IrInicioLista(Tab);
}

/*******************************************************

Função: Destrói uma dada matriz, liberando seus valores.

*********************************************************/

void DestruirMatriz ( LIS_tppLista Tab ) {
	
	LIS_tppLista Col;
	PtoTopo* p;

	while ( Tab != NULL) {
			
			IrFinalLista( Tab );
			Col = (LIS_tppLista) LIS_ObterValor( Tab );
			
		while (Col != NULL) {
				IrFinalLista( Col );
				p = (PtoTopo*) LIS_ObterValor( Col );
				libera( p );
				LIS_ExcluirElemento( Col );
				IrInicioLista( Col );			
		}

			LIS_ExcluirElemento( Tab );
			IrInicioLista( Tab );
	}		

		free ( Tab );
}