#ifndef PLAYER_H
#define PLAYER_H

#include<fstream>
using std::ifstream;
using std::getline;

#include<string>
using std::string;
using std::stoi;

#include<vector>
using std::vector;

#include<cmath>
using std::ceil;
using std::floor;
using std::abs;

#include "Glob.h"
#include "PlayerStats.h"
#include "Skills.h"

class Player : private PlayerStats, private Skills {
public:
	//Constructor
	Player(string, string, bool, bool);

	//Destructor
	~Player();

	//Functions
	void DscSts();
	void Mutate();
	int Roll();
	int getRlSkl(int);
	int getSwg();
	void setHp(int);
	void resetHp();
	void setScore(int);
	int getScore();
	void setNam(string);
	void setParent(string);

	string getNam();
	string getParent();
	string getVore();
	float getStat(int);
	int getPnts(int);

private:
	//Variables
	string name;
	string vore;
	string child_of;

	struct lang {
		string name;
		bool spoken;
		bool written;
	};
	// These are TODO
	// for future programs
	// vector<lang> langs;
	// vector<string> cults;
	// string appear;
	// string status;
	// string rep;

	int scr;

	int num_mkr;
	bool unit_test;
	string file;
	vector<int> nums;

	//Functions
	int Roll(int, int);
	int RollSum(int, int, int);
	void CalcPts();
	int Rnd(float);

