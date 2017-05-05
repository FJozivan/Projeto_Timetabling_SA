#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include "Funcoes.h"

// SIMULATED ANNEALING
void SimulatedAnnealing(Oferta SolucaoInicial[MAX_SEMESTRE][5][2], float taxaResfriamento, int SAmax, float TI, float TF, int numeroSemestres, int numeroProfessores, Professor Prof[MAX_PROFESSORES]){
	//FILE *sol = fopen("solOtimas.txt","a+");
	FILE *horario = fopen("Horario.txt","a+");
	//int temp = 1, armaneza = 1000;
	//int solp = 0;
	//int solBoas = 0,solRuins = 0,solOtimas = 0;
	//int soluGeral = 0;
	//double porSolBoas,porSolRuins,porSolOtimas;
	
	// ATRIBUINDO PISI�OES VAZIAS A MATRIZ DE SOLU�AO FINAL
    for(j = 1; j <= numeroSemestres; j++){
    	for(k = 0; k < 5; k++){
    		for(m = 0; m < 2; m++){
    			solucaoFinal[j][k][m].CodigoOferta = -1;
			}
		}   		
	}
	// ATRIBUINDO VALORES VAZIOS AS POSI�OES DA MATRIZ DE SOLU�AO VIZINHA
	for(j = 1; j <= numeroSemestres; j++){
    	for(k = 0; k < 5; k++){
    		for(m = 0; m < 2; m++){
    			solucaoVizinha[j][k][m].CodigoOferta = -1;
			}
		}   		
	}                                                                                                                                                                                                                                                           
	// SOLU�AO FINAL RECEBE A SOLU�AO INICIAL
	for(j = 1; j <= numeroSemestres; j++){
    	for(k = 0; k < 5; k++){
    		for(m = 0; m < 2; m++){
    			solucaoFinal[j][k][m] = SolucaoInicial[j][k][m];
			}
		}   		
	}
	
	// RECEBENDO A TEMPERATURA INICIAL
	double Temperatura = TI;
	
	// CRIA�AO E INICIALIZA�AO DA VARIAVEL QUE VAI INCREMENTAR ATE O NUMERO MAXIMO DE SOLU�OES VIZINHAS 
	double iterT = 0;
	
	// FUN�AO QUE ATRIBUI VALOR NULO A FUN�AO RAND USADA PARA SORTEAR ALEATORIAMENTE AS POSI�OES
	srand( (unsigned)time(NULL)); // Atribuindo valor nulo ao Rand() para os sorteios aleaatorios.
	
	// SIMULATED ANNEALING INICIA AQUI
	while(Temperatura > TF){
		while(iterT < SAmax){
			
			// SOLU�AO VIZINHA RECEBE A SOLU�AO ATUAL
			for(j = 1; j <= numeroSemestres; j++){
				
		    	for(k = 0; k < 5; k++){
		    		for(m = 0; m < 2; m++){
		    			solucaoVizinha[j][k][m] = SolucaoInicial[j][k][m];
					}
				}   		
			}
			 
			// TRABALHAR NESTA FUN�AO IMPLEMENTANDO A MUDAN�A DE ACORDO COM AS DISCIPLINAS QUE UM PROFESSOR POD MINISTRAR!!!!!!
			// FUN�AO RESPONSAVEL POR GERAR SOLU�OES VIZINHAS Obs.: A gera�ao de solu�ao vizinha esta sendo realizada pela troca de uma discplina com outra de mesma carga horaria em cada semestre.
			for(j = 1; j <= numeroSemestres;j++){			    	
							
                b = 0 + rand() % 5;
                c = 0 + rand() % 2;
                
                k=b;
                m=c; 
                
                b = 0 + rand() % 5;
                c = 0 + rand() % 2;
            	
                if(solucaoVizinha[j][k][m].cadeira.cargaHoraria == solucaoVizinha[j][b][c].cadeira.cargaHoraria){
                
					aux = solucaoVizinha[j][b][c];
                	solucaoVizinha[j][b][c] = solucaoVizinha[j][k][m];
                	solucaoVizinha[j][k][m] = aux;
            
				}else{
					while(solucaoVizinha[j][k][m].cadeira.cargaHoraria != solucaoVizinha[j][b][c].cadeira.cargaHoraria){
					
                    	b = 0 + rand() % 5;
                    	c = 0 + rand() % 2;
                    
						if(solucaoVizinha[j][k][m].cadeira.cargaHoraria == solucaoVizinha[j][b][c].cadeira.cargaHoraria){
                
							aux = solucaoVizinha[j][b][c];
	                    	solucaoVizinha[j][b][c] = solucaoVizinha[j][k][m];
	                    	solucaoVizinha[j][k][m] = aux;
	                    	
						}
					}
				}		   
		    }
		    
			// ENCERRA A GERRA�AO DA SOLU�AO VIZINHA
			
			// A VARIAVEL VERIFICA�AO RECEBE A DIFERENCA ENTRE FUN�OES DE CUSTO DA SOLU�AO ATUAL E VIZINHA PARA UTILIZAR COMO COMPARA�AO POSTERIORMENTE 
			verificacao = funcaoObjetivo(solucaoVizinha, numeroSemestres, numeroProfessores, Prof) - funcaoObjetivo(SolucaoInicial, numeroSemestres, numeroProfessores, Prof); // Calculando a varia�ao da fun�ao
			
			// A VARIAVEL PROBABILIDADE RECEBE A PROBABILIDADE BASEADA NA FORMULA A SEGUIR UTILIZANDO-SE DA VARIA�AO E DA TEMPERATURA ATUAL PARA POSIVELMENTE UTILIZAR SOLU�OES DE POIR CASO
			probabilidade = pow(2.7,( ( -(verificacao) ) / Temperatura));
			
			// COMPARANDO FUN�AO DE CUSTO DA SOLU�AO VIZINHA COMA SOLU�AO INICIAL
			if(verificacao < 0){
					
				for(j = 1; j <= numeroSemestres; j++){
		    		for(k = 0; k < 5; k++){
			    		for(m = 0; m < 2; m++){
			    			SolucaoInicial[j][k][m] = solucaoVizinha[j][k][m];
						}
					}   		
				}
				if((funcaoObjetivo(solucaoVizinha, numeroSemestres, numeroProfessores, Prof)) < (funcaoObjetivo(solucaoFinal, numeroSemestres, numeroProfessores, Prof))){
					//solOtimas++;
					for(j = 1; j <= numeroSemestres; j++){
						for(k = 0; k < 5; k++){
				    		for(m = 0; m < 2; m++){
				    			solucaoFinal[j][k][m] = solucaoVizinha[j][k][m];
							}
						}
					}
					//fprintf(sol,"%d,",funcaoObjetivo(solucaoVizinha,numeroSemestres,numeroProfessores,Prof));
				}
				
			}else{
				
				if(probabilidade > 0  &&  probabilidade < 1){
					//solp++;
					for(j = 1; j <= numeroSemestres; j++){
						for(k = 0; k < 5; k++){
			  	  			for(m=0; m<2; m++){
			  	  				SolucaoInicial[j][k][m] = solucaoVizinha[j][k][m];
							}
						}
					}
					
				}	
			}
			
			// FIM DA COMPARA�AO
			//printf("entrei\n");
			
			iterT++; // variavel de intera�ao e incrementada
		}
		//if(funcaoObjetivo(solucaoFinal,numeroSemestres,numeroProfessores,Prof) < armaneza ){
			//armaneza = funcaoObjetivo(solucaoFinal,numeroSemestres,numeroProfessores,Prof);
			
		//}
		//if(temp % 50 == 0){
			//	fprintf(sol,"%d,",armaneza);
			//	armaneza = 1000;
		//}
		
		Temperatura = Temperatura * taxaResfriamento; // A temperatura e incrementada ao ser mutiplicacda pela a taxa de resfriamento
		//temp++;
		iterT = 0; // A variavel de intera�ao recebe zero para realizar uma nova verifica�ao;
	}
	//fclose(sol);
	
	// MOSTRA O RESULTADO
    printf("\n\nHORARIO GERADO:\n");
       
	for(j = 1; j <= numeroSemestres; j++){
		
		if(j == 1){
            fprintf(horario,"SEMESTRE 1:\n");
        }else if(j == 2){
            fprintf(horario,"SEMESTRE 2:\n");
        }else if(j == 3){
            fprintf(horario,"SEMESTRE 3:\n");
        }else if(j == 4){
            fprintf(horario,"SEMESTRE 4:\n");
        }else if(j == 5){
            fprintf(horario,"SEMESTRE 5:\n");
        }else if(j == 6){
            fprintf(horario,"SEMESTRE 6:\n");
        }else if(j == 7){
            fprintf(horario,"SEMESTRE 7:\n");
        }else if(j == 8){
            fprintf(horario,"SEMESTRE 8:\n");
        }
    	
    	fprintf(horario,"Horario/Dia Segunda Ter�a Quarta Quinta Sexta\n");   
		fprintf(horario,"6:30-8:20 ");
		
	    for(k = 0; k < 5; k++){	        		
			fprintf(horario,"%s___%s ", solucaoFinal[j][k][0].cadeira.nomeDisciplina, solucaoFinal[j][k][0].prof.nomeProfessor);
	    }
	    fprintf(horario,"\n8:30-10:00 ");
	    for(k = 0; k < 5; k++){	        		
			fprintf(horario,"%s___%s ", solucaoFinal[j][k][1].cadeira.nomeDisciplina, solucaoFinal[j][k][1].prof.nomeProfessor);
	    }
	    fprintf(horario,"\n");
	}
	


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
	//printf("entraram %d solucoes na probabilidade\n",solp);
	//printf("a Temperatura foi incrementada  vezes =  %d\n",temp);
	/*printf("A quantidaee se solu�oes Geral foi =  %d\n",soluGeral);
	printf("A quantidaee se solu�oes Otimas foi =  %d\n",solOtimas);
	printf("A quantidaee se solu�oes Boas foi =  %d\n",solBoas);
	printf("A quantidaee se solu�oes Ruins foi =  %d\n",soluGeral - (solOtimas + solBoas));
	printf("A porcentahgem de solu�oes Otimas foi =  %.2lf\n",(solOtimas/soluGeral));
	printf("A porcentahgem de solu�oes Boas foi =  %.2lf\n",(solBoas/soluGeral));*/
	
	
}


