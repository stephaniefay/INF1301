/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTGRA.C
*  Letras identificadoras:      TGRA
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: sf - Stephanie Fay
			pp - Pedro Paulo
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   sf    3/out/2013 Início do desenvolvimento
*       2.00   pp   18/out/2013 Versão final sujeita a revisões pela equipe
*
*  $ED Descrição do módulo 
*     Este modulo contém as funções específicas para o teste do
*     módulo grafo. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo grafo:
*
*   "=GRAcriargrafo"       <inxGrafo> 
*              - Cria o grafo vazio ( Cabeça de grafo )
*
*   "=GRAcriarelemento"     <inxGrafo> <String-Nome> <String-Endereco> <Int-identificador> <RetornoEsperado>
*              - Cria um vertice do grafo
*
*   "=GRAcriararesta"      <inxGrafo> <String-Nome> <RetornoEsperado>
*              - Cria uma aresta ligando dois vertices
*
*   "=GRAirvertice"        <inxGrafo> <String-Nome> <RetornoEsperado>
*              - Caso exista aresta entre o vertice corrente e o indicado
*                por parametro, este passa a ser o corrente.
*
*   "=GRAobtervalor"       <inxGrafo> <String-Nome> <RetornoEsperado>
*              - Obtem valor do no corrente do grafo
*
*   "=GRAdestruirvertice"  <inxGrafo>   
*              - Destroi o vertice corrente
*
*   "=GRAdestruiraresta"   <inxGrafo> <String-Nome>
*              - Destroi uma aresta que liga o vertice corrente com o vertice identificado pelo parametro
*
*   "=GRAdestruirgrafo"    <inxGrafo>
*              - Destroi o grafo com indice passado por parametro
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "GRAFO.H"
#include    "VERTICE.H"
#include    "LISTA.H"


/* Tabela dos nomes dos comandos de teste específicos */

static const char     CRIAR_GRAFO_CMD      []=  "=criargrafo"      ;
static const char     CRIAR_VERTICE_CMD    []=  "=criarvertice"    ;
static const char     CRIAR_ARESTA_CMD     []=  "=criararesta"     ;
static const char     IR_VERTICE_CMD       []=  "=irvertice"       ;
static const char     OBTER_VAL_CMD        []=  "=obtervalor"      ;
static const char     DESTROI_VERTICE_CMD  []=  "=destruirvertice" ;
static const char     DESTROI_ARESTA_CMD   []=  "=destruiraresta"  ;
static const char     DESTROI_GRAFO_CMD    []=  "=destruirgrafo"   ;



#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

/* se modificado, deve-se modificar tambem a inicializacao do vtGrafo */
#define DIM_VT   5


/***** Estruturas de teste encapuladas no módulo *****/

#define DIM_NOME 80

typedef struct
{
   char conteudo [ DIM_NOME + 1 ] ;
   int id;
} 
TST_conteudo ;



GRA_tppGrafo   vtGrafo[ DIM_VT ] = { NULL , NULL , NULL , NULL , NULL } ;


