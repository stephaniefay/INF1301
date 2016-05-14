/***************************************************************************
*  $MCI Modulo de implementacao: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouco para a automacao de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatizacao dos testes de modulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Historico de evolucao:
*     Versao  Autor				Data     Observacoes	
*     4       avs				01/fev/2006 criar linguagem script simbolica
*     3       avs				08/dez/2004 uniformizacao dos exemplos
*     2       avs				07/jul/2003 unificacao de todos os modulos em um so projeto
*     1       avs				16/abr/2003 inicio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

#ifdef _DEBUG
#include "IdTiposEspaco.def"
#include "CESPDIN.H"
#include "CONTA.H"


#endif

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

typedef struct tagElemLista {

	void * pValor ;
	/* Ponteiro para o valor contido no elemento */

	struct tagElemLista * pAnt ;
	/* Ponteiro para o elemento predecessor */

	struct tagElemLista * pProx ;
	/* Ponteiro para o elemento sucessor */

} tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeca de lista
*
*
***********************************************************************/

typedef struct LIS_tagLista {

	tpElemLista * pOrigemLista ;
	/* Ponteiro para a origem da lista */

	tpElemLista * pFimLista ;
	/* Ponteiro para o final da lista */

	tpElemLista * pElemCorr ;
	/* Ponteiro para o elemento corrente da lista */

	int numElem ;
	/* Número de elementos da lista */

	void ( * ExcluirValor ) ( void * pValor ) ;
	/* Ponteiro para a função de destruição do valor contido em um elemento */

} LIS_tpLista ;

/***** Definições Encapsulados no Modulo ******/

static char Lixo [ 256 ] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;

/***** Prototipos das funcoes encapuladas no modulo *****/

static void LiberarElemento( LIS_tppLista   pLista ,
							tpElemLista  * pElem   ) ;

static tpElemLista * CriarElemento( LIS_tppLista pLista ,
									   void *       pValor  ) ;

static void LimparCabeca( LIS_tppLista pLista ) ;

#ifdef _DEBUG

static TST_tpCondRet LIS_DeturparEliminaCorrenteLista ( LIS_tppLista pLista ) ;

static TST_tpCondRet LIS_DeturparElemProximo( tpElemLista*  pElem );

static TST_tpCondRet LIS_DeturparElemAnterior( tpElemLista* pElem );

static TST_tpCondRet LIS_DeturparProximoInvalido( tpElemLista* pElem );

static TST_tpCondRet LIS_DeturparAnteriorInvalido( tpElemLista* pElem );

static TST_tpCondRet LIS_DeturparValorElem( tpElemLista* pElemAux );

static TST_tpCondRet LIS_DeturparRefCorrente( LIS_tppLista pLista );

static TST_tpCondRet LIS_DeturparElemCorrente( LIS_tppLista pLista );

static TST_tpCondRet LIS_DeturparInicioLista( LIS_tppLista pLista );

static TST_tpCondRet LIS_DeturparEstruturaCorrente( tpElemLista* pElem ) ; 

static void DeturparLiberarElemento( LIS_tppLista   pLista , tpElemLista  * pElem );

#endif

/*****  Codigo das funcoes exportadas pelo modulo  *****/

/***************************************************************************
*
*  Funcao: LIS  &Criar lista
*  ****/

LIS_tppLista LIS_CriarLista( void   ( * ExcluirValor ) ( void * pDado ) )
{

	LIS_tpLista * pLista = NULL ;

#ifdef _DEBUG
	CNT_CONTAR( "LIS_CriarLista" );
#endif

	pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
	if ( pLista == NULL )
	{
		return NULL ;
	} /* if */

#ifdef _DEBUG
	CED_DefinirTipoEspaco( pLista, LIS_TipoEspacoLista );
#endif

	LimparCabeca( pLista ) ;

	pLista->ExcluirValor = ExcluirValor ;

	return pLista ;

} /* Fim funcao: LIS  &Criar lista */

/***************************************************************************
*
*  Funcao: LIS  &Destruir lista
*  ****/

