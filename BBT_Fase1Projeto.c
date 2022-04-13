#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>

//STRUCTS GLOBAIS - PARA TODAS FASES

typedef struct sPlayer{
    int sentido;
}Player;

typedef struct sComandos{
    int tipodecom;
    int vezes;
}Comandos;

typedef struct sNO{
    Comandos info;
    struct sNO* prox;
}NO;

//STRUCTS PARA FASE 1
 
typedef struct sFila{
    NO* inicio;
    NO* fim;
}Fila;

//FUN��ES GLOBAIS - PARA TODAS FASES

NO* alocarNo(){
    return (NO*)malloc(sizeof(NO));
}

void desalocacao(NO *mat){
	
	free(mat);
}

void Preenche(char Tab[8][8]){
	Tab[0][0] = 'P'; Tab[0][1] = ' '; Tab[0][2] = ' '; Tab[0][3] = ' '; Tab[0][4] = ' '; Tab[0][5] = ' '; Tab[0][6] = ' '; Tab[0][7] = 'X';
	Tab[1][0] = ' '; Tab[1][1] = ' '; Tab[1][2] = ' '; Tab[1][3] = ' '; Tab[1][4] = ' '; Tab[1][5] = ' '; Tab[1][6] = ' '; Tab[1][7] = ' ';
	Tab[2][0] = 'X'; Tab[2][1] = ' '; Tab[2][2] = ' '; Tab[2][3] = ' '; Tab[2][4] = ' '; Tab[2][5] = ' '; Tab[2][6] = 'X'; Tab[2][7] = ' ';
	Tab[3][0] = ' '; Tab[3][1] = 'X'; Tab[3][2] = ' '; Tab[3][3] = ' '; Tab[3][4] = 'X'; Tab[3][5] = ' '; Tab[3][6] = ' '; Tab[3][7] = ' ';
	Tab[4][0] = ' '; Tab[4][1] = ' '; Tab[4][2] = ' '; Tab[4][3] = 'X'; Tab[4][4] = ' '; Tab[4][5] = 'X'; Tab[4][6] = ' '; Tab[4][7] = 'X';
	Tab[5][0] = ' '; Tab[5][1] = 'X'; Tab[5][2] = ' '; Tab[5][3] = ' '; Tab[5][4] = ' '; Tab[5][5] = ' '; Tab[5][6] = ' '; Tab[5][7] = ' ';
	Tab[6][0] = ' '; Tab[6][1] = ' '; Tab[6][2] = ' '; Tab[6][3] = ' '; Tab[6][4] = 'X'; Tab[6][5] = 'X'; Tab[6][6] = ' '; Tab[6][7] = ' ';
	Tab[7][0] = ' '; Tab[7][1] = ' '; Tab[7][2] = ' '; Tab[7][3] = ' '; Tab[7][4] = ' '; Tab[7][5] = ' '; Tab[7][6] = ' '; Tab[7][7] = 'O';
}

void sentido(Player playerzin){

	if(playerzin.sentido == 2){
	
		printf("Para direita\n");

	}

	if(playerzin.sentido == 3){
	
		printf("Para baixo\n");
		
	}

	if(playerzin.sentido == 4){
	
		printf("Para esquerda\n");
		
	}

	if(playerzin.sentido == 1){
	
		printf("Para cima\n");
		
	}
}

void ExibeTabuleiro1(char Tab[8][8], Player jogador){
		setlocale(LC_ALL, "Portuguese");
 		int i,j;
 		for(i = 0; i < 8; i++){
			for(j = 0; j < 8; j++){
	 			printf("| %c ", Tab[i][j]);
			}
			printf("|");
			printf("\n");
			printf("---------------------------------");
			printf("\n");
	 	}
 	
	 	printf("Sentido do Player no tabuleiro:\n");
	 	printf("|P| - ");
	 	sentido(jogador);
	 	printf("\nComandos:\n");
	 	printf("1)   F F\n\n");
	 	printf("2)   E F\n\n");
	 	printf("3)   D F\n");

}

//FUN��ES PARA FASE 1 E 3 (IDA)
 
void inic(Fila *ptr){
 
    ptr->inicio = NULL;
    ptr->fim = NULL;
}

int vazia(Fila *ptr){
 
    if(ptr->inicio == NULL){
        return 1;
    }else{
    	return 0;
	}
}

void desenfileirar(Fila *ptr){
	NO *aux;
	if(ptr->fim == ptr->inicio){  //S� H� UM ELEMENTO NA FILA
		desalocacao(ptr->inicio);
		ptr->fim = NULL;
		ptr->inicio = NULL;
	}else{
		aux = ptr->inicio;
		ptr->inicio = (ptr->inicio)->prox;
		desalocacao(aux);
	}
}

