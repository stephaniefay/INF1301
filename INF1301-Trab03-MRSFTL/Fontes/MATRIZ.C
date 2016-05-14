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

#define MATRIZ_OWN
#include	"LISTA.H"
#include	"PILHA.H"
#include	"MATRIZ.H"
#undef MATRIZ_OWN

/****************************************

Função: Cria lista matriz (tabela)

******************************************/

LIS_tppLista MTZ_criarTab(int x, int y) {
	int i,j;
	PLH_tppPilha Pilha;
	LIS_tppLista Elem;
	LIS_tppLista Col;

	LIS_tppLista Tab = LIS_CriarLista(0);
		/*Cria lista*/

	if (Tab == NULL)
		return NULL;
		/*if NULL*/

	for (i = 0; i < x; i++) {
		Col = LIS_CriarLista(0);
		LIS_InserirElementoApos(Tab, Col);			
		
		for (j = 0; j < y; j++) {
			Pilha = PLH_CriarTopo();
			LIS_InserirElementoApos(Col, Pilha);
		}
	}
		/* Cria toda a matriz de pilhas */

	IrInicioLista(Tab);
	return Tab;
}

/*********************************************************

Função: Acha coordenada e retorna a coordenada encontrada

*********************************************************/

LIS_tppLista MTZ_achaCoor(LIS_tppLista Tab, int x, int y) {

	LIS_tppLista coor;// = LIS_CriarLista(0);/* Armazena copia da coluna*/

	LIS_AvancarElementoCorrente(Tab, x);
	coor = (LIS_tppLista) LIS_ObterValor(Tab);
	IrInicioLista(coor);
	LIS_AvancarElementoCorrente(coor, y);

	IrInicioLista(Tab);

	return coor;
}

/***********************************************************

Função: Insere um valor (generico) na coordenada passada

**************************************************************/

MTZ_tpCondRet MTZ_pushCoor ( LIS_tppLista Tab, int x, int y, char valor ) {

	PLH_tppPilha p;// = PLH_CriarTopo(); // ISSO PRECISA SER DESTRUIDO DPS
	LIS_tppLista Col;// = LIS_CriarLista(NULL); // ISSO PRECISA SER DESTRUIDO DPS

	Col = MTZ_achaCoor(Tab, x, y);
	
	p = (PLH_tppPilha) LIS_ObterValor(Col);
	PLH_Insere(p, valor);

	IrInicioLista(Col);
	IrInicioLista(Tab);

	return MTZ_CondRetOK ;
}

/*******************************************************

Função: Retira um valor (generico) de uma coordenada

*********************************************************/

char MTZ_popCoor ( LIS_tppLista Tab, int x, int y ) {
	
	PLH_tppPilha p;// = PLH_CriarTopo(); // ISSO PRECISA SER DESTRUIDO DPS
	LIS_tppLista Col;// = LIS_CriarLista(NULL); // ISSO PRECISA SER DESTRUIDO DPS
	char * valor = (char *) malloc (sizeof(char));

	Col = MTZ_achaCoor(Tab, x, y);

	p = (PLH_tppPilha) LIS_ObterValor(Col);
	valor = PLH_Retira(p);

	if (valor == NULL)
		return MTZ_CondRetVazia;

	IrInicioLista(Tab);

	return *valor ;
}

/*******************************************************

Função: Destrói uma dada matriz, liberando seus valores.

*********************************************************/

MTZ_tpCondRet MTZ_DestruirMatriz ( LIS_tppLista Tab )
{
	
	LIS_tppLista Col;
	PLH_tppPilha p;

	while ( Tab != NULL) {
			
			IrFinalLista( Tab );
			Col = (LIS_tppLista) LIS_ObterValor( Tab );
			
		while (Col != NULL) {
				IrFinalLista( Col );
				p = (PLH_tppPilha) LIS_ObterValor( Col );
				PLH_Libera( p );
				LIS_ExcluirElemento( Col );
				IrInicioLista( Col );			
		}

			LIS_ExcluirElemento( Tab );
			IrInicioLista( Tab );
	}		

		free ( Tab );

		return MTZ_CondRetOK;
}