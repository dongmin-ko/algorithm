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
	if (today > total_days) // ���� ���� ��糯 ����
	{
		if (cur_cost > max_cost)
		{
			max_cost = cur_cost;
		}
		return;
	}
	else
	{
		if(is_days[today]) // ���� ������ �����Ҷ�
		{
			// ���� �������� �¾Ƽ� �ϴ� ���. => �ڽ�Ʈ�� �ö� (��, ���� ���ڸ� �������� ������ �����ؾ���.)
			if (today + consume_days[today] -1 <= total_days) {
				for (int s = today; s <= today + consume_days[today] - 1; s++)
				{
					is_days[s] = false; // ���� �����Ѵ� �����ϰ� ���� �Ұ��� �Ǵ�
				}
				recursive(today + 1, cur_cost + pays[today]); // ���� ����
				for (int s = today; s <= today + consume_days[today] - 1; s++)
				{
					is_days[s] = true; // ���� ���� ���� ������ �ٽ� ����
				}
			}

			// ���ϰ� �׳� �ѱ�� ���.
			recursive(today + 1, cur_cost);
		}
		else // ���� ������ �Ұ��� �ϸ� �׳� �ѱ�� �ȴ�.
		{
			recursive(today + 1, cur_cost);
		}
		return;
	}
	return;
}

int main()
{
	// �ϴ� ������ �����ϸ� true�� ���� set up
	memset(is_days, true, sizeof(is_days));
	cin >> total_days;
	for (int d = 1; d <= total_days; d++)
	{
		int cur_consume, cur_cost;
		cin >> cur_consume >> cur_cost;
		consume_days[d] = cur_consume;
		pays[d] = cur_cost;
	}

	// ��� ����
	recursive(1, 0);
	cout << max_cost << endl;
}