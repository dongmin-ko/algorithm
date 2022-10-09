//#include <iostream>
//#include <string>
//#include <memory.h>
//#include <queue>
//#include <tuple>
//#define MAX_LEN 100
//using namespace std;
//bool visited[MAX_LEN][MAX_LEN];
//int map_record[MAX_LEN][MAX_LEN];
//int map[MAX_LEN][MAX_LEN];
//int map_len;
//int dx[] = { 1,0,0,-1 };
//int dy[] = { 0,1,-1,0 };
//int answer;
//queue<tuple<int, int>> point;
//
//void init() {
//
//	cin >> map_len;
//	for (int s = 0; s < map_len; s++) {
//		for (int t = 0; t < map_len; t++) {
//			map_record[s][t] = (MAX_LEN * MAX_LEN * 9);
//			visited[s][t] = false;
//		}
//	} map_record[0][0] = 0;
//
//	string map_line;
//	for (int u = 0; u < map_len; u++) {
//		cin >> map_line;
//		for (int v = 0; v < map_len; v++) {
//			map[u][v] = (map_line[v] - '0');
//		}
//	}
//
//	return;
//}
//
//void game(int r, int c) {
//
//	for (int s = 0; s < 4; s++) {
//		int new_r = r + dx[s];
//		int new_c = c + dy[s];
//		if (new_r < map_len && new_c < map_len && new_r >= 0 && new_c >= 0)
//		{
//			if (map_record[r][c] + map[r][c] < map_record[new_r][new_c]) // 만약 다음 좌표가 최신화되어 주변을 다시 업데이트 해줘야 할 경우.
//			{
//				visited[new_r][new_c] = true; // 해당 좌표 방문 표기
//				map_record[new_r][new_c] = map_record[r][c] + map[r][c]; // 최신화
//				point.push(make_tuple(new_r, new_c)); // 해당 좌표 최신화로 인해 영향성 받는 좌표 모두 다시 최신화 해주어야 하므로 재 방문.
//
//			}
//			if (visited[new_r][new_c] == false) // 만약 한번도 안가본 좌표면
//			{
//				visited[new_r][new_c] = true; // 해당 좌표 방문 표기
//				point.push(make_tuple(new_r, new_c)); // 방문
//			}
//		}
//	}
//	return;
//}
//
//int main() {
//
//	int total_tc;
//	cin >> total_tc;
//	for (int tc = 1; tc <= total_tc; tc++) {
//		//init data
//		init();
//
//		// start game
//		point.push(make_tuple(0, 0));
//		while (!point.empty()) {
//			game(get<0>(point.front()), get<1>(point.front()));
//			point.pop();
//		}
//		answer = map_record[map_len - 1][map_len - 1];
//		cout << '#' << tc << ' ' << answer << endl;
//	}
//
//	return 0;
//}