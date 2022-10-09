//#include<iostream>
//#define MAP_LEN 100
//#define DOWN 0
//#define RIGHT 1
//#define LEFT 2
//using namespace std;
//int answer = -1;
//int last_count = 9999;
//int map[MAP_LEN + 2][MAP_LEN + 2];
//
//void find_answer(int row, int col, int direc, int counter, int start) {
//    if (counter > last_count) { // if counter is already bigger than last one
//        return;
//    }
//    else {
//        if ((row == MAP_LEN) && (map[row][col] == 1)) { // when position is reached to goal
//            if (counter <= last_count) {
//                last_count = counter;
//                answer = start;
//                return;
//            }
//            else {
//                return;
//            }
//        }
//        else {
//            if (direc == DOWN) {
//                if (map[row][col + 1] == 1) {
//                    find_answer(row, col + 1, RIGHT, counter + 1, start);
//                    return;
//                }
//                else if (map[row][col - 1] == 1) {
//                    find_answer(row, col - 1, LEFT, counter + 1, start);
//                    return;
//                }
//                else if (map[row + 1][col] == 1) {
//                    find_answer(row + 1, col, DOWN, counter + 1, start);
//                    return;
//                }
//                else {
//                    return;
//                }
//            }
//            else if (direc == LEFT) {
//                if (map[row + 1][col] == 1) {
//                    find_answer(row + 1, col, DOWN, counter + 1, start);
//                }
//                else {
//                    find_answer(row, col - 1, LEFT, counter + 1, start);
//                }
//            }
//            else if (direc == RIGHT) {
//                if (map[row + 1][col] == 1) {
//                    find_answer(row + 1, col, DOWN, counter + 1, start);
//                }
//                else {
//                    find_answer(row, col + 1, RIGHT, counter + 1, start);
//                }
//            }
//            else {
//                return;
//            }
//        }
//    }
//}
//
//int main(int argc, char** argv)
//{
//    for (int test_case = 1; test_case <= 10; test_case++)
//    {
//        answer = -1;
//        last_count = 9999;
//        int cur = 0;
//        cin >> cur;
//        // set boundary
//        for (int s = 0; s <= MAP_LEN + 1; s++) {
//            map[0][s] = -1;  map[s][0] = -1;
//            map[MAP_LEN + 1][s] = -1; map[s][MAP_LEN + 1] = -1;
//        }
//
//        // get data
//        int flag = 0;
//        for (int r = 1; r <= MAP_LEN; r++) {
//            for (int c = 1; c <= MAP_LEN; c++) {
//                cin >> flag;
//                map[r][c] = flag;
//            }
//        }
//
//        // cal data
//        for (int c = 1; c <= MAP_LEN; c++) {
//            if (map[1][c] == 1) {
//                find_answer(1, c, DOWN, 1, c - 1);
//            }
//            else {
//                continue;
//            }
//        }
//        cout << "#" << cur << " " << answer << endl;
//    }
//    return 0;//정상종료시 반드시 0을 리턴해야합니다.
//}