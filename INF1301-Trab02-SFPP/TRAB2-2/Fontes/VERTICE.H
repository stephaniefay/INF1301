#if ! defined( VERTICE_ )
#define VERTICE_

#if defined( VERTICE_OWN )
   #define VERTICE_EXT
#else
   #define VERTICE_EXT extern
#endif

typedef struct tpVertice * VER_tppVertice;

VER_tppVertice VER_CriarVertice ( int id );
void * VER_InserirValor ( VER_tppVertice vertice, char * nome );
void * VER_DestroiVertice (VER_tppVertice Vertice);
void * VER_ObterValor (VER_tppVertice Vertice, char * valor);
int VER_ObterID (VER_tppVertice Vertice);

#endif