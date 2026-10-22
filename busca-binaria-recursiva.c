//Busca binária RECURSIVA: mesma ideia da versão iterativa, mas em vez de um laço a função chama a si mesma
//passando apenas a metade do vetor onde o valor ainda pode estar. O caso base é o intervalo vazio (inicio > limite).

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tam 10

//Retorna o índice do elemento ou -1 se ele não existir. Em *cont fica o número de passos (comparações com o meio).
int buscaBinaria(int vet[], int var, int inicio, int limite, int *cont)
{

    int meio;

    //caso base: intervalo vazio, o elemento não está no vetor
    if(inicio > limite)    return -1;

    (*cont)++;

    //equivale a (inicio + limite) / 2, mas não estoura o limite do int em vetores enormes
    meio = inicio + (limite - inicio) / 2;

    if(var == vet[meio])
    {

        return meio;

    }

    if(var < vet[meio])
    {

        return buscaBinaria(vet, var, inicio, meio - 1, cont);

    }

    else
    {

        return buscaBinaria(vet, var, meio + 1, limite, cont);

    }

}

void trocar(int *a, int *b)
{

    int copia = *a;
    *a = *b;
    *b = copia;

}

int particionar(int vet[], int inicio, int fim)
{
    int pivo = vet[fim], i = inicio;
    
    for(int j = inicio; j < fim; j++)
    {

        if(vet[j] <= pivo)
        {

            trocar(&vet[i], &vet[j]);
            i++;

        }

    }

    trocar(&vet[i], &vet[fim]);

    return i;
}

void quickSort(int vet[], int inicio, int fim)
{

    if(inicio < fim)
    {

        //Seleciona o último elemento, pivô, e posiciona-o no lugar correto com os números menores à esquerda e os maiores à direita.
        //Em seguida, particiona o vetor em dois "subvetores" e organiza seguindo o mesmo principio do pivô
        int meio = particionar(vet, inicio, fim);
        quickSort(vet, inicio, meio - 1);
        quickSort(vet, meio + 1, fim);

    }

}

void preencher(int vet[])
{

    for(int i = 0; i < tam; i++)
    {

        vet[i] = rand() % 100;

    }

}

void imprimir(int vet[])
{

    for(int i = 0; i < tam; i++)
    {

        printf("[%d] ", vet[i]);

    }

    printf("\n");

}

int main()
{

    int vet[tam], var, indice, cont = 0;

    srand(time(NULL));

    preencher(vet);
    printf("Original: ");
    imprimir(vet);

    //a busca binária só funciona em vetores ordenados
    quickSort(vet, 0, tam - 1);
    printf("Ordenado: ");
    imprimir(vet);

    printf("Digite um valor a ser encontrado: ");
    if(scanf("%d", &var) != 1)
    {

        printf("Entrada inválida!\n");
        return 1;

    }

    indice = buscaBinaria(vet, var, 0, tam - 1, &cont);

    if(indice >= 0)     printf("Elemento %d encontrado no índice %d após %d passo(s)!\n", var, indice, cont);
    else                printf("Elemento %d não encontrado após %d passo(s)!\n", var, cont);

    return 0;

}
