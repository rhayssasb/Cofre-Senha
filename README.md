# 🔐 Cofre de Senhas com Cifra de César

Projeto desenvolvido para a disciplina de **Programação Imperativa e Funcional**, utilizando linguagem C e conceitos fundamentais como:

- Structs
- Arquivos (`fopen` / `fclose`)
- Recursividade
- Modularização
- Alocação dinâmica
- Manipulação de strings

---

## 📚 Informações Acadêmicas

- **Disciplina:** Programação Imperativa e Funcional  
- **Professor:** Ronierison Maciel  
- **Tema Sorteado:** Tema 1  
- **Ano:** 2026  

---

## 👥 Integrantes

- Guilherme
- Karollyne
- Lisa
- Maria Clara
- Rhayssa

---

## 📋 Descrição do Projeto

O projeto consiste em um **gerenciador de senhas via terminal**, capaz de armazenar credenciais de diferentes serviços, como:

- Gmail
- Instagram
- Bancos
- Redes sociais
- Plataformas digitais

As senhas são protegidas utilizando a técnica da **Cifra de César**, com deslocamento definido pela constante:

```c
#define SHIFT 3
```

Isso significa que as senhas **não ficam salvas em texto puro** no arquivo `cofre.txt`.

---

## 🔒 Exemplo de Senhas Cifradas

Exemplo de como as informações ficam armazenadas no arquivo:

```txt
gmail;usuario@email.com;Khoor#Pxqgr
banco;cpf123;Vhqkd@Vhjxud99
```

Mesmo abrindo o arquivo manualmente, o usuário verá apenas as versões cifradas das senhas.

## 🖥️ Exemplo de Uso

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

| Requisito | Implementação |
|---|---|
| Struct | Uso da struct `Credencial` |
| fopen / fclose | Leitura e escrita no `cofre.txt` |
| Switch-case | Menu principal interativo |
| Recursividade | Funções de cifra e decifra |
| Modularização | Separação em `.h` e `.c` |
| Sem warnings | Compilação com `-Wall -Wextra` |
| malloc/free (bônus) | Alocação dinâmica do cofre |

---

# 🔁 Como a Recursão Funciona

A cifra percorre a string caractere por caractere utilizando recursividade.

```c
void cifrar_recursivo(char *src, char *dst, int shift, int i) {
    if (src[i] == '\0') {
        dst[i] = '\0';
        return;
    }

    char base = islower(src[i]) ? 'a' : 'A';

    dst[i] = base + (src[i] - base + shift) % 26;

    cifrar_recursivo(src, dst, shift, i + 1);
}
```

---

## 📌 Exemplo

Com:

```txt
abc
```

E:

```c
SHIFT = 3
```

O resultado será:

```txt
def
```

Funcionamento:

- `a → d`
- `b → e`
- `c → f`

A função encerra quando encontra:

```c
'\0'
```

Que representa o final da string.

---

# 🎨 Decisões de Design

## 📌 Uso da Struct

A struct `Credencial` organiza:

- serviço
- usuário
- senha cifrada

Facilitando o armazenamento e manipulação das credenciais.

---

## 📌 Uso da Recursão

A recursão foi escolhida por combinar naturalmente com o processamento de strings caractere por caractere.

---

## 📌 Salvamento Automático

As alterações são salvas imediatamente para evitar perda de dados em caso de falha no programa.

---

## 📌 Uso de malloc/free

A alocação dinâmica permite maior flexibilidade e demonstra o gerenciamento correto de memória em C.

---

# 🚀 Tecnologias Utilizadas

- Linguagem C
- GCC
- Makefile
- Manipulação de arquivos
- Terminal / CLI

---

# 📄 Licença

Projeto acadêmico desenvolvido exclusivamente para fins educacionais.
