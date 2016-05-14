#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define true 1
#define false 0

#define MENU_OWN
#include	"LISTA.H"
#include	"PILHA.H"
#include	"MATRIZ.H"
#undef MENU_OWN

LIS_tppLista Mahjong; // Ponteiro para o mahjong

#define tabX 5
#define tabY 5
// Coordenadas maximas da tabela (x e y apenas)

int lib = 0;

void montarMahjong ();
void PegaCoor( int* X, int* Y, int* X2, int* Y2);
void printMahjong (int x, int y);
void PegarPeca ( int X, int Y, int X2, int Y2);

int main (void)
{
	int X,Y,X2,Y2; // Coordenadas das peças UM e DOIS
	int terminou=false;
	Mahjong = MTZ_criarTab(tabX,tabY); // Criar o mahjong

	montarMahjong();

	while (terminou==false)
	{
		if(lib == 25)
			terminou = true;
		
		printMahjong( tabX, tabY );
		PegaCoor( &X, &Y, &X2, &Y2 );
		PegarPeca( X, Y, X2, Y2 );
	}

	system("cls");

	MTZ_DestruirMatriz(Mahjong);

	printf("Parabens, voce concluiu o jogo.");

	return 0;
}

void PegarPeca (int X, int Y, int X2, int Y2)
{	
	int tCorr, tAnt, tProx, tam;
	char * Receber;
	char * Receber2;
	LIS_tppLista Col, Col2;
	PLH_tppPilha p, q;

	if ( (X==X2) &&
		(Y==Y2))
	{
		printf("Voce selecionou a mesma peca (serio isso?).\n");
		system("pause");
		system("cls");
		return ;
	}

	if ( X != 0 && X != tabX - 1)
	{
		// Não esta nas laterais

		Col = MTZ_achaCoor(Mahjong, X, Y);
		p = (PLH_tppPilha) LIS_ObterValor(Col);
		tCorr = PLH_ObterTam(p);

		Col = MTZ_achaCoor(Mahjong, X-1, Y);
		p = (PLH_tppPilha) LIS_ObterValor(Col);
		tAnt = PLH_ObterTam(p);

		Col = MTZ_achaCoor(Mahjong, X+1, Y);
		p = (PLH_tppPilha) LIS_ObterValor(Col);
		tProx = PLH_ObterTam(p);

		if ( (tCorr <= tAnt) &&
			(tCorr <= tProx))
		{
			// Tem peças nas laterais

			printf("Peca (%d, %d) bloqueada.\n", X, Y);
			system("pause");
			system("cls");
			return ;
		}

	}
	if ( X2 != 0 && X2 != tabX - 1)
	{
		// Não esta nas laterais
		Col = MTZ_achaCoor(Mahjong, X2, Y2);
		p = (PLH_tppPilha) LIS_ObterValor(Col);
		tCorr = PLH_ObterTam(p);

		Col = MTZ_achaCoor(Mahjong, X2-1, Y2);
		p = (PLH_tppPilha) LIS_ObterValor(Col);
		tAnt = PLH_ObterTam(p);

		Col = MTZ_achaCoor(Mahjong, X2+1, Y2);
		p = (PLH_tppPilha) LIS_ObterValor(Col);
		tProx = PLH_ObterTam(p);

		if ( (tCorr <= tAnt) &&
			(tCorr <= tProx))
		{
			// Tem peças nas laterais
			printf("Peca (%d, %d) bloqueada.\n", X2, Y2);
			system("pause");
			system("cls");
			return ;
		}
	}
	
	Col = MTZ_achaCoor(Mahjong, X, Y);
	p = (PLH_tppPilha) LIS_ObterValor(Col);
	Receber = PLH_Printar(p);

	Col = MTZ_achaCoor(Mahjong, X2, Y2);
	p = (PLH_tppPilha) LIS_ObterValor(Col);
	Receber2 = PLH_Printar(p);

	if (Receber == Receber2)
	{
		MTZ_popCoor(Mahjong, X, Y);
		MTZ_popCoor(Mahjong, X2, Y2);

		Col2 = MTZ_achaCoor(Mahjong, X, Y);
		q = (PLH_tppPilha) LIS_ObterValor(Col);
		tam = PLH_ObterTam(q);

		if (tam == 0)
			lib++;

		Col2 = MTZ_achaCoor(Mahjong, X2, Y2);
		q = (PLH_tppPilha) LIS_ObterValor(Col);
		tam = PLH_ObterTam(q);

		if (tam == 0)
			lib++;
		
		system("cls");
	}
	else
	{
		printf("Pecas sao diferentes.\n");
		system("pause");
		system("cls");
		return ;
	}
}

/*********************************************

Função: Pega a coordenada das duas peças que o usuario deseja tentar mexer

**********************************************/

