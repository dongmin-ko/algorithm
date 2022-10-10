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

void tour(int day, int posi, int time, int sati) { // DFS로 구현

	// is answer
	if (day == total_day && posi == airpot && time > 0) {
		if (sati > answer) {
			answer = sati;
			fin_route = cur_route;
		}
		return;
	}

	// is visited
	for (int p = 1; p <= total_p; p++) { // 모든 장소를 조회해 보자.
		if (p == posi) { // 현위치랑 같은곳을 갈 필요가 없다.
			continue;
		}
		else if (p_info[p] == 'P' && visited[p] == true) { // 이미 갔던 관광지도 갈 필요는 없다.
			continue;
		}

		// 다음 방문지를 생각해보자.
		if (day != total_day) { // 오늘이 마지막 날이 아니라면.
			if (p == airpot) { continue; } // 공항을 갈 필요가 없다.
			for (int s = 1; s <= hotel.size(); s++) { // 모든 호텔을 도착의 경우의 수로 생각해서
				if ((time + p_to_p[posi][p] + p_time_consume[p] + p_to_p[p][hotel[s]]) <= MAX_TIME && (p != hotel[s])) { // 여행지를 들렸다 해당 호텔을 갈 수 있다면
					visited[p] = true; // 일단 가보자
					cur_route.push_back(p);
					tour(day, p, time + p_to_p[posi][p] + p_time_consume[p], sati + p_satisfaction[p]); //일단 가보자
					cur_route.pop_back();
					visited[p] = false; // 가봤을 경우를 확인했으니 원복하자
				}
				else {
					cur_route.push_back(p);
					tour(day + 1, p, 0, sati); // 더이상 갈 곳이 없다면 다음날을 시작해보자
					cur_route.pop_back();
				}
			}
		}
		else { // 오늘이 마지막 날 이라면.
			for (int s = 1; s <= hotel.size(); s++) { if (p == hotel[s]) { continue; } }// 호텔을 갈 필요가 없다.
			if ((time + p_to_p[posi][p] + p_time_consume[p] + p_to_p[p][airpot]) <= MAX_TIME) { // 놀러갈 곳이 더 있고 갔다가 공항을 갈 수 있다면
				visited[p] = true; // 일단 가보자
				cur_route.push_back(p);
				tour(day, p, time + p_to_p[posi][p] + p_time_consume[p], sati + p_satisfaction[p]); //일단 가보자
				cur_route.pop_back();
				visited[p] = false; // 가봤을 경우를 확인했으니 원복하자
				return;
			}
			else { // 더이상 갈 곳이 없다면 공항으로 가자
				visited[p] = true;
				cur_route.push_back(p);
				tour(day, airpot, time + p_to_p[posi][airpot], sati); //일단 가보자
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
