#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD Módulo de definição: GRA  Grafo
*
*  Arquivo gerado:              GRAFO.H
*  Letras identificadoras:      GRA
*
*  Projeto: INF 1301 Trabalho II
*  Gestor:  Grupo Stephanie Fay e Pedro Paulo
*  Autores: Stephanie, Pedro
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       SF     3/out/2013 Primeira versão
*     2       PP    10/out/2013 Correção de comentários e do protótipo
*                                da função GRA_obterCorr
*
*  $ED Descrição do módulo
*     Implementa grafo que possui arestas, vertices e uma cabeça de grafo.
*     Podem existir N vertices criados.
*     Podem existir N arestas relacionando os vertices.
*     Os grafos possuem uma cabeça encapsulando o seu estado.
*
*     Cada elemento do grafo pode armazenar uma string.
*
*     Cada vértice está contido numa lista de vértices.
*        Esta lista utiliza o modulo LIS
*
*     Há uma lista de Origem, com origens do Grafo, de sucessores e antecessores.
*		 Estas listas utilizam o modulo LIS
***************************************************************************/
 

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */

typedef struct GRA_tagGrafo * GRA_tppGrafo ;
typedef struct GRA_ElemGrafo * GRA_tppElemento;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do grafo
*
***********************************************************************/

typedef enum {

         GRA_CondRetOK = 0 ,
               /* Concluiu corretamente */

         GRA_CondRetNaoAchou = 1 ,
               /* Não encontrou o valor procurado */

         GRA_CondRetFaltouMemoria = 2 ,
               /* Faltou memória ao tentar criar um elemento de lista */
   
         GRA_CondRetGrafoNaoExiste = 3 ,
               /* Grafo passado por parametro nao existe */

         GRA_CondRetVerticeCorrNaoExiste = 4 ,
               /* Vertice corrente nao existe */

         GRA_CondRetArestaNaoExiste = 5 ,
               /* Nao existe aresta entre o vertice corrente e o passado por parametro */

         GRA_CondRetArestaJaExiste = 6 ,
               /* Ja existe aresta entre o vertice corrente e o passado por parametro */

         GRA_CondRetParamInvalido = 7 ,
               /* Um ou mais parametros passados para funcao sao invalidos */

   } GRA_tpCondRet ;
   

/***********************************************************************
*
*  $FC Função: GRA  &Criar Grafo
*
*  $ED Descrição da função
*     Cria um grafo de char.
*     Ao criar o grafo a funcao cria uma cabeca da lista de vertices e inicializa
*     o ponteiro do vertice corrente com NULL, indicando que ele ainda nao foi definido.
*
*  $EP Parâmetros
*
*     parmGrafo     - Ponteiro do tipo cabeça de grafo que será inicializado.

*  $FV Valor retornado
*     GRA_CondRetParamInvalido - falha do parametro de entrada
*                                
*     GRA_CondRetFaltouMemoria - faltou memoria ao alocar a cabeca do grafo ou
*                                a cabeca da lista de vertices
*     GRA_CondRetOK            - foi alocada a cabeca do grafo e a cabeca da lista
*                                de vertices corretamente. Assim como o encapsulamento
*                                das funcoes passadas por parametro.
*
***********************************************************************/

GRA_tpCondRet GRA_criarGrafo ( GRA_tppGrafo parmGrafo );

/***********************************************************************
*
*  $FC Função: GRA  &Ir Vértice
*
*  $ED Descrição da função
*		
*       Modifica o ponteiro de vertice corrente para o vertice cujo identificador
*       foi passado por parametro.
*
*  $EP Parâmetros
*
*     parmGrafo     - Ponteiro do tipo cabeça de grafo.
*
*     id   - Identificador de vertice
*
*  $FV Valor retornado
*     GRA_CondRetParamInvalido        - identificador do vertice passado por parametro nao eh valido
*     GRA_CondRetVerticeCorrNaoExiste - vertice corrente nao existe
*     GRA_CondRetArestaNaoExiste      - aresta para vertice solicitado nao existe
*     GRA_CondRetOK                   - ponteiro corrente agora aponta para vertice
*                                       cujo identificador foi passado por parametro
*
***********************************************************************/

GRA_tpCondRet GRA_irVertice ( GRA_tppGrafo parmGrafo , int id );

/***********************************************************************
*
*  $FC Função: GRA  &Cria Vértice
*
*  $ED Descrição da função
*		
*     Cria um vertice com o dado valor e ID no final da lista vertices.
*
*  $EP Parâmetros
*
*     parmGrafo     - Ponteiro do tipo cabeça de grafo.
*
*
*     id   - Identificador de vertice
*
*  $FV Valor retornado
*     GRA_CondRetFaltouMemoria        - nao foi possivel alocar memoria para as estruturas
*     GRA_CondRetOK                   - vertice foi criado com sucesso
*
***********************************************************************/

GRA_tpCondRet GRA_criaVertice ( GRA_tppGrafo parmGrafo , char * parmValor, int id );

/***********************************************************************
*
*  $FC Função: GRA  &Destruir Vértice Corrente
*
*  $ED Descrição da função
*		
*       Destroi o vertice que está sendo apontado pela cabeça de grafo.
*		Faz as devidas ligações na lista vértices para manter a consistência da mesma.
*
*  $EP Parâmetros
*
*     parmGrafo     - Ponteiro do tipo cabeça de grafo.

*
*  $FV Valor retornado
*     GRA_CondRetGrafoNaoExiste       - grafo passado por parametro nao eh valido
*     GRA_CondRetNaoAchou             - vertice buscado nao foi encontrado
*     GRA_CondRetOK                   - vertice destruido com sucesso
*
*
*
***********************************************************************/

GRA_tpCondRet GRA_destruirVertice ( GRA_tppGrafo parmGrafo );

/***********************************************************************
*
*  $FC Função: GRA  &Destruir Aresta
*
*  $ED Descrição da função
*		
*       Destroi a aresta que aponta para os devidos IDs desponibilizados.
*
*  $EP Parâmetros
*
*     Grafo     - Ponteiro do tipo cabeça de grafo.
*
*     antecessor   - Identificador de vertice
*
*     sucessor   - Identificador de vertice
*
**  $FV Valor retornado
*     GRA_CondRetParamInvalido        - identificador do vertice passado por parametro nao eh valido
*
*     GRA_CondRetNaoAchou             - vertice buscado nao foi encontrado
*     GRA_CondRetOK                   - aresta foi criado com sucesso
*
***********************************************************************/


GRA_tpCondRet GRA_destruirAresta ( GRA_tppGrafo Grafo, int antecessor, int sucessor );

/***********************************************************************
*
*  $FC Função: GRA  &Criar Aresta
*
*  $ED Descrição da função
*		
*       Cria a aresta que aponta o vértice corrente ao vértice dado.
*
*  $EP Parâmetros
*
*     Grafo     - Ponteiro do tipo cabeça de grafo.
*
*     id   - Identificador de vertice
*
*     tipo   
*  $FV Valor retornado
*     GRA_CondRetGrafoNaoExiste       - grafo passado por parametro nao eh valido
*     GRA_CondRetParamInvalido        - identificador do vertice passado por parametro nao eh valido
*     GRA_CondRetVerticeCorrNaoExiste - vertice corrente nao existe
*     GRA_CondRetFaltouMemoria        - nao foi possivel alocar memoria para as estruturas
*     GRA_CondRetNaoAchou             - vertice buscado nao foi encontrado
*     GRA_CondRetOK                   - aresta foi criado com sucesso
*
***********************************************************************/

GRA_tpCondRet GRA_criarAresta ( GRA_tppGrafo Grafo, int id, char*  tipo );

/***********************************************************************
*
*  $FC Função: GRA  &Destruir Grafo
*
*  $ED Descrição da função
*		
*       Destroi o grafo dado e libera a memoria ocupada por todas
*       as suas estruturas.
*
*  $EP Parâmetros
*
*     parmGrafo     - Ponteiro do tipo cabeça de grafo
*
*  $FV Valor retornado
*     GRA_CondRetGrafoNaoExiste       - grafo passado por parametro nao eh valido
*     GRA_CondRetOK                   - grafo destruido com sucesso
*
*
*
*
***********************************************************************/

GRA_tpCondRet GRA_destruirGrafo ( GRA_tppGrafo parmGrafo ) ;

/***********************************************************************
*
*  $FC Função: GRA  &Obter Vertice Corrente
*
*  $ED Descrição da função
*		
*       Retorna a informação guardada no vertice corrente
*
*  $EP Parâmetros
*
*     parmGrafo     - Ponteiro do tipo cabeça de grafo.
*
*     ppValor       - Ponteiro para variavel do tipo ponteiro generica
*
*  $FV Valor retornado
*     GRA_CondRetGrafoNaoExiste       - grafo passado por parametro nao eh valido
*     GRA_CondRetParamInvalido        - ponteiro para variavel que armazenara a informacao
*                                       retornada eh invalido
*     GRA_CondRetVerticeCorrNaoExiste - vertice corrente nao existe
*     GRA_CondRetOK                   - valor obtido com sucesso
*
***********************************************************************/

GRA_tpCondRet GRA_obterCorr ( GRA_tppGrafo parmGrafo , char * valor ) ;

/***********************************************************************
*
*  $FC Função: GRA  &Ir Origem
*
*  $ED Descrição da função
*		
*       Vai para uma dada origem do Grafo
*
*  $EP Parâmetros
*
*     Grafo               - Ponteiro do tipo cabeça de grafo.
*
*     identificador       - Identificador para a escolha da origem
*
*  $FV Valor retornado
*     GRA_CondRetGrafoNaoExiste       - grafo passado por parametro nao eh valido
*     GRA_CondRetParamInvalido        - ponteiro para variavel que armazenara a informacao
*                                       retornada eh invalido
*     GRA_CondRetOK                   - valor obtido com sucesso
*
***********************************************************************/

GRA_tpCondRet GRA_IrOrigem ( GRA_tppGrafo Grafo, int verificador ) ;

/***********************************************************************
*
*  $FC Função: GRA  &Avançar Elemento Corrente
*
*  $ED Descrição da função
*		
*       Avança uma dada quantidade de vezes o ponteiro corrente do Grafo
*
*  $EP Parâmetros
*
*     Grafo         - Ponteiro do tipo cabeça de grafo.
*
*     id            - Contador para avanço no grafo.
*
*  $FV Valor retornado
*     GRA_CondRetGrafoNaoExiste       - grafo passado por parametro nao eh valido
*     GRA_CondRetParamInvalido        - ponteiro para variavel que armazenara a informacao
*                                       retornada eh invalido
*     GRA_CondRetOK                   - valor obtido com sucesso
*
***********************************************************************/

GRA_tpCondRet GRA_AvancaElemCorrente (GRA_tppGrafo Grafo, int id ) ;




#undef GRAFO_EXT

/********** Fim do módulo de definição: GRA  Grafo **********/

#else
#endif