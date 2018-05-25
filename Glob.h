#ifndef GLOB_H
#define GLOB_H

enum ez {E = 0, A = 1, H = 2, V = 3};

const static int ez_tab[4][28] = {	{0,0,0,0,0,0,0,1,2,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76},
					{0,0,0,0,0,0,1,2,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80},
					{0,0,0,0,0,1,2,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84},
									{0,0,0,0,1,2,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88}};

enum stat {pts = 0, ft = 1, in = 2, sz = 3, age = 4, app = 5, st = 6, dx = 7, iq = 8, ht = 9, will = 10, per = 11, hp = 12, fp = 13, bs = 14, dr = 15, tl = 16, pry = 17, blk = 18, lb = 19, no_bl = 20, lt_bl = 21, md_bl = 22, hv_bl = 23, xhv_bl = 24, no_bm = 25, lt_bm = 26, md_bm = 27, hv_bm = 28, xhv_bm = 29, no_dge = 30, lt_dge = 31, md_dge = 32, hv_dge = 33, xhv_dge = 34};

enum skl {bwl = 0, stl = 1};
enum lim {low = 0, up = 1};
enum val {lv = 0, pt = 1};

const static int win_cnt = 3;
#endif
