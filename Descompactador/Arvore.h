typedef struct node{
    char ch;
    struct node *esq;
    struct node *dir;
}node;

node* newNode(char _ch,node* esq, node* dir);
node* newArvore(char arvBuilder[],int* pos);
