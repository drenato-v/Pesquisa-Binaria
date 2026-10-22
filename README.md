# Algoritmos de Busca em C

Implementações em C da **busca binária**, em versão iterativa e recursiva, feitas durante um curso da Udemy. Cada programa gera um vetor de inteiros aleatórios, ordena com Quick Sort, pede um valor ao usuário e informa em qual índice ele está e quantos passos foram necessários.

| Arquivo | Algoritmo | Controle |
|---|---|---|
| [`busca-binaria-iterativa.c`](busca-binaria-iterativa.c) | Busca binária | Laço `while` |
| [`busca-binaria-recursiva.c`](busca-binaria-recursiva.c) | Busca binária | Recursão |

---

## Sumário

1. [O que é busca](#o-que-é-busca)
2. [Como compilar e executar](#como-compilar-e-executar)
3. [Busca binária](#busca-binária)
4. [Versão iterativa](#versão-iterativa)
5. [Versão recursiva](#versão-recursiva)
6. [Iterativa × recursiva](#iterativa--recursiva)
7. [Busca binária × busca linear](#busca-binária--busca-linear)
8. [Correções realizadas](#correções-realizadas)

---

## O que é busca

**Definição.** Um algoritmo de busca recebe uma coleção de *n* elementos `⟨a₀, a₁, …, aₙ₋₁⟩` e um valor-alvo *x* e retorna um índice *i* tal que `aᵢ = x`, ou um indicador de ausência (neste projeto, `-1`) quando nenhum elemento é igual a *x*.

**Desenvolvimento.** A estratégia mais simples é a **busca linear (sequencial)**: comparar *x* com cada elemento, do primeiro ao último. Ela funciona em qualquer vetor, mas no pior caso faz *n* comparações, ou seja, O(n).

Quando o vetor está **ordenado**, dá para fazer muito melhor. Cada comparação diz não só "é ou não é", mas também "está antes ou depois". Assim, metade dos candidatos é descartada de uma vez. Essa é a ideia da busca binária.

**Exemplo.** Procurar um nome numa lista de chamada fora de ordem obriga a ler nome por nome (busca linear). Num dicionário, você abre no meio, vê se a palavra vem antes ou depois e descarta metade do livro (busca binária).

---

## Como compilar e executar

É preciso ter um compilador C (`gcc` ou `clang`; no macOS, `xcode-select --install`).

```bash
gcc -Wall busca-binaria-iterativa.c -o busca-iterativa
./busca-iterativa
```

Saída de exemplo (o vetor muda a cada execução):

```
Original: [17] [93] [57] [6] [82] [69] [47] [56] [34] [72]
Ordenado: [6] [17] [34] [47] [56] [57] [69] [72] [82] [93]
Digite um valor a ser encontrado: 47
Elemento 47 encontrado no índice 3 após 4 passo(s)!
```

Se o valor não estiver no vetor:

```
Digite um valor a ser encontrado: 50
Elemento 50 não encontrado após 4 passo(s)!
```

O tamanho do vetor é a constante `tam` (`#define tam 10`). Os dois programas têm a mesma estrutura:

| Função | Papel |
|---|---|
| `preencher(vet)` | Preenche o vetor com valores aleatórios de 0 a 99 |
| `imprimir(vet)` | Mostra o vetor na tela |
| `quickSort(vet, inicio, fim)` | Ordena o vetor, que é pré-requisito da busca binária (veja o projeto *Algoritmos de ordenação*) |
| `buscaBinaria(vet, var, inicio, limite, &cont)` | Retorna o índice de `var` ou `-1`; grava em `cont` o número de passos |
| `main()` | Chama `srand(time(NULL))`, preenche, ordena, lê o valor e mostra o resultado |

---

## Busca binária

### Definição
A busca binária (*binary search*) é um algoritmo de busca em **vetores ordenados** que, a cada passo, compara o valor-alvo *x* com o elemento central do intervalo `[inicio, limite]`. Se forem iguais, a busca termina; se *x* for menor, o intervalo passa a ser `[inicio, meio − 1]`; se for maior, `[meio + 1, limite]`. O processo repete até encontrar *x* ou até o intervalo ficar vazio (`inicio > limite`).

### Desenvolvimento

**Pré-requisito: ordenação.** O algoritmo depende do vetor estar ordenado. Num vetor desordenado, ele pode dizer que um elemento presente "não foi encontrado". Por isso os dois programas chamam `quickSort` antes da busca.

**Por que é O(log n).** Cada passo divide o tamanho do intervalo por 2: *n → n/2 → n/4 → … → 1*. O número de divisões até sobrar um elemento é log₂ *n*. O número máximo de passos é **⌊log₂ n⌋ + 1**:

| Tamanho do vetor (*n*) | Máximo de passos (binária) | Máximo de passos (linear) |
|---|---|---|
| 10 | 4 | 10 |
| 1.000 | 10 | 1.000 |
| 1.000.000 | 20 | 1.000.000 |
| 1.000.000.000 | 30 | 1.000.000.000 |

Multiplicar o tamanho por 1.000 acrescenta só cerca de 10 passos.

**Complexidade:**
- **Tempo:** melhor caso O(1) (o alvo está no meio), médio e pior caso O(log n)
- **Espaço:** O(1) na versão iterativa; O(log n) na recursiva (pilha de chamadas)

**Cálculo do meio sem overflow.** O código usa:

```c
meio = inicio + (limite - inicio) / 2;
```

em vez de `(inicio + limite) / 2`. As duas dão o mesmo resultado, mas a soma `inicio + limite` pode passar do maior valor de um `int` (≈ 2,1 bilhões) em vetores muito grandes, e aí o índice fica negativo. Esse erro ficou famoso em 2006, quando foi encontrado na busca binária da biblioteca padrão do Java, que tinha passado anos sem ser notado.

**Valores repetidos.** Como os números são aleatórios entre 0 e 99, o vetor pode ter valores repetidos. Nesse caso a busca retorna o índice de **uma** das ocorrências, não necessariamente a primeira. Para achar sempre a primeira, uma variação continua buscando à esquerda depois de encontrar o valor.

### Exemplo
Vetor ordenado (índices em cima):

```
índice:  0   1   2   3   4   5   6   7   8   9
valor:  [6] [17][34][47][56][57][69][72][82][93]
```

**Buscando 69:**

| Passo | inicio | limite | meio | vet[meio] | Decisão |
|---|---|---|---|---|---|
| 1 | 0 | 9 | 4 | 56 | 69 > 56 → `inicio = 5` |
| 2 | 5 | 9 | 7 | 72 | 69 < 72 → `limite = 6` |
| 3 | 5 | 6 | 5 | 57 | 69 > 57 → `inicio = 6` |
| 4 | 6 | 6 | 6 | 69 | **encontrado no índice 6** |

**Buscando 50 (ausente):**

| Passo | inicio | limite | meio | vet[meio] | Decisão |
|---|---|---|---|---|---|
| 1 | 0 | 9 | 4 | 56 | 50 < 56 → `limite = 3` |
| 2 | 0 | 3 | 1 | 17 | 50 > 17 → `inicio = 2` |
| 3 | 2 | 3 | 2 | 34 | 50 > 34 → `inicio = 3` |
| 4 | 3 | 3 | 3 | 47 | 50 > 47 → `inicio = 4` |
| — | 4 | 3 | — | — | `inicio > limite` → **não encontrado (−1)** |

---

## Versão iterativa

### Definição
Na versão iterativa, um único laço `while (inicio <= limite)` atualiza as variáveis `inicio` e `limite` a cada passo. Todo o estado da busca fica em variáveis locais da própria função.

### Desenvolvimento
É a forma mais usada na prática: gasta memória constante, O(1), e não tem custo de chamadas de função. A condição do laço é exatamente "o intervalo ainda não está vazio".

Trecho de `busca-binaria-iterativa.c`:

```c
while(inicio <= limite) {
    (*cont)++;
    meio = inicio + (limite - inicio) / 2;

    if(var == vet[meio])  return meio;
    if(var <  vet[meio])  limite = meio - 1;   // descarta a metade direita
    else                  inicio = meio + 1;   // descarta a metade esquerda
}
return -1;
```

### Exemplo
Para buscar 69 no vetor acima, o laço roda 4 vezes. As variáveis evoluem exatamente como na primeira tabela: `(0,9) → (5,9) → (5,6) → (6,6)`.

---

## Versão recursiva

### Definição
Na versão recursiva, a função resolve o problema chamando a si mesma sobre a metade do vetor onde o valor ainda pode estar. O **caso base** é o intervalo vazio (`inicio > limite`, retorna `-1`) ou o elemento encontrado no meio (retorna `meio`).

### Desenvolvimento
A recursão espelha a definição matemática do algoritmo: "buscar em *n* elementos = comparar com o meio + buscar em *n/2* elementos". A recorrência é T(n) = T(n/2) + O(1), que resolve para O(log n).

Cada chamada ocupa um espaço na pilha, então o uso de memória é O(log n). Para 1 bilhão de elementos isso dá só cerca de 30 chamadas, sem risco de estouro. Como a chamada recursiva é a última coisa que a função faz (**recursão de cauda**), compiladores como o `gcc` com `-O2` costumam transformá-la num laço, igual à versão iterativa.

O contador de passos é passado por **ponteiro** (`int *cont`), porque cada chamada tem suas próprias variáveis locais. Com um `int` comum, a contagem se perderia a cada retorno.

Trecho de `busca-binaria-recursiva.c`:

```c
if(inicio > limite)    return -1;          // caso base: não encontrado

(*cont)++;
meio = inicio + (limite - inicio) / 2;

if(var == vet[meio])   return meio;        // caso base: encontrado
if(var <  vet[meio])   return buscaBinaria(vet, var, inicio, meio - 1, cont);
else                   return buscaBinaria(vet, var, meio + 1, limite, cont);
```

### Exemplo
Pilha de chamadas ao buscar 69:

```
buscaBinaria(vet, 69, 0, 9)   meio=4 (56)  → vai para a direita
└─ buscaBinaria(vet, 69, 5, 9)   meio=7 (72)  → vai para a esquerda
   └─ buscaBinaria(vet, 69, 5, 6)   meio=5 (57)  → vai para a direita
      └─ buscaBinaria(vet, 69, 6, 6)   meio=6 (69)  → retorna 6
      ← 6
   ← 6
← 6
```

---

## Iterativa × recursiva

| Critério | Iterativa | Recursiva |
|---|---|---|
| Tempo | O(log n) | O(log n) |
| Memória extra | O(1) | O(log n) (pilha) |
| Custo por passo | Só o laço | Uma chamada de função |
| Legibilidade | Direta | Mais próxima da definição matemática |
| Uso típico | Produção | Ensino; base para algoritmos de divisão e conquista |

As duas fazem **exatamente as mesmas comparações** e retornam o mesmo índice.

---

## Busca binária × busca linear

| Critério | Linear | Binária |
|---|---|---|
| Exige vetor ordenado | Não | Sim |
| Tempo (pior caso) | O(n) | O(log n) |
| Funciona em lista encadeada | Sim | Não de forma eficiente (precisa de acesso direto ao meio) |

Ordenar custa O(n log n). Para **uma única** busca, ordenar e depois fazer busca binária sai mais caro que uma busca linear direta. A busca binária compensa quando o vetor já está ordenado ou quando serão feitas **muitas** buscas no mesmo vetor.

---

## Correções realizadas

| Arquivo | Problema | Correção |
|---|---|---|
| Ambos | `(inicio + limite) / 2` pode estourar o `int` em vetores muito grandes | `inicio + (limite - inicio) / 2` |
| Ambos | `rand()` sem `srand()`: o mesmo vetor a cada execução | `srand(time(NULL))` no início da `main` |
| Ambos | `scanf` sem verificação: digitar letras deixava `var` com lixo | Verifica o retorno e mostra "Entrada inválida!" |
| Ambos | Funções `s` (preenchia **e** imprimia) e `print` com nomes pouco claros | Renomeadas para `preencher()` e `imprimir()`; a saída mostra "Original:" e "Ordenado:" |
| `busca-binaria-iterativa.c` | A função imprimia a mensagem por conta própria e o índice retornado era ignorado; a variável `bin` não era usada | A função só retorna o índice e conta os passos via `int *cont`, como a recursiva; a `main` mostra o índice |
| `busca-binaria-recursiva.c` | Mensagens sem `\n` e sem o número de passos no caso "não encontrado"; indentação desalinhada | Mensagens padronizadas com as da versão iterativa; indentação corrigida |

Os dois arquivos compilam sem avisos com `gcc -Wall -Wextra` e foram testados buscando todos os valores de 0 a 99: cada valor presente foi encontrado no índice correto e cada valor ausente retornou "não encontrado".

---

## Referências

- CORMEN, T. H. et al. *Algoritmos: Teoria e Prática*. 3ª ed. Rio de Janeiro: Elsevier, 2012.
- KNUTH, D. E. *The Art of Computer Programming, Vol. 3: Sorting and Searching*. 2ª ed. Addison-Wesley, 1998.
- BLOCH, J. *Extra, Extra – Read All About It: Nearly All Binary Searches and Mergesorts are Broken*. Google Research Blog, 2006.
