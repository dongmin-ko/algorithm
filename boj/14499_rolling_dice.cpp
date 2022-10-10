#include <iostream>
#include <memory.h>
#include <tuple>
#include <queue>
using namespace std;

#define MAXLEN 20
#define BOUNDARY -1

enum DIR {
	RIGHT=1,
	LEFT=2,
	UP=3,
	DOWN=4
};

class basic_dice {
public:
	basic_dice()
	{
		top = 0;
		bot = 0;
		up = 0;
		down = 0;
		left = 0;
		right = 0;
		posi = make_tuple(1, 1); // dice posi row, col
	}
	~basic_dice() {}
	int top, bot ,up, down, left, right;
	tuple<int, int> posi;

	void set_dice(DIR dir)
	{
		int momorizer = 0;
		switch (dir)
		{
		case RIGHT:
			momorizer = this->right;
			this->right = this->top;
			this->top = this->left;
			this->left = this->bot;
			this->bot = momorizer;
			break;
		case LEFT:
			momorizer = this->left;
			this->left = this->top;
			this->top = this->right;
			this->right = this->bot;
			this->bot = momorizer;
			break;
		case UP:
			momorizer = this->up;
			this->up = this->top;
			this->top = this->down;
			this->down = this->bot;
			this->bot = momorizer;
			break;
		case DOWN:
			momorizer = this->down;
			this->down = this->top;
			this->top = this->up;
			this->up = this->bot;
			this->bot = momorizer;
			break;
		default:
			break;
		}
	}
};

basic_dice dice;
int num_of_rollin;
queue <DIR> rollin;
int map[MAXLEN + 2][MAXLEN + 2]; // 1~MAXLEN 까지 사용 가능
int map_row_len;
int map_col_len;

void game(int cur_row, int cur_col, DIR cur_roll_dir)
{
	//cout << "debug : " << "cur_row : " << cur_row << " , " << " cur_col : " << cur_col << endl;
	if (map[cur_row][cur_col] == BOUNDARY)
	{
		// 경계값 도착
		// 명령 무시 => 종료
		return;
	}
	else
	{
		//주사위 위치 갱신
		dice.posi = make_tuple(cur_row, cur_col);

		//주사위 정보 갱신
		dice.set_dice(cur_roll_dir);

		//옮겨진 주사위 밑면과 맵 판단
		if (map[cur_row][cur_col]) // 위치한 map이 0이 아니면
		{
			// 주사위 밑면을 맵으로 대체하고 맵을 0으로 만듬
			dice.bot = map[cur_row][cur_col];
			map[cur_row][cur_col] = 0;
		}
		else { // 위치한 map이 0 이면
			// 맵을 주사위 밑면과 동일하게 만든다
			map[cur_row][cur_col] = dice.bot;
		}
		
		//상단에 위치한 값 출력
		cout << dice.top << endl;
	}
}

int main()
{
	cin >> map_row_len >> map_col_len;
	int dice_posi_row;
	int dice_posi_col;
	cin >> dice_posi_row >> dice_posi_col >> num_of_rollin;
	dice.posi = make_tuple(dice_posi_row+1, dice_posi_col+1); // 시작점을 1,1기준으로 변경하여 offset 진행

	// make boundary
	for (int s = 0; s <= map_row_len + 1; s++)
	{
		for (int t = 0; t <= map_col_len + 1; t++)
		{
			map[s][t] = BOUNDARY;
		}
	}

	// get map data
	for (int s = 1; s <= map_row_len; s++)
	{
		for (int t = 1; t <= map_col_len; t++)
		{
			int cur_data;
			cin >> cur_data;
			map[s][t] = cur_data;
		}
	}

	// get rolling data
	for (int p = 0; p < num_of_rollin; p++)
	{
		int cur_roll;
		cin >> cur_roll;
		rollin.push(static_cast<DIR>(cur_roll));
		/*cout << "debug : rollin back data = " << rollin.back() << endl;*/
	}

	while (!rollin.empty())
	{
		if (rollin.front() == DIR::UP) {
			game(get<0>(dice.posi)-1, get<1>(dice.posi), rollin.front());
		}
		else if (rollin.front() == DIR::DOWN) {
			game(get<0>(dice.posi)+1, get<1>(dice.posi), rollin.front());
		}
		else if (rollin.front() == DIR::RIGHT) {
			game(get<0>(dice.posi), get<1>(dice.posi)+1, rollin.front());
		}
		else { // when DIR::LEFT
			game(get<0>(dice.posi), get<1>(dice.posi)-1, rollin.front());
		}
		rollin.pop();
	}
	
	return 0;
}
