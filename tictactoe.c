include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//PROJETO DE INTRODUÇÃO À PROGRAMAÇÃO 2 EM C DA UNICAP
//PROJETO FEITO POR BRUNO HENRIQUE SILVA DO NASCIMENTO
 
void umJogador(char jogador[], int nivel, char tabuleiro[][3]);
void multijogador(char jogador1[], char jogador2[], char tabuleiro[][3]);
void exibirTab(char tabuleiro[][3]);
int deuVelha(char tabuleiro[][3], char simbolo);
int validaPosicao(char tabuleiro[][3], int linha, int coluna);
void nivelUm(char jogador[], char tabuleiro[][3]);
void nivelDois(char jogador[], char tabuleiro[][3]);
void limparTabuleiro(char tabuleiro[][3]);
int taArmado(char tabuleiro[][3], char simbolo);
 
int main() {
	int op = 1, opJogador = 0, opNivel = 0;
	char jogador1[20], jogador2[20] , tabuleiro[3][3];
	int i, linha, coluna;
 
	printf("JOGO DA VELHA\n");
	do {
		do {
			printf("1 - Jogar\n2 - Sair\nDigite sua opcao: ");
			scanf("%d", &op);
			fflush(stdin);
		} while (op < 1 || op > 2);
		switch (op) {
		case 1:
			system("cls");
			do {
				printf("1 - Um jogador\n2 - Dois jogadores\nDigite sua opcao: ");
				scanf("%d", &opJogador);
				fflush(stdin);
			} while (opJogador < 1 || opJogador > 2);
 
			if (opJogador == 1) {
				//MAQUINA VS. HOMEM
				printf("Informe o nome do jogador humano: ");
				fgets(jogador1, 20, stdin);
				fgets(jogador1, 20, stdin);
				fflush(stdin);
				printf("\nNIVEL DO JOGO\n1 - Facil\n2 - Dificil\nDigite sua opcao: ");
				scanf("%d", &opNivel);
				system("cls");
				limparTabuleiro(tabuleiro);
				umJogador(jogador1, opNivel, tabuleiro);
 
			}
			else {
				//MULTIJOGADOR
				printf("Informe o nome do jogador 1: ");
				fgets(jogador1, 20, stdin);
				fgets(jogador1, 20, stdin);
				fflush(stdin);
				printf("Informe o nome do jogador 2: ");
				fgets(jogador2, 20, stdin);
				fflush(stdin);
				limparTabuleiro(tabuleiro);
				multijogador(jogador1, jogador2, tabuleiro);
			}
			break;
		case 2:
			printf("Obrigado por jogar!\n");
			op = 2;
			break;
		default:
			printf("Opcao invalida!\n");
			break;
 
		}
	} while (op == 1);
 
	return 0;
 
}
void limparTabuleiro(char tabuleiro[][3]) {
	int linha, coluna;
	int cont = 0;
	char simbolo1 = '_';
	for (linha = 0; linha < 3; linha++) {
		for (coluna = 0; coluna < 3; coluna++) {
			tabuleiro[linha][coluna] = simbolo1;
 
 
		}
	}
}
void umJogador(char jogador[], int nivel, char tabuleiro[][3]) {
	int primeiroJogador, i;
	int vezDeJogar = 0;
	int linha = 0, coluna = 0;
	int ganhou = 0;
	int cont = 0;
	printf("X - %s\nO - Computador\n", jogador);
	printf("Sorteando quem vai começar ");
	for (int i = 0; i < 3; i++) {
		printf(".");
 
	}
	if (nivel == 1) {
		nivelUm(jogador, tabuleiro);
	}
	else {
		nivelDois(jogador, tabuleiro);
	}
}
 
void multijogador(char jogador1[], char jogador2[], char tabuleiro[][3]) {
	int primeiroJogador, vezDejogar = 0, i;
	int linha, coluna, validacao = 0, cont = 0;
	printf("X - %s\n", jogador1);
	printf("O - %s\n", jogador2);
	printf("Sorteando quem vai começar...");
	srand((unsigned)time(NULL));
	primeiroJogador = rand() % 2;
	if (primeiroJogador == 0) {
		printf("%s vai comecar...", jogador1);
		system("cls");
		exibirTab(tabuleiro);
		vezDejogar = 1;
	}
	else {
		printf("%s vai comecar...", jogador2);
		system("cls");
		exibirTab(tabuleiro);
		vezDejogar = 0;
	}
	for (i = 0; i < 9; i++) {
		if (vezDejogar == 1) {
			printf("Vez de %s de jogar!\n", jogador1);
			do {
				printf("Informe a linha: ");
				scanf("%d", &linha);
				linha--;
				fflush(stdin);
				printf("Informe a coluna: ");
				scanf("%d", &coluna);
				coluna--;
				fflush(stdin);
				validacao = validaPosicao(tabuleiro, linha, coluna);
			} while (validacao == 0);
			tabuleiro[linha][coluna] = 'X';
			system("cls");
			exibirTab(tabuleiro);
			if (deuVelha(tabuleiro, 'X') == 1) {
				printf("O(A) jogador(A)%s ganhou!\n", jogador1);
				break;
			}
			cont++;
			vezDejogar = 0;
		}
		else {
			printf("Vez de %s de jogar!\n", jogador2);
			do {
				printf("Informe a linha: ");
				scanf("%d", &linha);
				linha--;
				fflush(stdin);
				printf("Informe a coluna: ");
				scanf("%d", &coluna);
				coluna--;
				fflush(stdin);
				validacao = validaPosicao(tabuleiro, linha, coluna);
			} while (validacao == 0);
			tabuleiro[linha][coluna] = 'O';
			system("cls");
			exibirTab(tabuleiro);
			if (deuVelha(tabuleiro, 'O') == 1) {
				printf("O(A) jogador(a)%s ganhou!\n", jogador2);
				break;
			}
			cont++;
			vezDejogar = 1;
		}
		if (cont == 9) {
			printf("O jogo empatou!\n");
			break;
		}
 
	}
 
}
 
