#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncad.c"

int main()
{
    /*Leitura do arquivo a ser compactado;*/
    printf("Digite o nome do arquivo que deseja compactar:\n");
    char nomeArq[100];
    scanf("%s", nomeArq);

    char caminho[] = "C:/temp/";
    strcat(caminho, nomeArq);

    int i;

    system("cls");

    printf("\nLeitura do arquivo situado em %s:\n", caminho);


    FILE* arquivo = fopen(caminho, "rb");
    FILE* lengthFile = fopen(caminho, "r");

    if (arquivo == NULL) {
        printf("File Not Found!\n");
        return -1;
    }
    /*Obtendo o tamanho do arquivo;*/
    fseek(lengthFile, 0L, SEEK_END);

    long int tamanhoArq = ftell(lengthFile);

    /*Constroi uma string contendo o texto do arquivo e a tabela de frequencias*/
    char texto[tamanhoArq];
    int tabelaDeFrequencia[256] = {0};

    for(i = 0; i < 256; i++)
    { tabelaDeFrequencia[i] = 0; }

     for( i = 0; i < tamanhoArq; i++){
        texto[i] = fgetc(arquivo);
        tabelaDeFrequencia[texto[i]]++;
    }


    /*Cria a lista*/
    Lista* li = cria_lista();
    for(i = 0; i < 256; i++){
        if(tabelaDeFrequencia[i] > 0)
        {
            node* nodeChar = newNode(i,tabelaDeFrequencia[i],NULL,NULL);
            insere_lista_ordenada(li,nodeChar);
        }
    }
    /*Transforma a lista em uma arvore*/
    juntarNos(li);
    node *raiz = (*li)->nodeChar;

    /*Constroi uma tabela contendo os enderecos de cada char*/
    char* codChar[256][256];
    char caminhoCh[256] = {'0'};
    preencherTabela(raiz,caminhoCh, codChar);

    /*Imprime a arvore*/
    int altura = Altura(raiz);
    printArvore(raiz,altura);

    /*Gera a string da arvore para leitura no descompactador*/
    char* arvoreComprimida[511];
    int contador = 0;
    getArvoreComprimida(raiz, arvoreComprimida,&contador);

    /*Comeca o processo de escrita do arquivo compactado*/
    FILE *write_ptr;
    unsigned char buffer[contador];
    for(i=0; i < contador; i++)
        buffer[i] = arvoreComprimida[i];

    system("cls");
    /*Pede o nome do arquivo final e gera o endereco de saida*/
    printf("Digite o nome do arquivo compactado [Sem extencoes]:\n");
    char nomeArqOut[100];
    scanf("%s", nomeArqOut);

    char caminhoOut[] = "C:/temp/";
    char extencaoOut[] = ".mali";
    strcat(caminhoOut, nomeArqOut);
    strcat(caminhoOut, extencaoOut);

    write_ptr = fopen(caminhoOut,"wb");
    printf("Caminho: %s\n", caminho);

    /*Escreve o caminho e a string da arvore*/
    fwrite(caminho,sizeof(caminho) + sizeof(strlen(nomeArq)),1,write_ptr);
    fwrite(buffer,contador,1,write_ptr);

    char aux = 0;
    int tamConv = 0;
    int j;
    printf("---------------------------\n");
    printf("Tamanho: %d\n", tamanhoArq);

    /*Convertendo os chars em seus enderecos;*/
    for(i=0;i<tamanhoArq;i++)
    {
        /*Percorre char a char ("bit a bit") o endereco do caracter lido*/
        for(j=0;j<strlen(*codChar[texto[i]]);j++)
        {
            if((*codChar[texto[i]])[j] == '1'){
               /*Se o codigo do char for 1 ele adiciona 1 bit contendo True*/
                aux = aux|(1<<(tamConv % 8));
            }
            tamConv++;
                /*Terminou de ocupar 1 byte, escreve ele e reseta*/
            if(tamConv%8 == 0)
            {
                fwrite(&aux, 1, 1, write_ptr);
                aux = 0;
            }
        }
    }
    fwrite(&aux, 1, 1, write_ptr);
    /*A ultima coisa do arquivo compactado sao 3 valores int
    [Tamanho do caminho, Tamanho da string da arvore, numero de bits do texto compactado]*/
    int valoresNumericos[3] = {sizeof(caminho) + sizeof(strlen(nomeArq)),contador,tamConv};
    fwrite(valoresNumericos,sizeof(int)*3,1,write_ptr);

    libera_lista(li);
    fclose(arquivo);
    return 0;
}
