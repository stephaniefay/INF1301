#if ! defined( PILHA_ )
#define PILHA_
/**************************************************************
Pilha generica

Arquivo gerado:			PILHA.H

Projeto: INF1301
Autores: Stephanie, Marcos Rubio e Thiago

Histórico de evolução:
	Versão	Data		Observação
	1		09/05/2013	Inicio da codificação do módulo
	2		10/05/2013	Termino da codificação

Descrição do módulo
	Implementa pilhas genéricas e suas respectivas funções para
	um bom funcionamento.
	Por serem pilhas, seu conteúdo só pode ser alterado acessando
	o topo e, para isso, é feito o uso de duas structs.

	As pilhas são genérias, porém o valor é homogêneo durante
	a função.

	Utiliza ponteiros para a locomoção de informações.

*****************************************************************/

#if defined( PILHA_OWN )
   #define PILHA_EXT
#else
   #define PILHA_EXT extern
#endif

/* Tipo referência para uma lista */

typedef struct pilha Pilha;
typedef struct ptoProTopo PtoTopo;

/**************************************************************

$TC Tipo de dados: PLH Condições de retorno

$ED Descrição do tipo
	Condições de retorno das funções da pilha

***************************************************************/

typedef enum {

	PLH_CondRetOk ,
		/* Concluiu corretamente */

	PLH_CondRetPilhaVazia ,
		/* A pilha não contém valor */

	PLH_CondRetFaltouMemoria
		/* Faltou memória ao tentar criar um elemento novo*/

} PLH_tpCondRet;

/***********************************************************************

  $FC Função: PLH  &Criar Topo

  $ED Descrição da função
     Cria um topo para a referida pilha genérica.

  $EP Parâmetros
     VOID

  $FV Valor retornado
     Se executou corretamente retorna o ponteiro para o topo de uma pilha
     Este ponteiro será utilizado pelas funções que manipulem esta pilha.

     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
     a função retornará NULL.
     Não será dada mais informação quanto ao problema ocorrido.

***********************************************************************/

PtoTopo * criaTopo(void);

/***********************************************************************

  $FC Função: PLH  &Insere Valor

  $ED Descrição da função
     Insere um valor na pilha, alterando seu topo para
	  o novo valor obtido e mantém um ponteiro para o 
	  elemento anterior da pilha.

  $EP Parâmetros
     PtoTopo   -	O topo da pilha em que a informação será
					inserida.
     Void      -	Ponteiro para Void, assim assegurando que a
					informação que será inserida será genérica.

  $FV Valor retornado
     VOID

**********************************************************************/

PLH_tpCondRet insere(PtoTopo *,void *);

/***********************************************************************

  $FC Função: PLH  &É Vazio

  $ED Descrição da função
     Testa para saber se uma dada pilha está vazia (booleana).

  $EP Parâmetros
     PtoTopo   -	O topo da pilha que será testada.

  $FV Valor retornado
     0 se a pilha não está vazia.
	  1 se a pilha está vazia.

***********************************************************************/

int vazio(PtoTopo *);

/***********************************************************************

  $FC Função: PLH  &Retira Valor

  $ED Descrição da função
     Retira um dado valor da pilha genérica apresentada.

  $EP Parâmetros
     PtoTopo   -	O topo da pilha em que a informação será
					retirada.

  $FV Valor retornado
     Primeiro a função testa se há o que retirar da pilha, 
	  interrompendo a função se não houver, e retira o valor
	  armazenado do topo da pilha, retornando-o para o usuário.
***********************************************************************/

PLH_tpCondRet retira(PtoTopo *);

/***********************************************************************

  $FC Função: PLH  &Libera Pilha

  $ED Descrição da função
     Libera uma dada pilha.

  $EP Parâmetros
     PtoTopo   -	O topo da pilha que será liberada.

  $FV Valor retornado
     VOID
***********************************************************************/

PLH_tpCondRet libera(PtoTopo *);

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif