#include <iostream>
#include <memory.h>
using namespace std;

int room_total;
int* room_cap;

int major;
int minor;

int answer = 0;

int ref_table[1000001];

int counter(int& cur_room_cap, int cur_major, int cur_minor, int cur_total) {

	if (ref_table[cur_room_cap] != 0)
	{
		return ref_table[cur_room_cap];
	}
	else if (cur_room_cap <= cur_major)
	{
		ref_table[cur_room_cap] = 1;
		return ref_table[cur_room_cap];
	}
	else {
		ref_table[cur_room_cap] = 1 + ((cur_room_cap - cur_major) % cur_minor == 0 ? (cur_room_cap - cur_major) / cur_minor : (cur_room_cap - cur_major) / cur_minor + 1);
		return ref_table[cur_room_cap];
	}

	return 0;
}

int main() {
	cin >> room_total;
	room_cap = new int[room_total];
	memset(ref_table, 0, sizeof(int) * 1000001);

	for (int s = 0; s < room_total; s++)
	{
		int cur_room = 0;
		cin >> cur_room;
		room_cap[s] = cur_room;
	}

	cin >> major;
	cin >> minor;

	for (int t = 0; t < room_total; t++)
	{
		answer += counter(room_cap[t], major, minor, major);
	}

	cout << answer;

	delete[] room_cap;

	return 0;
}