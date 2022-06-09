#include <stdio.h>
#include <stdlib.h>


typedef struct nodo{
    int numero;
    float valor;
    int altura;
    struct nodo *esq;
    struct nodo *dir;
} AVL;

AVL **iniciar();
int altura_nodo(AVL* No);
int fatorBalanceamento(AVL** No);
int maior(int x, int y);
void RotacaoLL(AVL** raiz);
void RotacaoRR(AVL** raiz);
void RotacaoLR(AVL** raiz);
void RotacaoRL(AVL** raiz);
int insere_nodo(AVL **raiz, int numero, float valor);
int remove_nodo(AVL **raiz, int numero);
void imprimeAVL(AVL *raiz, int aux);
AVL* ordenaRmv(AVL *existente);
void busca(AVL** raiz, int numero);

int main (){

    AVL** raiz = iniciar();
    int Arvore, numero, nodos=0;
    float valor;
    int count=0;
    do{
    printf("\n\n-----[ Menu ]-----\n");
    printf("1. Inserir elemento\n");
    printf("2. Buscar elemento\n");
    printf("3. Remover elemento:\n");
    printf("4. Imprimir arvore\n");
    printf("5. Imprimir altura da arvore:\n");
    printf("6. Imprimir quantidade de elementos:\n");
    printf("0. Sair\n");
    scanf("%d", &count);
    setbuf(stdin, NULL);   

        switch (count){
    case 1:
        printf("\nInsira o codigo do item:");
        scanf("%d", &numero);
        printf("\nInsira a valor do item:");
        scanf("%f", &valor);
        Arvore = insere_nodo(raiz, numero, valor);
        nodos++;
        break;
    case 2:
        printf("\nPor favor, insira o codigo que deseja buscar:\n");
        scanf("%d", &numero);
        busca(raiz,numero);
        break;
    case 3:
        printf("\nPor favor, insira o codigo que deseja excluir:\n");
        scanf("%d", &numero);
        Arvore = remove_nodo(raiz,numero);
        nodos--;
        break;
    case 4:
        printf("\n\n------------------------\n");
        imprimeAVL(*raiz,0);
        printf("\n------------------------\n");
        break;
    case 5: 
        numero = altura_nodo(*raiz) + 1;
        printf("\n A altura da arvore: %d ", numero);
        break;
    case 6: 
        printf("\n A quantidade de integrantes da arvore: %d ", nodos);
        break;
    default:
        break;
    }
    }while(count==1||count==2||count==3||count==4||count==5||count==6);
    return 0;
}

AVL **iniciar() {
    AVL **raiz =  (AVL**)malloc(sizeof(AVL*));
    if(!raiz) {
        printf("Nao foi possivel alocar memoria");
        exit(1);
    }
    *raiz = NULL;
    return raiz;
}

int altura_nodo(AVL* No){
    if(No == NULL){
        return -1;
    }else{
        return No->altura;
    }
}

int fatorBalanceamento(AVL** No){
    return labs(altura_nodo((*No)->esq) - altura_nodo((*No)->dir)); 
}

int maior(int x, int y){
    if(x>y){
        return x;
    }else{
        return y;
    }
}

void RotacaoLL(AVL** raiz){
    AVL *No;
    No = (*raiz)->esq;        
    (*raiz)->esq = No->dir;    
    No->dir = (*raiz);         
    (*raiz)->altura = maior(altura_nodo((*raiz)->esq),altura_nodo((*raiz)->dir))+1;
    No->altura = maior(altura_nodo(No->esq),altura_nodo((*raiz)))+1;
    (*raiz) = No;
}

void RotacaoRR(AVL** raiz){
    AVL *No;
    No = (*raiz)->dir;
    (*raiz)->dir = No->esq;
    No->esq = (*raiz);
    (*raiz)->altura = maior(altura_nodo((*raiz)->esq),altura_nodo((*raiz)->dir))+1;
    No->altura = maior(altura_nodo(No->dir),altura_nodo((*raiz)))+1;
    (*raiz) = No;
}

void RotacaoLR(AVL** raiz ){
    RotacaoRR(&(*raiz)->esq);
    RotacaoLL(&(*raiz));
}

void RotacaoRL(AVL** raiz ){
    RotacaoLL(&(*raiz)->dir);
    RotacaoRR(&(*raiz));
}