void exibirTab(char tabuleiro[][3]) {
	int linha, coluna;
	int aux;
	system("cls");
	for (linha = 0; linha < 3; linha++){
		for (coluna = 0; coluna < 3; coluna++) {
			printf("%c", tabuleiro[linha][coluna]);
			if (coluna < 2){
				printf("|");
			}
		}
		printf("\n");
	}
}
 
int deuVelha(char tabuleiro[][3], char simbolo) {
	if (tabuleiro[1][1] != simbolo) {
		if (tabuleiro[0][0] == simbolo && tabuleiro[0][1] == simbolo && tabuleiro[0][2] == simbolo) {
			return 1;
		}
		else if (tabuleiro[0][0] == simbolo && tabuleiro[1][0] == simbolo && tabuleiro[2][0] == simbolo) {
			return 1;
		}
		else if (tabuleiro[2][0] == simbolo && tabuleiro[2][1] == simbolo && tabuleiro[2][2] == simbolo) {
			return 1;
		}
		else if (tabuleiro[0][2] == simbolo && tabuleiro[1][2] == simbolo && tabuleiro[2][2] == simbolo) {
			return 1;
		}
	}
	else {
		if (tabuleiro[0][0] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][2] == simbolo) {
			return 1;
		}
		else if (tabuleiro[0][2] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][0] == simbolo) {
			return 1;
		}
		else if (tabuleiro[0][1] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][1] == simbolo) {
			return 1;
		}
		else if (tabuleiro[1][0] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[1][2] == simbolo) {
			return 1;
		}
	}
	return 0;
}
int validaPosicao(char tabuleiro[][3], int linha, int coluna) {
	if (tabuleiro[linha][coluna] == 'X' || tabuleiro[linha][coluna] == 'O') {
		return 0;
	}
	else {
		return 1;
	}
}
 
void nivelUm(char jogador[], char tabuleiro[][3]) {
	int primeiroJogador, i;
	int vezDeJogar = 0;
	int linha = 0, coluna = 0;
	int ganhou = 0;
	int cont = 0;
 
	srand((unsigned)time(NULL));
	primeiroJogador = rand() % 2;
	if (primeiroJogador == 0) {
		printf("%s vai comecar...", jogador);
		system("cls");
		exibirTab(tabuleiro);
		vezDeJogar = 0;
	}
	else {
		printf("O computador vai comecar...\n");
		system("cls");
		exibirTab(tabuleiro);
		vezDeJogar = 1;
	}
	//laço para ficar rodando até ocorrer alguma vitória ou empate
	//sendo 1 para vitória e 0 porque não houve vitórias
	while (ganhou == 0) {
		if (vezDeJogar == 0) {
			printf("%s eh sua vez de jogar.\n", jogador);
			//usuario
			do {
				exibirTab(tabuleiro);
				printf("Informe a linha: ");
				scanf("%d", &linha);
				fflush(stdin);
				//subtrai para manusear corretamente a matriz
				linha--;
				printf("Informe a coluna: ");
				scanf("%d", &coluna);
				fflush(stdin);
				//subtrai para manusear corretamente a matriz
				coluna--;
				cont++;
				system("cls");
			} while (validaPosicao(tabuleiro, linha, coluna) == 0);
 
			tabuleiro[linha][coluna] = 'X';
			exibirTab(tabuleiro);
			if (deuVelha(tabuleiro, 'X') == 1) {
				printf("\n%s ganhou!\n", jogador);
				break;
				ganhou = 1;
			}
			vezDeJogar = 1;
		}
		else {
			//maquina
			printf("Eh a vez do computador de jogar.\n");
 
			do{
				srand((unsigned)time(NULL));
				linha = rand() % 3;
				srand((unsigned)time(NULL));
				coluna = rand() % 3;
			} while (validaPosicao(tabuleiro, linha, coluna) == 0);
			tabuleiro[linha][coluna] = 'O';
			cont++;
			system("cls");
			exibirTab(tabuleiro);
			if (deuVelha(tabuleiro, 'O') == 1) {
				printf("\nO computador ganhou!\n");
				break;
				ganhou = 1;
			}
			vezDeJogar = 0;
 
		}
 
		if (cont == 9) {
			printf("Empate!\n");
			break;
		}
	}
}
 
