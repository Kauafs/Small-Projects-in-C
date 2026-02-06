#include <stdlib.h>
#include <stdio.h>
#include "menu.h"
#include "utils.h"
#include "credentials.h"

void exibirCabecalho(){
    printf("=========================\n| Gerenciador de senhas |\n=========================\n");
}

int menu(){
    int choice = 0;
    int retr;
    while (choice != 7)
    {
        printf("(1) - Adicionar Credenciais\n(2) - Listar Crendenciais\n(3) - Buscar Credenciais\n(4) - Editar Credenciais\n(5) - RemoverCredenciais\n(6) - Exportar\n(7) - Sair\n(>):");
        retr = scanf(" %d", &choice);
        clearBuffer();
        if (retr == 0)
        {
            printf("Entrada Invalida\n");
            continue;
        }
        
        switch (choice)
        {
        case 1:
            printf("Adicionar\n");
            if (adicionarCredenciais() == 0){
                printf("[*] Limite de Cadastro Atingido!\n");
            }
            break;
        case 2:
            printf("Listar|\n");
            menuListar();
            break;
        case 3:
            printf("Buscar\n");
            buscarCadastro();
            break;
        case 4:
            printf("Editar\n");
            editarCredenciais();
            break;
        case 5:
            printf("Remover\n");
            removerCredenciais();
            break;
        case 6:
            printf("Exportar\n");
            if (exportarCredenciais() == 1)
            {
                printf("[+] Exportado com sucesso\n");
            } else
                printf("[-] Erro ao exportar\n");
            break;
        case 7:
            printf("Sair\n");
            break;
        default:
            printf("Nao existe essa opcao\n");
            break;
        }
    }
}
