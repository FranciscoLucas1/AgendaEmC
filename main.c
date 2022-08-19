// Alunos: Francisco Lucas Benvindo da Silva e lucas Gabriel de Sousa e Silva

#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definção de psesudo constantes
#define maxCon 100
#define tamNome 200
#define tamEnd 90
#define tamNumTel 12
#define tamEmail 60
#define tamRede 50

#define tamSubNome 90
#define tamSubEnd 200
#define tamSubRede 100

// Declaração dos tipos enumerados - Tipo de endereço, tipo de contato e rede
// social.
typedef enum
{
    Alameda = 1,
    Avenida,
    Praca,
    Rua,
    Travessa
} tipoEndereco;

typedef enum
{
    Instagram = 1,
    Facebook,
    Linkedin,
    Outro
} tipoRedeSocial;

typedef enum
{
    Celular = 1,
    Comercial,
    Fixo,
    Pessoal,
    Fax,
    Personalizado
} tipoContato;

// Definição da estrutura da agenda telefônica
typedef struct estruturaAgenda
{
    char nome[tamNome];
    tipoEndereco tEnd;
    char endereco[tamEnd];
    int numeroEnd;
    char numeroTel[tamNumTel];
    tipoContato tpContato;
    char email[tamEmail];
    char redeSocial[tamRede];
    tipoRedeSocial tipoRedeSocial;
} Agenda;

Agenda contato[maxCon];

// Definição das funções do programa
void limparTela(void);
int addContato(int id);
void mostrarContatos(int id, int quantidade, char nome[], char endereco[],
                     char rede[]);
int deletarContato(int id, int quantidade);
void buscarContato(int id, int quantidade);
void editarContato(int id, int quantidade);
int menu();
char confirmarNovoContato(char msg[]);
char *obterTipoEndereco(tipoEndereco tEnd);
char *obterTipoContato(tipoContato tpContato);
char *obterRedeSocial(tipoRedeSocial redeSocial);
int verificarEmail(int id, char *email);
int verificarTelefone(int id, char *telefone);
int verificarEndereco(int id, char *endereco);
void menuRedes();
void menuTipoEnd();
void menuEdicao();
void menuTipoContato();

void salvarNoArquivo(int id)
{

    FILE *ptrArquivo = NULL;
    ptrArquivo = fopen("minhaAgenda.csv", "w");

    if (ptrArquivo == NULL)
    {
        printf("Erro ao abrir o arquivo. Finalizando programa...\n");
        exit(0);
    }

    for (int i = 0; i < id; i++)
    {
        fprintf(ptrArquivo, "%s;%i;%i;%s;%i;%s;%s;%i;%s;\n",
                contato[i].nome,
                contato[i].tpContato, contato[i].tEnd, contato[i].endereco, contato[i].numeroEnd, contato[i].numeroTel, contato[i].email, contato[i].tipoRedeSocial, contato[i].redeSocial);
    }

    fclose(ptrArquivo);
    ptrArquivo = NULL;
}

int lerDoArquivo()
{

    FILE *ptrArquivo = NULL;
    ptrArquivo = fopen("minhaAgenda.csv", "r");

    int cont = 0, aux, id;
    char *token;
    char l[100];

    while ((fgets(l, sizeof(l), ptrArquivo)) != NULL)
    {
        token = strtok(l, ";");

        strcpy(contato[cont].nome, token);
        token = strtok(NULL, ";");

        contato[cont].tpContato = atoi(token);
        token = strtok(NULL, ";");
        contato[cont].tEnd = atoi(token);
        token = strtok(NULL, ";");
        strcpy(contato[cont].endereco, token);
        token = strtok(NULL, ";");
        contato[cont].numeroEnd = atoi(token);
        token = strtok(NULL, ";");
        strcpy(contato[cont].numeroTel, token);
        token = strtok(NULL, ";");
        strcpy(contato[cont].email, token);
        token = strtok(NULL, ";");
        contato[cont].tipoRedeSocial = atoi(token);
        token = strtok(NULL, ";");
        strcpy(contato[cont].redeSocial, token);
        token = strtok(NULL, ";");

        cont++;
    }

    fclose(ptrArquivo);
    ptrArquivo = NULL;

    return cont;
}

