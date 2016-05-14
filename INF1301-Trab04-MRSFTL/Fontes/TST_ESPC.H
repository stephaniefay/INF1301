#if ! defined( TST_ESPC_ )
#define TST_ESPC_
/***************************************************************************
*
*  $MCD Modulo de definicao: TSTE Interface de teste especifico
*
*  Arquivo gerado:              TST_ESPC.H
*
*  Nome da base de software:    Arcabouco para a automacao de testes de programas redigidos em C
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\INSTRUM.BSW
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
*     Este modulo consta somente do modulo de definicao de todos os modulos
*     de teste especificos a serem desenvolvidos, e tambem da especificacao
*     do tipo de condicoes de retorno deste modulo.
*
*     Ele estabelece a interface a ser utilizada pelo modulo de teste
*     generico com todos os modulos de teste especifico a serem
*     desenvolvidos.
*
*     Os modulos de teste especifico devem sempre incluir este modulo
*     de definicao e, idealmente, nao devem adicionar mais itens
*     à interface.
*
***************************************************************************/
 
#if defined( Tst_Espc_OWN )
   #define Tst_Espc_EXT
#else
   #define Tst_Espc_EXT extern
#endif

/***** Declaracoes exportadas pelo modulo *****/

#define     SINALIZA_ERRO       ">>>"
#define     SINALIZA_RECUPERA   "<<<"
#define     SINALIZA_COMENTARIO "!!!"


/***********************************************************************
*
*  $TC Tipo de dados: TST Condicoes de retorno do modulo de teste
*
*
*  $ED Descricao do tipo
*     Este tipo enumera todas as condicoes de retorno que podem ser
*     geradas pela funcao de teste especifica.
*
***********************************************************************/

   typedef enum {

         TST_CondRetOK ,
               /* Comando de teste executou corretamente */

         TST_CondRetErro ,
               /* Comando de teste encontrou uma ou mais falhas
               *
               *$ED Descricao
               *   Esta condicao sinaliza que um ou mais resultados da execucao
               *   da funcao sob teste resultou em um valor diferente do esperado. */

         TST_CondRetParm ,
               /* Comando de teste esta com a sintaxe em erro
               *
               *$ED Descricao
               *   A presente condicao de retorno deve ser retornada caso a sintaxe
               *   ou os valores do comando de teste estiverem em erro.
               *
               *   Todos os fragmentos de interpretacao devem:
               *   - realizar a analise dos parâmetros do comando
               *   - verificar se todos os parâmetros foram lidos
               *   - verificar se os valores dos parâmetros estao corretos
               *     por exemplo: verificar se os indices de acesso a elementos
               *     estao dentro dos limites dos correspondentes vetores.
               *   - efetuar a funcao a testar
               *   - verificar se os resultados retornados por esta funcao estao
               *     corretos */

         TST_CondRetNaoExecutou ,
               /* Comando de teste nao se destina ao presente interpretador
               *
               *$ED Descricao
               *   Esta condicao deve ser retornada por todas as funcoes de interpretacao
               *   de comandos de teste relativas a modulos do proprio arcabouco,
               *   caso nao tenha sido encontrado um comando valido. Isso permite
               *   estabelecer um "daisy chain" de interpretadores em que cada qual
               *   tenha finalidade especifica no contexto do arcabouco. */

         TST_CondRetNaoConhec ,
               /* Comando de teste nao e conhecido
               *
               *$ED Descricao
               *   Esta condicao deve ser retornada por todas as funcoes de interpretacao
               *   de casos de teste especifico visando determinado modulo em teste,
               *   sempre que esse interpretador nao consiga identificar o comando.
               *
               *   Cabe salientar a diferenca entre TST_CondRetNaoExecutou e
               *   TST_CondRetNaoConhec. A primeira corresponde à nao interpretacao
               *   de um comando possivelmente valido em interpretadores subsequentes.
               *   A segunda corresponde a comandos nao validos considerando todos
               *   os interpretadores. */

         TST_CondRetNaoImplementado ,
               /* Comando de teste nao implementado
               *
               *$ED Descricao
               *   Esta condicao deve ser retornada ao interpretar um comando de teste
               *   especifico ainda nao implementado.
               *
               *   Recomenda-se que o desenvolvimento dos modulos sob teste e do
               *   correpondente modulo de teste especifico se de incrementalmente.
               *   Consequentemente diversos comandos nao estarao implementados
               *   no inicio do desenvolvimento. Esta incompleteza podera ser
               *   sinalizada com esta condicao de retorno. */

         TST_CondRetMemoria
               /* Faltou memoria para executar o comando
               *
               *$ED Descricao
               *   Esta condicao deve ser retornada caso tenha ocorrido algum erro
               *   quando o modulo de teste especifico tentar alocar memoria ou
               *   outro recurso. */

   } TST_tpCondRet ;


