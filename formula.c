#include <stdio.h>
#include <stdlib.h>
#include "formula.h"

typedef struct {
    int var[3]; //vetor com as 3 variaveis de cada clausula
}Clausula; 

struct formula //TAD da formula
{
    int numVar; //numero de variaveis
    int numClau; //numero de clausulas
    Clausula *clausula; //vetor de clausulas
};

Formula *criaFormula (int n, int m){
    Formula *formula = (Formula *)malloc(sizeof(Formula)); //aloca formula
    if(formula == NULL){ //tratamento de erro
        //printf("memoria insuficiente");
        return NULL;
    }
    formula->numVar = n;
    formula->numClau = m;
    formula->clausula = (Clausula *)malloc(m * sizeof(Clausula)); //aloca clausula
    if (formula->clausula == NULL){ //tratamento de erro
        //printf("memoria insuficiente");
        free(formula);
        return NULL;
    }
    return formula;
}

void destroiFormula (Formula *formula){
    if(formula){ //ve se formula nao eh nulo
        free(formula->clausula); //free na clausula primeiro
        free(formula); //free na formula depois
    }
}

void adicionaClausula (Formula *formula, int i, int x, int y, int z){
    formula->clausula[i].var[0] = x;
    formula->clausula[i].var[1] = y;
    formula->clausula[i].var[2] = z;
}


void imprimeFormula (Formula *formula){
    printf("Formula:\n"); 
    
    for(int i = 0; i < formula->numClau; i++){
        printf("(");

        for (int j = 0; j < 3; j++){
            int valor = formula->clausula[i].var[j];
            int num = (valor < 0 ? valor * -1 : valor);

            char letra = 'a' + num - 1;

            printf("%s%c", valor < 0 ? "~" : "", letra);

            if (j < 2){
                printf(" v ");
            }
        }
        printf(")");

        if (i < formula->numClau - 1){
            printf(" ∧ ");
        }
    }
    printf("\n");
}


int solucaoFormula (Formula *formula,int *valores, int indice){
    if(indice == formula->numVar){ // verifica se valoracao eh satisfeita
        return testeformula(formula,valores,indice); 
    }

    valores[indice] = 1; // tenta como verdadeiro
    if(solucaoFormula(formula, valores, indice + 1)){
        return 1;       
    }

    valores[indice] = 0; // tenta como falso
    if(solucaoFormula(formula, valores, indice + 1)){
        return 1;
        }
    return 0;
} 


void imprimesolucao(Formula *formula, int *valores){
    printf("Solução encontrada:\n");
    
    for(int i = 0; i < formula->numVar; i++){
        char letra = 'a' + i;
        printf("%c: %s\n", letra, valores[i] ? "True" : "False");
    }
}

int testeformula(Formula *formula, int *valores, int indice)
{
    int sol = 0;

    for (int i = 0; i < formula->numClau; i++)
    {
        int clausulaSatisfeita = 0;

        for (int j = 0; j < 3; j++)
        {
            int var = formula->clausula[i].var[j];

            if (var > 0)
            {
                if (valores[var - 1] == 1)
                {
                    clausulaSatisfeita = 1;
                    break;
                }
            }
            else
            {
                if (valores[(var * -1) - 1] == 0)
                {
                    clausulaSatisfeita = 1;
                    break;
                }
            }
        }

        if (clausulaSatisfeita)
        {
            sol++;
        }
    }

    if (sol == formula->numClau)
    {
        return 1;
    }

    return 0;
}

//Ana Gabriela e Marcus Leandro