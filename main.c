//
// Created by renorram on 17/09/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "name_tree.h"

void show_menu() {
    system("clear");
    printf("|| (1) = Recarregar a listagem de nomes a partir do arquivo.         ||\n");
    printf("|| (2) = Listar todos os nomes em ordem alfabetica.                  ||\n");
    printf("|| (3) = Listar todos os nomes que contem uma substring fornecida.   ||\n");
    printf("|| (4) = Inserir um novo nome na memoria.                            ||\n");
    printf("|| (5) = Remover um nome da memoria.                                 ||\n");
    printf("|| (6) = Listar e remover da memoria todos os nomes que sao maiores  ||\n");
    printf("|| (7) = Listar e remover da memoria todos os nomes que sao menores. ||\n");
    printf("|| (8) = Salvar o conteudo da memoria em um arquivo texto.           ||\n\n");
    printf("|| (9) = SAIR DO PROGRAMA                                            ||\n");
    printf("Selecione uma das opcoes acima\n");
}

void wait_for_keypressed()
{
    while(getchar() != '\n') {}
}

int main(void) {
    const char *file_to_read = "/mnt/c/Users/1611331/Documents/tramped2/resources/names.txt";
    const char *file_to_save = "/mnt/c/Users/1611331/Documents/tramped2/resources/names2.txt";


    Tree *t = tree_create();
    name_tree_load_from_file(file_to_read, t);

    char op;
    char name[31];
    do {
        show_menu();
        op = (char)getchar();
        getchar(); // skip \n
        switch (op) {
            case '1':
                name_tree_load_from_file(file_to_read, t);
                wait_for_keypressed();
                break;
            case '2':
                tree_print(t);
                wait_for_keypressed();
                break;
            case '3':
                printf("Digite o que deseja buscar: \n");
                fgets(name, sizeof(name), stdin);
                fflush(stdin);
                tree_print_by_substring(t, name);
                wait_for_keypressed();
                break;
            case '4':
                printf("Digite o que deseja inserir: \n");
                fgets(name, sizeof(name), stdin);
                fflush(stdin);
                tree_insert(t, name);
                wait_for_keypressed();
                break;
            case '5':
                printf("Digite o que deseja remover: \n");
                fgets(name, sizeof(name), stdin);
                fflush(stdin);
                tree_remove(t, name);
                wait_for_keypressed();
                break;
            case '6':
                printf("Digite o que deseja remover (MAIORES): \n");
                fgets(name, sizeof(name), stdin);
                fflush(stdin);
                tree_remove_bigger_substring(t, name);
                wait_for_keypressed();
                break;
            case '7':
                printf("Digite o que deseja remover (MENORES): \n");
                fgets(name, sizeof(name), stdin);
                fflush(stdin);
                tree_remove_smaller_substring(t, name);
                wait_for_keypressed();
                break;
            case '8':
                name_tree_save_to_file(file_to_save, t);
                wait_for_keypressed();
                break;
            case '9':
                tree_destroy(t);
                exit(0);
            default:
                break;
        }
    } while (1);
}