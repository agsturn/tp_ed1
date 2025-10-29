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
    formula->clausula = (Clausula *)malloc(m * sizeof(Clausula)); //aloca clausula
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

void imprimeFormula (Formula *formula){
    printf("Formula:\n"); 
    
    for(int i=0;i<formula->numClau;i++){
        printf("(");

        for (int j=0;j<3;j++){
           int valor = formula->clausula[i].var[j];
           int num = valor;

           char letra = 'a' + num - 1;
           
           if(num<0){
                num = num * -1; // transforma em positivo
           }

            if(num<0){ //confere se eh negativo
                    printf("¬%c", letra);
                } else {
                    printf("%c", letra);
                }

                if (j < 2){
                printf(" v ");
                }
        }
        printf(") ");

        if (i < formula->numClau - 1){
            printf("^ ");
        }
    }
}


int solucaoFormula (Formula *formula,int *valores, int indice){
    if(indice == formula->numVar){ // verifica se valoracao eh satisfeita
        return 1; //achou uma solucao
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

//Ana Gabriela e Marcus Leandro