#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include <windows.h>
using namespace std; 
void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}
struct note{
	int x;
	int y;
};
int main(){
	struct note bfs[81];
	int mapp[9][9]={0} , next[8][2]={{1, 0}, {0, 1}, {-1, 0}, {0, -1}, { 1, 1}, { -1, 1}, { 1, -1}, { -1, -1}};
	int bomb=0, i, j, ii=0, x, y, ex = 3, ey = 0, dir, o = 10, head, tail, box[9][9], bx, by, flag = 0, gx, gy ,en = 0;
	char temp, fomap[9][9];
	for( i=0; i<9; i++)
		for( j=0; j<9; j++)
			box[i][j] = 0;
	for( i=0; i<10; i++){
		ii+=7;
		srand(time (0)+ii);
		x = rand() % 81;
		y = x % 9;
		x = x / 9;
		if( mapp[x][y] == -1 || (x == 0 && y == 0)){
			i--;
			continue;
		}
		mapp[x][y] = -1;
	} 
	for( i=0; i<9; i++){
		for( j=0;j<9; j++){
			if( mapp[j][i] == -1){
				for( int r=0; r<8; r++){
					x = next[r][0] + j;
					y = next[r][1] + i;
					if( x < 0 || y < 0 || x >8 || y > 8)
						continue;
					if( mapp[x][y] != -1)
						mapp[x][y]++;
				}
			}
		}
	}
	gotoxy( 0, 0);
	bomb = 0;
	int space = 0;
	gx = 3;
	gy = 0;
	for( i=0; i<9; i++){
		for( j=0; j<9; j++){
			cout<<"   #";
			fomap[j][i] = '#';
		}
		cout<<endl;
	}
	gotoxy( gx, gy);
	cout<<"/";
	temp = '#';
	do{
		gotoxy( 3, 11);
		cout<<" left "<< o<<" flags"<<endl<<endl<<" Enter == click  ,space == stand flag  ,0 == flag , * and Q == player"; 
		dir = getch();
        switch(dir){
        	case 13:
        		if( mapp[en][gy] == -1){
        			bomb =1;
        			gotoxy(3, 15);
        			cout<< "you lose"<<endl;
					continue;	
				}
        		if( mapp[en][gy] >0){
        			box[en][gy] = 1;
        			space++;
        			fomap[en][gy] = mapp[en][gy] + 48;
        			gotoxy(gx, gy);
        			cout<<"/";
        			gotoxy( 3, 15);
					cout<<"  / == "<<mapp[en][gy];
        			temp = fomap[en][gy];
        			continue;
				}
				tail = 1;
				head = 1;
				bfs[tail].x = en;
				bfs[tail].y = gy;
				box[en][gy] = 1;
				fomap[en][gy] = '.';
				tail++;
				while( head < tail){
					for( i=0; i<8; i++){
						bx = bfs[head].x + next[i][0];
						by = bfs[head].y + next[i][1];
						if( bx < 0 || by < 0 || bx >8 || by > 8)
							continue;
						if( mapp[bx][by] == 0 && box[bx][by] == 0){
							if( fomap[bx][by] == 'Q' || fomap[bx][by] == '0')
								o++;
							box [bx][by] = 1;
							bfs[tail].x = bx;
							bfs[tail].y = by;
							gotoxy( ( bx + 1) * 4 -1, by);
							fomap[bx][by] = '.';
							cout<<".";
							tail++;
							space++;
						}
						if( mapp[bx][by] > 0 && box[bx][by] == 0){
							if( fomap[bx][by] == 'Q' || fomap[bx][by] == '0')
								o++;
							box [bx][by] = 1; 
							gotoxy( ( bx + 1) * 4 -1, by);
							fomap[bx][by] = mapp[bx][by] + 48; 
							cout<<	fomap[bx][by];
							space++;
						}
					}
					head++;
				}
				gotoxy( ( en + 1) * 4 -1, gy);
				cout<<"/";
				temp = '.';
        		continue;
        	case 32:
        		if( o > 0 && fomap[en][gy] == '#' ){
        			fomap[en][gy] = '0';
        			o--;
        			gotoxy(gx, gy);
        			cout<<"Q";
        			if( mapp[en][gy] == -1)
        				flag++;
        			temp = '0';
				}
				else if( fomap[en][gy] == '0'){
					fomap[en][gy] = '#';
					gotoxy(gx, gy);
        			cout<<"/";
					o++;
					temp = '#';
					}	
        		continue;
            case 224:
                dir = getch();
                switch(dir){
                    case 75:    
						gx -= 4;
                        break;
                    case 77:     
						gx += 4;
                        break;
                    case 72:    
						gy--;
                        break;
                    case 80:    
						gy++;
                        break;
                }
    		}
    		if( gx < 0 || gy < 0 || gx >35 || gy > 8 || dir <72 || dir>80){
				gx = ex;
				gy = ey;
				continue;
			}
			gotoxy( gx, gy);
			cout<<"/";
			en = (gx -1 )/ 4;
			gotoxy( ex, ey);
			cout<<temp;
			gotoxy( 3, 15);
			temp = fomap[ en][ gy];
			if( temp > '0' && temp <= '9')
				cout<<"  / == "<<temp;
			else
				cout<<"                      ";
			ex = gx;
			ey = gy;
	} while ( space != 71 && bomb != 1 && flag != 10);
	if( space == 71 || flag == 10){
		gotoxy(3, 15);
		cout<<" you win!!!";
	}
	else{
		for( i=0; i<9; i++){
			for( j=0; j<9; j++){
				if( mapp[j][i] == -1){
					gotoxy( ( j + 1) * 4 -1, i);
					cout<<"@";
				}
			}
		}
	}
	gotoxy( 3,16);
	return 0;
}
