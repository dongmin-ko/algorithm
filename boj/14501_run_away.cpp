#include <iostream>
#include <memory.h>
using namespace std;
#define MAX_LEN 15

bool is_days[MAX_LEN + 1];
int consume_days[MAX_LEN + 1];
int pays[MAX_LEN + 1];
int total_days;
int max_cost = 0;

void recursive(int today, int cur_cost)
{
	if (today > total_days) // 기저 조건 퇴사날 정산
	{
		if (cur_cost > max_cost)
		{
			max_cost = cur_cost;
		}
		return;
	}
	else
	{
		if(is_days[today]) // 오늘 업무가 가능할때
		{
			// 남은 조건일이 맞아서 하는 경우. => 코스트가 올라감 (단, 오늘 일자를 기준으로 업무가 가능해야함.)
			if (today + consume_days[today] -1 <= total_days) {
				for (int s = today; s <= today + consume_days[today] - 1; s++)
				{
					is_days[s] = false; // 업무 진행한다 가정하고 업무 불가로 판단
				}
				recursive(today + 1, cur_cost + pays[today]); // 업무 진행
				for (int s = today; s <= today + consume_days[today] - 1; s++)
				{
					is_days[s] = true; // 업무 진행 가정 전으로 다시 복구
				}
			}

			// 안하고 그냥 넘기는 경우.
			recursive(today + 1, cur_cost);
		}
		else // 오늘 업무가 불가능 하면 그냥 넘기면 된다.
		{
			recursive(today + 1, cur_cost);
		}
		return;
	}
	return;
}

int main()
{
	// 일단 업무가 가능하면 true로 전부 set up
	memset(is_days, true, sizeof(is_days));
	cin >> total_days;
	for (int d = 1; d <= total_days; d++)
	{
		int cur_consume, cur_cost;
		cin >> cur_consume >> cur_cost;
		consume_days[d] = cur_consume;
		pays[d] = cur_cost;
	}

	// 재귀 시작
	recursive(1, 0);
	cout << max_cost << endl;
}