// Execução 'Função Principal'
int main()
{
    int opcao;
    int id = lerDoArquivo();
    int quantidade = id;
    char subStrNome[tamSubNome];
    char subStrEnd[tamSubEnd];
    char subStrRede[tamSubRede];

    setlocale(LC_ALL, "");

    do
    {
        opcao = menu();

        limparTela();
        switch (opcao)
        {
        case 0:
            printf(" Finalizando aplicação...\n");
            salvarNoArquivo(id);
            break;
        case 1:
            limparTela();
            printf("\nVocê selecionou a opção para inserir um contato!\n");
            id = addContato(id);
            quantidade = id;
            break;
        case 2:
            limparTela();
            printf("\nVocê selecionou a opção de editar um contato!\n");
            editarContato(id, quantidade);
            break;
        case 3:
            limparTela();
            printf("\nVocê selecionou a opção de consultar um contato!\n");
            buscarContato(id, quantidade);
            break;
        case 4:
            limparTela();
            printf("\nVocê selecionou a opção de excluir um contato!\n");
            limparTela();
            quantidade = deletarContato(id, quantidade);
            id = quantidade;
            break;
        case 5:
            limparTela();
            printf("\nVocê selecionou a opção de listar todos os contatos!\n");
            mostrarContatos(id, quantidade, subStrNome, subStrEnd, subStrRede);
            break;
        }
    } while (opcao != 0);
}

int addContato(int id)
{

    int continuar;
    char confirmacao = 's';
    do
    {
        menuTipoContato();

        printf("Digite o tipo de contato: ");
        scanf("%i", &contato[id].tpContato);

        if (contato[id].tpContato < 1 || contato[id].tpContato > 6)
        {
            printf("Opção inválida. Digite somente opções de 1 a 6. (\n");
        }

        while (contato[id].tpContato < 1 || contato[id].tpContato > 6)
        {
            printf("Digite o tipo de contato: ");
            scanf("%i", &contato[id].tpContato);
        }

        printf("Digite o nome do contato: ");
        fflush(stdin);
        scanf(" %[^\n]s", contato[id].nome);

        menuTipoEnd();

        printf("Digite o tipo de endereço: ");
        scanf("%i", &contato[id].tEnd);

        if (contato[id].tEnd < 1 || contato[id].tEnd > 5)
        {
            printf("Opção inválida. Digite somente opções de 1 a 5. \n");
        }
        while (contato[id].tEnd < 1 || contato[id].tEnd > 5)
        {
            printf("Digite o tipo de endereço: ");
            scanf("%i", &contato[id].tEnd);
        }

        printf("Insira o endereço: ");
        scanf(" %[^\n]s", contato[id].endereco);

        if (verificarEndereco(id, contato[id].endereco) == 0)
        {
            printf("O endereço não pode ser composto somente por números\n");
        }
        while (verificarEndereco(id, contato[id].endereco) == 0)
        {
            printf("Insira o endereço: ");
            fflush(stdin);
            scanf(" %[^\n]s", contato[id].endereco);
        }

        printf("Insira o número do endereço: ");
        scanf("%i", &contato[id].numeroEnd);

        fflush(stdin);
        printf("Insira o número de telefone: ");
        scanf("%11[0123456789]s", contato[id].numeroTel);

        fflush(stdin);
        printf("Insira o email do contato: ");
        scanf("%[^\n]s", contato[id].email);

        if (verificarEmail(id, contato[id].email) == 0)
        {
            printf("E-mail invalido, por favor utilize emails com o caractere @.\n");
        }
        while (verificarEmail(id, contato[id].email) == 0)
        {
            printf("Insira o email do contato: ");
            scanf("%[^\n]s", contato[id].email);
        }

        printf("Escolha uma rede social: \n");
        menuRedes();

        scanf("%i", &contato[id].tipoRedeSocial);

        if (contato[id].tipoRedeSocial < 1 || contato[id].tipoRedeSocial > 4)
        {
            printf("Opção inválida. Digite somente opções de 1 a 4. \n");
        }
        while (contato[id].tipoRedeSocial < 1 || contato[id].tipoRedeSocial > 4)
        {
            printf("Digite o tipo da rede social: ");
            scanf("%i", &contato[id].tipoRedeSocial);
        }

        printf("Digite o link para sua rede social: ");
        scanf(" %[^\n]s", contato[id].redeSocial);

        printf("Deseja realmente adicionar esse contato? (S/N)\n");
        scanf("%s", &confirmacao);

        if (confirmacao == 's')
        {
            id++;
            printf("Contato adicionado com sucesso.\n");
        }
        else
        {
            printf("Adição cancelada.\n");
        }

        continuar =
            confirmarNovoContato("Para inserir outro contato digite (S/N)  \n");

        limparTela();
    } while (continuar == 's');
    return id;
}

