#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>
#include <memory.h>
#define  MAX_LEN 8
using namespace std;

enum FLAG
{
	BOUNDARY = -1,
	CLEAN = 0,
	WALL = 1,
	VIRUS =2
};

int row_len;
int col_len;
int answer = 0;

vector<tuple<int, int>> clean_zone;
vector<tuple<int, int>> virus_zone;
vector<tuple<int, int>> virus_target_zone;
vector<tuple<int, int>> virus_rollback_zone;
bool visited[MAX_LEN + 2][MAX_LEN + 2];
FLAG map[MAX_LEN + 2][MAX_LEN + 2];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

void init_data()
{
	memset(visited, false, sizeof(visited));
	while (!virus_rollback_zone.empty())
	{
		map[get<0>(virus_rollback_zone.back())][get<1>(virus_rollback_zone.back())] = FLAG::CLEAN;
		virus_rollback_zone.pop_back();
	}
}

void get_result()
{
	int counter = 0;
	for (int s = 1; s <= row_len; s++)
	{
		for (int t = 1; t <= col_len; t++)
		{
			if (map[s][t] == FLAG::CLEAN)
			{
				counter++;
			}
		}
	}
	if (counter > answer) {
		answer = counter;
	}
}

void BFS(int cur_row, int cur_col)
{
	if (visited[cur_row][cur_col] || map[cur_row][cur_col] != FLAG::CLEAN)
	{
		return;
	}
	else
	{
		visited[cur_row][cur_col] = true;
		map[cur_row][cur_col] = FLAG::VIRUS;
		virus_rollback_zone.push_back(make_tuple(cur_row, cur_col));
		for (int s = 0; s < 4; s++)
		{
			tuple<int, int> next_posi = make_tuple(cur_row + dx[s], cur_col + dy[s]);
			if (!visited[get<0>(next_posi)][get<1>(next_posi)] && map[get<0>(next_posi)][get<1>(next_posi)] == FLAG::CLEAN)
			{
				virus_target_zone.push_back(next_posi);
			}
			else
			{
				continue;
			}
		}
		return;
	}
}

void simulation_virus()
{
	// 최초 BFS 돌려야 하는 포지션들 선별
	for (auto iter = virus_zone.begin(); iter != virus_zone.end(); iter++)
	{
		int cur_virus_row = get<0>(*iter);
		int cur_virus_col = get<1>(*iter);
		//cout << "cur_virus_posi : " << cur_virus_row << " , " << cur_virus_col << endl;
		for (int s = 0; s < 4; s++)
		{
			tuple<int, int> next_posi = make_tuple(cur_virus_row + dx[s], cur_virus_col +dy[s]);
			//cout << "cur_next_posi : " << get<0>(next_posi) << " , " << get<1>(next_posi) << endl;
			if (!visited[get<0>(next_posi)][get<1>(next_posi)] && (map[get<0>(next_posi)][get<1>(next_posi)] == FLAG::CLEAN))
			{
				virus_target_zone.push_back(next_posi);
			}
			else
			{
				continue;
			}
		}
	}

	// 전체 BFS 시작
	while (!virus_target_zone.empty())
	{
		int cur_row = get<0>(virus_target_zone.back());
		int cur_col = get<1>(virus_target_zone.back());
		virus_target_zone.pop_back();
		BFS(cur_row, cur_col);
	}
}

void simulation_build_wall(int cur_count, int vec_idx, int vec_size)
{
	if (cur_count >= 3)
	{
		// 만약 벽 3개를 모두 세웠다면
		simulation_virus();
		get_result();
		init_data();
		return;
	}
	else
	{
		if (vec_idx < vec_size)
		{
			// 벽을 세울 경우
			map[get<0>(clean_zone[vec_idx])][get<1>(clean_zone[vec_idx])] = FLAG::WALL;
			simulation_build_wall(cur_count + 1, vec_idx + 1, vec_size);
			map[get<0>(clean_zone[vec_idx])][get<1>(clean_zone[vec_idx])] = FLAG::CLEAN;

			// 벽을 안세울 경우
			simulation_build_wall(cur_count, vec_idx + 1, vec_size);
		}
		else
		{
			return;
		}
	}
}

int main()
{
	init_data();
	cin >> row_len >> col_len;

	for (int s = 0; s <= row_len + 1; s++)
	{
		for (int t = 0; t <= col_len + 1; t++)
		{
			map[s][t] = FLAG::BOUNDARY;
		}
	}

	for (int s = 1; s <= row_len; s++)
	{
		for (int t = 1; t <= col_len; t++)
		{
			int cur_data;
			cin >> cur_data;

			FLAG temp_data = static_cast<FLAG>(cur_data);
			if (temp_data == FLAG::CLEAN)
			{
				clean_zone.push_back(make_tuple(s, t));
			}

			if (temp_data == FLAG::VIRUS)
			{
				virus_zone.push_back(make_tuple(s, t));
			}

			map[s][t] = temp_data;
		}
	}

	int clean_zone_size = static_cast<int>(clean_zone.size());
	simulation_build_wall(0, 0, clean_zone_size);

	cout << answer << endl;

	return 0;
}