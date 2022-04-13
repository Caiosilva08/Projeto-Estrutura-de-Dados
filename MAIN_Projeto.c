#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "BBT_Fase1Projeto.c"
 
int main(){
	
	setlocale(LC_ALL, "Portuguese");
    Fila *F;
    NO *P;
    Comandos op, opp;
    int x, y, z, ganhar, fase = 1, continuar, tentativas = 3;
    Player jogador;
    jogador.sentido = 2;
    char Tab[8][8];
    printf("-----------------------------------------------\n");
 	printf("\t       COMANDOS EM LOOP\n");
 	printf("-----------------------------------------------\n\n");
 	printf("Descrição das ações dos comandos: \n");
    printf("F: avança 1 casa no sentido apontado pelo player\n");
    printf("E: rotaciona o sentido do player uma posição para esquerda sem movimentá-lo no tabuleiro\n");
    printf("D: rotaciona o sentido do player uma posição para direita sem movimentá-lo no tabuleiro\n\n");
 
    F = (Fila*)malloc(sizeof(Fila));
    inic(F);
    
    //INICIO DO JOGO NA FASE 1	
    Preenche(Tab);
    while(fase == 1){	
    	do{
    		printf("\n\n\t      FASE 1\n\n");
        	ExibeTabuleiro1(Tab, jogador);
 	    	printf("Selecione a opção que deseja\n");
    	    printf(" 1. Acrescentar comandos na fila \n 2. Executar jogo. \n");
        	printf(" 3. Sair do jogo. \n");
	        printf("______________________________\n");
    	    printf("Digite a opção: ");        
    	    scanf("%d", &x);
	        fflush(stdin);
	        impressaoNclassica(F);
        
	    	if(x == 1){
	            printf("\nDigite o comando desejado: ");        
	            scanf("%d", &op.tipodecom);
    	        fflush(stdin);
			 	printf("\nQuantas vezes ele vai ser executado? : ");        
	            scanf("%d", &op.vezes);
	            fflush(stdin);
	            enfileirar(F, op);
	    	}
 
    	    if(x == 2){
    	    	printf("\nA execução do jogo começou!\n\n");
    	    	system("pause");
				ganhar = ExecucaoFila(Tab, F, jogador);   //Ganhar recebe o resultado parcial do jogador
				
				if(ganhar == 0){  //Jogador perdeu 
					printf("\n\n**QUE PENA!, VOCÊ PERDEU A FASE %d DO JOGO**\n\n", fase);
					tentativas--;
					
					if(tentativas == 0){    //Perdeu o jogo todo
						printf("O NÚMERO DE TENTATIVAS ACABOU!\n");
						fase = 0;
						x = 4;
					}else{  //Perdeu a fase mas ainda possui tentativas
						printf("Seu número restante de tentativas nesta fase é: %d\n", tentativas);
						printf("Pretende continuar jogando?\n");
						printf("1.Sim\t 2.Não\n");
						printf("-->");
						scanf("%d", &continuar);
						fflush(stdin);
						if(continuar == 1){
							Preenche(Tab);
							jogador.sentido = 2;
							x = 1;
							free(F);
							inic(F);
							
						}else{
							x = 4;
							fase = 0;
						}		
					}
				}
				if(ganhar == 5){   // Ganhou a fase e vai para a proxima
					jogador.sentido = 2;
					printf("\n\n**PARABÉNS!, VOCÊ VENCEU A FASE %d DO JOGO**\n\n", fase);
					printf("Pretende continuar jogando?\n");
					printf("1.Sim\t 2.Não\n");
					printf("-->");
					scanf("%d", &continuar);
					fflush(stdin);
					if(continuar == 1){
						fase++;
						tentativas = 3;
						x = 4;
					}else{
						x = 4;
						fase = 0;
					}
				}
				if(ganhar == 1 || ganhar == 2 || ganhar == 3 || ganhar == 4){  //TODA VEZ QUE ENTRAR AQUI, O VALOR DA VARIÁVEL JOGADOR SERÁ ATUALIZADA
					jogador.sentido = ganhar;
					x = 1;
				}
    		}
    		
    		if(x == 3){  //Sai do jogo
    			fase = 0;
    			x = 4;
			}
			
		}while( x != 4); 
	}
	
	free(F);
	
	Preenche(Tab);
	inicializar(&P);
	
	//FASE 2
	while(fase == 2){
		do{
			printf("\n\n\t      FASE 2\n\n");
        	ExibeTabuleiro1(Tab, jogador);
        	retornaTodos(P);
 	    	printf("\nSelecione a opção que deseja\n");
    	    printf(" 1. Acrescentar comandos na pilha \n 2. Executar jogo. \n");
        	printf(" 3. Sair do jogo. \n");
	        printf("______________________________\n");
    	    printf("Digite a opção: ");        
    	    scanf("%d", &y);
	        fflush(stdin);
        
	    	if(y == 1){
	            printf("\nDigite o comando desejado: ");        
	            scanf("%d", &opp.tipodecom);
    	        fflush(stdin);
			 	printf("\nQuantas vezes ele vai ser executado? : ");        
	            scanf("%d", &opp.vezes);
	            fflush(stdin);
	            empilhar(&P, &opp);
	    	}
 
 			
    	    if(y == 2){
    	    	printf("\nA execução do jogo começou!\n\n");
    	    	system("pause");
				ganhar = ExecucaoPilha(Tab, &P, jogador);
				if(ganhar == 0){ //perdeu a fase
					printf("\n\n**QUE PENA!, VOCÊ PERDEU A FASE %d DO JOGO**\n\n", fase);
					tentativas--;
					
					if(tentativas == 0){
						printf("O NÚMERO DE TENTATIVAS ACABOU!\n");
						fase = 0;
						y = 4;
					}else{   // ainda possui tentativas
						printf("Seu número restante de tentativas nesta fase é: %d\n", tentativas);
						printf("Pretende continuar jogando?\n");
						printf("1.Sim\t 2.Não\n");
						printf("-->");
						scanf("%d", &continuar);
						fflush(stdin);
						if(continuar == 1){
							Preenche(Tab);
							jogador.sentido = 2;
							y = 1;
							free(P);
							inicializar(&P);
						}else{
							y = 4;
							fase = 0;
						}		
					}
				}
				if(ganhar == 5){  //ganhou a fase
					printf("\n\n**PARABÉNS!, VOCÊ VENCEU A FASE %d DO JOGO**\n\n", fase);
					printf("Pretende continuar jogando?\n");
					printf("1.Sim\t 2.Não\n");
					printf("-->");
					scanf("%d", &continuar);
					fflush(stdin);
					if(continuar == 1){
						fase++;
						tentativas = 3;
						y = 4;
					}else{
						y = 4;
						fase = 0;
					}
				}
				if(ganhar == 1 || ganhar == 2 || ganhar == 3 || ganhar == 4){  //TODA VEZ QUE ENTRAR AQUI, O VALOR DA VARIÁVEL JOGADOR SERÁ ATUALIZADA
					jogador.sentido = ganhar;
					y = 1;
				}
    		}
    		
    		if(y == 3){  //saiu do jogo
    			fase = 0;
    			y = 4;
			}
		}while(y != 4);
		
	}
	
	free(P);
		//NA FASE 3 IDA, OS COMANDOS SÃO SEMELHANTES AOS COMANDOS DA FASE 1
	Preenche(Tab);
	F = (Fila*)malloc(sizeof(Fila));
    inic(F);
	while(fase == 3){	// IDA
    	do{
    		printf("\n\n\t      FASE 3 - IDA\n\n");
        	ExibeTabuleiro1(Tab, jogador);
        	impressaoNclassica(F);
 	    	printf("\nSelecione a opção que deseja\n");
    	    printf(" 1. Acrescentar comandos na fila \n 2. Executar jogo. \n");
        	printf(" 3. Sair do jogo. \n");
	        printf("______________________________\n");
    	    printf("Digite a opção: ");        
    	    scanf("%d", &x);
	        fflush(stdin);
        
	    	if(x == 1){
	            printf("\nDigite o comando desejado: ");        
	            scanf("%d", &op.tipodecom);
    	        fflush(stdin);
			 	printf("\nQuantas vezes ele vai ser executado? : ");        
	            scanf("%d", &op.vezes);
	            fflush(stdin);
	            enfileirar(F, op);
	    	}
 
    	    if(x == 2){
    	    	printf("\nA execução do jogo começou!\n\n");
    	    	system("pause");
				ganhar = ExecucaoFila(Tab, F, jogador);
				if(ganhar == 0){
					printf("\n\n**QUE PENA!, VOCÊ PERDEU A FASE 3 (IDA) DO JOGO**\n\n");
					tentativas--;
					
					if(tentativas == 0){
						printf("O NÚMERO DE TENTATIVAS ACABOU!\n");
						fase = 0;
						x = 4;
					}else{
						printf("Seu número restante de tentativas nesta fase é: %d\n", tentativas);
						printf("Pretende continuar jogando?\n");
						printf("1.Sim\t 2.Não\n");
						printf("-->");
						scanf("%d", &continuar);
						fflush(stdin);
						if(continuar == 1){
							Preenche(Tab);
							jogador.sentido = 2;
							x = 1;
							free(F);
							inic(F);
						}else{
							x = 4;
							fase = 0;
						}		
					}
				}
				if(ganhar == 5){  //VENCE O JOGO
					jogador.sentido = 4;     // NA VOLTA O JOGADOR INICIA APONTANDO PRA CIMA
					printf("\n\n**PARABÉNS!, VOCÊ VENCEU A FASE 3 (IDA) DO JOGO**\n\n");
					printf("Pretende continuar jogando?\n");
					printf("1.Sim\t 2.Não\n");
					printf("-->");
					scanf("%d", &continuar);
					fflush(stdin);
					if(continuar == 1){
						fase++;
						x = 4;
					}else{
						x = 4;
						fase = 0;
					}
				}
				if(ganhar == 1 || ganhar == 2 || ganhar == 3 || ganhar == 4){  //O VALOR DA VARIÁVEL JOGADOR SERÁ ATUALIZADA A CADA FIM DE COMANDOS QUE O USUÁRIO NÃO CHEGUE AO OBJETIVO SEM PERDER
					jogador.sentido = ganhar;
					x = 1;
				}
    		}
    		
    		if(x == 3){   //SAI DO JOGO
    			fase = 0;
    			x = 4;
			}
			
		}while( x != 4); 
	}
	
	free(F);
	
	//NA FASE 3 VOLTA, OS COMANDOS SÃO SEMELHANTES AOS COMANDOS DA FASE 2
	Preenche2(Tab);
	inicializar(&P);
	while(fase == 4){  //VOLTA
		do{
			printf("\n\n\t      FASE 3 - VOLTA\n\n");
        	ExibeTabuleiro1(Tab, jogador);
        	retornaTodos(P);
 	    	printf("\nSelecione a opção que deseja\n");
    	    printf(" 1. Acrescentar comandos na pilha \n 2. Executar jogo. \n");
        	printf(" 3. Sair do jogo. \n");
	        printf("______________________________\n");
    	    printf("Digite a opção: ");        
    	    scanf("%d", &y);
	        fflush(stdin);
        
	    	if(y == 1){
	            printf("\nDigite o comando desejado: ");        
	            scanf("%d", &opp.tipodecom);
    	        fflush(stdin);
			 	printf("\nQuantas vezes ele vai ser executado? : ");        
	            scanf("%d", &opp.vezes);
	            fflush(stdin);
	            empilhar(&P, &opp);
	    	}
 
    	    if(y == 2){
    	    	printf("\nA execução do jogo começou!\n\n");
    	    	system("pause");
				ganhar = ExecucaoPilha2(Tab, &P, jogador);
				if(ganhar == 0){
					printf("\n\n**QUE PENA!, VOCÊ PERDEU A FASE 3 (VOLTA) DO JOGO**\n\n");
					tentativas--;
					
					if(tentativas == 0){
						printf("O NÚMERO DE TENTATIVAS ACABOU!\n");
						fase = 0;
						y = 4;
					}else{
						printf("Seu número restante de tentativas nesta fase é: %d\n", tentativas);
						printf("Pretende continuar jogando?\n");
						printf("1.Sim\t 2.Não\n");
						printf("-->");
						scanf("%d", &continuar);
						fflush(stdin);
						if(continuar == 1){
							fase = 3;
							jogador.sentido = 2;  //INICIA A FASE 3 IDA DE NOVO COM O SENTIDO PARA A DIREITA
							y = 4;
							free(P);
						}else{
							y = 4;
							fase = 0;
						}		
					}
				}
				if(ganhar == 5){
					printf("\n\n**PARABÉNS!, VOCÊ VENCEU O JOGO**\n");
					printf("OBRIGADO POR JOGAR CONOSCO!!!!\n\n");
						y = 4;
						fase = 0;
					}
				if(ganhar == 1 || ganhar == 2 || ganhar == 3 || ganhar == 4){  //TODA VEZ QUE ENTRAR AQUI, O VALOR DA VARIÁVEL JOGADOR SERÁ ATUALIZADA
					jogador.sentido = ganhar;
					y = 1;
				}
    		}
    		
    		if(y == 3){
    			fase = 0;
    			y = 4;
			}
		}while(y != 4);
		
	}
	
	free(P);
	
	//AQUI É A OPÇÃO EM QUE O USUÁRIO DESEJA SAIR
	if(fase == 0){
		printf("\nVocê saiu!\n\n");
		printf("Autores:\n");
		printf("Caio da Silva de Miranda - 6368\nGuilherme Gomes Stoppa - 6690\nAlexandre Bertulino 6029\n\n");
		system("pause");
		return 0;	
	}
}
