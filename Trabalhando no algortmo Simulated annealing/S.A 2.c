#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include "Funcoes.h"

// SIMULATED ANNEALING
void SimulatedAnnealing(Oferta SolucaoInicial[MAX_SEMESTRE][5][2], float taxaResfriamento, int SAmax, float TI, float TF, int numeroSemestres){
	
	//  ATRIBUINDO PISIÇOES VAZIAS A MATRIZ DE SOLUÇOES FINAL
    for(j = 1; j <= numeroSemestres; j++){
    	for(k = 0; k < 5; k++){
    		for(m = 0; m < 2; m++){
    			solucaoFinal[j][k][m].CodigoOferta = -1;
			}
		}   		
	}
	printf("Estou entrando !!!\n");
	// FAZENDO A SOLUÇAO FINAL RECEBER A SOLUÇAO INICIAL
	for(j = 1; j <= numeroSemestres; j++){
    	for(k = 0; k < 5; k++){
    		for(m = 0; m < 2; m++){
    			solucaoFinal[j][k][m] = SolucaoInicial[j][k][m];
			}
		}   		
	}
	
	// ATRIBUINDO VALORES VAZIOS AS POSIÇOES DA MATRIZ DE SOLUÇAO VIZINHA
	for(j = 1; j <= numeroSemestres; j++){
    	for(k = 0; k < 5; k++){
    		for(m = 0; m < 2; m++){
    			solucaoVizinha[j][k][m].CodigoOferta = -1;
			}
		}   		
	}
	
	// RECEBENDO A TEMPERATURA INICIAL
	float Temperatura = TI;
	
	// INICIALIZANDO A VARIAVEL QUE VAI INCREMENTAR ATE O NUMERO MAXIMO DE SOLUÇOES VIZINHAS 
	int iterT = 0;
	
	
	srand( (unsigned)time(NULL)); // Atribuindo valor nulo ao Rand() para os sorteios aleaatorios.
	
	// SIMULATED ANNEALING INICIA AQUI
	while(Temperatura > TF){
		while(iterT < SAmax){
			
			// RECEBE A SOLUÇAO ATUAL
			for(j = 1; j <= numeroSemestres; j++){
				
		    	for(k = 0; k < 5; k++){
		    		for(m = 0; m < 2; m++){
		    			solucaoVizinha[j][k][m] = SolucaoInicial[j][k][m];
					}
				}   		
			}
			 
			// TRABALHAR NESTA FUNÇAO IMPLEMENTANDO A MUDANÇA DE ACORDO COM AS DISCIPLINAS QUE UM PROFESSOR POD MINISTRAR!!!!!!
			// FUNÇAO QUE GERA UMA SOLUÇAO VIZINHA DE UMA DETERMINADA SOLUÇAO
			for(j = 1; j <= numeroSemestres;j++){
		        for(k = 0; k < 5; k++){
		            for(m = 0; m < 2; m++){			    	
					    		
	                    	b = 0 + rand() % 5;
	                    	c = 0 + rand() % 2;
	                    	
	                    	aux = solucaoVizinha[j][b][c];
	                    	solucaoVizinha[j][b][c] = solucaoVizinha[j][k][m];
	                    	solucaoVizinha[j][k][m] = aux;       
		            	
		            }
		        }
			}
			// ENCERRA A GERRAÇAO DA SOLUÇAO VIZINHA
			
			verificacao = (FuncaoCusto1(solucaoVizinha,numeroSemestres) + FuncaoCusto2(solucaoVizinha,numeroSemestres)) - (FuncaoCusto1(SolucaoInicial,numeroSemestres) + FuncaoCusto2(SolucaoInicial,numeroSemestres)); // Calculando a variaçao da funçao
			probabilidade = pow(2.7,( ( -(verificacao) ) / Temperatura)); // Calculando o valor
			
			// COMPARANDO FUNÇAO DE CUSTO DA SOLUÇAO VIZINHA COMA SOLUÇAO INICIAL
			if(verificacao < 0){
				
				for(j = 1; j <= numeroSemestres; j++){
		    		for(k = 0; k < 5; k++){
			    		for(m = 0; m < 2; m++){
			    			SolucaoInicial[j][k][m] = solucaoVizinha[j][k][m];
						}
					}   		
				}
				if((FuncaoCusto1(solucaoVizinha,numeroSemestres) + FuncaoCusto2(solucaoVizinha,numeroSemestres)) < (FuncaoCusto1(solucaoFinal,numeroSemestres) + FuncaoCusto2(solucaoFinal,numeroSemestres))){
					for(j = 1; j <= numeroSemestres; j++){
						for(k = 0; k < 5; k++){
				    		for(m = 0; m < 2; m++){
				    			solucaoFinal[j][k][m] = solucaoVizinha[j][k][m];
							}
						}
					}
				}
				
			}else{
				
				if(probabilidade > 0  &&  probabilidade < 1){
				
					for(j = 1; j <= numeroSemestres; j++){
						for(k = 0; k < 5; k++){
			  	  			for(m=0; m<2; m++){
			  	  				SolucaoInicial[j][k][m] = solucaoVizinha[j][k][m];
							}
						}
					}
					
				}
				
			}
			// FIM DA COMPARAÇAO
			
			iterT++; // variavel de interaçao e incrementada
		}
		Temperatura = Temperatura * taxaResfriamento; // A temperatura e incrementada ao ser mutiplicacda pela a taxa de resfriamento
		iterT = 0; // A variavel de interaçao recebe zero para realizar uma nova verificaçao;
	}
	
	
	// MOSTRA O RESULTADO
    printf("HORARIO GERADO:\n");
    
    for(j = 1; j <= numeroSemestres; j++){
    	
    	if(j == 1){
            printf("\n SEMESTRE 1:\n\n");
        }else if(j == 2){
            printf("\n SEMESTRE 2:\n\n");
        }else if(j == 3){
            printf("\n SEMESTRE 3:\n\n");
        }else if(j == 4){
            printf("\n SEMESTRE 4:\n\n");
        }else if(j == 5){
            printf("\n SEMESTRE 5:\n\n");
        }else if(j == 6){
            printf("\n SEMESTRE 6:\n\n");
        }else if(j == 7){
            printf("\n SEMESTRE 7:\n\n");
        }else if(j == 8){
            printf("\n SEMESTRE 8:\n\n");
        }
        
	    for(k = 0; k < 5; k++){
	    	
	    	if(k == 0){
            	printf("   SEGUNDA --\n\n");
	        }else if(k == 1){
	            printf("   TERCA --\n\n");
	        }else if(k == 2){
	            printf("   QUARTA --\n\n");
	        }else if(k == 3){
	            printf("   QUINTA --\n\n");
	        }else if(k == 4){
	            printf("   SEXTA --\n\n");
	        }
	    	
	        for(m = 0; m < 2; m++){
	            printf("\n%s %s\n", solucaoFinal[j][k][m].cadeira.nomeDisciplina, solucaoFinal[j][k][m].prof.nomeProfessor);
	        }
	    }
	}
	//printf("Fucao de Custo = %d\n",(FuncaoCusto1(solucaoFinal,numeroSemestres) + FuncaoCusto2(solucaoFinal,numeroSemestres)));
	
	printf("AULAS SEGUIDAS EM UM MESMO DIA = %d\nAulas em mais de uma turma ao mesmo tempo = %d\n",FuncaoCusto1(solucaoFinal,numeroSemestres),FuncaoCusto2(solucaoFinal,numeroSemestres));
	
	printf("Professores que estao sem folga = %d\n",FuncaoCusto3(solucaoFinal, numeroSemestres, numeroProfessores, RecProf));
	printf("Professores que estao com folga = %d\n",FuncaoCusto4(solucaoFinal, numeroSemestres, numeroProfessores, RecProf));
}


