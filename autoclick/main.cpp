#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <Windows.h>
using namespace std;

class Autoclicker
{
public:
	Autoclicker();
	~Autoclicker();
	void banner();
	void listen();
	void background();
private:
	static bool click;
	static bool flags;
	static int delay;
	string num;
	string options;
};

Autoclicker::Autoclicker()
{
}

Autoclicker::~Autoclicker()
{
}

bool Autoclicker::click = false;
bool Autoclicker::flags = true;
int Autoclicker::delay = 200;

void Autoclicker::banner()
{
	cout << "[F6] Start / Stop" << endl;
	cout << "[*] Delay" << endl;
	cout << "Delay: " << delay << endl;
	string result = (click == true) ? ">> ON" : ">> OFF";
	cout << result << endl;
}

void Autoclicker::background()
{
	while (flags)
	{
		if (click) {
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(delay);
		}
		Sleep(1);
	}
}

void Autoclicker::listen()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_F6)) {
			if (click == false) {
				click = true;
				Sleep(200);
			}
			else {
				click = false;
				Sleep(200);
			}
			system("cls");
			this->banner();
		}
		else if (GetAsyncKeyState(VK_MULTIPLY)) {
			const char* errStr = "Invalid Characters!";
			try
			{
				click = false;
				cout << "Autoclicker speed(ms): ";
				cin >> num;
				if (cin.eof()) {
					cin.clear();
					throw errStr;
				}
				for (char n : num) {
					if (isdigit(n) == false) {
						throw errStr;
					}
				}
				stringstream(num) >> delay;
				if (delay <= 0) {
					throw errStr;
				}
				system("cls");
				banner();
			}
			catch (const char* err)
			{
				click = false;
				num = "";
				delay = 200;
				system("cls");
				this->banner();
				cout << "Error: " << err << endl;
				cout << ">> Restoring default values" << endl;
			}
		}

		Sleep(1);
	}
}

void secondary(Autoclicker instance) {
	instance.background();
}

int main(void) {
#pragma region win < 11
	// Console size
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT windowsSize = { 0, 0, 60, 10 };
	SetConsoleWindowInfo(wHnd, 1, &windowsSize);

	// TOP MOST
	HWND consoleWindowHandle = GetConsoleWindow();
	SetWindowPos(consoleWindowHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

	// Properties of the console.
	ShowWindow(consoleWindowHandle, SW_NORMAL);
#pragma endregion

	Autoclicker instance;
	instance.banner();
	thread working(secondary, instance);
	instance.listen();
	return 0;
}