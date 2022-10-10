#include <iostream>
#include <tuple>
#include <memory.h>
#define MANLEN 500
#define BOUNDARY -1
using namespace std;

int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

bool visited[MANLEN + 2][MANLEN + 2];
int map[MANLEN + 2][MANLEN + 2];
int row_len;
int col_len;
int max_sum = 0;

void dfs(int cur_row, int cur_col, int sum, int count)
{
	if (visited[cur_row][cur_col] || map[cur_row][cur_col] == BOUNDARY) // exception
	{
		return;
	}
	else
	{
		if (count >= 4) // 기저 탈출
		{
			if (sum > max_sum)
			{
				max_sum = sum;
				return;
			}
		}
		else
		{
			visited[cur_row][cur_col] = true;
			int next_row, next_col;
			for (int s = 0; s < 4; s++)
			{
				next_row = cur_row + dx[s];
				next_col = cur_col + dy[s];
				dfs(next_row, next_col, sum + map[next_row][next_col], count + 1);
			}
			visited[cur_row][cur_col] = false;
		}
	}

	return;
}

void fkShaped(int cur_row, int cur_col)
{
	int sum = 0;
	// 현위치 기준 상방향
	if (map[cur_row-1][cur_col] != BOUNDARY && map[cur_row][cur_col-1] != BOUNDARY && map[cur_row][cur_col+1] != BOUNDARY)
	{
		sum = map[cur_row][cur_col] + map[cur_row - 1][cur_col] + map[cur_row][cur_col - 1] + map[cur_row][cur_col + 1];
		if (sum > max_sum)
			max_sum = sum;
	}

	// 현위치 기준 하방향
	if (map[cur_row+1][cur_col] != BOUNDARY && map[cur_row][cur_col+1] != BOUNDARY && map[cur_row][cur_col-1] != BOUNDARY)
	{
		sum = map[cur_row][cur_col] + map[cur_row + 1][cur_col] + map[cur_row][cur_col + 1] + map[cur_row][cur_col - 1];
		if (sum > max_sum)
			max_sum = sum;
	}

	// 현위치 기준 우방향
	if (map[cur_row-1][cur_col] != BOUNDARY && map[cur_row+1][cur_col] != BOUNDARY && map[cur_row][cur_col+1] != BOUNDARY)
	{
		sum = map[cur_row][cur_col] + map[cur_row - 1][cur_col] + map[cur_row + 1][cur_col] + map[cur_row][cur_col + 1];
		if (sum > max_sum)
			max_sum = sum;
	}

	// 현위치 기준 좌방향
	if (map[cur_row][cur_col-1] != BOUNDARY && map[cur_row-1][cur_col] != BOUNDARY && map[cur_row+1][cur_col] != BOUNDARY)
	{
		sum = map[cur_row][cur_col] + map[cur_row][cur_col - 1] + map[cur_row - 1][cur_col] + map[cur_row + 1][cur_col];
		if (sum > max_sum)
			max_sum = sum;
	}

	return;
}

int main()
{
	memset(visited, false, sizeof(visited));
	cin >> row_len >> col_len;
	for (int s = 0; s <= row_len + 1; s++)
	{
		for (int t = 0; t <= col_len + 1; t++)
		{
			map[s][t] = BOUNDARY;
		}
	}

	for (int s = 1; s <= row_len; s++)
	{
		for (int t = 1; t <= col_len; t++)
		{
			int data; cin >> data;
			map[s][t] = data;
		}
	}

	for (int s = 1; s <= row_len; s++)
	{
		for (int t = 1; t <= col_len; t++)
		{
			dfs(s, t, map[s][t], 1);
			fkShaped(s, t);
		}
	}


	cout << max_sum << endl;
}