#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct FichaHosp {
    char nome[30];
    char genero;
    float altura;
    float peso;
    char patologia[30];
};

void IMPRIMIR(FichaHosp pacientes[], int tamanho) { //FUNÇÃO PARA IMPRIMIR
    for (int i = 0; i < tamanho; i++) {
        cout << pacientes[i].nome << " " << pacientes[i].genero << " " << pacientes[i].peso << "kg " << pacientes[i].altura << "m " << pacientes[i].patologia << endl << endl;
    }
}

int main() {
    cout << fixed;
    cout << setprecision(2);
    ifstream arqE("registro.csv");
    if (not arqE) {
        cout << "Erro na leitura do arquivo";
    }
    else {
        FichaHosp Paciente[30];
        char virgula;
        for (int i = 0; i < 30; i++) {
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
        IMPRIMIR(Paciente, 30);
    }

    return 0;
}