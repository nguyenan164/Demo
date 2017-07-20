#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <iomanip>
#include <stdio.h>
#include <string.h>


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

void setPlayerShip(char & choice)
{
	
	char ch[4];
	int x1 = 0;
	int x2 = 0;
	int y1 = 0; 
	int y2 = 0;
	maxShip = 4;
	cout << "Enter the number of ships, maximum " << maxShip << " ship: ";
	cin >> maxShip;
	while (!cin || maxShip > 4 || maxShip < 1)
    {
    	gotoxy(0, 29);
    	cout << "                                                          ";
    	gotoxy(0, 29);
        cout << "Out of range, please enter again: " ;
        cin.clear();
        while (cin.get() != '\n')
            continue;
        cin >> maxShip;
    }
	cout << "Enter the position of your ship, you must enter " << maxShip << " times, q to quit" <<  endl;
	cout << "Each ship has the size 2x4, ex a1b4" << endl;
	for (int i = 0; i < maxShip; i++)
	{
		gotoxy(0, 31 + i);
		cout << "Ship " << i + 1 << ": " ;
		cin.clear();
		cin >> ch;

		Convert(ch, x1, y1, x2, y2);


		while (checkCondition(x1, y1, x2, y2) == false)
		{
		choice = ch[0];
		if ((choice == 'q' || choice == 'Q') && ch[1] == '\0')
			{
				showmenu2(choice);
				return;
			}
			cin.clear();
			while (cin.get() != '\n')
				continue;
			gotoxy(0, 31 + i);
			cout << "                                        ";
			
			gotoxy(0, 31 + i);
			cout << "Set another places:  " << "ship " << i + 1 << ": ";
			cin.clear();
			cin >> ch;
			Convert(ch, x1, y1, x2, y2);


		}
		while (checkLastShipPoint2(x1, y1, x2, y2) == false)
		{
			gotoxy(0, 31 + i);
			cout << "                                        ";
			gotoxy(0, 31 + i);
			cout << "Set another places:  " << "ship " << i + 1 << ": ";
			cin.clear();
			cin >> ch;
			Convert(ch, x1, y1, x2, y2);
			cout << endl;
		}

		int a1 = x1 > x2 ? x2 : x1;
		int a2 = x1 > x2 ? x1 : x2;
		int b1 = y1 > y2 ? y2 : y1;
		int b2 = y1 > y2 ? y1 : y2;
	
		
		
		for (int i = b1 ; i <= b2; i++)
		{
			for(int j = a1; j <= a2; j++)
			{
				PlayerBoard[i][j] = 'S';
				gotoxy(j +j + 2, i + 15);
				cout << 'S'; 
			}
		}
		
	}
	
}

