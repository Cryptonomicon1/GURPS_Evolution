#ifndef SKILLS_H
#define SKILLS_H

#include"Glob.h"

#include<vector>
using std::vector;

#include<string>
using std::string;

class Skills {
public:
	//Constructor
	Skills();

	//Destructor
	~Skills();

	//Variables
	struct skill {
		string name;
		ez dif;
		int att;
		int lvl;
		int pts;
	};
	//Functions
	Skills::skill getSkl(int);
	string getSklNam(int);
	int getSklDff(int);
	int getSklAtt(int);
	int getSklLvl(int);
	int getSklPts(int);
	int getSklCnt();

	int SkillCost(int, Skills::skill);
	void setSkill(int, int);
	int SkillJump(int, Skills::skill);

private:
	vector<skill> skills;

};
Skills::Skills() {
	skills.push_back({"Brawling",ez::E,dx,-4,0});
	skills.push_back({"Stealth",ez::A,dx,-5,0});
}
Skills::~Skills() {
}
Skills::skill Skills::getSkl(int ref) {
	switch(ref) {
		case 0 :
		return skills[ref];
		break;
		case 1 :
		return skills[ref];
		break;
		default :
		break;
	}
}
string Skills::getSklNam(int ref) {
	return skills[ref].name;
}
int Skills::getSklDff(int ref) {
	return skills[ref].dif;
}
int Skills::getSklAtt(int ref) {
	return skills[ref].att;
}
int Skills::getSklLvl(int ref) {
	return skills[ref].lvl;
}
int Skills::getSklPts(int ref) {
	return skills[ref].pts;
}
int Skills::getSklCnt() {
	return skills.size();
}
int Skills::SkillCost(int end_lvl, Skills::skill sk) {
	int total = 0;

	if(end_lvl == sk.lvl) {
		return 0;
	} else if(end_lvl > sk.lvl) {
		for(int i(sk.lvl + 8); i <= end_lvl + 7; i++) {
			total -= ez_tab[sk.dif][i];
		};
	} else if(end_lvl < sk.lvl) {
		for(int i(sk.lvl + 7); i > end_lvl + 7; i--) {
			total += ez_tab[sk.dif][i];
		};
	};
	// Troubleshooting Tool
	//cout << name << " " << sk.lvl << " " << end_lvl << " " << sk.pts << " " << total << "\n";
	return total;
}
void Skills::setSkill(int end_lvl, int ref) {
	skill temp = skills[ref];

	end_lvl = SkillJump(end_lvl, skills[ref]);

	int cost = SkillCost(end_lvl, skills[ref]);
	if(cost != 0) {
		skills[ref].pts = skills[ref].pts + cost;
		skills[ref].lvl = end_lvl;
	};
	if(temp.pts == skills[ref].pts && temp.lvl != skills[ref].lvl || temp.pts != skills[ref].pts && temp.lvl == skills[ref].lvl) {
		cout << "Error Bad Skill Calc Player.h:927!" << "\n\n";
	};
}
int Skills::SkillJump(int end_lvl, Skills::skill sk) {
	if(end_lvl < -sk.dif-4) {
		return -sk.dif-4;
	} else if(end_lvl > 10) {
		return 10;
	} else if(end_lvl == -sk.dif-3) {
		return -sk.dif;
	} else if(end_lvl < -sk.dif) {
		return -sk.dif-4;
	} else return end_lvl;
}
#endif
