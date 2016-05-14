#if ! defined( LerParm_ )
#define LerParm_
/***************************************************************************
*
*  $MCD Modulo de definicao: LER  Ler parâmetros de comandos
*
*  Arquivo gerado:              LerParm.h
*  Letras identificadoras:      LER
*
*  Nome da base de software:    Arcabouco para a automacao de testes de programas redigidos em C
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\INSTRUM.BSW
*
*  Projeto: INF 1301 / 1628 Automatizacao dos testes de modulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data			Observacoes
*     4       avs   01/fev/2006		criar linguagem script simbolica
*     3       avs   08/dez/2004		uniformizacao dos exemplos
*     2       avs   07/jul/2003		unificacao de todos os modulos em um so projeto
*     1       avs   16/abr/2003		inicio desenvolvimento
*
*  $ED Descricao do modulo
*     Le parâmetros contidos em um buffer.
*     Os parâmetros podem ser simbolicos ou literais.
*     Parâmetros simbolicos devem ser declarados antes de serem utilizados.
*
***************************************************************************/
 
#if defined( LerParm_OWN )
   #define LerParm_EXT
#else
   #define LerParm_EXT extern
#endif

/***** Declaracoes exportadas pelo modulo *****/

#define  LER_DIM_NOME     32
#define  LER_DIM_STRING  500
#define  LER_DIM_BUFFER      250


/***********************************************************************
*
*  $TC Tipo de dados: LER Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         LER_CondRetOK ,
               /* Ler retorno OK */

         LER_CondRetNaoAbriu
               /* Ler nao abriu arquivo */

   } LER_tpCondRet ;

/***** Dados exportados pelo modulo *****/

   /* Estrutura de dados: *LER  Dados globais públicos */

   LerParm_EXT int LER_TamBuffer ;
         /* Tamanho do string contido no buffer de leitura */

   LerParm_EXT char LER_Buffer[ LER_DIM_BUFFER + 1 ] ;
         /* Buffer de leitura */


/***********************************************************************
*
*  $FC Funcao: LER  &Inicializar modulo LerParm
*
*  $ED Descricao da funcao
*     Inicializa o modulo.
*     Deve ser chamada antes de iniciar a analise de comandos.
*     Deve ser chamada uma única vez no inicio ou apos terminar o modulo.
*
***********************************************************************/

   int LER_InicializarLeitura( void ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Obter nome do arquivo script
*
***********************************************************************/

   char * LER_ObterNomeArqScript( void ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Interpretar comandos de teste
*
*  $ED Descricao da funcao
*     Interpreta os comandos de teste disponibilizados pelo modulo
*     de leitura.
*
*     Ver a descricao do modulo para mais detalhes
*
***********************************************************************/

   TST_tpCondRet LER_InterpretarComandos( char * ComandoTeste ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Terminar modulo LerParm
*
***********************************************************************/

   void LER_TerminarLeitura( void ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Abrir arquivo script de teste
*
*  $ED Descricao da funcao
*     Abre o arquivo que contem o script de teste.
*     A extensao default do arquivo de comandos script de teste e
*     ".script" e sera acrescida ao nome do arquivo caso este nao
*     contenha nome de extensao.
*
*  $EP Parâmetros
*     $P NomeArqParm - nome do arquivo contendo o script de teste
*
*  $FV Valor retornado
*     LER_CondRetOK        - caso tenha sido possivel abrir o arquivo.
*     LER_CondRetNaoAbriu  - caso tenha ocorrido algum erro.
*                            Nao ha discriminacao do erro encontrado.
*
***********************************************************************/

   LER_tpCondRet LER_AbrirArquivoScript( char * NomeArqParm ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Fechar arquivo script
*
***********************************************************************/

   void LER_FecharScript( void ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Declarar parâmetro simbolico
*
***********************************************************************/

   int LER_DeclararParametro( void ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Exibir declaracao de simbolo
*
***********************************************************************/

   void LER_ExibirParametro( char * Simbolo ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Ler linha script eliminando brancos ao final
*
*  $ED Descricao da funcao
*     Le uma linha do arquivo script e elimina os caracteres branco,
*     fim de linha, tabulacao etc. do final da linha lida.
*
*  $FV Valor retornado
*     Retorna o tamanho da linha lida.
*     Sera:
*        -1 caso tenha ocorrido fim de arquivo.
*        -2 caso tenha ocorrido algum problema de leitura.
*
***********************************************************************/

   int LER_LerLinhaScript( void ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Obter número de linhas lidas ate o momento
*
***********************************************************************/

   int LER_ObterNumLinhas( void ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Ler linha de parâmetros
*
*  $ED Descricao da funcao
*     Le um número variavel de parâmetros
*
*  $EP Parâmetros
*     Tipos   e um string contendo a identificacao dos tipos dos parâmetros
*             a serem lidos.
*     ...     Os demais parâmetros sao referencias (ponteiros) para os
*             espacos onde deverao ser armazenados os valores lidos.
*
*     Tal como em scanf deve-se tomar o cuidado de assegurar que a lista
*     de referencia e o string de tipos tenha o mesmo tamanho
*     e que os indicadores de tipo sejam consistentes com a referencia
*     posicionalmente correspondente.
*
*     Ao ler um campo primeiro procura ler um nome de parâmetro ja
*     declarado. Caso isto seja possivel e o tipo esteja correto
*     e " lido" o valor contido no parâmetro
*     Caso nao seja possivel tenta ler um literal em acordo com o tipo
*     dado.
*
*     Gera mensagens de erro para parâmetros desconhecidos, sintaxe errada
*     e tipo inconsistente com o solicitado.
*
*  $FV Valor retornado
*     Retorna o número de campos lidos ate concluir ou ate encontrar
*     um erro.
*
***********************************************************************/

   int LER_LerParametros( char * Tipos , ... ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Ler parâmetro caractere
*
***********************************************************************/

   int LER_LerParmChar( char * Parm ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Ler parâmetro flutuante
*
***********************************************************************/

   int LER_LerParmDouble( double * Parm ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Ler parâmetro nome
*
***********************************************************************/

   int LER_LerParmNome( char * Parm , int * tamNome , int dimNome ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Ler parâmetro inteiro
*
***********************************************************************/

   int LER_LerParmInt( int * Parm ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Ler parâmetro string
*
***********************************************************************/

   int LER_LerParmString( char * Parm , int * tamString , int dimString ) ;


/***********************************************************************
*
*  $FC Funcao: LER  &Pular comando de teste
*
***********************************************************************/

   void LER_PularComando( void ) ;

#undef LerParm_EXT

/********** Fim do modulo de definicao: LER  Ler parâmetros de comandos **********/

#else
#endif
