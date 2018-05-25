#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

#include<string>
using std::string;

#include<vector>
using std::vector;

#include<cmath>
using std::pow;
using std::ceil;
using std::floor;

#include "Glob.h"

class PlayerStats {
public:
	//Constructor
	PlayerStats();

	//Destructor
	~PlayerStats();

	//Functions
	void Save();
	void Load();

	float getStt(int);
	int getPts(int);

	void setSt(int);
	void setDx(int);
	void setIq(int);
	void setHt(int);
	void setHitPts(int);
	void resetHitPts();
	void setWill(int);
	void setPer(int);
	void setBs(float);
	void setBm(int);
	void setSz(int);
	void setPts(int);

private:
	void CalcSt();
	void CalcDx();
	void CalcIq();
	void CalcHt();
	void CalcHp();
	void CalcWill();
	void CalcPer();
	void CalcBs();
	void CalcBl();
	void CalcBm();
	void CalcDg();
	void CalcSz();

	int def_stats[35];
	int stats[35][2];
	int costs[35];
	int limits[35][2];
	float basic_speed;
	float weight;

	int b_stats[35][2];
	float b_speed;
	float b_weight;

	int Rnd(float);
};
//Public
PlayerStats::PlayerStats() {
	int def_stt[35] =	{0,6,0,0,20,0,10,10,10,10,10,10,10,10,0,0,3,0,0,145,20,40,60,80,100,5,4,3,2,1,8,7,6,5,4};
	int def_csts[35] =	{0,0,0,0,0,4,10,20,20,10,5,5,5,5,5,0,0,0,0,0,5,0,0,0,0,5,0,0,0,0,5,0,0,0,0};
	int def_low_lims[35] = {0,0,0,-11,0,-10,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int def_up_lims[35] = {0,0,0,3,100,10,100,20,20,100,20,100,100,100,12,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};

	for(int i(0); i < 35; i++) {
		def_stats[i] = def_stt[i];
		stats[i][lv] = def_stt[i];
		stats[i][pt] = 0;
		costs[i] = def_csts[i];
		limits[i][low] = def_low_lims[i];
		limits[i][up] = def_up_lims[i];
	};
	basic_speed = def_stt[bs];
	weight = def_stt[lb];
}
PlayerStats::~PlayerStats() {
}
void PlayerStats::Save() {
	for(int i(0); i < 35; i++) {
		for(int j(0); j < 2; j++) {
			b_stats[i][j] = stats[i][j];
		};
	};
	b_speed = basic_speed;
	b_weight = weight;
}
void PlayerStats::Load() {
	for(int i(0); i < 35; i++) {
		for(int j(0); j < 2; j++) {
			stats[i][j] = b_stats[i][j];
		};
	};
	basic_speed = b_speed;
	weight = b_weight;
	setSz(stats[sz][lv]);
}
float PlayerStats::getStt(int stt) {
	if(stt == bs) {
		return basic_speed;
	} else if(stt == lb) {
		return weight;
	} else return stats[stt][lv];
}
int PlayerStats::getPts(int stt) {
	return stats[stt][pt];
}
void PlayerStats::setSt(int strength) {
	if(strength >= limits[st][low] && strength <= limits[st][up]) {
		stats[st][pt] = (10 * costs[st]) - (costs[st] * strength);
		CalcSt();
	};
}
void PlayerStats::setDx(int dex) {
	if(dex >= limits[dx][low] && dex <= limits[dx][up]) {
		stats[dx][pt] = (10 * costs[dx]) - (costs[dx] * dex);
		CalcDx();
	};
}
void PlayerStats::setIq(int intel) {
	if(intel >= limits[iq][low] && intel <= limits[iq][up]) {
		stats[iq][pt] = (10 * costs[iq]) - (costs[iq] * intel);
		CalcIq();
	};
}
void PlayerStats::setHt(int health) {
	if(health >= limits[ht][low] && health <= limits[ht][up]) {
		stats[ht][pt] = (10 * costs[ht]) - (costs[ht] * health);
		CalcHt();
	};
}
void PlayerStats::setHitPts(int hits) {
	stats[hp][lv] = hits;
}
void PlayerStats::resetHitPts() {
	CalcHp();
}
void PlayerStats::setWill(int wil) {
	if(wil >= limits[will][low] && wil <= limits[will][up]) {
		int base_points = costs[will] * stats[iq][lv];
		int set_points = costs[will] * wil;
		stats[will][pt] = base_points - set_points;
		CalcWill();
	};
}
void PlayerStats::setPer(int perception) {
	if(perception >= limits[per][low] && perception <= limits[per][up]) {
		int base_points = costs[per] * stats[iq][lv];
		int set_points = costs[per] * perception;
		stats[per][pt] = base_points - set_points;
		CalcPer();
	};
}
void PlayerStats::setBs(float speed) {
	if(speed >= limits[bs][low] && speed <= limits[bs][up]) {
		int base_points = costs[bs] * ( stats[ht][lv] + stats[dx][lv] );
		int set_points = costs[bs] * int(speed / 0.25);
		stats[bs][pt] = base_points - set_points;
		CalcBs();
	};
}
void PlayerStats::setBm(int move) {
	if(move >= limits[no_bm][low] && move <= limits[no_bm][up]) {
		int base_points = costs[no_bm] * int( stats[bs][lv] );
		int set_points = costs[no_bm] * move;
		stats[no_bm][pt] = base_points - set_points;
		CalcBm();
	};
}
void PlayerStats::setSz(int size) {
	if(size >= limits[sz][low] && size <= limits[sz][up]) {
		stats[sz][lv] = size;
		CalcSz();
	};
}
void PlayerStats::setPts(int set_points) {
	stats[pts][pt] = set_points;
}
// Calculations just recalculate secondary attributes
// from other attributes and points dedicated to the
// calculated attribute.
//---------------------------------------------------------------
void PlayerStats::CalcSt() {
	int strength1 = -stats[st][pt] / costs[st];
	int strength2 = 10;
	stats[st][lv] = strength1 + strength2;
	CalcBl();
}
void PlayerStats::CalcDx() {
	int dex1 = -stats[dx][pt] / costs[dx];
	int dex2 = 10;
	stats[dx][lv] = dex1 + dex2;
	CalcBs();
}
void PlayerStats::CalcIq() {
	int intel1 = -stats[iq][pt] / costs[iq];
	int intel2 = 10;
	stats[iq][lv] = intel1 + intel2;
	CalcWill();
	CalcPer();
}
void PlayerStats::CalcHt() {
	int health1 = -stats[ht][pt] / costs[ht];
	int health2 = 10;
	stats[ht][lv] = health1 + health2;
	CalcBs();
	CalcHp();
}
void PlayerStats::CalcHp() {
	int hit_points1 = -stats[hp][pt] / costs[hp];
	int hit_points2 = stats[ht][lv];
	stats[hp][lv] = hit_points1 + hit_points2;
}
void PlayerStats::CalcWill() {
	int will1 = -stats[will][pt] / costs[will];
	int will2 = stats[iq][lv];
	stats[will][lv] = will1 + will2;
}
void PlayerStats::CalcPer() {
	int perception1 = -stats[per][pt] / costs[per];
	int perception2 = stats[iq][lv];
	stats[per][lv] = perception1 + perception2;
}
void PlayerStats::CalcBl() {
	int lift = ( stats[st][lv] * stats[st][lv] ) / costs[no_bl];
	stats[no_bl][lv] = lift;

	for(int i(1); i < 5; i++) {
		stats[no_bl + i][lv] = (i+1) * stats[no_bl][lv];
	};
}
void PlayerStats::CalcBm() {
	int move1 = -stats[no_bm][pt] / costs[no_bm];
	int move2 = basic_speed;
	int move3 = stats[sz][lv];

	if(move1 + move2 + move3 >= 1) {
		stats[no_bm][lv] = move1 + move2 + move3;
	} else stats[no_bm][lv] = 1;

	for(int i(1); i < 5; i++) {
		stats[no_bm + i][lv] = (1 - (0.2*i)) * stats[no_bm][lv];
	};
}
void PlayerStats::CalcDg() {
	stats[no_dge][lv] =  stats[no_bm][lv] + 3;

	for(int i(1); i < 5; i++) {
		stats[no_dge + i][lv] = stats[no_dge][lv] - i;
	};
}
void PlayerStats::CalcBs() {
	float speed1 = -0.25 * ( stats[bs][pt] / float(costs[bs]) );
	float speed2 = float( stats[ht][lv] + stats[dx][lv] ) / 4;
	basic_speed = speed1 + speed2;
	CalcBm();
	CalcDg();

	// Troubleshooting Tool
	// This function was very buggy.
	// cout << "speed: " << stats2[bs][0] << '\n';
}
void PlayerStats::CalcSz() {
	float r = 0.24520346217816072;
	float m = pow(145, r);

	switch(stats[sz][lv]) {
		case -10 :	stats[ft][lv] = 0;
					stats[in][lv] = 2;
					costs[st] = 18;
					break;

		case -9 :	stats[ft][lv] = 0;
					stats[in][lv] = 3;
					costs[st] = 18;
					break;

		case -8 :	stats[ft][lv] = 0;
					stats[in][lv] = 4;
					costs[st] = 18;
					break;

		case -7 :	stats[ft][lv] = 0;
					stats[in][lv] = 5;
					costs[st] = 17;
					break;

		case -6 :	stats[ft][lv] = 0;
					stats[in][lv] = 7;
					costs[st] = 16;
					break;

		case -5 :	stats[ft][lv] = 0;
					stats[in][lv] = 10;
					costs[st] = 15;
					break;

		case -4 :	stats[ft][lv] = 1;
					stats[in][lv] = 6;
					costs[st] = 14;
					break;

		case -3 :	stats[ft][lv] = 2;
					stats[in][lv] = 0;
					costs[st] = 13;
					break;

		case -2 :	stats[ft][lv] = 3;
					stats[in][lv] = 0;
					costs[st] = 12;
					break;

		case -1 :	stats[ft][lv] = 4;
					stats[in][lv] = 6;
					costs[st] = 11;
					break;

		case 0 :	stats[ft][lv] = 6;
					stats[in][lv] = 0;
					costs[st] = 10;
					break;

		case 1 :	stats[ft][lv] = 9;
					stats[in][lv] = 0;
					costs[st] = 9;
					break;

		case 2 :	stats[ft][lv] = 15;
					stats[in][lv] = 0;
					costs[st] = 8;
					break;

		case 3 :	stats[ft][lv] = 21;
					stats[in][lv] = 0;
					costs[st] = 7;
					break;

		case 4 :	stats[ft][lv] = 30;
					stats[in][lv] = 0;
					costs[st] = 6;
					break;

		case 5 :	stats[ft][lv] = 45;
					stats[in][lv] = 0;
					costs[st] = 5;
					break;

		case 6 :	stats[ft][lv] = 60;
					stats[in][lv] = 0;
					costs[st] = 4;
					break;

		case 7 :	stats[ft][lv] = 90;
					stats[in][lv] = 0;
					costs[st] = 3;
					break;

		case 8 :	stats[ft][lv] = 150;
					stats[in][lv] = 0;
					costs[st] = 2;
					break;

		case 9 :	stats[ft][lv] = 210;
					stats[in][lv] = 0;
					costs[st] = 2;
					break;

		case 10 :	stats[ft][lv] = 300;
					stats[in][lv] = 0;
					costs[st] = 2;
					break;

		case 11 :	stats[ft][lv] = 450;
					stats[in][lv] = 0;
					costs[st] = 2;
					break;
	}
	float feet = stats[ft][lv] + ( float(stats[in][lv]) / 12.0 );
	weight = pow( feet * m / 6, (1/r));
	setSt(stats[st][lv]);
	CalcBm();
}
int PlayerStats::Rnd(float in) {
	return (in > 0.0) ? floor(in + 0.5) : ceil(in - 0.5);
}
#endif
