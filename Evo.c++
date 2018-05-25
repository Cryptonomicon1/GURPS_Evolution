#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include<cstdlib>
using std::rand;
using std::srand;

#include<vector>
using std::vector;

#include<string>
using std::string;
using std::to_string;

#include<cstring>
using std::strcmp;

#include<cmath>
using std::pow;
using std::ceil;
using std::floor;

#include<ctime>
using std::time;

#include "Glob.h"
#include "Player.h"
#include "Arena.h"
#include "Rec.h"

int main() {
	int num = 0;
	int mut_rnds = 100;
	bool test = true;

	srand(time(NULL));

	Arena A;
	Rec R;

	vector<Player> prd;
	vector<Player> pry;
	vector<Player*> prd_ptr;
	vector<Player*> pry_ptr;

	// Make Intial babies
	for(int i(0); i < win_cnt; i++) {
		prd.push_back(Player(to_string(num), "carnivore", false, test));
		num++;
		pry.push_back(Player(to_string(num), "herbivore", false, test));
		num++;
	};
	// Mutate Babies
	for(int i(0); i < 10; i++) {
		for(int j(0); j < prd.size(); j++) {
			prd[j].Mutate();
			pry[j].Mutate();
		};
	};
	// Save Initial Babies
	R.Save(prd, pry, 0, 0);

	for(int i(0); i < mut_rnds; i++) {
		//cout << i + 1 << " / " << mut_rnds << "\n";

		// Make Babies
		for(int j(0); j < win_cnt; j++) {
			for(int k(0); k < 2; k++) {
				prd.push_back( Player(prd[j]) );
				prd.back().setParent(prd[j].getNam());
				prd.back().setNam( to_string(num) );
				num++;
				pry.push_back( Player(pry[j]) );
				pry.back().setParent(pry[j].getNam());
				pry.back().setNam( to_string(num) );
				num++;
			};
		};
		// Mutate Babies
		for(int j(win_cnt); j < 10; j++) {
			for(int k(0); k < prd.size(); k++) {
				prd[k].Mutate();
				pry[k].Mutate();
			};
		};
		// Make Babies Fight
		for(int j(0); j < prd.size(); j++) {
			prd_ptr.push_back(&prd[j]);
			pry_ptr.push_back(&pry[j]);
		};
		A.Fight(prd_ptr, pry_ptr);
		prd_ptr.resize(0);
		pry_ptr.resize(0);

		// Save Babies
		R.Save(prd, pry, win_cnt, 0);

		// Cull The losers
		prd = A.Win(prd);
		pry = A.Win(pry);

		// Reset Scores
		for(int j(0); j < prd.size(); j++) {
			prd[j].setScore(0);
			pry[j].setScore(0);
		};
	};
	// Describe Animals
	for(int j(0); j < prd.size(); j++) {
		prd[j].DscSts();

		//cout << prd[j].getNam() << " " << prd[j].getScore() << " ";
		//cout << pry[j].getNam() << " " << pry[j].getScore() << "\n\n";
	};
	for(int j(0); j < prd.size(); j++) {
		pry[j].DscSts();
	};
	R.Record();
}
