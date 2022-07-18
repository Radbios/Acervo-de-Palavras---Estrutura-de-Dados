#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct noArvore{
    char cod;
    struct noArvore *dir;
    struct noArvore *prox;
} no;

// --- INIT ARVORE ---
void initArvore(no *pNovo){
	pNovo->cod = '#';
	pNovo->prox  = NULL;
	pNovo->dir  = NULL;
}

// --- ADICIONAR E ORDENAR PALAVRAS NA ÁRVORE N-ÁRIA ---
no *insertLetter(no *pNovo, char palavra[], int tamanho, int *indice){
    // --- SE NAO PERCORREU TODA A PALAVRA ---
    if(*indice < tamanho){
        if(pNovo->cod == '#'){
            pNovo->cod = palavra[*indice];
            // --- INICIALIZAR A DIREITA ---
            no *direita = (no*)malloc(sizeof(no));
            direita->cod = '#';
            direita->dir = NULL;
            direita->prox = NULL;

            pNovo->dir = direita;

            // --- INICIALIZAR O PRÓXIMO ---
            no *proximo = (no*)malloc(sizeof(no));
            proximo->cod = '#';
            proximo->dir = NULL;
            proximo->prox = NULL;

            pNovo->prox = proximo;

        }

        // --- PROCURAR O CARACTERE DA PALAVRA NO GRAFO ---
        if(pNovo->cod != palavra[*indice]){
            // --- SE NAO ACHAR, PROCURAR À ESQUERDA ---
            pNovo->dir = insertLetter(pNovo->dir, palavra, tamanho, indice);
        }
        else if(pNovo->cod == palavra[*indice]){
            // --- SE ACHAR, IR PARA A PRÓXIMA LETRA ---
            *indice = *indice + 1;
            pNovo->prox = insertLetter(pNovo->prox, palavra, tamanho, indice);
        }


    }
    // --- SE PERCORREU TODA A PALAVRA --- 
    if(pNovo->cod == '#'){
        // --- INDICAR O FIM DELA ---
        pNovo->cod = '!';
        // --- INICIALIZAR A DIREITA ---
        no *direita = (no*)malloc(sizeof(no));
        direita->cod = '#';
        direita->dir = NULL;
        direita->prox = NULL;
        pNovo->dir = direita;
    }
    return pNovo;
}

// --- PEGAR AS PALAVRAS NO TXT ---
void getLetter(no *pNovo){
    FILE *dicionario;
    dicionario  = fopen("palavras.txt", "r");
    // --- ENQUANTO NAO FOR O FIM DO ARQUIVO, ADICIONAR ELAS NA ÁRVORE ---
    while(!feof(dicionario)){
        char palavra[15];
        int tamanho, i;
        int *indice = (int *)malloc(sizeof(int));
        *indice = 0;
        fscanf(dicionario, "%s", palavra);

        tamanho = strlen(palavra);
        // --- INSERIR APENAS PALAVRAS QUE TENHAM MAIS DE 3 CARACTERES ---
        if(tamanho > 3){
            pNovo = insertLetter(pNovo, palavra, tamanho, indice);
        }
    }
    fclose(dicionario);
}

int main(){
    no *three = (no *)malloc(sizeof(no));
    initArvore(three);
    getLetter(three);
    
    return 0;
}