void LIS_DestruirLista( LIS_tppLista pLista )
{

#ifdef _DEBUG
	CNT_CONTAR( "LIS_DestruirLista" );
	assert( pLista != NULL ) ;
#endif

	LIS_EsvaziarLista( pLista ) ;

	free( pLista ) ;

} /* Fim funcao: LIS  &Destruir lista */

/***************************************************************************
*
*  Funcao: LIS  &Esvaziar lista
*  ****/

void LIS_EsvaziarLista( LIS_tppLista pLista )
{

	tpElemLista * pElem ;
	tpElemLista * pProx ;

#ifdef _DEBUG
	CNT_CONTAR( "LIS_EsvaziarLista" );
	assert( pLista != NULL ) ;
#endif

	pElem = pLista->pOrigemLista ;
	while ( pElem != NULL )
	{
		pProx = pElem->pProx ;
		LiberarElemento( pLista , pElem ) ;
		pElem = pProx ;
	} /* while */

	LimparCabeca( pLista ) ;

} /* Fim funcao: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Funcao: LIS  &Inserir elemento antes
*  ****/

LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
									   void * pValor        )
{

	tpElemLista * pElem ;

#ifdef _DEBUG
	CNT_CONTAR( "LIS_InserirElementoAntes" );
	assert( pLista != NULL ) ;
#endif

	/* Criar elemento a inerir antes */

	pElem = CriarElemento( pLista , pValor ) ;
	if ( pElem == NULL )
	{
		return LIS_CondRetFaltouMemoria ;
	} /* if */

	/* Encadear o elemento antes do elemento corrente */

	if ( pLista->pElemCorr == NULL )
	{
		pLista->pOrigemLista = pElem ;
		pLista->pFimLista = pElem ;
	} 
	else
	{
		if ( pLista->pElemCorr->pAnt != NULL )
		{
			pElem->pAnt  = pLista->pElemCorr->pAnt ;
			pLista->pElemCorr->pAnt->pProx = pElem ;
		} 
		else
		{
			pLista->pOrigemLista = pElem ;
		} /* if */

		pElem->pProx = pLista->pElemCorr ;
		pLista->pElemCorr->pAnt = pElem ;
	} /* if */

	pLista->pElemCorr = pElem ;

	return LIS_CondRetOK ;

} /* Fim funcao: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Funcao: LIS  &Inserir elemento apos
*  ****/

LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
									  void * pValor        )

{

	tpElemLista * pElem ;

#ifdef _DEBUG
	CNT_CONTAR("LIS_InserirElementoApos");
	assert( pLista != NULL ) ;
#endif

	/* Criar elemento a inerir apos */

	pElem = CriarElemento( pLista , pValor ) ;
	if ( pElem == NULL )
	{
		return LIS_CondRetFaltouMemoria ;
	} /* if */

	/* Encadear o elemento apos o elemento */

	if ( pLista->pElemCorr == NULL )
	{
		pLista->pOrigemLista = pElem ;
		pLista->pFimLista = pElem ;
	} else
	{
		if ( pLista->pElemCorr->pProx != NULL )
		{
			pElem->pProx  = pLista->pElemCorr->pProx ;
			pLista->pElemCorr->pProx->pAnt = pElem ;
		} else
		{
			pLista->pFimLista = pElem ;
		} /* if */

		pElem->pAnt = pLista->pElemCorr ;
		pLista->pElemCorr->pProx = pElem ;

	} /* if */

	pLista->pElemCorr = pElem ;

	return LIS_CondRetOK ;

} /* Fim funcao: LIS  &Inserir elemento apos */

/***************************************************************************
*
*  Função: LIS  &Verifica Lista Vazia
***************************************************************************/

   int LIS_VerificaListaVazia(LIS_tpLista * pLista)
	{
	return (pLista == NULL);
	}	
	
/* Fim função: LIS  &Verifica Lista Vazia*/


/***************************************************************************
*
*  Funcao: LIS  &Excluir elemento
*  *************************************************************************/

LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
{

	tpElemLista * pElem ;

#ifdef _DEBUG
	CNT_CONTAR( "LIS_ExcluirElemento" );
	assert( pLista  != NULL ) ;
#endif

	if ( pLista->pElemCorr == NULL )
	{
		return LIS_CondRetListaVazia ;
	} /* if */

	pElem = pLista->pElemCorr ;

	/* Desencadeia à esquerda */

	if ( pElem->pAnt != NULL )
	{
		pElem->pAnt->pProx   = pElem->pProx ;
		pLista->pElemCorr    = pElem->pAnt ;
	} else {
		pLista->pElemCorr    = pElem->pProx ;
		pLista->pOrigemLista = pLista->pElemCorr ;
	} /* if */

	/* Desencadeia à direita */

	if ( pElem->pProx != NULL )
	{
		pElem->pProx->pAnt = pElem->pAnt ;
	} else
	{
		pLista->pFimLista = pElem->pAnt ;
	} /* if */

	LiberarElemento( pLista , pElem ) ;

	return LIS_CondRetOK ;

} /* Fim funcao: LIS  &Excluir elemento */

/***************************************************************************
*
*  Funcao: LIS  &Obter referencia para o valor contido no elemento
*  ****/

void * LIS_ObterValor( LIS_tppLista pLista )
{

#ifdef _DEBUG
	CNT_CONTAR( "LIS_ObterValor" );
	assert( pLista != NULL ) ;
#endif

	if ( pLista->pElemCorr == NULL )
	{
		return NULL ;
	} /* if */

	return pLista->pElemCorr->pValor ;

} /* Fim funcao: LIS  &Obter referencia para o valor contido no elemento */

/***************************************************************************
*
*  Funcao: LIS  &Ir para o elemento inicial
*  ****/

void LIS_IrInicioLista( LIS_tppLista pLista )
{

#ifdef _DEBUG
	CNT_CONTAR( "LIS_IrInicioLista" );
	assert( pLista != NULL ) ;
#endif

	pLista->pElemCorr = pLista->pOrigemLista ;

} /* Fim funcao: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Funcao: LIS  &Ir para o elemento final
*  ****/

void LIS_IrFinalLista( LIS_tppLista pLista )
{

#ifdef _DEBUG
	CNT_CONTAR( "LIS_IrFinalLista" );
	assert( pLista != NULL ) ;
#endif

	pLista->pElemCorr = pLista->pFimLista ;

} /* Fim funcao: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Funcao: LIS  &Avancar elemento
*  ****/

LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
										  int numElem )
{

	int i ;

	tpElemLista * pElem ;

#ifdef _DEBUG
	CNT_CONTAR( "LIS_AvancarElementoCorrente" );
	assert( pLista != NULL ) ;
#endif

	/* Tratar lista vazia */

	if ( pLista->pElemCorr == NULL )
	{

		return LIS_CondRetListaVazia ;

	} /* fim ativa: Tratar lista vazia */

	/* Tratar avancar para frente */

	if ( numElem > 0 )
	{

		pElem = pLista->pElemCorr ;
		for( i = numElem ; i > 0 ; i-- )
		{
			if ( pElem == NULL )
			{
				break ;
			} /* if */
			pElem    = pElem->pProx ;
		} /* for */

		if ( pElem != NULL )
		{
			pLista->pElemCorr = pElem ;
			return LIS_CondRetOK ;
		} /* if */

		pLista->pElemCorr = pLista->pFimLista ;
		return LIS_CondRetFimLista ;

	} /* fim ativa: Tratar avancar para frente */

	/* Tratar avancar para tras */

	else if ( numElem < 0 )
	{

		pElem = pLista->pElemCorr ;
		for( i = numElem ; i < 0 ; i++ )
		{
			if ( pElem == NULL )
			{
				break ;
			} /* if */
			pElem    = pElem->pAnt ;
		} /* for */

		if ( pElem != NULL )
		{
			pLista->pElemCorr = pElem ;
			return LIS_CondRetOK ;
		} /* if */

		pLista->pElemCorr = pLista->pOrigemLista ;
		return LIS_CondRetFimLista ;

	} /* fim ativa: Tratar avancar para tras */

	/* Tratar nao avancar */

	return LIS_CondRetOK ;

} /* Fim funcao: LIS  &Avancar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {

       tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pElem->pValor == pValor )
         {
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim função: LIS  &Procurar elemento contendo valor */



