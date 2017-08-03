#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <conio.h>

using namespace std;

const int row = 9;
const int col = 9;
int maxShip = 4;
char PlayerBoard[col][row];
char ComBoard[col][row];
char Comboard[col][row];
char PlayerAttacked[col][row];
char ComAttacked[col][row];
int Player = 0;
int Com = 0;
double hits = 0;
double miss = 0;
double rate;
int Comx;
int Comy;
int Playerx;
int Playery;
//bool running = false;
char choice[2];
int numOfDirect;
bool turn = false;
//int x = 2;
//int y = 2;




// phototype

void setBoard();
void setPlayerShip(char & choice);
void setComShip();
void showBoard();
void showBoard2(int, int, int, int);
void playerAttack(int &x, int &y);
void comAttack(int &x, int &y);
char convert(int n);
void Convert(char ch[],int &,int &, int &, int &);
char * convert2( int x, int y);
void gotoxy(int x, int y);
void showmenu();
void gamePlay(char);
void gameRule(char &);
void showmenu2(char);
void showinfo();
void checkchoice(char []);
void reset();
void victory();
void setLastShipPoint( int &, int &, int &, int &);
int * checkDirect(int, int);
int count(int *);
bool checkLastShipPoint(int, int, int, int);
bool checkLastShipPoint2(int, int, int, int);
void convert3(char *, int &, int &);
int myAbs(int);
bool checkCondition(int, int, int, int);
void setPlayerShip2(char &);
void Convert3(char[], int &, int &);
void kb(int &x, int &y, char & ch);

//char back;


int main()
{
	showmenu();
	
	cin >> choice;
	checkchoice(choice);
		
		while (choice[0] != 'q' && choice[0] != 'Q')
		{
			switch(choice[0])
			{
				case '1': gameRule(choice[0]);
					break;
				case '2': gamePlay(choice[0]);
					break;
				default: cout << "That's not a choice, please enter again: " << endl;
						cin.clear();
			}
			reset();
			showmenu2(choice[0]);
		
			cin >> choice;
			checkchoice(choice);
		}
	showmenu();
	
	
	cout << "Bye" << endl;
	return 0;
}

void playerAttack( int &x, int &y)
{
	
	char ch;
	cout << "Enter the position you want to attack(q to surender): " ;
	
	kb(x, y, ch);
		if (ch == 'q')
		{
			Com = maxShip * 8;
			gotoxy(0, 29);
				cout << "You lose" << endl;
			return;
		}
	while (PlayerAttacked[(y - 2)][(x - 2) / 2] == '*')
	{
		gotoxy(0, 24);
		cout << "You've already attacked this point, please choose another point" << endl;
		kb(x, y, ch);
			if (ch == 'q')
				return;
	}

	while (!cin || y - 2 < 0 || (x - 2) / 2 > col || y < 0 || y - 2 > row)
	{
		gotoxy(0, 28);
		cout << "Out of range, please enter again " ;
		kb(x, y, ch);
			if (ch == 'q')
				return;
	}
	PlayerAttacked[y - 2 ][(x - 2) / 2] = '*';



	if (Comboard[y - 2][(x - 2) / 2] == 'S')
	{
		ComBoard[(y - 2)][(x - 2) / 2] = 'H';
		Player++;
		hits++;
		turn = true;
	}

	else 
		{	
			ComBoard[(y - 2)][(x - 2) / 2] = ' ';
			miss++;
			turn = false;
		}
		if (Player == maxShip * 8 || Com == maxShip * 8)
			turn = false;
}

void setBoard()
{
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			PlayerBoard[i][j] = '*';
			ComBoard[i][j] = '*';
			Comboard[i][j] = '*';
		}
	}
}

