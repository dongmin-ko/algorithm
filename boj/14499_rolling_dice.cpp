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
int map[MAXLEN + 2][MAXLEN + 2]; // 1~MAXLEN ���� ��� ����
int map_row_len;
int map_col_len;

void game(int cur_row, int cur_col, DIR cur_roll_dir)
{
	//cout << "debug : " << "cur_row : " << cur_row << " , " << " cur_col : " << cur_col << endl;
	if (map[cur_row][cur_col] == BOUNDARY)
	{
		// ��谪 ����
		// ��� ���� => ����
		return;
	}
	else
	{
		//�ֻ��� ��ġ ����
		dice.posi = make_tuple(cur_row, cur_col);

		//�ֻ��� ���� ����
		dice.set_dice(cur_roll_dir);

		//�Ű��� �ֻ��� �ظ�� �� �Ǵ�
		if (map[cur_row][cur_col]) // ��ġ�� map�� 0�� �ƴϸ�
		{
			// �ֻ��� �ظ��� ������ ��ü�ϰ� ���� 0���� ����
			dice.bot = map[cur_row][cur_col];
			map[cur_row][cur_col] = 0;
		}
		else { // ��ġ�� map�� 0 �̸�
			// ���� �ֻ��� �ظ�� �����ϰ� �����
			map[cur_row][cur_col] = dice.bot;
		}
		
		//��ܿ� ��ġ�� �� ���
		cout << dice.top << endl;
	}
}

int main()
{
	cin >> map_row_len >> map_col_len;
	int dice_posi_row;
	int dice_posi_col;
	cin >> dice_posi_row >> dice_posi_col >> num_of_rollin;
	dice.posi = make_tuple(dice_posi_row+1, dice_posi_col+1); // �������� 1,1�������� �����Ͽ� offset ����

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
