#ifndef REC_H
#define REC_H

#include<vector>
using std::vector;

#include<string>
using std::string;
using std::to_string;

#include<iostream>

#include<fstream>
using std::ofstream;

#include "Player.h"

class Rec {
public:
	//Constructor
	Rec();

	//Destructor
	~Rec();

	//Functions
	void Save(vector<Player>, vector<Player>, int, int);
	void Record();

private:
	//Variables
	vector<Player> animals;

	//Functions
	void Write(string);
};
Rec::Rec() {
}
Rec::~Rec() {
}
void Rec::Save(vector<Player> herb, vector<Player> carn, int cut_top, int cut_bottom) {
	animals.insert(animals.end(), herb.begin() + cut_top, herb.end() - cut_bottom);
	animals.insert(animals.end(), carn.begin() + cut_top, carn.end() - cut_bottom);
}
void Rec::Record() {
	string out = "Name,Child Of,Points,Eats,Feet,Inches,Weight,Strength,Hit Points,Dexterity,Will Power,Intelligence,Perception,Health,Fatigue,Damage Resistance,Speed,Basic Lift,Basic Move,Basic Dodge\n";

	for(int i(0); i < animals.size(); i++) {
		out += animals[i].getNam() + ',';
		out += animals[i].getParent() + ',';
		out += to_string(animals[i].getPnts(pts)) + ',';
		out += animals[i].getVore() + ',';
		out += to_string(animals[i].getStat(ft)) + ',';
		out += to_string(animals[i].getStat(in)) + ',';
		out += to_string(animals[i].getStat(lb)) + ',';
		out += to_string(animals[i].getStat(st)) + ',';
		out += to_string(animals[i].getStat(hp)) + ',';
		out += to_string(animals[i].getStat(dx)) + ',';
		out += to_string(animals[i].getStat(will)) + ',';
		out += to_string(animals[i].getStat(iq)) + ',';
		out += to_string(animals[i].getStat(per)) + ',';
		out += to_string(animals[i].getStat(ht)) + ',';
		out += to_string(animals[i].getStat(fp)) + ',';
		out += to_string(animals[i].getStat(dr)) + ',';
		out += to_string(animals[i].getStat(bs)) + ',';
		out += to_string(animals[i].getStat(no_bl)) + ',';
		out += to_string(animals[i].getStat(no_bm)) + ',';
		out += to_string(animals[i].getStat(no_dge)) + ',';
		out += '\n';
	};
	Write(out);
}
void Rec::Write(string out) {
	ofstream men;
	men.open("Menagerie.csv");
	men << out;
	men.close();
}
#endif
