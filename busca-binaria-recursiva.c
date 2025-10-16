#include <stdio.h>
#include <stdlib.h>
#define tam 10

int buscaBinaria(int vet[], int var, int inicio, int limite, int *cont)
{

    int meio;

    if(inicio > limite)    return -1;
    
        (*cont)++;
        meio = (inicio + limite) / 2;

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

    int vet[tam], var, bin, cont = 0;
    
    s(vet);
    quickSort(vet, 0, tam - 1);
    print(vet);

    printf("Digite um valor a ser encontrado: ");
    scanf("%d", &var);
    
    bin = buscaBinaria(vet, var, 0, tam - 1, &cont);

    if(bin >= 0)     printf("O elemento foi encontrado no indice %d após %d", bin, cont);
    else    printf("\nElemento não encontrado!"); 

    return 0;

}