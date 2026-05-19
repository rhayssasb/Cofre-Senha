
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* ============================================================
 *  DEFINES E STRUCT
 * ============================================================ */

#define MAX_NOME        50
#define MAX_SENHA       100
#define MAX_CREDENCIAIS 100
#define SHIFT           3
#define ARQUIVO_COFRE   "cofre.txt"

typedef struct {
    char servico[MAX_NOME];        /* ex: gmail, instagram, banco */
    char usuario[MAX_NOME];        /* email ou nome de usuario    */
    char senha_cifrada[MAX_SENHA]; /* senha embaralhada com Cesar */
} Credencial;

/* ============================================================
 *  CIFRA DE CESAR - RECURSIVA
 *
 *  Percorre a string caractere a caractere.
 *  Caso base:    chegou no '\0' -> encerra.
 *  Caso recursivo: cifra/decifra o char atual, chama para i+1.
 *  Apenas letras sao rotacionadas; numeros e simbolos passam intactos.
 * ============================================================ */
void cifrar_recursivo(char *src, char *dst, int shift, int i) {
    if (src[i] == '\0') {               /* caso base: fim da string */
        dst[i] = '\0';
        return;
    }

    char c = src[i];
    if (isalpha((unsigned char)c)) {
        char base = islower((unsigned char)c) ? 'a' : 'A';
        dst[i] = (char)(base + (c - base + shift) % 26);
    } else {
        dst[i] = c;                     /* preserva nao-alfabeticos */
    }

    cifrar_recursivo(src, dst, shift, i + 1); /* caso recursivo */
}

void decifrar_recursivo(char *src, char *dst, int shift, int i) {
    if (src[i] == '\0') {               /* caso base */
        dst[i] = '\0';
        return;
    }

    char c = src[i];
    if (isalpha((unsigned char)c)) {
        char base = islower((unsigned char)c) ? 'a' : 'A';
        dst[i] = (char)(base + (c - base - shift + 26) % 26);
    } else {
        dst[i] = c;
    }

    decifrar_recursivo(src, dst, shift, i + 1); /* caso recursivo */
}

/* Wrappers que escondem o indice inicial */
void cifrar(char *texto, char *resultado, int shift) {
    cifrar_recursivo(texto, resultado, shift, 0);
}

void decifrar(char *texto, char *resultado, int shift) {
    decifrar_recursivo(texto, resultado, shift, 0);
}

/* ============================================================
 *  PERSISTENCIA - LEITURA E ESCRITA EM ARQUIVO
 * ============================================================ */
int carregar_cofre(Credencial *cofre, int *total) {
    FILE *f = fopen(ARQUIVO_COFRE, "r");
    *total = 0;

    if (f == NULL) {
        printf("[INFO] Arquivo '%s' nao encontrado. Cofre vazio criado.\n",
               ARQUIVO_COFRE);
        return 0;
    }

    char linha[MAX_NOME + MAX_NOME + MAX_SENHA + 3];
    while (*total < MAX_CREDENCIAIS && fgets(linha, sizeof(linha), f) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        if (strlen(linha) == 0) continue;

        /* formato do arquivo: servico;usuario;senha_cifrada */
        char *servico = strtok(linha, ";");
        char *usuario = strtok(NULL, ";");
        char *senha   = strtok(NULL, ";");

        if (servico && usuario && senha) {
            strncpy(cofre[*total].servico,        servico, MAX_NOME  - 1);
            strncpy(cofre[*total].usuario,        usuario, MAX_NOME  - 1);
            strncpy(cofre[*total].senha_cifrada,  senha,   MAX_SENHA - 1);
            cofre[*total].servico[MAX_NOME  - 1]       = '\0';
            cofre[*total].usuario[MAX_NOME  - 1]       = '\0';
            cofre[*total].senha_cifrada[MAX_SENHA - 1] = '\0';
            (*total)++;
        }
    }

    fclose(f);
    printf("[INFO] %d credencial(is) carregada(s) do cofre.\n", *total);
    return 1;
}

void salvar_cofre(Credencial *cofre, int total) {
    FILE *f = fopen(ARQUIVO_COFRE, "w");
    if (f == NULL) {
        printf("[ERRO] Nao foi possivel salvar o cofre!\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(f, "%s;%s;%s\n",
                cofre[i].servico,
                cofre[i].usuario,
                cofre[i].senha_cifrada);
    }

    fclose(f);
}

/* ============================================================
 *  OPERACOES DO MENU
 * ============================================================ */

static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void adicionar_credencial(Credencial *cofre, int *total) {
    if (*total >= MAX_CREDENCIAIS) {
        printf("[ERRO] Cofre cheio! Limite de %d credenciais atingido.\n",
               MAX_CREDENCIAIS);
        return;
    }

    Credencial nova;
    char senha_original[MAX_SENHA];

    printf("\n--- Adicionar Credencial ---\n");

    printf("Servico (ex: gmail, github): ");
    fgets(nova.servico, MAX_NOME, stdin);
    nova.servico[strcspn(nova.servico, "\n")] = '\0';

    printf("Usuario / E-mail: ");
    fgets(nova.usuario, MAX_NOME, stdin);
    nova.usuario[strcspn(nova.usuario, "\n")] = '\0';

    printf("Senha (sera cifrada antes de salvar): ");
    fgets(senha_original, MAX_SENHA, stdin);
    senha_original[strcspn(senha_original, "\n")] = '\0';

    /* Cifra a senha ANTES de guardar - nunca armazena em texto puro */
    cifrar(senha_original, nova.senha_cifrada, SHIFT);

    cofre[*total] = nova;
    (*total)++;

    salvar_cofre(cofre, *total);
    printf("[OK] Credencial adicionada! Senha armazenada cifrada.\n");
}

