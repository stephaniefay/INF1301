#if ! defined( CESPDIN_ )
#define CESPDIN_
/***************************************************************************
*
*  $MCD Modulo de definicao: CED  Controlador de espacos de dados alocados dinamicamente
*
*  Arquivo gerado:              CESPDIN.h
*  Letras identificadoras:      CED
*
*  Nome da base de software:    Arcabouco para a automacao de testes de programas redigidos em C
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\ARCABOUC.BSW
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
*     O modulo de instrumentacao CNTESPAC disponibiliza um conjunto de
*     funcoes para
*     - controlar a extravasao de espacos de dados alocados ao usuario
*     - controlar o acesso a espacos ja desalocados
*     - controlar a consistencia entre o tipo implicito de um ponteiro e o
*       tipo do espaco por ele apontado
*     - controlar o vazamento de memoria
*     - simular ter-se atingido o limite de memoria disponivel
*     - gerar aleatoriamente a falta de memoria
*     - controlar a integridade da estrutura de espacos de dados dinâmicos
*     - exibir o contecudo de espacos de dados em formato hexadecimal
*
*  $EIU Interface com o usuario pessoa
*     Para fazer com que um determinado modulo tenha todos os usos de
*     malloc e free controlados, basta incluir o modulo de definicao
*     deste modulo. Idealmente use uma construcao similar a:
*
*     #ifdef _DEBUG
*        #include "cespdin.h"
*     #endif
*
*     Isto fara com que todas as chamadas malloc e free do modulo controlado
*     sejam direcionadas para as funcoes equivalentes disponibilizadas
*     pelo presente modulo.
*
*     Para possibilitar a remocao automatica da instrumentacao
*     circunde todos os usos de funcoes desse modulo porventura existentes
*     no modulo a testar com o comando de compilacao condicional
*
*     #ifdef _DEBUG
*        comandos
*     #endif
*
*     A recompilacao do modulo instrumentado sem o nome _DEBUG
*     definido deveria resultar em zero erros de compilacao.
*     OBSERVACAO: Antes de recompilar destrua o correspondente modulo objeto,
*     para que o make nao o encontre durante a reconstrucao do construto.
*
*     Para o correto funcionamento das funcoes desse modulo, e necessario
*     que o presente modulo contenha o comando:
*
*     #pragma pack (1)
*
*     Esse comando pode introduzir dependencias de plataforma,
*     tornando nao portatil o modulo CESPDIN.
*
*     Ao mover para outra plataforma de desenvolvimento, procure
*     documentacao sobre a forma com que esta plataforma aloca espacos,
*     em particular como alinha os espacos. Apos faca os ajustes necessarios
*     possivelmente ate no struct que contem o espaco efetivamente
*     alocado (espaco instrumentado) de modo que satisfaca as regras de
*     alinhamento da nova plataforma.
*
*     Em geral, os sintomas de mau funcionamento apos a remocao de #pragma
*     sao pequenas extravasoes de espaco passarem despercebidas pela
*     instrumentacao.
*
***************************************************************************/
 
#if defined( CESPDIN_OWN )
   #define CESPDIN_EXT
#else
   #define CESPDIN_EXT extern
#endif

/***** Declaracoes exportadas pelo modulo *****/

#define     CED_PONTEIRO_NULO       -2


/***********************************************************************
*
*  $TC Tipo de dados: CED Modos de exibicao
*
*
*  $ED Descricao do tipo
*     Enumera todos os modos de listar espacos alocados
*
***********************************************************************/

   typedef enum {

         CED_ExibirTodos    = 1 ,
               /* Exibir todos os espacos */

         CED_ExibirAtivos   = 2 ,
               /* Exibir todos os espacos ativos */

         CED_ExibirInativos = 3
               /* Exibir todos os espacos inativos */

   } CED_tpModoExibir ;


