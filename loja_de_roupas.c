#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100 
//oi tudo bem
typedef enum { 
    CAMISETA = 1,
    CALCA,
    JAQUETA,
    SHORT,
    VESTIDO
} Categoria;

typedef struct {
    char nome[50];
    Categoria categoria;
    float preco;
} Roupa; 

Roupa estoque[TAM]; 
int qtd = 0; 

void mostrarCategorias() {
    printf("1) Camiseta\n");
    printf("2) Cal�a\n");
    printf("3) Jaqueta\n");
    printf("4) Short\n");
    printf("5) Vestido\n");
} 

void adicionarRoupa() {
    if (qtd >= TAM) {
        printf("Estoque cheio!\n");
        return;
    } 

    FILE *arquivo = fopen("estoque.txt", "a"); 
    if (arquivo == NULL) { 
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Roupa nova; 

    printf("Nome da roupa: ");
    scanf(" %[^\n]", nova.nome); 

    mostrarCategorias();
    printf("Escolha a categoria (1-5): ");
    scanf("%d", (int*)&nova.categoria);

    printf("Pre�o da roupa: R$ ");
    scanf("%f", &nova.preco); 

    estoque[qtd++] = nova; 

    fprintf(arquivo, "%s;%d;%.2f\n", nova.nome, nova.categoria, nova.preco); 
    fclose(arquivo); 

    printf("Roupa adicionada com sucesso!\n");
    system("pause"); 
}

void listarRoupas() {
    FILE *arquivo = fopen("estoque.txt", "r"); 
    if (arquivo == NULL) {
        printf("Nenhum item cadastrado ainda.\n");
        return;
    }

    char linha[100]; // cria um vetor tam 100
    printf("\n- ESTOQUE -\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        char nome[50];
        int cat;
        float preco;

        sscanf(linha, "%[^;];%d;%f", nome, &cat, &preco); 

        printf("Nome: %s\n", nome);
        printf("Categoria: ");

        switch (cat) {
            case CAMISETA: printf("Camiseta\n"); break; 
            case CALCA: printf("Cal�a\n"); break; 
            case JAQUETA: printf("Jaqueta\n"); break;
            case SHORT: printf("Short\n"); break;
            case VESTIDO: printf("Vestido\n"); break;
            default: printf("Desconhecida\n");
        }

        printf("Pre�o: R$ %.2f\n\n", preco);
    }

    fclose(arquivo);
    system("pause");
}

void ordenarPorPreco() {
    int i, j;
    Roupa temp;

    for (i = 0; i < qtd - 1; i++) {
        for (j = 0; j < qtd - i - 1; j++) {
            if (estoque[j].preco > estoque[j + 1].preco) {
                temp = estoque[j];
                estoque[j] = estoque[j + 1];
                estoque[j + 1] = temp;
            }
        }
    }

    printf("\n- ROUPAS ORDENADAS POR PRE�O -\n");
    for (i = 0; i < qtd; i++) {
        printf("Nome: %s | Pre�o: R$ %.2f\n", estoque[i].nome, estoque[i].preco);
    }
    system("pause");
}

int main() { 
	
    int opcao; 
	
	
		
    do { 
        system("cls"); 
        printf("- LOJA DE ROUPAS -\n");
        printf("1) Adicionar roupa ao estoque\n"); 
        printf("2) Listar roupas\n");
        printf("3) Ordenar por pre�o (Bubble Sort)\n");
        printf("4) Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao); 

        switch (opcao) { 
            case 1:
                adicionarRoupa();
                break;
            case 2:
                listarRoupas();
                break;
            case 3:
                ordenarPorPreco();
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida!\n");
                system("pause"); 
        }

    } while (opcao != 4);

    return 0;
}

