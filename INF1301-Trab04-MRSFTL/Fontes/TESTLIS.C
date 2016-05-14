/***************************************************************************
*  $MCI Modulo de implementacao: TLIS Teste lista de simbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouco para a automacao de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatizacao dos testes de modulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Historico de evolucao:
*     Versao  Autor			 Data			 Observacoes
*     4       avs			 01/fev/2006	 criar linguagem script simbolica
*     3       avs			 08/dez/2004	 uniformizacao dos exemplos
*     2       avs			 07/jul/2003	 unificacao de todos os modulos em um so projeto
*     1       avs			 16/abr/2003	 inicio desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>
#include    "TST_ESPC.H"
#include    "LISTA.H"

#ifdef _DEBUG
#include    "GENERICO.H"
#include    "LERPARM.H"
#include    "CESPDIN.H"
#include    "CONTA.H"
#endif


/* Tabela dos nomes dos comandos de teste especificos */

static const char RESET_LISTA_CMD         [ ] = "=resetteste"      ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"      ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"   ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"   ;
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"    ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"     ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem"  ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"     ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"        ;
static const char IR_FIM_CMD              [ ] = "=irfinal"         ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"     ;

/* Tabela dos comandos que somente operam em modo _DEBUG */

static const char VER_LISTA_CMD           [ ] = "=verificarlista"  ;
static const char VER_ELEM_CMD			  [ ] = "=verificarelem"   ;
static const char DETURPAR_LISTA_CMD	  [ ] = "=deturparlista"   ;
static const char DETURPAR_ELEM_CMD		  [ ] = "=deturparelem"    ;
static const char ZERAR_CONTADORES_CMD    [ ] = "=zerarcontadores" ;
static const char VER_MEMORIA_CMD         [ ] = "=verificarmemoria";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VT_ELEMS   50
#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

/***** Prototipos das funcoes encapuladas no modulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  Codigo das funcoes exportadas pelo modulo  *****/


/***********************************************************************
*
*  $FC Funcao: TLIS &Testar lista
*
*  $ED Descricao da funcao
*     Podem ser criadas ate 10 listas, identificadas pelos indices 0 a 9
*
*     Comandos disponiveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memoria
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  string  CondRetEsp
*     =inselemapos                  inxLista  string  CondRetEsp
*     =obtervalorelem               inxLista  string  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp
*
*	  =verificarlista				inxLista  CondRetEsp
*	  =verificarelem			    inxLista  CondRetEsp
*	  =deturparlista				inxLista  codDeturpa  CondRetEsp
*	  =deturparelem					inxLista  codDeturpa  CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista   = -1 ,
		  inxLista2  = -1 ,
		  inxElem    = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1 ,
		  codDeturpa = -1 ;

      TST_tpCondRet CondRet ;

      char   StringDado[  DIM_VALOR ] ;
      char * pDado ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtListas[ inxLista ] =
                 LIS_CriarLista( DestruirValor ) ;

            return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista."  ) ;

         } /* fim ativa: Testar CriarLista */

      /* Testar Esvaziar lista lista */

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_EsvaziarLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar lista lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista */

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;


            CondRet = LIS_InserirElementoAntes( vtListas[ inxLista ] , pDado ) ;

            if ( CondRet != LIS_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir antes."                   ) ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;


            CondRet = LIS_InserirElementoApos( vtListas[ inxLista ] , pDado ) ;

            if ( CondRet != LIS_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,"Condicao de retorno errada ao inserir apos.") ;

         } /* fim ativa: Testar inserir elemento apos */

      /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp , LIS_ExcluirElemento( vtListas[ inxLista ] ) , "Condicao de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &ValEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) LIS_ObterValor( vtListas[ inxLista ] ) ;

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , pDado ,
                         "Valor nao deveria existir." ) ;
            } /* if */

            if ( pDado == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pDado ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

            return TST_CompararString( StringDado , pDado ,
                         "Valor do elemento errado." ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_IrInicioLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ir para o elemento inicial */

      /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_IrFinalLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: LIS  &Ir para o elemento final */

      /* LIS  &Avancar elemento */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: LIS  &Avancar elemento */


#ifdef _DEBUG
	 /* LIS  &Verificar Lista */

         else if ( strcmp( ComandoTeste , VER_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_VerificaLista( vtListas[ inxLista ] ) ,
                      "Verificacao de lista acusou falhas na estrutura" ) ;

         } /* fim ativa: LIS  &Verificar Lista */

	 /* LIS  &Verificar Elemento */

		 else if ( strcmp( ComandoTeste , VER_ELEM_CMD ) == 0 )
		 {

			 numLidos = LER_LerParametros( "ii" , &inxLista , &CondRetEsp ) ;

			 if ( ( numLidos != 2 )
				 || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 return TST_CompararInt( CondRetEsp ,
				 LIS_VerificaElem( vtListas[inxLista]),
				 "Verificacao de elemento acusou falhas na estrutura" ) ;

		 } /* fim ativa: LIS  &Verificar Elemento */

	 /* LIS  &Deturpar Lista */

		 else if ( strcmp( ComandoTeste , DETURPAR_LISTA_CMD ) == 0 )
		 {

			 numLidos = LER_LerParametros( "iii" , &inxLista ,&codDeturpa, &CondRetEsp ) ;

			 if ( ( numLidos != 3 )
				 || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 return TST_CompararInt( CondRetEsp ,
				 LIS_DeturparLista( vtListas[inxLista], codDeturpa ),
				 "Problemas encontrados na deturpacao da lista" ) ;

		 } /* fim ativa: LIS  &Deturpar Lista */

	 
	 /* CNT  &Zerar Contadores */

		 else if ( strcmp( ComandoTeste , ZERAR_CONTADORES_CMD ) == 0 )
		 {

			 numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;

			 if( numLidos != 1 )
			 {
				 return TST_CondRetParm ;
			 } /* if */

			 CNT_ZerarContadores();
			 return TST_CondRetOK;

		 } /* fim ativa: LIS  &Zerar Contadores */

	  /* LIS  &Verificar vazamento de memória */
		 else if ( strcmp( ComandoTeste , VER_MEMORIA_CMD ) == 0 )
		 {

			 CED_ExibirTodosEspacos( CED_ExibirTodos ) ;

			 return TST_CondRetOK ;

		 } /* fim ativa: Verificar vazamento de memória */
#endif

		 
      return TST_CondRetNaoConhec ;

   } /* Fim funcao: TLIS &Testar lista */


/*****  Codigo das funcoes encapsuladas no modulo  *****/


/***********************************************************************
*
*  $FC Funcao: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim funcao: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Funcao: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim funcao: TLIS -Validar indice de lista */

/********** Fim do modulo de implementacao: TLIS Teste lista de simbolos **********/