int menu()
{
    int opcao;
    printf("\n\nMenu: Agenda telefônica\n");
    printf("* 1 - Inserir um contato *\n");
    printf("* 2 - Alterar um contato *\n");
    printf("* 3 - Buscar por um contato *\n");
    printf("* 4 - Excluir contato *\n");
    printf("* 5 - Listar contatos cadastrados *\n");
    printf("* 0 - Sair *\n");

    printf("\nDigite uma opção: ");
    scanf("%i", &opcao);

    if (opcao < 0 || opcao > 5)
    {
        printf("Opção inválida. Digite somente opções  de 0 a 5. \n");
    }
    while (opcao < 0 || opcao > 5)
    {
        printf("Digite uma opção: ");
        scanf("%i", &opcao);
    }
    return opcao;
}

char confirmarNovoContato(char msg[])
{
    char cont;
    printf("%s", msg);
    do
    {
        fflush(stdin);
        cont = tolower(getchar());

        if ((cont != 's') && (cont != 'n'))
        {
            printf("Deseja inserir outro contato (S/N) ? \n");
        }
    } while ((cont != 's') && (cont != 'n'));

    return cont;
}

void mostrarContatos(int id, int quantidade, char nome[], char endereco[],
                     char rede[])

{

    printf("%i", id);
    if (quantidade == 0)
    {
        printf("Não há contatos cadastrados na sua agenda.\n\n");
    }
    else
    {
        printf("Exibindo todos os contatos:\n\n");

        for (int i = 0; i < id; i++)
        {
            strncpy(nome, contato[i].nome, 15);

            sprintf(endereco, "%s %s, %i", obterTipoEndereco(contato[i].tEnd),
                    contato[i].endereco, contato[i].numeroEnd);

            sprintf(rede, "%s - %s", contato[i].redeSocial,
                    obterRedeSocial(contato[i].tipoRedeSocial));

            printf("%-15s | %-20s | %20s | %20s | %20s | %20s \n", nome,
                   obterTipoContato(contato[i].tpContato), endereco,
                   contato[i].numeroTel, contato[i].email, rede);
        }
    }
}
// Funções para pegar o valor do Enum e transformar em uma string para a visualização do usuário linha 398 a 419
char *obterTipoContato(tipoContato tpContato)
{
    char *tipoDeContato[] = {"", "Celular", "Comercial", "Fixo",
                             "Pessoal", "Fax", "Personalizado"};

    return (tipoDeContato[tpContato]);
}

char *obterTipoEndereco(tipoEndereco tEnd)
{
    char *tipoDeEndereco[] = {"", "Al.", "Av.", "Pr.", "R.", "Trav."};

    return (tipoDeEndereco[tEnd]);
}

char *obterRedeSocial(tipoRedeSocial redeSocial)
{
    char *RedeSocial[] = {"", "Instagram", "Facebook", "Linkendin", "Outros"};

    return (RedeSocial[redeSocial]);
}

