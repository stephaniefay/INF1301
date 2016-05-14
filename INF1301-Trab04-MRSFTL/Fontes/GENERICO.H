#if ! defined( GENERICO_ )
#define GENERICO_
/***************************************************************************
*
*  $MCD Modulo de definicao: TSTG Controlador de teste generico
*
*  Arquivo gerado:              GENERICO.h
*  Letras identificadoras:      TST
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
*     O modulo de teste generico contem um conjunto de funcoes de
*     coordenacao, apoio e controle da execucao de testes de modulos
*     quaisquer.
*
*     Embora na pratica a funcao de teste especifica seja uma extensao da
*     funcao de teste generica, a funcao de teste especifica encontra-se em
*     outro modulo. Desta forma as alteracoes necessarias para cada
*     modulo a testar concentram-se exclusivamente naquele modulo.
*
*  $EIU Interface com o usuario pessoa
*     Os seguintes comandos genericos estao definidos:
*
*     linha em branco - faz nada
*
*     //      - comentario, e impresso no LOG
*
*     ==      - titulo de caso de teste, o titulo e impresso no LOG
*
*     =recuperar
*             - Caso o comando imediatamente anterior ao comando
*               =recuperar retorne TST_CondRetOK, obviemanete o comando
*               executou corretamente, portanto o comando =recuperar
*               reportara uma falha no script de teste, uma vez que nao
*               foi encontrada a falha esperada ao executar o comando.
*             - Caso o comando antecessor retorne TST_CondRetErro,
*               ou TST_CondRetParm (erro de parâmetros do comando)
*               a falha reportada sera desconsiderada, uma vez que
*               era esperada. O comando =recuperar destina-se a
*               apoiar o teste da corretude dos validadores de
*               parâmetros dos comandos e das funcoes por eles
*               ativadas.
*             - caso o comando antecessor retorne outras condicoes, o
*               comando =recuperar sera tratado como falha.
*
*     =bkpt   - permite interagir com o depurador utilizado para
*               desenvolver os modulos sob teste. O comando =bkpt
*               executa um codigo "dummy" no qual pode ser inserido
*               um "breakpoint" do depurador. Desta forma o teste pode
*               prosseguir sem interrupcao ate o comando =bkpt.
*               Para isto
*               - apague ou desative todos os breakpoints do depurador
*               - insira o comando =bkpt no script pouco antes do ponto
*                 de interrupcao desejado
*               - usando o depurador, estabeleca um breakpoint na linha de
*                 codigo: "Dummy = 0 ;" contida no modulo de teste
*                 generico. Esta linha pode ser encontrada
*                 procurando por "BKPT_CMD"
*               - de partida no programa e espere ate chegar ao breakpoint
*                 associado ao comando "dummy". Agora reative ou instale
*                 os breakpoints requeridos pela a sessao de depuracao.
*                 e continue depurando
*
*     =cancelar
*             - termina a interpretacao dos comandos de teste.
*               Sempre sinaliza falha.
*
*     =AceitaFalhasAcumuladas  numFalhas
*             - caso o contador de falhas registre numFalhas, ele sera
*               tornado zero. Este comando e similar a =recuperar.
*               Difere deste por ser executado desde que o comando
*               anterior nao tenha reportado erro, tal como acontece
*               com todos os comandos, exceto =recuperar.
*               O comando permite recuperar falhas sinalizadas por
*               modulos de apoio, tais como, leitor de parâmetros,
*               contador de passagens e controle de espaco dinâmico.
*               Caso o contador de número de falhas contenha um valor
*               diferente de numFalhas, sera reportado um erro e
*               o contador e incrementado de 1.
*
*     Os demais comandos sao passados para as funcoes de teste especifico.
*     Primeiro para as do arcabouco, depois para a especifica do modulo
*     a testar. A última funcao de teste especifico deve retornar a condicao
*     TST_CondRetNaoConhec caso nao consiga interpretar a diretiva.
*
*  $EIM Interface com outros modulos
*     A primeira funcao do arcabouco ("framework") a ser chamada deve a
*     sempre ser TST_InicializarTeste. Caso nao o seja, ocorrerao erros
*     de execucao (assert).
*
*     Apos abra o arquivo de script executando a funcao
*     TST_AbrirArquivoScript. Se for desejado gerar um log abra
*     o arquivo corresponente com a funcao TST_AbrirArquivoLog.
*
*     Depois de abrir os arquivos, execute os testes chamando a funcao
*     TST_RealizarTeste. A funcao de teste generico lera todo o arquivo
*     de script, retornando apos concluir o teste.
*
*     Apos, termine o teste atraves da funcao TST_TerminarTeste.
*     Esta funcao exibe as estatisticas do teste e, caso solicitado,
*     acumula essas estatisticas em um arquivo acumulador (ver
*     parâmetro /a do programa principal.
*
*     As funcoes "TST_ObterXXX" podem ser utilizadas antes de fechar o
*     modulo de teste para exibir o resumo do teste no modulo cliente do
*     modulo de controle generico.
*
*     O programa cliente do modulo controle de teste generico pode
*     efetuar as operacoes acima repetidas vezes, permitindo, assim o
*     teste envolvendo diversos arquivos scripts de teste. A saida
*     de cada teste deve ser dirigida para um log especifico, ou para
*     stdout, uma vez que, ao abrir um arquivo log, o seu conteúdo sera
*     sempre destruido.
*
*     O modulo de teste generico tambem implementa diversas funcoes
*     de comparacao "TST_CompararXXX" use-as no modulo de controle de
*     teste especifico. Desta forma sera assegurado o tratamento uniforme
*     de todas as falhas possivelmente encontradas.
*
*     O modulo disponibiliza ainda a funcao TST_ExibirPrefixo
*     que gera uma linha de saida obedecendo aos padroes de interface
*     estabelecidos. Sendo desejado pode-se adicionar textos à linha
*     usando a funcao fprintf( TST_pArqLog , ... ). Um exemplo disso
*     e quando se deseja imprimir informacao complementar ao interpretar
*     uma determinada diretiva.
*
*     Finalmente, o modulo disponibiliza a funcao TST_NotificarFalha
*     que incrementa o contador de falhas alem de emitir uma mensagem
*     de erro.
*
***************************************************************************/
 
