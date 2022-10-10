#include <iostream>
#include <vector>
#include <memory.h>
#define MAX_LEN 8
using namespace std;

vector<pair<int, int>> start_point;
int map[MAX_LEN + 2][MAX_LEN + 2];
bool visited[MAX_LEN + 2][MAX_LEN + 2];
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,1,-1 };

int answer;
int len;
int limit;

void init() {
	for (int s = 0; s < MAX_LEN + 2; s++) {
		for (int t = 0; t < MAX_LEN + 2; t++) {
			map[s][t] = -1;
		}
	}
	memset(visited, false, sizeof(visited));
	start_point.clear();
	answer = 1;
}

void sol(int x, int y, int cur_height, int len, bool chance) { // dfs

	// 못가는 길이면
	if (map[x][y] == -1) {
		return;
	}

	for (int s = 0; s < 4; s++) { // 상하좌우 search
		int nx = x + dx[s]; int ny = y + dy[s];
		if (visited[nx][ny] == true) { // 이미 간 곳이면 거르고
			continue;
		}
		else { // 안 간 곳이면
			if (map[x + dx[s]][y + dy[s]] < cur_height) { // 그냥 갈 수 있는 곳이면
				visited[nx][ny] = true; // 방문 해본다
				sol(nx, ny, map[nx][ny], len + 1, chance); // 찬스 상태를 유지 하고 이동
				visited[nx][ny] = false; // 방문 정보를 복구한다
			}
			else if (chance && (map[nx][ny] - limit) < cur_height) { // 깎아서라도 갈 수 있는 곳이면
				visited[nx][ny] = true; // 방문 해본다
				sol(nx, ny, cur_height - 1, len + 1, false); // 찬스를 유지 하고 이동
				visited[nx][ny] = false; // 방문 정보를 복구한다
			}
		}
	}

	// get_answer
	if (len >= answer) {
		answer = len;
	}

	return;
}

int main() {

	int total_tc;
	cin >> total_tc;

	for (int cur = 1; cur <= total_tc; cur++) {

		// init
		init();

		// get data
		cin >> len;
		cin >> limit;
		int biggest = 0;
		for (int s = 1; s <= len; s++) {
			for (int t = 1; t <= len; t++) {
				cin >> map[s][t];
				if (map[s][t] > biggest) {
					biggest = map[s][t];
				}
			}
		}
		for (int s = 1; s <= len; s++) {
			for (int t = 1; t <= len; t++) {
				if (map[s][t] == biggest) {
					start_point.push_back(make_pair(s, t));
				}
			}
		}

		// sol
		for (int s = 0; s < start_point.size(); s++) {
			visited[start_point[s].first][start_point[s].second] = true;
			sol(start_point[s].first, start_point[s].second, biggest, 1, true);
			visited[start_point[s].first][start_point[s].second] = false;
		}

		// cout asnwer
		cout << "#" << cur << ' ' << answer << endl;;
	}
	return 0;
}