int taArmado(char tabuleiro[][3], char simbolo) {
	int linha, coluna, contLinha = 0, aux, contColuna = 0, contDiagonalP = 0, contDiagonalS = 0;
	for (linha = 0; linha < 3; linha++) {
		for (coluna = 0; coluna < 3; coluna++) {
			if (tabuleiro[linha][coluna] == simbolo) { //checa linha por linha
				contLinha++;
			}
			if (tabuleiro[coluna][linha] == simbolo) {  //checa coluna por coluna
				contColuna++;
			}
			if (linha == coluna && tabuleiro[linha][coluna] == simbolo) { //checa a diagonal principal
				contDiagonalP++;
			}
			if (linha + coluna == 2 && tabuleiro[linha][coluna] == simbolo) { //checa a diagonal secundária, tendo em vista 
				contDiagonalS++;                                                   //que a contagem de uma matriz 3x3 começa do 0 e vai até 2
			}
		}
		if (contLinha == 2) {
			for (aux = 0; aux < 3; aux++) {
				if (tabuleiro[linha][aux] == '_') {  // procura espaço vago na linha para jogar
					tabuleiro[linha][aux] = 'O';
					return 1;
				}
			}
		}
		if (contColuna == 2) {
			for (aux = 0; aux < 3; aux++) {
				if (tabuleiro[aux][linha] == '_') {  //procura espaço vago na coluna para jogar
					tabuleiro[aux][linha] = 'O';
					return 1;
				}
			}
		}
 
	}
	if (contDiagonalP == 2) {
		for (linha = 0; linha < 3; linha++) {
			for (coluna = 0; coluna < 3; coluna++) {
				if (linha == coluna && tabuleiro[linha][coluna] == '_') { // procura espaço vago na diagonal principal para jogar
					tabuleiro[linha][coluna] = 'O';
					return 1;
				}
			}
		}
	}
	if (contDiagonalS == 2) {
		for (linha = 0; linha < 3; linha++) {
			for (coluna = 0; coluna < 3; coluna++) {
				if (linha + coluna == 2 && tabuleiro[linha][coluna] == '_') { //procura espaço vago na diagonal secundaria para jogar
					tabuleiro[linha][coluna] = 'O';
					return 1;
				}
			}
		}
	}
	return 0;
}
void nivelDois(char jogador[], char tabuleiro[][3]) {
	int primeiroJogador, i;
	int vezDeJogar = 0;
	int linha = 0, coluna = 0;
	int ganhou = 0;
	int cont = 0;
 
	srand((unsigned)time(NULL));
	primeiroJogador = rand() % 2;
	if (primeiroJogador == 0) {
		printf("%s vai comecar...", jogador);
		system("cls");
		exibirTab(tabuleiro);
		vezDeJogar = 0;
	}
	else {
		printf("O computador vai comecar...\n");
		system("cls");
		exibirTab(tabuleiro);
		vezDeJogar = 1;
	}
	//laço para ficar rodando até ocorrer alguma vitória ou empate
	//sendo 1 para vitória e 0 porque não houve vitórias
	while (ganhou == 0) {
		if (vezDeJogar == 0) {
			printf("%s eh sua vez de jogar.\n", jogador);
			vezDeJogar = 1;
			//usuario
			do {
				exibirTab(tabuleiro);
				printf("Informe a linha: ");
				scanf("%d", &linha);
				fflush(stdin);
				//subtrai para manusear corretamente a matriz
				linha--;
				printf("Informe a coluna: ");
				scanf("%d", &coluna);
				fflush(stdin);
				//subtrai para manusear corretamente a matriz
				coluna--;
				cont++;
				system("cls");
			} while (validaPosicao(tabuleiro, linha, coluna) == 0);
 
			tabuleiro[linha][coluna] = 'X';
			exibirTab(tabuleiro);
			if (deuVelha(tabuleiro, 'X') == 1) {
				printf("\n%s ganhou!\n", jogador);
				break;
				ganhou = 1;
			}
 
		}
		else {
			//maquina
			printf("Eh a vez do computador de jogar.\n");
			if (taArmado(tabuleiro, 'O') == 1) {
				cont++;
			}
			else if (taArmado(tabuleiro, 'X') == 1) {
				cont++;
			}
			else {
				while (validaPosicao(tabuleiro, linha, coluna) == 0) {
					srand((unsigned)time(NULL));
					linha = rand() % 3;
					srand((unsigned)time(NULL));
					coluna = rand() % 3;
				}
				tabuleiro[linha][coluna] = 'O';
				cont++;
			}
			system("cls");
			exibirTab(tabuleiro);
			if (deuVelha(tabuleiro, 'O') == 1) {
				printf("\nO computador ganhou!\n");
				break;
				ganhou = 1;
			}
			vezDeJogar = 0;
		}
		if (cont == 9) {
			printf("Empate!\n");
			break;
		}
	}
}