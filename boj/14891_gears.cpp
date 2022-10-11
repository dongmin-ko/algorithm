#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <tuple>
#include <queue>
#include <string>
using namespace std;

enum POLE{
	NORTH = 0,
	SOUTH = 1
};

enum CLOCKWISE {
	COUNTERCLOCK = -1,
	CLOCK = 1
};

class gear {
public:
	POLE north;
	POLE northeast;
	POLE east;
	POLE southeast;
	POLE south;
	POLE southwest;
	POLE west;
	POLE northwest;

	void cout_all()
	{
		cout << north << northeast << east << southeast << south << southwest << west << northwest << endl;
	}
	
	void rotate(CLOCKWISE WISE)
	{
		POLE TempPole;
		switch (WISE)
		{
			case COUNTERCLOCK:
				TempPole = this->north;
				this->north = this->northeast;
				this->northeast = this->east;
				this->east = this->southeast;
				this->southeast = this->south;
				this->south = this->southwest;
				this->southwest = this->west;
				this->west = this->northwest;
				this->northwest = TempPole;
				break;
			case CLOCK:
				TempPole = this->north;
				this->north = this->northwest;
				this->northwest = this->west;
				this->west = this->southwest;
				this->southwest = this->south;
				this->south = this->southeast;
				this->southeast = this->east;
				this->east = this->northeast;
				this->northeast = TempPole;
				break;
			default:
				break;
		}
	}
};

int total_rotation;
queue <tuple<int, CLOCKWISE>> rotations;
gear gears[5];

CLOCKWISE get_reverse(CLOCKWISE target)
{
	switch (target)
	{
	case CLOCKWISE::CLOCK:
		return CLOCKWISE::COUNTERCLOCK;
		break;
	case CLOCKWISE::COUNTERCLOCK:
		return CLOCKWISE::CLOCK;
		break;
	default:
		return CLOCKWISE::CLOCK;
		break;
	}
}

void simulation(int gear, CLOCKWISE cur_wise)
{
	tuple<bool, CLOCKWISE> is_gear[5];
	for (int s = 0; s <= 4; s++)
	{
		is_gear[s] = make_tuple(false, CLOCKWISE::CLOCK);
	}
	is_gear[gear] = make_tuple(true, cur_wise);

	switch (gear)
	{
		case 1:
			for (int s = 1; s <= 3;s++)
			{
				if (gears[s].east != gears[s+1].west)
				{
					is_gear[s + 1] = make_tuple(true, get_reverse(get<1>(is_gear[s])));
				}
				else // 다르면 더 돌릴 필요 없으니 멈춘다.
				{
					break;
				}
			}
			break;

		case 2:
			for (int s = 2; s <= 3; s++)
			{
				if (gears[s].east != gears[s + 1].west)
				{
					is_gear[s + 1] = make_tuple(true, get_reverse(get<1>(is_gear[s])));
				}
				else // 다르면 더 돌릴 필요 없으니 멈춘다.
				{
					break;
				}
			}
			for (int s = 2; s >= 2; s--)
			{
				if (gears[s].west != gears[s - 1].east)
				{
					is_gear[s - 1] = make_tuple(true, get_reverse(get<1>(is_gear[s])));
				}
				else // 다르면 더 돌릴 필요 없으니 멈춘다.
				{
					break;
				}
			}
			break;

		case 3:
			for (int s = 3; s <= 3; s++)
			{
				if (gears[s].east != gears[s + 1].west)
				{
					is_gear[s + 1] = make_tuple(true, get_reverse(get<1>(is_gear[s])));
				}
				else // 다르면 더 돌릴 필요 없으니 멈춘다.
				{
					break;
				}
			}
			for (int s = 3; s >= 2; s--)
			{
				if (gears[s].west != gears[s - 1].east)
				{
					is_gear[s - 1] = make_tuple(true, get_reverse(get<1>(is_gear[s])));
				}
				else // 다르면 더 돌릴 필요 없으니 멈춘다.
				{
					break;
				}
			}
			break;

		case 4:
			for (int s = 4; s >= 2; s--)
			{
				if (gears[s].west != gears[s-1].east)
				{
					is_gear[s-1] = make_tuple(true, get_reverse(get<1>(is_gear[s])));
				}
				else // 다르면 더 돌릴 필요 없으니 멈춘다.
				{
					break;
				}
			}
			break;

		default:
			return;
			break;
	}

	for (int g = 1; g <= 4; g++)
	{
		if (get<0>(is_gear[g]))
		{
			gears[g].rotate(get<1>(is_gear[g]));
		}
	}

	return;
}

int answer = 0;

int main()
{
	for (int g = 1; g <= 4; g++)
	{
		int temp_num;
		scanf("%1d", &temp_num);
		gears[g].north = static_cast<POLE>(temp_num);
		scanf("%1d", &temp_num);
		gears[g].northeast = static_cast<POLE>(temp_num);
		scanf("%1d", &temp_num);
		gears[g].east = static_cast<POLE>(temp_num);
		scanf("%1d", &temp_num);
		gears[g].southeast = static_cast<POLE>(temp_num);
		scanf("%1d", &temp_num);
		gears[g].south = static_cast<POLE>(temp_num);
		scanf("%1d", &temp_num);
		gears[g].southwest = static_cast<POLE>(temp_num);
		scanf("%1d", &temp_num);
		gears[g].west = static_cast<POLE>(temp_num);
		scanf("%1d", &temp_num);
		gears[g].northwest = static_cast<POLE>(temp_num);
		//gears[g].cout_all();
	} 

	cin >> total_rotation;
	for (int s = 1; s <= total_rotation; s++)
	{
		int cur_gear, cur_wise;
		cin >> cur_gear >> cur_wise;
		rotations.push(make_tuple(cur_gear, static_cast<CLOCKWISE>(cur_wise)));
	}

	while (!rotations.empty())
	{
		simulation(get<0>(rotations.front()), get<1>(rotations.front()));
		rotations.pop();
	}

	for (int s = 1; s <= 4; s++)
	{
		if (gears[s].north == POLE::SOUTH)
		{
			int num = 1;
			for (int t = s - 1; t > 0; t--)
			{
				num *= 2;
			}
			answer += num;
		}
	}
	cout << answer << endl;

	return 0;
}

// rotate를 멍청하게 구현했다. 한칸씩 밀고 당기는 방향으로 11101010 -> 01110101 혹은 반대 방향의 경우 11101010 -> 11010101 식으로 시계랑 반대방향 구현했으면 훨씬 진즉에 끝났을거다.
// 코드 길이측면에서 시간을 반으로 단축했을 듯 싶다.
