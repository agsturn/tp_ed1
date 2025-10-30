#include <stdio.h>
#include <stdlib.h>
#include "formula.h"

int main(){
    int n, m;

    printf("numero de variaveis e clausulas: ");
    scanf("%d %d", &n, &m);

    //aloca formula
    Formula *f = criaFormula(n, m);

    //add as clausulas (tem que fazer a logica ainda la em formula.c)
    printf("digite as clausulas:\n");

    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        adicionaClausula(f, i, x, y, z);
    }

    solucaoFormula(f);
    imprimeFormula(f);
    destroiFormula(f);

    return 0;
}

//Ana Gabriela e Marcus Leandro 