#ifdef _DEBUG

/***********************************************************************
*
*  $FC Funcao: LIS	&Verifica Elemento da Lista  
*  ****/

TST_tpCondRet LIS_VerificaElem(LIS_tppLista pLista )
{	

	tpElemLista* pElem = NULL;
	LIS_tppLista pListaAux = NULL ;

	// Criacao de lista auxiliar para nao modificar lista original
	pListaAux = ( LIS_tppLista )( pLista ) ;
	pElem = pLista->pElemCorr;

	CNT_CONTAR( "LIS_VerificaElem" );

	/* Verificar se o elemento e vaildo */

	if ( pLista->pElemCorr == NULL )
	{
		return TST_NotificarFalha( "Tentou verificar no inexistente." ) ;
	} /* if */

	if ( TST_CompararInt( LIS_TipoEspacoElemento, CED_ObterTipoEspaco( pElem ) ,
		"Tipo do espaco de dados nao e no de lista." ) != TST_CondRetOK )
	{
		return TST_CondRetErro ;
	} /* if */

	// Criacao de elemento auxiliar para nao modificar elemento original
	pElem= pLista->pElemCorr;


	/* Verifica Encadeamento */

	if( pElem->pAnt == NULL )
	{
		LIS_IrInicioLista( pListaAux );

		if ( TST_CompararPonteiro( pListaAux->pElemCorr , pElem, 
			"Encadeamento do No inconsistente." ) != TST_CondRetOK )
		{
			return TST_CondRetErro;
		} /* if */

	} /* if */

	if( pElem->pAnt != NULL )
	{
		if( TST_CompararPonteiro( pElem->pAnt->pProx, pElem, 
			"Encadeamento do No inconsistente." ) != TST_CondRetOK )
		{
			return TST_CondRetErro;
		} /* if */

	} /* if */

	if( pElem->pProx == NULL )
	{
		LIS_IrFinalLista( pListaAux );

		if ( TST_CompararPonteiro( pListaAux->pElemCorr , pElem, 
			"Encadeamento do No inconsistente." ) != TST_CondRetOK )
		{
			return TST_CondRetErro;
		} /* if */

	} /* if */

	if( pElem->pProx != NULL )
	{
		if( TST_CompararPonteiro( pElem->pProx->pAnt, pElem, 
			"Encadeamento do No inconsistente." ) != TST_CondRetOK )
		{
			return TST_CondRetErro;
		} /* if */

	} /* if */

	return TST_CondRetOK;

} /* Fim funcao:  &LIS Verifica Elemento da Lista  */


/***********************************************************************
*
*  $FC Funcao: LIS	&Verifica Lista  
*  ****/

