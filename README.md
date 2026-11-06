# Comparação entre Merge Sort e Quick Sort

## Sobre o projeto

Este projeto tem como objetivo comparar o desempenho dos algoritmos **Merge Sort** e **Quick Sort**, observando o tempo necessário para ordenar vetores de diferentes tamanhos e em diferentes condições de organização.

Os experimentos são realizados em C, e os resultados são registrados em um arquivo `.tsv`, que pode ser importado para o Google Planilhas para análise e criação de gráficos.

## Como os experimentos funcionam

### Tamanhos dos vetores

São utilizados cinco tamanhos diferentes:

- 100 elementos;
- 1.000 elementos;
- 10.000 elementos;
- 100.000 elementos;
- 1.000.000 de elementos.

### Tipos de vetores

Cada tamanho é testado em três condições:

- **Crescente:** elementos já organizados em ordem crescente.
- **Aleatório:** elementos em posições aleatórias.
- **Decrescente:** elementos organizados em ordem decrescente.

### Repetições

Cada combinação de tamanho e tipo de vetor é executada **30 vezes para cada algoritmo**.

Isso significa que os algoritmos são comparados nas mesmas condições, permitindo observar não apenas um resultado isolado, mas também as variações de desempenho entre as execuções.

Para cada repetição, os dois algoritmos recebem cópias do mesmo vetor original. Assim, ambos trabalham com os mesmos dados, garantindo uma comparação mais justa.

### Por que alternar a ordem dos algoritmos?

A ordem de execução é alternada entre as repetições:

| Repetição | Primeiro algoritmo | Segundo algoritmo |
|---|---|---|
| 1 | Merge Sort | Quick Sort |
| 2 | Quick Sort | Merge Sort |
| ... | ... | ... |

Essa alternância ajuda a reduzir possíveis interferências causadas pela ordem de execução.
Por exemplo, o primeiro algoritmo pode ser beneficiado ou prejudicado por condições momentâneas do computador, como cache, processos em segundo plano e variações de carga do sistema. Alternar a ordem ajuda a distribuir esses efeitos entre os dois algoritmos, tornando a comparação mais equilibrada.

## Registro dos resultados

Os tempos de execução são registrados em segundos em um arquivo chamado `resultados.tsv`.

O arquivo contém as seguintes colunas:

| Coluna | Descrição |
|---|---|
| Algoritmo | Merge Sort ou Quick Sort |
| Tamanho | Quantidade de elementos do vetor |
| Vetor | Tipo de organização dos dados |
| Repeticao | Número da repetição |
| Tempo (s) | Tempo de execução em segundos |

O arquivo é gerado automaticamente pelo programa. Para iniciar uma nova coleta de resultados, é necessário apagar ou renomear o arquivo anterior, pois o programa acrescenta novos registros ao arquivo existente.

## Importando os resultados para o Google Planilhas

Os tempos são registrados com **12 casas decimais**, pois algumas ordenações são concluídas em poucos microssegundos.

Por exemplo:

`0.000002199900`

Ao importar os dados, o Google Planilhas pode interpretar incorretamente o ponto decimal, dependendo da configuração regional, ou exibir os valores como zero por causa da formatação das células.

Para evitar esses problemas:

1. Importe o arquivo `.tsv`, selecionando a tabulação como separador de colunas, se necessário.
2. Crie uma nova coluna chamada Tempo (s) -PT-BR, mantendo a coluna original.
3. Na primeira linha de dados da nova coluna, insira a fórmula `=E2/10^12`, considerando que os tempos originais estão na coluna E.
4. Arraste a fórmula até a última linha preenchida.
5. Selecione toda a nova coluna `Tempo (s) -PT-BR`.
6. Acesse **Formatar → Números → Formato de número personalizado**.
7. Insira: `0,000000000000` e clique em aplicar.

Dessa forma, os valores serão convertidos para a notação decimal brasileira, com vírgula e 12 casas decimais, sem alterar os dados originais.

## Como compilar e executar

O projeto utiliza GCC para compilação.

Todos os arquivos `.c` devem ser compilados juntos, pois cada um contém parte da implementação do programa.

### Compilação

Abra o terminal na pasta do projeto e execute:

```bash
gcc -std=c99 -O2 main.c merge.c quick_sort.c tempo.c -o experimento
```

O parâmetro `-O2` ativa otimizações do compilador, enquanto `-o experimento` define o nome do executável gerado.

### Execução

**Windows:**

```bash
experimento.exe
```

**Linux:**

```bash
./experimento
```

Após a execução, o programa registrará os resultados no arquivo `resultados.tsv`.

## Observações importantes

- Evite executar outros programas pesados durante os experimentos, para reduzir interferências nas medições.
- Mantenha as condições de execução o mais consistentes possível entre as coletas.
- Não altere os dados de entrada de apenas um dos algoritmos: ambos devem receber cópias idênticas do vetor original em cada repetição.
- O arquivo `.tsv` contém os resultados experimentais e pode ser regenerado a qualquer momento executando o programa novamente.
