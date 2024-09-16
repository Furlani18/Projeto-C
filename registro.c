#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int registrar(){
    char cpf[12];
    char senha[7];

    printf("Digite seu cpf: ");
    scanf("%s", cpf);

    printf("Crie uma senha de 6 digitos: ");
    scanf("%s", senha);

    if(senha != strlen(senha))

    FILE *fp = fopen("dados.txt", "a");
        fprintf(fp, "\n%s:%s", cpf, senha);
    fclose(fp);
    return;
}

int main(void){
    int opcao;
    do{
        printf("\nMenu Inicial: \n1. Registrar \n2. Login \n3. Sair \nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao){
        case 1: 
            registrar();
            break;
        case 2: 
            //login();
            break;
        case 3: 
            break;
        default:
            printf("\nOpcao invalida.");
            break;
        }
    }while (opcao != 3);

    printf("\nSaindo...");

    return 0;
}
