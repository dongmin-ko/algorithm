#include <iostream>
#include <vector>
#include <memory.h>
#define LEN_MAX 50
#define MAX_TIME_LIMIT 21
using namespace std;
bool visited[LEN_MAX][LEN_MAX][MAX_TIME_LIMIT];
bool visited_answer[LEN_MAX][LEN_MAX];
int row_len;
int col_len;
int row_man;
int col_man;
int limit_time;
int answer;

// important : up, down, right, left
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,1,-1 };

typedef enum dir
{
	UP = 0,
	DOWN = 1,
	RIGHT = 2,
	LEFT = 3
}DIR;

typedef enum type
{
	NO = 0,
	CROSS = 1,
	UPDOWN = 2,
	RIGHTLEFT = 3,
	RIGHTUP = 4,
	RIGHTDOWN = 5,
	LEFTDOWN = 6,
	LEFTUP = 7
}TYPE;

typedef class game_map
{
public:
	bool dir[4];
}MAP;

MAP map[LEN_MAX][LEN_MAX];

void type_master(int row, int col, int cur_type)
{
	switch (cur_type)
	{
	case CROSS:
		map[row][col].dir[UP] = true;
		map[row][col].dir[DOWN] = true;
		map[row][col].dir[RIGHT] = true;
		map[row][col].dir[LEFT] = true;
	case UPDOWN:
		map[row][col].dir[UP] = true;
		map[row][col].dir[DOWN] = true;
		break;
	case RIGHTLEFT:
		map[row][col].dir[RIGHT] = true;
		map[row][col].dir[LEFT] = true;
		break;
	case RIGHTUP:
		map[row][col].dir[UP] = true;
		map[row][col].dir[RIGHT] = true;
		break;
	case RIGHTDOWN:
		map[row][col].dir[DOWN] = true;
		map[row][col].dir[RIGHT] = true;
		break;
	case LEFTDOWN:
		map[row][col].dir[DOWN] = true;
		map[row][col].dir[LEFT] = true;
		break;
	case LEFTUP:
		map[row][col].dir[UP] = true;
		map[row][col].dir[LEFT] = true;
		break;
	default: // if no tunnel
		map[row][col].dir[UP] = false;
		map[row][col].dir[DOWN] = false;
		map[row][col].dir[RIGHT] = false;
		map[row][col].dir[LEFT] = false;
		break;
	}
	return;
}

void init()
{
	limit_time = 0;
	answer = 0;

	cin >> row_len; // get N = sero
	cin >> col_len; // get M = garo
	cin >> row_man; // get man hole sero
	cin >> col_man; // get man hole garo
	cin >> limit_time;

	for (int s = 0; s < row_len; s++) {
		for (int t = 0; t < col_len; t++) {
			visited_answer[s][t] = false;
			for (int l = 0; l <= limit_time; l++) {
				visited[s][t][l] = false;
				for (int d = 0; d < 4; d++) {
					map[s][t].dir[d] = false;
				}
			}
		}
	}

	return;
}

void game(int r, int c, int time)
{
	visited[r][c][time] = true;
	visited_answer[r][c] = true;

	// this is last one
	if (time >= limit_time)
	{
		return;
	}

	// bfs
	for (int s = 0; s < 4; s++)
	{
		int new_x = r + dx[s];
		int new_y = c + dy[s];
		if ((new_x < 0) || (new_x >= row_len) || (new_y < 0) || (new_y >= col_len) || visited[new_x][new_y][time + 1])
		{
			continue;
		}
		else {
			switch (s)
			{
			case 0: // up
				if (map[r][c].dir[UP] == true && map[new_x][new_y].dir[DOWN] == true) {
					game(new_x, new_y, time + 1);
				}
				break;
			case 1: // down
				if (map[r][c].dir[DOWN] == true && map[new_x][new_y].dir[UP] == true) {
					game(new_x, new_y, time + 1);
				}
				break;
			case 2: // right
				if (map[r][c].dir[RIGHT] == true && map[new_x][new_y].dir[LEFT] == true) {
					game(new_x, new_y, time + 1);
				}
				break;
			case 3: // left
				if (map[r][c].dir[LEFT] == true && map[new_x][new_y].dir[RIGHT] == true) {
					game(new_x, new_y, time + 1);
				}
				break;
			default: // ???
				break;
			}
		}
	}

	return;
}

int main() {

	int total_tc;
	cin >> total_tc;
	for (int tc = 1; tc <= total_tc; tc++) {

		//get data & init
		init();

		int curType = 0;
		for (int s = 0; s < row_len; s++) {
			for (int t = 0; t < col_len; t++) {
				cin >> curType;
				type_master(s, t, curType);
			}
		}
		game(row_man, col_man, 1);

		// get answer
		for (int s = 0; s < row_len; s++) {
			for (int t = 0; t < col_len; t++) {
				if (visited_answer[s][t]) {
					answer += 1;
				}
			}
		}

		cout << '#' << tc << ' ' << answer << endl;
	}

	return 0;
}