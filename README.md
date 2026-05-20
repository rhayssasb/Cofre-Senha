# 🔐 Cofre de Senhas com Cifra de César

<p align="center">
  Projeto desenvolvido em <b>Linguagem C</b> para a disciplina de <b>Programação Imperativa e Funcional</b>.
</p>

---

## 📚 Conceitos Aplicados

Durante o desenvolvimento do projeto, foram utilizados os seguintes conceitos fundamentais da linguagem C:

* ✅ `struct`
* ✅ Manipulação de arquivos com `fopen` e `fclose`
* ✅ Recursividade
* ✅ Alocação dinâmica (`malloc` e `free`)
* ✅ Manipulação de strings
* ✅ Persistência de dados
* ✅ Estruturas de repetição e `switch-case`

---

# 🎓 Informações Acadêmicas

| Informação        | Detalhe                            |
| ----------------- | ---------------------------------- |
| **Disciplina**    | Programação Imperativa e Funcional |
| **Professor**     | Ronierison Maciel                  |
| **Tema Sorteado** | Tema 1                             |
| **Ano**           | 2026                               |

---

# 👥 Integrantes

* Guilherme
* Karollyne
* Lisa
* Maria Clara
* Rhayssa

---

# 📋 Sobre o Projeto

O projeto consiste em um **gerenciador de senhas via terminal**, desenvolvido em linguagem C, capaz de armazenar credenciais de diferentes serviços, como:

* Gmail
* Instagram
* Bancos
* Redes sociais
* Plataformas digitais

As senhas são protegidas utilizando a técnica da **Cifra de César**, impedindo que sejam armazenadas em texto puro no arquivo.

---

# 🔒 Cifra Utilizada

O deslocamento da cifra é definido pela constante:

```c
#define SHIFT 3
```

Exemplo de funcionamento:

```txt
abc → def
```

Cada letra é deslocada 3 posições no alfabeto.

---

# 💾 Exemplo do Arquivo `cofre.txt`

As informações ficam armazenadas da seguinte forma:

```txt
gmail;usuario@email.com;Khoor#Pxqgr
banco;cpf123;Vhqkd@Vhjxud99
```

Mesmo abrindo o arquivo manualmente, o usuário verá apenas as versões cifradas das senhas.

---

# 🗂️ Estrutura do Projeto

```txt
Cofre-Senha/
│
├── cofre_senha.c   -> Programa principal
├── cofre.txt       -> Banco de dados das credenciais
├── README.md       -> Documentação do projeto
└── .vscode/        -> Configurações do editor
```

---

# ⚙️ Como Compilar

## ▶️ Compilação com GCC

```bash
gcc -std=c11 -Wall -Wextra -pedantic cofre_senha.c -o cofre_senha
```

---

# ▶️ Como Executar

## Linux / macOS

```bash
./cofre_senha
```

## Windows

```bash
cofre_senha.exe
```

---

# 🖥️ Exemplo de Uso

```txt
╔══════════════════════════════════════════╗
║      COFRE DE SENHAS - Cifra de César   ║
╚══════════════════════════════════════════╝

[INFO] 3 credencial(is) carregada(s) do cofre.

┌─────────────────────────────┐
│       MENU PRINCIPAL        │
├─────────────────────────────┤
│ 1. Adicionar credencial     │
│ 2. Listar (cifradas)        │
│ 3. Buscar por serviço       │
│ 4. Decifrar credencial      │
│ 5. Remover credencial       │
│ 6. Salvar e sair            │
└─────────────────────────────┘
```

---

# ✅ Requisitos Obrigatórios Atendidos

| Requisito            | Implementação                            |
| -------------------- | ---------------------------------------- |
| ✅ `struct`           | Uso da struct `Credencial`               |
| ✅ `fopen` / `fclose` | Leitura e escrita no arquivo `cofre.txt` |
| ✅ `switch-case`      | Menu principal interativo                |
| ✅ Recursividade      | Funções de cifra e decifra               |
| ✅ Persistência       | Salvamento e carregamento automático     |
| ✅ Alocação dinâmica  | Uso de `malloc` e `free`                 |

---

# 🔁 Como a Recursão Funciona

A cifra percorre a string caractere por caractere utilizando recursividade.

```c
void cifrar_recursivo(char *src, char *dst, int shift, int i) {
    if (src[i] == '\0') {
        dst[i] = '\0';
        return;
    }

    char c = src[i];

    if (isalpha((unsigned char)c)) {
        char base = islower((unsigned char)c) ? 'a' : 'A';

        dst[i] = (char)(base + (c - base + shift) % 26);
    } else {
        dst[i] = c;
    }

    cifrar_recursivo(src, dst, shift, i + 1);
}
```

---

# 📌 Exemplo da Recursão

Entrada:

```txt
abc
```

Com:

```c
SHIFT = 3
```

Saída:

```txt
def
```

Funcionamento:

* `a → d`
* `b → e`
* `c → f`

A função encerra quando encontra:

```c
'\0'
```

Que representa o final da string.

---

# 🎨 Decisões de Design

### 📌 Uso da Struct

A `struct Credencial` organiza:

* serviço
* usuário
* senha cifrada

Facilitando a manipulação dos dados.

---

### 📌 Uso da Recursão

A recursão foi escolhida por combinar naturalmente com o processamento de strings caractere por caractere.

---

### 📌 Salvamento Automático

As alterações são salvas automaticamente para evitar perda de dados.

---

### 📌 Uso de Alocação Dinâmica

A utilização de `malloc` e `free` permite um gerenciamento mais flexível da memória.

---

# 🚀 Tecnologias Utilizadas

* Linguagem C
* GCC
* Manipulação de arquivos
* Terminal / CLI
* Estruturas de dados básicas

---

# 📄 Licença

Projeto acadêmico desenvolvido exclusivamente para fins educacionais.
