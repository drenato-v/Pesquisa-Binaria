#include <stdio.h>
#include <stdlib.h>
#define tam 10

int buscaBinaria(int vet[], int var, int inicio, int limite)
{

   int contador = 0, meio;

    while(inicio <= limite)
    {

        contador++;
        meio = (inicio +limite) / 2;

        if(var == vet[meio])
        {

            printf("Elemento %d foi encontrado após %d passos!\n", var, contador);
            return meio;
            
        }   
        
        if(var < vet[meio])
        {

            limite = meio - 1;

        }

        else
        {

            inicio = meio + 1;

        }

    }

    printf("Elemento %d não encontrado após %d passos!\n", var, contador);
    return -1;

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

        //Seleciona o último elemento, pivô, e o posiciona-o no lugar correto com os números menores à esquerda e os maiores à direita.
        //Em seguida, particiona o vetor em dois "subvetores" e organiza seguindo o mesmo principio do pivô
        int meio = particionar(vet, inicio, fim);
        quickSort(vet, inicio, meio - 1);
        quickSort(vet, meio + 1, fim);

    }

}

void s(int vet[])
{

    for(int i = 0; i < tam; i++)
    {

        vet[i] = rand() % 100;
        printf("[%d] ", vet[i]);

    }

    printf("\n");

}

void print(int vet[])
{

    for(int i = 0; i < tam; i++)
    {

        printf("[%d] ", vet[i]);

    }

    printf("\n");

}

int main()
{

    int vet[tam], var, bin;
    
    s(vet);
    quickSort(vet, 0, tam - 1);
    print(vet);

    printf("Digite um valor a ser encontrado: ");
    scanf("%d", &var);
    
    buscaBinaria(vet, var, 0, tam - 1);
    

    return 0;

}