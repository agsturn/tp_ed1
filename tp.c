#include <stdio.h>
#include <stdlib.h>
#include "formula.h"

int main(){
    int n, m;

    scanf("%d %d", &n, &m);

    Formula *f = criaFormula(n, m);
    if(f == NULL){
        return 1;
    }

    for (int i=0; i<m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        adicionaClausula(f, i, x, y, z);
    }

    int *valores = (int *)malloc(n * sizeof(int));
    if(valores == NULL){
        destroiFormula(f);
        return 1;
    }

    int resultado = solucaoFormula(f, valores, 0);

    if(resultado){
        imprimeFormula(f);
        imprimesolucao(f, valores);
    } else 
        printf("Formula insatisfazível!\n");

    free(valores);
    destroiFormula(f);

    return 0;
}

//Ana Gabriela e Marcus Leandro