int ExecucaoFila(char Tab[8][8], Fila *ptr, Player jogador){
	
	int atualiza;

	if(vazia(ptr) == 1){
		printf("\nA Fila de comandos est� vazia!!\n");
		atualiza = jogador.sentido;
		return atualiza;
	}else{
		NO* aux;
		int repe, i, j, pos = 1, k, l;
		while(ptr->inicio != NULL){
			aux = ptr->inicio;
			repe = aux->info.vezes;
			
			//COMANDOS DO TIPO 1
			if(aux->info.tipodecom == 1){ // PODEMOS MOVIMENTAR 3 POSI��ES EM TODOS SENTIDOS!!!!!
			while(repe != 0){
				int verifica;				
				if(jogador.sentido == 2){ // SE FOR PARA DIREITA, VAI SER EXECUTADO DESSA FORMA
					for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
						for(j = 0; j < 8; j++){
							if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
								Tab[i][j] = ' ';
								k = i;
								l = j;
								break;
							}
						}
					}

					for(verifica = l; verifica < l+3; verifica++){  //PERCORRE AT� TR�S POSI��ES PARA FRENTE PARA VER SE CONT�M 'X' OU EST� VAZIA
						if(verifica >= 8){ // A POSI��O EXISTE NO TABULEIRO?
							printf("\nPosi��o inexistente!\n");
							desenfileirar(ptr);
							return 0;
						}else{
							if(Tab[k][verifica] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, verifica);
								desenfileirar(ptr);
								return 0;
							}
							if(Tab[k][verifica] == 'O'){  //GANHOU
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desenfileirar(ptr);
								return 5;
							}		
						}	
					}			
					Tab[k][l + 2] = 'P';  //MOVIMENTA P, CASO N�O ENTRAR EM NENHUM CONDI��O
				}
						
				if(jogador.sentido == 3){ // SE FOR PARA BAIXO, VAI SER EXECUTADO DESSA FORMA
					for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
						for(j = 0; j < 8; j++){
							if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
								Tab[i][j] = ' ';
								k = i;
								l = j;
								break;
							}
						}
					}
								
						for(verifica = k; verifica < k+3; verifica++){  //PERCORRE AT� TR�S POSI��ES PARA FRENTE PARA VER SE CONT�M 'X' OU EST� VAZIA
							if(verifica >= 8){
								printf("\nPosi��o inexistente!\n");
								desenfileirar(ptr);
								return 0;
							}else{
								if(Tab[verifica][l] == 'X'){ // ACHOU X E PERDEU A FASE		
									printf("\nA coordenada (%d, %d) cont�m um X!!\n", verifica, l);
									desenfileirar(ptr);
									return 0;
								}
								if(Tab[verifica][l] == 'O'){
									printf("\nUsu�rio chegou ao objetivo\n");
									Tab[7][7] = 'P';
									ExibeTabuleiro1(Tab, jogador); 
									desenfileirar(ptr);
									return 5;
								}	
							}	
						}
						Tab[k + 2][l] = 'P';
				}
		
				if(jogador.sentido == 4){ // SE FOR PARA ESQUERDA, VAI SER EXECUTADO DESSA FORMA
					for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
						for(j = 0; j < 8; j++){
							if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
								Tab[i][j] = ' ';
								k = i;
								l = j;
								break;
							}
						}
					}
					
					for(verifica = l; verifica < l-3; verifica--){  //PERCORRE AT� TR�S POSI��ES PARA FRENTE PARA VER SE CONT�M 'X' OU EST� VAZIA
						if(verifica < 0){
							printf("\nPosi��o inexistente!\n");
							desenfileirar(ptr);
							return 0;
						}else{
							if(Tab[k][verifica] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, verifica);
								desenfileirar(ptr);
								return 0;
							}
							if(Tab[k][verifica] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desenfileirar(ptr);
								return 5;
							}	
						}		
					}
					Tab[k][l - 2] = 'P';
				}
			
				if(jogador.sentido == 1){ // SE FOR PARA CIMA, VAI SER EXECUTADO DESSA FORMA
					for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
						for(j = 0; j < 8; j++){
							if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
								Tab[i][j] = ' ';
								k = i;
								l = j;
								break;
							}
						}
					}
								
					
					for(verifica = k; verifica < k-3; verifica--){  //PERCORRE AT� TR�S POSI��ES PARA FRENTE PARA VER SE CONT�M 'X' OU EST� VAZIA
						if(verifica < 0){
							printf("\nPosi��o inexistente!\n");
							desenfileirar(ptr);
							return 0;
						}else{
							if(Tab[verifica][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", verifica, l);
								desenfileirar(ptr);
								return 0;
							}
							if(Tab[verifica][l] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desenfileirar(ptr);
								return 5;
							}	
						}		
					}	
					Tab[k - 2][l] = 'P';
				}
				repe--;
			}
				desenfileirar(ptr);   //DESENFILERA TODO COMANDO QUE N�O GERAR UMA PERDA OU UM GANHO DA FASE! EST� FORA DO WHILE POIS O MESMO COMANDO PODE TER REPETI��ES ANTES DE SER DE FATO EXCLUIDO
				
				ExibeTabuleiro1(Tab, jogador);  
				printf("\n---------------------------------------------\n");
				printf("****FIM DO COMANDO NA POSI��O %d da FILA****!\n", pos);
				printf("---------------------------------------------\n\n");
				pos++;
				if(ptr->inicio == NULL){
					pos = 0;   // REINICIA A CONTAGEM DE COMANDOS AP�S FICAR VAZIA
					printf("\n\n\n");
					atualiza = jogador.sentido;
					return atualiza;    //RETORNA PARA A MAIN A POSI��O QUE O JOGADOR EST�, ASSIM, A VARI�VEL CRIADA NA MAIN TAMB�M SER� ATUALIZADA L� AP�S COMANDOS
				}else{
					printf("Deseja prosseguir para o comando %d??\n", pos);
					system("pause");
				}
			}

			//COMANDOS DO TIPO 2
			if(aux->info.tipodecom == 2){
				while(repe != 0){
					
					jogador.sentido--;   // NO COMANDO 2 O JOGADOR VIRA NO SENTIDO ANTI HOR�RIO ANTES DE MOVER UMA POSI��O, DECREMENTANDO A VARI�VEL DE SENTIDO
					if(jogador.sentido == 0){ // OS N�MEROS CORRESPONDENTES V�O DE 1 � 4, QUANDO CHEGAR NO N�MERO ZERO, AUTOMATICAMENTE O PROGRAMA ATRIBUI O VALOR 4 � VARIAVEL, '' VOLTANDO AO INICIO DO CICLO ''
						jogador.sentido = 4;
					}
					
					if(jogador.sentido == 2){ // SE FOR PARA DIREITA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
								
						if(l+1 >= 8){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desenfileirar(ptr);
							return 0;
						}else{
							if(Tab[k][l+1] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, l+1);
								desenfileirar(ptr);
								return 0;
							}
							if(Tab[k][l+1] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desenfileirar(ptr);
								return 5;
							}					
							Tab[k][l+1] = 'P';
						}
					}
							
					if(jogador.sentido == 3){ // SE FOR PARA BAIXO, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
				
						if(k+1 >= 8){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desenfileirar(ptr);
							return 0;
						}else{
							if(Tab[k+1][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k+1, l);
								desenfileirar(ptr);
								return 0;
							}
							if(Tab[k+1][l] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desenfileirar(ptr);
								return 5;
							}		
							Tab[k+1][l] = 'P';
						}
					}
					
					if(jogador.sentido == 4){ // SE FOR PARA ESQUERDA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
						if(l-1 < 0){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desenfileirar(ptr);
							return 0;
						}else{
							if(Tab[k][l-1] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, l-1);
								desenfileirar(ptr);
								return 0;
							}
							if(Tab[k][l-1] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desenfileirar(ptr);
								return 5;
							}	
							Tab[k][l-1] = 'P';
						}
					}
					
					if(jogador.sentido == 1){ // SE FOR PARA CIMA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
								
						if(k-1 < 0){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desenfileirar(ptr);
							return 0;
						}else{
							if(Tab[k-1][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k-1, l);
								desenfileirar(ptr);
								return 0;
							}
							if(Tab[k-1][l] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desenfileirar(ptr);
								return 5;
							}			
							Tab[k-1][l] = 'P';
						}
					}
					
					repe--;
				}
				
				desenfileirar(ptr);
								
				ExibeTabuleiro1(Tab, jogador);  
				printf("\n---------------------------------------------\n");
				printf("****FIM DO COMANDO NA POSI��O %d da FILA****!\n", pos);
				printf("---------------------------------------------\n\n");
				pos++;
				if(ptr->inicio == NULL){
					pos = 0;
					printf("\n\n\n");
					atualiza = jogador.sentido;
					return atualiza;
				}else{
					printf("Deseja prosseguir para o comando %d??\n", pos);
					system("pause");
				}
			}
				
			//COMANDOS DO TIPO 3 --- SEGUE A MESMA LINHA DE RACIOC�NIO DO COMANDO TIPO 2
			if(aux->info.tipodecom == 3){
				while(repe != 0){
					jogador.sentido++; // O JOGADOR VIRA NO SENTIDO HOR�RIO ANTES DE SE MOVIMENTAR, INCREMENTANDO A VARIAVEL DE SENTIDO
					if(jogador.sentido == 5){ // CASO O JOGADOR CHEGUE NO VALOR 5 (N�O EXISTE), ELE VOLTA �O INICIO DO CICLO NO SENTIDO CORRESPONDENTE AO VALOR 1
						jogador.sentido = 1;
					}
					if(jogador.sentido == 2){ // SE FOR PARA DIREITA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
								
						if(l+1 >= 8){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desenfileirar(ptr);
							return 0;
						}else{
							if(Tab[k][l+1] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, l+1);
								desenfileirar(ptr);
								return 0;
							}
							if(Tab[k][l+1] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desenfileirar(ptr);
								return 5;
							}					
							Tab[k][l+1] = 'P';
						}
					}
										
					if(jogador.sentido == 3){ // SE FOR PARA BAIXO, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}

						if(k+1 >= 8){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desenfileirar(ptr);
							return 0;
						}else{
							if(Tab[k+1][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k+1, l);
								desenfileirar(ptr);
								return 0;
							}
							if(Tab[k+1][l] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desenfileirar(ptr);
								return 5;
							}		
							Tab[k+1][l] = 'P';
						}
					}
						
					if(jogador.sentido == 4){ // SE FOR PARA ESQUERDA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
						if(l-1 < 0){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desenfileirar(ptr);
							return 0;
						}else{
							if(Tab[k][l-1] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, l-1);
								desenfileirar(ptr);
								return 0;
							}
							if(Tab[k][l-1] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desenfileirar(ptr);
								return 5;
							}	
							Tab[k][l-1] = 'P';
						}
					}			
								
					if(jogador.sentido == 1){ // SE FOR PARA CIMA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
								
						if(k-1 < 0){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desenfileirar(ptr);
							return 0;
						}else{
							if(Tab[k-1][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k-1, l);
								desenfileirar(ptr);
								return 0;
							}
							if(Tab[k-1][l] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desenfileirar(ptr);
								return 5;
							}			
							Tab[k-1][l] = 'P';
						}
					}
					repe--;
				}
				
				desenfileirar(ptr);
								
				ExibeTabuleiro1(Tab, jogador);  
				printf("\n---------------------------------------------\n");
				printf("****FIM DO COMANDO NA POSI��O %d da FILA****!\n", pos);
				printf("---------------------------------------------\n\n");
				pos++;
				if(ptr->inicio == NULL){
					pos = 0;
					printf("\n\n\n");
					atualiza = jogador.sentido;
					return atualiza;
				}else{
					printf("Deseja prosseguir para o comando %d??\n", pos);
					system("pause");
				}
			}
		
		}
		ptr->fim = NULL;
		ptr->inicio = NULL;
		//QUANDO CHEGAR AQUI, QUER DIZER QUE TODOS OS COMANDOS DA FILA FORAM EXECUTADOS E REMOVIDOS
	}
}