void listar_credenciais(Credencial *cofre, int total) {
    printf("\n--- Credenciais cadastradas (senhas cifradas) ---\n");

    if (total == 0) {
        printf("Nenhuma credencial no cofre.\n");
        return;
    }

    printf("%-4s  %-18s  %-24s  %s\n",
           "#", "Servico", "Usuario", "Senha (cifrada)");
    printf("%-4s  %-18s  %-24s  %s\n",
           "----", "------------------",
           "------------------------", "----------------------------");

    for (int i = 0; i < total; i++) {
        printf("%-4d  %-18s  %-24s  %s\n",
               i + 1,
               cofre[i].servico,
               cofre[i].usuario,
               cofre[i].senha_cifrada);
    }
}

void buscar_servico(Credencial *cofre, int total) {
    char busca[MAX_NOME];
    printf("\n--- Buscar por Servico ---\n");
    printf("Nome do servico: ");
    fgets(busca, MAX_NOME, stdin);
    busca[strcspn(busca, "\n")] = '\0';

    int encontrou = 0;
    for (int i = 0; i < total; i++) {
        if (strcasecmp(cofre[i].servico, busca) == 0) {
            printf("\n  Servico  : %s\n", cofre[i].servico);
            printf("  Usuario  : %s\n", cofre[i].usuario);
            printf("  Senha    : %s  [cifrada - use opcao 4 para ver a original]\n",
                   cofre[i].senha_cifrada);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Servico '%s' nao encontrado no cofre.\n", busca);
    }
}

void decifrar_credencial(Credencial *cofre, int total) {
    if (total == 0) {
        printf("Nenhuma credencial cadastrada.\n");
        return;
    }

    listar_credenciais(cofre, total);

    int escolha;
    printf("\nNumero da credencial para decifrar (0 = cancelar): ");
    scanf("%d", &escolha);
    limpar_buffer();

    if (escolha <= 0 || escolha > total) {
        printf("Operacao cancelada.\n");
        return;
    }

    char senha_decifrada[MAX_SENHA];
    decifrar(cofre[escolha - 1].senha_cifrada, senha_decifrada, SHIFT);

    printf("\n  Servico  : %s\n", cofre[escolha - 1].servico);
    printf("  Usuario  : %s\n",  cofre[escolha - 1].usuario);
    printf("  Senha    : %s  <<< SENHA ORIGINAL >>>\n", senha_decifrada);
}

void remover_credencial(Credencial *cofre, int *total) {
    if (*total == 0) {
        printf("Nenhuma credencial para remover.\n");
        return;
    }

    listar_credenciais(cofre, *total);

    int escolha;
    printf("\nNumero da credencial para remover (0 = cancelar): ");
    scanf("%d", &escolha);
    limpar_buffer();

    if (escolha <= 0 || escolha > *total) {
        printf("Operacao cancelada.\n");
        return;
    }

    printf("Removendo credencial: %s / %s\n",
           cofre[escolha - 1].servico,
           cofre[escolha - 1].usuario);

    /* Desloca os elementos para preencher o espaco removido */
    for (int i = escolha - 1; i < *total - 1; i++) {
        cofre[i] = cofre[i + 1];
    }
    (*total)--;

    salvar_cofre(cofre, *total);
    printf("[OK] Credencial removida!\n");
}

/* ============================================================
 *  MAIN - MENU PRINCIPAL
 * ============================================================ */
static void exibir_banner(void) {
    printf("\n");
    printf("  +==========================================+\n");
    printf("  |    COFRE DE SENHAS - Cifra de Cesar      |\n");
    printf("  |    PIF - Prof. Ronierison Maciel         |\n");
    printf("  +==========================================+\n");
}

static void exibir_menu(void) {
    printf("\n  +-----------------------------+\n");
    printf("  |      MENU PRINCIPAL         |\n");
    printf("  |-----------------------------|\n");
    printf("  |  1. Adicionar credencial    |\n");
    printf("  |  2. Listar (cifradas)       |\n");
    printf("  |  3. Buscar por servico      |\n");
    printf("  |  4. Decifrar credencial     |\n");
    printf("  |  5. Remover credencial      |\n");
    printf("  |  6. Salvar e sair           |\n");
    printf("  +-----------------------------+\n");
    printf("  Opcao: ");
}

int main(void) {
    /* Alocacao dinamica - malloc */
    Credencial *cofre = (Credencial *)malloc(MAX_CREDENCIAIS * sizeof(Credencial));
    if (cofre == NULL) {
        fprintf(stderr, "[ERRO FATAL] Falha ao alocar memoria.\n");
        return EXIT_FAILURE;
    }

    int total = 0;
    int opcao;

    exibir_banner();
    carregar_cofre(cofre, &total);

    do {
        exibir_menu();
        scanf("%d", &opcao);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcao) {
            case 1: adicionar_credencial(cofre, &total); break;
            case 2: listar_credenciais(cofre, total);    break;
            case 3: buscar_servico(cofre, total);        break;
            case 4: decifrar_credencial(cofre, total);   break;
            case 5: remover_credencial(cofre, &total);   break;
            case 6:
                salvar_cofre(cofre, total);
                printf("\n[OK] Cofre salvo. Encerrando... Ate logo!\n\n");
                break;
            default:
                printf("[AVISO] Opcao invalida! Digite um numero de 1 a 6.\n");
        }

    } while (opcao != 6);

    /* Libera a memoria alocada */
    free(cofre);
    return EXIT_SUCCESS;
}