	vector<int> TestNums();
};
//Public
Player::Player(string n, string vr, bool sapient, bool u_test) {
	//Beginning
	name = n;
	child_of = "none";
	vore = vr;

	if(!sapient) {
		if(vore == "plant" || vore == "Plant") {
		} else if(vore == "herbivore" || vore == "Herbivore") {
			file = "prey_rnd.csv";
		} else if(vore == "omnivore" || vore == "Omnivore") {
		} else if(vore == "carnivore" || vore == "Carnivore") {
			file = "pred_rnd.csv";
		} else if(vore == "detritivore" || vore == "Detritivore") {
		};
	} else {
	};
	scr = 0;

	num_mkr = 0;
	unit_test = u_test;
	if(unit_test) nums = TestNums();
}
Player::~Player() {
}
void Player::DscSts() {
	cout << "Name...: " << name << "\n";
	cout << "Points.: " << getStat(pts) << "\n";
	cout << "Eats...: " << vore << "\n";
	cout << "Ht.....: " << getStat(ft) << " ft " << getStat(in) << " in     ";
	cout << "Wt: " << getStat(lb) << " lb\n";
	cout << "St.....: " << getStat(st) << "     ";
	cout << "HP: " << getStat(hp) << "     ";
	cout << "Dex: " << getStat(dx) << "\n";
	cout << "Will...: " << getStat(will) << "     ";
	cout << "IQ: " << getStat(iq) << "     ";
	cout << "Per: " << getStat(per) << "\n";
	cout << "Hlt....: " << getStat(ht) << "     ";
	cout << "Fat: " << getStat(fp) << "     ";
	cout << "DR: " << getStat(dr) << "\n";
	cout << "Spd....: " << getStat(bs) << "\n";
	cout << "Lft....: " << getStat(no_bl) << "     Mv: " << getStat(no_bm) << "     Ddg: " << getStat(no_dge) << "\n";

	for(int i(0); i < getSklCnt(); i++) {
		cout << getSklNam(i) << " Lvl: " << getSklLvl(i) << "\n";
	};
	cout << "\n";
}
void Player::Mutate() {
	int which_mut = 0;
	int add_sub = 1;
	int last_pts;
	bool backed_last_time = false;

	do {
		//Save();
		//last_pts = getPts(pts);
		which_mut = Roll(0, 9);
		//Troubleshooting Tool
		//cout << name << " " << which_mut << "\n";
		switch(which_mut) {
			case 0 :
				add_sub = ( 2 * Roll(0, 1) ) -1;
				setSz(getStat(sz) + add_sub);
				break;
			case 1 :
				setSt(getStat(st) + add_sub);
				break;
			case 2 :
				setDx(getStat(dx) + add_sub);
				break;
			case 3 :
				setIq(getStat(iq) + add_sub);
				break;
			case 4 :
				setHt(getStat(ht) + add_sub);
				break;
			case 5 :
				setWill(getStat(will) + add_sub);
				break;
			case 6 :
				setPer(getStat(per) + add_sub);
				break;
			case 7 :
				setBs(getStat(bs) + (0.25*add_sub) );
				break;
			case 8 :
				setSkill(getSklLvl(bwl) + add_sub, bwl);
				break;
			case 9 :
				setSkill(getSklLvl(stl) + add_sub, stl);
				break;
			}
		CalcPts();
		/*
		if(backed_last_time == true) {
			backed_last_time = false;
		} else if(add_sub < 0 && getPts(pts) < 0) {
			Load();
			CalcPts();
			backed_last_time = true;
		} else if(add_sub < 0 && last_pts < getPts(pts) ) {
			Load();
			CalcPts();
			backed_last_time = true;
		};
		*/
		add_sub = -1;

	} while(getPts(pts) < 0);
}
int Player::Roll() {
	return RollSum(3, 1, 6);
}
int Player::getRlSkl(int skl_ind) {
	return getStat(getSklAtt(skl_ind)) + getSklLvl(skl_ind);
}
int Player::getSwg() {
	int dmg;
	switch( int( getStat(st) ) ) {
		case 1 :
			dmg = Roll(1,6) - 5;
			break;
		case 2 :
			dmg = Roll(1,6) - 5;
			break;
		case 3 :
			dmg = Roll(1,6) - 4;
			break;
		case 4 :
			dmg = Roll(1,6) - 4;
			break;
		case 5 :
			dmg = Roll(1,6) - 3;
			break;
		case 6 :
			dmg = Roll(1,6) - 3;
			break;
		case 7 :
			dmg = Roll(1,6) - 2;
			break;
		case 8 :
			dmg = Roll(1,6) - 2;
			break;
		case 9 :
			dmg = Roll(1,6) - 1;
			break;
		case 10 :
			dmg = Roll(1,6);
			break;
		case 11 :
			dmg = Roll(1,6) + 1;
			break;
		case 12 :
			dmg = Roll(1,6) + 2;
			break;
		case 13 :
			dmg = RollSum(2,1,6) - 1;
			break;
		case 14 :
			dmg = RollSum(2,1,6);
			break;
		case 15 :
			dmg = RollSum(2,1,6) + 1;
			break;
		case 16 :
			dmg = RollSum(2,1,6) + 2;
			break;
		case 17 :
			dmg = RollSum(3,1,6) - 1;
			break;
		case 18 :
			dmg = RollSum(3,1,6);
			break;
		case 19 :
			dmg = RollSum(3,1,6) + 1;
			break;
		case 20 :
			dmg = RollSum(3,1,6) + 2;
			break;
		default :
			dmg = Roll(1,6);
			break;
	}
	if(dmg < 0) dmg = 0;
	return dmg;
}
string Player::getNam() {
	return name;
}
string Player::getParent() {
	return child_of;
}
void Player::setNam(string n) {
	name = n;
}
void Player::setParent(string parent) {
	child_of = parent;
}
void Player::setScore(int score) {
	scr = score;
}
int Player::getScore() {
	return scr;
}
void Player::setHp(int hit_points) {
	setHitPts(hit_points);
}
void Player::resetHp() {
	resetHitPts();
}
string Player::getVore() {
	return vore;
}
// Private Functions ------------------------------------------------------------------------------------------------------------------
int Player::Roll(int min, int max) {
	if(!unit_test) {
		return ( rand() % (1+max-min) ) + min;
	} else {
		int temp = ( nums[num_mkr] % (1+max-min) ) + min;
		num_mkr = (num_mkr + 1) % 100;
		return temp;
	};
}
int Player::RollSum(int rolls, int min, int max) {
	int sum = 0;
	for(int i(0); i < rolls; i++) {
		sum += Roll(min, max);
	};
	return sum;
};
void Player::CalcPts() {
	setPts(0);

	for(int i(app); i <= no_bl; i++) {
		setPts(getPts(i) + getPts(pts));
		// Troubleshooting Tool
		// cout << stats[i][1] << '\n';
	};
	setPts(getPts(no_bm) + getPts(pts));
	setPts(getPts(no_dge) + getPts(pts));

	for(int i(0); i < getSklCnt(); i++) {
		setPts( getSklPts(i) + getPts(pts) );
	};
	// Troubleshooting Tool
	// cout << stats2[bs][1] << ' ' << stats2[enc_no][1] << ' ' << stats2[enc_no][3] << "\n\n";
}
vector<int> Player::TestNums() {
	vector<int> out;
	ifstream input(file);

	for(string line; getline(input, line); ) {
		out.push_back( stoi(line) );
	};
	return out;
}
float Player::getStat(int stt) {
	return getStt(stt);
}
int Player::getPnts(int stt) {
	return getPts(stt);
}
int Player::Rnd(float in) {
	return (in > 0.0) ? floor(in + 0.5) : ceil(in - 0.5);
}
#endif
