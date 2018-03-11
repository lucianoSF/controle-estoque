//follow the white rabbit...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define cons50 50
//.................................INICIO STRUCTS
typedef struct {
    char logradouro[cons50];
    char complemento[cons50];
    char cep[20];
    char bairro[cons50];
    char cidade[cons50];
    char estado[20];
}endereco;

typedef struct{
    char codigo[20];
    char nome[cons50];
    char cnpj_cpf[20];
    char telefone[20];
    endereco XEndereco;
}cliente;

typedef struct{
    char codigo[20];
    char nome[cons50];
    char fornecedor[cons50];
    char categoria[20];
    int quantidade;
    float valor_unitario;
}produto;
typedef struct{
    int dia;
    int mes;
    int ano;
    int quantidade[20];
    cliente comprador;
    produto mercadoria[20];
    int quantidade_cada_produto;
}pedido;
//...............................FINAL STRUCTS

void limpar_buffer(){
char c;
    while((c=getchar())!='\n' && c!=EOF);
}
void verificar_arquivo(FILE *arquivo){
    if(arquivo==NULL){
        printf("ERRO.Nao foi possivel abrir o arquivo!\n");
        exit(1);

    }


}
//...............................INICIO FUNÇOES DE CLIENTE
void cadastrar_clientes(){
    FILE *arquivo;
    cliente aux;

    arquivo = fopen("cliente.txt","ab");
    verificar_arquivo(arquivo);
    printf("Preencha as informaçoes do cliente\n");
    printf("Nome do cliente:\n");
    scanf("%[^\n]s",aux.nome);getchar();
    printf("Codigo do cliente:\n");
    scanf("%[^\n]s",aux.codigo);getchar();
    printf("CNPJ ou CPF:\n");
    scanf("%[^\n]s",aux.cnpj_cpf);getchar();
    printf("Telefone de contato\n");
    scanf("%[^\n]s",aux.telefone);getchar();
    printf("Logradouro:\n");
    scanf("%[^\n]s",aux.XEndereco.logradouro);getchar();
    printf("Complemento:\n");
    scanf("%[^\n]s",aux.XEndereco.complemento);getchar();
    printf("CEP:\n");
    scanf("%[^\n]s",aux.XEndereco.cep);getchar();
    printf("Bairro:\n");
    scanf("%[^\n]s",aux.XEndereco.bairro);getchar();
    printf("Cidade:\n");
    scanf("%[^\n]s",aux.XEndereco.cidade);getchar();
    printf("Estado:\n");
    scanf("%[^\n]s",aux.XEndereco.estado);getchar();

    fwrite(&aux,sizeof(cliente),1,arquivo);
    fclose(arquivo);

}
void buscar_clientes(){
    FILE *arquivo;
    cliente aux;
    int opcao_menu,cont=0;
    char nome[20],codigo[20];
    arquivo = fopen("cliente.txt","rb");
    verificar_arquivo(arquivo);
    printf("Digite 1 para buscar pelo codigo e 2 para buscar pelo nome:\n");
    scanf("%i",&opcao_menu);getchar();
    switch(opcao_menu){
        case 1:
            printf("Digite o codigo:\n");
            scanf("%[^\n]s",codigo);getchar();
            strcpy(nome,"\0");
        break;
        case 2:
            printf("Digite o nome:\n");
            scanf("%[^\n]s",nome);getchar();
            strcpy(codigo,"\0");
        break;
    }
    while(fread(&aux,sizeof(cliente),1,arquivo)==1){
        if(strcmp(codigo,aux.codigo)==0 || strcmp(nome,aux.nome)==0){
            printf("========================================================\n");
            printf("Cliente: %s\n",aux.nome);
            printf("Codigo: %s\n",aux.codigo);
            printf("CNPJ ou CPF: %s\n",aux.cnpj_cpf);
            printf("Telefone: %s\n",aux.telefone);
            printf("Logradouro: %s\n",aux.XEndereco.logradouro);
            printf("Complemento: %s\n",aux.XEndereco.complemento);
            printf("CEP: %s\n",aux.XEndereco.cep);
            printf("Bairro: %s\n",aux.XEndereco.bairro);
            printf("Cidade: %s\n",aux.XEndereco.cidade);
            printf("Estado: %s\n",aux.XEndereco.estado);
            printf("--------------------------------------------------------\n");
            cont=1;
        }
    }
    if(cont==0){
        printf("Cliente nao cadastrado\n");
    }
    fclose(arquivo);
}
void listar_clientes(){
    FILE *arquivo;
    cliente *aux,aux_aux;
    int i=0,j,l,cont=0;
    aux=(cliente*)malloc(sizeof(cliente));
    arquivo = fopen("cliente.txt","rb");
    verificar_arquivo(arquivo);
    while(fread(&aux[i],sizeof(cliente),1,arquivo)==1){
    i++;
    aux=(cliente*)realloc(aux,sizeof(cliente)*(i+1));

    }

    for(j=0;j<i;j++){
        for(l=0;l<i-1;l++){

            if(strcmp(aux[l].nome,aux[l+1].nome)>0){

              aux_aux=aux[l];
              aux[l]=aux[l+1];
              aux[l+1]=aux_aux;



            }
        }
    }
    for(j=0;j<i;j++){
        printf("========================================================\n");
            printf("Cliente: %s\n",aux[j].nome);
            printf("Codigo: %s\n",aux[j].codigo);
            printf("CNPJ ou CPF: %s\n",aux[j].cnpj_cpf);
            printf("Telefone: %s\n",aux[j].telefone);
            printf("Logradouro: %s\n",aux[j].XEndereco.logradouro);
            printf("Complemento: %s\n",aux[j].XEndereco.complemento);
            printf("CEP: %s\n",aux[j].XEndereco.cep);
            printf("Bairro: %s\n",aux[j].XEndereco.bairro);
            printf("Cidade: %s\n",aux[j].XEndereco.cidade);
            printf("Estado: %s\n",aux[j].XEndereco.estado);
        printf("--------------------------------------------------------\n");
        cont=1;
    }
    if(cont==0){
        printf("Nao existem clientes cadastrados\n");
    }
    free(aux);
    fclose(arquivo);
}
void atualizar_clientes(){
    FILE *arquivo,*arquivo_aux;
    cliente aux;
    int cont=0;
    char codigo[20];

    arquivo=fopen("cliente.txt","rb");verificar_arquivo(arquivo);
    arquivo_aux=fopen("auxCliente.txt","wb");verificar_arquivo(arquivo_aux);

    printf("Digite o codigo do cliente a ser atualizado:\n");
    scanf("%[^\n]s",codigo);getchar();

    while(fread(&aux,sizeof(cliente),1,arquivo)==1){
        if(strcmp(codigo,aux.codigo)!=0){
            fwrite(&aux,sizeof(cliente),1,arquivo_aux);
        }else{
        cont=1;
            printf("Digite os novos dados a serem atualizados\n\n");
            printf("Nome do cliente:\n");
            scanf("%[^\n]s",aux.nome);getchar();
            printf("Codigo do cliente:\n");
            scanf("%[^\n]s",aux.codigo);getchar();
            printf("CNPJ ou CPF:\n");
            scanf("%[^\n]s",aux.cnpj_cpf);getchar();
            printf("Telefone de contato\n");
            scanf("%[^\n]s",aux.telefone);getchar();
            printf("Logradouro:\n");
            scanf("%[^\n]s",aux.XEndereco.logradouro);getchar();
            printf("Complemento:\n");
            scanf("%[^\n]s",aux.XEndereco.complemento);getchar();
            printf("CEP:\n");
            scanf("%[^\n]s",aux.XEndereco.cep);getchar();
            printf("Bairro:\n");
            scanf("%[^\n]s",aux.XEndereco.bairro);getchar();
            printf("Cidade:\n");
            scanf("%[^\n]s",aux.XEndereco.cidade);getchar();
            printf("Estado:\n");
            scanf("%[^\n]s",aux.XEndereco.estado);getchar();



            fwrite(&aux,sizeof(cliente),1,arquivo_aux);
        }
    }
    if(cont==0){
        printf("Codigo nao cadastrado\n");
    }
    fclose(arquivo);fclose(arquivo_aux);
    arquivo=fopen("cliente.txt","wb");verificar_arquivo(arquivo);
    arquivo_aux=fopen("auxCliente.txt","rb");verificar_arquivo(arquivo_aux);
    while(fread(&aux,sizeof(cliente),1,arquivo_aux)==1){
        fwrite(&aux,sizeof(cliente),1,arquivo);
    }
    fclose(arquivo);fclose(arquivo_aux);
}
void excluir_clientes(){
    FILE *arquivo,*arquivo_aux;
    cliente aux;
    int cont=0;
    char codigo[20];
    arquivo = fopen("cliente.txt","rb");verificar_arquivo(arquivo);
    arquivo_aux = fopen("auxCliente.txt","wb");verificar_arquivo(arquivo_aux);

    printf("Digite o codigo do cliente a ser excluido:\n");
    scanf("%[^\n]s",codigo);getchar();

    while(fread(&aux,sizeof(cliente),1,arquivo)==1){
        if(strcmp(codigo,aux.codigo)!=0){
           fwrite(&aux,sizeof(cliente),1,arquivo_aux);
        }else{
            cont=1;
        }
    }
    if(cont==0){
        printf("Codigo nao cadastrado\n");
    }
    fclose(arquivo);fclose(arquivo_aux);
    arquivo = fopen("cliente.txt","wb");verificar_arquivo(arquivo);
    arquivo_aux = fopen("auxCliente.txt","rb");verificar_arquivo(arquivo_aux);
    while(fread(&aux,sizeof(cliente),1,arquivo_aux)==1){
        fwrite(&aux,sizeof(cliente),1,arquivo);
    }

    fclose(arquivo);fclose(arquivo_aux);
}
//...............................FINAL FUNÇOES DE CLIENTE

