#include <stdio.h>
#include <stdlib.h>
# include <string.h>
#include "Arvore.h"

node* newNode(char _ch,node* _esq, node* _dir)
{
    node* nNode = (node*)malloc(sizeof(node));
    nNode->ch = _ch;
    nNode->esq = _esq;
    nNode->dir = _dir;
    return nNode;
}
node* newArvore(char arvBuilder[],int* pos)
{
    /*Percorre char a char a sring arvBuilder,
    cria um no usando o char lido e se o valor for NULL
    somar 1 na variavel pos e depois atribui pra a esquerda
    e para a direita do no o endereco de um novo no ultilizando recursao
    */
    node* no = newNode(arvBuilder[(*pos)],NULL,NULL);
    if(arvBuilder[(*pos)] == NULL)
    {
        (*pos)++;
        no->esq = newArvore(arvBuilder,pos);
        (*pos)++;
        no->dir = newArvore(arvBuilder,pos);
    }
    return no;
}
/* Metodos apenas para visualizacao*/
int Altura(node *noAtual)
{
    int alturaEsquerda, alturaDireita;
    if (noAtual == NULL)
        return 0;
    alturaEsquerda = Altura(noAtual->esq);
    alturaDireita  = Altura(noAtual->dir);
    if (alturaEsquerda >= alturaDireita)
        return 1 + alturaEsquerda;
    return 1 + alturaDireita;
}
void padding ( char ch, int n ){
  int i;
  for ( i = 0; i < n; i++ )
    putchar ( ch );
}

void printArvore (node *root, int level ){
  if ( root == NULL ) {
    padding ( '\t', level );
    puts ( "~" );
  }
  else {
    printArvore ( root->dir, level + 1 );
    padding ( '\t', level );
    printf ( "|%c|\n", root->ch);
    printArvore ( root->esq, level + 1 );
  }
}
