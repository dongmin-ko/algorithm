#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>
#include <memory.h>
#include <math.h>
#define  MAX_LEN 20 // �׻� ���̴� ¦�� ����
using namespace std;

bool is_players[MAX_LEN+1];
int total_players;
int team_players;
int status[MAX_LEN + 1][MAX_LEN + 1];

vector<int> teamA;
vector<int> teamB;

int min_difference = 100000000;

void make_team(int count, int player)
{
	if (count + (total_players - player + 1) < team_players)
	{
		return;
	}

	if (teamA.size() >= team_players)
	{
		// �ַ�� ����
		for (int p = 1; p <= total_players; p++)
		{
			if (!is_players[p])
			{
				teamB.push_back(p);
			}
		}

		if (teamA.size() == teamB.size())
		{
			int teamAscore = 0;
			int teamBscore = 0;

			for (int p1 = 0; p1 < team_players; p1++)
			{
				for (int p2 = 0; p2 < team_players; p2++)
				{
					if (p1 == p2)
					{
						continue;
					}
					else
					{
						teamAscore += status[teamA[p1]][teamA[p2]];
						teamBscore += status[teamB[p1]][teamB[p2]];
					}
				}
			}

			if (abs(teamAscore - teamBscore) < min_difference)
			{
				min_difference = abs(teamAscore - teamBscore);
			}
		}
		teamB.clear();
		return;
	}
	else
	{
		// �� ������ a������ ���� �ϴ� ���.
		is_players[player] = true;
		teamA.push_back(player);
		make_team(count + 1, player + 1);
		teamA.pop_back();

		// �� ������ a������ ���� ���ϴ� ���.
		is_players[player] = false;
		make_team(count, player + 1);
	}
	return;
}

int main()
{
	memset(is_players, false, sizeof(is_players));
	cin >> total_players;
	team_players = total_players / 2;

	for (int s = 1; s <= total_players;s++)
	{
		for (int t = 1; t <= total_players; t++)
		{
			int status_data;
			cin >> status_data;
			status[s][t] = status_data;
		}
	}

	make_team(0,1);

	cout << min_difference << endl;

	return 0;
}