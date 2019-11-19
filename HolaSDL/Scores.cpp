#include "Scores.h"
#include <vector>
#include "checkML.h"
#include <fstream>
#include <string>


Scores::Scores()
{
}

Scores::~Scores()
{
}

void Scores::load(const string& filename) {
	ifstream input;
	input.open(filename);
	
	string line;

	int pos = 0;
	int i = 0;

	while (i < 10 && getline(input, line)) { //carga todos los records  SI DE PUNTUACION TIENE -1 ES QUE ESE ESPACIO AUN ESTÁ LIBRE
		pos = line.find(" ");
		int puntua = stoi(line.substr(0, pos));
		string nam = line.erase(0, pos + 1);
		highScores.push_back(ScoreReg(puntua, nam)); //guarda en el vector la puntuacion
		i++;
	}

	input.close();
}

void Scores::print() { //imprime en consola todos los highScores guardados
	cout << "High Scores: \n";
	for (int i = 0; i < highScores.size(); i++) {
		if(highScores[i].puntuacion >= 0)cout << highScores[i].name << ": " << highScores[i].puntuacion << "\n";
	}
}

bool Scores::addScore(string name,int s) { //s de score
	int i = 0;
	bool candidato = false; //si es candidato a entrar en el top 10

	while (i < highScores.size() && !candidato) {
		if (highScores[i].puntuacion < s) {
			candidato = true;
			highScores[i].name = name;
			highScores[i].puntuacion = s; //actualiza el vector
		}
		i++;
	}

	return candidato;
}

void Scores::save(const string& filename) {
	ofstream output;
	output.open(filename);

	for (int i = 0; i < highScores.size(); i++) {
		output << highScores[i].puntuacion << " " << highScores[i].name << "\n"; //guarda todos los valores en archivo
	}

	output.close();
}