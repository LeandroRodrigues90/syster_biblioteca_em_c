#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---define contanstes globais do programa---
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define TAM_STRING 100

//---definição das estruturas---

//---estrutura para guardar as informações do livro
struct Livro
{
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel;// 1 para sim,0 para não disponivel

};

//--estrutura para armazenar informações do emprestimo
struct Emprestimo
{
    int indiceLivro;//para saber qual livro do array foi emprestado
    char nomeUsuario[TAM_STRING];
};


//---função para limpar o buffer de entrada---
void limparBufferEntrada();
void exibirMenu();
void cadastrarLivro (struct Livro *biblioteca,int *totalLivros);
void listarLivros(const struct Livro *biblioteca,int totalLivros);
void realizarEmprestimo(struct Livro *biblioteca,int totalLivros,struct Emprestimo *emprestimos,int totalEmprestimos);
void listarEmprestimos(const struct Livro *biblioteca,const struct Emprestimo *emprestimos,int totalEmprestimos);
void liberarMemoria(struct Livro *biblioteca,struct Emprestimo *emprestimos);

//---função principal (main)---

int main(){
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;

    //--Usaremos calloc para o array de livros pois inicializa toda a memoria com zeros.
    biblioteca= (struct Livro *)calloc(MAX_LIVROS, sizeof(struct Livro));

    //--Usaremos malloc para o array de emprestimos 
    emprestimos= (struct Emprestimo *)malloc(MAX_EMPRESTIMOS* sizeof(struct Emprestimo));

    //verificação :é crucual verificar se a alocação de memória deu certo.
    if (biblioteca==NULL || emprestimos==NULL){
        printf("Erro:Falha ao alocar memoria.\n");
        return 1;//retorna 1 para indicar um erro.
    }
    
    //variaveis globais
    int totalLivros=0;
    int totalEmprestimos=0;
    int opcao;

    do{
        exibirMenu();
        scanf("%d",&opcao);
        limparBufferEntrada();
        switch (opcao)
        {
        case 1://Cadastro de Livro
                //passamos & comercial pois o valor precisa ser modificado durante a execução
                cadastrarLivro(biblioteca,&totalLivros);
                break;
        case 2://Listar livros cadastrados
            listarLivros(biblioteca,totalLivros);
            break;
        case 3://fazer emprestimo do livro
            realizarEmprestimo(biblioteca,totalLivros,emprestimos,&totalEmprestimos);
            break;
        case 4://listar emprestimos
            listarEmprestimos(biblioteca,emprestimos,totalEmprestimos);
            break;
        case 0:
            printf("\nSaindo do sistema....\n");
            break;
            
        default:
            printf("\nOpção Invalida\n");
            break;
        }
        
    }
    while (opcao!=0);

        liberarMemoria(biblioteca,emprestimos);
        
    return 0;
}

//implementação de funções

void liberarMemoria(struct Livro *biblioteca,struct Emprestimo *emprestimos){
        free(biblioteca);
        free(emprestimos);
        printf("Memoria Liberada com sucesso!");
}

void exibirMenu(){
     printf("===========================\n");
        printf("        Biblioteca        \n");
        printf("===========================\n");
        printf("1- Cadastrar novo Livro\n");
        printf("2- Listar todos os Livros cadastrados\n");
        printf("3- Realizar Emprestimo\n");
        printf("4- Listar Emprestimos\n");
        printf("0- Sair\n");
        printf("--------------------------\n");
        printf("Escolha uma opcao: ");
        
}

void cadastrarLivro(struct Livro *biblioteca,int *totalLivros){
        printf("---Cadastro de Novo Livro---\n\n");
            if (*totalLivros<MAX_LIVROS){
                printf("Digite o nome do Livro: ");
                fgets(biblioteca[*totalLivros].nome,TAM_STRING,stdin);

                printf("Digite o autor: ");
                fgets(biblioteca[*totalLivros].autor,TAM_STRING,stdin);

                printf("Digite a Edidora: ");
                fgets(biblioteca[*totalLivros].editora,TAM_STRING,stdin);

                biblioteca[*totalLivros].nome[strcspn(biblioteca[*totalLivros].nome,"\n")]='\0';
                biblioteca[*totalLivros].autor[strcspn(biblioteca[*totalLivros].autor,"\n")]='\0';
                biblioteca[*totalLivros].editora[strcspn(biblioteca[*totalLivros].editora,"\n")]='\0';
                
                printf("Digite a edicao: ");
                scanf("%d",&biblioteca[*totalLivros].edicao);
                limparBufferEntrada();

                //ao cadastrar,o livro automaticamente se torna disponivel.
                biblioteca[*totalLivros].disponivel=1;

                totalLivros++;
                printf("\nLivro Cadastrado com Sucesso!\n");   
            }
            else{
                printf("Biblioteca cheia\n");
            }
            printf("Pressione enter para continuar...");
            getchar();
}

void listarLivros(const struct Livro *biblioteca,int totalLivros){
    printf("---Listar Livros Cadastrados---\n\n");
            if(totalLivros==0){
                printf("Nenhum livro cadastrado\n");
            }
            else{

            for (int i = 0; i < totalLivros; i++)
                {   
                printf("\n--------------------------------\n");
                printf("Livro== %d\n",i+1);
                printf("Nome do Livro: %s\n",biblioteca[i].nome);
                printf("Autor: %s\n",biblioteca[i].autor);
                printf("Editora: %s\n",biblioteca[i].editora);
                printf("Edição: %d\n",biblioteca[i].edicao);
                }
            }
            printf("Pressione enter para continuar....");
            getchar();
}

void realizarEmprestimo(struct Livro *biblioteca,int totalLivros,struct Emprestimo *emprestimos ,int totalEmprestimos){
            printf("---Emprestimo de livro--\n\n");
            if(totalEmprestimos>=MAX_EMPRESTIMOS){
                printf("Limite de emprestimo de livro atingido!\n");
            }else{
                printf("Livros disponiveis: \n");
                int disponiveis=0;
                for (int i = 0; i < totalLivros; i++)
                {
                    if(biblioteca[i].disponivel){
                        printf("%d-%s\n",i+1,biblioteca[i].nome);
                        disponiveis++;
                    }
                }
                if (disponiveis==0){
                    printf("Nenhum livro disponivel para emprestimo!\n");
                }else{
                    printf("Digite o numero da linha para selecionar o livro para emprestimo: ");
                    int numLivro;
                    scanf("%d",&numLivro);
                    limparBufferEntrada();
                    int indice=numLivro-1; // converte para o indice do array (0 a N-1)

                    //validação da escolha do usuario.
                    if (indice>=0 && indice < totalLivros && biblioteca[indice].disponivel){
                        printf("Digite o nome do usuario que esta pegando o livro: ");
                        fgets(emprestimos[totalEmprestimos].nomeUsuario,TAM_STRING,stdin);
                        emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario,"\n")] ='\0';

                        //Registo o emprestimo
                        emprestimos[totalEmprestimos].indiceLivro=indice;

                        //atualiza o status do livro para indisponivel.
                        biblioteca[indice].disponivel=0;
                        totalEmprestimos++;
                        printf("\nEmprestimo realizado com sucesso!");
                    }else{
                        printf("\nNumero do livro invalido ou livro indisponivel!\n");
                    }
                }
            }
            printf("Digite enter para continuar...\n");
            getchar();
}

void limparBufferEntrada(){
    int c;
    while ((c=getchar()) != '\n' && c !=EOF);    
}
