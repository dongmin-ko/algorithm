#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <memory.h>
#define MAX_TIME 540
using namespace std;

int total_p;
int total_day;
bool visited[36];
int p_to_p[36][36]; // time consume to move other point
char p_info[36];
int p_time_consume[36];
int p_satisfaction[36];
int airpot;
vector<int> hotel;
vector<int> fin_route;
vector<int> cur_route;
int answer;

void init() {
	for (int s = 0; s < 36; s++) { visited[s] = false; }
	hotel.clear();
	fin_route.clear();
	cur_route.clear();
	answer = 0;
	return;
}

void tour(int day, int posi, int time, int sati) { // DFS�� ����

	// is answer
	if (day == total_day && posi == airpot && time > 0) {
		if (sati > answer) {
			answer = sati;
			fin_route = cur_route;
		}
		return;
	}

	// is visited
	for (int p = 1; p <= total_p; p++) { // ��� ��Ҹ� ��ȸ�� ����.
		if (p == posi) { // ����ġ�� �������� �� �ʿ䰡 ����.
			continue;
		}
		else if (p_info[p] == 'P' && visited[p] == true) { // �̹� ���� �������� �� �ʿ�� ����.
			continue;
		}

		// ���� �湮���� �����غ���.
		if (day != total_day) { // ������ ������ ���� �ƴ϶��.
			if (p == airpot) { continue; } // ������ �� �ʿ䰡 ����.
			for (int s = 1; s <= hotel.size(); s++) { // ��� ȣ���� ������ ����� ���� �����ؼ�
				if ((time + p_to_p[posi][p] + p_time_consume[p] + p_to_p[p][hotel[s]]) <= MAX_TIME && (p != hotel[s])) { // �������� ��ȴ� �ش� ȣ���� �� �� �ִٸ�
					visited[p] = true; // �ϴ� ������
					cur_route.push_back(p);
					tour(day, p, time + p_to_p[posi][p] + p_time_consume[p], sati + p_satisfaction[p]); //�ϴ� ������
					cur_route.pop_back();
					visited[p] = false; // ������ ��츦 Ȯ�������� ��������
				}
				else {
					cur_route.push_back(p);
					tour(day + 1, p, 0, sati); // ���̻� �� ���� ���ٸ� �������� �����غ���
					cur_route.pop_back();
				}
			}
		}
		else { // ������ ������ �� �̶��.
			for (int s = 1; s <= hotel.size(); s++) { if (p == hotel[s]) { continue; } }// ȣ���� �� �ʿ䰡 ����.
			if ((time + p_to_p[posi][p] + p_time_consume[p] + p_to_p[p][airpot]) <= MAX_TIME) { // ��� ���� �� �ְ� ���ٰ� ������ �� �� �ִٸ�
				visited[p] = true; // �ϴ� ������
				cur_route.push_back(p);
				tour(day, p, time + p_to_p[posi][p] + p_time_consume[p], sati + p_satisfaction[p]); //�ϴ� ������
				cur_route.pop_back();
				visited[p] = false; // ������ ��츦 Ȯ�������� ��������
				return;
			}
			else { // ���̻� �� ���� ���ٸ� �������� ����
				visited[p] = true;
				cur_route.push_back(p);
				tour(day, airpot, time + p_to_p[posi][airpot], sati); //�ϴ� ������
				cur_route.pop_back();
				visited[p] = false;
				return;
			}
		}
	}

	return;
}

int main() {

	int total, current;
	cin >> total;
	for (current = 1; current <= total; current++)
	{
		init();

		cin >> total_p;
		cin >> total_day;

		// get data
		for (int s = 1; s <= total_p - 1; s++) {
			for (int t = s + 1; t <= total_p; t++) {
				int move_time;
				cin >> move_time;
				p_to_p[s][t] = move_time;
				p_to_p[t][s] = move_time;
			}
		}

		for (int s = 1; s <= total_p; s++) {
			char info;
			int cur_timeconsume;
			int cur_satisfication;
			cin >> info;
			if (info == 'P') {
				cin >> cur_timeconsume;
				cin >> cur_satisfication;
				p_info[s] = info;
				p_time_consume[s] = cur_timeconsume;
				p_satisfaction[s] = cur_satisfication;
			}
			else {
				p_info[s] = info;
				p_time_consume[s] = 0;
				p_satisfaction[s] = 0;
				if (info == 'A') {
					airpot = s;
				}
				else {
					hotel.push_back(s);
				}
			}
		}
		// solution
		tour(1, airpot, 0, 0);

		cout << '#' << current << ' ' << answer;
		for (int s = 1; s <= fin_route.size(); s++) {
			cout << ' ' << fin_route[s];
		}
		cout << endl;

	}

	return 0;
}