/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRA Efetuar operações de teste específicas para grafo
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     grafo sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      GRA_tpCondRet CondRetObtido   = GRA_CondRetOK ;
      GRA_tpCondRet CondRetEsperada = GRA_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      int  NumLidos = -1 ;
      int  inxGrafo = -1 ;

      char conteudoTmp [ DIM_NOME + 1 ] ;
	  char * tipo = "aaaa";
      int  idTmp =  0 ;
	  int  idTmp2 = 0 ;

      TST_conteudo * TST_Content = 0 ;
	  char * TST_infoCorr ;
	        

      /* Testar CriarGrafo */

         if ( strcmp( ComandoTeste , CRIAR_GRAFO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" , &inxGrafo ) ;

            if ( ( NumLidos != 1 )
              || ( inxGrafo < 0 ) || ( inxGrafo >= DIM_VT ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = GRA_criarGrafo( vtGrafo[ inxGrafo ] ) ;

            if( CondRetObtido == GRA_CondRetFaltouMemoria )
            {
               return TST_CondRetMemoria ;
            } /* if */
            if( CondRetObtido != GRA_CondRetOK )
            {
               return TST_CondRetNaoExecutou ;
            } /* if */

            return TST_CondRetOK ;
         } /* fim ativa: Testar CriarGrafo */

      /* Testar CriaVertice */

         else if ( strcmp( ComandoTeste , CRIAR_VERTICE_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "isii" , &inxGrafo , &conteudoTmp , idTmp , 
													&CondRetEsperada ) ;

            if ( ( NumLidos != 4 )
              || ( inxGrafo < 0 ) || ( inxGrafo >= DIM_VT ))
            {
               return TST_CondRetParm ;
            } /* if */

            TST_Content = ( TST_conteudo * ) malloc ( sizeof ( TST_conteudo ) ) ;
            if( TST_Content == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

			strcpy ( TST_Content->conteudo , conteudoTmp ) ;
			TST_Content->id = idTmp;

			CondRetObtido = GRA_criaVertice( vtGrafo[ inxGrafo ] , TST_Content->conteudo,
											 TST_Content->id ) ;

            return TST_CompararInt( CondRetObtido , CondRetEsperada ,
                     "Condicao de retorno errada ao criar vertice." ) ;

         } /* fim ativa: Testar CriarVertice */

      //* Testar CriarAresta */

         else if ( strcmp( ComandoTeste , CRIAR_ARESTA_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iisi" , &inxGrafo , idTmp, &tipo, &CondRetEsperada ) ;

            if ( ( NumLidos != 3 )
              || ( inxGrafo < 0 ) || ( inxGrafo >= DIM_VT ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = GRA_criarAresta( vtGrafo[ inxGrafo ] , idTmp, tipo ) ;

            return TST_CompararInt( CondRetObtido , CondRetEsperada ,
                     "Condicao de retorno errada ao criar aresta." ) ;

         } /* fim ativa: Testar CriarAresta */

      /* Testar IrVertice */

         else if ( strcmp( ComandoTeste , IR_VERTICE_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &inxGrafo , idTmp , &CondRetEsperada ) ;

            if ( ( NumLidos != 3 )
              || ( inxGrafo < 0 ) || ( inxGrafo >= DIM_VT ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido =  GRA_irVertice ( vtGrafo[ inxGrafo ] , idTmp ) ;  

            return TST_CompararInt( CondRetObtido , CondRetEsperada ,
                     "Condicao de retorno errada ao ir para o vertice." ) ;

         } /* fim ativa: Testar IrVertice */

      /* Testar ObterCorr */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "isi" , &inxGrafo , &conteudoTmp , &CondRetEsperada ) ;

            if ( ( NumLidos != 3 )
              || ( inxGrafo < 0 ) || ( inxGrafo >= DIM_VT ))
            {
               return TST_CondRetParm ;
            } /* if */

            TST_infoCorr = NULL ;
            CondRetObtido = GRA_obterCorr ( vtGrafo[ inxGrafo ] , TST_infoCorr ) ;

            if( CondRetObtido == GRA_CondRetOK )
            {
               if( strcmp( TST_infoCorr , conteudoTmp ) != 0 )
               {
                  CondRetObtido = GRA_CondRetNaoAchou ;
               } /* if */
            } /* if */

            return TST_CompararInt( CondRetObtido , CondRetEsperada ,
                     "Condicao de retorno errada ao obter valor do vertice corrente." ) ;

         } /* fim ativa: Testar ObterCorr */

     /* Testar DestroiVertice */

         else if ( strcmp( ComandoTeste , DESTROI_VERTICE_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "i" , &inxGrafo ) ;

            if ( ( NumLidos != 1 )
              || ( inxGrafo < 0 ) || ( inxGrafo >= DIM_VT ))
            {
               return TST_CondRetParm ;
            } /* if */

            GRA_destruirVertice ( vtGrafo[ inxGrafo ] ) ; 

            return TST_CondRetOK ;

         } /* fim ativa: DestroiVertice */

      /* Testar DestroiAresta */

         else if ( strcmp( ComandoTeste , DESTROI_ARESTA_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "iii" , &inxGrafo , idTmp, idTmp2 ) ;

            if ( ( NumLidos != 3 )
              || ( inxGrafo < 0 ) || ( inxGrafo >= DIM_VT ))
            {
               return TST_CondRetParm ;
            } /* if */

            GRA_destruirAresta( vtGrafo[ inxGrafo ] , idTmp, idTmp2) ;

            return TST_CondRetOK ;

         } /* fim ativa: DestroiAresta */

      /* Testar DestroiGrafo */

         else if ( strcmp( ComandoTeste , DESTROI_GRAFO_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "i" , &inxGrafo ) ;

            if ( ( NumLidos != 1 )
              || ( inxGrafo < 0 ) || ( inxGrafo >= DIM_VT ))
            {
               return TST_CondRetParm ;
            } /* if */

            GRA_destruirGrafo ( vtGrafo[ inxGrafo ] ) ; 

            vtGrafo[ inxGrafo ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: DestroiGrafo */
   
      return TST_CondRetNaoConhec;

   } /* Fim função: TGRA Efetuar operações de teste específicas para grafo */


/********** Fim do módulo de implementação: Módulo de teste específico **********/
