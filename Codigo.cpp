#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

/*TRABALHO FINAL DE INTRODUÇÃO AOS ALGORITMOS - UNIVERSIDADE FEDERAL DE LAVRAS

TEMA: FICHAS HOSPITALARES

INTEGRANTES:
AUGUSTO ANTÔNIO COSTA GONTIJO


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

int main() {
    cout << fixed;
    cout << setprecision(2);	//LIMITA 2 DIGITOS DEPOIS DA VIRGULA
    ifstream arqE("registro.csv");
    
    if (not arqE) {	//VERIFICAÇÃO DE ABERTURA
        cout << "Erro na leitura do arquivo";
    }
    else {
        FichaHosp Paciente[42];
        char virgula;
        for (int i = 0; i < 42; i++) {
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
    int escolha;
    cout << "ESCOLHA O QUE DESEJA FAZER:" << endl << 
            "[1] IMPRIMIR FICHA DOS PACIENTES" << endl <<
            "[0] FECHAR O PROGRAMA" << endl;
    cin >> escolha;
    switch(escolha){
        case 1:
            IMPRIMIR(Paciente, 42);
            break;
        case 0:
            return 0;
            break;
        }
    }

    return 0;
}
