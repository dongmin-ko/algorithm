//#include<iostream>
//#include<string>
//#include<memory.h>
//#include<queue>
//#include<tuple>
//using namespace std;
//
//typedef enum {
//    LEFT = 0,
//    RIGHT,
//    UP,
//    DOWN
//}DIR;
//
//bool answer;
//int max_r, max_c; // map size, col, row
//char map[22][22];
//bool visited[22][22][16][4]; // row, col, value, dir -> to check same condition was happened.
//
//queue<tuple<int, int, int, DIR>> gamers; // row, col, dir, score
//
//char read_current_mask(int r, int c) {
//    return map[r][c];
//}
//
//void play(int r, int c, int score, DIR dir) {
//
//    // 기저 조건
//    if (visited[r][c][score][dir] == true) { // if visited this position with new condition -> no need to see more.
//        return; // 볼필요 x
//    }
//    else {
//        visited[r][c][score][dir] = true; // if visited this position with new condition -> go to main logic.
//    }
//
//    // '#' flag
//    bool sharp_is = false;
//    bool sharp_flag[4] = { false, false ,false ,false};
//    bool question_flag(false);
//
//    // map search
//    switch (map[r][c])
//    {
//        case '@':
//            answer = true;
//            while (gamers.size()) {
//                gamers.pop();
//            }
//            return;
//            break;
//
//        case '#': // '#' is outlines of total map.
//            sharp_is = true;
//            sharp_flag[dir] = true;
//            break;
//
//        case '<':
//            dir = LEFT;
//            break;
//
//        case '>':
//            dir = RIGHT;
//            break;
//
//        case '^':
//            dir = UP;
//            break;
//
//        case 'v':
//            dir = DOWN;
//            break;
//
//        case '_':
//            if (score == 0) { dir = RIGHT; }
//            else { dir = LEFT; }
//            break;
//
//        case '|':
//            if (score == 0) { dir = DOWN; }
//            else { dir = UP; }
//            break;
//
//        case '+':
//            if (score >= 15) { score = 0; }
//            else { score += 1; }
//            break;
//
//        case '-':
//            if (score <= 0) { score = 15; }
//            else { score -= 1; }
//            break;
//
//        case '?':
//            question_flag = true;
//            break;
//
//        case '.':
//            break;
//
//        default: // if 0~9
//            score = (int)(map[r][c] - '0');
//            break;
//
//        // end of switch
//    }
//
//    // main logic
//
//    // exception : sharp_flag (position changer)
//    if (sharp_is) {
//        if (sharp_flag[UP] == true) {
//            r = max_r;
//            play(r, c, score, dir);
//            return;
//        }
//        else if (sharp_flag[DOWN] == true) {
//            r = 1;
//            play(r, c, score, dir);
//            return;
//        }
//        else if (sharp_flag[RIGHT] == true) {
//            c = 1;
//            play(r, c, score, dir);
//            return;
//        }
//        else { // when sharp_flag[LEFT] == true
//            c = max_c;
//            play(r, c, score, dir);
//            return;
//        }
//    }
//
//    // question_flag (direction changer)
//    if (question_flag) {
//        gamers.push(make_tuple(r, c + 1, score, RIGHT));
//        gamers.push(make_tuple(r, c - 1, score, LEFT));
//        gamers.push(make_tuple(r - 1, c, score, UP));
//        gamers.push(make_tuple(r + 1, c, score, DOWN));
//        return;
//    }
//    else { // when normal
//        if (dir == RIGHT) {
//            c += 1;
//            play(r, c, score, dir);
//            return;
//        }
//        else if (dir == LEFT) {
//            c -= 1;
//            play(r, c, score, dir);
//            return;
//        }
//        else if (dir == UP) {
//            r -= 1;
//            play(r, c, score, dir);
//            return;
//        }
//        else { // dir == DOWN
//            r += 1;
//            play(r, c, score, dir);
//            return;
//        }
//    }
//
//    // ok, let's go on to next recursive.
//
//    return;
//}
//
//int main(int argc, char** argv)
//{
//    int tc;
//    cin >> tc;
//    for (int cur = 1; cur <= tc; cur++)
//    {
//        // init
//        memset(map, '#', sizeof(map));
//        memset(visited, false, sizeof(visited));
//        cin >> max_r >> max_c;
//        answer = false;
//        gamers.push(make_tuple(1, 1, 0, RIGHT));
//
//        // get map
//        for (int r = 1; r <= max_r; r++) {
//            string receiver;
//            cin >> receiver;
//            for (int c = 1; c <= max_c; c++) {
//                map[r][c] = receiver[c - 1];
//            }
//        }
//
//        // let the game begging
//        while (gamers.size() != 0) {
//            tuple<int, int, int, DIR> current_gamer = gamers.front();
//            gamers.pop();
//            play(get<0>(current_gamer), get<1>(current_gamer), get<2>(current_gamer), get<3>(current_gamer));
//        }
//
//        if (answer) {
//            cout << "#" << cur << ' ' << "YES" << endl;
//        }
//        else {
//            cout << "#" << cur << ' ' << "NO" << endl;
//        }
//    }
//    return 0;
//}