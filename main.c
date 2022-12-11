// Integrantes da equipe: Matheus Macedo Gomes (20211045050330) e João Vitor Abreu Castro (20211045050446)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int* lista;
    int tamanho;
    int capacidade;
}MinHeap;

int elementoPai(int);
int filhoEsquerdo(int);
int filhoDireito(int);
int menorElemento(MinHeap*);
MinHeap* iniciarMinHeap(int);
MinHeap* inserir(MinHeap*, int);
MinHeap* organizar(MinHeap*, int);
MinHeap* removerMinimo(MinHeap*);
MinHeap* deletarElemento(MinHeap*, int);
void printarMinHeap(MinHeap*);
void liberarMinHeap(MinHeap*);
void ordenarLista(MinHeap*);

int main() {
    MinHeap* heap = iniciarMinHeap(10);

    puts("MIN HEAP GENERATOR");
    puts("Insira seus números");

    int lista[8];
    
    for(int i = 0; i <= 6; i++){
        scanf("%d", &lista[i]);
    }

    for(int i = 0; i <= 6; i++) {
        inserir(heap, lista[i]);
    }
    
    printarMinHeap(heap);
    
    ordenarLista(heap);
    
    liberarMinHeap(heap);
    
    return 0;
}

int elementoPai(int i) {
    return (i - 1) / 2;
}

int filhoEsquerdo(int i) {
    return (2*i + 1);
}

int filhoDireito(int i) {
    return (2*i + 2);
}

int menorElemento(MinHeap* heap) {
    return heap->lista[0];
}

MinHeap* iniciarMinHeap(int capacidade) {
    MinHeap* minHeap = (MinHeap*) calloc (1, sizeof(MinHeap));
    minHeap->lista = (int*) calloc (capacidade, sizeof(int));
    minHeap->capacidade = capacidade;
    minHeap->tamanho = 0;
    return minHeap;
}

MinHeap* inserir(MinHeap* heap, int elemento) {
    if (heap->tamanho == heap->capacidade) {
        fprintf(stderr, "Não é possível mais inserir, o minheap está cheio.\n");
        return heap;
    }
    heap->tamanho++;
    heap->lista[heap->tamanho - 1] = elemento;

    int atual = heap->tamanho - 1;

    while (atual > 0 && heap->lista[elementoPai(atual)] > heap->lista[atual]) {
        int aux = heap->lista[elementoPai(atual)];
        heap->lista[elementoPai(atual)] = heap->lista[atual];
        heap->lista[atual] = aux;
        atual = elementoPai(atual);
    }
    return heap; 
}

MinHeap* organizar(MinHeap* heap, int posicao) {
    if (heap->tamanho <= 1){
        return heap;
    }
    
    int esquerdo = filhoEsquerdo(posicao); 
    int direito = filhoDireito(posicao); 
    int menor = posicao; 
    
    if (esquerdo < heap->tamanho && heap->lista[esquerdo] < heap->lista[posicao]) {
        menor = esquerdo; 
    }
    if (direito < heap->tamanho && heap->lista[direito] < heap->lista[menor]) {
        menor = direito; 
    }
    if (menor != posicao) { 
        int aux = heap->lista[posicao];
        heap->lista[posicao] = heap->lista[menor];
        heap->lista[menor] = aux;
        heap = organizar(heap, menor); 
    }

    return heap;
}

MinHeap* removerMinimo(MinHeap* heap) {
    if (!heap || heap->tamanho == 0){
        return heap;
    }
    
    int tamanho = heap->tamanho;
    int ultimoElemento = heap->lista[tamanho-1];

    heap->lista[0] = ultimoElemento;

    heap->tamanho--;
    tamanho--;

    heap = organizar(heap, 0);
    return heap;
}

MinHeap* deletarElemento(MinHeap* heap, int posicao) {
    heap->lista[posicao] = menorElemento(heap) - 1;
    int atual = posicao;
    
    while (atual > 0 && heap->lista[elementoPai(atual)] > heap->lista[atual]) {
        int aux = heap->lista[elementoPai(atual)];
        heap->lista[elementoPai(atual)] = heap->lista[atual];
        heap->lista[atual] = aux;
        atual = elementoPai(atual);
    }

    heap = removerMinimo(heap);
    return heap;
}

void printarMinHeap(MinHeap* heap) {
    printf("Min Heap:\n");
    for (int i=0; i<heap->tamanho; i++) {
        printf("%d -> ", heap->lista[i]);
    }
    printf("\n");
}

void liberarMinHeap(MinHeap* heap) {
    if (!heap){
        return;
    }
    free(heap->lista);
    free(heap);
}

void ordenarLista(MinHeap* heap) {
    int listaOrdenada[7];
    int menor_numero;
    
    for(int i = 0; i <= 6; i++){
        menor_numero = menorElemento(heap);
        listaOrdenada[i] = menor_numero;
        removerMinimo(heap);
    }

    puts("Lista ordenada: ");
    for(int i = 0; i <= 6; i++){
        printf("%d ", listaOrdenada[i]);
    }
}