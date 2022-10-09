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
//			if (map_record[r][c] + map[r][c] < map_record[new_r][new_c]) // ���� ���� ��ǥ�� �ֽ�ȭ�Ǿ� �ֺ��� �ٽ� ������Ʈ ����� �� ���.
//			{
//				visited[new_r][new_c] = true; // �ش� ��ǥ �湮 ǥ��
//				map_record[new_r][new_c] = map_record[r][c] + map[r][c]; // �ֽ�ȭ
//				point.push(make_tuple(new_r, new_c)); // �ش� ��ǥ �ֽ�ȭ�� ���� ���⼺ �޴� ��ǥ ��� �ٽ� �ֽ�ȭ ���־�� �ϹǷ� �� �湮.
//
//			}
//			if (visited[new_r][new_c] == false) // ���� �ѹ��� �Ȱ��� ��ǥ��
//			{
//				visited[new_r][new_c] = true; // �ش� ��ǥ �湮 ǥ��
//				point.push(make_tuple(new_r, new_c)); // �湮
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