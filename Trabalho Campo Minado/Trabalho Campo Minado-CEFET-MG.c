#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define limpar system("clear||cls");

//variáveis globais
int dificuldade = 10, quantBOMBAS;
char char1, char2;
char dif[10];
int matrizBOMBAS[100][100], cont = 0;
unsigned char matriz[100][100];
char nome[64];
int pontos = 0;
int jogardnv = 0;
int hora1, hora2, hora3;

void gerar(){   //Atribui o valor '-' a todas as posições no tabuleiro de caracteres
	int i, j;
	for(i = 0; i < dificuldade; i++){
	    for(j = 0; j < dificuldade; j++){
			matriz[i][j] = '-';
		}
	}
}

void menu()   //Tela inicial mostrada ao usário do qual vai mostrar escolhas
{
  	if(dificuldade == 10){  //se a matriz for 10x10, entao a dificuldade é facil
    	strcpy(dif, "Fácil");
  	}
  	else if(dificuldade == 15){ //se a matriz for 15x15, entao a dificuldade é medio
    	strcpy(dif, "Médio");
  	}
  	else if(dificuldade == 20){ //se a matriz for 20x20, entao a dificuldade é dificil
   	 	strcpy(dif, "Difícil");
  	}
  	printf("*************************");
  	printf("\n\n");
  	printf("   Campo minado em C");
  	printf("\n\n");
  	printf("*************************");
  	printf("\n(a) Jogar\n(b) Alterar dificuldade\t\tDificuldade atual: %s\n(c) Sair\n ", dif);
  	fflush(stdin);
  	scanf(" %c", &char1); //ler a escolha
}

void config() //definir a dificuldade e o tamnho do tabuleiro
{
  	limpar;
  	fflush(stdin);
  	printf("Dificuldade:\n");
  	printf(" (a) Fácil: 10x10\t10 bombas\n (b) Médio: 15x15\t40 bombas\n (c) Difícil: 20x20\t99 bombas\n  ");
  	scanf("%c", &char2);  //ler a opcao de dificuldade
}

void instrucao()  //explicar regras do jogo
{
  	limpar;
  	printf("Bem vindo ao Jogo de Campo Minado!!!\n");
  	printf("A área de jogo consiste num campo de quadrados retangular,que pode ser representado através de uma matriz M x M. Ao se  referir ao endereço de determinada posição dentro da matriz as seguintes situações podem ocorrer:\n\n1. Encontrar uma bomba;\n\n2. Encontrar um espaço vazio\n\n3. Encontrar um valor que indicará o número de bomba(s) existente(s) nas adjacências da posição.\n\n");
  	printf("Ganha-se o jogo quando todos os quadrados que não tem minas são revelados\n\n");
}

void tabuleiro()  //mostrar o nome, a pontuacao e a qunat de bombas, alem de mostrar o tabuleiro para o usuario
{
	int LINHA, COLUNA, i, j;

	printf("Nome: %s\tPontuação: %d\tBombas Restantes: %d\n\n", nome, pontos, quantBOMBAS);
    printf("   ");
    for(i = 0; i < dificuldade; i++)
        printf("%4d", i);
    	printf("\n\n");
    for(i = 0; i < dificuldade; i++){
        printf("%3d", i);
        for(j = 0; j < dificuldade; j++){
            printf("%4c", matriz[i][j]);
        }
        printf("\n\n");
    }
}

