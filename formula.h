#ifndef FORMULA_H
#define FORMULA_H

typedef struct {
    int var[3]; //vetor com as 3 variaveis de cada clausula
}Clausula; 

typedef struct //TAD da formula
{
    int numVar; //numero de variaveis
    int numClau; //numero de clausulas
    Clausula *clausula; //vetor de clausulas
}Formula;

Formula *criaFormula (int n, int m); //alocar TAD formula vazia

void destroiFormula (Formula *formula); //dar free no TAD formula

void adicionaClausula (Formula *formula, int i, int x, int y, int z); //adiciona uma clausula na formula

void imprimeFormula (Formula *formula); //imprime o TAD formula no formato 3-CNF

int solucaoFormula (Formula *formula); //tenta achar uma valoração que satisfaça a fórmula

//Ana Gabriela e Marcus Leandro 
#endif