TST_tpCondRet LIS_VerificaLista( LIS_tppLista pLista )
{
	tpElemLista* pElem = NULL ;	
	LIS_tppLista pListaAux = NULL ;

	// Criacao de lista auxiliar para nao modificar lista original
	pListaAux = ( LIS_tppLista )( pLista ) ;

	CNT_CONTAR( "LIS_VerificaLista" );

	//CED_MarcarEspacoAtivo( pListaAux );

	/* Verificar se a lista e vailda */

	if( pListaAux == NULL )
	{
		return TST_NotificarFalha( "Tentou verificar lista inexistente." ) ;
	} /* if */

	if ( TST_CompararInt( LIS_TipoEspacoLista, CED_ObterTipoEspaco( pLista ) ,
		"Tipo de espaco nao eh lista." ) != TST_CondRetOK )
	{
		return TST_CondRetErro ;
	} /* if */


	//pListaAux = ( LIS_tppLista * )( pElemLista ) ;

	/* Verifica Estrutura da Lista */

	if( ( pListaAux->pOrigemLista == NULL ) && ( pListaAux->pFimLista != NULL ) ||
		( pListaAux->pOrigemLista == NULL ) && ( pListaAux->pElemCorr != NULL ) ||
		( pListaAux->pOrigemLista != NULL ) && ( pListaAux->pElemCorr == NULL ) ||
		( pListaAux->pOrigemLista != NULL ) && ( pListaAux->pFimLista == NULL ) ||
		( pListaAux->pFimLista == NULL )    && ( pListaAux->pElemCorr != NULL ) ||
		( pListaAux->pFimLista != NULL )    && ( pListaAux->pElemCorr == NULL ) )
	{
		return TST_NotificarFalha( "Erro de ponteiros na estrutura lista." ) ;

	} /* if */

	if( pListaAux->pOrigemLista == pListaAux->pFimLista )
	{
		if( TST_CompararInt( 1, pListaAux->numElem, 
			"Contador de elementos da lista ou ponteiros de inicio e final inconsistentes" ) )
		{
			return TST_CondRetErro;
		} /* if */

	} /* if */

	if( ( pListaAux->pOrigemLista != pListaAux->pFimLista ) &&
		( pListaAux->pElemCorr != NULL ) )
	{
		if( pListaAux->numElem <= 1 )
		{
			return TST_NotificarFalha( 
				"Contador de elementos da lista ou ponteiros de inicio e final inconsistentes" ) ;
		} /* if */

	} /* if */

	if( pListaAux->pElemCorr == NULL )
	{
		if( TST_CompararInt( 0, pListaAux->numElem, 
			"Contador de elementos da lista inconsistente") )
		{
			return TST_CondRetErro;
		} /* if */

	} /* if */

	if( pListaAux->pElemCorr != NULL )
	{
		if( pListaAux->numElem < 1 )
		{
			return TST_NotificarFalha( 
				"Contador de elementos da lista ou ponteiro para elemento corrente inconsistentes" ) ;
		} /* if */

	} /* if */

	LIS_IrInicioLista( pListaAux );
	pElem = pListaAux->pElemCorr;

	if( TST_CompararPonteiro( pListaAux->pOrigemLista, pElem,
		"Funcao de retornar origem da lista incompativel com a estrutura" ) )
	{
		return TST_CondRetErro;
	} /* if */

	LIS_IrFinalLista( pListaAux );
	pElem = pListaAux->pElemCorr;

	if( TST_CompararPonteiro( pListaAux->pFimLista, pElem,
		"Funcao de retornar final da lista incompativel com a estrutura" ) )
	{
		return TST_CondRetErro;
	} /* if */

	/* Verifica Elementos da Lista */

	LIS_IrInicioLista( pListaAux );

	for( pElem =  pListaAux->pElemCorr;
		pElem != NULL;
		pElem =  pElem->pProx )
	{
		CED_MarcarEspacoAtivo( pElem );

		if( LIS_VerificaElem(pListaAux ) != TST_CondRetOK )
		{
			return TST_CondRetErro ;

		} /* if */

	} /* for */


	return TST_CondRetOK ;

} /* Fim funcao: LIS  &Verifica Lista */

#endif


/*****  Codigo das funcoes encapsuladas no modulo  *****/

/***********************************************************************
*
*  $FC Funcao: LIS  -Liberar elemento da lista
*
*  $ED Descricao da funcao
*     Elimina os espacos apontados pelo valor do elemento e o
*     proprio elemento.
*
***********************************************************************/

void LiberarElemento( LIS_tppLista   pLista ,
					 tpElemLista  * pElem   )
{

	if ( ( pLista->ExcluirValor != NULL )
		&& ( pElem->pValor != NULL        ))
	{
		pLista->ExcluirValor( pElem->pValor ) ;
	} /* if */

	free( pElem ) ;

	pLista->numElem-- ;

} /* Fim funcao: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Funcao: LIS  -Criar o elemento
*
***********************************************************************/

tpElemLista * CriarElemento( LIS_tppLista pLista ,
								void *       pValor  )
{

	tpElemLista * pElem ;

	pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
	if ( pElem == NULL )
	{
		return NULL ;
	} /* if */

#ifdef _DEBUG
	CED_DefinirTipoEspaco( pElem, LIS_TipoEspacoElemento );
#endif

	pElem->pValor = pValor ;
	pElem->pAnt   = NULL  ;
	pElem->pProx  = NULL  ;

	pLista->numElem ++ ;

	return pElem ;

} /* Fim funcao: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Funcao: LIS  -Limpar a cabeca da lista
*
***********************************************************************/

