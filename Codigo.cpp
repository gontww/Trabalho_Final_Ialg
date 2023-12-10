/*TRABALHO FINAL DE INTRODUÇÃO AOS ALGORITMOS - UNIVERSIDADE FEDERAL DE LAVRAS

TEMA: FICHAS HOSPITALARES

INTEGRANTES:
AUGUSTO ANTÔNIO COSTA GONTIJO
JOÃO MARCUS LEITE DA SILVA
CARLOS EDUARDO BORGES DE SOUSA
*/
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct FichaHosp
{
    int identificador;
    char nome[30];
    char genero;
    float altura;
    float peso;
    char patologia[30];
};

void aumentarCapacidade(FichaHosp *&Paciente, int &capacidade, int &tamanho) // PROCEDIMENTO PARA REDIMENSIONAR DE 1 EM 1 A CAPACIDADE DO VETOR
{
    FichaHosp *Pivo = new FichaHosp[capacidade + 1];
    for (int i = 0; i < tamanho; i++)
    {
        Pivo[i] = Paciente[i];
    }
    for (int i = tamanho; i < capacidade + 1; i++)
    {
        Pivo[i] = {};
    }
    delete[] Paciente;
    Paciente = Pivo;
    capacidade += 1;
}

void imprimirLista(FichaHosp Paciente[], int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        cout << Paciente[i].identificador << " " << Paciente[i].nome << " "
             << Paciente[i].genero << " " << Paciente[i].peso << "kg "
             << Paciente[i].altura << "m " << Paciente[i].patologia << endl
             << endl;
    }
}

