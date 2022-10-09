//#include <iostream>
//#include <deque>
//#include <queue>
//#include <utility>
//#include <memory.h>
//using namespace std;
//
//#define MAXLEN 100
//
//enum DIR {
//	UP = 0,
//	DOWN,
//	RIGHT,
//	LEFT
//};
//
//DIR cur_dir;
//int map_size;
//int total_turn;
//int apples;
//
//int game_time = 0;
//int turn_time = 0;
//int remained_apples = 0;
//
//bool map[MAXLEN + 1][MAXLEN + 1] = {false, };
//bool is_body[MAXLEN + 1][MAXLEN + 1] = { false, };
//bool game_over = false;
//
//deque<pair<int, int>> snake;
//queue<pair<int, char>> turns;
//
//DIR get_direction(DIR cur_dir, char cur_rot)
//{
//	if (cur_rot == 'D') // 시계방향 90도
//	{
//		switch (cur_dir)
//		{
//		case DIR::UP:
//			return DIR::RIGHT;
//			break;
//
//		case DIR::DOWN:
//			return DIR::LEFT;
//			break;
//
//		case DIR::RIGHT:
//			return DIR::DOWN;
//			break;
//
//		case DIR::LEFT:
//			return DIR::UP;
//			break;
//
//		default:
//			break;
//		}
//	}
//	else { // cur_rot == 'L'
//		switch (cur_dir)
//		{
//		case DIR::UP:
//			return DIR::LEFT;
//			break;
//
//		case DIR::DOWN:
//			return DIR::RIGHT;
//			break;
//
//		case DIR::RIGHT:
//			return DIR::UP;
//			break;
//
//		case DIR::LEFT:
//			return DIR::DOWN;
//			break;
//
//		default:
//			break;
//		}
//	}
//
//	return cur_dir;
//}
//
//void game(int cur_row, int cur_col)
//{
//	game_time += 1;
//	turn_time -= 1;
//
//	// 우선 게임 오버 조건을 만든다
//	if (cur_row <= 0 || cur_row >= map_size + 1 || cur_col <= 0 || cur_col >= map_size + 1 || is_body[cur_row][cur_col])
//	{
//		game_over = true;
//		return;
//	}
//
//	if (turn_time <= 0 && !turns.empty())
//	{
//		cur_dir = get_direction(cur_dir, turns.front().second);
//		turns.pop();
//		turn_time = turns.front().first - game_time;
//	}
//
//	if (map[cur_row][cur_col]) // 만약 사과가 있다면 다음 위치만 추가
//	{
//		map[cur_row][cur_col] = false; // 사과를 먹고
//
//		switch (cur_dir)
//		{
//		case DIR::UP:
//			is_body[cur_row][cur_col] = true;
//			snake.push_front(make_pair(cur_row - 1, cur_col));
//			break;
//		case DIR::DOWN:
//			is_body[cur_row][cur_col] = true;
//			snake.push_front(make_pair(cur_row + 1, cur_col));
//			break;
//		case DIR::RIGHT:
//			is_body[cur_row][cur_col] = true;
//			snake.push_front(make_pair(cur_row, cur_col + 1));
//			break;
//		case DIR::LEFT:
//			is_body[cur_row][cur_col] = true;
//			snake.push_front(make_pair(cur_row, cur_col - 1));
//			break;
//		default:
//			cout << "Something is wrong" << endl;
//			break;
//		}
//
//	}
//	else // 만약 사과가 없다면 다음 위치를 추가
//	{
//		switch (cur_dir)
//		{
//		case DIR::UP:
//			is_body[cur_row][cur_col] = true;
//			snake.push_front(make_pair(cur_row - 1, cur_col));
//			is_body[snake.back().first][snake.back().second] = false;
//			snake.pop_back();
//			break;
//		case DIR::DOWN:
//			is_body[cur_row][cur_col] = true;
//			snake.push_front(make_pair(cur_row + 1, cur_col));
//			is_body[snake.back().first][snake.back().second] = false;
//			snake.pop_back();
//			break;
//		case DIR::RIGHT:
//			is_body[cur_row][cur_col] = true;
//			snake.push_front(make_pair(cur_row, cur_col+1));
//			is_body[snake.back().first][snake.back().second] = false;
//			snake.pop_back();
//			break;
//		case DIR::LEFT:
//			is_body[cur_row][cur_col] = true;
//			snake.push_front(make_pair(cur_row, cur_col-1));
//			is_body[snake.back().first][snake.back().second] = false;
//			snake.pop_back();
//			break;
//		default:
//			cout << "Something is wrong" << endl;
//			break;
//		}
//	}
//
//	return;
//}
//
//int main()
//{
//	memset(map, false, sizeof(map));
//	memset(is_body, false, sizeof(is_body));
//	cur_dir = DIR::RIGHT;
//	cin >> map_size;
//	cin >> apples;
//	remained_apples = apples;
//	for (int s = 0; s < apples; s++)
//	{
//		int cur_row, cur_col;
//		cin >> cur_row >> cur_col;
//		map[cur_row][cur_col] = true;
//	}
//
//	cin >> total_turn;
//	
//	for (int t = 0; t < total_turn; t++)
//	{
//		int cur_time;
//		char cur_char;
//		cin >> cur_time >> cur_char;
//		turns.push(make_pair(cur_time, cur_char));
//	}
//
//	snake.push_front(make_pair(1, 1));
//	is_body[snake.front().first][snake.front().second] = true;
//	snake.push_front(make_pair(1, 2));
//	turn_time = turns.front().first;
//
//	while (!game_over)
//	{
//		game(snake.front().first, snake.front().second);
//	}
//	cout << game_time << endl;
//	return 0;
//
//}