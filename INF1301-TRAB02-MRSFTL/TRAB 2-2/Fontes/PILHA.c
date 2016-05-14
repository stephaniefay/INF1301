/**************************************************************
Pilha generica

Arquivo gerado:			PILHA.C

Projeto: INF1301
Autores: Stephanie, Marcos Rubio e Thiago

Hist�rico de evolu��o:
	Vers�o	Data		Observa��o
	1		09/05/2013	Inicio da codifica��o do modulo
	2		10/05/2013	Termino da codifica��o

*****************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   <stdlib.h>
#include "LISTA.h"

#define PILHA_OWN
#include "PILHA.h"
#undef PILHA_OWN

/********************************************

Tipo de dados: Ponteiro para pilha generica

********************************************/

typedef struct pilha {
	int tipo;
	void * valor;
	Pilha* prox;
} Pilha;

/******************************************

Tipo de dados: Topo da pilha

******************************************/

typedef struct ptoProTopo {
	Pilha* topo;
} PtoTopo;

/****************************************

Fun��o: Cria Topo da Pilha

******************************************/

PtoTopo * criaTopo (void) {
	PtoTopo* p = (PtoTopo*)malloc(sizeof(PtoTopo));

		if ( p == NULL)
			return NULL;
	
	p->topo = NULL;
	return p;
}

/*****************************************

Fun��o: Push na pilha

******************************************/

PLH_tpCondRet insere (PtoTopo * plh, void * a) {
	Pilha * p = (Pilha *)malloc(sizeof(Pilha));

	if (p == NULL)
		return PLH_CondRetFaltouMemoria;
	
	p->valor = a;
	p->prox = plh->topo;
	plh->topo = p;

	return PLH_CondRetOk;
}

/*****************************************

Fun��o: Pop na pilha

******************************************/

PLH_tpCondRet retira (PtoTopo * plh) {
	Pilha* p;
	void * a;

	if(vazio(plh)==1)
		return PLH_CondRetPilhaVazia;

	p = plh->topo;
	a = p->valor;
	plh->topo = p->prox;

	free(p);
	return PLH_CondRetOk;
}

/****************************************

Fun��o: Confere se a pilha esta vazia

*****************************************/

int vazio (PtoTopo * plh) {
	if (plh->topo == NULL)
		return 1;
	return 0;
}

/*****************************************

Fun��o: Libera pilha

*******************************************/

PLH_tpCondRet libera (PtoTopo* plh) {
	Pilha *p, *q;
	q = plh->topo;
	while (q!=NULL) {
		p=q->prox;
		free(q);
		q=p;
	}
	free(p);
	return PLH_CondRetOk;
}

