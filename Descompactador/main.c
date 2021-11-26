#include <stdio.h>
#include <stdlib.h>
#include "Arvore.c"
int main()
{
    /*Pegando o nome do arquivo;*/
printf("Digite o nome do arquivo que deseja descompactar:\n");
    char nomeArq[100];
    scanf("%s", nomeArq);

    char caminho[] = "C:/temp/";
    strcat(caminho, nomeArq);

    int i;

    system("cls");

    /*Buscando o arquivo e pegando seu tamanho em bytes;*/
    printf("\nLeitura do arquivo situado em %s:\n", caminho);

    FILE* arquivo = fopen(caminho, "rb");
    FILE* lengthFile = fopen(caminho, "r");

    if (arquivo == NULL) {
        printf("File Not Found!\n");
        return -1;
    }
    fseek(lengthFile, 0L, SEEK_END);
    long int tamanho = ftell(lengthFile);
    printf("Tamanho do arquivo: %d bytes\n", tamanho);

    /*Lendo o arquivo e separando suas partes;*/
    char texto[tamanho-12];
    fread( texto, sizeof( char ), tamanho-12, arquivo );

    int valoresNumericos[3] = {0,0,0};
    fread( valoresNumericos, sizeof( int ), 3, arquivo );

    /*Imprime o endereco de saida;*/
    char camSaida[valoresNumericos[0]];
    for(i=0; i < valoresNumericos[0];i++){
        camSaida[i] = texto[i];
    }
    printf("%s\n",camSaida);
    /*Constroi a arvore;*/
    char arvBuilder[valoresNumericos[1]];
    int j;
    for(j=0; j < valoresNumericos[1];j++) {
        arvBuilder[j] = texto[i];
        i++;
    }

    /*Imprime a arvore;*/
    int pos = 0;
    node* raiz = newArvore(arvBuilder,&pos);
    int altura = Altura(raiz);
    printArvore(raiz,altura);

    /*Abre o arquivo de saida;*/
    FILE *write_ptr;
    unsigned char buffer[10];
    write_ptr = fopen(camSaida,"wb");

    if(raiz->ch != NULL)
    {
        /*Arquivo de apenas 1 tipo de caracter!*/
        for(j=0; j < valoresNumericos[2];j++){
            fwrite(&raiz->ch,sizeof(char),1,write_ptr);
        }
    }
    else
    {
        char aux;
        char* saidaCh;
        node* atual;
        atual = raiz;
        int countCaminho = 0;
        for(j=0; j < valoresNumericos[2];j++)
        {
            if(j % 8 == 0) {
                /*leu um byte;*/
                aux = texto[i];
                i++;
            }
            /*Contador de caminho permite ele ignorar o primeiro bit do
            endereco de cada char (o primeiro sempre sera 0);*/
            if(countCaminho != 0)
            {
                /*Leitura bit a bit, se foi 0 ele vai para a esquerda da arvore,
                se for 1 ele vai para a direita;*/
                if((aux&(1<<(j%8))) == 0)
                    atual = atual->esq;
                else
                    atual = atual->dir;
            }
            countCaminho++;
            /*Se chegou em uma folha / char;*/
            if(atual->esq == NULL)
            {
                fwrite(&atual->ch,sizeof(char),1,write_ptr);
                countCaminho = 0;
                atual = raiz;
            }
        }
    }
    fclose(arquivo);
    fclose(write_ptr);

    return 0;
}
