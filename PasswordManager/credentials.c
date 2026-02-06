#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "credentials.h"
#include "utils.h"
#include "crypto.h"


struct cadastro {
    int id;
    char nameService[128];
    char nameUser[128];
    char passCipher[128];
    char observation[128];
} cad[4];

int totalCadastro = 0;
int contId = 0;

#define FILEEX "file.dat"

int adicionarCredenciais(){
    if (totalCadastro >= 4)
        return 0;

    cad[totalCadastro].id = contId;
    printf("Entre com o nome do servico\n(>):\t");
    fgets(cad[totalCadastro].nameService, sizeof(cad[totalCadastro].nameService), stdin);
    clearCaracter(cad[totalCadastro].nameService);
    printf("Entre com o nome do usuario\n(>):\t");
    fgets(cad[totalCadastro].nameUser, sizeof(cad[totalCadastro].nameUser), stdin);
    clearCaracter(cad[totalCadastro].nameUser);
    printf("Entre com a senha do usuario\n(>):\t");
    fgets(cad[totalCadastro].passCipher, sizeof(cad[totalCadastro].passCipher), stdin);
    clearCaracter(cad[totalCadastro].passCipher);
    printf("Entre com a alguma observacao do usuario\n(>):\t");
    fgets(cad[totalCadastro].observation, sizeof(cad[totalCadastro].observation), stdin);
    clearCaracter(cad[totalCadastro].observation);
    
    crypto(cad[totalCadastro].passCipher);

    contId++;
    
    totalCadastro++;

    printf("[+] Cadastrado com sucesso\n");

    return 1;

}

int listarCredenciais(){
    
    for (int i = 0; i < totalCadastro; i++)
    {
        printf("|ID:\t%d\n",cad[i].id);
        printf("|Nome Servico:\t%s\n", cad[i].nameService);
        printf("|Nome Usuario:\t%s\n", cad[i].nameUser);
        printf("|Password:\t%s\n", cad[i].passCipher);
        printf("|Observacoes:\t%s\n", cad[i].observation);
        printf("---------------------------------------------------\n");
    }

    return totalCadastro;
}

int listarResumido(){
    for (int  j = 0; j < totalCadastro; j++)
    {
        printf("|Nome Servico:\t%s\n", cad[j].nameService);
        printf("|Nome Usuario:\t%s\n", cad[j].nameUser);
        printf("-----------------------------------------------\n");
    }

    return totalCadastro;
}

int listarDetalhes(){
    for (int i = 0; i < totalCadastro; i++)
    {
        printf("|Nome:\t%s\n",cad[i].nameUser);
        printf("|Detalhes:\t%s\n",cad[i].observation);
        printf("----------------------------------------------------\n");
    }
    
    return totalCadastro;
}

int buscarCadastro(){
    char nameService[128];
    char copy[128];
    char opc;
    int len;
    
    printf("Informe o nome do servico:\t");
    fgets(nameService, sizeof(nameService), stdin);
    clearCaracter(nameService);

    len = strlen(nameService);

    for (int i = 0; i < totalCadastro; i++)
    {
        if (strncmp(nameService, cad[i].nameService, len) == 0)
        {
            printf("|%s de %s\n",cad[i].nameService, cad[i].nameUser);
            printf("Deseja ver a senha?\n(Y) or (y) - Sim\n(N) or (n) - Nao\n(>):\t");
            opc = getchar();
            clearBuffer();

            strcpy(copy, cad[i].passCipher);

            if (opc == 'Y' || opc == 'y')
            {
                decrypt(copy);
                printf("[+] Senha descriptografada:\t%s\n",copy);
            } else
                printf("[-] Saindo...\n");
        } 
    }
}

int editarCredenciais(){
    int usr, chc;
    int i, maxBuff;
    char newName[128];

    printf("O que deseja alterar ?\n1 - (Nome)\n2 - (Senha)\n3 - (Observacao)\n(>):\t");
    scanf(" %d",&usr);
    clearBuffer();

    printf("Lista de Credenciais\n");
    menuListar();

    printf("Entre com o ID que quer alterar\n(>):\t");
    scanf(" %d", &chc);

    clearBuffer();

    if (usr == 1)
    {
        printf("Alterar nome\n");
        printf("Entre com o novo nome\n(>)\t");
        fgets(newName, sizeof(newName), stdin);
        clearCaracter(newName);
        changeAny(newName, cad[chc].nameUser, sizeof(cad[chc].nameUser));
    }

    if (usr == 2)
    {
        printf("Alterar Senha\n");
        printf("Entre com o nova senha\n(>)\t");
        fgets(newName, sizeof(newName), stdin);
        clearCaracter(newName);
        changeAny(newName, cad[chc].passCipher, sizeof(cad[chc].passCipher));
        crypto(cad[chc].passCipher);
    }
    
    if (usr == 3)
    {
        printf("Alterar Descricao\n");
        printf("Entre com o nova descricao\n(>)\t");
        fgets(newName, sizeof(newName), stdin);
        clearCaracter(newName);
        changeAny(newName, cad[chc].observation, sizeof(cad[chc].observation));
    }
}

void removerCredenciais(){
    int rusr;
    menuListar();

    printf("Informe o ID que deseja remover\n");
    scanf(" %d",&rusr);

    clearBuffer();
    
    if (rusr < 0 || rusr >= totalCadastro){
        printf("Nao existe esse ID\n");
        return;
    }

    for (int i = rusr; i < totalCadastro - 1; i++)
    {

        cad[i].id = cad[i+1].id;
        strcpy(cad[i].nameService,cad[i+1].nameService);
        strcpy(cad[i].nameUser,cad[i+1].nameUser);
        strcpy(cad[i].passCipher,cad[i+1].passCipher);
        strcpy(cad[i].observation,cad[i+1].observation);
    }
    totalCadastro--;
}

int exportarCredenciais(){
 
    FILE *writeFile;

    writeFile = fopen(FILEEX, "ab");
    if (writeFile == NULL)
    {
        return 0;
    }
    
    fwrite(cad, sizeof(struct cadastro),4,writeFile);
    
    fclose(writeFile);
    
    return 1;


}

void menuListar(){
    char ent;
    printf("(A) or (a) - Lista Completa\n(R) or (r) Lista Resumida\n(D) or (d) - Detalhes\n(>):\t");
    ent = getchar();
    clearBuffer();
    if (ent == 'A' || ent == 'a'){
        if (!listarCredenciais())
            printf("Lista Completa Vazia\n");
    }
    else if (ent == 'R' || ent == 'r'){
        if (listarResumido() == 0)
            printf("Lista vazia\n");
    }
    else if (ent == 'D' || ent == 'd'){
        if (!listarDetalhes())
            printf("Lista Detalhes vazio\n");
    } else {
        printf("Opcao nao encontrada\n");   
        menuListar();
    }
}