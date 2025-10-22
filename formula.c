#include <stdio.h>
#include <stdlib.h>
#include "formula.h"

Formula *criaFormula (int n, int m){
    Formula *formula = (Formula *)malloc(sizeof(Formula)); //aloca formula
    if(formula == NULL){ //tratamento de erro
        printf("memoria insuficiente");
        return NULL;
    }
    formula->numVar = n;
    formula->numClau = m;
    formula->clausula == (Clausula *)malloc(m * sizeof(Clausula)); //aloca clausula
    if (formula->clausula == NULL){ //tratamento de erro
        printf("memoria insuficiente");
        free(formula);
        return NULL;
    }
    return formula;
}

void destroiFormula (Formula *formula){
    if(formula){ //ve se formula não é nulo
        free(formula->clausula); //free na clausula primeiro
        free(formula); //free na formula depois
    }
}

void adicionaClausula (Formula *formula, int i, int x, int y, int z){
    formula->clausula[i].var[0] = x;
    formula->clausula[i].var[1] = y;
    formula->clausula[i].var[2] = z;
}

void imprimeFormula (){

}

int solucaoFormula (){

}

//Ana Gabriela e Marcus Leandro 