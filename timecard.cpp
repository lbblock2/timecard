/*
 */
#include <stdio.h>
#include <time.h>
#include <iostream.h>
#include <string.h>
using namespace std;

#define kNumMonths 12

void showHelp();
void actOnCommand(std::string command, int *quitSignal);


class timecard
{
public:
	timecard(){}

	~timecard()

	void showHelp() {
		cout << "Open" << endl;
		cout << "Add" << endl;
		cout << "View" << endl;
		cout << "Edit" << endl;
		cout << "Delete" << endl;
		cout << "Save" << endl;
		cout << "Quit" << endl;
		cout << "help" << endl;
	}

	void actOnCommand(std::string command, int *quitSignal) {
		char cmnd = tolower(command[0]);
		switch(cmnd) {
			case 'h' :
				showHelp();
				break;
			// case 'o':
			// case 'a':
			// case 'v':
			// case 'e':
			// case 'd':
			// case 's':
				case 'q':
				*quitSignal = 0;
				break;
			default:
				showHelp();
		}
	}	

	/* data */
};


int main() {
	FILE *fp = fopen("timecard.tmc", "r+");
	time_t initTime = time(0);
	struct tm *	now = localtime(&initTime);
	int currYear = now->tm_year + 1900;
	int currMonth = now->tm_mon + 1;
	cout << "Welcome to Timecard!" << endl;
	std::string command;
	int quitSignal = 1;
	while (quitSignal == 1) {
		cout << "Command: ";
		cin >> command;
		actOnCommand(command, &quitSignal);
	}
}