// FUNÇAO PRINCIPAL
int main(){	

	setlocale(LC_ALL,"");

    srand( (unsigned)time(NULL));   // Atribuindo valor nulo ao Rand() para os sorteios aleaatorios.
     
    // ENTRANDO COM OS VALORES
    // Semestres
	printf("Digite o Numero de Semestres:\n");
	scanf("%d", &numeroSemestres);
	
	// Disciplinas
	printf("Digite o Numero de Disciplinas:\n");
	scanf("%d", &numeroDisciplinas);
	
	// Professores
    printf("Digite o Numero de Professores:\n");
	scanf("%d", &numeroProfessores);
	
    // ATRIBUINDO PISIÇOES VAZIAS A MATRIZ DE HORARIOS
    for(j = 1; j <= numeroSemestres; j++){
    	for(k = 0; k < 5; k++){
    		for(m = 0; m < 2; m++){
    			Solucao[j][k][m].CodigoOferta = -1;
			}
		}   		
	}

    // RECEBENDO AS DISCIPLINAS E COLOCANDO-AS NO VETOR DE DISCIPLINAS
    FILE *readDis = fopen("DisSisT.txt","r");
    
    for(a = 1; a <= numeroDisciplinas; a++){
    	fscanf(readDis,"%s %d %d\n", &RecCadeiras[a].nomeDisciplina, &RecCadeiras[a].semestre, &RecCadeiras[a].cargaHoraria);
    	fscanf(readDis,"%d\n", &RecCadeiras[a].cargaHoraria);
    	RecCadeiras[a].Aloca = 0;
    	RecCadeiras[a].codigoDisciplina = a;
	}
	
	fclose(readDis);
	
	// RECEBENDO OS PROFESSORES E COLOCANDO-AS NO VETOR DE PROFESSORES
	FILE *readProf = fopen("ProfSI.txt","r+");
	if (readProf == NULL) {
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
	for(g = 0; g < numeroProfessores; g++){
    	fscanf(readProf,"%s\n", &RecProf[g].nomeProfessor);
    	fscanf(readProf,"%d\n",&DisApto);
    	for(d = 0; d < DisApto; d++){
    		fscanf(readProf,"%s %d\n", &RecProf[g].DisMinis[d].nomeDisciplina, &RecProf[g].DisMinis[d].preferencia);
		}    	
	}   
	
    fclose(readProf);
    
    
    // Mostrando as vetores
    printf("DISCILPINAS\n");
    for(a = 1; a <= numeroDisciplinas; a++){
    	printf("\n%s %d %d\n", RecCadeiras[a].nomeDisciplina, RecCadeiras[a].semestre, RecCadeiras[a].cargaHoraria);
	}
	printf("PROFESSORES\n");
	for(g = 0; g < numeroProfessores; g++){
    	printf("%s\n", RecProf[g].nomeProfessor);
    	for(d = 0; d < 6; d++){
    		printf("Disciplina: %s preferencia: %d\n\n", RecProf[g].DisMinis[d].nomeDisciplina, RecProf[g].DisMinis[d].preferencia);
		} 
			
	} 
    
	// GERANDO A SOLUÇAO (HORARIO) INICIAL
    for(j = 1; j <= numeroSemestres; j++){
         for(k = 0; k < 5; k++){
        	for(m = 0; m < 2; m++){
				
                for(a = 1; a <= numeroDisciplinas; a++){
                	
                	if(RecCadeiras[a].Aloca == 0){
                		
						if(RecCadeiras[a].cargaHoraria == 2 && RecCadeiras[a].semestre == j){
														
							for(d = 0; d < numeroProfessores; d++){
								for(g = 0; g < 6; g++){
								
									if(stricmp(RecProf[d].DisMinis[g].nomeDisciplina, RecCadeiras[a].nomeDisciplina) == 0 && RecProf[d].DisMinis[g].preferencia > armP ){
										armP = RecProf[d].DisMinis[g].preferencia;
										armPosi = d;
										
										
									}
									
								}
							}
                			
		                	if(Solucao[j][k][m].CodigoOferta == -1){
		                		
				                Solucao[j][k][m].cadeira = RecCadeiras[a];
				                strcpy(Solucao[j][k][m].prof.nomeProfessor, RecProf[armPosi].nomeProfessor);
				                RecCadeiras[a].Aloca = 1;
				                Solucao[j][k][m].CodigoOferta = RecCadeiras[a].codigoDisciplina;
	    
				            }else if(Solucao[j][k][m].CodigoOferta > -1){ 
				            	
				            	b = k;
				            	c = m;
				            	
				            	while(Solucao[j][b][c].CodigoOferta != -1){
				            		
				            		b = 0 + (rand() % 5);
					            	c = 0 + (rand() % 2);
					            	
				            		if(Solucao[j][b][c].CodigoOferta == -1){
	                					RecCadeiras[a].Aloca = 1;
			                			Solucao[j][b][c].cadeira = RecCadeiras[a];
				                		strcpy(Solucao[j][b][c].prof.nomeProfessor, RecProf[armPosi].nomeProfessor);
			                			Solucao[j][b][c].CodigoOferta = -1;
									}
									
								}
								
								
								Solucao[j][b][c].CodigoOferta = RecCadeiras[a].codigoDisciplina;
								
							}
							//armPosi = -1;
							armP = 0; 
							a = numeroDisciplinas;
								
			            }else if(RecCadeiras[a].cargaHoraria == 4 && RecCadeiras[a].semestre == j){
			            	
			            	for(d = 0; d < numeroProfessores; d++){
								for(g = 0; g < 6; g++){
								
									if(stricmp(RecProf[d].DisMinis[g].nomeDisciplina, RecCadeiras[a].nomeDisciplina) == 0 && RecProf[d].DisMinis[g].preferencia > armP ){
										armP = RecProf[d].DisMinis[g].preferencia;
										armPosi = d;	
									}
									
								}
							}
			            	
		                	if(Solucao[j][k][m].CodigoOferta == -1){
		                		
		                		Solucao[j][k][m].cadeira = RecCadeiras[a];
				                strcpy(Solucao[j][k][m].prof.nomeProfessor, RecProf[armPosi].nomeProfessor);
				                Solucao[j][k][m].CodigoOferta = RecCadeiras[a].codigoDisciplina;
								
		                		b = k;
				            	c = m;	
				            	
							}else if(Solucao[j][k][m].CodigoOferta > -1){ 
							
								b = k;
				            	c = m;
				            
								while(Solucao[j][b][c].CodigoOferta != -1){
				            		
				            		b = 0 + (rand() % 5);
					            	c = 0 + (rand() % 2);
					            	
				            		if(Solucao[j][b][c].CodigoOferta == -1){
	                				
			                			Solucao[j][b][c].cadeira = RecCadeiras[a];
				                		strcpy(Solucao[j][b][c].prof.nomeProfessor, RecProf[armPosi].nomeProfessor);
			                			Solucao[j][b][c].CodigoOferta = -1;
			                				
									}
									
								}
								
								Solucao[j][b][c].CodigoOferta = RecCadeiras[a].codigoDisciplina;
								b = b;
				            	c = c;
							}
							
							while(Solucao[j][b][c].CodigoOferta != -1){
								
								b = 0 + (rand() % 5);
				            	c = 0 + (rand() % 2);
			            		if(Solucao[j][b][c].CodigoOferta == -1){
			            			
	            					RecCadeiras[a].Aloca = 1;
	            					Solucao[j][b][c].cadeira = RecCadeiras[a];
				                	strcpy(Solucao[j][b][c].prof.nomeProfessor, RecProf[armPosi].nomeProfessor);
		                			Solucao[j][b][c].CodigoOferta = -1;
		                			
								}
								
							}
							
							Solucao[j][b][c].CodigoOferta = RecCadeiras[a].codigoDisciplina;
							armP = 0;
							a = numeroDisciplinas;
							m = 2;
						}				
						
					}
					
				}	
				
   			}
   			
    	}
    	
    }
    printf("ACABEI A PRIMEIRA PARTE");
    //teste de melhora do algorotmo
    
    for(j = 1; j <= numeroSemestres; j++){
        for(k=0;k<5;k++){
            for(m=0;m<2;m++){
                for(a = j+1;a <= numeroSemestres;a++){
    
                    if(strcmp(Solucao[j][k][m].prof.nomeProfessor, Solucao[a][k][m].prof.nomeProfessor) == 0 && Solucao[j][k][m].CodigoOferta != -1 && Solucao[a][k][m].CodigoOferta != -1){ //ANALISA SE PROFESSOR ESTA EM DUAS SALAS AO MESMO TEMPO
                    	
					    b = 0 + (rand() % 5);
		            	c = 0 + (rand() % 2);
	            		if(Solucao[j][b][c].CodigoOferta != Solucao[j][k][m].CodigoOferta){
        					
        					aux = Solucao[j][b][c];
	                    	Solucao[j][b][c] = Solucao[j][k][m];
	                    	Solucao[j][k][m] = aux;
                			
						}
					    
                    }   
            	}
	        }
        }
	}
    
for(j=1;j<=numeroSemestres;j++){
    	
    	if(j==1){
            printf("\n SEMESTRE 1:\n\n");
        }else if(j==2){
            printf("\n SEMESTRE 2:\n\n");
        }else if(j==3){
            printf("\n SEMESTRE 3:\n\n");
        }else if(j==4){
            printf("\n SEMESTRE 4:\n\n");
        }else if(j==5){
            printf("\n SEMESTRE 5:\n\n");
        }else if(j==6){
            printf("\n SEMESTRE 6:\n\n");
        }else if(j==7){
            printf("\n SEMESTRE 7:\n\n");
        }else if(j==8){
            printf("\n SEMESTRE 8:\n\n");
        }
        
	    for(k=0;k<5;k++){
	    	
	    	if(k==0){
            	printf("   SEGUNDA --\n\n");
	        }else if(k==1){
	            printf("   TERCA --\n\n");
	        }else if(k==2){
	            printf("   QUARTA --\n\n");
	        }else if(k==3){
	            printf("   QUINTA --\n\n");
	        }else if(k==4){
	            printf("   SEXTA --\n\n");
	        }
	    	
	        for(m=0;m<2;m++){
	            printf("%s %s\n", Solucao[j][k][m].cadeira.nomeDisciplina, Solucao[j][k][m].prof.nomeProfessor);
	        }
	    }
	}
	//int d = FuncaoCusto1(h,numeroSemestres) + FuncaoCusto2(h,numeroSemestres);
	printf("AULAS SEGUIDAS EM UM MESMO DIA = %d\nAulas em mais de uma turma ao mesmo tempo = %d\n",FuncaoCusto1(Solucao,numeroSemestres),FuncaoCusto2(Solucao,numeroSemestres));
	printf("Professores que estao sem folga = %d\n",FuncaoCusto3(Solucao, numeroSemestres, numeroProfessores, RecProf));
	printf("Professores que estao com folga = %d\n",FuncaoCusto4(Solucao, numeroSemestres, numeroProfessores, RecProf));
    
    
SimulatedAnnealing(Solucao, taxaResfriamento, SAmax, TI, TF, numeroSemestres);




return 0;
}