// FUN�AO PRINCIPAL
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
	
    // ATRIBUINDO PISI�OES VAZIAS A MATRIZ DE HORARIOS
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
    	fscanf(readProf,"%d\n",&RecProf[g].DisApto);
    	for(d = 0; d < RecProf[g].DisApto; d++){
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
    
	// GERANDO A SOLU�AO (HORARIO) INICIAL
    for(j = 1; j <= numeroSemestres; j++){
         for(k = 0; k < 5; k++){
        	for(m = 0; m < 2; m++){
				
                for(a = 1; a <= numeroDisciplinas; a++){
                	
                	if(RecCadeiras[a].Aloca == 0){
                		
						if(RecCadeiras[a].cargaHoraria == 2 && RecCadeiras[a].semestre == j){
														
							for(d = 0; d < numeroProfessores; d++){
								for(g = 0; g < RecProf[d].DisApto; g++){
								
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
								for(g = 0; g < RecProf[d].DisApto; g++){
								
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
	            		if(Solucao[a][b][c].CodigoOferta != Solucao[a][k][m].CodigoOferta){
        					
        					aux = Solucao[a][b][c];
	                    	Solucao[a][b][c] = Solucao[a][k][m];
	                    	Solucao[a][k][m] = aux;
                			
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
	printf("funcao de custo geral = %d",funcaoObjetivo(Solucao, numeroSemestres, numeroProfessores, RecProf));
    
    
SimulatedAnnealing(Solucao, taxaResfriamento, SAmax, TI, TF, numeroSemestres,numeroProfessores,RecProf);




return 0;
}
