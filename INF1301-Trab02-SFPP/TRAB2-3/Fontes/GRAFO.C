/***************************************************************************
*  $MCI Módulo de implementação: GRA  Grafo
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRA
*
*  Projeto: INF 1301 Trabalho 2
*  Gestor:  DI/PUC-Rio
*  Autores: SF - Stephanie Fay
			PP - Pedro Paulo
*
*  $HA Histórico de evolução:
*     Versão  Autor      Data        Observações
*     0.5      sf&pp   10/out/2013 início desenvolvimento
*     1.0      sf&pp   18/out/2013 fim do desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "lista.h"
#include   "GENERICO.H"
#include   "VERTICE.H"

#define GRAFO_OWN
#include "GRAFO.H"
#undef GRAFO_OWN



typedef struct GRA_ElemGrafo {

	VER_tppVertice conteudo;
	LIS_tppLista sucessor;
	LIS_tppLista antecessor;

} GRA_pGrafo;

   typedef struct GRA_tagGrafo {

		 LIS_tppLista pListaOrigens;
			   /* Ponteiro para Origens do Grafo */
		  
         LIS_tppLista pListaVert ;
               /* Ponteiro para a cabeca da lista de vertices */

         GRA_tppElemento corrente;
               /* Ponteiro para a cabeca do vertice corrente */
		 
		 int id;
			  /* int de identificação do Grafo */

   } GRA_tpGrafo ;

/***** Protótipos das funções encapuladas no módulo *****/


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRA  &Criar grafo
*
****************************************************************************/

   GRA_tpCondRet GRA_criarGrafo ( GRA_tppGrafo parmGrafo )
   {
      GRA_tppGrafo pGrafo = NULL ;

      
      /* teste de parametros de entrada */
      if ( parmGrafo == NULL )
      {
         return GRA_CondRetParamInvalido ;
      } /* if */

      /* aloca dinamicamente a cabeca do grafo */
      pGrafo = ( GRA_tppGrafo ) malloc( sizeof( GRA_tppGrafo )) ;
      if ( pGrafo == NULL )
      {
         return GRA_CondRetFaltouMemoria ;
      } /* if */

      /* criacao da lista de vertices */
      pGrafo->pListaVert = LIS_CriarLista( NULL ) ;
      if( pGrafo->pListaVert == NULL )
      {
         return GRA_CondRetFaltouMemoria ;
      } /* if */

      /* nao existe vertice corrente */
	  pGrafo->corrente->conteudo = NULL ;

      
      /* caso esse ponteiro ja aponte para um grafo, destrua-o */
      if( parmGrafo != NULL )
      {
         GRA_destruirGrafo( parmGrafo ) ;
      }

      /* ponteiro passa a apontar para novo grafo */
      parmGrafo = pGrafo ;

      /* funcao executou corretamente */
      return GRA_CondRetOK ;

   } /* Fim função: GRA  &Criar grafo */

/***************************************************************************
*
*  Função: GRA  &Ir vertice
*
****************************************************************************/

 GRA_tpCondRet GRA_irVertice ( GRA_tppGrafo parmGrafo , int id ) {
	 GRA_tppGrafo Grafo = parmGrafo ;
	 LIS_tpCondRet retornoObtido ;
	 /* teste de parametros de entrada */
	 if( parmGrafo == NULL ) { 
		 return GRA_CondRetGrafoNaoExiste ;
	 } /* if */

	 /* verificacao da existencia de um vertice corrente */
	 if( parmGrafo->corrente == NULL ) {
		 return GRA_CondRetVerticeCorrNaoExiste ;
	 } /* if */
	 
	 /* procura vertice na lista de vertices */ 
	 IrInicioLista( Grafo->pListaVert ) ; 
	 while ( Grafo->pListaVert != NULL ) {
		 LIS_ObterValor(Grafo->pListaVert);
		 if (VER_ObterID (Grafo->corrente->conteudo) == id) {
			 retornoObtido = LIS_CondRetOK ;
			 break;
		 } 
		 LIS_AvancarElementoCorrente (Grafo->pListaVert, 1);
	 }

	 /* caso nao encontre, nao ha como ir para o vertice requisitado */ 
	 if( retornoObtido != LIS_CondRetOK ) { 
		 return GRA_CondRetArestaNaoExiste ;
	 } /* if */
	 
	 /* caso contrario, pega o ponteiro do vertice e diz que eh o corrente */ 
	 parmGrafo->corrente = (GRA_pGrafo*) LIS_ObterValor (Grafo->pListaVert) ;
	 
	 /* funcao executou corretamente */
	 return GRA_CondRetOK ;

} /* Fim função: GRA &Ir vertice */

