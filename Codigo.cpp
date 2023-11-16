#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

/*TRABALHO FINAL DE INTRODUÇÃO AOS ALGORITMOS - UNIVERSIDADE FEDERAL DE LAVRAS

TEMA: FICHAS HOSPITALARES

INTEGRANTES:
AUGUSTO ANTÔNIO COSTA GONTIJO
JOÃO MARCUS LEITE DA SILVA
CARLOS EDUARDO BORGES DE SOUSA
*/

struct FichaHosp
{ // CRIA O REGISTRO
  int identificador;
  char nome[30];
  char genero;
  float altura;
  float peso;
  char patologia[30];
};

void IMPRIMIR(FichaHosp Paciente[], int tamanho)
{ // FUNÇÃO PARA IMPRIMIR
  for (int i = 0; i < tamanho - 1; i++)
  {
    cout << Paciente[i].identificador << " " << Paciente[i].nome << " "
         << Paciente[i].genero << " " << Paciente[i].peso << "kg "
         << Paciente[i].altura << "m " << Paciente[i].patologia << endl
         << endl;
  }
}
void buscarNomePaciente(FichaHosp Paciente[], int tamanho, char nomeBuscado[])
{ // FUNÇAO PARA BUSCAR POR NOME DO PACIENTE
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
  }
}

void buscarIDPaciente(
    FichaHosp Paciente[], int tamanho,
    int idBuscado)
{ // FUNÇAO PARA BUSCAR POR IDENTIFICADOR DE PACIENTE
  if (idBuscado > 0 and idBuscado <= tamanho)
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

void adicionarPaciente(FichaHosp Paciente[], int &capacidade, int &tamanho)
{
  capacidade++;

  cout << "Digite os dados do novo paciente:" << endl;
  cout << "Identificador: " << tamanho-- << endl;

  cout << "Nome: ";
  cin >> Paciente[capacidade].nome;

  cout << "Genero: ";
  cin >> Paciente[capacidade].genero;

  cout << "Peso: ";
  cin >> Paciente[capacidade].peso;

  cout << "Altura: ";
  cin >> Paciente[capacidade].altura;

  cout << "Patologia: ";
  cin >> Paciente[capacidade].patologia;

  tamanho++;
  
}

void removerPaciente(FichaHosp Paciente[], int &capacidade, int idRemover) // REMOVER PACIENTE
{
  if (idRemover > 0 && idRemover <= capacidade)
  {
    for (int i = idRemover - 1; i < capacidade - 1; i++)
    {
      Paciente[i] = Paciente[i + 1];
    }
    capacidade--;
    cout << "Paciente removido com sucesso." << endl;
  }
  else
  {
    cout << "Identificador de paciente invalido." << endl;
  }
}
void menu1ou0(int capacidade, int tamanho, FichaHosp *Paciente);
void menuPrincipal(int capacidade, int tamanho, FichaHosp *Paciente)
{ // MENU DE ESCOLHA PRINCIPAL
  int escolha;
  cout << "ESCOLHA O QUE DESEJA FAZER:" << endl
       << "[1] IMPRIMIR FICHA DOS PACIENTES" << endl
       << "[2] PESQUISAR NOME DE PACIENTE" << endl
       << "[3] BUSCAR POR IDENTIFICADOR DO PACIENTE" << endl
       << "[4] ADICIONAR PACIENTE" << endl
       << "[5] REMOVER PACIENTE" << endl
       << "[0] FECHAR O PROGRAMA" << endl;
  cin >> escolha;
  switch (escolha)
  {
  case 1:
    IMPRIMIR(Paciente, tamanho);
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
    adicionarPaciente(Paciente, capacidade, tamanho);
    menu1ou0(capacidade, tamanho, Paciente);
    break;
  case 5:
    int idRemover;
    cout << "Digite o identificador do paciente que deseja remover: ";
    cin >> idRemover;
    removerPaciente(Paciente, capacidade, idRemover);
    menu1ou0(capacidade, tamanho, Paciente);
    break;
  case 0:
    break;
  }
}
void menu1ou0(int capacidade, int tamanho, FichaHosp *Paciente)
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
  cout << setprecision(2); // LIMITA 2 DIGITOS DEPOIS DA VIRGULA

  ifstream arqE("registro.csv");
  int capacidade = 75;
  int tamanho = 0;

  FichaHosp *Paciente = new FichaHosp[capacidade];

  if (not arqE)
  { // VERIFICAÇÃO DE ABERTURA
    cout << "Erro na leitura do arquivo";
  }
  else
  {
    char virgula;
    while (arqE)
    {
      if (tamanho >= capacidade - 1)
      {
        FichaHosp *Pivo = new FichaHosp[capacidade + 1];
        for (int i = 0; i < tamanho; i++)
        {
          Pivo[i] = Paciente[i];
        }
        delete[] Paciente;
        Paciente = Pivo;
        capacidade += 1;
      }

      arqE >> Paciente[tamanho].identificador;
      arqE >> virgula; // Leitura da vírgula
      arqE.get(Paciente[tamanho].nome, 30, ',');
      arqE >> virgula; // Leitura da vírgula
      arqE >> Paciente[tamanho].genero;
      arqE >> virgula; // Leitura da vírgula
      arqE >> Paciente[tamanho].peso;
      arqE >> virgula; // Leitura da vírgula
      arqE >> Paciente[tamanho].altura;
      arqE >> virgula; // Leitura da vírgula
      arqE.get(Paciente[tamanho].patologia, 30, ',');
      arqE.ignore(); // Ignora a vírgula após o último campo

      tamanho += 1; // Aumenta e retorna pro loop while
    }
    menuPrincipal(capacidade, tamanho, Paciente);
  }
  return 0;
}