void LimparCabeca( LIS_tppLista pLista )
{

	pLista->pOrigemLista = NULL ;
	pLista->pFimLista = NULL ;
	pLista->pElemCorr = NULL ;
	pLista->numElem   = 0 ;

} /* Fim funcao: LIS  -Limpar a cabeca da lista */


#ifdef _DEBUG

/***********************************************************************
*
*  $FC: LIS  Deturpar Nó Próximo da Lista (ação 2)
*
***********************************************************************/

TST_tpCondRet LIS_DeturparElemProximo( tpElemLista*  pElem )
{
	CNT_CONTAR( "LIS_DeturparElemProximo" );

	if( pElem == NULL )
	{
		return TST_CondRetErro;
	} /* if */

	pElem->pProx = NULL ;

	return TST_CondRetOK ;

} /* Fim: LIS  Deturpar Nó Próximo da Lista */

/***********************************************************************
*
*  $FC: LIS  Deturpar Nó Anterior da Lista (ação 3)
*
***********************************************************************/

TST_tpCondRet LIS_DeturparElemAnterior( tpElemLista* pElem )
{
	CNT_CONTAR( "LIS_DeturparElemAnterior" );

	if( pElem == NULL )
	{
		return TST_CondRetErro ;
	} /* if */

	pElem->pAnt = NULL ;

	return TST_CondRetOK ;

} /* Fim: LIS  Deturpar Nó Anterior da Lista   */


/***********************************************************************
*
*  $FC: LIS Deturpar Nó Próximo da Lista Atribuindo Lixo ao Valor (ação 4)
*
***********************************************************************/

TST_tpCondRet LIS_DeturparProximoInvalido( tpElemLista* pElem )
{
	CNT_CONTAR( "LIS_DeturparProximoInvalido" );

	if( pElem == NULL )
	{
		return TST_CondRetErro ;
	} /* if */

	pElem->pProx = Lixo ;

	return TST_CondRetOK ;

} /* Fim: LIS Deturpar Nó Próximo da Lista Atribuindo Lixo ao Valor   */

/***********************************************************************
*
*  $FC: LIS Deturpar Nó Anterior da Lista Atribuindo Lixo ao Valor (ação 5)
*
***********************************************************************/

TST_tpCondRet LIS_DeturparAnteriorInvalido( tpElemLista* pElem )
{
	CNT_CONTAR( "LIS_DeturparAnteriorInvalido" );

	if( pElem == NULL )
	{
		return TST_CondRetErro;
	} /* if */

	pElem->pAnt = Lixo ;

	return TST_CondRetOK;


} /* Fim: LIS Deturpar Nó Anterior da Lista atribuindo lixo ao valor */

/***********************************************************************
*
*  $FC: LIS Deturpar o Conteúdo do Elemento (ação 6)
*
***********************************************************************/

TST_tpCondRet LIS_DeturparValorElem( tpElemLista* pElemAux ) 
{
	CNT_CONTAR( "LIS_DeturparValorElem" ) ;

	if( pElemAux == NULL )
	{
		return TST_CondRetErro;
	} /* if */	

	pElemAux->pValor = NULL ;

	return TST_CondRetOK ;

}/* Fim: LIS  Deturpar o Conteúdo do Elemento*/

/***********************************************************************
*
*  $FC: LIS Deturpar Elemento Corrente (ação 8)
*
***********************************************************************/

