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

void aumentarCapacidade(FichaHosp *&Paciente, int &capacidade, int &tamanho)//PROCEDIMENTO PARA REDIMENSIONAR DE 1 EM 1 A CAPACIDADE DO VETOR
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
void imprimirLista(FichaHosp Paciente[], int tamanho)//IMPRIME OS PACIENTES DA MEMORIA
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        cout << Paciente[i].identificador << " " << Paciente[i].nome << " "
             << Paciente[i].genero << " " << Paciente[i].peso << "kg "
             << Paciente[i].altura << "m " << Paciente[i].patologia << endl
             << endl;
    }
}
void buscarNomePaciente(FichaHosp Paciente[], int tamanho, char nomeBuscado[])//BUSCA NOME DE PACIENTE USANDO "strstr", FUTURAMENTE CRIAREMOS UMA FUNCAO PARA DEIXAR TUDO MINUSCULO ANTES DO strstr
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
void buscarIDPaciente(FichaHosp Paciente[], int tamanho, int idBuscado) //BUSCA IDENTIFICADOR SOLICITADO POR BUSCA BINARIA
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
void addPaciente(FichaHosp *&Paciente, int &capacidade, int &tamanho) //ADICAO DE PACIENTE VIA TECLADO, COM REDIMENSIONAMENTO SE NECESSARIO
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
void salvarBinarioCsv(FichaHosp *&Paciente, int tamanho) //GRAVA OS VETORES EM ARQUIVOS BINARIO E CSV
{
    ofstream arqBin("registroBinarioNovo.bin", ios::binary);
    ofstream arqS("registroNovo.csv");
    for (int i = 0; i < tamanho; i++)
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
void menuPrincipal(int capacidade, int tamanho, FichaHosp *Paciente);
void removerPaciente(FichaHosp Paciente[], int &tamanho, int capacidade){
    int idRemover;
    cout << "Digite o identificador do Paciente que deseja remover (entre 1 e " << tamanho -1 << "): ";
    cin.ignore();
    cin >> idRemover;
    if(idRemover > 0 and idRemover < tamanho){
      cout <<
      endl << "Identificador: " << Paciente[idRemover-1].identificador << 
      endl << "Nome: " << Paciente[idRemover-1].nome <<
      endl << "Genero: " << Paciente[idRemover-1].genero << 
      endl << "Peso: " << Paciente[idRemover-1].peso << "kg" << 
      endl << "Altura: " << Paciente[idRemover-1].altura << "m" << 
      endl << "Patologia: " <<Paciente[idRemover-1].patologia << endl;

      cout << "Deseja remover este paciente?" << 
      endl << "[S/N]" << endl;
      char SimOuNao;
      cin >> SimOuNao;
      if(SimOuNao =='S' or SimOuNao == 's'){
        for (int i = idRemover; i < tamanho; i++){
            strcpy(Paciente[i-1].nome, Paciente[i].nome);
            Paciente[i-1].genero = Paciente[i].genero;
            Paciente[i-1].peso = Paciente[i].peso;
            Paciente[i-1].altura = Paciente[i].altura;
            strcpy(Paciente[i-1].patologia, Paciente[i].patologia);
        }
        tamanho--;
        for(int i=0;i<tamanho;i++){
          Paciente[i].identificador = i+1;
        }
        cout << "Paciente removido!" << endl;
        menuPrincipal(capacidade, tamanho, Paciente);
      }
      else if(SimOuNao == 'N' or SimOuNao == 'n'){
        cout << "Deseja remover outro Paciente?" << 
        endl << "[S/N]" << endl;
        char SairOuNao;
        cin >> SairOuNao;
        if(SairOuNao == 'n' or SairOuNao == 'N'){
        menuPrincipal(capacidade,tamanho,Paciente);
        }
        else{
          removerPaciente(Paciente,tamanho,capacidade);
        }
      }
    }
    else{
      cout << "Digite um numero valido!" << endl;
      removerPaciente(Paciente,tamanho,capacidade);
    }
}
void menu1ou0(int capacidade, int tamanho, FichaHosp *Paciente);
void menuPrincipal(int capacidade, int tamanho, FichaHosp *Paciente)// MENU DE ESCOLHA QUE É APRESENTADO AS FUNCIONALIDADES DO CODIGO, CHAMA A FUNÇAO "menu1ou0" APOS O 'CASE' FINALIZAR
{
    int escolha;
    cout << "Escolha o que deseja fazer:" << endl
         << "[1] Imprimir ficha dos pacientes" << endl
         << "[2] Pesquisar nome de pacientes" << endl
         << "[3] Buscar por identificador de paciente" << endl
         << "[4] Adicionar paciente" << endl
         << "[5] Salvar lista atual em binario e csv" << endl
         << "[6] Remover paciente" << endl
         << "[0] Fechar o programa" << endl;
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
        break;
    case 5:
        salvarBinarioCsv(Paciente, tamanho);
        menu1ou0(capacidade, tamanho, Paciente);
        break;
    case 6:
        removerPaciente(Paciente, tamanho, capacidade);
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


int main()
{
    cout << fixed;
    cout << setprecision(2);

    int capacidade = 75;
    int tamanho = 0;

    FichaHosp *Paciente = new FichaHosp[capacidade];

    ifstream arquivoBinario("registroBinario.bin", ios::binary);

    if (!arquivoBinario.is_open())
    {
        cout << "Erro ao abrir o arquivo binário." << std::endl;
        return 1;
    }
    while (arquivoBinario) { //LEITURA DO ARQUIVO BINARIO, REDIMENSIONAMENTO SE NECESSARIO E ATRIBUICAO NA MEMORIA
    if (tamanho + 1 == capacidade) {
        aumentarCapacidade(Paciente, capacidade, tamanho);
    }
    tamanho < capacidade and arquivoBinario.read(reinterpret_cast<char*>(&Paciente[tamanho]), sizeof(FichaHosp));
    tamanho++;
}

    menuPrincipal(capacidade, tamanho, Paciente);
    return 0;
}
