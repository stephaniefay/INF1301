#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Pilha.h"


static const char CRIAR_PILHA_CMD         [ ] = "=criarpilha"     ;
static const char DESTRUIR_PILHA_CMD      [ ] = "=destruirpilha"  ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"    ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PILHA   10
#define DIM_VALOR     100

PtoTopo * vtPilhas[ DIM_VT_PILHA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxPilha( int inxPilha , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar pilha
*
*  $ED Descrição da função
*     Podem ser criadas até 10 pilhas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de pilhas. Provoca vazamento de memória
*     =criarpilha                   inxPilha
*     =destruirpilha                inxPilha
*     =inselemapos                  inxPilha  string  CondRetEsp
*     =obtervalorelem               inxPilha  string  CondretPonteiro
*
***********************************************************************/

 TST_tpCondRet TST_EfetuarComando2( char * ComandoTeste )
   {

      int inxPilha  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char   StringDado[  DIM_VALOR ] ;
      char * pDado ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado[ 0 ] = 0 ;

      /* Testar Criarpilha */

         if ( strcmp( ComandoTeste , CRIAR_PILHA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,  &inxPilha ) ;

            if ( ( numLidos != 1 ) || ( ! ValidarInxPilha( inxPilha , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtPilhas[ inxPilha ] =
                 criaTopo() ;

            return TST_CompararPonteiroNulo( 1 , vtPilhas[ inxPilha ] ,
               "Erro em ponteiro de nova pilha."  ) ;

         } /* fim ativa: Testar CriarPilha */

      /* Testar Destruir Pilha */

         else if ( strcmp( ComandoTeste , DESTRUIR_PILHA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxPilha ) ;

            if ( ( numLidos != 1 ) || ( ! ValidarInxPilha( inxPilha , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            libera( vtPilhas[ inxPilha ] ) ;
            vtPilhas[ inxPilha ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir pilha */

      /* Testar inserir */

         else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxPilha , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxPilha( inxPilha , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;


            CondRet = (TST_tpCondRet)insere( vtPilhas[ inxPilha ] , pDado ) ;

            if ( CondRet != PLH_CondRetOk )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir apos."                   ) ;

         } /* fim ativa: Testar inserir */

      /* Testar retirar da pilha */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxPilha , StringDado , &ValEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxPilha( inxPilha , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) retira( vtPilhas[ inxPilha ] ) ;

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , pDado ,
                         "Valor não deveria existir." ) ;
            } /* if */

            if ( pDado == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pDado ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

            return TST_CompararString( StringDado , pDado ,
                         "Valor do elemento errado." ) ;

         } /* fim ativa: Testar retirar da pilha */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar pilha */
   

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de pilha
*
***********************************************************************/

   int ValidarInxPilha( int inxPilha , int Modo )
   {

      if ( ( inxPilha <  0 )
  || ( inxPilha >= DIM_VT_PILHA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtPilhas[ inxPilha ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtPilhas[ inxPilha ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de pilha */

/********** Fim do módulo de implementação: TLIS Teste pilha de símbolos **********/