//...............................INICIO FUNÇOES DE PRODUTO
void cadastrar_produtos(){
    FILE *arquivo;
    produto aux;

    arquivo = fopen("produto.txt","ab");
    verificar_arquivo(arquivo);
    printf("Digite os dados referentes ao produto\n\n");
    printf("Nome do produto:\n");
    scanf("%[^\n]s",aux.nome);getchar();
    printf("Codigo do produto:\n");
    scanf("%[^\n]s",aux.codigo);getchar();
    printf("Fornecedor do produto:\n");
    scanf("%[^\n]s",aux.fornecedor);getchar();
    printf("Categoria do produto\n");
    scanf("%[^\n]s",aux.categoria);getchar();
    printf("Quantidade do produto\n");
    scanf("%i",&aux.quantidade);getchar();
    printf("Valor unitario do produto:\n");
    scanf("%f",&aux.valor_unitario);getchar();
    fwrite(&aux,sizeof(produto),1,arquivo);
    fclose(arquivo);
}
void listar_produtos(){
    FILE *arquivo;
    produto *aux,aux_aux;
    int i=0,j,l,cont=0,cont2=0;
    char categoria[20];
    strcpy(categoria,"\0");
    aux=(produto*)malloc(sizeof(produto));
    arquivo = fopen("produto.txt","rb");verificar_arquivo(arquivo);

    while(fread(&aux[i],sizeof(produto),1,arquivo)==1){
        i++;
        aux=(produto*)realloc(aux,sizeof(produto)*(i+1));

    }
    printf("Digite uma categoria para pesquisa\n");
    scanf("%[^\n]s",categoria);getchar();
    if(strcmp(categoria,"\0")==0){
        cont2=1;
    }
    for(j=0;j<i;j++){
        for(l=0;l<i-1;l++){

            if(strcmp(aux[l].nome,aux[l+1].nome)>0){
                aux_aux=aux[l];
                aux[l]=aux[l+1];
                aux[l+1]=aux_aux;
            }
        }
    }
    for(j=0;j<i;j++){
        if(strcmp(aux[j].categoria,categoria)==0 || cont2==1){
            printf("========================================================\n");
            printf("Nome: %s\n",aux[j].nome);
            printf("Codigo: %s\n",aux[j].codigo);
            printf("Fornecedor: %s\n",aux[j].fornecedor);
            printf("Categoria: %s\n",aux[j].categoria);
            printf("Quantidade: %i\n",aux[j].quantidade);
            printf("Valor unitario: %.2f\n",aux[j].valor_unitario);
            printf("--------------------------------------------------------\n");
            cont=1;
        }
    }
    if(cont==0){
        printf("Nao existem produtos cadastrados nesta categoria\n");
    }
    free(aux);
    fclose(arquivo);
}
void buscar_produtos(){
    FILE *arquivo;
    produto aux;
    int opcao_menu,cont=0;
    char nome[20],codigo[20];
    arquivo = fopen("produto.txt","rb");
    verificar_arquivo(arquivo);
    printf("Digite 1 para buscar pelo codigo e 2 para buscar pelo nome:\n");
    scanf("%i",&opcao_menu);getchar();
    switch(opcao_menu){
        case 1:
            printf("Digite o codigo:\n");
            scanf("%[^\n]s",codigo);getchar();
            strcpy(nome,"\0");
        break;
        case 2:
            printf("Digite o nome:\n");
            scanf("%[^\n]s",nome);getchar();
            strcpy(codigo,"\0");
        break;
    }
    while(fread(&aux,sizeof(produto),1,arquivo)==1){
        if(strcmp(codigo,aux.codigo)==0 || strcmp(nome,aux.nome)==0){
            printf("========================================================\n");
            printf("Nome: %s\n",aux.nome);
            printf("Codigo: %s\n",aux.codigo);
            printf("Fornecedor: %s\n",aux.fornecedor);
            printf("Categoria: %s\n",aux.categoria);
            printf("Quantidade: %i\n",aux.quantidade);
            printf("Valor unitario: %.2f\n",aux.valor_unitario);
            printf("--------------------------------------------------------\n");
            cont=1;
        }
    }
    if(cont==0){
        printf("Produto nao cadastrado\n");
    }
    fclose(arquivo);
}
void atualizar_produtos(){
     FILE *arquivo,*arquivo_aux;
    produto aux;
    int cont=0;
    char codigo[20];
    arquivo=fopen("produto.txt","rb");verificar_arquivo(arquivo);
    arquivo_aux=fopen("auxProduto.txt","wb");verificar_arquivo(arquivo_aux);

    printf("Digite o codigo do cliente a ser atualizado:\n");
    scanf("%[^\n]s",codigo);getchar();

    while(fread(&aux,sizeof(produto),1,arquivo)==1){
        if(strcmp(codigo,aux.codigo)!=0){
            fwrite(&aux,sizeof(produto),1,arquivo_aux);
        }else{
        cont=1;
            printf("Digite novamente os dados do produto:\n\n");
            printf("Nome do produto:\n");
            scanf("%[^\n]s",aux.nome);getchar();
            printf("Codigo do produto:\n");
            scanf("%[^\n]s",aux.codigo);getchar();
            printf("Fornecedor:\n");
            scanf("%[^\n]s",aux.fornecedor);getchar();
            printf("Categoria: \n");
            scanf("%[^\n]s",aux.categoria);getchar();
            printf("Quantidade:\n\n");
            scanf("%i",&aux.quantidade);getchar();
            printf("Valor unitario:\n\n");
            scanf("%f",&aux.valor_unitario);getchar();

            fwrite(&aux,sizeof(produto),1,arquivo_aux);
        }
    }
    if(cont==0){
        printf("Codigo nao cadastrado\n");
    }
    fclose(arquivo);fclose(arquivo_aux);
    arquivo=fopen("produto.txt","wb");verificar_arquivo(arquivo);
    arquivo_aux=fopen("auxProduto.txt","rb");verificar_arquivo(arquivo_aux);
    while(fread(&aux,sizeof(produto),1,arquivo_aux)==1){
        fwrite(&aux,sizeof(produto),1,arquivo);
    }
    fclose(arquivo);fclose(arquivo_aux);
}
void atualizar_estoque(){
    FILE *arquivo,*arquivo_aux;
    produto aux;
    char codigo[20];
    arquivo=fopen("produto.txt","rb");verificar_arquivo(arquivo);
    arquivo_aux=fopen("auxProduto.txt","wb");verificar_arquivo(arquivo_aux);
    printf("Digite o codigo do produto:\n");
    scanf("%[^\n]s",codigo);getchar();
    while(fread(&aux,sizeof(produto),1,arquivo)==1){
        if(strcmp(codigo,aux.codigo)!=0){
            fwrite(&aux,sizeof(produto),1,arquivo_aux);
        }else{
            printf("Digite a nova quantidade:\n");
            scanf("%i",&aux.quantidade);getchar();
            fwrite(&aux,sizeof(produto),1,arquivo_aux);
        }
    }

    fclose(arquivo);fclose(arquivo_aux);
    arquivo=fopen("produto.txt","wb");verificar_arquivo(arquivo);
    arquivo_aux=fopen("auxProduto.txt","rb");verificar_arquivo(arquivo);
    while(fread(&aux,sizeof(produto),1,arquivo_aux)==1){
        fwrite(&aux,sizeof(produto),1,arquivo);
    }
    fclose(arquivo);fclose(arquivo_aux);
}
//...............................FINAL FUNÇOES DE PRODUTO

