#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CPF_TAMANHO 12
#define MAX_SENHA_TAMANHO 7
#define ARQUIVO_USUARIOS "usuarios.txt"
#define MAX_USUARIOS 10

// Estrutura para armazenar dados do usuário
typedef struct {
    char cpf[MAX_CPF_TAMANHO];
    char senha[MAX_SENHA_TAMANHO];
    double saldo;
    double bitcoin;
    double ethereum;
    double ripple;
    int num_transacoes;
} Usuario;

Usuario usuarios[MAX_USUARIOS];
int num_usuarios = 0; // Contador de usuários

// Função para salvar usuários e saldos em um arquivo binário
void salvar_usuarios() {
    FILE *file = fopen(ARQUIVO_USUARIOS, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }
    fwrite(&num_usuarios, sizeof(int), 1, file);
    fwrite(usuarios, sizeof(Usuario), num_usuarios, file);
    fclose(file);
}

// Função para ler usuários e saldos do arquivo binário
void ler_usuarios() {
    FILE *file = fopen(ARQUIVO_USUARIOS, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }
    fread(&num_usuarios, sizeof(int), 1, file);
    fread(usuarios, sizeof(Usuario), num_usuarios, file);
    fclose(file);
}

// Função para registrar um novo usuário
void registrar() {
    if (num_usuarios >= MAX_USUARIOS) {
        printf("Número máximo de usuários atingido.\n");
        return;
    }
    
    char cpf[MAX_CPF_TAMANHO];
    char senha[MAX_SENHA_TAMANHO];
    printf("Informe seu CPF (somente números): ");
    scanf("%s", cpf);
    if (strlen(cpf) != 11) {
        printf("CPF inválido. Deve conter 11 números.\n");
        return;
    }
    printf("Informe sua senha (6 dígitos, somente números): ");
    scanf("%s", senha);
    if (strlen(senha) != 6) {
        printf("Senha inválida. Deve ter 6 dígitos.\n");
        return;
    }

    for (int i = 0; i < num_usuarios; i++) {
        if (strcmp(cpf, usuarios[i].cpf) == 0) {
            printf("CPF já registrado.\n");
            return;
        }
    }

    Usuario novo_usuario;
    strcpy(novo_usuario.cpf, cpf);
    strcpy(novo_usuario.senha, senha);
    novo_usuario.saldo = 0.0;
    novo_usuario.bitcoin = 0.0;
    novo_usuario.ethereum = 0.0;
    novo_usuario.ripple = 0.0;
    novo_usuario.num_transacoes = 0;

    usuarios[num_usuarios++] = novo_usuario;
    salvar_usuarios();
    printf("Usuário registrado com sucesso!\n");
}

// Função para verificar se o usuário existe e a senha está correta
int verificar_usuario(const char *cpf, const char *senha) {
    for (int i = 0; i < num_usuarios; i++) {
        if (strcmp(cpf, usuarios[i].cpf) == 0 && strcmp(senha, usuarios[i].senha) == 0) {
            return i;
        }
    }
    return -1;
}

// Função para exibir o menu principal
void menu_principal() {
    int opcao;
    do {
        printf("\n===================\n");
        printf("    Menu Principal   \n");
        printf("===================\n");
        printf("1. Registrar\n");
        printf("2. Login\n");
        printf("3. Sair\n");
        printf("===================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                registrar();
                break;
            case 2: {
                char cpf[MAX_CPF_TAMANHO];
                char senha[MAX_SENHA_TAMANHO];
                printf("Informe seu CPF: ");
                scanf("%s", cpf);
                printf("Informe sua senha: ");
                scanf("%s", senha);

                int index = verificar_usuario(cpf, senha);
                if (index != -1) {
                    printf("Login bem-sucedido! Bem-vindo, %s!\n", usuarios[index].cpf);
                } else {
                    printf("CPF ou senha incorretos.\n");
                }
                break;
            }
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 3);
}

int main() {
    ler_usuarios(); // Carrega usuários do arquivo
    menu_principal(); // Exibe menu principal
    return 0;
}