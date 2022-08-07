#include <stdlib.h> // inclui bibliotecas a serem usadas
#include <stdio.h>
#include <locale.h>
#include <string.h>

#define TABLESIZE 11 // Define a constante TABLESIZE com seu valor;

// DEFINE MINHAS ESTRUTURAS CUSTOMIZADAS
typedef struct // Define o tipo aluno com seus atributos;
{
    int RU;
    char name[60];
    char email[50];
} Student;

typedef struct hashList // Define o tipo hashlist
{
    Student student;
    struct hashList *next;
} hashList;

typedef struct Table // Define o tipo Table
{
    int size;
    struct hashList **keyList;
} Table;

// ------------ FUNÇÕES
Student readStudentData();                      // Le os dados do estudante
void insert(struct Table *myTable);             /// Função para inserir o aluno na tabela
int hashFunc(int RUnumber);                     /// Função hash, retorna o resto da divisao do numero do RU pelo tamanho da tabela para ser usado como índice
Table initTable();                              // Cria e inicia a tabela
void showHashTable(struct Table *myTable);      // Imprime o que tem em casa posição da hashtable
void hashSearch(struct Table *myTable, int RU); // Busca o número com
void printStudent(Student student);             // Função para imprimir a struct student para evitar repetir código
void pause();                                   // Aguarda algum caractere para continuar
void populateTable(struct Table *myTable);      // Função para popular a tabelaHash com alguns valores pre definidos
int main()
{
    setlocale(LC_ALL, "Portuguese");
    int option, c, num, pos;

    Table myTable = initTable();
    populateTable(&myTable);

    do
    // MENU
    {
        printf("\tMENU PRINCIPAL\n\n");
        printf("(1) - Inserir novo estudante\n");
        printf("(2) - Procurar estudante pelo RU\n");
        printf("(3) - Listar todos os estudantes\n");
        printf("(4) - Encerrar\n\n");
        printf("Digite a opção desejada:\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            system("clear");
            printf("Modo de inserção\n");
            insert(&myTable);
            break;
        case 2:
            system("clear");
            int toSearch;
            printf("Digite o RU do estudante que deseja procurar: ");
            scanf("%d", &toSearch);
            printf("\n");
            hashSearch(&myTable, toSearch);
            break;
        case 3:
            showHashTable(&myTable);
            break;
        }
    } while (option != 4);

    return 0;
}

Student readStudentData()  //Chama o input para ler dados de um estudante
{
    Student myStudent;
    printf("Digite o RU do estudante: ");
    scanf("%d", &myStudent.RU);
    scanf("%*c");
    printf("\n");
    printf("Digite o nome do estudante: ");
    fgets(myStudent.name, 50 - 1, stdin);
    printf("\n");
    printf("Digite o e-mail do estudante: ");
    fgets(myStudent.email, 50 - 1, stdin);
    printf("\n");
    printf("\nDados inseridos com sucesso!\n");
    printStudent(myStudent);
    return myStudent;
}

void insert(struct Table *myTable) //Insere elemento na posição definida pela função hash
{
    Student myStudent = readStudentData();

    int pos = hashFunc(myStudent.RU);

    hashList *newElement;
    newElement = (struct hashList *)malloc(sizeof(struct hashList));
    newElement->student = myStudent;
    newElement->next = NULL;

    newElement->next = myTable->keyList[pos];
    myTable->keyList[pos] = newElement;

    printf("Inserido na posição %d da tabela...\n", pos);
    printf("____________________________________\n");
    printf("\n");
}

Table initTable()  //Inicia Tabela
{
    Table *hashTable = (struct Table *)malloc(sizeof(struct Table));
    hashTable->size = TABLESIZE;
    hashTable->keyList = (struct hashList **)malloc(TABLESIZE * sizeof(struct hashList *));

    for (int i = 0; i < TABLESIZE; i++)
    {
        hashTable->keyList[i] = NULL;
    }

    return *hashTable;
}

int hashFunc(int RUnumber) // Função hash, retorna o resto da divisao do numero do RU pelo tamanho da tabela para ser usado como índice
{
    return RUnumber % TABLESIZE;
}

void showHashTable(struct Table *myTable)  // Imprime elementos contidos em cada posição da tabela HASH
{
    int v;
    for (v = 0; v < myTable->size; v++)
    {
        struct hashList *cursor = myTable->keyList[v];
        printf("\n-----Chaves na posição %d -----\n", v);
        while (cursor != NULL)
        {
            printStudent(cursor->student);
            cursor = cursor->next;
        }
    }
}

void hashSearch(struct Table *myTable, int RU)
{
    // Faz a hash func com o RU e verifica diretamente naquele índice se existe
    // Algum RU igual o que foi passado, se sim imprime se não fala que não encontrou
    int index = hashFunc(RU);
    int err = 0;

    struct hashList *cursor = myTable->keyList[index];
    while (cursor != NULL)
    {
        if (cursor->student.RU == RU)
        {
            printf(" --- ENCONTRADO --- \n");
            printStudent(cursor->student);
            err = 1;
            break;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    if (err == 0)
    {
        printf("Estudante não encontrado, tente novamente!\n");
    }
}

void printStudent(Student student)
{
    printf("\nRU:......%d\n", student.RU);
    printf("Nome:....%s\n", student.name);
    printf("E-mail:..%s", student.email);
    printf("____________________________________\n");
}

void pause()
{
    printf("Pressione ENTER para continuar; \n");
    getchar();
}

void populateTable(struct Table *myTable) //Função para popular meu programa
{
    int RUS[] = {104192, 318940, 47819, 37812, 37819, 37829, 48923, 37821, 33451, 3624104, 1707};
    char names[TABLESIZE][25] = {{"Nicoly"}, {"Lara"}, {"Lana"}, {"Mello"}, {"Camila"}, {"Magda"},
    {"Bella"}, {"Luiz"}, {"Iolanda"}, {"Jean"}, {"Gordon"}};

    for (int i = 0; i < TABLESIZE; i++)
    {
        int pos = hashFunc(RUS[i]);
        char name[25] = "";

        Student tmpStudent = {RUS[i]};
        strcpy(tmpStudent.name, names[i]);
        strcpy(name, names[i]);
        char email[25] = "@gmail.com\n";
        strcpy(tmpStudent.email, strcat(name, email));

        hashList *newElement;
        newElement = (struct hashList *)malloc(sizeof(struct hashList));
        newElement->student = tmpStudent;
        newElement->next = NULL;

        newElement->next = myTable->keyList[pos];
        myTable->keyList[pos] = newElement;
    }
}