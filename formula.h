#ifndef FORMULA_H
#define FORMULA_H

typedef struct formula Formula;

//aloca TAD formula vazio
Formula *criaFormula (int n, int m);

//libera memoria do TAD formula
void destroiFormula (Formula *formula);

//adiciona uma clausula na formula
void adicionaClausula (Formula *formula, int i, int x, int y, int z);

//imprime o TAD formula no formato 3-CNF
void imprimeFormula (Formula *formula);

//tenta achar uma valoracao que satisfaca a formula usando backtracking
int solucaoFormula (Formula *formula, int *valores, int indice);

//imprime a solucao encontrada
void imprimesolucao(Formula *formula, int *valores);

//verifica se a valoracao atual satisfaz a formula
int testeformula(Formula *formula, int *valores, int indice);

//Ana Gabriela e Marcus Leandro 
#endif