void showBoard()
{
	system("CLS") ;
	cout << "   Computer Board" << endl << "  ";
	for (int i = 0; i < col; i++)
	{
		cout << i + 1 << " " ;
	}
	cout << endl;
	for (int i = 0; i < col;  i++)
	{
		cout << convert(i) << " ";
		for (int j = 0; j < row; j++)
		{
			cout << ComBoard[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl << endl;

	cout << "    Player Board" << endl << "  ";

		for (int i = 0; i < col; i++)
	{
		cout << i + 1 << " " ;
	}
	cout << endl;
	for (int i = 0; i < col;  i++)
	{
		cout << convert(i) << " ";
		for (int j = 0; j < row; j++)
		{
			cout << PlayerBoard[i][j] << " ";
		}
		cout << endl;
	}
	
	showinfo();
}

void showBoard2(int a, int b, int c, int d)
{
	system("CLS");
	cout << "   Computer Board" << endl << "  ";
	for (int i = 0; i < col; i++)
	{
		cout << i + 1 << " " ;
	}
	cout << endl;
	for (int i = 0; i < col;  i++)
	{
		cout << convert(i) << " ";
		for (int j = 0; j < row; j++)
		{
			cout << ComBoard[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl << endl;

	cout << "    Player Board" << endl << "  ";

		for (int i = 0; i < col; i++)
	{
		cout << i + 1 << " " ;
	}
	cout << endl;
	for (int i = 0; i < col;  i++)
	{
		cout << convert(i) << " ";
		for (int j = 0; j < row; j++)
		{
			cout << PlayerBoard[i][j] << " ";
		}
		cout << endl;
	}
	char * playerPoint;
	char * comPoint;
	playerPoint = convert2(a, b);

	cout << "You've attacked the point "<< playerPoint[0] << playerPoint[1] <<  endl;
	comPoint = convert2(c, d);
	cout << "The enemy've attacked the point "<< comPoint[0] << comPoint[1] <<  endl;

	showinfo();

}

char * convert2( int x, int  y)
{
	char *ch =new char[10];
	if (x == 0) ch[0] = 'A';
	else if (x == 1) ch[0] = 'B';
	else if (x == 2) ch[0] = 'C';
	else if (x == 3) ch[0] = 'D';
	else if (x == 4) ch[0] = 'E';
	else if (x == 5) ch[0] = 'F';
	else if (x == 6) ch[0] = 'G';
	else if (x == 7) ch[0] = 'H';
	else if (x == 8) ch[0] = 'I';
	else if (x == 9) ch[0] = 'K';

	if (y == 0) ch[1] = '1';
	else if (y == 1) ch[1] = '2';
	else if (y == 2) ch[1] = '3';
	else if (y == 3) ch[1] = '4';
	else if (y == 4) ch[1] = '5';
	else if (y == 5) ch[1] = '6';
	else if (y == 6) ch[1] = '7';
	else if (y == 7) ch[1] = '8';
	else if (y == 8) ch[1] = '9';
	else if (y == 9)
	{
		ch[1] == '1';
		ch[2] == '0';
	}
	
	if (y != 9)
	    ch[2] == '\0';
	return ch;

}
void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}

void comAttack(int &x, int &y)
{
	turn = true;
	x = rand() % col;
	y = rand() % row;
	while (ComAttacked[x][y] == '*')
	{
		x = rand() % col;
		y = rand() % row;
	}
		if (PlayerBoard[x][y] == 'S')
	{
	//	cout << "You've being hited by the enemy " << endl;
		PlayerBoard[x][y] = 'H';
		ComAttacked[x][y] = '*';
		Com++;
		turn = true;
		return;
	}

	else
	{
		PlayerBoard[x][y] = ' ';
		ComAttacked[x][y] = '*';
		turn = false;
		return;
	}
	
	if (Player == maxShip * 8 || Com == maxShip * 8)
	{
		turn = false;
		return;
	}
		
 }

 char convert(int n)
 {
 	switch (n)
 	{
 		case 0 : return 'A';
 		case 1 : return 'B';
 		case 2 : return 'C';
 		case 3 : return 'D';
 		case 4 : return 'E';
 		case 5 : return 'F';
 		case 6 : return 'G';
 		case 7 : return 'H';
 		case 8 : return 'I';
 		case 9 : return 'K';

	 }
 }

 void Convert(char ch[],int &x1,int &y1, int &x2, int &y2)
 {
 	if (ch[0] == 'a' || ch[0] == 'A')  y1 = 0;
 	else if (ch[0] == 'b' || ch[0] == 'B')  y1 = 1;
 	else if (ch[0] == 'c' || ch[0] == 'C')  y1 = 2;
 	else if (ch[0] == 'd' || ch[0] == 'D')  y1 = 3;
 	else if (ch[0] == 'e' || ch[0] == 'E')  y1 = 4;
 	else if (ch[0] == 'f' || ch[0] == 'F')  y1 = 5;
 	else if (ch[0] == 'g' || ch[0] == 'G')  y1 = 6;
 	else if (ch[0] == 'h' || ch[0] == 'H')  y1 = 7;
 	else if (ch[0] == 'i' || ch[0] == 'I')  y1 = 8;
 	else if (ch[0] == 'k' || ch[0] == 'K')  y1 = 9;
 	else if (ch[0] == 'q' || ch[0] == 'Q')  y1 = -2;
 	else y1 = -1;

 	if (ch[1] == '1')  x1 = 0;
 	else if (ch[1] == '2' ) x1 = 1;
 	else if (ch[1] == '3' ) x1 = 2;
 	else if (ch[1] == '4' ) x1 = 3;
 	else if (ch[1] == '5' ) x1 = 4;
 	else if (ch[1] == '6' ) x1 = 5;
 	else if (ch[1] == '7' ) x1 = 6;
 	else if (ch[1] == '8' ) x1 = 7;
 	else if (ch[1] == '9' ) x1 = 8;
 	else if (ch[1] == '1' ) x1 = 9;
 	else x1 = -1;
 	
 	if (ch[2] == 'a' || ch[2] == 'A')  y2 = 0;
 	else if (ch[2] == 'b' || ch[2] == 'B')  y2 = 1;
 	else if (ch[2] == 'c' || ch[2] == 'C')  y2 = 2;
 	else if (ch[2] == 'd' || ch[2] == 'D')  y2 = 3;
 	else if (ch[2] == 'e' || ch[2] == 'E')  y2 = 4;
 	else if (ch[2] == 'f' || ch[2] == 'F')  y2 = 5;
 	else if (ch[2] == 'g' || ch[2] == 'G')  y2 = 6;
 	else if (ch[2] == 'h' || ch[2] == 'H')  y2 = 7;
 	else if (ch[2] == 'i' || ch[2] == 'I')  y2 = 8;
 	else if (ch[2] == 'k' || ch[2] == 'K')  y2 = 9;
 	else if (ch[2] == 'q' || ch[2] == 'Q')  y2 = -2;
 	else y2= -1;

 	if (ch[3] == '1' && ch[3] == '\0')  x2 = 0;
 	else if (ch[3] == '2' && ch[4] == '\0') x2 = 1;
 	else if (ch[3] == '3' && ch[4] == '\0') x2 = 2;
 	else if (ch[3] == '4' && ch[4] == '\0') x2 = 3;
 	else if (ch[3] == '5' && ch[4] == '\0') x2 = 4;
 	else if (ch[3] == '6' && ch[4] == '\0') x2 = 5;
 	else if (ch[3] == '7' && ch[4] == '\0') x2 = 6;
 	else if (ch[3] == '8' && ch[4] == '\0') x2 = 7;
 	else if (ch[3] == '9' && ch[4] == '\0') x2 = 8;
 	else if (ch[3] == '1' && ch[4] == '\0') x2= 9;
 	else x2 = -1;

 }

 
void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}

void showmenu()
{
	system("CLS");
	cout << "Welcome to Battle Ship" << endl;
	cout << "Please enter 1, 2 or q:\n"
			"1) Show the game rule\n"
			"2) Enjoy the game\n"
			"q) Quiz the game\n";
}

void gamePlay(char ch)
{
	reset();
	setBoard();
	showBoard();
	setPlayerShip(ch);
//	setPlayerShip2(choice);
	

	if (ch == 'q' || ch == 'Q')
		return;
	setComShip();
	showBoard();
	while (Player != maxShip * 8 && Com != maxShip * 8)
	{
		playerAttack(Playerx, Playery);
		showBoard2(Playerx, Playery, Comx, Comy);
		while (turn == true)
		{
			cout << " ahihi " << endl;
			playerAttack(Playerx, Playery);
			showBoard2(Playerx, Playery, Comx, Comy);
			if (choice[0] == 'q')
				break;
			
		}
		if (Player == maxShip * 8 || Com == maxShip * 8)
			break;
		comAttack(Comx, Comy);
			
		showBoard2(Playerx, Playery, Comx, Comy);
		if (Player == maxShip * 8 || Com == maxShip * 8)
			break;
		while (turn == true)
		{
			cout << "You are hited by the enemy " << endl;
			Sleep(500);
			comAttack(Comx, Comy);
			showBoard2(Playerx, Playery, Comx, Comy);
		}

	}
	if (Player == maxShip * 8)
		cout << "You win " << endl;
	else if (Com == maxShip * 8)  cout << "You lose" << endl;
	
	cout << "press any key to exit" << endl;
	char ch1;
	cin >> ch1;
	showmenu();
	return;

	
	
}
void showmenu2(char choice)
{
	if (choice == 'q' || choice == 'Q')
		showmenu();
}

void showinfo()
{
	gotoxy(50,0);
		cout << "H = HITS" << endl;
	gotoxy(50,1);
		cout << "M = MISS" << endl;
	gotoxy(50,2);
		cout << "Hits = " <<  fixed << setprecision(0) << hits << endl;
	gotoxy(50,3);
		cout << "Miss = "<< fixed << setprecision(0)  << miss << endl;
	
	if (miss == 0) 
	{
		gotoxy(50,4);
			cout << "Rate = 100%" << endl; 
	} 
	else
	{
		rate = hits / (hits + miss);
		gotoxy(50,4);
			cout << "Rate = " << fixed << setprecision(3) << rate * 100 << "%" << endl;
	}
	
	gotoxy(50, 7);
		cout << "W: Move up ";
	gotoxy(50, 8);
		cout << "S: Move down ";
	gotoxy(50, 9);
		cout << "A: Move left ";
	gotoxy(50, 10);
		cout << "D: Move right ";
	gotoxy(50, 11);
		cout << "J: Attack ";
	gotoxy(0, 28);
}

void reset()
{
	Player = 0;
	Com = 0;
	hits = 0;
	miss = 0;
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			PlayerAttacked[i][j] = ' ';
			ComAttacked[i][j] = ' ';
		}
	}
}

void checkchoice(char choice[])
{
	while (strlen(choice) != 1)
	{
		cout << "Please enter again: " ;
		cin >> choice;
	}
}

int myAbs(int a)
{
	if (a > 0 ) return a;
	else return -a;
}
void kb(int &x, int &y, char & ch)
{
    	
    	if (x == 0)
    		x = 2;
    	if (y == 0)
    		y = 2;
    while (1)
    {
		gotoxy(x, y);
        if (_kbhit())
        {
            int key = _getch();
            switch (key)
            {
			
            	case 'W':
            	case 'w': y = y - 1;
            		gotoxy(x, y);
					break;
				case 'A':
				case 'a': x = x - 2;
					gotoxy(x, y);
					break;
				case 'S': 
				case 's': y = y + 1;
					gotoxy(x, y);
					break;
				case 'D':
				case 'd': x = x + 2;
					gotoxy(x, y);
					break;
				case 'j':
				case 'J':
					return;
				case 'Q':
				case 'q':
					ch = 'q';
					return;
			}
			
        }
        
    }

}


