#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <tuple>
#include <math.h>
#define MAX_LEN 100
using namespace std;

int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

int total_fishbowl = 0;
int move_counter = 0;
int difference = 0;
int max_num = 0;
int min_num = 10000000;

tuple<int, int> sp;
vector <int> fish_list;
int map[MAX_LEN+2][MAX_LEN+2];
queue <tuple<int, int>> fish_posi;
queue <tuple<int, int>> fish_bot_posi;
queue <tuple<int, int, int>> fish_move;

void cout_debug()
{

	// map 출력
	cout << "cout::map" << endl;
	for (int s = MAX_LEN - 10; s <= MAX_LEN + 1; s++)
	{
		for (int t = 0; t < 10; t++)
		{
			cout << map[s][t] << ' ';
		}
		cout << endl;
	} 

	// fish list 출력
	cout << "cout::fish_list" << endl;
	for (int s = 0; s < fish_list.size(); s++)
	{
		cout << fish_list[s] << ' ';
	}
	cout << endl;

}

void init()
{
	// clear map
	for (int s = 0; s < MAX_LEN+2; s++)
	{
		for (int t = 0; t < MAX_LEN+2; t++)
		{
			map[s][t] = -1;
		}
	}

	// set start point
	sp = make_tuple(MAX_LEN, 1);
	
	return;
}

void phase_1_rotation(bool& phase_1)
{
	int cur_sp_col = get<1>(sp);
	int bot_dist = total_fishbowl-cur_sp_col;
	int side_height = 0;
	for (int s = 0; s >= 0; s++) {
		if (map[MAX_LEN-s][cur_sp_col - 1] == -1)
		{
			break;
		}
		else
		{
			side_height++;
		}
	}

	if (bot_dist >= side_height) { // 가능
		int offset = 1;
		for (int s = cur_sp_col - 1; s >= 0; s--)
		{
			for (int t = 0; t < side_height; t++) {
				if (map[MAX_LEN - t][s] == -1) { break; }
				map[MAX_LEN - offset][cur_sp_col + t] = map[MAX_LEN - t][s];
				map[MAX_LEN - t][s] = -1;
				
			}
			offset++;
		}
		sp = make_tuple(MAX_LEN, cur_sp_col + side_height);

		return;
	}
	else { // 불가능
		phase_1 = false;
		return;
	}
}

void phase_2_rotation()
{
	// 반 띡 접기 위한 시작점 찾기
	int cur_sp_row = get<0>(sp);
	int cur_half_col = (total_fishbowl - 1) / 2 + 1; // 반 접히는 부분의 시작점

	// 반 띡 접어서 올리기
	int offset = 0;
	for (int s = cur_half_col - 1; s >= 0; s--)
	{
		map[cur_sp_row -1][cur_half_col+offset] = map[cur_sp_row][s];
		map[cur_sp_row][s] = -1;
		offset++;
	}

	// 반 띡 다시 접기 위한 시작점 찾기
	int new_half_dist = (total_fishbowl - cur_half_col) / 2;
	int new_half_col = cur_half_col + new_half_dist; // 새로운 반 접히는 부분의 시작점

	// 또 반 띡 접어서 올리기
	int new_offset = 0;
	while(new_offset < new_half_dist)
	{
		map[MAX_LEN - 2][new_half_col + new_offset] = map[MAX_LEN - 1][new_half_col - 1 - new_offset];
		map[MAX_LEN - 3][new_half_col + new_offset] = map[MAX_LEN][new_half_col - 1 - new_offset];
		map[MAX_LEN - 1][new_half_col - 1 - new_offset] = -1;
		map[MAX_LEN][new_half_col - 1 - new_offset] = -1;
		new_offset++;
	}

	sp = make_tuple(MAX_LEN, new_half_col);

	return;
}

