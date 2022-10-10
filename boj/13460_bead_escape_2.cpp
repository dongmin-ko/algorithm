#include <iostream>
#include <string>
#include <memory>
#include <queue>
#include <tuple>
#define MAX_LEN 10
using namespace std;

queue<tuple<int, int>> point;

const char symbol_block = '#';
const char symbol_whole = 'O';
const char symbol_red = 'R';
const char symbol_blue = 'B';
const char symbol_path = '.';

char map[MAX_LEN][MAX_LEN];
bool visited[MAX_LEN][MAX_LEN][4];

int row_len = 0;
int col_len = 0;

int min_count;
bool is_escaped;

int dx[] = { 1,-1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

enum DIREC
{
	UP=0,
	DOWN=1,
	RIGHT=2,
	LEFT=3,
};

void BFS(int row, int col, int count, DIREC dir)
{
	//cout << "row" << row << ':' << "col" << col << ':' << "count" << ':' << count << ':' << "direc" << dir << endl;
	// 예외 처리
	if (visited[row][col][dir] || map[row][col] == symbol_block || map[row][col] == symbol_blue) {
		//cout << "cut" << endl;
		return;
	}
	else {
		visited[row][col][dir] = true;
	}

	// 기저 조건
	if (map[row][col] == symbol_whole)
	{
		is_escaped = true;
		if (count < min_count) {
			min_count = count;
		}
		return;
	}

	// BFS
	switch (dir)
	{
		case UP:
			if (map[row - 1][col] == symbol_path || map[row - 1][col] == symbol_whole)
			{
				BFS(row - 1, col, count, dir);
			}
			else {
				BFS(row + 1, col, count + 1, DOWN);
				BFS(row, col + 1, count + 1, RIGHT);
				BFS(row, col - 1, count + 1, LEFT);
			}
			break;
		case DOWN:
			if (map[row + 1][col] == symbol_path || map[row + 1][col] == symbol_whole)
			{
				BFS(row + 1, col, count, dir);
			}
			else {
				BFS(row - 1, col, count + 1, UP);
				BFS(row, col + 1, count + 1, RIGHT);
				BFS(row, col - 1, count + 1, LEFT);
			}
			break;
		case RIGHT:
			if (map[row][col + 1] == symbol_path || map[row][col + 1] == symbol_whole)
			{
				BFS(row, col + 1, count, dir);
			}
			else {
				BFS(row - 1, col, count + 1, UP);
				BFS(row + 1, col, count + 1, DOWN);
				BFS(row, col - 1, count + 1, LEFT);
			}
			break;
		case LEFT:
			if (map[row][col - 1] == symbol_path || map[row][col - 1] == symbol_whole)
			{
				BFS(row, col - 1, count, dir);
			}
			else {
				BFS(row - 1, col, count + 1, UP);
				BFS(row + 1, col, count + 1, DOWN);
				BFS(row, col + 1, count + 1, RIGHT);
			}
			break;
		default:
			return;
			break;
	}
}

int main() {

	is_escaped = false;
	min_count = 1000000;
	memset(visited, false, sizeof(visited));
	cin >> row_len >> col_len;

	for (int s = 0; s < row_len; s++) {
		string map_data_line;
		cin >> map_data_line;
		for (int t = 0; t < col_len; t++) {
			map[s][t] = map_data_line[t];
			if (map[s][t] == symbol_red) {
				point.push(make_tuple(s, t));
			}
		}
	}

	while(point.size() > 0){
		//cout << get<0>(point.front()) << ',' << get<1>(point.front()) << endl;
		if (map[get<0>(point.front())+1][get<1>(point.front())] == symbol_path) {
			BFS(get<0>(point.front()), get<1>(point.front()), 1, DOWN);
		}
		if (map[get<0>(point.front()) -1][get<1>(point.front())] == symbol_path) {
			BFS(get<0>(point.front()), get<1>(point.front()), 1, UP);
		}
		if (map[get<0>(point.front())][get<1>(point.front())-1] == symbol_path) {
			BFS(get<0>(point.front()), get<1>(point.front()), 1, LEFT);
		}
		if (map[get<0>(point.front())][get<1>(point.front())+1] == symbol_path) {
			BFS(get<0>(point.front()), get<1>(point.front()), 1, RIGHT);
		}
		point.pop();
	}

	if (is_escaped) {
		cout << min_count << endl;
	}
	else {
		cout << -1 << endl;
	}

	return 0;
}