// DEFINIÇAO DE CONSTANTES 
#define MAXNomeDisciplina	100
#define MAXNomeProfessor	100
#define MAXNomeCurso	100
#define MAX_SEMESTRE	12
#define MAX_DISCIPLINAS  100
#define MAX_PROFESSORES  100

//	ESTRUTURA DE DADOS DE CADA VARIAVEL:

// Para as Disciplinas
typedef struct disciplina{
	char nomeDisciplina[MAXNomeDisciplina];
	int cargaHoraria;
	int codigoDisciplina;
	char Curso[MAXNomeCurso];
	int semestre;
	int Aloca;
	int preferencia;
}Disciplina;
 
// Para os Professores
 typedef struct professor{
	char nomeProfessor[MAXNomeProfessor];
	Disciplina DisMinis[10];
	int DisApto;
 }Professor;
 
/*// Para as Turmas
 typedef struct turma{
	char Curso[MAXNomeCurso];
	int semestre;
	Disciplina dis;
 }Turma;*/
 
// Para as Ofertas
typedef struct oferta{
	Disciplina cadeira;
	Professor prof;
	int CodigoOferta;
}Oferta;

// DECLARANDO AS VARIAVEIS

// Variaveis para geraçao da suloçao inicial
Oferta Solucao[MAX_SEMESTRE][5][2];     	// Matriz Tridimensional de Horarios.
Disciplina RecCadeiras[MAX_DISCIPLINAS];    // Vetor para receber as Disciplinas
Professor RecProf[MAX_PROFESSORES];         // Vetor para receber os Professores e as respectivas disciplinas ministradas por cada um deles
int numeroSemestres;              			// Variavel que armazena o numero de semestres.
int numeroDisciplinas;            			// Variavel que armazena o numero de Disciplinas
int numeroProfessores;                      // Variavel que armazena o numero de Professores
int j, k, m, d, a, g;  				        // Variavel de apoio para trabalhar com as posiçoes dos vetores e das matrizes
int  b, c;                                  // Variaveis de apoio para o sorteio de posiçoes aleatorias da matriz
int DisApto, armP = 0, armPosi = 0;      	// Variaveis para trabalhar com o armazenamento de (quantidade de discilinas que o professor esta apto aministrar, armazenamento de preferencias maiores, armazenamento de posiçao dessa preferencia)  

// Variaveis para o Simulated Annealing 
Oferta solucaoVizinha[MAX_SEMESTRE][5][2];  // Matriz tridimensional para armzenamento de de soluçoes vizinhas
Oferta aux;                  				// Variavel Auxiliar para receber asa ofertas da soluçao vizinha
Oferta solucaoFinal[MAX_SEMESTRE][5][2];    // Matriz tridimensional para armazenamento da melhor soluçao encontrada 
double taxaResfriamento = 0.995;             // taxa de resfriamento
int SAmax = 10;                            // numero de interacoes maxima a cada temperatura
double TI = 10;                               // temperatura inicial
double TF = 0.001;                           // temperatura final
double probabilidade;                        // Variavel recebe a probabilidade de usar um pessimo local
int verificacao;                            // Variavel recebe a diferença entre funçao de custo da soluçao vizinha e da soluçao inicial


// Calcula a quantidade de vezes que uma mesma mesma disciplina e ministrada 4 vezes seguidas em um dia 
int FuncaoCusto1(Oferta h[MAX_SEMESTRE][5][2], int numeroSemestre){
	
	int contDisciplinas = 0;
	
	
	for(j=1;j<=numeroSemestre;j++){
        for(k=0;k<5;k++){
            for(m=0;m<1;m++){
    			
				if(stricmp(h[j][k][m].cadeira.nomeDisciplina, h[j][k][m+1].cadeira.nomeDisciplina) == 0 && h[j][k][m].CodigoOferta != -1 && h[j][k][m+1].CodigoOferta != -1){ //ANALISA SE PROFESSOR ESTA EM DUAS SALAS AO MESMO TEMPO
                	
				    contDisciplinas++;
                }   
            	
	        }
        }
	}
    contDisciplinas = contDisciplinas * 250;
    return contDisciplinas;
	
}

