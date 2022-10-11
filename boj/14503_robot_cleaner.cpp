#include <iostream>
#include <tuple>
#include <stack>
#include <queue>
#include <memory.h>
#define MAXLEN 50
using namespace std;

enum FLAG {
	BOUNDARY = -1,
	UNCLEAN = 0,
	WALL = 1,
	CLEAN = 2
};

enum DIR {
	UP=0,
	RIGHT=1,
	DOWN=2,
	LEFT=3
};

int row_len;
int col_len;

int new_row;
int new_col;
int new_dir;

int answer = 0;
stack <tuple<int, int, DIR>> next_posi;
FLAG map[MAXLEN + 2][MAXLEN + 2];

DIR rotate(DIR cur_dir)
{
	switch (cur_dir)
	{
		case UP:
			return DIR::LEFT;
			break;
		case RIGHT:
			return DIR::UP;
			break;
		case DOWN:
			return DIR::RIGHT;
			break;
		case LEFT:
			return DIR::DOWN;
			break;
		default:
			return cur_dir;
			break;
	}
}

tuple<bool, int, int, DIR> is_clean(int get_row, int get_col, DIR dir)
{
	switch (dir)
	{
	case UP:
		if (map[get_row-1][get_col] == FLAG::UNCLEAN)
		{
			return make_tuple(true, get_row - 1, get_col, DIR::UP);
		}
		else
		{
			return make_tuple(false, get_row - 1, get_col, DIR::UP);
		}
		break;
	case RIGHT:
		if (map[get_row][get_col+1] == FLAG::UNCLEAN)
		{
			return make_tuple(true, get_row, get_col+1, DIR::RIGHT);
		}
		else
		{
			return make_tuple(false, get_row, get_col+1, DIR::RIGHT);
		}
		break;
	case DOWN:
		if (map[get_row+1][get_col] == FLAG::UNCLEAN)
		{
			return make_tuple(true, get_row+1, get_col, DIR::DOWN);
		}
		else
		{
			return make_tuple(false, get_row+1, get_col, DIR::DOWN);
		}
		break;
	case LEFT:
		if (map[get_row][get_col-1] == FLAG::UNCLEAN)
		{
			return make_tuple(true, get_row, get_col-1, DIR::LEFT);
		}
		else
		{
			return make_tuple(false, get_row, get_col-1, DIR::LEFT);
		}
		break;
	default:
		cout << "something is wrong" << endl;
		return make_tuple(false, get_row, get_col, dir);
		break;
	}
}

tuple<int, int, DIR> move_back(int get_row, int get_col, DIR dir)
{
	switch (dir)
	{
	case UP:
		return make_tuple(get_row+1, get_col, dir);
		break;
	case RIGHT:
		return make_tuple(get_row, get_col-1, dir);
		break;
	case DOWN:
		return make_tuple(get_row-1, get_col, dir);
		break;
	case LEFT:
		return make_tuple(get_row, get_col+1, dir);
		break;
	default:
		return make_tuple(get_row, get_col, dir);
		break;
	}
}

void clean_room(int cur_row, int cur_col, DIR cur_dir)
{
	if (map[cur_row][cur_col] == FLAG::BOUNDARY || map[cur_row][cur_col] == FLAG::WALL)
	{
		return;
	}
	else if (map[cur_row][cur_col] == FLAG::UNCLEAN)
	{
		map[cur_row][cur_col] = FLAG::CLEAN;
		answer += 1;
	}

	int count = 0;
	tuple<bool, int, int, DIR> is_possi = make_tuple(false, 0, 0, cur_dir);
	for (int s = 0; s < 4; s++)
	{
		cur_dir = rotate(cur_dir);
		is_possi = is_clean(cur_row, cur_col, cur_dir);
		if (get<0>(is_possi)) // 청소 가능이면
		{
			next_posi.push(make_tuple(get<1>(is_possi), get<2>(is_possi), get<3>(is_possi)));
			return;
		}
		else { // 청소 불가능 이면
			count++;
		}
	}

	if (count >= 4)
	{
		next_posi.push(move_back(cur_row, cur_col, cur_dir));
	}

	return;
}

int main()
{

	cin >> row_len >> col_len;
	cin >> new_row >> new_col >> new_dir;
	next_posi.push(make_tuple(new_row+1, new_col+1, static_cast<DIR>(new_dir))); // new_row, new_col off set 필수

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
			int temp_data;
			cin >> temp_data;
			map[s][t] = static_cast<FLAG>(temp_data);
		}
	}

	while (!next_posi.empty())
	{
		tuple<int, int, DIR> cur_posi = next_posi.top();
		next_posi.pop();
		clean_room(get<0>(cur_posi), get<1>(cur_posi), get<2>(cur_posi));
	}

	cout << answer << endl;

	return 0;
}