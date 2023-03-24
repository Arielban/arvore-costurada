#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef enum {NoEsquerdo, NoDireito, NoPai, NoRaiz} DIRECAO;

typedef struct {
    TIPOCHAVE chave;
} ITEM;

typedef struct estrutura {
    ITEM item;
    struct estrutura *esq;
    struct estrutura *dir;
    struct estrutura *pai;
    DIRECAO direcao;
    struct estrutura *suc; // ponteiro para o sucessor em ordem de percurso
    struct estrutura *pred; // ponteiro para o predecessor em ordem de percurso
} ARVORE_COSTURADA;

ARVORE_COSTURADA* encontraPredecessor(ARVORE_COSTURADA *no) {
    ARVORE_COSTURADA *atual = no->esq;
    while(atual->dir != NULL) {
        atual = atual->dir;
    }
    return atual;
}

ARVORE_COSTURADA* encontraSucessor(ARVORE_COSTURADA *no) {
    ARVORE_COSTURADA *atual = no->dir;
    while(atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

ARVORE_COSTURADA* criarNo(ITEM item) {
    ARVORE_COSTURADA *novo = (ARVORE_COSTURADA*) malloc(sizeof(ARVORE_COSTURADA));
    novo->item = item;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    novo->direcao = NoRaiz;
    novo->suc = NULL;
    novo->pred = NULL;
    return novo;
}

ARVORE_COSTURADA* insere(ARVORE_COSTURADA *raiz, ITEM item) {
    if(raiz == NULL) {
        return criarNo(item);
    } else if(item.chave < raiz->item.chave) {
        ARVORE_COSTURADA *esquerda = insere(raiz->esq, item);
        esquerda->pai = raiz;
        esquerda->direcao = NoEsquerdo;
        if(raiz->esq == NULL) { // costura com o predecessor
            raiz->esq = esquerda;
            esquerda->pred = encontraPredecessor(raiz);
        }
        return esquerda;
    } else {
        ARVORE_COSTURADA *direita = insere(raiz->dir, item);
        direita->pai = raiz;
        direita->direcao = NoDireito;
        if(raiz->dir == NULL) { // costura com o sucessor
            raiz->dir = direita;
            direita->suc = encontraSucessor(raiz);
        }
        return direita;
    }
}

void destruir(ARVORE_COSTURADA *raiz) {
    if(raiz != NULL) {
        destruir(raiz->esq);
        destruir(raiz->dir);
        free(raiz);
    }
}

void percorrerEmOrdem(ARVORE_COSTURADA *raiz) {
    if (raiz == NULL) {
        return;
    }

    percorrerEmOrdem(raiz->esq);
    printf("%d ", raiz->item.chave);
    percorrerEmOrdem(raiz->dir);
}



int main() {
    ARVORE_COSTURADA *raiz = NULL;
    int valor[5];

    for (int i = 0; i < 5; i++) {
        printf("Digite o valor a ser inserido na arvore: ");
        scanf("%d", &valor[i]);
        ITEM item;
        item.chave = valor[i];
        raiz = insere(raiz, item);
    }

    printf("\nValores armazenados na arvore em ordem: ");
    percorrerEmOrdem(raiz);
    printf("\n");

    destruir(raiz);
    return 0;
}