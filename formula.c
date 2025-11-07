#include <stdio.h>
#include <stdlib.h>
#include "formula.h"

//estrutura que armazena as tres variaveis de cada clausula
typedef struct {
    int var[3]; //positivo = variavel normal      negativo = variavel negada
}Clausula; 

struct formula
{
    int numVar; //numero de variaveis
    int numClau; //numero de clausulas
    Clausula *clausula; //vetor de clausulas
};

Formula *criaFormula (int n, int m){
    Formula *formula = (Formula *)malloc(sizeof(Formula));
    if(formula == NULL)
        return NULL;
    formula->numVar = n;
    formula->numClau = m;
    
    //aloca vetor de clausulas
    formula->clausula = (Clausula *)malloc(m * sizeof(Clausula));
    if (formula->clausula == NULL){
        free(formula);
        return NULL;
    }
    return formula;
}

void destroiFormula (Formula *formula){
    if(formula){
        free(formula->clausula); //libera vetor primeiro
        free(formula);
    }
}

void adicionaClausula (Formula *formula, int i, int x, int y, int z){
    formula->clausula[i].var[0] = x;
    formula->clausula[i].var[1] = y;
    formula->clausula[i].var[2] = z;
}

void imprimeFormula (Formula *formula){
    printf("Formula:\n"); 
    
    for(int i=0; i < formula->numClau; i++){
        printf("(");

        for (int j=0; j<3; j++){
            int valor = formula->clausula[i].var[j];
            //pega o valor absoluto
            int num = (valor < 0 ? valor * -1 : valor);
            //converte numero para letra correspondente (tabela ascii)
            char letra = 'a' + num - 1;

            printf("%s%c", valor < 0 ? "~" : "", letra);

            if (j < 2)
                printf(" v ");
        }
        printf(")");

        if (i < formula->numClau - 1)
            printf(" ∧ ");
    }
    printf("\n");
}

int solucaoFormula (Formula *formula,int *valores, int indice){
    //caso base: todas as variaveis foram atribuidas
    if(indice == formula->numVar){
        return testeformula(formula,valores,indice); 
    }

    //tenta valorar como verdadeiro
    valores[indice] = 1;
    if(solucaoFormula(formula, valores, indice + 1)){
        return 1;       
    }

    //backtrack: tenta valorar como falso
    valores[indice] = 0;
    if(solucaoFormula(formula, valores, indice + 1)){
        return 1;
    }
    return 0;
} 

void imprimesolucao(Formula *formula, int *valores){
    printf("Solução encontrada:\n");
    
    for(int i=0; i < formula->numVar; i++){
        char letra = 'a' + i;
        printf("%c: %s\n", letra, valores[i] ? "True" : "False");
    }
}

int testeformula(Formula *formula, int *valores, int indice)
{
    int sol = 0;

    //percorre todas as clausulas
    for (int i=0; i<formula->numClau; i++)
    {
        int clausulaSatisfeita = 0;

        //verifica cada variavel da clausula
        for (int j=0; j<3; j++)
        {
            int var = formula->clausula[i].var[j];

            //variavel positiva: satisfeita se valor = 1
            if (var > 0)
            {
                if (valores[var - 1] == 1)
                {
                    clausulaSatisfeita = 1;
                    break; //clausula ja esta satisfeita
                }
            }
            //variavel negada: satisfeita se valor = 0
            else
            {
                //converte variavel negativa para indice positivo
                if (valores[(var * -1) - 1] == 0)
                {
                    clausulaSatisfeita = 1;
                    break;
                }
            }
        }

        if (clausulaSatisfeita)
            sol++;
    }

    //formula satisfeita se todas as clausulas forem verdadeiras
    if (sol == formula->numClau)
        return 1;

    return 0;
}

//Ana Gabriela e Marcus Leandro