void enfileirar(Fila *ptr, Comandos elem){
    NO* novo;
    novo = alocarNo();
 
    if(novo != NULL){
        novo->info.vezes = elem.vezes;
	  	novo->info.tipodecom = elem.tipodecom;
        novo->prox = NULL;
        if(vazia(ptr) == 1){
            ptr->inicio = novo;
            ptr->fim = novo;
        }else{
            (ptr->fim)->prox = novo;
            ptr->fim = novo;
        }
        printf("Comando inserido com sucesso!\n\n");
    }else{
 
        printf("Problema na alocacao!\n\n");
 
    }
}

//FUN��ES PARA FASE 2 E 3 (VOLTA)

void inicializar(NO **topo){
 
    *topo = NULL;
}

void impressaoNclassica(Fila *ptr){
	NO *aux;
	int i = 1;
	aux = ptr->inicio;
	if(vazia(ptr) == 1){
		printf("\n\nErro, fila vazia\n\n");
	}else{
		while(aux != NULL){
			printf("(%d - %d)", aux->info.tipodecom, aux->info.vezes);
			i++;
			aux = aux->prox;
		}
	}	
}

int pilhaVazia(NO *topo){
	if(topo == NULL){
		return 1;
	}else{
		return 0;
	}
}

void desempilhar(NO **topo){   
	NO *aux;
	aux = *topo;
	if(pilhaVazia(*topo) == 0){  // H� ITENS NA LISTA
		*topo = aux->prox;
		desalocacao(aux);
	}else{
		printf("\nErro, pilha vazia\n");
	}
}

