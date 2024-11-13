#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;
void sensingMaze(string windyMaze[][7], int west, int north, int east, int south); //Gives the sensing updates
void movementMaze(string windyMaze[][7], char direction);//Gives the movement Update
int main() {
	//initialize the maze
	string windyMaze[6][7]{};
	//Setting up initial maze
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			windyMaze[i][j] = "2.63";
		}
	}
	//setting walls within the maze
	windyMaze[1][1] = "####", windyMaze[3][1] = "####", windyMaze[1][4] = "####",
		windyMaze[3][4] = "####";
	//printing the starting maze out
	cout << "Made by Dalton Heising" << endl;
	cout << "Initial Location Probabilities:" << endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			cout << setfill(' ') << setw(8) << left << setprecision(4) << windyMaze[i][j];
		}
		cout << endl;
	}
	//performing the sensing and movement updates within the maze
	sensingMaze(windyMaze, 0, 0, 0, 0);
	movementMaze(windyMaze, 'N');
	sensingMaze(windyMaze, 1, 0, 0, 0);
	movementMaze(windyMaze, 'N');
	sensingMaze(windyMaze, 0, 0, 0, 0);
	movementMaze(windyMaze, 'W');
	sensingMaze(windyMaze, 0, 1, 0, 1);
	movementMaze(windyMaze, 'W');
	sensingMaze(windyMaze, 1, 0, 0, 0);
	return 0;
}
void sensingMaze(string windyMaze[][7], int west, int north, int east, int south) {
	float westProb = 0, northProb = 0, eastProb = 0, southProb = 0, temp = 0;
	float detectWall = 0.8, falseNoWall = 0.2, detectFalseWall = 0.15, detectNoWall = 0.85;
	float total = 0;
	string tempMaze[6][7];
	for (int i = 0; i < 6; i++) { //Loop to run through 2d array
		for (int j = 0; j < 7; j++) {
			if (windyMaze[i][j] == "####") { // skip calculations for wall coords
			}
			else {
				//Switches used to determine if there is actual wall or not
				//West Start
				switch (west) { //check if there is wall or not
				case 1:
					if ((j - 1 <= -1 || windyMaze[i][j - 1] == "####"))
						westProb = detectWall;
					else
						westProb = detectFalseWall;
					break;
				case 0:
					if ((j - 1 > -1 && windyMaze[i][j - 1] != "####"))
						westProb = detectNoWall;
					else
						westProb = falseNoWall;
					break;
				}
				//West End
				//North Start
				switch (north) {//check if there is wall or not
				case 1:
					if ((i - 1 <= -1 || windyMaze[i - 1][j] == "####"))
						northProb = detectWall;
					else
						northProb = detectFalseWall;
					break;
				case 0:
					if ((i - 1 > -1 && windyMaze[i - 1][j] != "####"))
						northProb = detectNoWall;
					else
						northProb = falseNoWall;
					break;
				}
				//North End
				//East Start
				switch (east) {//check if there is wall or not
				case 1:
					if ((j + 1 >= 7 || windyMaze[i][j + 1] == "####"))
						eastProb = detectWall;
					else
						eastProb = detectFalseWall;
					break;
				case 0:
					if ((j + 1 < 7 && windyMaze[i][j + 1] != "####"))
						eastProb = detectNoWall;
					else
						eastProb = falseNoWall;
					break;
				}
				//East End
				//South Start
				switch (south) {//check if there is wall or not
				case 1:
					if ((i + 1 >= 6 || windyMaze[i + 1][j] == "####"))
						southProb = detectWall;
					else
						southProb = detectFalseWall;
					break;
				case 0:
					if ((i + 1 < 6 && windyMaze[i + 1][j] != "####"))
						southProb = detectNoWall;
					else
						southProb = falseNoWall;
					break;
				}
				//South End
				temp = (westProb * northProb * eastProb * southProb) *
					stof(windyMaze[i][j]); // P(z|s) P(s);
				total += temp; //P(z)
				tempMaze[i][j] = to_string(temp); //sending value to temp array
			}
		}
	}
	cout << "Made by Dalton Heising";
	cout << endl << "Filtering after Evidence: [" << west << ", " << north << ", " << east << "," << south << "]" << endl;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				if (windyMaze[i][j] == "####") { //skip calculations for wall coords
					cout << setfill(' ') << setw(8) << left << setprecision(4) <<
						windyMaze[i][j];
				}
				else {
					temp = 100 * (stof(tempMaze[i][j])) / total; //Still working on
					windyMaze[i][j] = to_string(temp); //sending value to actual maze
					cout << setfill(' ') << setw(8) << left << setprecision(2) << fixed <<
						temp; //simple print of array element value with 2 decimal precision
				}
			}
			cout << endl;
		}
	return;
}
void movementMaze(string windyMaze[][7], char direction) {
	float mainDir = 0.8, altDir = 0.1;
	string tempMaze[6][7] = {};
	char charDirection = direction;
	float temp = 0;
	for (int i = 0; i < 6; i++) {//Simple initilization of a temp array to hold values
		for (int j = 0; j < 7; j++) {
			tempMaze[i][j] = "0";
		}
	}
	tempMaze[1][1] = "####", tempMaze[3][1] = "####", tempMaze[1][4] = "####",
		tempMaze[3][4] = "####"; //set walls for temp array
	cout << "Made by Dalton Heising";
	cout << endl << "Prediction after Action " << charDirection << ": " << endl;
	switch (charDirection) {//Switch used to determine direction
	case 'W'://Takes the value of direction to figure out actual actions to perform
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				if (windyMaze[i][j] == "####") { //skip calculations for wall coords
					cout << setfill(' ') << setw(8) << left << setprecision(2) <<
						fixed << tempMaze[i][j];
				}
				else {
					if (j + 1 < 7 && windyMaze[i][j + 1] != "####")
						temp += stof(windyMaze[i][j + 1]) * mainDir;//Part of movement
						if (j - 1 <= -1 || windyMaze[i][j - 1] == "####")
							temp += stof(windyMaze[i][j]) * mainDir;//Part of movement
						if (-1 < i - 1 && windyMaze[i - 1][j] != "####")
							temp += stof(windyMaze[i - 1][j]) * altDir;//Part of movement
						if (i - 1 <= -1 || windyMaze[i - 1][j] == "####")
							temp += stof(windyMaze[i][j]) * altDir;//Part of movement
						if (i + 1 < 6 && windyMaze[i + 1][j] != "####")
							temp += stof(windyMaze[i + 1][j]) * altDir;//Part of movement
						if (i + 1 >= 6 || windyMaze[i + 1][j] == "####")
							temp += (stof(windyMaze[i][j]) * altDir);//Part of movement
						cout << setfill(' ') << setw(8) << left << setprecision(2) <<
						fixed << temp;
					tempMaze[i][j] = to_string(temp);//Setting up temp array with valuues of the movement
				}
				temp = 0;
			}
			cout << endl;
		}
		break;
	case 'N':
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				if (windyMaze[i][j] == "####") { //skip calculations for wall coords
					cout << setfill(' ') << setw(8) << left << setprecision(2) <<
						fixed << tempMaze[i][j];
				}
				else {
					if (i + 1 < 6 && windyMaze[i + 1][j] != "####")
						temp += stof(windyMaze[i + 1][j]) * mainDir;//Part of movement
						if (i - 1 <= -1 || windyMaze[i - 1][j] == "####")
							temp += stof(windyMaze[i][j]) * mainDir;//Part of movement
						if (-1 < j - 1 && windyMaze[i][j - 1] != "####")
							temp += stof(windyMaze[i][j - 1]) * altDir;//Part of movement
						if (j - 1 <= -1 || windyMaze[i][j - 1] == "####")
							temp += stof(windyMaze[i][j]) * altDir;//Part of movement
						if (j + 1 < 7 && windyMaze[i][j + 1] != "####")
							temp += stof(windyMaze[i][j + 1]) * altDir;//Part of movement
						if (j + 1 >= 7 || windyMaze[i][j + 1] == "####")
							temp += (stof(windyMaze[i][j]) * altDir);//Part of movement
						cout << setfill(' ') << setw(8) << left << setprecision(2) <<
						fixed << temp;
					tempMaze[i][j] = to_string(temp);//Setting up temp array with valuues of the movement
				}
				temp = 0;
			}
			cout << endl;
		}
		break;
	case 'E':
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				if (windyMaze[i][j] == "####") { //skip calculations for wall coords
					cout << setfill(' ') << setw(8) << left << setprecision(2) <<
						fixed << tempMaze[i][j];
				}
				else {
					if (j - 1 > -1 && windyMaze[i][j - 1] != "####")
						temp += stof(windyMaze[i][j - 1]) * mainDir;//Part of movement
						if (j + 1 >= 7 || windyMaze[i][j + 1] == "####")
							temp += stof(windyMaze[i][j]) * mainDir;//Part of movement
						if (-1 < i - 1 && windyMaze[i - 1][j] != "####")
							temp += stof(windyMaze[i - 1][j]) * altDir;//Part of movement
						if (i - 1 <= -1 || windyMaze[i - 1][j] == "####")
							temp += stof(windyMaze[i][j]) * altDir;//Part of movement
						if (i + 1 < 6 && windyMaze[i + 1][j] != "####")
							temp += stof(windyMaze[i + 1][j]) * altDir;//Part of movement
						if (i + 1 >= 6 || windyMaze[i + 1][j] == "####")
							temp += (stof(windyMaze[i][j]) * altDir);//Part of movement
						cout << setfill(' ') << setw(8) << left << setprecision(2) <<
						fixed << temp;
					tempMaze[i][j] = to_string(temp);//Setting up temp array with valuues of the movement
				}
				temp = 0;
			}
			cout << endl;
		}
		break;
	case 'S':
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 7; j++) {
				if (windyMaze[i][j] == "####") {//skip calculations for wall coords
					cout << setfill(' ') << setw(8) << left << setprecision(2) <<
						fixed << tempMaze[i][j];
				}
				else {
					if (i - 1 > -1 && windyMaze[i - 1][j] != "####")
						temp += stof(windyMaze[i - 1][j]) * mainDir;//Part of movement
						if (i + 1 >= 6 || windyMaze[i + 1][j] == "####")
							temp += stof(windyMaze[i][j]) * mainDir;//Part of movement
						if (-1 < j - 1 && windyMaze[i][j - 1] != "####")
							temp += stof(windyMaze[i][j - 1]) * altDir;//Part of movement
						if (j - 1 <= -1 || windyMaze[i][j - 1] == "####")
							temp += stof(windyMaze[i][j]) * altDir;//Part of movement
						if (j + 1 < 7 && windyMaze[i][j + 1] != "####")
							temp += stof(windyMaze[i][j + 1]) * altDir;//Part of movement
						if (j + 1 >= 7 || windyMaze[i][j + 1] == "####")
							temp += (stof(windyMaze[i][j]) * altDir);//Part of movement
						cout << setfill(' ') << setw(8) << left << setprecision(2) <<
						fixed << temp;//Prints value at array element
					tempMaze[i][j] = to_string(temp);//Setting up temp array with values of the movement
				}
				temp = 0;
			}
			cout << endl;
		}
		break;
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			windyMaze[i][j] = tempMaze[i][j];//Sets actual maze values to the movement update
		}
	}
}
