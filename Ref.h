#ifndef REF_H
#define REF_H

#include "Glob.h"
#include "Player.h"

class Ref {
public:
	//Constructor
	Ref();

	//Destructor
	~Ref();

	//Functions
	bool StlthChck(Player*, Player*);
	bool SpdChck(Player*, Player*);
	int FightDmg(Player*, Player*);
	int TallyScore(Player*);
	void Brawl(Player*, Player*);
	vector<int> Winners(vector<Player>);

protected:

private:
	// Variables
	int damage_delt;
	int damage_got;
};
Ref::Ref() {
	damage_delt = 0;
	damage_got = 0;
}
Ref::~Ref() {
}
// This function checks to see if the prey
// out stealths the predator's perception.
bool Ref::StlthChck(Player* pred, Player* prey) {
	bool tied = true; // Tied as in both rolls are equal
	int pred_roll;
	int prey_roll;

	while(tied) {
		pred_roll = pred->getStat(per) + ( prey->getStat(sz) - pred->getStat(sz) ) - pred->Roll();
		prey_roll = prey->getRlSkl(stl) - prey->getStat(sz) - prey->Roll();

		// Troubleshooting Tool
		//cout << t1 << " " << pred_roll << " " << t2 << " " << prey_roll << "\n";

		if(pred_roll > 0 && prey_roll < 0) {
			return true;
		} else if(pred_roll < 0 && prey_roll > 0) {
			return false;
		} else if(pred_roll > prey_roll) {
			return true;
		} else if(pred_roll < prey_roll) {
			return false;
		};
	};
}
bool Ref::SpdChck(Player* pred, Player* prey) {
	bool tied = true;
	int pred_roll;
	int prey_roll;

	while(tied) {
		pred_roll = pred->getStat(no_bm) - pred->Roll();
		prey_roll = prey->getStat(no_bm) - prey->Roll();

		if(pred_roll > 0 && prey_roll < 0) {
			return true;
		} else if(pred_roll < 0 && prey_roll > 0) {
			return false;
		} else if(pred_roll > prey_roll) {
			return true;
		} else if(pred_roll < prey_roll) {
			return false;
		};
	};
}
void Ref::Brawl(Player* p1, Player* p2) {
	int i = 0;
	while(p1->getStat(hp) > 0 && p2->getStat(hp) > 0 && i < 100) {
		p2->setHp( p2->getStat(hp) - FightDmg(p1, p2) );
		p1->setHp( p1->getStat(hp) - FightDmg(p2, p1) );
		i++;
	};
}
int Ref::FightDmg(Player* attacker, Player* defender) {
	int att_roll = attacker->getRlSkl(bwl) - attacker->Roll();
	int def_roll = defender->getStat(no_dge) - defender->Roll();

	/*
	// Troubleshooting Tool
	cout << attacker->getRlSkl(bwl) << " ";
	cout << defender->getDge() << " ";
	cout << "Atckr: " << attacker->getNam() << " " << att_roll << " " << def_roll << " " << attacker->getHp() << " " << defender->getHp() << " " << attacker->getSwg() << "\n\n";
	*/
	if(att_roll >= 0 && def_roll < 0) {
		int damage = attacker->getSwg();

		if(defender->getVore() == "herbivore" || defender->getVore() == "Herbivore") {
			damage_got -= damage;
		};
		if(attacker->getVore() == "carnivore" || attacker->getVore() == "Carnivore") {
			damage_delt += damage;
		};
		return damage;
	} else {
		return 0;
	};
}
int Ref::TallyScore(Player* p1) {
	if(p1->getVore() == "herbivore" || p1->getVore() == "Herbivore") {
		if(damage_got < 0) {
			int damage = damage_got;
			damage_got = 0;
			return damage;
		} else {
			return 0;
		};
	} else if(p1->getVore() == "carnivore" || p1->getVore() == "Carnivore") {
		if(damage_delt > 0) {
			int damage = damage_delt;
			damage_delt = 0;
			return damage;
		} else {
			return 0;
		};
	};
}
vector<int> Ref::Winners(vector<Player> players) {
	vector<int> win_ind;
	vector<int> scores;
	int top = win_cnt;

	for(int i(0); i < top; i++) {
		win_ind.push_back(i);
		scores.push_back(players[i].getScore());
	};
	for(int i(top); i < players.size(); i++) {
		for(int j(0); j < top; j++) {
			if(players[i].getScore() > scores[j]) {
				win_ind[j] = i;
				scores[j] = players[i].getScore();
				j = 9999;
			};
		};
	};
	return win_ind;
}
#endif