void PegaCoor( int* X, int* Y, int* X2, int* Y2)
{
	int firstTime=true;

	*X=-1;
	*Y=-1;
	*X2=-1;
	*Y2=-1;
	// Parametros podem ter vindo com o valor de um mahjong antigo

	// Coordenadas tem que ser > 0 e <= ao tamanho do eixo X ou Y
	// Pegando as coordenadas da primeira peça e salvando em X2 e Y2
	while( (*X < 0) || (*X > tabX-1) ||
		(*Y < 0) || (*Y > tabY-1) )
	{
		if (firstTime==false)
		{
			system("cls");
			printMahjong(tabX, tabY);
			printf("!!! Valores digitados INVALIDOS, tente novamente\n\n");
		}
		// Limpar a tela e printar tudo novamente

		printf("- Digite a coordenada X da PRIMEIRA peca que deseja:\n");
		scanf("%d", X);
		printf("- Digite a coordenada Y da PRIMEIRA peca que deseja:\n");
		scanf("%d", Y);
		printf("\n");

		firstTime=false;
	}

	firstTime=true;

	while( (*X2 < 0) || (*X2 > tabX-1) ||
		(*Y2 < 0) || (*Y2 > tabY-1) )
	{
		if (firstTime==false)
		{
			system("cls");
			printMahjong(tabX, tabY);
			printf("- Digite a coordenada X da PRIMEIRA peca que deseja: \n%d\n", *X);
			printf("- Digite a coordenada Y da PRIMEIRA peca que deseja: \n%d\n\n", *Y);
			printf("!!! Valores digitados INVALIDOS, tente novamente\n\n");
		}
		// Limpar a tela e printar tudo novamente

		printf("- Digite a coordenada X da SEGUNDA peca que deseja:\n");
		scanf("%d", X2);
		printf("- Digite a coordenada Y da SEGUNDA peca que deseja:\n");
		scanf("%d", Y2);

		firstTime=false;
	}
	printf("\n\n");
	firstTime=true;
}

void printMahjong (int x, int y) {

	int i, j, tam, lib;
	int tCorr, tAnt, tProx; // Ver Tamanho Corrente, Anterior, Proximo
	LIS_tppLista Col;
	PLH_tppPilha p;
	char * Receber;
	HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (j = 0; j < y; j++) 
	{
		for (i = 0; i < x; i++)
		{
			
			Col = MTZ_achaCoor(Mahjong, i, j);
			p = (PLH_tppPilha) LIS_ObterValor(Col);
			Receber = PLH_Printar(p);

			tam = PLH_ObterTam(p);

			if (tam == 0)
			{
				SetConsoleTextAttribute(hConsole, 15);
				printf("     ");

			}
				

			else if ( (i == 0) ||
				(i == x - 1))
			{
				SetConsoleTextAttribute(hConsole, 31);
				printf("| %c |", Receber);
			}
			else
			{

				Col = MTZ_achaCoor(Mahjong, i, j);
				p = (PLH_tppPilha) LIS_ObterValor(Col);
				tCorr = PLH_ObterTam(p);

				Col = MTZ_achaCoor(Mahjong, i-1, j);
				p = (PLH_tppPilha) LIS_ObterValor(Col);
				tAnt = PLH_ObterTam(p);

				Col = MTZ_achaCoor(Mahjong, i+1, j);
				p = (PLH_tppPilha) LIS_ObterValor(Col);
				tProx = PLH_ObterTam(p);

				if( (tCorr > tAnt) ||
					(tCorr > tProx) )
				{
					SetConsoleTextAttribute(hConsole, 31);
					printf("| %c |", Receber);
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 79);
					printf("| %c |", Receber);
				}
			}
			SetConsoleTextAttribute(hConsole, 15);
			printf(" ");
		}
		SetConsoleTextAttribute(hConsole, 15);
		if (j != y)
			printf("\n- - - - - - - - - - - - - - -\n");
	}
}