void escolha(){   //definir o que acontecera com o programa de acordo com a escolha do menu
	switch(char1){
    case 'a':

      		break;

    case 'b':
    	do{
    	config();
        char2 = tolower(char2);

        if(char2 == 'a'){ //facil
    	    dificuldade = 10;
    	    quantBOMBAS = 10;
  		}else if(char2 == 'b'){ //medio
    	    dificuldade = 15;
    	    quantBOMBAS = 40;
  		}else if(char2 == 'c'){ //dificil
    	    dificuldade = 20;
    	    quantBOMBAS = 99;
  		}else{  //caso ele nao digite nenhuma das opcoes dadas
    	    printf("\nOpção invalida!!!!!!\n\n");
      	}
     	}
      	while(char2 != 'a' && char2 != 'b' && char2 != 'c');
      	limpar;
      	menu(); //apos definir a dificuldade, limpar tela e voltar para o menu
      	escolha();
   	  		break;

    case 'c':  //sair do codigo
        printf("\nVocê saiu!"); 
        exit(0);
      		break;
	}
}



void bombasaleatorias(){  //definir as posicoes das bombas

	int bombas, i, j;
	  //inicializando a matriz
	for(i = 0; i < dificuldade; i++){
		for(j = 0; j < dificuldade; j++){
			  //iniciando a matriz com zero
			  matrizBOMBAS[i][j] = 0;

		}
	}
	//carregar as bombas
	bombas = 0;
	while(bombas < quantBOMBAS){
		  //escolher uma posição aleatória
		  i = rand() % dificuldade;
		  j = rand() % dificuldade;

		  //verifica se existe bomba na posição, se não ele incrementa as bombas
		if(matrizBOMBAS[i][j] == 0){
        	//se não, incrementa as bombas
        	matrizBOMBAS[i][j] = -1;
        	bombas++;
		}

	}


}

void jogar(){ //ler a linha e a coluna e dar opcaoes para oq fzr com a posicao

	int LINHA, COLUNA, i, j;
	char opcao;
	int win = 0, contador1 = 0, bombasADC;
	do{
		printf("\nDigite a linha que deseja: ");
	    scanf("%d", &LINHA);
	    printf("\nDigite a coluna que deseja: ");
	    scanf("%d", &COLUNA);
	    fflush(stdin);
	    printf("\n");
		printf("Deseja marcar com:\n(a)Visitar a posição\n(b)Marcar a posição com dúvida\n(c)Marcar com uma bandeira de bomba \n");
		fflush(stdin);
		scanf("%c", &opcao);
		limpar;

	    switch(opcao){  //switch com opcao
	    	case 'b': //se ele escolher interrogacao trocar no tabuleiro
	    		matriz[LINHA][COLUNA] = '?';
	 			tabuleiro();
	    		break;
	    	case 'c': //se escolher bandeira, atualizar no tabuleiro
	    		matriz[LINHA][COLUNA] = 'B';
	    		if(matrizBOMBAS[LINHA][COLUNA] == -1){
	    		    quantBOMBAS--;  //diminuir 1 bomba caso o usuario acerte a bandeira
	    		}
	    		tabuleiro();
	    		break;
	    	case 'a': //se escolher visitar a casa, verificar se a posição é uma bomba e verificar as casas nos arredores
						if(matrizBOMBAS[LINHA][COLUNA] == -1){

							win = 1;

							limpar;
							printf("Nome: %s\tPontuação: %d\tBombas Restantes: %d\n\n",nome, pontos, quantBOMBAS);  //imprimir e atualizar a matriz
    						printf("   ");
							for(i = 0; i < dificuldade; i++)
        						printf("%4d", i);
    							printf("\n\n");
    							for(i = 0; i < dificuldade; i++){
        							printf("%3d", i);
        							for(j = 0; j < dificuldade; j++){
        								if(matrizBOMBAS[i][j] == -1){
		        							matriz[i][j] = '*';
										}
            							printf("%4c", matriz[i][j]);
        							}
        								printf("\n\n");
    							}


							printf("Você perdeu\n\n");
							printf("Você fez %d pontos", pontos);
							hora2 = time(NULL);
							hora3 = hora2 - hora1;
							printf("\n\nVocê demorou %d segundos\n\n", hora3);  //mostrar o tempo em que o usuario jogou o jogo
							printf("Quer jogar denovo?\n (1) Sim\n (0) Não\n  ");
							scanf("%d", &jogardnv);
							getchar();
							fflush(stdin);
							    break;

					    }else{

							for(i = -1; i < 2; i++){
								for(j = -1; j < 2; j++){
									if(matrizBOMBAS[LINHA+i][COLUNA+j] == 0){ //se os arredores nao forem nenhuma bomba, eles serao '0'
										matriz[LINHA][COLUNA] = 0;
									}else{
										cont++; //se eles forem bombas, aumentar mais um
									}
								}
							}
						}
						matriz[LINHA][COLUNA] = cont + '0'; //contar quantas bombas tem em volta da posicao escolhida
						if(matriz[LINHA][COLUNA] != '0'){
							pontos++; //1 ponto caso a casa nao seja uma bomba nem uma casa vazia
						}
						cont = 0;
						contador1 = 0;
						if(matriz[LINHA][COLUNA] == '0'){ //se a posicao for igual a 0, 9 pontos
							for(i = -1; i < 2; i++){
								for(j = -1; j < 2; j++){
									bombasADC = revelarcasasadj(LINHA+i, COLUNA+j);
									if(matriz[LINHA+i][COLUNA+j] == '-'){
										contador1++; //se a posicao escolhida for igual a 0, conta o núnero de casas vizinhas que abriram
									}
									if(i != 0 || j != 0){
										if(matriz[LINHA+i][COLUNA+j] == '-'){
											matriz[LINHA+i][COLUNA+j] = bombasADC + '0';
										}
									}

								}
							}
							pontos += contador1;
							pontos++;
						}
				    	for(i = 0; i < dificuldade; i++){
		        			for(j = 0; j < dificuldade; j++){
						    	if(matrizBOMBAS[i][j] != -1){
							    	if(matriz[i][j] != '-'){
									}
								}
							}
						}
				limpar;
				if(win == 0){
					tabuleiro();
				}
				if(quantBOMBAS == 0){
					ganhar();
					win = 1;
				}
				    break;

			default:
				printf("\nOpção invalida\n");
				tabuleiro();
				    break;
		}
	}while(win == 0);
}

