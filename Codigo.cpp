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

void IMPRIMIR(FichaHosp Paciente[], int numeroAtualPaciente)
{ // FUNÇÃO PARA IMPRIMIR
  for (int i = 0; i < numeroAtualPaciente-1; i++)
  {
    cout << Paciente[i].identificador << " " << Paciente[i].nome << " "
         << Paciente[i].genero << " " << Paciente[i].peso << "kg "
         << Paciente[i].altura << "m " << Paciente[i].patologia << endl
         << endl;
  }
}
void buscarNomePaciente(
    FichaHosp Paciente[], int numeroAtualPacientes,
    char nomeBuscado[])
{ // FUNÇAO PARA BUSCAR POR NOME DO PACIENTE
  int j = 0;
  char *ptr;
  int nomesEncontrados[numeroAtualPacientes];

  for (int i = 0; i < numeroAtualPacientes; i++)
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
    FichaHosp Paciente[], int numeroAtualPacientes,
    int idBuscado)
{ // FUNÇAO PARA BUSCAR POR IDENTIFICADOR DE PACIENTE
  if (idBuscado > 0 and idBuscado <= numeroAtualPacientes)
  {
    int esquerda = 0;
    int direita = numeroAtualPacientes;
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
    buscarIDPaciente(Paciente, numeroAtualPacientes, idBuscado);
  }
}
int main()
{
  cout << fixed;
  cout << setprecision(2); // LIMITA 2 DIGITOS DEPOIS DA VIRGULA

  ifstream arqE("registro.csv");
  int numeroPacientes = 30;
  int numeroAtualPacientes = 0;

  FichaHosp *Paciente = new FichaHosp[numeroPacientes];

  if (not arqE)
  { // VERIFICAÇÃO DE ABERTURA
    cout << "Erro na leitura do arquivo";
  }
  else
  {
    char virgula;
    while (arqE)
    {
      if (numeroAtualPacientes >= numeroPacientes - 1)
      {
        FichaHosp *Pivo = new FichaHosp[numeroPacientes + 1];
        for (int i = 0; i < numeroAtualPacientes; i++)
        {
          Pivo[i] = Paciente[i];
        }
        delete[] Paciente;
        Paciente = Pivo;
        numeroPacientes += 1;
      }

      arqE >> Paciente[numeroAtualPacientes].identificador;
      arqE >> virgula; // Leitura da vírgula
      arqE.get(Paciente[numeroAtualPacientes].nome, 30, ',');
      arqE >> virgula; // Leitura da vírgula
      arqE >> Paciente[numeroAtualPacientes].genero;
      arqE >> virgula; // Leitura da vírgula
      arqE >> Paciente[numeroAtualPacientes].peso;
      arqE >> virgula; // Leitura da vírgula
      arqE >> Paciente[numeroAtualPacientes].altura;
      arqE >> virgula; // Leitura da vírgula
      arqE.get(Paciente[numeroAtualPacientes].patologia, 30, ',');
      arqE.ignore(); // Ignora a vírgula após o último campo

      numeroAtualPacientes += 1; // Aumenta e retorna pro loop while
    }
    int escolha;
    cout << "ESCOLHA O QUE DESEJA FAZER:" << endl
         << "[1] IMPRIMIR FICHA DOS PACIENTES" << endl
         << "[2] PESQUISAR NOME DE PACIENTE" << endl
         << "[3] BUSCAR POR IDENTIFICADOR DO PACIENTE" << endl
         << "[0] FECHAR O PROGRAMA" << endl;
    cin >> escolha;
    switch (escolha)
    {
    case 1:
      IMPRIMIR(Paciente, numeroAtualPacientes);
      break;
    case 2:
      char nomeBuscado[30];
      cout << "Digite o nome que deseja pesquisar: ";
      cin >> nomeBuscado;
      buscarNomePaciente(Paciente, numeroPacientes, nomeBuscado);
      break;
    case 3:
      int idBuscado;
      cout << "Digite o numero de identificacao: ";
      cin >> idBuscado;
      buscarIDPaciente(Paciente, numeroPacientes, idBuscado);
      break;
    case 0:
      return 0;
      break;
    }

    return 0;
  }
}
