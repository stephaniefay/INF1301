#if ! defined( CONTA_ )
#define CONTA_
/***************************************************************************
*
*  $MCD Modulo de definicao: CNT  Contadores de passagem
*
*  Arquivo gerado:              CONTA.h
*  Letras identificadoras:      CNT
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
*     Este modulo implementa funcoes para o controle de cobertura dos
*     testes de modulos. O controle de cobertura baseia-se
*     em contagem de passagens
*
*     Contadores sao identificados por nomes simbolicos, um string.
*     Para assegurar o controle efetivoo, deve ser criado um arquivo
*     com todos os nomes de contadores definidos no modulo a testar.
*     Este arquivo devera ser lido antes de iniciar os testes.
*     Ao final a tabela de simbolos pode ser examinada à procura de
*     contadores que nao tenham sido contados durante a execucao do
*     teste.
*
*     Os modulos a serem medidos devem ser marcados com chamadas para
*     a funcao de contagem disponibilizada pelo presente modulo:
*        CNT_Conta( <nome> ) ;
*     em que <nome> e um dos nomes que figura no arquivo de contagem.
*     Deve-se assegurar que todas as chamadas utilizem nomes diferentes
*     dos demais nomes utilizados em outras chjamadas a esta funcao.
*
*     Os contadores podem ser inicializados com valores. Os seguintes
*     valores tem significado especial:
*        -1 - contador opcional. Caso o teste nao passe pela correspondente
*             chamada à funcao de contagem, o sistema nao acusara
*             erro de falta de cobertura.
*        -2 - contador proibido. Deve ser utilizado para marcar os
*             fragmentos de codigo que em uma execucao correta normal
*             jamais devem ser executados. Estes fragmentos correspondem
*             tipicamente ao codigo de controle de integridade da execucao.
*
*     O arquivocontem dados por linha de texto. Cada linha de texto
*     podera ser um de:
*
*       // comentario - linha de comentario
*
*       linha em branco
*
*       nome/=numero  - definicao de um contador.
*                       nome e o string que identifica o contador
*                       /= e o operador de inicializacao, opcional
*                       numero e o valor inicial a ser atribuido
*                              so pode ser fornecido se o operador /=
*                              for fornecido
*
*     Os contadores podem ser acumulados em arquivos de totatilzacao.
*     Isto permite controlar a cobertura dos testes quando forem
*     utilizadas varias massas (scripts) de teste.
*     O arquivo de totalizacao tem o mesmo formato que o de definicao
*     de contadores.
*
*     Antes de iniciar a execucaos dos testes deve ser lido o arquivo
*     de definicao de contadores e, se for o caso, identificado
*     o arquivo de totalizacao.
*
*     Ao terminar os testes deve ser verificada a cobertura medida.
*     Caso esta nao seja integral, as massas de teste devem ser
*     corrigidas de modo que a cobertura passe a ser integral.
*
*     Veja os comandos de teste
*        =inicializarcontadores
*        =lerarquivocontadores
*     definidos no modulo de interpretacao de comandos de contagem
*
*        INTCNT
*
*  $EIU Interface com o usuario pessoa
*     Ao desenvolver modulos que deverao ser medidos siga as
*     seguintes instrucoes:
*
*     - Assegure que a funcao CNT_InicializarContadores seja
*       chamada antes de iniciar a medicao
*
*     - Assegure que a funcao de declaracao de contadores seja
*       lida antes de iniciar a medicao
*
*     - Assegure que a funcao CNT_IniciarContagem seja chamada
*       ao iniciar a execucao do codigo a ser medido
*
*     - Dependendo do modo de medir inclua no modulo a medir
*       o fragmento
*          #ifdef _DEBUG
*             CNT_CONTAR( NomeContador ) ;
*          #endif
*
*     - Assegure que cada chamada a esta funcao referencie um
*       contador nao referenciado pelas demais chamadas.
*
*     - Ao terminar a execucao da porcao de codigo a medir
*       chame a funcao CNT_PararContagem
*
*     - Antes de terminar a execucao chame a funcao CNT_VerificarContagem
*       Esta funcao listara todos os contadores que contenham zero,
*       ou seja que nao tenham figurado em uma chamada para
*       CNT_CONTAR no decorrer da execucao.
*
*     Este processo pode ser modificado no caso de se querer realizar
*     outras formas de contagem.
*
***************************************************************************/
 
