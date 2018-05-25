#ifndef ARENA_H
#define ARENA_H

#include "Glob.h"
#include "Player.h"
#include "Ref.h"

class Arena: private Ref {
public:
	//Constructor
	Arena();

	//Destructor
	~Arena();

	//Functions
	void Fight(vector<Player*>, vector<Player*>);
	vector<Player> Win(vector<Player>);

private:
	//Variables
	vector<Player> pred;
	vector<Player> prey;

	//Functions
};
// Public
Arena::Arena() {
}
Arena::~Arena() {
}
void Arena::Fight(vector<Player*> pred, vector<Player*> prey) {
	bool pred_pass_stlth = false;
	bool pred_pass_run = false;

	for(int predi(0); predi < pred.size(); predi++) {
		for(int preyi(0); preyi < prey.size(); preyi++) {
			// Troubleshooting Tool
			//cout << StlthChck(pred[predi], prey[preyi]) << "\n\n";

			pred_pass_stlth = StlthChck(pred[predi], prey[preyi]);
			pred_pass_run = SpdChck(pred[predi], prey[preyi]);
			//pred_pass_run = true;

			if(pred_pass_stlth && pred_pass_run) {
				if( prey[preyi]->getStat(bs) < pred[predi]->getStat(bs) ) {
					Brawl(pred[predi], prey[preyi]);
				} else {
					Brawl(pred[predi], prey[preyi]);
				};
				pred[predi]->setScore( pred[predi]->getScore() + TallyScore(pred[predi]) );
				prey[preyi]->setScore( prey[preyi]->getScore() + TallyScore(prey[preyi]) );

				pred[predi]->resetHp();
				prey[preyi]->resetHp();
			};
		};
	};
}
vector<Player> Arena::Win(vector<Player> players) {
	vector<Player> wp;
	vector<int> win_ind = Winners(players);

	for(int i(0); i < win_ind.size(); i++) {
		wp.push_back(players[win_ind[i]]);
		//cout << win_ind[i] << " ";
	};
	//cout << "\n\n";
	return wp;
}
#endif