/***************************************************************************
*
*  Função: GRA  &Criar vertice
*
****************************************************************************/

   GRA_tpCondRet GRA_criaVertice ( GRA_tppGrafo parmGrafo , char * parmValor, int id )
   {
	   int CondRet;
	   GRA_tppElemento Elemento = (GRA_pGrafo*)malloc(sizeof(GRA_pGrafo));
	   /* insere a string no elemento criado */
	   VER_tppVertice Vertice = VER_CriarVertice ( id );
	   VER_InserirValor (Vertice, parmValor);
	   
	   Elemento->conteudo = Vertice;
	   /* inicializa a lista de sucessores e antecessores do vertice */
	   Elemento->sucessor = LIS_CriarLista (NULL);
	   Elemento->antecessor = LIS_CriarLista (NULL);
	   IrFinalLista (parmGrafo->pListaVert);
	   CondRet = LIS_InserirElementoApos( parmGrafo->pListaVert, Elemento);
	   /* se nao conseguir inserir elemento  */
      if (CondRet != LIS_CondRetOK)
		  return GRA_CondRetFaltouMemoria;
	  /* vertice criado com sucesso */
	  return GRA_CondRetOK;
   }
   /* Fim função: GRA  &Criar vertice */

/***************************************************************************
*
*  Função: GRA  &Destruir vertice corrente
*
****************************************************************************/

   GRA_tpCondRet GRA_destruirVertice ( GRA_tppGrafo parmGrafo )
   {
	int CondRet;
	GRA_tppElemento Elemento = parmGrafo->corrente;
	/* testa o parametro de entrada */
	if ( parmGrafo == NULL )
		return GRA_CondRetGrafoNaoExiste ;
	
	CondRet = LIS_ProcurarValor (Elemento->sucessor, Elemento);
	if ( CondRet != GRA_CondRetOK )
		return GRA_CondRetNaoAchou;
   	LIS_ExcluirElemento (parmGrafo->corrente->sucessor);
	LIS_DestruirLista (Elemento->sucessor);
	free (Elemento->sucessor);

	CondRet = LIS_ProcurarValor (parmGrafo->corrente->antecessor, parmGrafo->corrente);
	if ( CondRet != GRA_CondRetOK )
		return GRA_CondRetNaoAchou;
   	LIS_ExcluirElemento (parmGrafo->corrente->antecessor);
	LIS_DestruirLista (parmGrafo->corrente->antecessor);
	free (parmGrafo->corrente->antecessor);
	free (parmGrafo->corrente->conteudo);

	GRA_IrOrigem ( parmGrafo, NULL );
	
	return GRA_CondRetOK;

   } /* Fim função: GRA  &Destruir vertice corrente */

/***************************************************************************
*
*  Função: GRA  &Ir para Origem do Grafo
*
****************************************************************************/

GRA_tpCondRet GRA_IrOrigem ( GRA_tppGrafo Grafo, int verificador ) {
	
	if (verificador == NULL)
		Grafo->corrente = (GRA_pGrafo*)LIS_ObterValor(Grafo->pListaOrigens);

	IrInicioLista (Grafo->pListaOrigens);
	LIS_AvancarElementoCorrente (Grafo->pListaOrigens, verificador);
	Grafo->corrente = (GRA_pGrafo*)LIS_ObterValor (Grafo->pListaOrigens);
	
	return GRA_CondRetOK;
} /*Fim da função: GRA &Ir para Origem do Grafo */

/***************************************************************************
*
*  Função: GRA  &Destruir aresta
*
****************************************************************************/

GRA_tpCondRet GRA_destruirAresta ( GRA_tppGrafo Grafo, int antecessor, int sucessor ) {

	GRA_tppElemento verticeSucessor;
	GRA_tppElemento verticeAntecessor;
	int CondRet = NULL;
	int contador = 1;

	while (CondRet != GRA_CondRetNaoAchou) {
		CondRet = GRA_AvancaElemCorrente (Grafo, contador);
		if (VER_ObterID (Grafo->corrente->conteudo) == sucessor) {
			verticeSucessor = Grafo->corrente;
			break;
		}
		contador++;
	}

	if (CondRet == GRA_CondRetNaoAchou)
		return GRA_CondRetParamInvalido;

	CondRet = NULL;
	contador = 1;

	while (CondRet != GRA_CondRetNaoAchou) {
		CondRet = GRA_AvancaElemCorrente (Grafo, contador);
		if (VER_ObterID (Grafo->corrente->conteudo) == antecessor) {
			verticeAntecessor = Grafo->corrente;
			break;
		}
		contador++;
	}

	if (CondRet == GRA_CondRetNaoAchou)
		return GRA_CondRetParamInvalido;

	LIS_ProcurarValor (verticeAntecessor->sucessor, verticeSucessor);
	LIS_ExcluirElemento (verticeAntecessor->sucessor);
	LIS_ProcurarValor (verticeSucessor->antecessor, verticeAntecessor);
	LIS_ExcluirElemento (verticeSucessor->antecessor);

	return GRA_CondRetOK;

} /* Fim função: GRA &Destruir aresta */