//...............................INICIO FUNÇOES DE PEDIDO
void cadastrar_pedidos(){
FILE *arquivo_pedido;
pedido aux_pedido;
char codigo_nome[20],opcao_menu='\0';
//...............................
time_t rawtime;
struct tm *timeinfo;
int dia,mes,ano,codigo_produto,cont_cliente=0,cont_produto=0,i=0;
time (&rawtime);
timeinfo = localtime (&rawtime);
//........................................

//.....................................
strcpy(aux_pedido.comprador.codigo,"\0");
strcpy(aux_pedido.comprador.nome,"\0");
//.........................................
    printf("Digite o codigo ou o nome do cliente:\n");
    scanf("%[^\n]s",codigo_nome);getchar();

    FILE *arquivo_cliente;
    cliente aux_cliente;
    arquivo_cliente=fopen("cliente.txt","rb");verificar_arquivo(arquivo_cliente);
    while(fread(&aux_cliente,sizeof(cliente),1,arquivo_cliente)==1){
        if((strcmp(aux_cliente.codigo,codigo_nome)==0 || strcmp(aux_cliente.nome,codigo_nome)==0)){
                aux_pedido.comprador=aux_cliente;
                cont_cliente=1;
        }
    }
    fclose(arquivo_cliente);
    if(cont_cliente==0 && strcmp(codigo_nome,"\0")!=0){
        printf("Cliente digitado nao existe...\n");
    }else{
        printf("Digite quantidade de produtos a serem cadastrados:\n");
        scanf("%i",&aux_pedido.quantidade_cada_produto);getchar();
        do{

            printf("Digite o codigo do produto:\n");
            scanf("%[^\n]s",codigo_nome);getchar();
            FILE *arquivo_produto;
            produto aux_produto;
            arquivo_produto = fopen("produto.txt","rb");verificar_arquivo(arquivo_produto);

            cont_produto=0;
            while(fread(&aux_produto,sizeof(produto),1,arquivo_produto)==1){
                if(strcmp(aux_produto.codigo,codigo_nome)==0){
                    aux_pedido.mercadoria[i]=aux_produto;
                    printf("Digite a quantidade do produto:\n");
                    scanf("%i",&aux_pedido.quantidade[i]);getchar();
                    cont_produto=1;
                    i++;
                    break;
                }
            }
            fclose(arquivo_produto);
        if(cont_produto==0){
            printf("Codigo informado nao corresponde a nenhum produto.\n\nDigite ENTER se deseja digitar de novo ou S para sair\n");
            scanf("%c",&opcao_menu);
        }

        }while(opcao_menu!='S' && i<aux_pedido.quantidade_cada_produto);
        if(cont_produto==1){
             aux_pedido.dia=timeinfo->tm_mday;
             aux_pedido.mes=timeinfo->tm_mon+1;
             aux_pedido.ano=timeinfo->tm_year+1900;
             arquivo_pedido = fopen("pedido.txt","ab");verificar_arquivo(arquivo_pedido);
             fwrite(&aux_pedido,sizeof(pedido),1,arquivo_pedido);
             fclose(arquivo_pedido);
        }
    }

}
void listar_pedidos_cliente(){
FILE *arquivo;
pedido *aux,aux_aux;
aux=(pedido*)malloc(sizeof(pedido));
int i,j=0,l;
char nome_codigo[20];
arquivo = fopen("pedido.txt","rb");verificar_arquivo(arquivo);
printf("Digite o codigo ou nome do cliente:\n");
scanf("%[^\n]s",nome_codigo);getchar();
while(fread(&aux[j],sizeof(pedido),1,arquivo)==1){
    j++;
    aux=(pedido*)realloc(aux,sizeof(pedido)*(j+1));
}
for(l=0;l<j;l++){
    for(i=0;i<j-1;i++){
        if(aux[i].ano<aux[i+1].ano){
            aux_aux=aux[i];
            aux[i]=aux[i+1];
            aux[i+1]=aux_aux;
        }
        if(aux[i].ano==aux[i+1].ano && aux[i].mes<aux[i+1].mes){
            aux_aux=aux[i];
            aux[i]=aux[i+1];
            aux[i+1]=aux_aux;
        }
        if(aux[i].ano==aux[i+1].ano && aux[i].mes==aux[i+1].mes && aux[i].dia<aux[i+1].dia){
            aux_aux=aux[i];
            aux[i]=aux[i+1];
            aux[i+1]=aux_aux;
        }
    }

}

for(l=0;l<j;l++){
    if(strcmp(aux[l].comprador.codigo,nome_codigo)==0 || strcmp(aux[l].comprador.nome,nome_codigo)==0){
        printf("Data:   %i/%i/%i\n",aux[l].dia,aux[l].mes,aux[l].ano);
        printf("=====================================================================\n");
        for(i=0;i<aux[l].quantidade_cada_produto;i++){
            printf("nome produto: %s\n",aux[l].mercadoria[i].nome);
            printf("quantidade produto: %i\n",aux[l].quantidade[i]);
            printf("---------------------------------------------------------------------\n");

        }
    }

}
free(aux);fclose(arquivo);

}
void listar_pedidos_dia(){
FILE *arquivo;
pedido *aux,aux_aux;
int i=0,j,l,dia,mes,ano;
aux=(pedido*)malloc(sizeof(pedido));
arquivo = fopen("pedido.txt","rb");verificar_arquivo(arquivo);
printf("Digite o dia:\n");
scanf("%i",&dia);getchar();
printf("Digite o mes:\n");
scanf("%i",&mes);getchar();
printf("Digite o ano:\n");
scanf("%i",&ano);getchar();

while(fread(&aux[i],sizeof(pedido),1,arquivo)==1){
    i++;
    aux=(pedido*)realloc(aux,sizeof(pedido)*(i+1));
}

for(l=0;l<i;l++){
    for(j=0;j<i-1;j++){
        if(strcmp(aux[j].comprador.nome,aux[j+1].comprador.nome)>0){
            aux_aux=aux[j];
            aux[j]=aux[j+1];
            aux[j+1]=aux_aux;

        }

    }

}

for(l=0;l<i;l++){
    if(dia==aux[l].dia && mes==aux[l].mes && ano==aux[l].ano){
    printf("%s\n",aux[l].comprador.nome);
        printf("=====================================================================\n");
        for(j=0;j<aux[l].quantidade_cada_produto;j++){
            printf("nome produto: %s\n",aux[l].mercadoria[j].nome);
            printf("quantidade produto: %i\n",aux[l].quantidade[j]);
            printf("---------------------------------------------------------------------\n");
        }


    }

}
free(aux);fclose(arquivo);



}
//...............................FINAL FUNÇOES DE PEDIDO