int revelarcasasadj(int LINHA, int COLUNA){ //revelar as casas adjacentes

	int i, j, n1, n2;
	int cont = 0;

	for(i = -1; i < 2; i++){
		for(j = -1; j < 2; j++){
			if(matrizBOMBAS[LINHA + i][COLUNA + j] == -1){
				cont++;
			}
		}
	}

	return cont;
}

void ganhar(){  //mostrar oque acontecera caso o usuario ganhe

	if(quantBOMBAS == 0){
		printf("Você venceu\n");
		printf("Parabéns!!!!!\n");
		printf("Você fez %d pontos\n" , pontos);
		hora2 = time(NULL);
		hora3 = hora2 - hora1;
		printf("\n\nVocê demorou %d segundos\n\n", hora3);
		printf("Quer jogar denovo?\n (1) Sim\n (0) Não\n"); //caso o usuario queira jogar de novo
		scanf("%d", &jogardnv);
		getchar();
		fflush(stdin);
	}
}


int main()
{
	setlocale(LC_ALL, "Portuguese");  //permitir acentuação

	int i, j;
	char opcao;


	time_t currentTime;
	time(&currentTime);

	limpar;

	typedef long time_t;
	srand(time(NULL));

	do{
    limpar;
    dificuldade = 10;
    quantBOMBAS = 10;
    pontos = 0;
    jogardnv = 0;

    menu();
    escolha();
    fflush(stdin);
    instrucao();
    fflush(stdin);

    printf("\n\nDigite seu nome: ");  //pedir o nome do usuario
    gets(nome);

    gerar();
    limpar;
    hora1 = time(NULL);
    tabuleiro();
    bombasaleatorias();
    jogar();
	}while(jogardnv == 1); //repetir enquanto o usuario querer jogar denovo

	  return 0;
}
