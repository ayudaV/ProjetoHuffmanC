typedef struct node{
    char ch;
    int prio;
    struct node *esq;
    struct node *dir;
}node;

typedef struct charHuff{
    char ch;
    char caminho[1024];
}charHuff;

typedef struct elemento* Lista;

Lista* cria_lista();
node* newNode(char _ch, int _prio,node* esq, node* dir);
void libera_lista(Lista* li);
int insere_lista_ordenada(Lista* li, node* no);
int remove_lista_inicio(Lista* li);
int tamanho_lista(Lista* li);
int consulta_lista_pos(Lista* li, int pos, node *no);