// Função para verificar se o e-mail contém @
int verificarEmail(int id, char *email)
{

    const char *enderecoEmail = email;
    char *verificar;

    verificar = strstr(enderecoEmail, "@");
    if (verificar)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// Função para verificar se o endereço contem somente dígitos
// função isdigit retorna um valor diferente de 0 se houver dígitos, caso não ele retorna 0
int verificarEndereco(int id, char *endereco)
{
    for (int i = 0; i <= strlen(endereco); i++)
    {
        if (isdigit(endereco[i]))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

int deletarContato(int id, int quantidade)
{
    char confirmacao = 's';
    char nome[tamNome];
    int encontrado = 0;
    int i = 0;

    printf("Digite o nome do contato que deseja excluir: ");
    scanf(" %[^\n]s", nome);

    for (i = 0; i < id; i++)
    {
        if (strcmp(nome, contato[i].nome) == 0)
        {
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 1)
    {
        printf("Contato encontrado.\n\n");
        printf("Nome: %s\n", contato[i].nome);
        printf("Tipo: %s\n", obterTipoContato(contato[i].tpContato));
        printf("Endereço do contato: %s %s, %i\n",
               obterTipoEndereco(contato[i].tEnd), contato[i].endereco,
               contato[i].numeroEnd);
        printf("Número de telefone: %s\n", contato[i].numeroTel);
        printf("Email: %s\n", contato[i].email);
        printf("Rede social: %s - %s\n", contato[i].redeSocial,
               obterRedeSocial(contato[i].tipoRedeSocial));

        fflush(stdin);
        printf("Deseja realmente excluir este contato? (S/N)\n");
        scanf("%s", &confirmacao);

        if (confirmacao == 's')
        {
            for (int j = i; j < id; j++)
            {
                contato[j] = contato[j + 1];
            }
            id--;
            quantidade--;
            printf("Contato excluído com sucesso.\n");
        }
        else
        {
            printf("Contato não excluído.\n");
        }
    }
    else
    {
        printf("Contato não encontrado.\n\n");
    }

    return quantidade;
}

void buscarContato(int id, int quantidade)
{

    if (quantidade == 0)
    {

        printf("Não há contatos para serem buscados.\n");
    }

    char nome[200];
    int encontrado = 0;
    int i;

    printf("Digite o nome do contato que deseja buscar: ");
    scanf(" %[^\n]s", nome);

    for (i = 0; i < id; i++)
    {
        if (strcmp(nome, contato[i].nome) == 0)
        {
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 1)
    {
        printf("Contato encontrado.\n\n");
        printf("Nome: %s\n", contato[i].nome);
        printf("Tipo: %s\n", obterTipoContato(contato[i].tpContato));
        printf("Endereço do contato: %s %s, %i\n",
               obterTipoEndereco(contato[i].tEnd), contato[i].endereco,
               contato[i].numeroEnd);
        printf("Número de telefone: %s\n", contato[i].numeroTel);
        printf("Email: %s\n", contato[i].email);
        printf("Rede social: %s - %s\n", contato[i].redeSocial,
               obterRedeSocial(contato[i].tipoRedeSocial));
    }
    else
    {
        printf("Contato não encontrado.\n");
    }
}

void editarContato(int id, int quantidade)
{
    char confirmacao = 's';
    char nome[tamNome];
    int encontrado = 0;
    int i = 0;
    int opc;

    printf("Digite o nome do contato que deseja editar: ");
    scanf(" %[^\n]s", nome);

    for (i = 0; i < id; i++)
    {
        if (strcmp(nome, contato[i].nome) == 0)
        {
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 1)
    {

        printf("Contato encontrado.\n\n");
        printf("Nome: %s\n", contato[i].nome);
        printf("Tipo: %s\n", obterTipoContato(contato[i].tpContato));
        printf("Endereço do contato: %s %s, %i\n",
               obterTipoEndereco(contato[i].tEnd), contato[i].endereco,
               contato[i].numeroEnd);
        printf("Número de telefone: %s\n", contato[i].numeroTel);
        printf("Email: %s\n", contato[i].email);
        printf("Rede social: %s - %s\n", contato[i].redeSocial,
               obterRedeSocial(contato[i].tipoRedeSocial));

        fflush(stdin);
        printf("Deseja realmente editar este contato? (S/N): \n");
        scanf("%s", &confirmacao);
        i++;
        if (confirmacao == 's')
        {

            menuEdicao();

            printf("Digite uma opção: ");
            scanf("%i", &opc);

            if (opc < 1 || opc > 9)
            {
                printf("Opção inválida. Digite somente opções  de 1 a 9. \n");
            }
            while (opc < 1 || opc > 9)
            {
                printf("Digite uma opção: ");
                scanf("%i", &opc);
            }

            switch (opc)
            {
            case 1:
                limparTela();
                printf("\nVocê selecionou alterar nome do contato\n");
                printf("Digite o novo nome do contato: ");
                scanf(" %[^\n]s", contato[i].nome);
                break;
            case 2:
                limparTela();
                printf("\nVocê selecionou alterar tipo do contato!\n");

                menuTipoContato();

                printf("Digite o tipo de contato: ");
                scanf("%i", &contato[i].tpContato);

                if (contato[i].tpContato < 1 || contato[i].tpContato > 6)
                {
                    printf("Opção inválida. Digite somente opções de 1 a 6. \n");
                }
                while (contato[i].tpContato < 1 || contato[i].tpContato > 6)
                {
                    printf("Digite o tipo de contato: ");
                    scanf("%i", &contato[i].tpContato);
                }

                break;
            case 3:
                limparTela();
                printf("\nVocê selecionou alterar endereço do contato!\n");

                printf("Digite o novo endereço do contato: ");
                scanf(" %[^\n]s", contato[i].endereco);

                if (verificarEndereco(id, contato[i].endereco) == 0)
                {
                    printf("O endereço não pode ser composto somente por números\n");
                }
                while (verificarEndereco(id, contato[i].endereco) == 0)
                {
                    printf("Insira o endereço: ");
                    fflush(stdin);
                    scanf(" %[^\n]s", contato[i].endereco);
                }

                break;
            case 4:
                limparTela();
                printf("\nVocê selecionou alterar tipo do endereço\n");

                menuTipoEnd();

                printf("Digite o tipo de endereço: ");
                scanf("%i", &contato[i].tEnd);

                if (contato[i].tEnd < 1 || contato[i].tEnd > 5)
                {
                    printf("Opção inválida. Digite somente opções de 1 a 5. \n");
                }
                while (contato[i].tEnd < 1 || contato[i].tEnd > 5)
                {
                    printf("Digite o tipo de endereço: ");
                    scanf("%i", &contato[i].tEnd);
                }
                break;
            case 5:
                limparTela();
                printf("\nVocê selecionou alterar número do endereço!\n");

                printf("Digite o novo número de endereço do contato: ");
                scanf(" %i", &contato[i].numeroEnd);

                break;
            case 6:
                limparTela();
                printf("\nVocê selecionou alterar número do telefone!\n");

                printf("Digite o novo número de telefone: ");
                scanf("% 11[0123456789]s", contato[i].numeroTel);

                break;
            case 7:
                limparTela();
                printf("\nVocê selecionou alterar e-mail do contato!\n");

                printf("Digite o novo email do contato: ");
                scanf(" %[^\n]s", contato[i].email);

                if (verificarEmail(id, contato[i].email) == 0)
                {
                    printf(
                        "E-mail invalido, por favor utilize emails com o caractere @.\n");
                }
                while (verificarEmail(id, contato[i].email) == 0)
                {
                    printf("Insira o email do contato: ");
                    scanf("%s", contato[i].email);
                }

                break;
            case 8:
                limparTela();
                printf("\nVoce selecionou alterar tipo da rede social\n");

                menuRedes();

                printf("Digite o novo tipo de rede social: ");
                scanf(" %i", &contato[i].tipoRedeSocial);

                if (contato[i].tipoRedeSocial < 1 || contato[i].tipoRedeSocial > 4)
                {
                    printf("opção inválida. Digite somente opções de 1 a 4. \n");
                }
                while (contato[i].tipoRedeSocial < 1 || contato[i].tipoRedeSocial > 4)
                {
                    printf("Digite o tipo da rede social: ");
                    scanf("%i", &contato[i].tipoRedeSocial);
                }

                break;
            case 9:
                limparTela();
                printf("\nVocê selecionou alterar usuario da rede social\n");

                printf("Digite o novo nome da rede social: ");
                scanf(" %[^\n]s", contato[i].redeSocial);

                break;
            }
            printf("Contato editado com sucesso.\n");
        }
        else
        {
            printf("Edição cancelada. \n");
        }
    }
    else
    {
        printf("Contato não encontrado.\n");
    }
}

// Funções simples para a exibição de de menus (l 717 a 759)
void menuRedes()
{

    printf("* 1 - Instagram \n");
    printf("* 2 - Facebook \n");
    printf("* 3 - Linkendin \n");
    printf("* 4 - Outro \n");
}

void menuTipoEnd()
{

    printf("* 1 - Alameda \n");
    printf("* 2 - Avenida \n");
    printf("* 3 - Praça \n");
    printf("* 4 - Rua \n");
    printf("* 5 - Travessa \n");
}

void menuTipoContato()
{

    printf("* 1 - Celular \n");
    printf("* 2 - Comercial \n");
    printf("* 3 - Fixo \n");
    printf("* 4 - Pessoal \n");
    printf("* 5 - Fax \n");
    printf("* 6 - Personalizado \n");
}

void menuEdicao()
{

    printf("1 - Alterar nome do contato\n");
    printf("2 - Alterar tipo do contato\n");
    printf("3 - Alterar endereço do contato\n");
    printf("4 - Alterar tipo do endereço\n");
    printf("5 - Alterar número do endereço\n");
    printf("6 - Alterar número de telefone\n");
    printf("7 - Alterar e-mail do contato\n");
    printf("8 - Alterar a rede social do usuário\n");
    printf("9 - Alterar usuário da rede social\n");
}

// Limpeza de tela para deixar a exibição visual do programa mais limpa
void limparTela(void)
{
#ifdef __linux__
    system("clear");
#elif _WIN32
    system("cls");
#endif
}