int main()
{
	init();
	fish_list.clear();
	cin >> total_fishbowl;
	cin >> difference;

	for (int s = 0; s < total_fishbowl; s++)
	{
		int cur_bowl; cin >> cur_bowl;
		fish_list.push_back(cur_bowl);
	}

	while (abs(max_num-min_num) > difference)
	{
		//먼저 물고기 수가 가장 적은 수를 찾는다.
		move_counter++;
		int temp_min = 10000000;
		for (int f = 0; f < fish_list.size(); f++)
		{
			if (fish_list[f] < temp_min)
			{
				temp_min = fish_list[f];
			}
		}

		//물고기가 가장 적은 어항들을 싹다 찾아 물고리를 한마리 추가한다.
		for (int f = 0; f < fish_list.size(); f++)
		{
			if (fish_list[f] == temp_min)
			{
				fish_list[f] += 1;
			}
		}

		//일단 저장 받은 어항 리스트를 배열로 옮긴다.
		for (int s = 0; s < fish_list.size(); s++)
		{
			map[get<0>(sp)][get<1>(sp) + -1 + s] = fish_list[s];
		}

		//저장 받은 어항 리스트를 계속 쌓는다. (phase 1)
		bool phase_1 = true;
		while (phase_1)
		{
			phase_1_rotation(phase_1);
		}

		//저장 받은 어항 리스트에서 bowl의 모든 위치를 뽑는다
		for (int s = 0; s < MAX_LEN + 2; s++) {
			for (int t = 0; t < MAX_LEN + 2; t++)
			{
				if (map[s][t] != -1)
				{
					fish_posi.push(make_tuple(s, t));
					if (s == MAX_LEN)
					{
						fish_bot_posi.push(make_tuple(s,t));
					}
				}
			}
		}

		//모든 점들을 비교하여 생선을 옮길 곳 과 받을 곳을 queue에 밀어 넣는다.
		while (!fish_posi.empty())
		{
			int cur_row = get<0>(fish_posi.front());
			int cur_col = get<1>(fish_posi.front());

			for (int s = 0; s < 4; s++)
			{
				int next_row = cur_row + dx[s];
				int next_col = cur_col + dy[s];
				if (map[next_row][next_col] == -1)
				{
					continue;
				}
				
				if (map[cur_row][cur_col] > map[next_row][next_col])
				{
					fish_move.push(make_tuple(cur_row, cur_col, -1 * ((map[cur_row][cur_col] - map[next_row][next_col]) / 5)));
					fish_move.push(make_tuple(next_row, next_col, 1 * ((map[cur_row][cur_col] - map[next_row][next_col]) / 5)));
				}
			}
			fish_posi.pop();
		}

		// 물고기를 이제 옮긴다.
		while (!fish_move.empty())
		{
			map[get<0>(fish_move.front())][get<1>(fish_move.front())] += get<2>(fish_move.front());
			fish_move.pop();
		}

		// 이제 다시 fish list를 정리하고 phase 1을 마친다.
		fish_list.clear();
		while (!fish_bot_posi.empty())
		{
			int temp_row = get<0>(fish_bot_posi.front());
			int temp_col = get<1>(fish_bot_posi.front());
			for (int row = temp_row; row >= 0; row--)
			{
				if (map[row][temp_col] == -1)
				{
					break;
				}
				fish_list.push_back(map[row][temp_col]);
			}
			fish_bot_posi.pop();
		}

		// phase2 시작을 위해 map 초기화
		init();

		for (int s = 0; s < fish_list.size(); s++)
		{
			map[get<0>(sp)][get<1>(sp) + -1 + s] = fish_list[s];
		}

		//저장 받은 어항 리스트를 계속 쌓는다. (phase 2)
		phase_2_rotation();

		//저장 받은 어항 리스트에서 bowl의 모든 위치를 뽑는다
		for (int s = 0; s < MAX_LEN + 2; s++) {
			for (int t = 0; t < MAX_LEN + 2; t++)
			{
				if (map[s][t] != -1)
				{
					fish_posi.push(make_tuple(s, t));
					if (s == MAX_LEN)
					{
						fish_bot_posi.push(make_tuple(s, t));
					}
				}
			}
		}

		//모든 점들을 비교하여 생선을 옮길 곳 과 받을 곳을 queue에 밀어 넣는다.
		while (!fish_posi.empty())
		{
			int cur_row = get<0>(fish_posi.front());
			int cur_col = get<1>(fish_posi.front());

			for (int s = 0; s < 4; s++)
			{
				int next_row = cur_row + dx[s];
				int next_col = cur_col + dy[s];
				if (map[next_row][next_col] == -1)
				{
					continue;
				}

				if (map[cur_row][cur_col] > map[next_row][next_col])
				{
					fish_move.push(make_tuple(cur_row, cur_col, -1 * ((map[cur_row][cur_col] - map[next_row][next_col]) / 5)));
					fish_move.push(make_tuple(next_row, next_col, 1 * ((map[cur_row][cur_col] - map[next_row][next_col]) / 5)));
				}
			}
			fish_posi.pop();
		}

		// 물고기를 이제 옮긴다.
		while (!fish_move.empty())
		{
			map[get<0>(fish_move.front())][get<1>(fish_move.front())] += get<2>(fish_move.front());
			fish_move.pop();
		}

		// 다시 fist list로 결과를 옮기고 phase2를 마친다.

		fish_list.clear();
		while (!fish_bot_posi.empty())
		{
			int temp_row = get<0>(fish_bot_posi.front());
			int temp_col = get<1>(fish_bot_posi.front());
			for (int row = temp_row; row >= 0; row--)
			{
				if (map[row][temp_col] == -1)
				{
					break;
				}
				fish_list.push_back(map[row][temp_col]);
			}
			fish_bot_posi.pop();
		}

		// 다음 반복 작업을 위해 init 진행
		init();

		// 결과 도출
		min_num = 10000000;
		max_num = 0;
		for (int s = 0; s < fish_list.size(); s++)
		{
			if (min_num > fish_list[s])
			{
				min_num = fish_list[s];
			}

			if (max_num < fish_list[s])
			{
				max_num = fish_list[s];
			}
		}

		//cout_debug();
	}
	
	cout << move_counter << endl;
	return 0;
}