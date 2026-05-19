# 🔐 Cofre de Senhas com Cifra de César

**Disciplina:** Programação Imperativa e Funcional  
**Professor:** Ronierison Maciel  
**Tema sorteado:** Tema 1  
**Data:** 2026

---

## 👥 Integrantes

| Nome Completo | Matrícula |
|---|---|
| [Nome do integrante 1] | [Matrícula] |
| [Nome do integrante 2] | [Matrícula] |
| [Nome do integrante 3] | [Matrícula] |

---

## 📋 Descrição do Projeto

Gerenciador de senhas de linha de comando que armazena credenciais de diversos serviços (Gmail, Instagram, banco, etc.) com proteção via **Cifra de César** com deslocamento configurável pelo `#define SHIFT`.

As senhas **nunca são armazenadas em texto puro** no arquivo `cofre.txt`. Ao abrir o arquivo em qualquer editor de texto, as senhas aparecem embaralhadas. A senha original só é exibida quando o usuário escolhe explicitamente a opção "Decifrar".

Exemplo de como o cofre.txt é salvo:
```
gmail;usuario@email.com;Khoor#Pxqgr
banco;cpf123;Vhqkd@Vhjxud99
```

---

## 🗂️ Estrutura do Projeto

```
cofre-senhas/
├── main.c        # Menu principal (loop + switch-case)
├── cofre.c       # Implementação de todas as funções
├── cofre.h       # Header: structs, #defines, protótipos
├── Makefile      # Compilação automatizada
├── cofre.txt     # Banco de dados das credenciais (gerado em runtime)
├── .gitignore
└── README.md
```

---

## ⚙️ Como Compilar

### Com Make (recomendado)
```bash
make
```

### Manualmente com GCC
```bash
gcc -Wall -Wextra -g -o cofre main.c cofre.c
```

---

## ▶️ Como Executar

```bash
./cofre
```

---

## 🖥️ Exemplo de Uso

```
  ╔══════════════════════════════════════════╗
  ║       COFRE DE SENHAS - Cifra de Cesar   ║
  ╚══════════════════════════════════════════╝
[INFO] 3 credencial(is) carregada(s) do cofre.

  ┌─────────────────────────────┐
  │        MENU PRINCIPAL       │
  ├─────────────────────────────┤
  │  1. Adicionar credencial    │
  │  2. Listar (cifradas)       │
  │  3. Buscar por servico      │
  │  4. Decifrar credencial     │
  │  5. Remover credencial      │
  │  6. Salvar e sair           │
  └─────────────────────────────┘
```

**Adicionando uma senha:**
```
Opcao: 1
Servico: gmail
Usuario / E-mail: joao@gmail.com
Senha (sera cifrada antes de salvar): MinhaS3nh@
[OK] Credencial adicionada! Senha armazenada cifrada.
```

**Decifrando:**
```
Opcao: 4
[... lista as credenciais com senhas cifradas ...]
Numero da credencial para decifrar: 1
  Servico  : gmail
  Usuario  : joao@gmail.com
  Senha    : MinhaS3nh@  <<< SENHA ORIGINAL >>>
```

---

## ✅ Requisitos Obrigatórios Atendidos

| Requisito | Como foi implementado | Arquivo / Linha |
|---|---|---|
| **struct** | `typedef struct { char servico[]; ... } Credencial` definida em `.h` | `cofre.h`, linha 16 |
| **fopen/fclose** | `carregar_cofre()` lê com `"r"` e `salvar_cofre()` escreve com `"w"` | `cofre.c`, linhas 55 e 79 |
| **switch-case** | Menu principal com 6 opções dentro de loop `do-while` | `main.c`, linha 48 |
| **Função recursiva** | `cifrar_recursivo()` e `decifrar_recursivo()` — processam string char a char | `cofre.c`, linhas 28 e 47 |
| **Modularização** | `cofre.h` com `#ifndef`, `#define`, protótipos + `cofre.c` com implementação | `cofre.h` e `cofre.c` |
| **Compila sem warnings** | `gcc -Wall -Wextra -g` — zero warnings | Makefile |
| **malloc/free (bônus)** | `malloc(MAX_CREDENCIAIS * sizeof(Credencial))` no início, `free()` ao sair | `main.c`, linhas 28 e 68 |

---

## 🔁 Como a Recursão Funciona

```c
void cifrar_recursivo(char *src, char *dst, int shift, int i) {
    if (src[i] == '\0') {       // CASO BASE: fim da string
        dst[i] = '\0';
        return;
    }
    // Cifra o caractere atual
    char base = islower(src[i]) ? 'a' : 'A';
    dst[i] = base + (src[i] - base + shift) % 26;

    cifrar_recursivo(src, dst, shift, i + 1); // CASO RECURSIVO
}
```

A função avança índice a índice pela string. Para "abc" com SHIFT=3:
- `i=0` → 'a' vira 'd'
- `i=1` → 'b' vira 'e'  
- `i=2` → 'c' vira 'f'
- `i=3` → `'\0'` → caso base, encerra

---

## 😓 Dificuldades e Como Foram Superadas

- **Overflow no wrap do alfabeto**: ao cifrar 'z' com SHIFT=3, precisávamos voltar para 'c'. Resolvido com `(c - base + shift) % 26`.
- **Buffer sujo após scanf**: misturar `scanf` com `fgets` causava leituras vazias. Resolvido limpando o buffer com um `while (getchar() != '\n')`.
- **Formato do arquivo com strtok**: `strtok` modifica a string original; copiamos para um buffer temporário antes de usar.

---

## 🎨 Decisões de Design

- **Por que essa struct?** Os três campos (`servico`, `usuario`, `senha_cifrada`) representam exatamente o que um gerenciador de senhas precisa: onde usar, com qual login, e qual senha.
- **Por que recursão na cifra?** É a aplicação mais natural — processar uma string caractere a caractere é um problema que se reduz a si mesmo a cada passo.
- **Por que salvar após cada alteração?** Evita perda de dados se o programa travar; o arquivo sempre reflete o estado atual.
- **Por que malloc?** Permite que o limite `MAX_CREDENCIAIS` seja ajustado facilmente, e demonstra o uso correto de alocação dinâmica com `free` ao encerrar.

---

## 🔗 Repositório

[https://github.com/SEU_USUARIO/pif-tema-01-grupoNN](https://github.com/SEU_USUARIO/pif-tema-01-grupoNN)