#if defined( CONTA_OWN )
   #define CONTA_EXT
#else
   #define CONTA_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: CNT Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         CNT_CondRetOK = 0 ,
               /* CNT retornou normal */

         CNT_CondRetErro = -11 ,
               /* CNT Encontrou erro */

         CNT_CondRetNaoContador = -12 ,
               /* CNT Contador nao existe */

         CNT_CondRetOpcional = -13 ,
               /* CNT Contador e opcional */

         CNT_CondRetProibido = -14 ,
               /* CNT Contador nao pode ser contado */

         CNT_CondRetInicializado = -15 ,
               /* CNT Modulo contador ja inicializado */

         CNT_CondRetNaoInicializado = -16 ,
               /* CNT Modulo contador nao inicializado */

         CNT_CondRetNaoIterador = -17
               /* CNT Iterador lista ordenada nao incializado */

   } CNT_tpCondRet ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Inicializar contadores
*
*  $ED Descricao da funcao
*     Esta funcao inicializa uma secao de contagem.
*     Uma aplicacao pode conter diversas secoes de contagem mutuamente
*     independentes.
*     Esta funcao deve ser chamada exatamente uma vez no inicio de
*     cada secao.
*     Ao final da secao deve ser chamada a funcao
*        CNT_TerminarContadores
*
*  $EP Parâmetros
*     $P pArqLog  - ponteiro FILE * apontando para o arquivo log
*                   em uso. Todas as mensagens sao gravadas no arquivo log.
*                   Se este ponteiro for NULL sera utilizado o arquivo
*                   stdout.
*
*     $P NomeArquivo - ponteiro para o nome do arquivo de contagem
*                   acumulada. Se NULL ou se nao conseguir abrir,
*                   nao existe arquivo de contagem acumulada.
*                   Neste caso deve ser lido o arquivo de definicao
*                   de nomes de contadores.
*                   Ao final da secao de contagem sera gerado o arquivo
*                   de contagem acumulada, caso o parâmetro tenha sido
*                   diferente de NULL.
*
***********************************************************************/

   CNT_tpCondRet CNT_InicializarContadores( FILE * pArqLog , char * NomeArquivo ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Registrar arquivo acumulador
*
*  $ED Descricao da funcao
*     Registra ou substitui o nome do arquivo acumulador registrado no
*     modulo contador
*
***********************************************************************/

   void CNT_RegistrarAcumulador( char * NomeArquivo ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Terminar contadores
*
*  $ED Descricao da funcao
*     Termina a secao de contagem.
*     Grava o arquivo de contagem acumulada caso tenha sido definido.
*
*     Veja CNT_InicializarContadores para mais detalhes.
*
***********************************************************************/

   CNT_tpCondRet CNT_TerminarContadores( ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Ler arquivo de definicao de contadores
*
*  $FV Valor retornado
*     Retorna o número de erros de leitura reportado.
*
***********************************************************************/

   int CNT_LerContadores( char * NomeArquivoDefinicao ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Iniciar a contagem
*
*  $ED Descricao da funcao
*     Inicia a contagem. Enquanto esta funcao nao tiver sido chamada,
*     nao e realizada a contagem ao passar pela funcao CNT_Conta
*     Starts passage counting. Passage counting will occur only
*
*     Contagem pode ser parada com CNT_PararContagem
*
***********************************************************************/

   void CNT_IniciarContagem( ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Contar
*
*  $ED Descricao da funcao
*     Adiciona 1 ao contador dado.
*     Se o contador continha -1 - atribui 1 a ele.
*     Se o contador continha -2 - emite uma mensagem de erro acusando
*     a execucao de um fragmento de codigo proibido.
*
*     No modulo a medir devem ser inseridas chamadas para esta funcao em
*     todos os lugares em que interessa contar conforme a estrategia de
*     contagem utilizada.
*
*  $EP Parâmetros
*     $P NomeContador - a zero terminated string identifying the counter.
*                      Assure that names are unique, for example using
*                      a module identifying prefix for all names of
*                      a given module. Should not be NULL.
*     $P numLinha     - the line number where the call is issued.
*                      Use allways the ANSI-C standard __LINE__ constant
*                      as the actual parameter. Or use the CNT_COUNT macro.
*
*  $FV Valor retornado
*     CNT_CondRetOK  se processou normal
*     CNT_CondRetProibido se tentou contar um contador marcado proibido,
*             contagem inicializada para -2
*     CNT_CondRetNaoContador se tentou contar um contador que nao consta
*             da tabela de contadores lida de arquivo
*     CNT_CondRetNaoInicializado o modulo ainda nao foi inicializado
*
*  $EIU Interface com usuario pessoa
*     Sinaliza erro na saida se
*     Nome do contador nao existe
*     Se for tentado contar um contador proibido
*
*     As mensagens indicam a causa e o número da linha de codigo fonte
*     que contem a chamada para a funcao CNT_Contar
*
***********************************************************************/

   #define CNT_CONTAR( NomeContador )  \
           CNT_Contar( NomeContador , __LINE__ )

   CNT_tpCondRet CNT_Contar( char * NomeContador , int numLinha ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Parar contagem
*
*  $ED Descricao da funcao
*     Para a contagem. Apos este comando todas as chamadas da funcao
*     CNT_Contar realizam nada.
*     A contagem somente sera iniciada ou retomada com uma chamada
*     da funcao CNT_IniciarContagem
*
***********************************************************************/

   void CNT_PararContagem( ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Verificar contagem
*
*  $ED Descricao da funcao
*     Verifica se existe algum contador com contagem igual a zero
*     (nunca foi contado). Emite uma mensagem para cada contador
*     zero encontrado.
*     Retorna o número de erros reportados.
*       -1 se ainda nao incializado
*
***********************************************************************/

   int CNT_VerificarContagem( ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Obter valor de contagem
*
*  $ED Descricao da funcao
*     Retorna CNT_CondRetNaoContador se o contador nao existe
*     Obs. o valor de todas as condicoes de retorno sao negativas.
*
***********************************************************************/

   long CNT_ObterContagem( char * NomeContador ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Obter número de contadores
*
***********************************************************************/

   int CNT_ObterNumeroContadores( ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Obter total de contagem
*
***********************************************************************/

   long CNT_ObterContagemTotal( ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Iterador: obter contagem corrente
*
*  $ED Descricao da funcao
*     Retorna a contagem associada com o contador corrente do iterador
*
*     Retorna CNT_CondRetNaoIterador caso este nao tenha sido iniciado
*     ou ja tenha percorrido todos os contadores
*
***********************************************************************/

   long CNT_ObterContagemCorrente( ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Iterator: obter nome de contador corrente
*
*  $FV Valor retornado
*     Retorna o ponteiro para o nome do contador.
*     Jamais altere o nome pois o contador se tornaria inacessivel.
*     Retorna NULL se o iterador nao esta ativo.
*
***********************************************************************/

   char * CNT_ObterContadorCorrente( ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Iterador: avancar para o proximo contador
*
***********************************************************************/

   void CNT_IrProximoContador( ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Iterator: iniciar percorrimento da lista em ordem alfabetica
*
*  $ED Descricao da funcao
*     Inicializa ou reinicializa o iterador que percorre a lista ordenada.
*     A qualquer momento no maximo um um iterador estara ativo.
*
***********************************************************************/

   void CNT_IniciarIterador( ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Iterator: verificar se o iterador esta ativo
*
***********************************************************************/

   int CNT_EhAtivoIterador( ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Zerar todos contadores
*
***********************************************************************/

   CNT_tpCondRet CNT_ZerarContadores( ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Zerar contador dado
*
***********************************************************************/

   CNT_tpCondRet CNT_ZerarContador( char * NomeContador ) ;


/***********************************************************************
*
*  $FC Funcao: CNT  &Verificar a estrutura dos contadores
*
*  $ED Descricao da funcao
*     Verifica a integridade da estrutura de dados do modulo contador
*
*  $FV Valor retornado
*     Retorna o número de erros estruturais encontrados. Este número
*     nao corresponde à totalidade de erros, uma vez que o processamento
*     pode ser interrompido dependendo da severidade do erro encontrado.
*
***********************************************************************/

#ifdef _DEBUG

   int CNT_VerificarEstruturaContadores( ) ;

#endif

#undef CONTA_EXT

/********** Fim do modulo de definicao: CNT  Contadores de passagem **********/

#else
#endif