/***********************************************************************
*
*  $FC Funcao: TSTE &Efetuar comandos de teste especificos
*
*  $ED Descricao da funcao
*     Efetua os diversos comandos de teste especificos para o modulo
*     sendo testado.
*
*     Cada modulo de teste especifico deve desenvolver esta funcao.
*     Podera conter diversas outras conforme necessario. No entanto
*     estas devem todas ser funcoes encapsuladas no modulo (static)
*
*     Freqüentemente e necessario desenvolver um contexto para o teste.
*     Por exemplo, pode ser necessario tratar n elementos disponibilizados
*     pelo modulo sob teste. Neste caso deveria ser criado um vetor
*     global com referencias para estas elemento. Ao iniciar os teste
*     este vetor devera ser inicializado. Ao terminar, os elementos do
*     vetor referenciando algum elemento devem ser destruidos.
*
*     Uma das formas para estabelecer o contexto seria a de incluir
*     no mcodulo de teste especifico comando semelhantes a:
*
*       =iniciaXXX  que inicializa o contexto do modulo sob teste para
*                   vazio. Este comando deve ser utilizado uma única vez
*                   logo ao inciar a execucao do teste.
*       =reset      restaura o contexto para vazio. Este comando usualmente
*                   assumira que o contexto a esvaziar esteja correto.
*                   O comando devera liberar os espacos alocados aos
*                   elementos, anular as referencias a ele, inicializar
*                   valores de vetores de referencias, etc.
*                   O comando tem utilidade especial ao segmentar um teste
*                   em partes estanques e ao controlar vazamento de
*                   memoria.
*       =terminaXXX este comando destroi todo o contexto e nao o
*                   reinicializa. O objetivo e poder verificar vazamento
*                   de memoria.
*
*     Evidentemente, outra forma seria a de alterar as funcoes de
*     inicializacao e termino do modulo de teste generico o que e pouco
*     recomendavel pois viola o principio de um mesmo modulo generico
*     servir para testar todos os construtos.
*
*     Para cada funcao do modulo a ser testado deve existir pelo menos
*     um comando. Em alguns casos pode ser interessante criar
*     comandos que armazenem, alterem ou consultem variaveis de
*     estado do proprio modulo de teste. Ver os comentarios sobre
*     contexto acima.
*
*     Todos os controles de consistencia devem ser realizados no
*     modulo de teste especifico.
*
*     A funcao TST_EfetuarComando( ) deve retornar as condicoes de retorno
*     identificadas no tipo TST_tpCondRet definida no modulo TesteGen.
*
*     As funcoes do modulo sob teste que retornam algum valor sempre
*     devem sempre ter este valor verificado, mesmo sendo uma condicao de
*     retorno. Para fazer a vereficacao da corretude, recomenda-se
*     utilizar as funcoes TST_CompararXXX definidas no modulo generico.
*     Assegura-se assim a uniformidade da saida gerada durante o teste.
*
*     Para realizar a analise de um comando de teste recomenda-se
*     utilizar as funcoes definidas no modulo LerParm. Elas, alem
*     de realizarem a analise lexica, permitem o uso intercambiavel
*     de parâmetros simbolicos ou literais. Tambem realizam a
*     verificacao da corretude dos tipos dos parâmetros, contribuindo
*     assim para a reducao de erros de redacao de scripts de teste
*     que possam passar despercebidos.
*
*     As funcoes a serem testadas que requeiram algum argumento, devem
*     ser chamadas com valores (parâmetros) extraidos do comando de
*     teste sendo executado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     TST_CondRetXXX       - veja a descriocao dos possiveis valores
*                            retornados na especificacao do correspondente
*                            enum
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ) ;

#undef Tst_Espc_EXT

/********** Fim do modulo de definicao: TSTE Interface de teste especifico **********/

#else
#endif