void setComShip()
{
	
	srand(time(NULL));
	int n = 0;
	int x1, y1;
	int x2 = -1;
	int y2 = -1;
	for (int i = 0; i < maxShip; i++)
	{
		again:
		n = 0;
		x1 = rand() % col;
		y1 = rand() % row;
		
		while (Comboard[x1][y1] == 'S')
		{
			x1 = rand() % col;
			y1 = rand() & row;
		}
		
		setLastShipPoint( x1, y1, x2, y2);
//		cout << "x " << x1 << " " << x2 << endl;
//		cout << "y " << y1 << " " << y2 << endl;
		while (checkLastShipPoint(x1, y1, x2, y2) == false)
		{
			setLastShipPoint(x1, y1, x2, y2);
			n++;
			if (n > 10) goto again;
		}
	
		int a1 = x1 > x2 ? x2 : x1;
		int a2 = x1 > x2 ? x1 : x2;
		int b1 = y1 > y2 ? y2 : y1;
		int b2 = y1 > y2 ? y1 : y2;
		
		cout << "a1 = " << a1 << endl;
	
		
		
		for (int i = b1 ; i <= b2; i++)
		{
			for(int j = a1; j <= a2; j++)
			{
				Comboard[i][j] = 'S';
			}
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

void playerAttack(int &x, int &y)
{
	char ch[3];
	cout << "Enter the position you want to attack(q to surender): " ;
	cin.clear();
	cin >> ch;
	choice[0] = ch[0];
	if (ch[0] == 'q' || ch[0] == 'Q')
	{
		Com = maxShip * 8;
		cout << "You Lose" << endl;
		
	//	cout << "Press any key to back to main menu" << endl;
		//cin >> back;
		
		return;
	}
	convert3(ch, x, y);
	while (PlayerAttacked[x][y] == '*')
	{
		cout << "You've already attacked this point, please choose another point" << endl;
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cin >> ch;
		convert3(ch, x, y);
	}

	while (!cin || x < 0 || x > col || y < 0 || y > row)
	{
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "Out of range, please enter again " ;
	cin >> ch;
	convert3(ch, x, y);
	}
	PlayerAttacked[x][y] = '*';



	if (Comboard[x][y] == 'S')
	{
		cout << "You've hit the enemy boat" << endl;
		ComBoard[x][y] = 'H';
		Player++;
		hits++;
		turn = true;
	}

	else 
		{	
			ComBoard[x][y] = ' ';
			miss++;
			turn = false;
		}
		if (Player == maxShip * 8 || Com == maxShip * 8)
			turn = false;
}

void comAttack(int &x, int &y)
{
	//srand(time(NULL));
	x = rand() % col;
	//srand(time(NULL));
	y = rand() % row;
	while (ComAttacked[x][y] == '*')
	{
		//srand(time(NULL));
		x = rand() % col;
		//srand(time(NULL));
		y = rand() % row;
	}
		if (PlayerBoard[x][y] == 'S')
	{
		cout << "You've being hited by the enemy " << endl;
		PlayerBoard[x][y] = 'H';
		Com++;
		turn = true;
	}

	else
	{
		PlayerBoard[x][y] = ' ';
		ComAttacked[x][y] = '*';
		turn = false;
	}
	
	if (Player == maxShip * 8 || Com == maxShip * 8)
		turn = false;	
		
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
	while (Player != maxShip && Com != maxShip)
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
//		if (back != '\0') 
//			return;
		comAttack(Comx, Comy);
	//	cout << Playerx << Playery << Comx << Comy << endl;
			
		showBoard2(Playerx, Playery, Comx, Comy);
		if (Player == maxShip * 8 || Com == maxShip * 8)
			break;
		while (turn == true)
		{
			cout << "You are hited: " << endl;
			Sleep(2000);
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


void gameRule(char & ch)
{
	system("CLS");
	cout << "Battleship : The Game " << endl;
	cout << "~~ Game Rule ~~" << endl;
	cout << "You as a commander is trying to flat out the enemy front line with you ships crew, consist of various ship formations " << endl;
	cout << "(4 ships at a time maximum) with up to 2x4 blocks per ship, in a battleground of 9*9 blocks wide." << endl;
	cout << "Arrange your ship at unexpected locations, note in mind that the enemy has the same ship types as yours." << endl;
	cout << "Fire by input the location as you desire in an exciting turn-based system." << endl;
	cout << "q to back to the menu \n" << endl;
	cin >> choice;
	checkchoice(choice);
	
	while (choice[0] != 'q' && choice[0] != 'Q')
	{
		switch (choice[0])
		{
			
			
			case 'Q':
			case 'q': 
				return;
			default: cout << "Thats is not a choice, please enter again" << endl;
		}
		cin >> choice;
		checkchoice(choice);
	}

	
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


void setLastShipPoint(int &x1, int &y1, int &x2, int &y2)
{
//	srand(time(NULL));	
	x2 = -1;
	y2 = -1;
	int direct;
	while (x2 < 0 || x2 > col - 1 || y2 < 0 || y2 > row - 1 )
	{
		direct = rand() % 8;
		switch(direct)
		{
			case 0: x2 = x1 + 3;
					y2 = y1 + 1;
					break;
			case 1: x2 = x1 + 3;
					y2 = y1 - 1;
					break;
			case 2: x2 = x1 + 1;
					y2 = y1 - 3;
					break;
			case 3: x2 = x1 - 1;
					y2 = y1 - 3;
					break;
			case 4: x2 = x1 - 3;
					y2 = y1 - 1;
					break;
			case 5: x2 = x1 - 3;
					y2 = y1 + 1;
					break;
			case 6: x2 = x1 - 1;
					y2 = y1 + 3;
					break;
			case 7: x2 = x1 + 1;
					y2 = y1 + 3;
					break;
		}
		
	}
	
}
bool checkLastShipPoint(int x1, int y1, int x2, int y2)
{
	int a1 = x1 > x2 ? x2 : x1;
	int a2 = x1 > x2 ? x1 : x2;
	int b1 = y1 > y2 ? y2 : y1;
	int b2 = y1 > y2 ? y1 : y2;
		
	for (int i = b1; i <= b2; i++)
	{
		for (int j = a1; j <= a2; j++)
		{
			if (Comboard[i][j] == 'S') 
				return false;
			else 
				continue;
		}
	}
	
	return true;
}

void convert3(char * ch, int &x1, int &y1)
{
	 	if (ch[0] == 'a' || ch[0] == 'A')  x1 = 0;
 	else if (ch[0] == 'b' || ch[0] == 'B')  x1 = 1;
 	else if (ch[0] == 'c' || ch[0] == 'C')  x1 = 2;
 	else if (ch[0] == 'd' || ch[0] == 'D')  x1 = 3;
 	else if (ch[0] == 'e' || ch[0] == 'E')  x1 = 4;
 	else if (ch[0] == 'f' || ch[0] == 'F')  x1 = 5;
 	else if (ch[0] == 'g' || ch[0] == 'G')  x1 = 6;
 	else if (ch[0] == 'h' || ch[0] == 'H')  x1 = 7;
 	else if (ch[0] == 'i' || ch[0] == 'I')  x1 = 8;
 	else if (ch[0] == 'k' || ch[0] == 'K')  x1 = 9;
 	else if (ch[0] == 'q' || ch[0] == 'Q')  x1 = -2;
 	else x1 = -1;

 	if (ch[1] == '1' && ch[2] == '\0')  y1 = 0;
 	else if (ch[1] == '2' ) y1 = 1;
 	else if (ch[1] == '3' ) y1 = 2;
 	else if (ch[1] == '4' ) y1 = 3;
 	else if (ch[1] == '5' ) y1 = 4;
 	else if (ch[1] == '6' ) y1 = 5;
 	else if (ch[1] == '7' ) y1 = 6;
 	else if (ch[1] == '8' ) y1 = 7;
 	else if (ch[1] == '9' ) y1 = 8;
 	else if (ch[1] == '1' ) y1 = 9;
 	else y1 = -1;
 	
}

int myAbs(int a)
{
	if (a > 0 ) return a;
	else return -a;
}

bool checkCondition(int x1, int y1, int x2, int y2)
{
	if (x1 < 0 || x1 > row || y1 < 0 || y1 > col || x2 < 0 || x2 > row || y2 < 0 || y2 > col || myAbs((x2 - x1) * (y2 - y1)) != 3)
		return false;
	else 
		return true;
}

bool checkLastShipPoint2(int x1, int y1, int x2, int y2)
{
	int a1 = x1 > x2 ? x2 : x1;
	int a2 = x1 > x2 ? x1 : x2;
	int b1 = y1 > y2 ? y2 : y1;
	int b2 = y1 > y2 ? y1 : y2;
		
	for (int i = b1; i <= b2; i++)
	{
		for (int j = a1; j <= a2; j++)
		{
			if (PlayerBoard[i][j] == 'S') 
				return false;
			else 
				continue;
		}
	}
	
	return true;
}



