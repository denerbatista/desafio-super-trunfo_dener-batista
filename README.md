# 🃏 Super Trunfo em C

Implementação em linguagem **C** do jogo **Super Trunfo de Países**, em três níveis de dificuldade (Novato, Aventureiro e Mestre), conforme enunciado do trabalho acadêmico.

## 🚀 Como compilar e executar

Certifique-se de ter um compilador C instalado (como o **gcc**).

No Linux/MacOS:
```bash
gcc super_trunfo.c -o super_trunfo
./super_trunfo
```
No Windows (usando MinGW ou similar):
```bash
gcc super_trunfo.c -o super_trunfo.exe
super_trunfo.exe
```
O jogo será iniciado no terminal, exibindo as opções e aguardando sua jogada.

## 📌 Funcionalidades

- Cadastro de **2 cartas** com os seguintes atributos:
  - Estado (A–H)
  - Código da carta (ex: A01)
  - Nome da cidade
  - População (habitantes)
  - Área (km²)
  - PIB
  - Número de pontos turísticos
- Cálculo automático de:
  - **Densidade populacional**  
  - **PIB per capita**  
  - **Super Poder** (população + área + PIB + pontos turísticos + PIB per capita + 1/densidade)
- Comparação dos atributos entre as cartas:
  - Regra: **maior vence**, exceto **densidade** (onde **menor vence**).
- Impressão dos resultados em formato claro (1 = Carta 1 venceu, 0 = Carta 2 venceu).

---

## 📂 Estrutura do Projeto

```
super-trunfo-c/
├─ super_trunfo.c   # código principal em C
└─ README.md        # este arquivo
```

---

## ⚙️ Compilação e Execução

### Compilar
```bash
gcc -std=c99 -Wall -Wextra -O2 -o super_trunfo super_trunfo.c
```

### Executar
```bash
./super_trunfo
```

---

## 🖥️ Exemplo de Uso

Entrada simulada:
```
=== Cadastro da Carta 1 ===
Estado (A-H): A
Codigo da carta (ex: A01): A01
Nome da cidade: Cidade X
Populacao (habitantes): 1000000
Area (km^2): 500
PIB: 2000000000
Numero de pontos turisticos: 10

=== Cadastro da Carta 2 ===
Estado (A-H): B
Codigo da carta (ex: A01): B01
Nome da cidade: Cidade Y
Populacao (habitantes): 2000000
Area (km^2): 1000
PIB: 5000000000
Numero de pontos turisticos: 15
```

Saída (resumida):
```
Carta 1:
Estado: A
Codigo: A01
Nome da Cidade: Cidade X
Populacao: 1000000
Area: 500.00 km^2
PIB: 2000000000.00
Numero de Pontos Turisticos: 10
Densidade Populacional: 2000.00 hab/km^2
PIB per Capita: 2000.00

Carta 2:
...

Super Poder Carta 1: 2000205010.50
Super Poder Carta 2: 5000201515.50

=== Comparacao de Cartas (1 = Carta 1 venceu; 0 = Carta 2 venceu) ===
Populacao: 0
Area: 0
PIB: 0
Pontos Turisticos: 0
Densidade Populacional (menor vence): 0
PIB per Capita: 0
Super Poder: 0
```

---

## 📖 Regras de Comparação

- **População** → maior vence  
- **Área** → maior vence  
- **PIB** → maior vence  
- **Pontos turísticos** → maior vence  
- **Densidade populacional** → **menor vence**  
- **PIB per capita** → maior vence  
- **Super Poder** → maior vence  

---

## 📝 Licença

Este projeto está sob a licença MIT — sinta-se livre para usar, modificar e compartilhar.  
