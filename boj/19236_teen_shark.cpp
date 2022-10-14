#include <iostream>
#include <tuple>
#include <vector>
#define SHARK 0
#define MAXLEN 4
#define MAXFISH 16

using namespace std;

enum DIR {
	UP=0,
	UPLEFT=1,
	LEFT=2,
	DOWNLEFT=3,
	DOWN=4,
	DOWNRIGHT=5,
	RIGHT=6,
	UPRIGHT=7
};

DIR rotate(DIR cur_dir)
{
	switch (cur_dir)
	{
	case UP:
		return LEFT;
		break;
	case UPRIGHT:
		return UPLEFT;
		break;
	case RIGHT:
		return UP;
		break;
	case DOWNRIGHT:
		return UPRIGHT;
		break;
	case DOWN:
		return RIGHT;
		break;
	case DOWNLEFT:
		return DOWNRIGHT;
		break;
	case LEFT:
		return DOWN;
		break;
	case UPLEFT:
		return DOWNLEFT;
		break;
	default:
		return cur_dir;
		break;
	}
}

class BOWL{
public:
	bool is_shark;
	bool is_fish;
	int num;
	DIR dir;
};

//fish 0 is shark;
tuple<bool, int, int, DIR> fish_status[MAXFISH+1]; // 0:status true is alive, 1&2:position, 3:dir

BOWL bowl[MAXLEN + 2][MAXLEN + 2];
int map_len = 4;
int eaten_fishes = 0;

// 상어는 물고기가 없는 칸으로는 이동할 수 없다 !!

int main()
{
	// 생선 정보 받기
	for (int s = 1; s <= map_len; s++)
	{
		for (int t = 1; t <= map_len; t++)
		{
			int num, dir;
			cin >> num >> dir;
			bowl[s][t].is_shark = false;
			bowl[s][t].is_fish = true;
			bowl[s][t].num = num;
			bowl[s][t].dir = static_cast<DIR>(dir);
			fish_status[s] = make_tuple(true, s, t, static_cast<DIR>(dir));
		}
	}

	// 상어 정보 넣기
	bowl[1][1].is_shark = true;
	bowl[1][1].is_fish = false;
	eaten_fishes += bowl[1][1].num;
	fish_status[bowl[1][1].num] = make_tuple(false, 1, 1, bowl[1][1].dir); // fish died
	fish_status[SHARK] = make_tuple(true, 1, 1, bowl[1][1].dir); // shark updated
	bowl[1][1].num = 0; // 비어있는곳의 숫자는 0
	
	return 0;
}