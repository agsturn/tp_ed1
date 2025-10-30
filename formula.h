#ifndef FORMULA_H
#define FORMULA_H

typedef struct formula Formula;

Formula *criaFormula (int n, int m); //alocar TAD formula vazia

void destroiFormula (Formula *formula); //dar free no TAD formula

void adicionaClausula (Formula *formula, int i, int x, int y, int z); //adiciona uma clausula na formula

void imprimeFormula (Formula *formula); //imprime o TAD formula no formato 3-CNF

int solucaoFormula (Formula *formula, int *valores, int indice); //tenta achar uma valoração que satisfaça a fórmula

//Ana Gabriela e Marcus Leandro 
#endif