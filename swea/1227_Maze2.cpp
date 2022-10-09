//#include<iostream>
//#define MAP_LEN 100
//using namespace std;
//
//bool answer;
//bool is_map[MAP_LEN + 2][MAP_LEN + 2];
//int data_map[MAP_LEN + 2][MAP_LEN + 2];
//
//int start_x;
//int start_y;
//
//int dx[] = { 1, 0, -1 ,0 };
//int dy[] = { 0, 1, 0, -1 };
//
//void init_data();
//void get_data();
//
//void fs(int x, int y) {
//    // if already visited or answer done.
//    if (is_map[x][y] == true || answer == true) {
//        return;
//    }
//    else {
//        is_map[x][y] = true;
//        if (data_map[x][y] == 3) { // If can reach to destination.
//            answer = true;
//            return;
//        }
//        else {
//            for (int i = 0; i < 4; i++) { // search next place
//                if (data_map[x + dx[i]][y + dy[i]] != 1) {
//                    fs(x + dx[i], y + dy[i]);
//                }
//                else {
//                    continue;
//                }
//            }
//        }
//    }
//    return;
//}
//
//int main(int argc, char** argv)
//{
//    for (int tc = 1; tc <= 10; tc++)
//    {
//        int cur;
//        cin >> cur;
//
//        // init
//        init_data();
//        get_data();
//
//        // answer data;
//        fs(start_x, start_y);
//        cout << "#" << cur << ' ' << answer << endl;
//    }
//    return 0;
//}
//
//void init_data() {
//    answer = false;
//    for (int s = 0; s < MAP_LEN + 2; s++) {
//        for (int t = 0; t < MAP_LEN + 2; t++) {
//            is_map[s][t] = false;
//            data_map[s][t] = -1;
//        }
//    }
//    return;
//}
//
//void get_data() {
//    for (int s = 1; s <= MAP_LEN; s++) {
//        string cheeze;
//        cin >> cheeze;
//        for (int t = 1; t <= MAP_LEN; t++) {
//            data_map[s][t] = (cheeze[t - 1] - '0');
//            if (data_map[s][t] == 2) {
//                start_x = s;
//                start_y = t;
//            }
//            else {
//                continue;
//            }
//        }
//    }
//    return;
//}