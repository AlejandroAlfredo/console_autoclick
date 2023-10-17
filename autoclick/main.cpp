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
	void listen();
	void background();
	void banner();
private:
	bool click = false;
	bool flags = false;
	int delay = 200;
	string num;
	string options;
};

Autoclicker::Autoclicker()
{

}

Autoclicker::~Autoclicker()
{

}

void Autoclicker::banner()
{
	cout << "[F6] Start / Stop" << endl;
	cout << "[*] Delay" << endl;
	cout << "Delay: " << this->delay << endl;
	string result = (this->click == true) ? ">> ON" : ">> OFF";
	cout << result << endl;
}

void Autoclicker::background()
{
	while (this->flags)
	{
		if (this->click) {
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(this->delay);
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
	instance.listen();
	thread working(secondary, instance);
	return 0;
}