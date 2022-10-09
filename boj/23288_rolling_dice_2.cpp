//#include <iostream>
//#include <algorithm>
//#include <tuple>
//#include <memory.h>
//#define  MAP_MAX 20
//#define  BOUNDARY -1
//using namespace std;
//
//int dx[4] = { 1, -1, 0, 0 };
//int dy[4] = { 0, 0, 1, -1 };
//
//bool visited[MAP_MAX + 2][MAP_MAX + 2];
//int map[MAP_MAX + 2][MAP_MAX + 2];
//int map_dp[MAP_MAX + 2][MAP_MAX + 2];
//int map_row_max;
//int map_col_max;
//int cur_answer;
//int move_time;
//
//int temp_dice[6];
//int dice[6];
//
//int answer;
//
//typedef enum dice_direc {
//    dTOP = 0,
//    dBOT = 1,
//    dUP =2,
//    dDOWN = 3,
//    dLEFT = 4,
//    dRIGHT = 5
//}DICE_DIREC;
//
//typedef enum roll_direc {
//    rUP = 10,
//    rRIGHT = 11,
//    rDOWN = 12,
//    rLEFT =13
//}ROLL_DIREC;
//
//int roll_dice(ROLL_DIREC direc) {
//
//    // back up dice
//    memcpy(temp_dice, dice, sizeof(temp_dice));
//
//    // roll dice
//    switch (direc)
//    {
//    case ROLL_DIREC::rUP:
//        dice[DICE_DIREC::dUP] = temp_dice[DICE_DIREC::dTOP];
//        dice[DICE_DIREC::dTOP] = temp_dice[DICE_DIREC::dDOWN];
//        dice[DICE_DIREC::dDOWN] = temp_dice[DICE_DIREC::dBOT];
//        dice[DICE_DIREC::dBOT] = temp_dice[DICE_DIREC::dUP];
//        break;
//
//    case ROLL_DIREC::rDOWN:
//        dice[DICE_DIREC::dTOP] = temp_dice[DICE_DIREC::dUP];
//        dice[DICE_DIREC::dDOWN] = temp_dice[DICE_DIREC::dTOP];
//        dice[DICE_DIREC::dBOT] = temp_dice[DICE_DIREC::dDOWN];
//        dice[DICE_DIREC::dUP] = temp_dice[DICE_DIREC::dBOT];
//        break;
//
//    case ROLL_DIREC::rLEFT:
//        dice[DICE_DIREC::dLEFT] = temp_dice[DICE_DIREC::dTOP];
//        dice[DICE_DIREC::dTOP] = temp_dice[DICE_DIREC::dRIGHT];
//        dice[DICE_DIREC::dRIGHT] = temp_dice[DICE_DIREC::dBOT];
//        dice[DICE_DIREC::dBOT] = temp_dice[DICE_DIREC::dLEFT];
//        break;
//
//    case ROLL_DIREC::rRIGHT:
//        dice[DICE_DIREC::dRIGHT] = temp_dice[DICE_DIREC::dTOP];
//        dice[DICE_DIREC::dBOT] = temp_dice[DICE_DIREC::dRIGHT];
//        dice[DICE_DIREC::dLEFT] = temp_dice[DICE_DIREC::dBOT];
//        dice[DICE_DIREC::dTOP] = temp_dice[DICE_DIREC::dLEFT];
//        break;
//
//    default: // impossible case
//        break;
//    }
//
//    // return bot value of dice
//    return dice[DICE_DIREC::dBOT];
//}
//
//int get_next_roll_direc(int bot_num, int map_num, ROLL_DIREC cur_direc) {
//
//    if (bot_num > map_num) { // clock wise
//        if (cur_direc != ROLL_DIREC::rLEFT) {
//            return (cur_direc + 1);
//        }
//        else {
//            return ROLL_DIREC::rUP;
//        }
//    }
//    else if (bot_num < map_num) { // reverse clock wise
//        if (cur_direc != ROLL_DIREC::rUP) {
//            return (cur_direc -1);
//        }
//        else {
//            return ROLL_DIREC::rLEFT;
//        }
//    }
//    else { // same direc
//        return cur_direc;
//    }
//}
//
//void init() {
//    // set dice data
//    dice[DICE_DIREC::dUP] = 2;
//    dice[DICE_DIREC::dTOP] = 1;
//    dice[DICE_DIREC::dDOWN] = 5;
//    dice[DICE_DIREC::dBOT] = 6;
//    dice[DICE_DIREC::dLEFT] = 4;
//    dice[DICE_DIREC::dRIGHT] = 3;
//
//    // init visited, map boundary
//    memset(visited, false, sizeof(visited));
//    memset(map_dp, 0, sizeof(map_dp));
//
//    // get len data
//    cin >> map_row_max;
//    cin >> map_col_max;
//    cin >> move_time;
//
//    // init map boundary
//    for (int s = 0; s <= map_row_max+1; s++) {
//        for (int t = 0; t <= map_col_max+1; t++) {
//            map[s][t] = BOUNDARY;
//        }
//    }
//
//    // get map data
//    for (int s = 1; s <= map_row_max; s++) {
//        for (int t = 1; t <= map_col_max; t++) {
//            cin >> map[s][t];
//        }
//    }
//
//    // clear answer
//    cur_answer = 0;
//    answer = 0;
//}
//
//void init_visited() {
//    memset(visited, false, sizeof(visited));
//}
//
//void get_sum(int row, int col, int target) {
//    visited[row][col] = true;
//    cur_answer += target;
//    for (int s = 0; s < 4; s++) {
//        int next_row = row + dx[s];
//        int next_col = col + dy[s];
//        if (visited[next_row][next_col] || (map[next_row][next_col] == BOUNDARY) || map[next_row][next_col] != target) {
//            continue;
//        }
//        else {
//            get_sum(next_row, next_col, target);
//        }
//    }
//}
//
//void simulation(int row, int col) {
//    if (map_dp[row][col] != 0) {
//        answer += map_dp[row][col];
//    }
//    else {
//        get_sum(row, col, map[row][col]);
//        map_dp[row][col] = cur_answer;
//        answer += cur_answer;
//        cur_answer = 0;
//    }
//    return;
//}
//
//int main() {
//
//    // init
//    init();
//
//    // simul
//    int cur_move_time = 1;
//    int cur_row = 1;
//    int cur_col = 2;
//    int cur_roll_direc = ROLL_DIREC::rRIGHT;
//
//    while (cur_move_time <= move_time)
//    {
//        simulation(cur_row, cur_col);
//        cur_roll_direc = get_next_roll_direc( roll_dice(static_cast<ROLL_DIREC>(cur_roll_direc)), map[cur_row][cur_col], static_cast<ROLL_DIREC>(cur_roll_direc) );
//        if (static_cast<ROLL_DIREC>(cur_roll_direc) == ROLL_DIREC::rUP)
//        {
//            if (map[cur_row - 1][cur_col] == BOUNDARY) {
//                cur_row += 1;
//                cur_roll_direc = ROLL_DIREC::rDOWN;
//            }
//            else {
//                cur_row -= 1;
//            }
//        }
//        else if (static_cast<ROLL_DIREC>(cur_roll_direc) == ROLL_DIREC::rDOWN)
//        {
//            if (map[cur_row + 1][cur_col] == BOUNDARY) {
//                cur_row -= 1;
//                cur_roll_direc = ROLL_DIREC::rUP;
//            }
//            else {
//                cur_row += 1;
//            }
//        }
//        else if (static_cast<ROLL_DIREC>(cur_roll_direc) == ROLL_DIREC::rLEFT)
//        {
//            if (map[cur_row][cur_col-1] == BOUNDARY) {
//                cur_col += 1;
//                cur_roll_direc = ROLL_DIREC::rRIGHT;
//            }
//            else {
//                cur_col -= 1;
//            }
//        }
//        else // when ROLL_DIREC::RIGHT
//        {
//            if (map[cur_row][cur_col+1] == BOUNDARY) {
//                cur_col -= 1;
//                cur_roll_direc = ROLL_DIREC::rLEFT;
//            }
//            else {
//                cur_col += 1;
//            }
//        }
//        init_visited();
//        cur_move_time++;
//    }
//
//    // answer
//    cout << answer << endl;
//
//    return 0;
//}