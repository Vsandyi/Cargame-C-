#include<iostream>
#include<conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];

char car[4][4] = {
        ' ','.','.',' ',
        '0','±','±','0',
        ' ','±','±',' ',
        '0','±','±','0',
                    };

char enemyDesigns[3][5][4] = {
    {

        '0','±','±','0',
        ' ','±','±',' ',
        '0','±','±','0',
        ' ','-','-',' ',
    },
    {
        '0','±','±','0',
        ' ','±','±',' ',
        '0','±','±','0',
        ' ','^','^',' ',
    },
    {
        '0','±','±','0',
        ' ','±','±',' ',
        '0','±','±','0',
        ' ','=','=',' ',
    },
};

int carPos = 37;
int carPosY = 23;
int score = 0;
int lives = 3;
int difficulty = 1;

bool checkCollisionWithOtherEnemies(int ind, int newX, int newY) {
    for (int i = 0; i < ind; i++) {
        if (enemyFlag[i] && newX < enemyX[i] + 4 && newX + 4 > enemyX[i] && newY < enemyY[i] + 4 && newY + 4 > enemyY[i]) {
            return true;
        }
    }
    return false;
}

void setDifficultySpeed(int& speed) {
    switch (difficulty) {
    case 1:
        speed = 1;
        break;
    case 2:
        speed = 2;
        break;
    case 3:
        speed = 3;
        break;
    case 4:
        speed = 4;
        break;
    }
}

void setTextColor(int color) {
    SetConsoleTextAttribute(console, color);
}

void resetTextColor() {
    SetConsoleTextAttribute(console, 15);
}

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder() {
   setTextColor(14);
    for (int i = 0; i < 30; i++) {
        char b = 206;
        gotoxy(0, i);
        cout << b;

    }
    resetTextColor();

    int gap = 3;
    setTextColor(15);
    for (int i = 0; i < 30; i++) {
        if (i % gap == 0) {
            gotoxy(30, i);
            cout << "|";
        }
    }
    resetTextColor();

    setTextColor(15);
    for (int i = 0; i < 30; i++) {
        if (i % gap == 0) {
            gotoxy(49, i);
            cout << "|";
        }
    }
    resetTextColor();

    setTextColor(15);
    for (int i = 0; i < 30; i++) {
        if (i % gap == 0) {
            gotoxy(10, i);
            cout << "|";
        }
    }
    resetTextColor();
    setTextColor(10);

    for (int i = 0; i < 30; i++) {
        char a = 186;
         char b = 206;
         setTextColor(14);
        gotoxy(19, i);
        cout << a;
        setTextColor(14);
        gotoxy(39, i);
        cout << a;
          setTextColor(14);
        gotoxy(59, i);
        cout << b;
    }
    resetTextColor();
}

void genEnemy(int ind) {
    int newX, newY;

    do {
        newX = 1 + rand() % 58;
        newY = 1;
    } while (newX < 4 || newX > 54 || checkCollisionWithOtherEnemies(ind, newX, newY));

    enemyX[ind] = newX;
    enemyY[ind] = newY;
}

void drawEnemy(int ind) {
    if (enemyFlag[ind]) {
        setTextColor(04);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                gotoxy(enemyX[ind] + j, enemyY[ind] + i);
                cout << enemyDesigns[ind][i][j];
            }
        }
        resetTextColor();
    }
}


void eraseEnemy(int ind) {
    if (enemyFlag[ind] == true) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                gotoxy(enemyX[ind] + j, enemyY[ind] + i);
                cout << " ";
            }
        }
    }
}

void resetEnemy(int ind) {
    eraseEnemy(ind);
    genEnemy(ind);
}

void drawCar() {
    setTextColor(06);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carPos, i + carPosY);
            cout << car[i][j];
        }
    }
    resetTextColor();
}

void eraseCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carPos, i + carPosY);
            cout << " ";
        }
    }
}

