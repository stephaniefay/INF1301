#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Modulo de definicao: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
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
*     Versao  Autor    Data     Observacoes
*     4       avs   01/fev/2006 criar linguagem script simbolica
*     3       avs   08/dez/2004 uniformizacao dos exemplos
*     2       avs   07/jul/2003 unificacao de todos os modulos em um so projeto
*     1       avs   16/abr/2003 inicio desenvolvimento
*
*  $ED Descricao do modulo
*     Implementa listas genericas duplamente encadeadas.
*     Podem existir n listas em operacao simultaneamente.
*     As listas possuem uma cabeca encapsulando o seu estado.
*
*     Cada lista e homogenea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contem.
*
*     Os ponteiros para os dados sao copiados para elementos da lista.
*        Nao e copiado o valor apontado por estes ponteiros.
*
*     O controle da destruicao do valor de um elemento a ser excluido
*        e realizado por uma funcao fornecida pelo usuario.
*
*     Cada lista referencia uma funcao que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A funcao de liberacao dos valores contidos nos elementos deve
*        assegurar a liberacao de todos os espacos referenciados pelo
*        valor contido em um elemento.
*        Esta funcao e chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso nao seja necessario desalocar o valor referenciado pelo
*        elemento, o ponteiro para a funcao de liberacao podera ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta funcao deve promover a destruicao (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

//#include "def.h" REVER O QUE EH NECESSARIO

#ifdef _DEBUG
	#include "GENERICO.H"
#endif

/***** Declaracoes exportadas pelo modulo *****/

/* Tipo referencia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condicoes de retorno
*
*
*  $ED Descricao do tipo
*     Condicoes de retorno das funcoes da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista nao contem elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* Nao encontrou o valor procurado */

         LIS_CondRetFaltouMemoria
               /* Faltou memoria ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Modos de deturpar
*
*
*  $ED Descricao do tipo
*     Especificacoes dos modos de deturpacao a serem realizados 
*
***********************************************************************/

#ifdef _DEBUG

	typedef enum {

		/* Deturpacoes da Lista Genérica */

		DeturparEliminaCorrenteLista = 1,
			/* Elimina elemento corrente da lista */

		DeturparElemProximo,
			/* Deturpa o próximo elemento */

		DeturparElemAnterior,
			/* Deturpa o elemento anterior */

		DeturparProximoInvalido,
			/* Deturpa o próximo elemento com um valor inválido */

		DeturparAnteriorInvalido,
			/* Deturpa o elemento anterior com um valor inválido */

		DeturparValorElem,
			/* Deturpa o ponteiro do conteúdo do nó atribuindo NULL */

		DeturparEstruturaCorrente,
			/* altera estrutura do nó corrente */

		DeturparElemCorrente,
			/* Deturpa desencadeando o nó sem libera-lo com free */

		DeturparRefCorrente,
			/* Deturpa o ponteiro corrente atribuindo NULL  */

		DeturparInicioLista
			/* Deturpa o ponteiro de origem atribuindo NULL  */
	

	} LIS_tpModoDeturpar;

#endif


/***********************************************************************
*
*  $FC Funcao: LIS  &Criar lista
*
*  $ED Descricao da funcao
*     Cria uma lista generica duplamente encadeada.
*     Os possiveis tipos sao desconhecidos a priori.
*     A tipagem e implicita.
*     Nao existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a funcao que processa a
*                     exclusao do valor referenciado pelo elemento
*                     a ser excluido.
*                     Ver descricao do modulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro sera utilizado pelas funcoes que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memoria ou dados errados,
*     a funcao retornara NULL.
*     Nao sera dada mais informacao quanto ao problema ocorrido.
*
***********************************************************************/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Destruir lista
*
*  $ED Descricao da funcao
*     Destroi a lista fornecida.
*     O parâmetro ponteiro para a lista nao e modificado.
*     Se ocorrer algum erro durante a destruicao, a lista resultara
*     estruturalmente incorreta.
*     OBS. nao existe previsao para possiveis falhas de execucao.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   void LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Esvaziar lista
*
*  $ED Descricao da funcao
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Inserir elemento antes
*
*  $ED Descricao da funcao
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Inserir elemento apos
*
*  $ED Descricao da funcao
*     Insere novo elemento apas o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Excluir elemento
*
*  $ED Descricao da funcao
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente sera o novo corrente.
*     Se nao existir e existir o elemento à direita, este se tornara corrente.
*     Se este tambem nao existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Obter referencia para o valor contido no elemento
*
*  $ED Descricao da funcao
*     Obtem a referencia para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     nao NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

   void * LIS_ObterValor( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;

/***********************************************************************
*
*  $FC Funcao: LIS  &Ir para o elemento inicial
*
*  $ED Descricao da funcao
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista esta vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void LIS_IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Ir para o elemento final
*
*  $ED Descricao da funcao
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista esta vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void LIS_IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Avancar elemento
*
*  $ED Descricao da funcao
*     Avanca o elemento corrente numElem elementos na lista
*     Se numElem for positivo avanca em direcao ao final
*     Se numElem for negativo avanca em direcao ao inicio
*     numElem pode ser maior do que o númro de elementos existentes na
*               direcao desejada
*     Se numElem for zero somente verifica se a lista esta vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista esta vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Funcao: LIS Verifica lista
*
*  $FV Valor retornado
*     TST_CondRetOK
*     TST_CondRetErro    
*
***********************************************************************/

#ifdef _DEBUG

	TST_tpCondRet LIS_VerificaElem(LIS_tppLista pLista ) ;

#endif

/***********************************************************************
*
*  $FC Funcao: LIS Verifica lista
*
*  $FV Valor retornado
*     TST_CondRetOK
*     TST_CondRetErro    
*
***********************************************************************/

#ifdef _DEBUG

	TST_tpCondRet LIS_VerificaLista( LIS_tppLista pLista ) ;

#endif

/***********************************************************************
*
*  $FC Funcao: LIS Verifica lista
*
*  $FV Valor retornado
*     TST_CondRetOK
*     TST_CondRetErro    
*
***********************************************************************/

#ifdef _DEBUG

	TST_tpCondRet LIS_DeturparLista( LIS_tppLista pLista , 
									LIS_tpModoDeturpar ModoDeturpar ) ;

#endif


#undef LISTA_EXT

/********** Fim do modulo de definicao: LIS  Lista duplamente encadeada **********/


#else
#endif
