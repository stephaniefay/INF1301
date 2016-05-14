#if ! defined( MATRIZ_ )
#define MATRIZ_
/**************************************************************
Matriz generica

Arquivo gerado:			MATRIZ.H

Projeto: INF1301
Autores: Stephanie, Marcos Rubio e Thiago

Histórico de evolução:
	Versão	Data		Observação
	1		13/05/2013	Inicio e termino da codificação do modulo

Descrição do módulo
	Implementa uma matriz de listas genéricas duplamente
	encadeadas que o conteúdo são pilhas genéricas.

	A matriz funcionará com uma lista principal que terá ponteiros
	para a origem, o último elemente dela, além dos ponteiros
	de locomoção normais (próximo e anterior). Seu conteúdo terá 
	um ponteiro para outra lista com cabeça que funcionará da
	mesma maneira que a principal, sendo assim as colunas de
	nossa matriz. O conteúdo dessas, no entantanto, são ponteiros
	para pilhas genéricas.

	Lida-se o tempo todo com os ponteiros das listas, usando
	de funções implementadas em outros módulos para complemento
	das dispostas neste.


*****************************************************************/

#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif

/**************************************************************

$TC Tipo de dados: MTZ Condições de retorno

$ED Descrição do tipo
	Condições de retorno das funções da matriz

***************************************************************/

typedef enum {

	MTZ_CondRetOK ,
		/* Concluiu corretamente */

	MTZ_CondRetVazia ,
		/* A pilha não contém valor */

	MTZ_CondRetFaltouMemoria
		/* Faltou memória ao tentar criar um elemento novo*/

} MTZ_tpCondRet;

/***********************************************************************

  $FC Função: MTZ  &Cria Matriz (Tabela)

  $ED Descrição da função
     Essa função será responsável pela criação de uma
	 matriz de listas de tamanho fornecido pelo usuário.

  $EP Parâmetros
     X	   -	Um int que é responsável pela largura da matriz.
	 Y	   -	Um int que é responsável pela altura da matriz.

  $FV Valor retornado
     A função retornará NULL caso a lista não consiga ser criada,
	 porém se houver a criação da lista, a função retornará um
	 ponteiro para a cabeça da lista.

***********************************************************************/

LIS_tppLista MTZ_criarTab(int, int);

/***********************************************************************

  $FC Função: MTZ  &Acha Coordenada

  $ED Descrição da função
     Essa função será responsável por achar uma certa coordenada
	 que o usuário informar.

  $EP Parâmetros
	Tab    -	A tabela (matriz) qual a função percorrerá.
	X	   -	Um int que representa a posição lateral.
	Y	   -	Um int que representa a posição vertical.
	Coor   -    Um ponteiro que servirá para apontar para a coordenada encontrada.

  $FV Valor retornado
     Essa função retorna um ponteiro para a coordenada passada.

***********************************************************************/

LIS_tppLista MTZ_achaCoor( LIS_tppLista , int , int );

/***********************************************************************

  $FC Função: MTZ  &Insere na Coordenada

  $ED Descrição da função
     Essa função irá procurar a coordenada fornecida pelo usuário
	 e inserir um valor na pilha que existe nela.

  $EP Parâmetros
	Tab    -	A tabela (matriz) qual a função percorrerá.
	X	   -	Um int que representa a posição lateral.
	Y	   -	Um int que representa a posição vertical.
	valor  -	O valor a ser inserido na pilha.

  $FV Valor retornado
     VOID

***********************************************************************/

MTZ_tpCondRet MTZ_pushCoor(LIS_tppLista, int, int, char);

/***********************************************************************

  $FC Função: MTZ  &Retira da Coordenada

  $ED Descrição da função
     Essa função irá procurar a coordenada fornecida pelo usuário
	 e retirar um valor na pilha que existe nela.

  $EP Parâmetros
	Tab    -	A tabela (matriz) qual a função percorrerá.
	X	   -	Um int que representa a posição lateral.
	Y	   -	Um int que representa a posição vertical.
	Valor  -    Um ponteiro que receberá o valor retirado matriz.

  $FV Valor retornado
     VOID

***********************************************************************/

char MTZ_popCoor ( LIS_tppLista, int, int);

/***********************************************************************

  $FC Função: MTZ  &Destrói Matriz

  $ED Descrição da função
     A função irá destruir e liberar os valores que tem na 
	 matriz passada.

  $EP Parâmetros
	Tab    -	A tabela (matriz) qual a função destruirá.

  $FV Valor retornado
     VOID

***********************************************************************/

MTZ_tpCondRet MTZ_DestruirMatriz ( LIS_tppLista  );


#undef MATRIZ_EXT

/********** Fim do módulo de definição: MTZ Matriz **********/

#else
#endif