int collision() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (carPosY + i >= enemyY[0] && carPosY + i < enemyY[0] + 4 &&
                carPos + j >= enemyX[0] && carPos + j < enemyX[0] + 4 &&
                car[i][j] != ' ') {
                return 1;
            }
        }
    }

    for (int k = 1; k < 3; k++) {
        if (enemyFlag[k]) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (carPosY + i >= enemyY[k] && carPosY + i < enemyY[k] + 4 &&
                        carPos + j >= enemyX[k] && carPos + j < enemyX[k] + 4 &&
                        car[i][j] != ' ') {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

void gameover() {

    system("cls");
  system("color 04");     gotoxy(15, 12);
    cout<<"       ::::::::     :::       :::   :::    ::::::::::           ::::::::  :::     ::: :::::::::: ::::::::: "<<endl;
    gotoxy(15, 13);
    cout<<"     :+:    :+:  :+: :+:    :+:+: :+:+:   :+:                 :+:    :+: :+:     :+: :+:        :+:    :+: "<<endl;
     gotoxy(15, 14);
    cout<<"    +:+         +:+   +:+  +:+ +:+:+ +:+ +:+                 +:+    +:+ +:+     +:+ +:+        +:+    +:+  "<<endl;
      gotoxy(15, 15);
    cout<<"   :#:        +#++:++#++: +#+  +:+  +#+ +#++:++#            +#+    +:+ +#+     +:+ +#++:++#   +#++:++#:    "<<endl;
    gotoxy(15, 16);
    cout<<"  +#+   +#+# +#+     +#+ +#+       +#+ +#+                 +#+    +#+  +#+   +#+  +#+        +#+    +#+    "<<endl;
     gotoxy(15, 17);
    cout<<" #+#    #+# #+#     #+# #+#       #+# #+#                 #+#    #+#   #+#+#+#   #+#        #+#    #+#     "<<endl;
    gotoxy(15, 18);
    cout<<" ########  ###     ### ###       ### ##########           ########      ###     ########## ###    ###      "<<endl;


gotoxy(3, 3);cout<<"  .oooooo.       .o.     ooooooooo. oooooo     ooooooooooooooooooooo      ooooooooooooooooooooo     oooooooooooo.  oooooooooooo "<<endl;
gotoxy(3, 4);cout<<" d8P'  `Y8b     .888.    `888   `Y88.`888.     .8' `888'     `8`888b.     `8'8'   888   `8`888'     `8'`888   `Y88.`888'     `8 "<<endl;
gotoxy(3, 5);cout<<"888            .8 888.    888   .d88' `888.   .8'   888         8 `88b.    8      888      888       8  888    d88' 888         "<<endl;
gotoxy(3, 6);cout<<"888           .8' `888.   888ooo88P'   `888. .8'    888oooo8    8   `88b.  8      888      888       8  888ooo88P'  888oooo8    "<<endl;
gotoxy(3, 7);cout<<"888          .88ooo8888.  888`88b.      `888.8'     888         8     `88b 8      888      888       8  888`88b.    888         "<<endl;
gotoxy(3, 8);cout<<"`88b    ooo .8'     `888. 888  `88b.     `888'      888       o 8       `888      888      `88.    .8'  888  `88b   888       o "<<endl;
gotoxy(3, 9);cout<<" `Y8bood8P'o88o     o8888oo888o  o888o    `8'      o888ooooood8o8o        `8     o888o       `YbodP'   o888o  o888oo888ooooood8 "<<endl;




 system("color 4A");     gotoxy(15, 23);
    cout << "Your total score is: " << score;
    gotoxy(15, 24);
    getch();
}

void updateScore() {
    gotoxy(89, 7);
   setTextColor(2); cout << "Score:    " << score <<' ';
}
void updateLives() {
    gotoxy(89,8);
   setTextColor(2); cout << "Lives:    " << lives << ' ';
}
void displayDifficultyPopup(){

    gotoxy(35, 12);
    cout <<"Difficulty Inreased!";
    Sleep(1000);
    system("cls");
}

void instructions() {
    system("cls");
     char a = 187;
    char b = 188;
    char c = 200;
    char d = 201;
    char e = 205;
    char f = 186;
 setTextColor(06); gotoxy(50, 11);     cout << d << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << a<<endl;
   setTextColor(06); gotoxy(50, 12);   cout << f << " \t \t \t  \t \t     " << f <<  endl;
   setTextColor(06); gotoxy(50, 13);   cout << f << "     "  << "           Instructions"<< " \t     " << f <<endl;
   setTextColor(06); gotoxy(50, 14);   cout << f << " " <<  "            ----------------"<< " \t     " << f <<  endl;
  setTextColor(06); gotoxy(50, 15);    cout << f << " " << "  Avoid Cars by moving left or right.  " << "  " << f << endl;
  setTextColor(06); gotoxy(50, 16);    cout << f << "  " << " Press 'a' to move left" << "\t \t     " << f << endl;
  setTextColor(06); gotoxy(50, 17);    cout << f << "  " << " Press 'd' to move rigt"<< "\t \t     " << f << endl;
   setTextColor(06); gotoxy(50, 18);   cout << f << "  " << " Press 'escape' to exit"<< "\t \t     " << f << endl;
   setTextColor(06); gotoxy(50, 19);   cout << f << "  " << " Press any key to go back to the menu"<< "   "  << f <<endl;
   setTextColor(06); gotoxy(50, 20);   cout << c  << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << e << b<<endl;


    getch();
}

void loadingBar() {
  char a = 47;
   char b = 92;
   char c = 95;
   char d = 179;
   char e = 41;
   char f = 46;
   char g = 205;
   char i = 206;
   char h = 186 ;
   char m = 235;
   char n = 248;
   char o = 219;
 setTextColor(06);    gotoxy(55,9);    cout << "              " << c << c << c << c << c << c << c << c<< c << c << endl;
 setTextColor(06); gotoxy(55, 10);  cout << "             " << a << "" << a << "    " << d << "" << d << " " << b << " " << b <<endl;
setTextColor(06); gotoxy(55, 11);  cout << "      " << c << c << c << c << c << c << a << "" << a << c << c << c << c << c << d << "" << d << c << c << b << " " << b<< c<< c << c <<endl;
 setTextColor(06);gotoxy(55, 12);  cout << "      "<< e  << "  "<< c << c << "      "<< n << "      " << c << c <<"   " << b <<endl;
setTextColor(06);gotoxy(55, 13);  cout << "      " << d << c << a << "  " << b<<  c << c << c << c<<  c << c << c << c << c <<  c << c <<a << "  " << b << c << c << d << endl;
 setTextColor(06); gotoxy(55, 14); cout << "        " << b << c << c << a << "           " << b << c << c <<a <<endl;
   gotoxy(50,15); cout << "Loading: ";
    for (int i = 0; i <30; ++i) {
      cout << o;
      Sleep(100);
    }

      cout << "100%"<<endl;
    gotoxy(63,17); cout << "Loading Complete."<<endl;

    Sleep(1000);
}



void play() {
   carPos = 37;
    carPosY = 23;
    score = 0;
    lives = 3;


   system("cls");
   loadingBar();
    system("cls");
   char a = 47;
   char b = 92;
   char c = 95;
   char d = 179;
   char e = 41;
   char f = 46;
   char g = 205;
   char i = 206;
   char h = 186 ;// |
   char m = 215;
   char n = 248;
   char o = 178;
    int numEnemies = 3;
    int enemyTimers[3] = {0};

    for (int i = 0; i < numEnemies; i++) {
        enemyFlag[i] = 1;
        genEnemy(i);
    }

    system("cls");
    drawBorder();

    while (lives > 0) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 'a' || ch == 'A') {
                if (carPos > 2)
                    carPos -= 3;
            }
            if (ch == 'd' || ch == 'D') {
                if (carPos < 54)
                    carPos += 3;
            }
             if (ch == ' ' || ch == ' ') {
                gotoxy(85, 26 ); system("pause");
            if (ch == 27) {
                break;
            }
        }
        }
        drawCar();
        for (int i = 0; i < numEnemies; i++) {
            drawEnemy(i);
            if (collision() == 1) {
                lives--;
                updateLives();
                eraseCar();

                Sleep(1);

                if (lives == 0) {
                    gameover();
                    return;
                } else {
                    carPos = 37;
                }
            }
        }

       Sleep(30);
        eraseCar();
        for (int i = 0; i < numEnemies; i++) {
            eraseEnemy(i);
        }

        for (int i = 0; i < numEnemies; i++) {

            enemyY[i] += 1 * difficulty;

            if (enemyY[i] == 10 && enemyFlag[i] == 0) {
                enemyFlag[i] = 1;
                genEnemy(i);
                enemyTimers[i] = rand() % 50 + 10;
            }

            if (enemyTimers[i] > 0) {
                enemyTimers[i]--;
            }


            if (enemyTimers[i] == 0) {
                resetEnemy(i);
                enemyTimers[i] = rand() % 50 + 10;
            }

            if (enemyY[i] > 25) {
                resetEnemy(i);
                score++;
                updateScore();

              if (score >= 20 && score < 50 && difficulty == 1) {
            difficulty = 2;
           displayDifficultyPopup();

        } else if (score >= 50 && difficulty == 2) {
            difficulty = 3;
            displayDifficultyPopup();

        }
        else if (score >= 100 && difficulty == 3) {
            difficulty = 4;
            displayDifficultyPopup();

        }
            }
        }

        drawBorder();
 setTextColor(06);    gotoxy(80,12);    cout << "              " << c << c << c << c << c << c << c << c<< c << c << endl;
 setTextColor(06); gotoxy(80, 13);  cout << "             " << a << "" << a << "    " << d << "" << d << " " << b << " " << b <<endl;
setTextColor(06); gotoxy(80, 14);  cout << "      " << c << c << c << c << c << c << a << "" << a << c << c << c << c << c << d << "" << d << c << c << b << " " << b<< c<< c << c <<endl;
 setTextColor(06);gotoxy(80, 15);  cout << "      "<< e  << "  "<< c << c << "      "<< n << "      " << c << c <<"   " << b <<endl;
setTextColor(06);gotoxy(80, 16);  cout << "      " << d << c << a << "  " << b<<  c << c << c << c<<  c << c << c << c << c <<  c << c <<a << "  " << b << c << c << d << endl;
 setTextColor(06); gotoxy(80, 17); cout << "        " << b << c << c << a << "           " << b << c << c <<a <<endl;
 setTextColor(06); gotoxy(80, 18); cout << g << g << g<< g << g << g<< g << g << g<< g << g << g<< g << g << g<< g << g << g<< g << g << g<< g << g << g<< g << g << g<< g << g << g<< g << g << g<< g << g << g;
   cout<<endl;
   cout<<endl;
    cout<<endl;
 setTextColor(04);   gotoxy(71,19);cout << "  " << c << c << c << c << c << "           " << c << c << c << c << c<<"     "<< c << c << c<< c << c <<"           " << c << c << "  " << c << c<<" " << c << c << c<<c<<c <<"     ";
 setTextColor(04);  gotoxy(71, 20); cout << " " << a << " " << c << c<< c<< c <<d << "    " << a << b << "   "<< d << "  " << c << c << " " << b << "   " <<a << " "  << c << c << c << c <<d << "    " << a << b << "   " << d << "  " << b << a << "  " << d << "  " << c << c << c << d << "     ";
 setTextColor(06); gotoxy(71, 21);  cout << d << " " << d << "        " << a << "  " << b << "  " << d << " " << d << c << c << e << " " << d  << " "<< d << " "<< d <<"  " << c << c << "    " << a << "  " << b << "  " << d << " "<< b << "  " << a << " " << d << " " << d << c << c << "     ";
 setTextColor(06);  gotoxy(71, 22); cout << d << " " << d << "       " << a <<" "<< a << b<<" "<< b << " " << d << "  "  << c << "  " << a << "  " << d << " " << d<< " " << d << c << " " << d  << "  " << a << " " << a<< b<< " " << b << " "<< d << " " << d << b << a  << d << " " << d << "  " << c << c << d << "     ";
 setTextColor(01); gotoxy(71, 23);  cout <<d << " " << d << c<< c<< c << c << "  " << a << " " << c  << c << c << c << " " << b << d << " " << d << " " << b << " " << b << "  " << d << " " <<  d << c << c <<d << " " << d << " " << a << " " << c << c << c << c << " " << b << d << " " << d << "  "<< d << " " << d  << " " << d << c << c << c <<"     ";
 setTextColor(01);  gotoxy(71, 24); cout <<b << c << c << c<< c << c << c << d << a << c <<a << "    " << b << c << b << c << d  << "  "<< b << c <<b << " "<< d   << c << c << c  << c << c <<c << d << a << c << a<< "    "  << b << c << b << c <<d << "  "<< d << c << d << c << c << c << c << c << d <<"     ";
setTextColor(01);  gotoxy(67, 26 );  cout << o <<  o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o  << o << o << o  << o << o << o  << o << o << o  << o << o << o  << o << o << o  << o << o << o  << o << o << o  << o << o << o  << o << o << o << o << o << o << o << o << o << o << o <<endl;
setTextColor(04);       gotoxy(62, 11); cout << " " << " " << " " << " " << " " << " " << " " << " "<< " " << " " << " " << " " << " " << m << " " << " "<< " " << " " << " " <<endl;
setTextColor(04);  gotoxy(62, 12); cout << " " << " " << " " << m << " " << " " << " " << " "<< m << " " << " " << " " << m << " " << " " << " "<< " " << " " << m<<endl;
setTextColor(04);  gotoxy(62, 13); cout << " " << " " << " " << " " << m << " "<< " " << m<< m << " " << " " << m << m << " " << " " << " "<< " " << m << m<<endl;
 setTextColor(04);gotoxy(62, 14); cout << m << " " << " " << " " << m << m << m << m<< m << m << " " << m << m << " " << " " << " "<< m << m << m<<endl;
setTextColor(04);gotoxy(62, 15); cout << " " << m << m << " " << " " << " " << m << m<< m << m << m << m << m << m << " " << m<< m << m << m<<endl;
setTextColor(04);  gotoxy(62, 16); cout << " " << " " << " " << m << m << m << m << m<< m << m << m << m << m << m << m << m<< m << " " << " "<<endl;
setTextColor(04); gotoxy(62, 17); cout << " " << " " << " " << " " << m << m << m << m<< m << m << m << m << m << m << m << " "<< " " << " " << " "<<endl;
 setTextColor(04); gotoxy(62, 18); cout << " "<< " " << " " << " " <<" "<< " " << " " << m<< m << m << m << m << m << " " << " " << " "<< " " << " " << " "<<endl;



  setTextColor(04);  gotoxy(114, 11); cout << " " << " " << " " << " " << " " << " " << " " << " "<< " " << " " << " " << " " << " " << m << " " << " "<< " " << " " << " " <<endl;
 setTextColor(04); gotoxy(114, 12); cout << " " << " " << " " << m << " " << " " << " " << " "<< m << " " << " " << " " << m << " " << " " << " "<< " " << " " << m<<endl;
 setTextColor(04); gotoxy(114, 13); cout << " " << " " << " " << " " << m << " "<< " " << m<< m << " " << " " << m << m << " " << " " << " "<< " " << m << m<<endl;
setTextColor(04);gotoxy(114, 14); cout << m << " " << " " << " " << m << m << m << m<< m << m << " " << m << m << " " << " " << " "<< m << m << m<<endl;
setTextColor(04);gotoxy(114, 15); cout << " " << m << m << " " << " " << " " << m << m<< m << m << m << m << m << m << " " << m<< m << m << m<<endl;
 setTextColor(04); gotoxy(114, 16); cout << " " << " " << " " << m << m << m << m << m<< m << m << m << m << m << m << m << m<< m << " " << " "<<endl;
setTextColor(04); gotoxy(114, 17); cout << " " << " " << " " << " " << m << m << m << m<< m << m << m << m << m << m << m << " "<< " " << " " << " "<<endl;
 setTextColor(04); gotoxy(114, 18); cout << " "<< " " << " " << " " <<" "<< " " << " " << m<< m << m << m << m << m << " " << " " << " "<< " " << " " << " "<<endl;
    }
}