void buscarNomePaciente(FichaHosp Paciente[], int tamanho, char nomeBuscado[]) // BUSCA NOME DE PACIENTE USANDO "strstr", FUTURAMENTE CRIAREMOS UMA FUNCAO PARA DEIXAR TUDO MINUSCULO ANTES DO strstr
{
    int j = 0;
    char *ptr;
    int nomesEncontrados[tamanho];

    for (int i = 0; i < tamanho; i++)
    {
        ptr = strstr(Paciente[i].nome, nomeBuscado);
        if (ptr)
        {
            nomesEncontrados[j] = i;
            j++;
        }
    }
    if (j == 0)
    {
        cout << "Nao foi encontrado nenhum paciente com esse nome." << endl;
    }
    else
    {
        cout << "Fichas dos pacientes com esse nome: " << endl;
        for (int k = 0; k < j; k++)
        {
            cout << Paciente[nomesEncontrados[k]].identificador << " "
                 << Paciente[nomesEncontrados[k]].nome << " "
                 << Paciente[nomesEncontrados[k]].genero << " "
                 << Paciente[nomesEncontrados[k]].peso << " "
                 << Paciente[nomesEncontrados[k]].altura << " "
                 << Paciente[nomesEncontrados[k]].patologia << endl;
        }
        cout << endl;
    }
}
void buscarIDPaciente(FichaHosp Paciente[], int tamanho, int idBuscado) // BUSCA IDENTIFICADOR SOLICITADO POR BUSCA BINARIA
{
    if (idBuscado > 0 and idBuscado <= tamanho - 1)
    {
        int esquerda = 0;
        int direita = tamanho;
        bool encontrou = false;
        while (esquerda <= direita and encontrou == false)
        {
            int meio = (esquerda + direita) / 2;
            if (idBuscado == meio)
            {
                cout << Paciente[meio - 1].identificador << " "
                     << Paciente[meio - 1].nome << " " << Paciente[meio - 1].genero
                     << " " << Paciente[meio - 1].peso << " "
                     << Paciente[meio - 1].altura << " " << Paciente[meio - 1].patologia
                     << endl
                     << endl;
                encontrou = true;
            }
            else if (idBuscado > meio)
            {
                esquerda = meio + 1;
            }
            else if (idBuscado < meio)
            {
                direita = meio - 1;
            }
        }
    }
    else
    {
        cout << "Digite um numero valido: ";
        cin >> idBuscado;
        buscarIDPaciente(Paciente, tamanho, idBuscado);
    }
}
void addPaciente(FichaHosp *&Paciente, int &capacidade, int &tamanho) // ADICAO DE PACIENTE VIA TECLADO, COM REDIMENSIONAMENTO SE NECESSARIO
{
    if (tamanho >= capacidade)
    {
        aumentarCapacidade(Paciente, capacidade, tamanho);
    }
    cout << "Digite os dados do novo paciente:" << endl;
    cout << "Identificador: " << tamanho << endl;
    Paciente[tamanho - 1].identificador = tamanho;

    cout << "Nome: ";
    cin.ignore();
    cin.getline(Paciente[tamanho - 1].nome, 30);

    cout << "Genero: ";
    cin >> Paciente[tamanho - 1].genero;

    cout << "Peso: ";
    cin >> Paciente[tamanho - 1].peso;

    cout << "Altura: ";
    cin >> Paciente[tamanho - 1].altura;

    cout << "Patologia: ";
    cin.ignore();
    cin.getline(Paciente[tamanho - 1].patologia, 30);
    tamanho++;
}
void salvarBinarioCsv(FichaHosp *&Paciente, int tamanho) // GRAVA OS VETORES EM ARQUIVOS BINARIO E CSV
{
    ofstream arqBin("registroBinarioNovo.bin", ios::binary);
    ofstream arqS("registroNovo.csv");
    for (int i = 0; i < tamanho - 1; i++)
    {
        arqBin.write((char *)&Paciente[i], sizeof(FichaHosp));
    }
    for (int i = 0; i < tamanho - 1; i++)
    {
        char virgula = ',';
        arqS << Paciente[i].identificador;
        arqS << virgula;
        arqS.write(Paciente[i].nome, strlen(Paciente[i].nome));
        arqS << virgula;
        arqS << Paciente[i].genero;
        arqS << virgula;
        arqS << Paciente[i].peso;
        arqS << virgula;
        arqS << Paciente[i].altura;
        arqS << virgula;
        arqS.write(Paciente[i].patologia, strlen(Paciente[i].patologia));
        arqS << virgula << endl;
    }
    cout << "Foi criado com a lista atual de Pacientes um novo .csv  e um arquivo binario, nomeados respectivamente: 'registroNovo.csv' 'registroBinarioNovo.bin'." << endl;
}
void menu1ou0(int capacidade, int tamanho, FichaHosp *Paciente);
void removerPaciente(FichaHosp Paciente[], int &tamanho, int capacidade);
void pesquisarParte(int tamanho, FichaHosp *Paciente, int capacidade);
void ordenarLista(int tamanho, FichaHosp *Paciente)
{
    int gaps[9] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int posgap = 8;
    int escolha;
    cout << "Deseja ordenar entre:" << endl
         << "[1] Nome" << endl
         << "[2] Peso" << endl
         << "[3] Altura" << endl;
    cin >> escolha;
    switch (escolha)
    {
    case 1:
        while (gaps[posgap] >= tamanho - 1)
        {
            posgap--;
        }
        while (posgap >= 0)
        {
            int gap = gaps[posgap];
            for (int i = gap; i < tamanho - 1; i++)
            {
                FichaHosp aux;
                aux = Paciente[i];
                int j = i;

                while (j >= gap and strcmp(Paciente[j - gap].nome, aux.nome) > 0)
                {
                    Paciente[j] = Paciente[j - gap];
                    j = j - gap;
                }
                Paciente[j] = aux;
            }
            posgap--;
        }
        break;
    case 2:
        while (gaps[posgap] >= tamanho - 1)
        {
            posgap--;
        }
        while (posgap >= 0)
        {
            int gap = gaps[posgap];
            for (int i = gap; i < tamanho - 1; i++)
            {
                FichaHosp aux;
                aux = Paciente[i];
                int j = i;

                while (j >= gap and Paciente[j - gap].peso > aux.peso)
                {
                    Paciente[j] = Paciente[j - gap];
                    j = j - gap;
                }
                Paciente[j] = aux;
            }
            posgap--;
        }
        break;
    case 3:
        while (gaps[posgap] >= tamanho - 1)
        {
            posgap--;
        }
        while (posgap >= 0)
        {
            int gap = gaps[posgap];
            for (int i = gap; i < tamanho - 1; i++)
            {
                FichaHosp aux;
                aux = Paciente[i];
                int j = i;

                while (j >= gap and Paciente[j - gap].altura > aux.altura)
                {
                    Paciente[j] = Paciente[j - gap];
                    j = j - gap;
                }
                Paciente[j] = aux;
            }
            posgap--;
        }
    default:
        break;
    }
}
void menuPrincipal(int capacidade, int tamanho, FichaHosp *Paciente) // MENU DE ESCOLHA QUE É APRESENTADO AS FUNCIONALIDADES DO CODIGO, CHAMA A FUNÇAO "menu1ou0" APOS O 'CASE' FINALIZAR
{
    int escolha;
    cout << "ESCOLHA O QUE DESEJA FAZER:" << endl
         << "[1] IMPRIMIR FICHA DOS PACIENTES" << endl
         << "[2] PESQUISAR NOME DE PACIENTE" << endl
         << "[3] BUSCAR POR IDENTIFICADOR DO PACIENTE" << endl
         << "[4] ADICIONAR PACIENTE" << endl
         << "[5] SALVAR LISTA ATUAL EM BINARIO E CSV" << endl
         << "[6] REMOVER PACIENTE" << endl
         << "[7] PESQUISAR DENTRO DE UMA FAIXA DE INFORMACAO" << endl
         << "[8] ORDENAR A LISTA DE OUTRA MANEIRA" << endl
         << "[0] FECHAR O PROGRAMA" << endl;
    cin >> escolha;
    switch (escolha)
    {
    case 1:
        imprimirLista(Paciente, tamanho);
        menu1ou0(capacidade, tamanho, Paciente);
        break;
    case 2:
        char nomeBuscado[30];
        cout << "Digite o nome que deseja pesquisar: ";
        cin >> nomeBuscado;
        buscarNomePaciente(Paciente, capacidade, nomeBuscado);
        menu1ou0(capacidade, tamanho, Paciente);
        break;
    case 3:
        int idBuscado;
        cout << "Digite o numero de identificacao: ";
        cin >> idBuscado;
        buscarIDPaciente(Paciente, capacidade, idBuscado);
        menu1ou0(capacidade, tamanho, Paciente);
        break;
    case 4:
        addPaciente(Paciente, capacidade, tamanho);
        menu1ou0(capacidade, tamanho, Paciente);
        break;
    case 5:
        salvarBinarioCsv(Paciente, tamanho);
        menu1ou0(capacidade, tamanho, Paciente);
        break;
    case 6:
        removerPaciente(Paciente, tamanho, capacidade);
        break;
    case 7:
        pesquisarParte(tamanho, Paciente, capacidade);
        break;
    case 8:
        ordenarLista(tamanho, Paciente);
        menu1ou0(capacidade, tamanho, Paciente);
        break;
    default:
        break;
    }
}
void menu1ou0(int capacidade, int tamanho, FichaHosp *Paciente) // ESSA FUNÇAO RETORNA O USUARIO AO MENU PRINCIPAL OU FINALIZA O PROGRAMA
{
    int escolha;
    cout << "ESCOLHA O QUE DESEJA FAZER:" << endl
         << "[1] VOLTAR PARA O MENU PRINCIPAL" << endl
         << "[0] FECHAR PROGRAMA" << endl;
    cin >> escolha;
    switch (escolha)
    {
    case 1:
        menuPrincipal(capacidade, tamanho, Paciente);
        break;

    case 0:
        break;
    }
}
void pesquisarParte(int tamanho, FichaHosp *Paciente, int capacidade) // FUNCAO QUE BUSCA DENTRO DE UMA FAIXA NUMEROS QUE O USUARIO DESEJA
{
    int escolha;
    cout << "Deseja pesquisar entre:" << endl
         << "[1] Posicao no vetor" << endl
         << "[2] Peso" << endl
         << "[3] Altura" << endl;
    cin >> escolha;
    switch (escolha)
    {
    case 1:
    {
        int inicioID, fimID;
        cout << "Deseja pesquisar em qual faixa de IDs? (entre 1 e " << tamanho - 1 << ")\n";
        cout << "Inicio: ";
        cin >> inicioID;
        cout << "Fim: ";
        cin >> fimID;
        if (inicioID <= fimID and fimID <= tamanho - 1 and inicioID > 0)
        {
            for (int i = inicioID; i <= fimID; i++)
            {
                cout << Paciente[i - 1].identificador << " " << Paciente[i - 1].nome << " "
                     << Paciente[i - 1].genero << " " << Paciente[i - 1].peso << "kg "
                     << Paciente[i - 1].altura << "m " << Paciente[i - 1].patologia << endl
                     << endl;
            }
        }
        cout << "Deseja pesquisar novamente ou voltar para o Menu?\n";
        cout << "[1] Pesquisar" << endl
             << "[0] Voltar" << endl;
        int escolha2ID;
        cin >> escolha2ID;
        switch (escolha2ID)
        {
        case 1:
            pesquisarParte(tamanho, Paciente, capacidade);
            break;

        default:
            menuPrincipal(capacidade, tamanho, Paciente);
            break;
        }
        break;
    }

    case 2:
    {
        float inicioP, fimP;
        int achouPESO = 0;
        cout << "Deseja pesquisar em qual faixa de peso?\n";
        cout << "Inicio: ";
        cin >> inicioP;
        cout << "Fim: ";
        cin >> fimP;
        if (inicioP <= fimP)
        {
            for (int i = 1; i < tamanho; i++)
            {
                if (Paciente[i - 1].peso >= inicioP and Paciente[i - 1].peso <= fimP)
                {
                    achouPESO += 1;
                    cout << Paciente[i - 1].identificador << " " << Paciente[i - 1].nome << " "
                         << Paciente[i - 1].genero << " " << Paciente[i - 1].peso << "kg "
                         << Paciente[i - 1].altura << "m " << Paciente[i - 1].patologia << endl
                         << endl;
                }
            }
        }
        if (achouPESO == 0)
        {
            cout << "Não foi encontrado nenhum paciente dentro desta faixa!" << endl;
        }
        cout << "Deseja pesquisar novamente ou voltar para o Menu?\n";
        cout << "[1] Pesquisar" << endl
             << "[0] Voltar" << endl;
        int escolha2;
        cin >> escolha2;
        switch (escolha2)
        {
        case 1:
        {
            pesquisarParte(tamanho, Paciente, capacidade);
            break;
        }
        default:
            menuPrincipal(capacidade, tamanho, Paciente);
            break;
        }
        break;
    }
    case 3:
    {
        float inicioA, fimA;
        int achouA = 0;
        cout << "Deseja pesquisar em qual faixa de peso?\n";
        cout << "Inicio: ";
        cin >> inicioA;
        cout << "Fim: ";
        cin >> fimA;
        if (inicioA <= fimA)
        {
            for (int i = 1; i < tamanho; i++)
            {
                if (Paciente[i - 1].altura >= inicioA and Paciente[i - 1].altura <= fimA)
                {
                    achouA += 1;
                    cout << Paciente[i - 1].identificador << " " << Paciente[i - 1].nome << " "
                         << Paciente[i - 1].genero << " " << Paciente[i - 1].peso << "kg "
                         << Paciente[i - 1].altura << "m " << Paciente[i - 1].patologia << endl
                         << endl;
                }
            }
        }
        if (achouA == 0)
        {
            cout << "Não foi encontrado nenhum paciente dentro desta faixa!" << endl;
        }
        cout << "Deseja pesquisar novamente ou voltar para o Menu?\n";
        cout << "[1] Pesquisar" << endl
             << "[0] Voltar" << endl;
        int escolha3;
        cin >> escolha3;
        switch (escolha3)
        {
        case 1:
        {
            pesquisarParte(tamanho, Paciente, capacidade);
            break;
        }
        default:
            menuPrincipal(capacidade, tamanho, Paciente);
            break;
        }
        break;
    }
    break;
    }
}
void removerPaciente(FichaHosp Paciente[], int &tamanho, int capacidade) // FUNÇAO DE REMOVER PACIENTE
{
    int idRemover;
    cout << "Digite o identificador do Paciente que deseja remover (entre 1 e " << tamanho - 1 << "): ";
    cin.ignore();
    cin >> idRemover;
    if (idRemover > 0 and idRemover < tamanho)
    {
        cout << endl
             << "Identificador: " << Paciente[idRemover - 1].identificador << endl
             << "Nome: " << Paciente[idRemover - 1].nome << endl
             << "Genero: " << Paciente[idRemover - 1].genero << endl
             << "Peso: " << Paciente[idRemover - 1].peso << "kg" << endl
             << "Altura: " << Paciente[idRemover - 1].altura << "m" << endl
             << "Patologia: " << Paciente[idRemover - 1].patologia << endl;

        cout << "Deseja remover este paciente?" << endl
             << "[S/N]" << endl;
        char SimOuNao;
        cin >> SimOuNao;
        if (SimOuNao == 'S' or SimOuNao == 's')
        {
            for (int i = idRemover; i < tamanho; i++)
            {
                strcpy(Paciente[i - 1].nome, Paciente[i].nome);
                Paciente[i - 1].genero = Paciente[i].genero;
                Paciente[i - 1].peso = Paciente[i].peso;
                Paciente[i - 1].altura = Paciente[i].altura;
                strcpy(Paciente[i - 1].patologia, Paciente[i].patologia);
            }
            tamanho--;
            for (int i = 0; i < tamanho; i++)
            {
                Paciente[i].identificador = i + 1;
            }
            cout << "Paciente removido!" << endl;
            menu1ou0(capacidade, tamanho, Paciente);
        }
        else if (SimOuNao == 'N' or SimOuNao == 'n')
        {
            cout << "Deseja remover outro Paciente?" << endl
                 << "[S/N]" << endl;
            char SairOuNao;
            cin >> SairOuNao;
            if (SairOuNao == 'n' or SairOuNao == 'N')
            {
                menu1ou0(capacidade, tamanho, Paciente);
            }
            else
            {
                removerPaciente(Paciente, tamanho, capacidade);
            }
        }
    }
    else
    {
        cout << "Digite um numero valido!" << endl;
        removerPaciente(Paciente, tamanho, capacidade);
    }
}
int main()
{
    cout << fixed;
    cout << setprecision(2);

    ifstream arqEnt("registro.csv");
    int capacidade = 75;
    int tamanho = 0;

    FichaHosp *Paciente = new FichaHosp[capacidade];
    int escolhaAbertura;
    cout << "Deseja abrir como:" << endl
         << "[1] Binario (registroBinario.bin)" << endl
         << "[2] CSV (registro.csv)" << endl;
    cin >> escolhaAbertura;

    if (escolhaAbertura == 1)
    {

        ifstream arquivoBinario("registroBinario.bin", ios::binary);

        if (!arquivoBinario.is_open())
        {
            cout << "Erro ao abrir o arquivo binário." << std::endl;
            return 1;
        }
        while (arquivoBinario)
        { // LEITURA DO ARQUIVO BINARIO, REDIMENSIONAMENTO SE NECESSARIO E ATRIBUICAO NA MEMORIA
            if (tamanho + 1 == capacidade)
            {
                aumentarCapacidade(Paciente, capacidade, tamanho);
            }
            tamanho < capacidade and arquivoBinario.read(reinterpret_cast<char *>(&Paciente[tamanho]), sizeof(FichaHosp));
            tamanho++;
        }

        menuPrincipal(capacidade, tamanho, Paciente);
    }

    else
    {
        ifstream arqCSV("registro.csv");
        char lixo;

        while (arqCSV)
        {
            if (tamanho == capacidade)
            {
                aumentarCapacidade(Paciente, capacidade, tamanho);
            }

            arqCSV >> Paciente[tamanho].identificador;
            arqCSV >> lixo;
            arqCSV.get(Paciente[tamanho].nome, 30, ',');
            arqCSV >> lixo;
            arqCSV >> Paciente[tamanho].genero;
            arqCSV >> lixo;
            arqCSV >> Paciente[tamanho].peso;
            arqCSV >> lixo;
            arqCSV >> Paciente[tamanho].altura;
            arqCSV >> lixo;
            arqCSV.get(Paciente[tamanho].patologia, 30, ',');
            arqCSV >> lixo;

            tamanho++;
        }
        menuPrincipal(capacidade, tamanho, Paciente);
    }

    return 0;
}
