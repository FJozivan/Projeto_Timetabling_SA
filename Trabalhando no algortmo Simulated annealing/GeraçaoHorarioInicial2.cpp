#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include "Funcoes.h"

// SIMULATED ANNEALING
void SimulatedAnnealing(Oferta SolucaoInicial[MAX_SEMESTRE][5][2], float taxaResfriamento, int SAmax, float TI, float TF, int numeroSemestres, int numeroProfessores, Professor Prof[MAX_PROFESSORES]){
	FILE *horario = fopen("horario.html","a+");
	FILE *prob = fopen("probabilidades.txt","a+");
	FILE *S = fopen("soluPerfeitas.txt","a+");
//	FILE *f = fopen("Other.html","a+");
	int temp = 1, armaneza = 1000;
	int solp = 0;
	//int solBoas = 0,solRuins = 0,solOtimas = 0;
	//int soluGeral = 0;
	//double porSolBoas,porSolRuins,porSolOtimas;
	
	// ATRIBUINDO PISIÇOES VAZIAS A MATRIZ DE SOLUÇAO FINAL
    for(j = 1; j <= numeroSemestres; j++){
    	for(k = 0; k < 5; k++){
    		for(m = 0; m < 2; m++){
    			solucaoFinal[j][k][m].CodigoOferta = -1;
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
	// SOLUÇAO FINAL RECEBE A SOLUÇAO INICIAL
	for(j = 1; j <= numeroSemestres; j++){
    	for(k = 0; k < 5; k++){
    		for(m = 0; m < 2; m++){
    			solucaoFinal[j][k][m] = SolucaoInicial[j][k][m];
			}
		}   		
	}
	
	// RECEBENDO A TEMPERATURA INICIAL
	double Temperatura;
	
	// CRIAÇAO E INICIALIZAÇAO DA VARIAVEL QUE VAI INCREMENTAR ATE O NUMERO MAXIMO DE SOLUÇOES VIZINHAS 
	double iterT = 0;
	
	// FUNÇAO QUE ATRIBUI VALOR NULO A FUNÇAO RAND USADA PARA SORTEAR ALEATORIAMENTE AS POSIÇOES
	srand( (unsigned)time(NULL)); // Atribuindo valor nulo ao Rand() para os sorteios aleaatorios.
	int gh;
	
	// SIMULATED ANNEALING INICIA AQUI
	//while(funcaoObjetivo(solucaoFinal,numeroSemestres,numeroProfessores,Prof) > 0){
		printf("\n******************************************************************************************************************************************");
		Temperatura = TI;
		
		while(Temperatura > TF){
			while(iterT < SAmax){
				
				// SOLUÇAO VIZINHA RECEBE A SOLUÇAO ATUAL
				for(j = 1; j <= numeroSemestres; j++){
			    	for(k = 0; k < 5; k++){
			    		for(m = 0; m < 2; m++){
			    			solucaoVizinha[j][k][m] = SolucaoInicial[j][k][m];
						}
					}   		
				}
				 
				// TRABALHAR NESTA FUNÇAO IMPLEMENTANDO A MUDANÇA DE ACORDO COM AS DISCIPLINAS QUE UM PROFESSOR PODE MINISTRAR!!!!!!
				// FUNÇAO RESPONSAVEL POR GERAR SOLUÇOES VIZINHAS Obs.: 
				for(gh = 0; gh < 4; gh++){			    	
					
					j = 1 + rand() % 9;			
	                b = 0 + rand() % 5;
	                c = 0 + rand() % 2;
	                
	                k=b;
	                m=c; 
	                
	                b = 0 + rand() % 5;
	                c = 0 + rand() % 2;
	            	
	            	/* para gerar suloçoes vizinhas baseado na troca de slots entre duas disciplinas de mesma carga horaria
					deve-se pensar tambem se podera ser usado um slot vazio para alocar aquela disciplina, caso a segundo slot selecionado para ser trocado 
					seja vazio */
					
					/* Tambem deve-se pensar que para um semestre que so tenha uma disciplina de carga horaria dois, pois o while usado abaixo nao tera fim,
					pois a condição de parada sera quando encontrar uma disciplina diferente de mesma carga horaria, no caso de ser implementado a mudança descrita acima*/
	                
					aux = solucaoVizinha[j][b][c];
                	solucaoVizinha[j][b][c] = solucaoVizinha[j][k][m];
                	solucaoVizinha[j][k][m] = aux;		   
			    }
				// ENCERRA A GERRAÇAO DA SOLUÇAO VIZINHA
				
				// A VARIAVEL VERIFICAÇAO RECEBE A DIFERENCA ENTRE FUNÇOES DE CUSTO DA SOLUÇAO ATUAL E VIZINHA PARA UTILIZAR COMO COMPARAÇAO POSTERIORMENTE 
				verificacao = funcaoObjetivo(solucaoVizinha, numeroSemestres, numeroProfessores, Prof) - funcaoObjetivo(SolucaoInicial, numeroSemestres, numeroProfessores, Prof); // Calculando a variaçao da funçao
				
				// A VARIAVEL PROBABILIDADE RECEBE A PROBABILIDADE BASEADA NA FORMULA A SEGUIR UTILIZANDO-SE DA VARIAÇAO E DA TEMPERATURA ATUAL PARA POSIVELMENTE UTILIZAR SOLUÇOES DE POIR CASO
				probabilidade = pow(2.7,( ( -(verificacao) ) / Temperatura));
				
				// COMPARANDO FUNÇAO DE CUSTO DA SOLUÇAO VIZINHA COMA SOLUÇAO INICIAL
				if(verificacao < 0){
						
					for(j = 1; j <= numeroSemestres; j++){
			    		for(k = 0; k < 5; k++){
				    		for(m = 0; m < 2; m++){
				    			SolucaoInicial[j][k][m] = solucaoVizinha[j][k][m];
							}
						}   		
					}
					if( (funcaoObjetivo(solucaoVizinha, numeroSemestres, numeroProfessores, Prof)) < (funcaoObjetivo(solucaoFinal, numeroSemestres, numeroProfessores, Prof)) ){
						//solOtimas++;
						printf("\nSOU UMA SOLUÇÃO OTIMA COM FUNCAO DE CUSTO = %d",funcaoObjetivo(solucaoVizinha, numeroSemestres, numeroProfessores, Prof));
						for(j = 1; j <= numeroSemestres; j++){
							for(k = 0; k < 5; k++){
					    		for(m = 0; m < 2; m++){
					    			solucaoFinal[j][k][m] = solucaoVizinha[j][k][m];
								}
							}
						}
						//fprintf(sol,"%d,",funcaoObjetivo(solucaoVizinha,numeroSemestres,numeroProfessores,Prof));
					}else if((funcaoObjetivo(solucaoVizinha, numeroSemestres, numeroProfessores, Prof)) < (funcaoObjetivo(solucaoFinal, numeroSemestres, numeroProfessores, Prof))){
						printf("\nSOU UMA SOLUÇÃO BOA COM FUNCAO DE CUSTO = %d",funcaoObjetivo(solucaoVizinha, numeroSemestres, numeroProfessores, Prof));
					}
					
				}else{
					
					// Aqui as outras soluçoes boas chegam
					if(funcaoObjetivo(solucaoFinal,numeroSemestres,numeroProfessores,Prof) == 0 && funcaoObjetivo(solucaoVizinha,numeroSemestres,numeroProfessores,Prof) == 0){
						
						if(restricaoFraca2(solucaoVizinha,numeroSemestres,numeroProfessores,Prof) < restricaoFraca2(solucaoFinal,numeroSemestres,numeroProfessores,Prof)){
							
							for(j = 1; j <= numeroSemestres; j++){
			    				for(k = 0; k < 5; k++){
				    				for(m = 0; m < 2; m++){
				    					solucaoFinal[j][k][m] = solucaoVizinha[j][k][m];
									}
								}   		
							}
							printf("\nSOU OUTRA SOLUÇÃO OTIMA COM CUSTO = %d",funcaoObjetivo(solucaoVizinha, numeroSemestres, numeroProfessores, Prof));
						}
					}
					if(probabilidade > 0.9 && probabilidade < 1){
						printf("\nSOU UMA SOLUÇÃO QUE ENTROU NA PROBABILIDADE COM FUNCAO DE CUSTO = %d",funcaoObjetivo(solucaoVizinha, numeroSemestres, numeroProfessores, Prof));
						solp++;
						fprintf(prob,"%d, ",funcaoObjetivo(solucaoVizinha, numeroSemestres, numeroProfessores, Prof));
						for(j = 1; j <= numeroSemestres; j++){
							for(k = 0; k < 5; k++){
				  	  			for(m=0; m<2; m++){
				  	  				SolucaoInicial[j][k][m] = solucaoVizinha[j][k][m];
								}
							}
						}
						
					}	
				}
				iterT++; // variavel de interaçao e incrementada
			}
			
			/*if(funcaoObjetivo(solucaoFinal,numeroSemestres,numeroProfessores,Prof)==0){
				iterT=SAmax;
				Temperatura = TF;
			}
			*/
			if(funcaoObjetivo(solucaoFinal,numeroSemestres,numeroProfessores,Prof) < armaneza ){
				armaneza = funcaoObjetivo(solucaoFinal,numeroSemestres,numeroProfessores,Prof);
				
			}
			if(temp % 50 == 0){
				fprintf(S,"%d,",armaneza);
				armaneza = 500000;
			}
			
			
			Temperatura = Temperatura * taxaResfriamento; // A temperatura e incrementada ao ser mutiplicacda pela a taxa de resfriamento
			temp++;
			iterT = 0; // A variavel de interaçao recebe zero para realizar uma nova verificaçao;
		}
	//}
	fclose(prob);
	fclose(S);	
	// MOSTRA O RESULTADO
    printf("\n\nHORARIO GERADO:\n");
    
    fprintf(horario,"<html>\n\t<head>\n\t\t<meta cahrset=""\"UTF-8\""">\n\t\t<link href=""\"Style.css\""" rel=""\"stylesheet\""">\n\t</head>\n\t<body>\n");
    fprintf(horario,"\t\t<div class=""\"cabecalho\"""><h1>Horario Gerado</h1></div>\n");
       
	for(j = 1; j <= numeroSemestres; j++){
		
		if(j == 1){
            fprintf(horario,"\t\t\t<center><div class=""\"nome\""">1° Semestre</div>\n");
            fprintf(horario,"\t\t\t<table class=""semestre"" border=""1px"">\n");
        }else if(j == 2){
            fprintf(horario,"\t\t\t<div class=""\"nome\""">2° Semestre</div>\n");
            fprintf(horario,"\t\t\t<table class=""semestre"" border=""1px"">\n");
        }else if(j == 3){
            fprintf(horario,"\t\t\t<div class=""\"nome\""">3° Semestre</div>\n");
            fprintf(horario,"\t\t\t<table class=""semestre"" border=""1px"">\n");
        }else if(j == 4){
            fprintf(horario,"\t\t\t<div class=""\"nome\""">4° Semestre</div>\n");
            fprintf(horario,"\t\t\t<table class=""semestre"" border=""1px"">\n");
        }else if(j == 5){
            fprintf(horario,"\t\t\t<div class=""\"nome\""">5° Semestre</div>\n");
            fprintf(horario,"\t\t\t<table class=""semestre"" border=""1px"">\n");
        }else if(j == 6){
            fprintf(horario,"\t\t\t<div class=""\"nome\""">6° Semestre</div>\n");
            fprintf(horario,"\t\t\t<table class=""semestre"" border=""1px"">\n");
        }else if(j == 7){
            fprintf(horario,"\t\t\t<div class=""\"nome\""">7° Semestre</div>\n");
            fprintf(horario,"\t\t\t<table class=""semestre"" border=""1px"">\n");
        }else if(j == 8){
            fprintf(horario,"\t\t\t<div class=""\"nome\""">8° Semestre</div>\n");
            fprintf(horario,"\t\t\t<table class=""semestre"" border=""1px"">\n");
        }
    	
    	fprintf(horario,"\t\t\t\t<tr>\n\t\t\t\t\t<th class=""\"linha\""">Horarios/Dias</th>\n\t\t\t\t\t<th>Segunda</th>\n\t\t\t\t\t<th>Terça</th>\n\t\t\t\t\t<th>Quarta</th>\n\t\t\t\t\t<th>Quinta</th>\n\t\t\t\t\t<th>Sexta</th>\n\t\t\t\t</tr>\n");   
    	
		fprintf(horario,"\t\t\t\t<tr class=""\"linha\""">\n\t\t\t\t\t<th>6:20 - 8:10</th>\n");
	    for(k = 0; k < 5; k++){	        		                     		
			fprintf(horario,"\t\t\t\t\t<td>%s___%s</td>\n", solucaoFinal[j][k][0].cadeira.nomeDisciplina, solucaoFinal[j][k][0].prof.nomeProfessor);
	    }
	    fprintf(horario,"\t\t\t\t</tr>\n");
	    
	    fprintf(horario,"\t\t\t\t<tr class=""\"linha\""">\n\t\t\t\t\t<th>8:20 - 10:00</th>\n");
	    for(k = 0; k < 5; k++){	                  		
			fprintf(horario,"\t\t\t\t\t<td>%s___%s</td>\n", solucaoFinal[j][k][1].cadeira.nomeDisciplina, solucaoFinal[j][k][1].prof.nomeProfessor);
	    }
	    fprintf(horario,"\t\t\t\t</tr>\n");
	    fprintf(horario,"\t\t\t</table>\n");
	}
	fprintf(horario,"\t\t</center>\n");
	fprintf(horario,"\t</body>\n");
	fprintf(horario,"</html>\n");

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
	
	printf("Forte --- AULAS SEGUIDAS EM UM MESMO DIA = %d\nForte --- Aulas em mais de uma turma ao mesmo tempo = %d\n",FuncaoCusto1(solucaoFinal,numeroSemestres),FuncaoCusto2(solucaoFinal,numeroSemestres));
	
	printf("Forte --- Professores que estao sem folga = %d\n",FuncaoCusto3(solucaoFinal, numeroSemestres, numeroProfessores, RecProf));
	//printf("Professores que estao com folga = %d\n",FuncaoCusto4(solucaoFinal, numeroSemestres, numeroProfessores, RecProf));
	printf("Fraca --- Aulas no 2° horario com o 1° vago = %d\n",restricaoFraca1(solucaoFinal,numeroSemestres));
	//printf("Restriçao fraca 1 = %d\n",restricaoFraca1(solucaoFinal, numeroSemestres, numeroProfessores, RecProf));
	//printf("Restricao fraca 3 = %d\n",restricaoFraca3(solucaoFinal, numeroSemestres, numeroProfessores, RecProf));
	
	printf("a Temperatura foi incrementada  vezes =  %d\n",temp);
	printf("A quantidaee se soluçoes Geral foi =  %d\n",temp*SAmax);
	printf("entraram %d solucoes na probabilidade\n",solp);
	/*printf("A quantidaee se soluçoes Otimas foi =  %d\n",solOtimas);
	printf("A quantidaee se soluçoes Boas foi =  %d\n",solBoas);
	printf("A quantidaee se soluçoes Ruins foi =  %d\n",soluGeral - (solOtimas + solBoas));
	printf("A porcentahgem de soluçoes Otimas foi =  %.2lf\n",(solOtimas/soluGeral));
	printf("A porcentahgem de soluçoes Boas foi =  %.2lf\n",(solBoas/soluGeral));*/
	
	
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
    	fscanf(readProf,"%s %d\n", &RecProf[g].nomeProfessor,&RecProf[g].folga);
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
    
	// GERANDO A SOLUÇAO (HORARIO) INICIAL
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
	printf("funcao de custo geral = %d\n",funcaoObjetivo(Solucao, numeroSemestres, numeroProfessores, RecProf));
	printf("Restriçao fraca 1 = %d\n",restricaoFraca2(Solucao, numeroSemestres, numeroProfessores, RecProf));
	printf("Restricao fraca 3 = %d\n",restricaoFraca3(Solucao, numeroSemestres, numeroProfessores, RecProf)); 
    
SimulatedAnnealing(Solucao, taxaResfriamento, SAmax, TI, TF, numeroSemestres,numeroProfessores,RecProf);




return 0;
}