int main(){
int i;
    char opcao_menu;
    do{
        printf("Digite um comando para prosseguir:\nC – Gerenciar Clientes\nP – Gerenciar Produtos\nE – Gerenciar Pedidos\nS – Sair\n");
        scanf("%c",&opcao_menu);limpar_buffer();system("clear");
                switch(opcao_menu){
                    case 'C':
                        printf("============ Gerenciar Clientes ============\nDigite um comando para prosseguir:\nC – Cadastrar um cliente.\nL – Listar todos os clientes cadastrados.\nB – Buscar cliente já cadastrado.\nA – Atualizar um cliente cadastrado.\nE – Excluir um cliente cadastrado.\n");
                            scanf("%c",&opcao_menu);limpar_buffer();system("clear");
                            switch(opcao_menu){
                                case 'C':
                                    cadastrar_clientes();
                                    printf("Pressione ENTER para continuar...\n");limpar_buffer();system("clear");
                                break;
                                case 'L':
                                    listar_clientes();
                                    printf("Pressione ENTER para continuar...\n");limpar_buffer();system("clear");
                                break;
                                case 'B':
                                    buscar_clientes();
                                    printf("Pressione ENTER para continuar...\n");limpar_buffer();system("clear");
                                break;
                                case 'A':
                                    atualizar_clientes();
                                    printf("Pressione ENTER para continuar...\n");limpar_buffer();system("clear");
                                break;
                                case 'E':
                                    excluir_clientes();
                                    printf("Pressione ENTER para continuar...\n");limpar_buffer();system("clear");
                                break;
                            }
                        break;


                    case 'P':
                        printf("============== Gerenciar Produtos ==============\nDigite um comando para prosseguir:\nC – Cadastrar um produto.\nL – Listar todos os produtos cadastrados.\nB – Buscar produto já cadastrado.\nA – Atualizar um produto cadastrado.\nT – Atualizar estoque de um produto.\n");
                        scanf(" %c",&opcao_menu);system("clear");limpar_buffer();
                    switch(opcao_menu){
                                case 'C':
                                    cadastrar_produtos();
                                    printf("Pressione ENTER para continuar...\n");limpar_buffer();system("clear");
                                break;
                                case 'L':
                                    listar_produtos();
                                    printf("Pressione ENTER para continuar...\n");limpar_buffer();system("clear");
                                break;
                                case 'B':
                                    buscar_produtos();
                                    printf("Pressione ENTER para continuar...\n");limpar_buffer();system("clear");
                                break;
                                case 'A':
                                    atualizar_produtos();
                                    printf("Pressione ENTER para continuar...\n");limpar_buffer();system("clear");
                                break;
                                case 'T':
                                    atualizar_estoque();
                                    printf("Pressione ENTER para continuar...\n");limpar_buffer();system("clear");
                                break;
                            }
                            break;


                    case 'E':
                        printf("============== Gerenciar Pedidos ==============\nDigite um comando para prosseguir:\nC – Cadastrar um pedido.\nL – Listar todos os pedidos de um cliente.\nD – Listar todos os pedidos em um dia específico.\n");
                            scanf(" %c",&opcao_menu);system("clear");limpar_buffer();
                            switch(opcao_menu){
                                case 'C':
                                    cadastrar_pedidos();
                                    printf("Pressione ENTER para continuar...\n");limpar_buffer();system("clear");
                                break;
                                case 'L':
                                    listar_pedidos_cliente();
                                    printf("Pressione ENTER para continuar...\n");limpar_buffer();system("clear");
                                break;
                                case 'D':
                                    listar_pedidos_dia();
                                    printf("Pressione ENTER para continuar...\n");limpar_buffer();system("clear");
                                break;
                            }

                        break;


                }
    }while(opcao_menu!='S');

printf("##......................OBRIGADO POR SUA VISITA......................##\n");
        return 0;
}