int main() {

    setcursor(0, 0);
    srand((unsigned)time(NULL));
    system("pause");

     char a = 47;
   char b = 92;
   char c = 95;
   char d = 179;
   char e = 41;
   char f = 46;
   char g = 205;
   char i = 206;
   char h = 186 ;
   char m = 215;
    char n = 248;

   setTextColor(04);       gotoxy(108, 3); cout << " " << " " << " " << " " << " " << " " << " " << " "<< " " << " " << " " << " " << " " << m << " " << " "<< " " << " " << " " <<endl;
setTextColor(04);  gotoxy(108,4); cout << " " << " " << " " << m << " " << " " << " " << " "<< m << " " << " " << " " << m << " " << " " << " "<< " " << " " << m<<endl;
setTextColor(04);  gotoxy(108, 5); cout << " " << " " << " " << " " << m << " "<< " " << m<< m << " " << " " << m << m << " " << " " << " "<< " " << m << m<<endl;
 setTextColor(04);gotoxy(108, 6); cout << m << " " << " " << " " << m << m << m << m<< m << m << " " << m << m << " " << " " << " "<< m << m << m<<endl;
setTextColor(04);gotoxy(108, 7); cout << " " << m << m << " " << " " << " " << m << m<< m << m << m << m << m << m << " " << m<< m << m << m<<endl;
setTextColor(04);  gotoxy(108, 8); cout << " " << " " << " " << m << m << m << m << m<< m << m << m << m << m << m << m << m<< m << " " << " "<<endl;
setTextColor(04); gotoxy(108, 9); cout << " " << " " << " " << " " << m << m << m << m<< m << m << m << m << m << m << m << " "<< " " << " " << " "<<endl;
 setTextColor(04); gotoxy(108, 10); cout << " "<< " " << " " << " " <<" "<< " " << " " << m<< m << m << m << m << m << " " << " " << " "<< " " << " " << " "<<endl;

 setTextColor(04);   gotoxy(10,3); cout << " " << " " << " " << " " << " " << " " << " " << " "<< " " << " " << " " << " " << " " << m << " " << " "<< " " << " " << " " <<endl;
setTextColor(04);  gotoxy(10, 4); cout << " " << " " << " " << m << " " << " " << " " << " "<< m << " " << " " << " " << m << " " << " " << " "<< " " << " " << m<<endl;
setTextColor(04);  gotoxy(10, 5); cout << " " << " " << " " << " " << m << " "<< " " << m<< m << " " << " " << m << m << " " << " " << " "<< " " << m << m<<endl;
 setTextColor(04);gotoxy(10, 6); cout << m << " " << " " << " " << m << m << m << m<< m << m << " " << m << m << " " << " " << " "<< m << m << m<<endl;
setTextColor(04);gotoxy(10, 7); cout << " " << m << m << " " << " " << " " << m << m<< m << m << m << m << m << m << " " << m<< m << m << m<<endl;
setTextColor(04);  gotoxy(10, 8); cout << " " << " " << " " << m << m << m << m << m<< m << m << m << m << m << m << m << m<< m << " " << " "<<endl;
setTextColor(04); gotoxy(10, 9); cout << " " << " " << " " << " " << m << m << m << m<< m << m << m << m << m << m << m << " "<< " " << " " << " "<<endl;
 setTextColor(04); gotoxy(10, 10); cout << " "<< " " << " " << " " <<" "<< " " << " " << m<< m << m << m << m << m << " " << " " << " "<< " " << " " << " "<<endl;



 setTextColor(06);    gotoxy(85,21);    cout << "              " << c << c << c << c << c << c << c << c<< c << c << endl;
 setTextColor(06); gotoxy(85, 22);  cout << "             " << a << "" << a << "    " << d << "" << d << " " << b << " " << b <<endl;
setTextColor(06); gotoxy(85, 23);  cout << "      " << c << c << c << c << c << c << a << "" << a << c << c << c << c << c << d << "" << d << c << c << b << " " << b<< c<< c << c <<endl;
 setTextColor(06);gotoxy(85, 24);  cout << "      "<< e  << "  "<< c << c << "      "<< n << "      " << c << c <<"   " << b <<endl;
setTextColor(06);gotoxy(85, 25);  cout << "      " << d << c << a << "  " << b<<  c << c << c << c<<  c << c << c << c << c <<  c << c <<a << "  " << b << c << c << d << endl;
 setTextColor(06); gotoxy(85, 26); cout << "        " << b << c << c << a << "           " << b << c << c <<a <<endl;

 gotoxy(17, 8); setTextColor(04);   cout << m << " " << " "<< " " << " "<< " "<< " "<< " "<< " " << m << " " << " " << "                                                                                "<< " " << " " << " " << " " << m << " " << " " << " " << " " << " " << " " << " " << " " << m << endl;
 gotoxy(17, 9);  setTextColor(04);  cout << m << m << " "<< m << " "<< " "<< " "<< " "<< " " << m<<m<< " " << " " <<"                                                                               "<< " " << " " << " " << m << m << " " << " " << " " << " " << " " << m << " " << m << m << endl;
 gotoxy(17, 10);  setTextColor(04); cout << " " << m << m<< m << m<< m<< " "<< " "<< " " << m << m << m<< " " <<"                                                                               "<< " " << " " << m << m << m << " " << " " << " " << m << m << m << m << m << " " <<endl;
 gotoxy(17, 11);  setTextColor(04); cout<< " " << " " << " "<< " " << " "<< m<< m<< m<< m << m << m<< m << m << " "<< i << g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g << g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g << i << " " << m << m << m << m << m << m << m << " " << " " << " " << " " << " " << " " <<endl;
 gotoxy(17, 12); setTextColor(06);  cout<< " "<< " " << " "<< m << " "<< " "<< " "<< m<< m << m << m << m << m << m << h <<"   "<< c << c<< c << c<< c<<"           "<< c<< c<< c<< c<< c<< c<< c << "      "<< c<< c<< c<< c<< c<< c<< c<< c<<" "<< c<<"   "<<c <<" "<< c<< c<< c<< c<< c<< c<< c<< " "<< c << "    "<< c << " "<< c<< c<< c<< c<< c<< "  "<< c<< c<< c<< c<< c<< "  "<< h<< m << m << m << m << m << m << m << " " << " " << " " << m << " " << " " << " " <<endl;
 gotoxy(17, 13); setTextColor(06);  cout<< " " << " " << " "<< m << m<< " "<< " "<< " "<< m << m << m << m << m << m << h<< "  "<< a <<" "<< c << c << c << c<< d << "    " << a << b <<"   " << d << "  " << c << c  << " " << b <<" " << b << "    "<< a << " "<< a << "  "<<c << c <<c << c << d << " " << b << " " << d << " " <<d << c << c << "   "<< c << c <<d << " " << d << "  " << d << " "<<d << "  "<< c << c<<" " << b<< d <<"  "<< c << c<< c <<d << " "<<  h << m << m << m << m << m << m << " " << " " << " " << m<< m << " " << " " << " " <<endl;
 gotoxy(17, 14);  setTextColor(06); cout<< " "<<" " << " "<< m << m<< m<< " "<< " "<< " " << m << m << m << m << m << h << " "<<d << " " << d <<"        "<<a << "  " << b <<"  "<< d<<" " << d << c << c << e << " "<< b<< " " << b<< "  " << "" << a << " " <<a << "" << d << " " << d<<  c << c << "  "<< d << "  " << b << d << " " << d << "  " << d << " " << d << "  "<< d << " "<< d << "  " << d << " " << d  << " " << d<< c << c <<e  << " "<< d << " "<< d << c << c<< "   "<< h << m << m << m << m << m << " " << " " << " " << m << m << m << " " << " " << " " << endl;
 gotoxy(17, 15); setTextColor(06);  cout<< " " << " " << " "<< " " << m<< m<< m<< " "<< " " << m << m << m << m << m << h<< " "<<d << " " << d <<"       " <<a << " " << a << b<< " "<< b  << " "<< d<< "  " << c << "  "<< a << " " << b << " " << b <<""<<a << " " <<a <<" " << d << "  "<< c << c << d << " " << d << " "<<f << "   "<< d << "  " << d <<" " << d << "  "<<d   << " " << d << "  " << d<< " " <<d <<"  "<< c << "  "<<a <<d <<  "  "<< c << c <<d <<"  " <<h<< m << m << m << m << m << " " << " " << m << m << m << " " << " " << " " << " " <<endl;
 gotoxy(17, 16); setTextColor(01);  cout<< " " << " " << " "<< " " << " "<< m<< m<< m<< " " << m << m << m << m << m << h<< " "<<d << " " << d  << c << c << c << c <<"  "<< a <<" " << c << c << c << c <<" " << b << d << " " << d << " " << b << " " << b << "  " << b << "  " << a << "  "<< d << " "<<d << c << c<< c <<c <<d << " " << d << b << "  " << d << "  " << d << " " <<d  << "  " << d << " " << d << c << c<< d << " " << d << " " << d << " " << b << " " << b << d << " " << d << c << c<< c << "  "<< h << m << m << m << m << m << " " << m << m << m <<" " << " " << " " << " " << " " <<  endl;
 gotoxy(17, 17); setTextColor(01); cout<< " " <<" " << " "<< " " << " "<< " "<< " "<< m<< m << m << m << m << m << m<< h << "  " << b<< c << c << c  << c << c  << d << a << " " <<a << "    " << b <<c << b << c << d << "  "<< b << " " << b << "  "<<b << a << "   "<< d << c << c << c<< c<< c << c << d << " " << d << " "<< b <<c << d << "  " << d << " "<< d << "  " << b << c << c << c << c << c<< a << d << c << d << "  " << b << c << d << c << c << c << c << c <<d <<" "<< h << m << m << m << m << m << m << m << " " << " " <<" " << " " << " " << " " << " " <<endl;
 gotoxy(17, 18); setTextColor(01); cout<< " " <<" " << " "<< " " << " "<< " "<< " "<< " "<< m << m << m << m << m << m<< h <<"                                                                            " << h<< m << m << m << m << m << m << " " << " " << " " << " " << " " << " " << " " << " " << endl;
 gotoxy(17, 19); setTextColor(01);  cout<< " " << " " <<" "<< " " << " "<< " "<< " "<< " "<< " " << " " << " " << m << m << m<< i << g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g << g<< g << g<< g << g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g<< g << g << i << m << m << m << " " << " " << " " << " " << " " << " " << " " << " "<< " " << " " << " " <<endl;


    do {

         cout << endl;
    gotoxy(60, 22); setTextColor(2);   cout << "1. Start Game" << endl;
    gotoxy(60, 23); setTextColor(2);   cout << "2. Instructions" << endl;
    gotoxy(60,24);  setTextColor(2);   cout << "3. Quit" << endl;
    gotoxy(60, 25); setTextColor(2);   cout << "Select option: ";

        char op = getche();

        if (op == '1') {
            play();
        } else if (op == '2') {
            instructions();
        } else if (op == '3') {
            exit(0);
        }

    } while (1);

    return 0;
}