TST_tpCondRet LIS_DeturparElemCorrente( LIS_tppLista pLista )
{
	tpElemLista* pElem    = NULL;
	tpElemLista* pElemAux = NULL;

	CNT_CONTAR( "LIS_DeturparElemCorrente" );

	if( pLista == NULL || pLista->pElemCorr == NULL )
	{
		return TST_CondRetErro;
	} /* if */

	/* Se o elemento for o único na lista */
	if( pLista->pElemCorr->pProx == NULL &&
		pLista->pElemCorr->pAnt == NULL ) 
	{		
		pLista->pElemCorr = NULL ;
		pLista->pFimLista = NULL ;
		pLista->pOrigemLista = NULL ;

	} /* if */

	/* Se o elemento for o primeiro da lista */
	else if( pLista->pElemCorr->pAnt == NULL &&
		pLista->pElemCorr->pProx != NULL )
	{
		pElem = pLista->pElemCorr->pProx ;
		pLista->pOrigemLista = pElem ;
		pLista->pElemCorr = pElem ;

	} /* else if */

	/* Se o elemento estiver no meio da lista */
	else if( pLista->pElemCorr->pProx != NULL )
	{
		pElem    = pLista->pElemCorr->pProx ;
		pElemAux = pLista->pElemCorr->pAnt ;

		pElemAux->pProx = pElem ;
		pElem->pAnt = pElemAux ;
		pLista->pElemCorr = pElemAux ;		

	} /* else if */

	/* Se o elemento for o último da lista */
	else
	{
		pElem = pLista->pElemCorr->pAnt ;
		pElem->pProx = NULL ;
		pLista->pElemCorr = pElem ;	

	} /* else */

	return TST_CondRetOK;

} /* Fim: LIS Deturpar Elemento Corrente */

/***********************************************************************
*
*  $FC: LIS  Deturpar ponteiro Corrente (ação 9)
*
***********************************************************************/

TST_tpCondRet LIS_DeturparRefCorrente( LIS_tppLista pLista )
{
	CNT_CONTAR( "LIS_DeturparRefCorrente" );

	if( pLista == NULL || pLista->pElemCorr == NULL )
	{
		return TST_CondRetErro;
	} /* if */

	pLista->pElemCorr = NULL;

	return TST_CondRetOK;

} /* Fim: LIS  Deturpar ponteiro Corrente*/


/***********************************************************************
*
*  $FC: LIS  Deturpar Ponteiro Origem (ação 10)
*
***********************************************************************/

TST_tpCondRet LIS_DeturparInicioLista( LIS_tppLista pLista )
{
	CNT_CONTAR( "LIS_DeturparInicioLista" );

	if( pLista == NULL || pLista->pOrigemLista == NULL )
	{
		return TST_CondRetErro;
	} /* if */

	pLista->pOrigemLista = NULL;

	return TST_CondRetOK;

} /* Fim: LIS  Deturpar Ponteiro Origem*/

/***************************************************************************
*
*  Funcao: LIS  &Deturpar Lista
*  ****/

TST_tpCondRet LIS_DeturparLista( LIS_tppLista pLista , 
								LIS_tpModoDeturpar ModoDeturpar )
{
	tpElemLista * pElem;

	CNT_CONTAR( "LIS_DeturparLista" );

	if ( pLista->pElemCorr == NULL )
	{
		return TST_CondRetErro ;
	} /* if */

	pElem = pLista->pElemCorr;

	switch ( ModoDeturpar ) {

		/* Deturpa excluir elemento sem free */
		   case DeturparEliminaCorrenteLista:
			   {

				   return LIS_DeturparEliminaCorrenteLista ( pLista );
				   
			   } /* fim ativa: Deturpa excluir elemento sem free

				 /* Deturpa o próximo elemento */

		   case DeturparElemProximo :
			   {

				   return LIS_DeturparElemProximo( pElem ) ;

			   } /* fim ativa: Deturpa o próximo elemento */

			   /* Deturpa o Elemento Anterior */

		   case DeturparElemAnterior :
			   {

				   return LIS_DeturparElemAnterior ( pElem ) ; 

			   } /* fim ativa: Deturpa o Elemento Anterior */

			   /* Deturpa o próximo elemento com um valor inválido */

		   case DeturparProximoInvalido :
			   {

				   return LIS_DeturparProximoInvalido ( pElem ) ;
				   

			   } /* fim ativa: Deturpa o próximo elemento com um valor inválido */ 

			   /* Deturpa o elemento anterior com um valor inválido */

		   case DeturparAnteriorInvalido :
			   {

				   return LIS_DeturparAnteriorInvalido ( pElem ) ;

			   } /* fim ativa: Deturpa o elemento anterior com um valor inválido */

			   /* Deturpa o ponteiro do conteúdo do nó atribuindo NULL */

		   case DeturparValorElem :
			   {

				   return LIS_DeturparValorElem ( pElem ) ;
				   

			   } /* fim ativa: Deturpa o ponteiro do conteúdo do nó atribuindo NULL */

				/* Deturpa estrutura do elemento corrente */
		   case DeturparEstruturaCorrente:
			   {
				   return LIS_DeturparEstruturaCorrente( pElem );				   

			   }/* fim ativa: Deturpa estrutura do elemento corrente  */

			   /* Deturpa desencadeando o nó sem libera-lo com free */

		   case DeturparElemCorrente :
			   {

				   return LIS_DeturparElemCorrente(pLista);

			   } /* fim ativa: Deturpa desencadeando o nó sem libera-lo com free */

			   /* Deturpa o ponteiro corrente atribuindo NULL  */	

		   case DeturparRefCorrente :
			   {

				   return LIS_DeturparRefCorrente(pLista);
				   
			   } /* fim ativa: Deturpa o ponteiro corrente atribuindo NULL */

			   /* Deturpa o ponteiro de origem atribuindo NULL  */	

		   case DeturparInicioLista :
			   {

				   return LIS_DeturparInicioLista(pLista);

			   } /* fim ativa: Deturpa o ponteiro de origem atribuindo NULL */

		   default :
			   {

				   return TST_CondRetErro;
			   }

	} /* switch ModoDeturpar */
	return TST_CondRetErro;

} /* Fim: LIS  &Deturpar Lista */


