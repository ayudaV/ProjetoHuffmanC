#include <stdio.h>
#include <stdlib.h>
# include <string.h>
#include "ListaDinEncad.h"

/*struct utilizada na lista ligada para guardar os nos*/
struct elemento{
     node* nodeChar;
    struct elemento* prox;
};
typedef struct elemento Elem;

/*Cria uma lista e aloca espaco na memoria*/
Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}
/*Construtor de node*/
node* newNode(char _ch, int _prio,node* _esq, node* _dir)
{
    node* nNode = (node*)malloc(sizeof(node));
    nNode->ch = _ch;
    nNode->prio = _prio;
    nNode->esq = _esq;
    nNode->dir = _dir;
    return nNode;
}
/*Percorre a lista liberando seu conteudo*/
void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

/*Encontra a posição cetta na lista ligada e insere um novo no*/
int insere_lista_ordenada(Lista* li, node *al){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->nodeChar = al;
    if((*li) == NULL){
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        Elem *ant, *atual = *li;
        while(atual != NULL && atual->nodeChar->prio < al->prio){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}
/*Passa o endereco do primeiro conteudo para o proximo*/
int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)
        return 0;

    Elem *no = *li;
    *li = no->prox;
    return 1;
}
/*Percorre a lista e retorna o tamanho*/
int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}
/* boolean que verifica se a lista esta vazia*/
int lista_vazia(Lista* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

/*Pega os 2 primeiros nos da lista, cria um novo no com o primeiro no da lista
sendo o no esquerdo, o segundo no como o da direita, e depois adiciona o novo no
tendo como prioridade a soma das prioridade dos filhos */
int juntarNos(Lista* li) {
    while(tamanho_lista(li) > 1)
    {
        Elem* noEsq = *li;
        remove_lista_inicio(li);
        Elem* noDir = *li;
        remove_lista_inicio(li);
        node *juncNo = newNode(0, (noDir->nodeChar->prio + noEsq->nodeChar->prio),noEsq->nodeChar, noDir->nodeChar );
        insere_lista_ordenada(li,juncNo);
    }
    return 0;
}
/*Percorre a arvore e se for para a esquerda guarda 0, se for para a direita guarda 1 no caminhoAtual
quando encontra um char ele salva uma copia do caminho atual na matriz codChar no enderco equivalente ao numero do char
*/
void preencherTabela(node *atual, char caminho[], char* codChar[256][256]){
    char caminhoAtual[256] = {0};
    strcpy(caminhoAtual, caminho);

    if(atual->esq == NULL){
        char* nCaminhoChar = (char*) malloc(sizeof(256));
        strcpy(nCaminhoChar,caminhoAtual);
        codChar[atual->ch][0] = nCaminhoChar;
    }
    if(atual->esq != NULL){
        caminhoAtual[strlen(caminho)] = '0';
        char _caminho[256];
        strcpy(_caminho, caminhoAtual);
        preencherTabela(atual->esq, _caminho, codChar);
    }
    if(atual->dir != NULL){
        caminhoAtual[strlen(caminho)] = '1';
        char _caminho[256];
        strcpy(_caminho, caminhoAtual);
        preencherTabela(atual->dir, _caminho, codChar);
    }
}

void getArvoreComprimida(node* raiz, char* str[511],int* contador)
{
    /*Percorre a arvore escrevendo todos os caracteres presentes nela incluindo
    os NULL das subarvores*/
    str[(*contador)++] = raiz->ch;
    if(raiz->esq != NULL)
    {
        getArvoreComprimida(raiz->esq,str,contador);
        getArvoreComprimida(raiz->dir,str,contador);
    }
}
/*Metodos apenas para visualizacao*/
void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL){
        printf("-------------------------------\n");
        printf("Character: %c\n",no->nodeChar->ch);
        printf("Prioridade: %d\n",no->nodeChar->prio);
        printf("-------------------------------\n");

        no = no->prox;
    }
}
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
    printf ( "|%c: %d|\n", root->ch, root->prio);
    printArvore ( root->esq, level + 1 );
  }
}
