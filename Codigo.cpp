#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
using namespace std;

/*TRABALHO FINAL DE INTRODUÇÃO AOS ALGORITMOS - UNIVERSIDADE FEDERAL DE LAVRAS

TEMA: FICHAS HOSPITALARES

INTEGRANTES:
AUGUSTO ANTÔNIO COSTA GONTIJO
JOÃO MARCUS LEITE DA SILVA
CARLOS EDUARDO BORGES DE SOUSA
*/


struct FichaHosp {	//CRIA O REGISTRO
    int identificador;
    char nome[42];
    char genero;
    float altura;
    float peso;
    char patologia[42];
};

void IMPRIMIR(FichaHosp pacientes[], int tamanho) {	//FUNÇÃO PARA IMPRIMIR
    for (int i = 0; i < tamanho; i++) {
        cout <<pacientes[i].identificador << " " << pacientes[i].nome << " " << pacientes[i].genero << " " << pacientes[i].peso << "kg " << pacientes[i].altura << "m " << pacientes[i].patologia << endl << endl;
    }
}
void buscarPaciente(FichaHosp Paciente[],int numeroPacientes,char nomeBuscado[]){
    int j = 0;
    char *ptr;
    int nomesEncontrados[numeroPacientes];

    for (int i=0;i < numeroPacientes;i++){
        ptr = strstr(Paciente[i].nome,nomeBuscado);
        if(ptr){
            nomesEncontrados[ j ] = i;
            j++;
        }
    }
    if(j==0){
        cout << "Nao foi encontrado nenhum paciente com esse nome." << endl;
    }
    else{
        cout << "Fichas dos pacientes com esse nome: " << endl;
        for(int k=0;k<j;k++){
            cout << Paciente[nomesEncontrados[k]].identificador << " "
            << Paciente[nomesEncontrados[k]].nome << " "
            << Paciente[nomesEncontrados[k]].genero << " "
            << Paciente[nomesEncontrados[k]].peso << " "
            << Paciente[nomesEncontrados[k]].altura << " "
            << Paciente[nomesEncontrados[k]].patologia << endl;
        }
    }
}

void buscarIDPaciente(FichaHosp Paciente[],int numeroPacientes,int idBuscado){
	if(idBuscado>0){
		int esquerda = 0;
		int direita = numeroPacientes-1;
		bool encontrou = false;
		while(esquerda<=direita and encontrou == false){
			int meio = (esquerda+direita)/2;
			if(idBuscado==meio){
				cout << Paciente[meio-1].identificador << " "
				<< Paciente[meio-1].nome << " "
				<< Paciente[meio-1].genero << " "
				<< Paciente[meio-1].peso << " "
				<< Paciente[meio-1].altura << " "
				<< Paciente[meio-1].patologia << endl;
				encontrou=true;
			}
			else if(idBuscado>meio){
				esquerda=meio+1;
			}
		else if(idBuscado<meio){
			direita=meio-1;
		}
		}
	}else{
		cout << "Digite um numero valido";
	}
}
int main() {
    cout << fixed;
    cout << setprecision(2);	//LIMITA 2 DIGITOS DEPOIS DA VIRGULA
    ifstream arqE("registro.csv");
    int numeroPacientes = 30;
    
    if (not arqE) {	//VERIFICAÇÃO DE ABERTURA
        cout << "Erro na leitura do arquivo";
    }
    else {
        FichaHosp Paciente[numeroPacientes];
        char virgula;
        for (int i = 0; i < numeroPacientes; i++) {
			arqE >> Paciente[i].identificador;
			arqE >> virgula;  // Leitura da vírgula
			arqE.get(Paciente[i].nome, 30, ',');
			arqE >> virgula;  // Leitura da vírgula
			arqE.get(Paciente[i].genero);
			arqE >> virgula;  // Leitura da vírgula
			arqE >> Paciente[i].peso;
			arqE >> virgula;  // Leitura da vírgula
			arqE >> Paciente[i].altura;
			arqE >> virgula;  // Leitura da vírgula
			arqE.get(Paciente[i].patologia, 30, ',');
			arqE.ignore();  // Ignora a vírgula após o último campo
        }
		}
    int escolha;
    cout << "ESCOLHA O QUE DESEJA FAZER:" << endl << 
            "[1] IMPRIMIR FICHA DOS PACIENTES" << endl <<
            "[2] PESQUISAR NOME DE PACIENTE" << endl <<
            "[3] BUSCAR POR IDENTIFICADOR DO PACIENTE" << endl << 
            "[0] FECHAR O PROGRAMA" << endl;
    cin >> escolha;
    switch(escolha){
        case 1:
            IMPRIMIR(Paciente, numeroPacientes);
            break;
           case 2:
           char nomeBuscado[30];
           cout << "Digite o nome que deseja pesquisar: ";
           cin >> nomeBuscado;
           buscarPaciente(Paciente,numeroPacientes,nomeBuscado);
           break;
           case 3:
           int idBuscado;
           cout << "Digite o numero de identificacao: ";
           cin >> idBuscado;
           buscarIDPaciente(Paciente,numeroPacientes,idBuscado);
	   break;
        case 0:
            return 0;
            break;
        }
    }

    return 0;
}
