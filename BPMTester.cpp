#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
using std::cout, std::endl;

void clear() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };
	DWORD dwWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &dwWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}

size_t t_start = 0, t_finish = 0, t_back = SIZE_MAX - 5001, counter = 0;
double bpm = 0;

int main() {
	cout << "开始计数\n请切换到英文输入法" << endl;
	while (_getch()) {
		t_finish = clock();
		if (t_finish > t_back + 5000) {
			counter = 0;
		}
		t_back = t_finish;
		clear();
		counter++;
		if (counter == 1) {
			t_start = t_finish;
			cout << "BPM精确值: 第一次点击" << endl;
			cout << "BPM整数值: 第一次点击" << endl;
		}
		else {
			bpm = (counter - 1) / double(t_finish - t_start) * 60000;
			cout << "BPM精确值: " << bpm << endl;
			cout << "BPM整数值: " << round(bpm) << endl;
		}
		cout << "点击次数: " << counter << endl;
		cout << "5s未点击将重新开始计数" << endl;
	}
	return 0;
}