int ExecucaoPilha(char Tab[8][8], NO **topo, Player jogador){    //FUN��O QUASE IDENTICA AO DA EXECU��O DA FILA, S� FOI TROCADO FUN��ES QUE ANTES ERAM DE FILA POR DE PILHAS
	
	int atualiza;

	if(pilhaVazia(*topo) == 1){
		printf("\nA Pilha de comandos est� vazia!!\n");
		atualiza = jogador.sentido;
		return atualiza;
	}else{
		NO* aux;
		aux = *topo;
		int repe, i, j, pos = 1, k, l;
		while(aux != NULL){
			aux = *topo;
			repe = aux->info.vezes;
			
			//COMANDOS DO TIPO 1
			if(aux->info.tipodecom == 1){ // PODEMOS MOVIMENTAR 3 POSI��ES EM TODOS SENTIDOS!!!!!
			while(repe != 0){
				int verifica;				
				
				if(jogador.sentido == 2){ // SE FOR PARA DIREITA, VAI SER EXECUTADO DESSA FORMA
					for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
						for(j = 0; j < 8; j++){
							if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
								Tab[i][j] = ' ';
								k = i;
								l = j;
								break;
							}
						}
					}

					for(verifica = l; verifica < l+3; verifica++){  //PERCORRE AT� TR�S POSI��ES PARA FRENTE PARA VER SE CONT�M 'X' OU EST� VAZIA
						if(verifica >= 8){  //EXISTE ESSA POSI��O?
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k][verifica] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, verifica);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k][verifica] == 'O'){  //GANHOU A FASE
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}		
						}	
					}			
					Tab[k][l + 2] = 'P'; // CASO N�O ENTRE EM NENHUMA CONDI��O, O JOGO S� MOVIMENTA O PLAYER
				}
						
				if(jogador.sentido == 3){ // SE FOR PARA BAIXO, VAI SER EXECUTADO DESSA FORMA
					for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
						for(j = 0; j < 8; j++){
							if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
								Tab[i][j] = ' ';
								k = i;
								l = j;
								break;
							}
						}
					}
								
					for(verifica = k; verifica < k+3; verifica++){  //PERCORRE AT� TR�S POSI��ES PARA FRENTE PARA VER SE CONT�M 'X' OU EST� VAZIA
						if(verifica >= 8){  //POSI��O EXISTE?
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[verifica][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", verifica, l);
								desempilhar(topo);
								return 0;
							}
							if(Tab[verifica][l] == 'O'){  //GANHOU FASE
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}	
						}	
					}
					Tab[k + 2][l] = 'P'; // CASO N�O ENNTRE EM NENHUMA CONDI��O, O JOGO S� MOVIMENTA O PLAYER
				}
		
				if(jogador.sentido == 4){ // SE FOR PARA ESQUERDA, VAI SER EXECUTADO DESSA FORMA
					for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
						for(j = 0; j < 8; j++){
							if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
								Tab[i][j] = ' ';
								k = i;
								l = j;
								break;
							}
						}
					}
					
					for(verifica = l; verifica < l-3; verifica--){  //PERCORRE AT� TR�S POSI��ES PARA FRENTE PARA VER SE CONT�M 'X' OU EST� VAZIA
						if(verifica < 0){  //A POSI��O EXISTE?
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k][verifica] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, verifica);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k][verifica] == 'O'){  //GANHOU
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}	
						}		
					}
					Tab[k][l - 2] = 'P'; // CASO N�O ENNTRE EM NENHUMA CONDI��O, O JOGO S� MOVIMENTA O PLAYER
				}
			
				if(jogador.sentido == 1){ // SE FOR PARA CIMA, VAI SER EXECUTADO DESSA FORMA
					for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
						for(j = 0; j < 8; j++){
							if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
								Tab[i][j] = ' ';
								k = i;
								l = j;
								break;
							}
						}
					}
								
					
					for(verifica = k; verifica < k-3; verifica--){  //PERCORRE AT� TR�S POSI��ES PARA FRENTE PARA VER SE CONT�M 'X' OU EST� VAZIA
						if(verifica < 0){  //POSI��O EXISTE?
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[verifica][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", verifica, l);
								desempilhar(topo);
								return 0;
							}
							if(Tab[verifica][l] == 'O'){  //GANHOU
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}	
						}		
					}	
					Tab[k - 2][l] = 'P';  // CASO N�O ENNTRE EM NENHUMA CONDI��O, O JOGO S� MOVIMENTA O PLAYER
				}
				repe--;
			}
				
				desempilhar(topo);
				ExibeTabuleiro1(Tab, jogador);  // RETORNAR VALOR PARA FUN��O EXIBIR, PARA PERMANECER EXECUTANDO C�DIGOS DA FILA
				printf("\n---------------------------------------------\n");
				printf("****FIM DO COMANDO NA POSI��O %d da PILHA****!\n", pos);
				printf("---------------------------------------------\n\n");
				pos++;
				if(aux->prox == NULL){   //N�O H� MAIS COMANDOS PARA SEREM EXECUTADOS
					pos = 0;
					printf("\n\n\n");
					atualiza = jogador.sentido;
					return atualiza;
				}else{
					printf("Deseja prosseguir para o comando %d??\n", pos);
					system("pause");
				}
			}
			
			//COMANDOS DO TIPO 2
			if(aux->info.tipodecom == 2){
				while(repe != 0){
					
					jogador.sentido--;
					if(jogador.sentido == 0){
						jogador.sentido = 4;
					}
					
					if(jogador.sentido == 2){ // SE FOR PARA DIREITA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
								
						if(l+1 >= 8){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k][l+1] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, l+1);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k][l+1] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}					
							Tab[k][l+1] = 'P';
						}
					}
							
					if(jogador.sentido == 3){ // SE FOR PARA BAIXO, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
				
						if(k+1 >= 8){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k+1][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k+1, l);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k+1][l] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}		
							Tab[k+1][l] = 'P';
						}
					}
					
					if(jogador.sentido == 4){ // SE FOR PARA ESQUERDA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
						if(l-1 < 0){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k][l-1] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, l-1);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k][l-1] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}	
							Tab[k][l-1] = 'P';
						}
					}
					
					if(jogador.sentido == 1){ // SE FOR PARA CIMA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
								
						if(k-1 < 0){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k-1][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k-1, l);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k-1][l] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}			
							Tab[k-1][l] = 'P';
						}
					}
					
					repe--;
				}
				desempilhar(topo);
								
				ExibeTabuleiro1(Tab, jogador);  // RETORNAR VALOR PARA FUN��O EXIBIR, PARA PERMANECER EXECUTANDO C�DIGOS DA FILA
				printf("\n---------------------------------------------\n");
				printf("****FIM DO COMANDO NA POSI��O %d da PILHA****!\n", pos);
				printf("---------------------------------------------\n\n");
				pos++;
				if(aux->prox == NULL){ //N�O H� MAIS COMANDOS PARA SEREM EXECUTADOS
					pos = 0;
					printf("\n\n\n");
					atualiza = jogador.sentido;
					return atualiza;
				}else{
					printf("Deseja prosseguir para o comando %d??\n", pos);
					system("pause");
				}
			}
			
			//COMANDOS DO TIPO 3
			if(aux->info.tipodecom == 3){
				while(repe != 0){
					jogador.sentido++;
					if(jogador.sentido == 5){
						jogador.sentido = 1;
					}
					if(jogador.sentido == 2){ // SE FOR PARA DIREITA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
								
						if(l+1 >= 8){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k][l+1] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, l+1);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k][l+1] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}					
							Tab[k][l+1] = 'P';
						}
					}
										
					if(jogador.sentido == 3){ // SE FOR PARA BAIXO, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}

						if(k+1 >= 8){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k+1][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k+1, l);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k+1][l] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}		
							Tab[k+1][l] = 'P';
						}
					}
						
					if(jogador.sentido == 4){ // SE FOR PARA ESQUERDA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
						if(l-1 < 0){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k][l-1] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, l-1);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k][l-1] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}	
							Tab[k][l-1] = 'P';
						}
					}			
								
					if(jogador.sentido == 1){ // SE FOR PARA CIMA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
								
						if(k-1 < 0){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k-1][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k-1, l);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k-1][l] == 'O'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[7][7] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}			
							Tab[k-1][l] = 'P';
						}
					}
					repe--;
				}
				desempilhar(topo);
								
				ExibeTabuleiro1(Tab, jogador);  // RETORNAR VALOR PARA FUN��O EXIBIR, PARA PERMANECER EXECUTANDO C�DIGOS DA FILA
				printf("\n---------------------------------------------\n");
				printf("****FIM DO COMANDO NA POSI��O %d da PILHA****!\n", pos);
				printf("---------------------------------------------\n\n");
				pos++;
				if(aux->prox == NULL){  //N�O H� MAIS COMANDOS PARA SEREM EXECUTADOS
					pos = 0;
					printf("\n\n\n");
					atualiza = jogador.sentido;
					return atualiza;
				}else{
					printf("Deseja prosseguir para o comando %d??\n", pos);
					system("pause");
				}
			}
		
		}
		*topo = NULL;
		//QUANDO CHEGAR AQUI, QUER DIZER QUE TODOS OS COMANDOS DA FILA FORAM EXECUTADOS E REMOVIDOS
	}
 } 

