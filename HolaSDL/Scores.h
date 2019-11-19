#pragma once
#include <iostream>
#include <vector>
#include "checkML.h"

using namespace std;

struct ScoreReg {

	ScoreReg(int i, string n) {
		name = n;
		puntuacion = i;
	}

	string name;
	int puntuacion;
};


class Scores
{
private:
	vector<ScoreReg> highScores;
public:
	Scores();
	~Scores();
	void load(const string &filename);
	void print();
	bool addScore(string name, int s);
	void save(const string & filename);
};