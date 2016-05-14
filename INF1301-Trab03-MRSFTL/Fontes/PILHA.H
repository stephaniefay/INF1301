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

typedef struct PLH_tagPilha * PLH_tppPilha;

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

  $FC Função: PLH  &Criar pilha

  $ED Descrição da função
     Cria uma pilha genérica.
     Os possíveis tipos são desconhecidos a priori.
     A tipagem é implicita.
     Não existe identificador de tipo associado à lista.

  $EP Parâmetros
     ExcluirValor  - ponteiro para a função que processa a
                     exclusão do valor referenciado pelo elemento
                     a ser excluído.
                     Ver descrição do módulo.

  $FV Valor retornado
     Se executou corretamente retorna o ponteiro para o topo de uma pilha
     Este ponteiro será utilizado pelas funções que manipulem esta pilha.

     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
     a função retornará NULL.
     Não será dada mais informação quanto ao problema ocorrido.

***********************************************************************/

PLH_tppPilha PLH_CriarTopo ();

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

PLH_tpCondRet PLH_Insere (PLH_tppPilha plh, char pValor);

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

char * PLH_Retira (PLH_tppPilha plh);

/***********************************************************************

  $FC Função: PLH  &Libera Pilha

  $ED Descrição da função
     Libera uma dada pilha.

  $EP Parâmetros
     PtoTopo   -	O topo da pilha que será liberada.

  $FV Valor retornado
     VOID
***********************************************************************/

PLH_tpCondRet PLH_Libera (PLH_tppPilha plh);

/******************************************************************

********************************************************************/

int PLH_ObterTam (PLH_tppPilha plh);

/********************************************************************

*******************************************************************/

char * PLH_Printar (PLH_tppPilha plh);

#undef PILHA_EXT

/********** Fim do módulo de definição: PLH  Pilha **********/

#else
#endif