/***********************************************************************
*
*  $FC Funcao: CED  &Inicializar o controlador de alocacao de espacos dinâmicos
*
*  $ED Descricao da funcao
*     Esta funcao inicializa o controlador de espacos em memoria dinâmica.
*     A funcao deve ser chamada uma única vez, antes de qualquer outra funcao
*     do modulo.
*     Sugere-se que seja chamada ao iniciar o teste do modulo controlado.
*     O interpretador de comandos de controle de espacos dinâmicos
*     prove o comando de teste  =inicializarespacos  que chama a presente
*     funcao.
*
*  $EP Parâmetros
*     $P pArqLogParm - ponteiro para o arquivo log de teste. Nao pode ser nulo.
*
***********************************************************************/

   void CED_InicializarControlador( void ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Alocar espaco
*
*  $ED Descricao da funcao
*     Nos modulos controlados esta funcao substitui a funcao "malloc".
*     A susbtituicao e transparente para o modulo controlado,
*     basta que inclua o modulo de controle de acesso a espacos de dados
*     dinâmicos. Ou seja, se o modulo de definicao "CESPDIN.H" for
*     incluido, a presente funcao sera utilizada ao chamar "malloc"
*     dentro do modulo cliente. Nao sendo incluido "CESPDIN.H", sera
*     chamada a funcao "malloc" padrao de C.
*
*     O espaco sera alocado com controle somente se o modulo de controle
*     de espaco dinâmico tiver sido inicializado, ver comando de teste
*
*         =inicializarespacos     e a correspondente funcao.
*
*     Desta forma pode-se restringir o controle somente aos modulos
*     sob teste.
*
*     O valor (parte útil do espaco alocado) e inicializado para o
*     caractere '|', permitindo a verificacao de se o valor foi
*     corretamente inicializado ou nao apos à inicializacao na funcao
*     cliente.
*
*     Para assegurar transparencia e definida a macro CED_MALLOC
*     que providencia os argumentos linha e arquivo fonte. Estes, por sua
*     vez, permitem identificar onde o espaco foi alocado, facilitando,
*     assim, resolver eventuais problemas de vazamento de memoria
*     e/ou de uso incorreto de espacos.
*
*     A funcao aloca um "struct" contendo diversos controles alem do
*     espaco útil (valor). O campo valor deste "struct" corresponde ao
*     espaco que seria alocado pela funcao de biblioteca "malloc".
*     O ponteiro retornado aponta para o campo valor, tornando
*     transparente o fato de se utilizar "malloc" ou esta funcao.
*
*     A funcao pode simular o esgotamento de memoria. Para isto e necessario
*     estabelecer um limite atraves de uma das funcoes a isto destinadas.
*     Por exemplo, se o limite de espaco alocado for diferente de zero e o
*     total de espaco ja alocado acrescido do espaco solicitado for maior
*     do que o limite estabelecido, a funcao nao aloca espaco e retorna NULL,
*     simulando falta de memoria.
*
*     A funcao pode simular esgotamento aleatorio de memoria. Para isto
*     e necessario estabelecer a freqüencia de NULLs simulados, vela o
*     comando =limitarfrequencia em INTRPCED.C
*
*     Consulte as funcoes CED_Limitar... para detalhes das formas de
*     limite que podem ser estabelecidas.
*
*  $EP Parâmetros
*     $P Tamanho          - número de bytes do valor a ser alocado.
*     $P numLinhaFonte    - número da linha do codigo fonte onde foi
*                           chamada a funcao. Use __LINE__ como argumento
*                           da chamada.
*     $P NomeArquivoFonte - nome do arquivo fonte contendo a chamada.
*                           Use __FILE__ como argumento da chamada.
*
*  $FV Valor retornado
*     Ponteiro void para o espaco útil disponibilizado para a funcao
*     cliente. O espaco útil corresponde a o que seria retornado por malloc
*
*  $EIU Interface com usuario pessoa
*     Ao inves de utilizar a funcao CED_Malloc utilize a macro CED_MALLOC
*     uma vez que esta fornece automaticamente a identificacao do local
*     onde foi realizada a chamada.
*
***********************************************************************/

   #define  CED_MALLOC( Tamanho ) \
               CED_Malloc( Tamanho , __LINE__ , __FILE__ )

   void * CED_Malloc( size_t Tamanho ,
                      int    numLinhaFonte ,
                      char * NomeArquivoFonte ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Desalocar espaco
*
*  $ED Descricao da funcao
*     Elimina o elemento da lista de controle. Todos os bytes sao tornados
*     iguais a 'x'. O identificador do tipo do espaco tambem
*     e destruido, possibilitando verificar se ele ainda esta alocado.
*
*     Ao usar esta funcao deve-se tomar o cuidado de nunca usar free para
*     desalocar um espaco controlado por este modulo.
*     Ou seja, evite o uso de malloc e free em modulos distintos em
*     que malloc esta num modulo controlado e free nao.
*     O mais seguro e ou ter todos os modulos sob controle, ou ter nenhum.
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o campo valor (espaco útil) do espaco
*                   a ser liberado
*
***********************************************************************/

   void CED_Free( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Exibir conteúdo do espaco
*
*  $ED Descricao da funcao
*     Exibe o conteudo completo de um espaco de memoria.
*     A parte útil e exibida em formato hexadecimal convencional
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o valor (parte útil) contido no espaco
*                   alocado, e o ponteiro retornado por CED_Malloc.
*
***********************************************************************/

   void CED_ExibirEspaco( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Exibir todos os espacos
*
*  $ED Descricao da funcao
*     Exibe todos os espacos que satisfazem uma determinada regra.
*     Ver o tipo CED_tpModoExibir para uma explicacao quanto às regras
*     de selecao de espacos a exibir.
*        CED_ExibirTodos     - exibe todos os espacos
*        CED_ExibirAtivos    - exibe os espacos marcados ativos
*        CED_ExibirInativos  - exibe os espacos marcados nao ativos
*
***********************************************************************/

   void CED_ExibirTodosEspacos( CED_tpModoExibir Regra ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Definir tipo do espaco
*
*  $ED Descricao da funcao
*     Caso o tipo do espaco ainda nao esteja definido, atribui o tipo.
*
*     O tipo do espaco e inicializado para CED_ID_TIPO_VALOR_NULO
*     quando da alocacao com CED_Malloc. Posteriormente pode ser
*     alterado com a presente funcao.
*
*     A atribuicao sera realizada somente se uma das condicoes a seguir
*     for verdadeira:
*     - o tipo a ser atribuido e CED_ID_TIPO_VALOR_NULO
*     - ou o tipo do espaco e CED_ID_TIPO_VALOR_NULO
*
*     Para trocar o tipo de um espaco precisa-se primeiro torna-lo
*     igual a CED_ID_TIPO_VALOR_NULO para, depois, atribuir o novo tipo.
*
*     Uma vez definido o tipo do espaco, funcoes cliente podem controlar
*     a consistencia entre o tipo implicitamente associado ao ponteiro
*     e o tipo que o espaco de fato contem.
*
*     Sugere-se que o desenvolvedor da aplicacao crie uma tabela global
*     contendo um "enum" com os nomes de todos os tipos ('typedef struct') que
*     podem ser utilizados como declaradores de espacos dinâmicos.
*     Ao definir o tipo, pode-se, agora, utilizar o nome correspondente
*     ao tipo do espaco alocado como o idTipo a ser definido. Veja
*     as explicacoes no arquivo IdTiposEspaco.def no subdiretorio Tabelas
*
*     O presente sistema de controle de tipos nao preve mecanismos para
*     tratamento de heranca.
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o campo valor (espaco útil) do espaco
*                   a ser tipado
*     $P idTipo   - novo identificador de tipo a ser dado ao espaco.
*
*  $FV Valor retornado
*     TRUE   1    - se a atribuicao foi bem sucedida
*     FALSE  0    - se nao foi possivel atribuir. Isto sera o caso se
*                   o tipo do espaco ja estava definido ao chamar a funcao,
*                   ou se o ponteiro for NULL.
*
***********************************************************************/

   int CED_DefinirTipoEspaco( void * Ponteiro , int idTipo ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Marcar ativo o espaco
*
*  $ED Descricao da funcao
*     Marca determinado espaco como ativo.
*
*     A marca ativo/nao ativo e utilizada para apoiar o controle de
*     vazamento de memoria. Siga o seguinte roteiro:
*     - Marque todos os espacos nao ativos.
*     - A partir das âncoras, percorra as estruturas ativas marcando
*       ativos os espacos visitados. Este percorrimento e recursivo.
*       Retorna-se da chamada se encontrar um espaco ja marcado ativo, ou
*       se nao tiver para onde caminhar. Note que para poder fazer isto
*       e necessario conhecer-se o tipo dos dados contidos em cada um
*       dos espacos alocados.
*     - Percorra a lista de todos os espacos verificando se cada espaco
*       visitado e ou nao inativo. Os nao ativos provavelmente correspondem
*       a vazamento de memoria.
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o campo valor (espaco útil) do espaco
*                   a ser marcado
*
***********************************************************************/

   void CED_MarcarEspacoAtivo( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Marcar nao ativo o espaco
*
*  $ED Descricao da funcao
*     Ver CED_MarcarEspacoAtivo
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o campo valor (espaco útil) do espaco
*                   a ser marcado
*
***********************************************************************/

   void CED_MarcarEspacoNaoAtivo( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Marcar nao ativos todos os espacos
*
*  $ED Descricao da funcao
*     Percorre todos os espacos alocados marcando-os inativos.
*
*     Veja: CED_MarcarEspacoAtivo
*
***********************************************************************/

   void CED_MarcarTodosEspacosInativos( ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Limitar memoria disponivel
*
*  $ED Descricao da funcao
*     Estabelece um limite de memoria disponivel. Este limite afeta
*     o comportamento da funcao CED_Malloc.
*
*     Embora a funcao possa ser chamada a qualquer momento, recomenda-se
*     que seja chamada antes do primeiro caso de teste capaz de alocar
*     espaco de memoria dinâmica por intermedio da funcao CED_Malloc
*     contida nesse modulo.
*
*  $EP Parâmetros
*     $P NovoLimiteMemoria - Estabelece o limite de memoria disponivel.
*                            Caso seja zero, o controle de limite nao
*                            sera efetuado por CED_Malloc.
*
***********************************************************************/

   void CED_LimitarMemoriaDisponivel( long NovoLimiteMemoria ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Limitar número de espacos alocados
*
*  $ED Descricao da funcao
*     Limita o número de espacos alocados. Esta funcao afeta o comportamento
*     de CED_Malloc, estabelecendo um limite para o número total de
*     espacos alocados em um dado momento.
*
*     Embora a funcao possa ser chamada a qualquer momento, recomenda-se
*     que seja chamada antes do primeiro caso de teste que provoque
*     alocacao de espaco de memoria.
*
*  $EP Parâmetros
*     $P numTotalEspacos - indica o limite de espacos que podem estar
*                          alocados a cada instante. Se zero, nao
*                          sera realizado o controle.
*
***********************************************************************/

   void CED_LimitarNumeroTotalEspacos( long numTotalEspacos ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Limitar com freqüencia de geracao de NULL
*
*  $ED Descricao da funcao
*     Esta funcao estabelece a freqüencia com a qual nao devera ser
*     gerado NULL, o complemento a esta freqüencia e a frequüencia com
*     a qual devera ser retornado NULL (nao aloca) independentemente da
*     existencia ou nao de memoria disponivel.
*     A funcao visa apoiar a verificacao de se o comportamento de um
*     programa leva em conta os retornos de falta de memoria.
*
*  $EP Parâmetros
*     $P Frequencia - e um inteiro 10 <= Frequencia < 1000 e que indica
*                     a freqüencia em cada 1000 alocacoes em que memoria
*                     sera alocada. Exemplo: para que 95% das vezes
*                     ocorra alocacao, forneca o parâmetro 950, ja se for
*                     desejado que ocorra em 99,9% das vezes, forneca
*                     999. Se zero, nao sera realizada a simulacao de
*                     falta de memoria.
*
*  $FV Valor retornado
*     TRUE   se tiver sido estabelecido o limite por freqüencia
*     FALSE  se tiver ocorrido algum erro
*
***********************************************************************/

   int CED_LimitarFrequencia( int Frequencia ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Limitar, eliminar limites
*
*  $ED Descricao da funcao
*     Esta funcao elimina todos os limites de memoria por ventura em vigor.
*
***********************************************************************/

   void CED_EliminarLimites( ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Obter o tipo do espaco de dados
*
*  $ED Descricao da funcao
*     Retorna o identificador do tipo do espaco apontado.
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o campo valor (espaco útil) do espaco
*                   do qual se deseja saber o tipo
*
*  $FV Valor retornado
*     Tipo do valor retornado, cajo tenha sido definido
*
*        CED_ID_TIPO_ESPACO_NULO  se nunca foi atribuido um tipo ao espaco
*        CED_ID_TIPO_ILEGAL       se o espaco nao corresponder a um espaco
*                                 controlado pelo modulo CESPDIN
*        CED_PONTEIRO_NULO        se o parâmetro Ponteiro for NULL
*
***********************************************************************/

   int CED_ObterTipoEspaco( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Obter tamanho do valor contido no espaco
*
*  $ED Descricao da funcao
*     Retorna o número de bytes úteis do espaco
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para a porcao útil do espaco
*                   da qual se deseja saber o tamanho
*
***********************************************************************/

   int CED_ObterTamanhoValor( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Obter número de espacos alocados
*
*  $ED Descricao da funcao
*     Retorna o número de elementos da lista de espacos alocados
*
***********************************************************************/

   int CED_ObterNumeroEspacosAlocados( ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Obter total de espacos alocados
*
*  $ED Descricao da funcao
*     Retorna o número total de vezes que foi chamada a funcao
*     CED_Malloc.
*
***********************************************************************/

   int CED_ObterTotalAlocacoes( ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Obter número total de NULLs gerados
*
*  $ED Descricao da funcao
*     Retorna o número de NULLs retornados em virtude de limitacoes impostas.
*     Veja as funcoes CED_LimitarXXX
*
***********************************************************************/

   long CED_ObterNumNULL( void ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Obter número de espacos segundo regra
*
*  $ED Descricao da funcao
*     Obtem o número de elementos contidos na lista de espacos alocados,
*     segundo a regra:
*        CED_ExibirTodos     - exibe todos os espacos
*        CED_ExibirAtivos    - exibe os espacos marcados ativos
*        CED_ExibirInativos  - exibe os espacos marcados nao ativos
*
***********************************************************************/

   int CED_ObterNumeroEspacos( CED_tpModoExibir Regra ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Obter espaco total alocado
*
*  $ED Descricao da funcao
*     Obtem o total, em bytes, de espacos úteis alocados.
*
***********************************************************************/

   long CDE_ObterEspacoTotalAlocado( ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Iterador: iniciar iterador de espacos
*
*  $ED Descricao da funcao
*     Inicia o iterador com o primeiro espaco da lista de controle de espacos
*     dinâmicos.
*
*     O iterador pode ser utilizado para verificar a integridade dos
*     espacos de dados sob controle do modulo. Para isto a funcao de
*     verificacao de espacos deve percorrer todos os espacos alocados
*     disparando o controle individual para cada um deles.
*     Pode-se tambem simular um garbage collector, percorrendo todos
*     os espacos e marca-los inativos. Depois percorrer, a partir
*     das ancoras, todos os espacos adjacentes, marcando ativos os
*     espacos visitados. Evidentemente se ja estiver marcado ativo
*     retorna-se para tratar do proximo estado pendente na pilha.
*     Ao final, os espacos que ainda estiverem marcados inativos
*     correspondem a vazamento de memoria.
*
***********************************************************************/

   void CED_InicializarIteradorEspacos( ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Iterador: avancar para o proximo espaco
*
*  $ED Descricao da funcao
*     Avanca o iterador para o proximo espaco.
*
*  $FV Valor retornado
*     TRUE  caso o espaco para o qual caminhou existe.
*     FALSE se nao existe iterador ou chegou ao fim da lista de espacos
*
***********************************************************************/

   int CED_AvancarProximoEspaco( ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Iterador: obter referencia para o espaco corrente
*
*  $ED Descricao da funcao
*     Obtem a referencia para a parte útil do espaco corrente.
*
***********************************************************************/

   void * CED_ObterPonteiroEspacoCorrente( ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Iterador: existe espaco corrente
*
*  $ED Descricao da funcao
*     Verifica se o iterador referencia um espaco corrente.
*     Caso retorne FALSE, o iterador chegou ao final da lista de espacos
*     ou, entao, ainda nao foi inicializado.
*
***********************************************************************/

   int CED_ExisteEspacoCorrente( ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Iterador: terminar iterador
*
*  $ED Descricao da funcao
*     Desativa o iterador. A referencia para o espaco corrente passa
*     a ser NULL.
*
***********************************************************************/

   void CED_TerminarIteradorEspacos( ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Iterador: excluir espaco corrente
*
*  $ED Descricao da funcao
*     Elimina o espaco corrente da lista de espacos controlados.
*     O espaco e liberado tornando ilegais todos os acessos realizados
*     por funcoes do usuario.
*     Na realidade esta funcao corresponde a um CED_Free.
*     Utilize esta funcao somente para para eliminar espacos sabidamente
*     inativos, ou para deturpar ao testar reacoes a anomalias em estruturas
*     de dados.
*
***********************************************************************/

   void CED_ExcluirEspacoCorrente( ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Verificar se espaco e ativo
*
*  $ED Descricao da funcao
*     Retorna TRUE se o espaco referenciado esta marcado ativo
*
*  $EP Parâmetros
*     $P Ponteiro - ponteiro para o campo valor (espaco útil) do espaco
*                   do qual se deseja saber se e ativo ou nao
*
***********************************************************************/

   int CED_EhEspacoAtivo( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Verificar a integridade de um espaco de dados
*
*  $ED Descricao da funcao
*     Verifica a integridade de um determinado espaco de dados.
*     Retorna o número de falhas encontradas.
*     Esta funcao pode levar a um cancelamento do programa, caso o ponteiro
*     fornecido esteja errado.
*
*  $EP Parâmetros
*     $P Ponteiro para a porcao útil do espaco. Este e o ponteiro
*                 retornado pela funcao CED_Malloc
*
*     $P int pVerificarValor( void * pValor )
*                 funcao fornecida pelo cliente para verificar a corretude
*                 do espaco útil. A funcao recebe como parâmetro um
*                 ponteiro para o espaco a verificar e deve retornar
*                      0 caso o espaco nao esteja correto e
*                   != 0 se estiver correto.
*                 Todas as mensagens de erro devem ser dadas
*                 pela funcao de verificacao. Procure utilizar as
*                 funcoes do modulo GENERICO para exibir as mensagens
*                 e realizar as comparacoes.
*                 Caso nao deseje verificar o valor, forneca NULL como
*                 argumento.
*
*  $FV Valor retornado
*     TRUE   se espaco e valido ou o ponteiro for NULL
*     FALSE  se nao for um espaco controlado pelo modulo CESPDIN, ou
*            se o conteúdo do espaco total nao for valido
*
***********************************************************************/

   int CED_VerificarEspaco( void * Ponteiro ,
                            int ( * pVerificarValor )( void * pValor )) ;


/***********************************************************************
*
*  $FC Funcao: CED  &Verificar todos os espacos alocados
*
*  $ED Descricao da funcao
*     Percorre toda a lista, verificando um a um os espacos.
*     Caso um ou mais espacos estejam errados, pode ocorrer
*     cancelamento da execucao em virtude de acesso a memoria ilegal.
*
*  $EP Parâmetros
*     $P pVerificarValor - e o ponteiro para uma funcao que verifica o conteúdo
*                          do espaco útil. O parâmetro pValor dessa funcao
*                          apontara para o valor a ser controlado
*
*  $FV Valor retornado
*     TRUE   se todos os espacos estao validos
*     FALSE  caso contrario
*
***********************************************************************/

   int CED_VerificarTudo( int ( * pVerificarValor )( void * pValor )) ;

/***********************************************************************

/* Codigo final do modulo */

#if !defined( CESPDIN_OWN )
   #define malloc CED_MALLOC
   #define free   CED_Free
#endif

#undef CESPDIN_EXT

/********** Fim do modulo de definicao: CED  Controlador de espacos de dados alocados dinamicamente **********/

#else
#endif