int insere_nodo(AVL** raiz, int numero, float valor){
    int res; 
    if((*raiz) == NULL){
        AVL *No;
        No = (AVL*)malloc(sizeof(AVL));
        if(No == NULL){
            return 0;
        }
        No->numero = numero;
        No->valor = valor;
        No->altura = 0;
        No->esq = NULL;
        No->dir = NULL;
        *raiz = No;
        return 1;
         }else{
            if(numero < (*raiz)->numero){
                if((res=insere_nodo(&(*raiz)->esq, numero, valor))==1){
                    if(fatorBalanceamento(&(*raiz)) >= 2){
                        if(numero < (*raiz)->esq->numero){
                            RotacaoLL(&(*raiz));
                        }else{
                            RotacaoLR(&(*raiz));
                        }
                    }
                }
            }else{
                if(numero > (*raiz)->numero){
                    if((res=insere_nodo(&(*raiz)->dir, numero, valor))==1){
                        if(fatorBalanceamento(&(*raiz)) >= 2){
                            if((*raiz)->dir->numero < numero) {
                                RotacaoRR(&(*raiz));
                            }else{
                                RotacaoRL(&(*raiz));
                            }
                        }
                    }
                }else{
                    printf("O mesmo numero nao pode existir duas vezes!\n");
                    return 0;
                }
            }
            (*raiz)->altura = maior(altura_nodo((*raiz)->esq),altura_nodo((*raiz)->dir))+1;
            return res;
        }
        return 0;
}

void imprimeAVL(AVL *raiz, int aux) {
    int i;
    if (raiz==NULL){
        return;
    }
    aux += 1;
    imprimeAVL(raiz->dir, aux);
    for (i = 0; i < aux; i++){
        printf("\t");
    }
    printf("%d\n", raiz->numero);
    imprimeAVL(raiz->esq, aux);
    return;
}

int remove_nodo(AVL **raiz, int numero){
    if(*raiz==NULL){
        printf("\nCodigo nao existe!\n");
        return 0;
    }
    int res;
    if(numero<(*raiz)->numero){
        if((res=remove_nodo(&(*raiz)->esq, numero))==1){
            if(fatorBalanceamento(&(*raiz)) >= 2){
                if(altura_nodo((*raiz)->dir->esq) <= altura_nodo((*raiz)->dir->dir)){
                    RotacaoRR(&(*raiz));
                }else{
                    RotacaoRL(&(*raiz));
                }
            }
        }
    }
    if(numero>(*raiz)->numero){
        if((res=remove_nodo(&(*raiz)->dir, numero))==1){
            if(fatorBalanceamento(&(*raiz)) >= 2){
                if(altura_nodo((*raiz)->esq->dir) <= altura_nodo((*raiz)->esq->esq)){
                    RotacaoRR(&(*raiz));
                }else{
                    RotacaoRL(&(*raiz));
                }
            }
        }
    }
    if((*raiz)->numero == numero){
        if((*raiz)->esq==NULL || (*raiz)->dir == NULL){
            AVL* antigo = (*raiz);
            if((*raiz)->esq != NULL){
                *raiz = (*raiz)->esq;
            }else{ 
                *raiz = (*raiz)->dir;
            }
            free(antigo);
        }else{
            AVL* aux = ordenaRmv((*raiz)->dir);
            (*raiz)->numero = aux->numero;
            remove_nodo(&(*raiz)->dir, (*raiz)->numero);
            if(fatorBalanceamento(&(*raiz)) >= 2){
                if(altura_nodo((*raiz)->esq->dir) <= altura_nodo((*raiz)->esq->esq)){
                    RotacaoLL(&(*raiz));
                }else{
                    RotacaoLR(&(*raiz));
                }
            }
        }
        return 1;
    }
    return res;
}

AVL* ordenaRmv(AVL *existente){
    AVL* superior = existente;
    AVL* inferior = existente->esq;
    while(inferior != NULL){
        superior = inferior;
        inferior = inferior->esq;
    }
    return superior;
}

void busca(AVL** raiz, int numero){
    if(*raiz==NULL){
        printf("\nA arvore esta vazia!\n");
        return;
    }
    if(numero<(*raiz)->numero){
        busca(&(*raiz)->esq, numero);
        return;
    }
    if(numero>(*raiz)->numero){
        busca(&(*raiz)->dir, numero);
        return;
    }
    if(numero==(*raiz)->numero){
        printf("\n\nCodigo do item: %d", numero);
        printf("\nValor do item: %.1f", (*raiz)->valor);
        return;
    }
}