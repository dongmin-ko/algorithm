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
int map[MAX_LEN + 2][MAX_LEN + 2];

int answer = 0;
int map_len;
int bridge_len;

void simul_down(int row, int col, int cur_num, int stack, int counter)
{ // counter 1부터 시작 // stack 1부터 시작
	if (counter > map_len)
	{
		answer++;
		return;
	}
	else
	{
		if (cur_num == map[row+1][col] || map[row+1][col] == -1)
		{
			simul_down(row +1, col, cur_num, stack + 1, counter + 1);
			return;
		}
		else if (cur_num == map[row+1][col] + 1) // 내가 더 크면
		{
			bool is_possi = true;
			for (int offset = 1; offset <= bridge_len; offset++)
			{
				if (cur_num - 1 == map[row + offset][col]) {
					continue;
				}
				else {
					is_possi = false;
					break;
				}
			}
			if (is_possi) {
				simul_down(row + bridge_len, col, map[row + bridge_len][col], 0, counter + bridge_len);
			}
			else {
				return;
			}
		}
		else if (cur_num == map[row + 1][col] - 1) // 내가 더 작으면
		{
			if (stack >= bridge_len)
			{
				simul_down(row + 1, col, map[row +1 ][col], 1, counter + 1);
				return;
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}
		return;
	}
	return;
}

void simul_right(int row, int col, int cur_num, int stack, int counter)
{ // counter 1부터 시작 // stack 1부터 시작
	if (counter > map_len)
	{
		answer++;
		return;
	}
	else
	{
		if (cur_num == map[row][col+1] || map[row][col+1] == -1)
		{
			simul_right(row, col + 1, cur_num, stack+1, counter+1);
			return;
		}
		else if (cur_num == map[row][col+1] + 1) // 내가 더 크면
		{
			bool is_possi = true;
			for (int offset = 1; offset <= bridge_len; offset++)
			{
				if (cur_num - 1 == map[row][col + offset]) {
					continue;
				}
				else {
					is_possi = false;
					break;
				}
			}
			if (is_possi){
				simul_right(row, col + bridge_len, map[row][col+bridge_len], 0, counter + bridge_len);
			}
			else {
				return;
			}
		}
		else if (cur_num == map[row][col + 1] - 1) // 내가 더 작으면
		{
			if (stack >= bridge_len)
			{
				simul_right(row, col + 1, map[row][col + 1], 1, counter + 1);
				return;
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}
		return;
	}
	return;
}

int main()
{
	for (int s = 0; s < MAX_LEN + 2; s++)
	{
		for (int t = 0; t < MAX_LEN + 2; t++)
		{
			map[s][t] = -1;
		}
	}

	cin >> map_len >> bridge_len;
	
	for (int s = 1; s <= map_len; s++)
	{
		for (int t = 1; t <= map_len; t++) {
			int cur_data;
			cin >> cur_data;
			map[s][t] = cur_data;
		}
	}

	for (int t = 1; t <= map_len; t++)
	{
		simul_down(1,t,map[1][t], 1, 1);
		simul_right(t, 1, map[t][1], 1, 1);
	}

	cout << answer << endl;
}