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
  for (int i = 0; i < tamanho-1; i++)
  {
    cout << Paciente[i].identificador << " " << Paciente[i].nome << " "
         << Paciente[i].genero << " " << Paciente[i].peso << "kg "
         << Paciente[i].altura << "m " << Paciente[i].patologia << endl
         << endl;
  }
}
void buscarNomePaciente(
    FichaHosp Paciente[], int tamanho,
    char nomeBuscado[])
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

void adicionarPaciente(FichaHosp Paciente[], int &numeroPacientes)
{
    if (numeroPacientes < 50)
    {
        cout << "Digite os dados do novo paciente:" << endl;
        cout << "Identificador: ";
        cin >> Paciente[numeroPacientes].identificador;

        cout << "Nome: ";
        cin >> Paciente[numeroPacientes].nome;

        cout << "Genero: ";
        cin >> Paciente[numeroPacientes].genero;

        cout << "Peso: ";
        cin >> Paciente[numeroPacientes].peso;

        cout << "Altura: ";
        cin >> Paciente[numeroPacientes].altura;

        cout << "Patologia: ";
        cin >> Paciente[numeroPacientes].patologia;

        numeroPacientes++;
    }
    else
    {
        cout << "Limite de pacientes atingido." << endl;
    }
}

void removerPaciente(FichaHosp Paciente[], int &numeroPacientes, int idRemover)
{
    if (idRemover > 0 && idRemover <= numeroPacientes)
    {
        for (int i = idRemover - 1; i < numeroPacientes - 1; i++)
        {
            Paciente[i] = Paciente[i + 1];
        }
        numeroPacientes--;
        cout << "Paciente removido com sucesso." << endl;
    }
    else
    {
        cout << "Identificador de paciente invalido." << endl;
    }
}

int main()
{
  cout << fixed;
  cout << setprecision(2); // LIMITA 2 DIGITOS DEPOIS DA VIRGULA

  ifstream arqE("registro.csv");
  int capacidades = 75;
  int tamanho = 0;

  FichaHosp *Paciente = new FichaHosp[capacidades];

  if (not arqE)
  { // VERIFICAÇÃO DE ABERTURA
    cout << "Erro na leitura do arquivo";
  }
  else
  {
    char virgula;
    while (arqE)
    {
      if (tamanho >= capacidades - 1)
      {
        FichaHosp *Pivo = new FichaHosp[capacidades + 1];
        for (int i = 0; i < tamanho; i++)
        {
          Pivo[i] = Paciente[i];
        }
        delete[] Paciente;
        Paciente = Pivo;
        capacidades += 1;
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
    int escolha;
    cout << "ESCOLHA O QUE DESEJA FAZER:" << endl
         << "[1] IMPRIMIR FICHA DOS PACIENTES" << endl
         << "[2] PESQUISAR NOME DE PACIENTE" << endl
         << "[3] BUSCAR POR IDENTIFICADOR DO PACIENTE" << endl
         << "[4] ADICIONAR PACIENTE" << endl;
         << "[5] REMOVER PACIENTE" << endl
         << "[0] FECHAR O PROGRAMA" << endl;
    cin >> escolha;
    switch (escolha)
    {
    case 1:
      IMPRIMIR(Paciente, tamanho);
      break;
    case 2:
      char nomeBuscado[30];
      cout << "Digite o nome que deseja pesquisar: ";
      cin >> nomeBuscado;
      buscarNomePaciente(Paciente, capacidades, nomeBuscado);
      break;
    case 3:
      int idBuscado;
      cout << "Digite o numero de identificacao: ";
      cin >> idBuscado;
      buscarIDPaciente(Paciente, capacidades, idBuscado);
      break;
    case 4:
      adicionarPaciente(Paciente, capacidades);
      break;
    case 5:
      int idRemover;
      cout << "Digite o identificador do paciente que deseja remover: ";
      cin >> idRemover;
      removerPaciente(Paciente, capacidades, idRemover);
      break;
    case 0:
      return 0;
      break;
    }

    return 0;
  }
}