void empilhar(NO **topo, Comandos *elem){  
	NO *novo;
	novo = alocarNo();
	if(novo != NULL){
		novo->info.tipodecom = elem->tipodecom;
		novo->info.vezes = elem->vezes;
		novo->prox = *topo;
		*topo = novo;
		printf("\n***ELEMENTO EMPILHADO COM SUCESSO***\n");
	}else{
		printf("\nErro de alocacao\n");
	}
	
}

void retornaTodos(NO *topo){
	NO *aux;
	aux = topo;
	if(pilhaVazia(topo) == 1){
		printf("\nComandos na pilha:");
		printf("\nErro, pilha vazia\n");
	}else{
		printf("\nComandos na pilha:\n");
		while(aux != NULL){   //VAI AT� O PEN�LTIMO ELEMENTO
			printf("(%d - %d)", aux->info.tipodecom, aux->info.vezes);
			aux = aux->prox;
		}
		
		printf("\n\n");
	}
}

//FUN��ES PARA FASE 3 (VOLTA)
int ExecucaoPilha2(char Tab[8][8], NO **topo, Player jogador){    // FUN��O QUASE IDENTICA AO DE EXECU��O PILHA. ESTA FUN��O FOI CRIADA POIS O TABULEIRO PARA O TRAJETO DA VOLTA DA FASE 3 � DIFERENTE
	
	int atualiza;

	if(pilhaVazia(*topo) == 1){
		printf("\nA Pilha de comandos est� vazia!!\n");
		atualiza = jogador.sentido;
		return atualiza;
	}else{
		NO* aux;
		aux = *topo;
		int repe, i, j, pos = 1, k, l;
		while(aux != NULL){
			aux = *topo;
			repe = aux->info.vezes;
			
			//COMANDOS DO TIPO 1
			if(aux->info.tipodecom == 1){ // PODEMOS MOVIMENTAR 3 POSI��ES EM TODOS SENTIDOS!!!!!
			while(repe != 0){
				
				int verifica;				
				if(jogador.sentido == 2){ // SE FOR PARA DIREITA, VAI SER EXECUTADO DESSA FORMA
					for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
						for(j = 0; j < 8; j++){
							if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
								Tab[i][j] = ' ';
								k = i;
								l = j;
								break;
							}
						}
					}

					for(verifica = l; verifica < l+3; verifica++){  //PERCORRE AT� TR�S POSI��ES PARA FRENTE PARA VER SE CONT�M 'X' OU EST� VAZIA
						if(verifica >= 8){
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k][verifica] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, verifica);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k][verifica] == 'I'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[0][0] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}		
						}	
					}			
					Tab[k][l + 2] = 'P';
				}
						
				if(jogador.sentido == 3){ // SE FOR PARA BAIXO, VAI SER EXECUTADO DESSA FORMA
					for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
						for(j = 0; j < 8; j++){
							if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
								Tab[i][j] = ' ';
								k = i;
								l = j;
								break;
							}
						}
					}
								
						for(verifica = k; verifica < k+3; verifica++){  //PERCORRE AT� TR�S POSI��ES PARA FRENTE PARA VER SE CONT�M 'X' OU EST� VAZIA
							if(verifica >= 8){
								printf("\nPosi��o inexistente!\n");
								desempilhar(topo);
								return 0;
							}else{
								if(Tab[verifica][l] == 'X'){ // ACHOU X E PERDEU A FASE		
									printf("\nA coordenada (%d, %d) cont�m um X!!\n", verifica, l);
									desempilhar(topo);
									return 0;
								}
								if(Tab[verifica][l] == 'I'){
									printf("\nUsu�rio chegou ao objetivo\n");
									Tab[0][0] = 'P';
									ExibeTabuleiro1(Tab, jogador); 
									desempilhar(topo);
									return 5;
								}	
							}	
						}
						Tab[k + 2][l] = 'P';
				}
		
				if(jogador.sentido == 4){ // SE FOR PARA ESQUERDA, VAI SER EXECUTADO DESSA FORMA
					for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
						for(j = 0; j < 8; j++){
							if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
								Tab[i][j] = ' ';
								k = i;
								l = j;
								break;
							}
						}
					}
					
					for(verifica = l; verifica < l-3; verifica--){  //PERCORRE AT� TR�S POSI��ES PARA FRENTE PARA VER SE CONT�M 'X' OU EST� VAZIA
						if(verifica < 0){
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k][verifica] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, verifica);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k][verifica] == 'I'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[0][0] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}	
						}		
					}
					Tab[k][l - 2] = 'P';
				}
			
				if(jogador.sentido == 1){ // SE FOR PARA CIMA, VAI SER EXECUTADO DESSA FORMA
					for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
						for(j = 0; j < 8; j++){
							if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
								Tab[i][j] = ' ';
								k = i;
								l = j;
								break;
							}
						}
					}
								
					
					for(verifica = k; verifica < k-3; verifica--){  //PERCORRE AT� TR�S POSI��ES PARA FRENTE PARA VER SE CONT�M 'X' OU EST� VAZIA
						if(verifica < 0){
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[verifica][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", verifica, l);
								desempilhar(topo);
								return 0;
							}
							if(Tab[verifica][l] == 'I'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[0][0] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}	
						}		
					}	
					Tab[k - 2][l] = 'P';
				}
				repe--;
			}
				
				desempilhar(topo);
				ExibeTabuleiro1(Tab, jogador);  // RETORNAR VALOR PARA FUN��O EXIBIR, PARA PERMANECER EXECUTANDO C�DIGOS DA FILA
				printf("\n---------------------------------------------\n");
				printf("****FIM DO COMANDO NA POSI��O %d da PILHA****!\n", pos);
				printf("---------------------------------------------\n\n");
				pos++;
				if(aux->prox == NULL){
					pos = 0;
					printf("\n\n\n");
					atualiza = jogador.sentido;
					return atualiza;
				}else{
					printf("Deseja prosseguir para o comando %d??\n", pos);
					system("pause");
				}
			}
			
			//COMANDOS DO TIPO 2
			if(aux->info.tipodecom == 2){
				while(repe != 0){
					
					jogador.sentido--;
					if(jogador.sentido == 0){
						jogador.sentido = 4;
					}
					
					if(jogador.sentido == 2){ // SE FOR PARA DIREITA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
								
						if(l+1 >= 8){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k][l+1] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, l+1);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k][l+1] == 'I'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[0][0] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}					
							Tab[k][l+1] = 'P';
						}
					}
							
					if(jogador.sentido == 3){ // SE FOR PARA BAIXO, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
				
						if(k+1 >= 8){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k+1][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k+1, l);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k+1][l] == 'I'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[0][0] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}		
							Tab[k+1][l] = 'P';
						}
					}
					
					if(jogador.sentido == 4){ // SE FOR PARA ESQUERDA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
						if(l-1 < 0){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k][l-1] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, l-1);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k][l-1] == 'I'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[0][0] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}	
							Tab[k][l-1] = 'P';
						}
					}
					
					if(jogador.sentido == 1){ // SE FOR PARA CIMA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
								
						if(k-1 < 0){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k-1][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k-1, l);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k-1][l] == 'I'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[0][0] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}			
							Tab[k-1][l] = 'P';
						}
					}
					
					repe--;
				}
				
				desempilhar(topo);
								
				ExibeTabuleiro1(Tab, jogador);  // RETORNAR VALOR PARA FUN��O EXIBIR, PARA PERMANECER EXECUTANDO C�DIGOS DA FILA
				printf("\n---------------------------------------------\n");
				printf("****FIM DO COMANDO NA POSI��O %d da PILHA****!\n", pos);
				printf("---------------------------------------------\n\n");
				pos++;
				if(aux->prox == NULL){
					pos = 0;
					printf("\n\n\n");
					atualiza = jogador.sentido;
					return atualiza;
				}else{
					printf("Deseja prosseguir para o comando %d??\n", pos);
					system("pause");
				}
			}
			
			//COMANDOS DO TIPO 3
			if(aux->info.tipodecom == 3){
				while(repe != 0){
					jogador.sentido++;
					if(jogador.sentido == 5){
						jogador.sentido = 1;
					}
					if(jogador.sentido == 2){ // SE FOR PARA DIREITA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
								
						if(l+1 >= 8){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k][l+1] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, l+1);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k][l+1] == 'I'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[0][0] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}					
							Tab[k][l+1] = 'P';
						}
					}
										
					if(jogador.sentido == 3){ // SE FOR PARA BAIXO, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}

						if(k+1 >= 8){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k+1][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k+1, l);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k+1][l] == 'I'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[0][0] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}		
							Tab[k+1][l] = 'P';
						}
					}
						
					if(jogador.sentido == 4){ // SE FOR PARA ESQUERDA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
						if(l-1 < 0){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k][l-1] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k, l-1);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k][l-1] == 'I'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[0][0] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}	
							Tab[k][l-1] = 'P';
						}
					}			
								
					if(jogador.sentido == 1){ // SE FOR PARA CIMA, VAI SER EXECUTADO DESSA FORMA
						for(i = 0; i < 8; i++){  // PERCORRER O TABULEIRO PARA ENCONTRAR O PLAYER E MOVIMENT�-LO
							for(j = 0; j < 8; j++){
								if(Tab[i][j] == 'P'){  //ACHOU O PLAYER
									Tab[i][j] = ' ';
									k = i;
									l = j;
									break;
								}
							}
						}
								
						if(k-1 < 0){ // O CAMPO N�O EXISTE, JOGADOR PERDE!
							printf("\nPosi��o inexistente!\n");
							desempilhar(topo);
							return 0;
						}else{
							if(Tab[k-1][l] == 'X'){ // ACHOU X E PERDEU A FASE		
								printf("\nA coordenada (%d, %d) cont�m um X!!\n", k-1, l);
								desempilhar(topo);
								return 0;
							}
							if(Tab[k-1][l] == 'I'){
								printf("\nUsu�rio chegou ao objetivo\n");
								Tab[0][0] = 'P';
								ExibeTabuleiro1(Tab, jogador); 
								desempilhar(topo);
								return 5;
							}			
							Tab[k-1][l] = 'P';
						}
					}
					repe--;
				}
				desempilhar(topo);
								
				ExibeTabuleiro1(Tab, jogador);  // RETORNAR VALOR PARA FUN��O EXIBIR, PARA PERMANECER EXECUTANDO C�DIGOS DA FILA
				printf("\n---------------------------------------------\n");
				printf("****FIM DO COMANDO NA POSI��O %d da PILHA****!\n", pos);
				printf("---------------------------------------------\n\n");
				pos++;
				if(aux->prox == NULL){
					pos = 0;
					printf("\n\n\n");
					atualiza = jogador.sentido;
					return atualiza;
				}else{
					printf("Deseja prosseguir para o comando %d??\n", pos);
					system("pause");
				}
			}
		
		}
		*topo = NULL;
		//QUANDO CHEGAR AQUI, QUER DIZER QUE TODOS OS COMANDOS DA FILA FORAM EXECUTADOS E REMOVIDOS
	}
 } 
 
 void Preenche2(char Tab[8][8]){   //TABULEIRO DA VOLTA
	Tab[0][0] = 'I'; Tab[0][1] = ' '; Tab[0][2] = ' '; Tab[0][3] = ' '; Tab[0][4] = ' '; Tab[0][5] = ' '; Tab[0][6] = ' '; Tab[0][7] = 'X';
	Tab[1][0] = ' '; Tab[1][1] = ' '; Tab[1][2] = ' '; Tab[1][3] = ' '; Tab[1][4] = ' '; Tab[1][5] = ' '; Tab[1][6] = ' '; Tab[1][7] = ' ';
	Tab[2][0] = 'X'; Tab[2][1] = ' '; Tab[2][2] = ' '; Tab[2][3] = ' '; Tab[2][4] = ' '; Tab[2][5] = ' '; Tab[2][6] = 'X'; Tab[2][7] = ' ';
	Tab[3][0] = ' '; Tab[3][1] = 'X'; Tab[3][2] = ' '; Tab[3][3] = ' '; Tab[3][4] = 'X'; Tab[3][5] = ' '; Tab[3][6] = ' '; Tab[3][7] = ' ';
	Tab[4][0] = ' '; Tab[4][1] = ' '; Tab[4][2] = ' '; Tab[4][3] = 'X'; Tab[4][4] = ' '; Tab[4][5] = 'X'; Tab[4][6] = ' '; Tab[4][7] = 'X';
	Tab[5][0] = ' '; Tab[5][1] = 'X'; Tab[5][2] = ' '; Tab[5][3] = ' '; Tab[5][4] = ' '; Tab[5][5] = ' '; Tab[5][6] = ' '; Tab[5][7] = ' ';
	Tab[6][0] = ' '; Tab[6][1] = ' '; Tab[6][2] = ' '; Tab[6][3] = ' '; Tab[6][4] = 'X'; Tab[6][5] = 'X'; Tab[6][6] = ' '; Tab[6][7] = ' ';
	Tab[7][0] = ' '; Tab[7][1] = ' '; Tab[7][2] = ' '; Tab[7][3] = ' '; Tab[7][4] = ' '; Tab[7][5] = ' '; Tab[7][6] = ' '; Tab[7][7] = 'P';
}