/***************************************************************************
*
*  Função: GRA  &Criar aresta
*
****************************************************************************/

   GRA_tpCondRet GRA_criarAresta ( GRA_tppGrafo Grafo , int id, char * tipo ) { 
	   GRA_tppGrafo Grafoparm = Grafo;
	   /* testa parametros de entrada */
	   if ( Grafo == NULL ) 
		   return GRA_CondRetGrafoNaoExiste;

	   if ( strcmp (tipo, "sucessor") == 0 ){
		   GRA_irVertice (Grafoparm, id);
		   LIS_InserirElementoApos (Grafo->corrente->sucessor, Grafoparm->corrente);
		   LIS_InserirElementoApos (Grafo->corrente->antecessor, Grafo->corrente);
		   return GRA_CondRetOK;
	   }

	   else if ( strcmp (tipo, "antecessor") == 0 ) {
		   GRA_irVertice (Grafoparm, id);
		   LIS_InserirElementoApos (Grafo->corrente->antecessor, Grafoparm->corrente);
		   LIS_InserirElementoApos (Grafoparm->corrente->sucessor, Grafo->corrente);
		   return GRA_CondRetOK;
	   }
	   return GRA_CondRetParamInvalido;
   } /* Fim função: GRA &Criar aresta */

/***************************************************************************
*
*  Função: GRA  &Destruir grafo
*
****************************************************************************/

   GRA_tpCondRet GRA_destruirGrafo ( GRA_tppGrafo parmGrafo )
   {
	   GRA_tppElemento Elemento;
	   /* testa o parametro de entrada */
	   if (parmGrafo == NULL)
		   return GRA_CondRetGrafoNaoExiste;

	   /* prossegue enquanto existir a lista de vertices */
	   while ( parmGrafo->pListaVert != NULL ) {
		   Elemento = (GRA_pGrafo*)LIS_ObterValor(parmGrafo->pListaVert);
		   LIS_DestruirLista (Elemento->antecessor);
		   LIS_DestruirLista (Elemento->sucessor);
		   VER_DestroiVertice (Elemento->conteudo);
		   LIS_AvancarElementoCorrente (parmGrafo->pListaVert, 1);
	   }
	   /* destroi as listas */
	   LIS_DestruirLista (parmGrafo->pListaOrigens);
	   LIS_DestruirLista (parmGrafo->pListaVert);
	   /* libera a cabeça */
	   free (parmGrafo->corrente);
	   free (parmGrafo);

	   return GRA_CondRetOK;

   } /* Fim função: GRA  &Destruir grafo */

/***************************************************************************
*
*  Função: GRA  &Obter valor corrente
*
****************************************************************************/

   GRA_tpCondRet GRA_obterCorr ( GRA_tppGrafo parmGrafo , char * valor )
   {
	   VER_ObterValor (parmGrafo->corrente->conteudo, valor);
	   return GRA_CondRetOK;

   } /* Fim função: GRA  &Obter valor corrente */

  GRA_tpCondRet GRA_AvancaElemCorrente (GRA_tppGrafo Grafo, int id ) {

	  if (id == NULL || id == 1) {
		  IrInicioLista (Grafo->corrente->sucessor);
		  Grafo->corrente = (GRA_pGrafo*) LIS_ObterValor (Grafo->corrente->sucessor);
		  return GRA_CondRetOK;
	  }

	  else {
		  IrInicioLista (Grafo->corrente->sucessor);
		  Grafo->corrente = (GRA_pGrafo*) LIS_AvancarElementoCorrente(Grafo->corrente->sucessor, id);
		  return GRA_CondRetOK;
	  }

	  return GRA_CondRetNaoAchou;
  }

/********** Fim do módulo de implementação: GRA  Grafo **********/