// Calcula a quantidade de vezez que um professor da aulas em mais de uma turma ao mesmo tempo
int FuncaoCusto2(Oferta h[MAX_SEMESTRE][5][2], int numeroSemestre){
	
	int contProfessor = 0;
	
	
    for(j=1;j<=numeroSemestre;j++){
        for(k=0;k<5;k++){
            for(m=0;m<2;m++){
                for(a = j+1;a<=numeroSemestres;a++){
    
                    if(stricmp(h[j][k][m].prof.nomeProfessor, h[a][k][m].prof.nomeProfessor) == 0 && h[j][k][m].CodigoOferta != -1 && h[a][k][m].CodigoOferta != -1){ //ANALISA SE PROFESSOR ESTA EM DUAS SALAS AO MESMO TEMPO
                    	
					    contProfessor++;
                    }   
            	}
	        }
        }
	} 
	contProfessor = contProfessor * 1000;
    return contProfessor;
	
}
// Calcula quantos professore estao sem folga
int FuncaoCusto3(Oferta h[MAX_SEMESTRE][5][2], int numeroSemestre,int numeroProfessores,Professor RecProf[MAX_PROFESSORES]){
	
	int contDias = 0, Penalidade = 0;
	for(a = 0; a < numeroProfessores; a++){
		for(k = 0; k < 5; k++){
			for(j = 1; j <= numeroSemestres; j++){
				for(m = 0;m<1;m++){
				
					if( ( stricmp(RecProf[a].nomeProfessor, h[j][k][m].prof.nomeProfessor) == 0 && h[j][k][m].CodigoOferta != -1 ) || ( stricmp(RecProf[a].nomeProfessor, h[j][k][m+1].prof.nomeProfessor) == 0 && h[j][k][m+1].CodigoOferta != -1)  ){
						contDias++;
				        j = numeroSemestres + 1;
					}
				
				}
			}
		}
		if(contDias == 5){
			Penalidade++;
		}
		contDias = 0;	
	}
	Penalidade = Penalidade * 500;
    return Penalidade;
	
}

int FuncaoCusto4(Oferta h[MAX_SEMESTRE][5][2], int numeroSemestres,int numeroProfessores,Professor RecProf[MAX_PROFESSORES]){
	
	int cont = 0,contF = 0;
	for(a = 0; a < numeroProfessores; a++){
		for(k = 0; k < 5; k++){
			for(j = 1; j <= numeroSemestres; j++){
				for(m = 0;m<1;m++){
				
					if( ( stricmp(RecProf[a].nomeProfessor, h[j][k][m].prof.nomeProfessor) == 0 && h[j][k][m].CodigoOferta != -1 ) || ( stricmp(RecProf[a].nomeProfessor, h[j][k][m+1].prof.nomeProfessor) == 0 && h[j][k][m+1].CodigoOferta != -1)  ){
						cont++;
				        j = numeroSemestres + 1;
					}
				
				}
			}
		}
		if(cont < 5){
			contF++;
		}
		cont = 0;	
	}
	
    return contF;
	
}
// FUNÇAO QUE CALCULA A FUNLAO OBJETIVO DE DETERMINADA SOLUÇAO ---- Pronta!!!
int funcaoObjetivo(Oferta h[MAX_SEMESTRE][5][2], int numeroSemestres,int numeroProfessores,Professor RecProf[MAX_PROFESSORES]){
	
	int FuncaoObjetivo;
	FuncaoObjetivo = FuncaoCusto1(h,numeroSemestres) + FuncaoCusto2(h,numeroSemestres) + FuncaoCusto3(h,numeroSemestres,numeroProfessores,RecProf);
	return FuncaoObjetivo;
}

int comparacaoFuncaoObjetivo(Oferta h[MAX_SEMESTRE][5][2],Oferta s[MAX_SEMESTRE][5][2], int numeroSemestres,int numeroProfessores,Professor RecProf[MAX_PROFESSORES]){
	int verifica;
	verifica = funcaoObjetivo(h, numeroSemestres, numeroProfessores, RecProf) - funcaoObjetivo(s, numeroSemestres, numeroProfessores, RecProf);
	return verifica;
}
