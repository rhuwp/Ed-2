// Estrutura programa Tabela Hash - Professor Lucas.
// Aluno: Rhuan Vinicius R. Martins
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO_TABELA 10
#define TAMANHO_NOME 100
#define TAMANHO_TELEFONE 20

// Estrutura para armazenar um contato
typedef struct Contato {
    char nome[TAMANHO_NOME];
    char telefone[TAMANHO_TELEFONE];
    struct Contato *proximo;
} Contato;

// Tabela hash
Contato *tabelaHash[TAMANHO_TABELA];

// Função hash simples
int funcaoHash(const char *nome) {
    int hash = 0;
    while (*nome) {
        hash = (hash * 31 + *nome) % TAMANHO_TABELA;
        nome++;
    }
    return hash;
}


void adicionarContato() {
    char nome[TAMANHO_NOME], telefone[TAMANHO_TELEFONE];
    printf("Nome: ");
    getchar();
    fgets(nome, TAMANHO_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Telefone: ");
    fgets(telefone, TAMANHO_TELEFONE, stdin);
    telefone[strcspn(telefone, "\n")] = '\0';

    int indice = funcaoHash(nome);
    Contato *atual = tabelaHash[indice];

    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            strcpy(atual->telefone, telefone);
            printf("Contato atualizado com sucesso.\n");
            return;
        }
        atual = atual->proximo;
    }

    Contato *novoContato = (Contato *)malloc(sizeof(Contato));
    if (!novoContato) {
        printf("Erro: Falha ao alocar memória.\n");
        return;
    }
    strcpy(novoContato->nome, nome);
    strcpy(novoContato->telefone, telefone);
    novoContato->proximo = tabelaHash[indice];
    tabelaHash[indice] = novoContato;

    printf("Contato adicionado com sucesso.\n");
}


void buscarContato() {
    char nome[TAMANHO_NOME];
    printf("Nome: ");
    getchar(); // Limpar buffer
    fgets(nome, TAMANHO_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int indice = funcaoHash(nome);
    Contato *atual = tabelaHash[indice];

    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Telefone de %s: %s\n", nome, atual->telefone);
            return;
        }
        atual = atual->proximo;
    }
    printf("Erro: Contato não encontrado.\n");
}


void removerContato() {
    char nome[TAMANHO_NOME];
    printf("Nome: ");
    getchar(); // Limpar buffer
    fgets(nome, TAMANHO_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove '\n'

    int indice = funcaoHash(nome);
    Contato *atual = tabelaHash[indice];
    Contato *anterior = NULL;

    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                tabelaHash[indice] = atual->proximo;
            }
            free(atual);
            printf("Contato removido com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Erro: Contato não encontrado.\n");
}


void exibirContatos() {
    printf("Lista de contatos:\n");
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Contato *atual = tabelaHash[i];
        while (atual) {
            printf("Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
            atual = atual->proximo;
        }
    }
}


void liberarTabela() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Contato *atual = tabelaHash[i];
        while (atual) {
            Contato *remover = atual;
            atual = atual->proximo;
            free(remover);
        }
        tabelaHash[i] = NULL;
    }
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int opcao;


    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabelaHash[i] = NULL;
    }

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarTabela();
    return 0;
}