void montarMahjong ()
{
	char Inserir;
	//char Receber;
	// Variaveis para manipulação do valor
	
	// Nivel 4

	Inserir = 'H';
	MTZ_pushCoor(Mahjong, 0, 0, Inserir);
	Inserir = 'I';
	MTZ_pushCoor(Mahjong, 1, 0, Inserir);
	Inserir = 'N';
	MTZ_pushCoor(Mahjong, 2, 0, Inserir);
	Inserir = 'W';
	MTZ_pushCoor(Mahjong, 3, 0, Inserir);
	Inserir = 'Z';
	MTZ_pushCoor(Mahjong, 4, 0, Inserir);
	Inserir = 'Y';
	MTZ_pushCoor(Mahjong, 0, 1, Inserir);
	Inserir = 'E';
	MTZ_pushCoor(Mahjong, 1, 1, Inserir);
	Inserir = 'J';
	MTZ_pushCoor(Mahjong, 2, 1, Inserir);
	Inserir = 'W';
	MTZ_pushCoor(Mahjong, 3, 1, Inserir);
	Inserir = 'N';
	MTZ_pushCoor(Mahjong, 4, 1, Inserir);
	Inserir = 'O';
	MTZ_pushCoor(Mahjong, 0, 2, Inserir);
	Inserir = 'I';
	MTZ_pushCoor(Mahjong, 1, 2, Inserir);
	Inserir = 'J';
	MTZ_pushCoor(Mahjong, 2, 2, Inserir);
	Inserir = 'H';
	MTZ_pushCoor(Mahjong, 3, 2, Inserir);
	Inserir = 'S';
	MTZ_pushCoor(Mahjong, 4, 2, Inserir);
	Inserir = 'D';
	MTZ_pushCoor(Mahjong, 0, 3, Inserir);
	Inserir = 'G';
	MTZ_pushCoor(Mahjong, 1, 3, Inserir);
	Inserir = 'G';
	MTZ_pushCoor(Mahjong, 2, 3, Inserir);
	Inserir = 'E';
	MTZ_pushCoor(Mahjong, 3, 3, Inserir);
	Inserir = 'C';
	MTZ_pushCoor(Mahjong, 4, 3, Inserir);
	Inserir = 'Z';
	MTZ_pushCoor(Mahjong, 0, 4, Inserir);
	Inserir = 'S';
	MTZ_pushCoor(Mahjong, 1, 4, Inserir);
	Inserir = 'F';
	MTZ_pushCoor(Mahjong, 2, 4, Inserir);
	Inserir = 'X';
	MTZ_pushCoor(Mahjong, 3, 4, Inserir);
	Inserir = 'Y';
	MTZ_pushCoor(Mahjong, 4, 4, Inserir);

	// Nivel 3

	Inserir = 'Y';
	MTZ_pushCoor(Mahjong, 0, 0, Inserir);
	Inserir = 'L';
	MTZ_pushCoor(Mahjong, 1, 0, Inserir);
	Inserir = 'O';
	MTZ_pushCoor(Mahjong, 2, 0, Inserir);
	Inserir = 'F';
	MTZ_pushCoor(Mahjong, 3, 0, Inserir);
	Inserir = 'Z';
	MTZ_pushCoor(Mahjong, 4, 0, Inserir);
	Inserir = 'R';
	MTZ_pushCoor(Mahjong, 0, 1, Inserir);
	Inserir = 'N';
	MTZ_pushCoor(Mahjong, 1, 1, Inserir);
	Inserir = 'B';
	MTZ_pushCoor(Mahjong, 2, 1, Inserir);
	Inserir = 'K';
	MTZ_pushCoor(Mahjong, 3, 1, Inserir);
	Inserir = 'Y';
	MTZ_pushCoor(Mahjong, 4, 1, Inserir);
	Inserir = 'L';
	MTZ_pushCoor(Mahjong, 0, 2, Inserir);
	Inserir = 'A';
	MTZ_pushCoor(Mahjong, 1, 2, Inserir);
	Inserir = 'V';
	MTZ_pushCoor(Mahjong, 2, 2, Inserir);
	Inserir = 'X';
	MTZ_pushCoor(Mahjong, 3, 2, Inserir);
	Inserir = 'N';
	MTZ_pushCoor(Mahjong, 4, 2, Inserir);
	Inserir = 'T';
	MTZ_pushCoor(Mahjong, 0, 3, Inserir);
	Inserir = 'C';
	MTZ_pushCoor(Mahjong, 1, 3, Inserir);
	Inserir = 'D';
	MTZ_pushCoor(Mahjong, 2, 3, Inserir);
	Inserir = 'K';
	MTZ_pushCoor(Mahjong, 3, 3, Inserir);
	Inserir = 'A';
	MTZ_pushCoor(Mahjong, 4, 3, Inserir);
	Inserir = 'V';
	MTZ_pushCoor(Mahjong, 0, 4, Inserir);
	Inserir = 'T';
	MTZ_pushCoor(Mahjong, 1, 4, Inserir);
	Inserir = 'R';
	MTZ_pushCoor(Mahjong, 2, 4, Inserir);
	Inserir = 'B';
	MTZ_pushCoor(Mahjong, 3, 4, Inserir);
	Inserir = 'Z';
	MTZ_pushCoor(Mahjong, 4, 4, Inserir);

	// Nivel 2

	Inserir = 'L';
	MTZ_pushCoor(Mahjong, 0, 0, Inserir);
	Inserir = 'P';
	MTZ_pushCoor(Mahjong, 1, 0, Inserir);
	Inserir = 'V';
	MTZ_pushCoor(Mahjong, 2, 0, Inserir);
	Inserir = 'C';
	MTZ_pushCoor(Mahjong, 3, 0, Inserir);
	Inserir = 'R';
	MTZ_pushCoor(Mahjong, 4, 0, Inserir);
	Inserir = 'M';
	MTZ_pushCoor(Mahjong, 0, 1, Inserir);
	Inserir = 'W';
	MTZ_pushCoor(Mahjong, 1, 1, Inserir);
	Inserir = 'X';
	MTZ_pushCoor(Mahjong, 2, 1, Inserir);
	Inserir = 'W';
	MTZ_pushCoor(Mahjong, 3, 1, Inserir);
	Inserir = 'O';
	MTZ_pushCoor(Mahjong, 4, 1, Inserir);
	Inserir = 'Q';
	MTZ_pushCoor(Mahjong, 0, 2, Inserir);
	Inserir = 'K';
	MTZ_pushCoor(Mahjong, 1, 2, Inserir);
	Inserir = 'X';
	MTZ_pushCoor(Mahjong, 2, 2, Inserir);
	Inserir = 'M';
	MTZ_pushCoor(Mahjong, 3, 2, Inserir);
	Inserir = 'I';
	MTZ_pushCoor(Mahjong, 4, 2, Inserir);
	Inserir = 'J';
	MTZ_pushCoor(Mahjong, 0, 3, Inserir);
	Inserir = 'P';
	MTZ_pushCoor(Mahjong, 1, 3, Inserir);
	Inserir = 'B';
	MTZ_pushCoor(Mahjong, 2, 3, Inserir);
	Inserir = 'V';
	MTZ_pushCoor(Mahjong, 3, 3, Inserir);
	Inserir = 'G';
	MTZ_pushCoor(Mahjong, 4, 3, Inserir);
	Inserir = 'H';
	MTZ_pushCoor(Mahjong, 0, 4, Inserir);
	Inserir = 'F';
	MTZ_pushCoor(Mahjong, 1, 4, Inserir);
	Inserir = 'Q';
	MTZ_pushCoor(Mahjong, 2, 4, Inserir);
	Inserir = 'T';
	MTZ_pushCoor(Mahjong, 3, 4, Inserir);
	Inserir = 'E';
	MTZ_pushCoor(Mahjong, 4, 4, Inserir);

	// Nivel 1

	Inserir = 'A';
	MTZ_pushCoor(Mahjong, 0, 0, Inserir);
	Inserir = 'S';
	MTZ_pushCoor(Mahjong, 1, 0, Inserir);
	Inserir = 'M';
	MTZ_pushCoor(Mahjong, 2, 0, Inserir);
	Inserir = 'D';
	MTZ_pushCoor(Mahjong, 3, 0, Inserir);
	Inserir = 'P';
	MTZ_pushCoor(Mahjong, 4, 0, Inserir);
	Inserir = 'G';
	MTZ_pushCoor(Mahjong, 0, 1, Inserir);
	Inserir = 'P';
	MTZ_pushCoor(Mahjong, 1, 1, Inserir);
	Inserir = 'B';
	MTZ_pushCoor(Mahjong, 2, 1, Inserir);
	Inserir = 'Q';
	MTZ_pushCoor(Mahjong, 3, 1, Inserir);
	Inserir = 'S';
	MTZ_pushCoor(Mahjong, 4, 1, Inserir);
	Inserir = 'E';
	MTZ_pushCoor(Mahjong, 0, 2, Inserir);
	Inserir = 'H';
	MTZ_pushCoor(Mahjong, 1, 2, Inserir);
	Inserir = 'J';
	MTZ_pushCoor(Mahjong, 2, 2, Inserir);
	Inserir = 'I';
	MTZ_pushCoor(Mahjong, 3, 2, Inserir);
	Inserir = 'D';
	MTZ_pushCoor(Mahjong, 4, 2, Inserir);
	Inserir = 'T';
	MTZ_pushCoor(Mahjong, 0, 3, Inserir);
	Inserir = 'Q';
	MTZ_pushCoor(Mahjong, 1, 3, Inserir);
	Inserir = 'K';
	MTZ_pushCoor(Mahjong, 2, 3, Inserir);
	Inserir = 'F';
	MTZ_pushCoor(Mahjong, 3, 3, Inserir);
	Inserir = 'A';
	MTZ_pushCoor(Mahjong, 4, 3, Inserir);
	Inserir = 'C';
	MTZ_pushCoor(Mahjong, 0, 4, Inserir);
	Inserir = 'O';
	MTZ_pushCoor(Mahjong, 1, 4, Inserir);
	Inserir = 'M';
	MTZ_pushCoor(Mahjong, 2, 4, Inserir);
	Inserir = 'R';
	MTZ_pushCoor(Mahjong, 3, 4, Inserir);
	Inserir = 'L';
	MTZ_pushCoor(Mahjong, 4, 4, Inserir);
}