/***************************************************************************
*
*  Funcao: LIS  Elimina o elemento corrente da lista (ação 1)
*  ************************************************************************/

TST_tpCondRet LIS_DeturparEliminaCorrenteLista ( LIS_tppLista pLista )
{

	tpElemLista * pElem ;

#ifdef _DEBUG
	CNT_CONTAR( "LIS_DeturparEliminaCorrenteLista" );
	assert( pLista  != NULL ) ;
#endif

	if ( pLista->pElemCorr == NULL )
	{
		return LIS_CondRetListaVazia ;
	} /* if */

	pElem = pLista->pElemCorr ;

	/* Desencadeia à esquerda */

	if ( pElem->pAnt != NULL )
	{
		pElem->pAnt->pProx   = pElem->pProx ;
		pLista->pElemCorr    = pElem->pAnt ;
	} else {
		pLista->pElemCorr    = pElem->pProx ;
		pLista->pOrigemLista = pLista->pElemCorr ;
	} /* if */

	/* Desencadeia à direita */

	if ( pElem->pProx != NULL )
	{
		pElem->pProx->pAnt = pElem->pAnt ;
	} else
	{
		pLista->pFimLista = pElem->pAnt ;
	} /* if */

	DeturparLiberarElemento( pLista , pElem ) ;

	return LIS_CondRetOK ;

} /* Fim :LIS  Elimina o elemento corrente da lista */


/***********************************************************************
*
*  $FC: LIS  Liberar elemento da lista para deturpar
*
*  $ED Descricao da função
*     Elimina os espacos apontados pelo valor do elemento e o
*     proprio elemento sem dar free.
*
***********************************************************************/

void DeturparLiberarElemento( LIS_tppLista   pLista ,
							 tpElemLista  * pElem   )
{

	if ( ( pLista->ExcluirValor != NULL )
		&& ( pElem->pValor != NULL        ))
	{
		pLista->ExcluirValor( pElem->pValor ) ;
	} /* if */

	pLista->numElem-- ;

} /* Fim: LIS  DeturparLiberar elemento da lista */



/***********************************************************************
*
*  $FC: LIS  Altera o tipo da estrutura apontada no nó (ação 7)
*
***********************************************************************/

TST_tpCondRet LIS_DeturparEstruturaCorrente( tpElemLista* pElem )
{
	CNT_CONTAR( "LIS_DeturparEstruturaCorrente" );

	if( pElem == NULL )
	{
		return TST_CondRetErro;
	} /* if */

	pElem = 6;  //valor aleatorio

	return TST_CondRetOK;


} /* Fim: LIS  Altera o tipo da estrutura apontada no nó*/

#endif

/********** Fim do modulo de implementacao: LIS  Lista duplamente encadeada **********/

