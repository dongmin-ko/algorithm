#include <iostream>
#include <math.h>
#define BILLION 1000000000
using namespace std;
long long int op_plus=0, op_minus=0, op_multiply=0, op_division=0;
long long int max_num = -1000000000;
long long int min_num = 1000000000;

int total_data;
int data_list[11];

void calc(int cur_sum, int idx)
{
	if (idx >= total_data)
	{
		if (cur_sum >= max_num)
		{
			max_num = cur_sum;
		}

		if (cur_sum <= min_num)
		{
			min_num = cur_sum;
		}
	}

	if (op_plus > 0)
	{
		op_plus--;
		calc(cur_sum + data_list[idx], idx + 1);
		op_plus++;
	}

	if (op_minus > 0)
	{
		op_minus--;
		calc(cur_sum - data_list[idx], idx + 1);
		op_minus++;
	}

	if (op_multiply > 0)
	{
		op_multiply--;
		calc(cur_sum * data_list[idx], idx + 1);
		op_multiply++;
	}

	if (op_division > 0)
	{
		op_division--;
		if ((cur_sum >= 0 && data_list[idx] >= 0) || (cur_sum < 0 && data_list[idx] < 0))
		{
			calc(abs(cur_sum) / abs(data_list[idx]), idx + 1);
		}
		else // 만약 음수 결과라면
		{
			calc(abs(cur_sum) / abs(data_list[idx]) * -1, idx + 1);
		}
		op_division++;
	}

	return;
}

int main()
{
	cin >> total_data;
	for (int s = 0; s < total_data; s++)
	{
		int cur_data;
		cin >> cur_data;
		data_list[s] = cur_data;
	}

	cin >> op_plus;
	cin >> op_minus;
	cin >> op_multiply;
	cin >> op_division;

	calc(data_list[0], 1);

	cout << max_num << endl;
	cout << min_num << endl;

	return 0;
}