#if defined( GENERICO_OWN )
   #define GENERICO_EXT
#else
   #define GENERICO_EXT extern
#endif

/***** Declaracoes exportadas pelo modulo *****/

#include    "TST_Espc.h"


/***********************************************************************
*
*  $TC Tipo de dados: TST Cond ret modulo de teste generico
*
*
***********************************************************************/

   typedef enum {

         TST_CondOK ,
               /* Generico executou correto */

         TST_CondNaoAbriu
               /* Generico nao abriu arquivo */

   } TST_tpCond ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Inicializar o modulo de teste
*
*  $ED Descricao da funcao
*     Inicializa todas as variaveis globais exportadas e encapsuladas
*     do modulo de teste generico.
*
*     Embora pouco recomendavel (ver descricao do modulo TesteSpc)
*     esta funcao pode ser alterada para assegurar o estabelecimento
*     do contexto inicial do modulo TesteSpc. Este deve conter uma
*     funcao de inicializacao a ser chamada pela presente funcao.
*
***********************************************************************/

   void TST_InicializarTeste( void ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Terminar a execucao do modulo de teste
*
*  $ED Descricao da funcao
*     Fecha todos os arquivos e desaloca todos os espacos de dados
*     alocados sob controle do modulo de teste generico
*
***********************************************************************/

   void TST_TerminarTeste( void ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Obter origem do nome da extensao de arquivo
*
*  $ED Descricao da funcao
*     Procura o inicio do nome da extensao contido no nome do arquivo
*     dado por parâmetro
*
*     Evite o uso de nomes de arquivos com dois ou mais caracteres ".".
*     Isto pode confundir no caso de se desejar a adicao de algum nome
*     de extensao padrao.
*
*  $EP Parâmetros
*     $P NomeArqParm - nome de arquivo a ser analisado
*
*  $FV Valor retornado
*     Ponteiro para o caractere '.' que separa a extensao.
*     Sera NULL caso o nome do arquivo nao contenha extensao.
*
***********************************************************************/

   char * TST_ObterInicioExtensao( char * NomeArqParm ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Abrir arquivo log
*
*  $ED Descricao da funcao
*     Abre o arquivo log a ser utilizado como saida durante os testes.
*     Todas as saidas geradas pelo modulo de teste sao dirigidos para
*     este arquivo. Caso nao tenha sido aberto, sera utilizado o
*     arquivo stdout.
*
*     A extensao default do arquivo log e ".log" e sera acrescida ao nome
*     do arquivo caso este nao contenha nome de extensao.
*
*  $EP Parâmetros
*     $P NomeArqParm - nome do arquivo. Pode (deve) ser um nome relativo
*                      ao diretorio corrente. Caso o arquivo
*                      exista, sera destruido sem perguntar se pode.
*
*  $FV Valor retornado
*     TST_CondRetOK       - abriu corretamente
*     TST_CondRetNaoAbriu - ocorreu algum problema ao tentar abrir.
*                           O problema nao e descriminado.
*                           O arquivo de saida do log volta a ser stdout
*
*  $EIU Interface com usuario pessoa
*     Esta funcao deve ser chamada antes de iniciar a execucao dos testes.
*
***********************************************************************/

   TST_tpCondRet TST_AbrirArquivoLog( char * NomeArqParm ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Obter ponteiro para arquivo LOG
*
*  $ED Descricao da funcao
*     Retorna o ponteiro para o FILE do log.
*     Sera stdout caso nao seja definido explicitamente por
*     TSTG_DefinirLog
*
*  $FV Valor retornado
*     Ponteiro valido para um arquivo de texto de saida
*
***********************************************************************/

   FILE * TST_ObterArqLog( void ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Registrar nome do arquivo acumulador
*
*  $ED Descricao da funcao
*     Registra o nome do arquivo acumulador. Este arquivo e utilizado
*     para acumular as estatisticas de um teste formado por um conjunto
*     de massas de teste. Cada massa de teste gera o seu conjunto de
*     estatisticas de execucao. O arquivo acumulador acumula estas
*     estatisticas permitindo ver o total de todas as massas de teste.
*
*  $EIU Interface com usuario pessoa
*     O arquivo acumulador tem serventia somente se o teste e formado
*     por um conjunto de duas ou mais massas de teste.
*     Antes de executar a primeira deve ser apagado o arquivo acumulador.
*     Apos terminar a execucao da última massa de teste exiba o resultado
*     como o programa "ExbeEstat" que faz parte do arcabouco.
*
***********************************************************************/

   void TST_RegistrarArquivoAcumulador( char * pNomeArquivoAcumulador ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Interpretar toda a massa de teste
*
*  $ED Descricao da funcao
*     Interpreta o arquivo de diretivas (script) de teste ja aberto
*
*     A funcao de teste e dividida em tres classes de comandos:
*
*     - os de teste generico, que coordenam e controlam a realizacao do
*       teste. Estes comandos sao interpretados por esta funcao.
*     - os de teste e controle de modulos componentes do arcabouco.
*       Estes comandos sao interpretados por funcoes de teste especificas
*       para cada um dos modulos componentes.
*     - os de teste especifico do modulo (ou modulos) a ser testado.
*       O modulo de teste especifico interpreta os comandos projetados
*       para realizar os testes do modulo a testar.
*
*     A funcao de teste generico le um arquivo de diretivas de teste.
*     Cada linha deste arquivo e um comando de teste.
*     A funcao de teste le uma a uma as linhas do arquivo, limpa os
*     caracteres em branco no final da linha e procura interpretar o
*     comando.
*
*     As funcoes de teste especificas comunicam os resultados da execucao
*     de cada comando por meio de uma condicao de retorno.
*
*     Cada linha do arquivo script de teste corresponde a um comando de
*     teste.
*
*     Caso seja encontrada uma falha nao esperada (ver comando =recuperar)
*     os restantes comandos do caso de teste serao ignorados e contados
*     como problemas.
*
*     A sintaxe utilizada pelos comandos de teste e semelhante a assembler.
*     Esta sintaxe facilita a analise:
*
*        =<cmd> <parâmetros>
*
*     em que:
*        =            - todos os comandos a serem interpretados iniciam
*                       com este caractere
*        <cmd>        - e o string que identifica o comando
*        <parâmetros> - sao zero ou mais itens a serem utilizados
*                       pelo comando de teste. Os itens devem, de preferencia,
*                       ser separados um do outro por um caractere "espaco"
*
*     Deve ser adotado o seguinte padrao de uso:
*
*     - procure sempre utlizar uma das funcoes TST_CompararXXX, na forma:
*          return TST_CompararXXX( valoresperado, funcao a testar , mensagem )
*
*     - as funcoes de comparacao fornecidas sempre geram as mensagens no
*       padrao estipulado
*
*     - quando nao for possivel utilizar uma funcao de comparacao, reporte
*       a falha, esperadas ou nao, atraves da funcao
*          TST_ImprimirPrefixo( Mensagem )
*
*     - a seguir mostre o valor esperado e o obtido
*
*     - Informacoes relativas a falhas dos testes sao sinalizadas por
*       uma mensagem iniciando com ">>>" o número da linha do comando de teste
*       e o número de falhas encontradas ate o momento.
*
*     - Informacoes relativas à execucao dos testes sao sinalizadas por
*       uma mensagem iniciando com "!!!".
*
*  $FV Valor retornado
*     TST_CondRetErro   - caso tenha sido encontrado um ou mais problemas
*     TST_CondRetOK     - caso o teste tenha terminado com zero problemas
*                         nao esperados.
*
*  $FGP Tipos e Variaveis globais externas do proprio modulo
*     pArqScript - deve referenciar o arquivo script aberto
*     pArqLog    - deve referenciar o arquivo log aberto
*
***********************************************************************/

   TST_tpCondRet TST_RealizarTeste( char * Construto ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Obter número de casos de teste efetuados
*
*  $ED Descricao da funcao
*     Retorna o número de casos de teste lidos.
*     Cada caso de teste inicia com o comando "== <nome do caso de teste>".
*
***********************************************************************/

   int TST_ObterNumCasosTeste( ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Obter número de comandos especificos corretamente interpretados
*
*  $ED Descricao da funcao
*     Retorna o número de comandos de teste especificos lidos e
*     corretamente interpretados. Nao conta comandos que retornem nao OK
*     independentemento do motivo. Tambem nao conta comandos recuperar.
*
***********************************************************************/

   int ObterNumComandosExecutados( void ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Obter número de problemas encontrados
*
*  $ED Descricao da funcao
*     Retorna o número de problemas encontrados.
*     O modulo de teste especifico sinaliza problemas atraves de
*     uma condicao de retorno diferente de TST_CondRetOK.
*     Sao tratados como problema tambem comandos de teste em erro,
*     e todos os comandos de teste de um dado caso de teste ignorados
*     em virtude de alguma falha encontrada.
*     Portanto, e possivel que o número de problemas venha a ser maior do
*     que o número de casos de teste existente no script.
*
***********************************************************************/

   int TST_ObterNumFalhas( void ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Incrementar contador de falhas
*
***********************************************************************/

   void TST_ContarFalhas( ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Comparar booleano
*
*  $ED Descricao da funcao
*     Compara valor booleano esperado com valor booleano obtido,
*     reportamdo uma falha caso nao sejam iguais.
*     Note que "!= 0" corresponde a TRUE e "== 0" corresponde a FALSE
*
*  $EP Parâmetros
*     ValorEsperado  - e um valor fornecido como parâmetro do comando
*                      de teste
*     ValorObtido    - e o valor retornado pela funcao em teste
*     pMensagem      - mensagem explanatoria da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor esperado nao for consistente com o obtido
*     TST_CondRetOK    se os valores forem consistentes
*
***********************************************************************/

   TST_tpCondRet TST_CompararBool( int    ValorEsperado ,
                                   int    ValorObtido   ,
                                   char * pMensagem      ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Comparar caractere
*
*  $ED Descricao da funcao
*     Compara um caractere esperado com um caractere obtido, emitindo mensagem de
*     erro caso nao sejam iguais.
*
*  $EP Parâmetros
*     ValorEsperado  - e um valor fornecido como parâmetro do comando
*                      de teste
*     ValorObtido    - e o valor retornado pela funcao em teste
*     pMensagem      - mensagem explanatoria da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor esperado nao for igual ao obtido
*     TST_CondRetOK    se os valores forem iguais
*
***********************************************************************/

   TST_tpCondRet TST_CompararChar( char   ValorEsperado ,
                                   char   ValorObtido   ,
                                   char * pMensagem       ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Comparar inteiro
*
*  $ED Descricao da funcao
*     Compara valor inteiro long esperado com valor inteiro obtido,
*     reportamdo uma falha caso nao sejam iguais.
*
*  $EP Parâmetros
*     ValorEsperado  - e um valor fornecido como parâmetro do comando
*                      de teste
*     ValorObtido    - e o valor retornado pela funcao em teste
*     pMensagem      - mensagem explanatoria da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor esperado nao for igual ao obtido
*     TST_CondRetOK    se os valores forem iguais
*
***********************************************************************/

   TST_tpCondRet TST_CompararInt( long   ValorEsperado ,
                                  long   ValorObtido   ,
                                  char * pMensagem       ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Comparar flutuante
*
*  $ED Descricao da funcao
*     Compara valor flutuante esperado com valor flutuante obtido,
*     reportando uma falha caso
*     1 - Tolerancia > esperado / obtido ou
*     1 + Tolerancia < esperado / obtido
*
*  $EP Parâmetros
*     ValorEsperado  - e um valor fornecido como parâmetro do comando
*                      de teste
*     ValorObtido    - e o valor retornado pela funcao em teste
*     Tolerância     - indica os limites da relacao entre esperado e obtido.
*                      Deve ser um valor positivo, menor do que 1.
*                      Use um valor do tipo 10 ** -n, no qual n e o
*                      número de digitos significativos desejado.
*     pMensagem      - mensagem explanatoria da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor obtido nao estiver dentro do dominio da
*                      tolerância em torno do valor esperado
*     TST_CondRetOK    se os valores estiverem dentro da tolerância
*
***********************************************************************/

   TST_tpCondRet TST_CompararFloat( double   ValorEsperado ,
                                    double   ValorObtido   ,
                                    double   Tolerancia    ,
                                    char *   pMensagem      ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Comparar string
*
*  $ED Descricao da funcao
*     Compara string esperado com string obtido, reportamdo uma falha
*     caso nao sejam iguais. Ambos os strings devem obedecer o
*     padrao C, terminando em zero.
*
*  $EP Parâmetros
*     ValorEsperado  - e um string fornecido como parâmetro do comando
*                      de teste.
*     ValorObtido    - e o string retornado pela funcao em teste
*     pMensagem      - mensagem explanatoria da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor esperado nao for igual ao obtido
*     TST_CondRetOK    se os valores forem iguais
*
***********************************************************************/

   TST_tpCondRet TST_CompararString( char * ValorEsperado ,
                                     char * ValorObtido   ,
                                     char * pMensagem       ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Comparar espaco
*
*  $ED Descricao da funcao
*     Compara espacos de dados, reportando uma falha caso nao sejam iguais.
*     Esta funcao pode ser utilizada para comparar qualquer coisa,
*     inclusive valores do tipo  "struct"
*     O tipo do valor e indefinido e os valores serao exibidos em
*     formato hexadecimal, caso nao sejam iguais
*
*  $EP Parâmetros
*     ValorEsperado  - ponteiro para o espaco que contem o valor esperado
*     ValorObtido    - ponteiro para o espaco que contem o valor obtido
*     TamEspaco      - tamanho do espaco a ser comparado
*     pMensagem      - mensagem explanatoria da falha encontrada
*
*  $FV Valor retornado
*     TST_CondRetErro  se o valor esperado nao for igual ao obtido
*     TST_CondRetOK    se os valores forem iguais
*
***********************************************************************/

   TST_tpCondRet TST_CompararEspaco( void * ValorEsperado ,
                                     void * ValorObtido   ,
                                     int    TamEspaco     ,
                                     char * pMensagem       ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Comparar ponteiro
*
*  $ED Descricao da funcao
*     Compara dois ponteiros emitindo uma mensagem caso nao sejam iguais
*
*  $FV Valor retornado
*     TST_CondRetErro  se os dois ponteiros forem diferentes
*     TST_CondRetOK    se forem iguais
*
***********************************************************************/

   TST_tpCondRet TST_CompararPonteiro( void * PonteiroEsperado ,
                                       void * PonteiroObtido   ,
                                       char * pMensagem       ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Comparar ponteiro nulo
*
*  $ED Descricao da funcao
*     Verifica
*       - quando ModoEsperado     e 0 se o ponteiro e nulo
*       - quando ModoEsperado nao e 0 se o ponteiro e nao nulo
*
*  $FV Valor retornado
*     TST_CondRetErro  se os dois ponteiros forem diferentes
*     TST_CondRetOK    se forem iguais
*
***********************************************************************/

   TST_tpCondRet TST_CompararPonteiroNulo( int ModoEsperado ,
                                           void * PonteiroObtido   ,
                                           char * pMensagem       ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Assertiva controlada
*
*  $ED Descricao da funcao
*     Esta funcao substitui a funcao assert de C.
*     e utilizada no contexto do arcabouco de teste.
*     Ela imprime mensagens mais visiveis tanto no log como na
*     janela de comando.
*
*     Recomenda-se, no entanto, utilizar a funcao assert de C em aplicacoes.
*
*  $FV Valor retornado
*     Termina a execucao do programa com codigo de retorno == 4
*
***********************************************************************/

   #define  TST_ASSERT( Expressao ) \
      TST_Assert( Expressao , __LINE__ , __FILE__ )

   void TST_Assert( int Expressao , int Linha , char * NomeArq ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Notificar falha
*
*  $ED Descricao da funcao
*     Exibe uma mensagem de falha no formato padrao do arcabouco.
*
*  $FV Valor retornado
*     TST_CondRetErro  sempre
*
***********************************************************************/

   TST_tpCondRet TST_NotificarFalha( char * pMensagem ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Exibir prefixo da mensagem
*
*  $ED Descricao da funcao
*     Imprime o prefixo de mensages de falha
*
*  $EH Hipoteses assumidas pela funcao
*     O contador de falhas e incrementado somente pela funcao de teste
*     generica e apos à conclusao da interpretacao do comando.
*
***********************************************************************/

   void TST_ExibirPrefixo( char * Indicador , char * pMensagem ) ;


/***********************************************************************
*
*  $FC Funcao: TSTG &Exibir um espaco qualquer em formato hexadecimal e char
*
*  $EP Parâmetros
*     $P tamEspaco - tamanho em bytes do espaco a exibir
*     $P Ponteiro  - ponteiro para o primeiro byte do espaco a exibir
*
***********************************************************************/

   void TST_ExibirEspacoHexa( int    tamEspaco ,
                              void * Ponteiro   ) ;

#undef GENERICO_EXT

/********** Fim do modulo de definicao: TSTG Controlador de teste generico **********/

#else
#endif
