//Game Of Life simulation by Kushal Pathak
#include<iostream>
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define pi 3.14159
#define height 49
#define width 105
#define alive 'X'
#define dead ' '
using namespace std;
char present[height][width];
char next[height][width];
int population;

void init(int);//initializes certain matrices with cetrain values
void display();//displays present matrix
void activate_cell(int,int,int,int,float);//takes: position(x,y), rotate-about(h,k), angle(deg) 
void pattern(int,int,int,float);//takes: pattern-number(n), center-of-pattern(h,k), angle(deg)
void evolve();//evolves life to next generation
void birth(int,int);
void die(int,int);
int isAlive(int,int);
void delay(float);//creates time delay
void randomPattern();//initiates a random life pattern
void maximizeWindow();//maximized the console window
void menu();

int main(){
	int i;
	srand(time(0));
	maximizeWindow();
	init(1);//reset present
	menu();
	while(1){
		display();
		cout<<i<<" Generations";
		//delay(0.0001);
		evolve();
		i++;
	}	
	getch();
	return 0;
}
void evolve(){
	int left,right,top,down,n;
	init(2);//reset next
	//population=0;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			n=0;//reset number of alive neighbouring cells
			right=(j+1)%width;left=(j+width-1)%width;
			down=(i+1)%height;top=(i+height-1)%height;
			if(isAlive(left,top)) n++;
			if(isAlive(left,i)) n++;
			if(isAlive(left,down)) n++;
			if(isAlive(j,top)) n++;
			if(isAlive(j,down)) n++;
			if(isAlive(right,top)) n++;
			if(isAlive(right,i)) n++;
			if(isAlive(right,down)) n++;
			if(isAlive(j,i)){
				if(n==2||n==3){
					//population++;
					birth(j,i);
				}
			}else{
				if(n==3){
					//population++;
					birth(j,i);
				}
			}
		}
	}
	init(1);//reset present
	init(3);//update present
}
void birth(int x,int y){
	next[y][x]=alive;
}
void die(int x,int y){
	next[y][x]=dead;
}
int isAlive(int x,int y){
	if(present[y][x]==alive) return 1;
	return 0;
}
void display(){
	system("cls");
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++)
		cout<<present[i][j]<<" ";
		cout<<"\n";
	}
}
void init(int n){
	switch(n){
		case 1://reset present matrix
			for(int i=0;i<height;i++){
				for(int j=0;j<width;j++)
				present[i][j]=dead;
			}
			break;
		case 2://reset next matrix
			for(int i=0;i<height;i++){
				for(int j=0;j<width;j++)
				next[i][j]=dead;
			}
			break;
		case 3://transfer from next to present
			for(int i=0;i<height;i++){
				for(int j=0;j<width;j++)
				present[i][j]=next[i][j];
			}
			break;
	}
}
void delay(float n){
	for(int i=0;i<1000;i++){
		for(int j=0;j<100;j++)
			for(int k=0;k<n*100;k++);
	}
}
void activate_cell(int x,int y,int h,int k,float angle){
	int rotatedX, rotatedY;
	angle=(pi/180)*angle;
	rotatedX=round((x-h)*cos(angle)-(y-k)*sin(angle))+h;
	rotatedY=round((x-h)*sin(angle)+(y-k)*cos(angle))+k;
	
	if(rotatedX>width-1)rotatedX=rotatedX%width;
	if(rotatedX<0)rotatedX=(rotatedX%width)+width;
	if(rotatedY>height-1)rotatedY=rotatedY%height;
	if(rotatedY<0)rotatedY=(rotatedY%height)+height;
	present[rotatedY][rotatedX]=alive;
}

void randomPattern(){
	int n;
	//population=0;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			n=rand()%2;
			if(n==0)present[i][j]=dead;
			else if(n==1){
				//population++;
				present[i][j]=alive;
			}
		}
	}
}
void menu(){
	int n,h,k,a;
	cout<<"GAME OF LIFE BY KUSHAL PATHAK\n";
	cout<<"1-Blinker\n2-Toad\n3-Beacon\n4-Pulsar\n5-Pentadecathlon\n";
	cout<<"6-Block\n7-Beehive\n8-Loaf\n9-Boat\n10-Tub\n";
	cout<<"11-Glider\n12-Light weight spaceship\n13-Middle weight spaceship\n14-Heavy weight spaceship\n";
	cout<<"15-The R-pentomino\n16-Diehard\n17-Acorn\n18-Gosper Glider Gun\n19-Eater\n";
	cout<<"Choose a pattern: ";cin>>n;
	if(n==0) {
		pattern(0,0,0,0);
		return;
	}
	cout<<"Enter position (eg:- 52 24): ";cin>>h;cin>>k;
	cout<<"Enter angle: ";cin>>a;
	pattern(n,h,k,a);
}
void maximizeWindow(){
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}

void pattern(int n,int h,int k, float angle){
	//(h,k) represents center of pattern
	int x,y;
	switch(n){
		case 1://Blinker (period 2)
			activate_cell(h-1,k,h,k,angle);
			activate_cell(h,k,h,k,angle);
			activate_cell(h+1,k,h,k,angle);
			
			break;
		case 2: //Toad (period 2)
			pattern(1,h,k,angle);
			pattern(1,h+1,k+1,angle);
			
			break;
		
		case 3://Beacon (period 2)
			activate_cell(h,k,h,k,angle);
			activate_cell(h-1,k,h,k,angle);
			activate_cell(h-1,k-1,h,k,angle);
			activate_cell(h,k-1,h,k,angle);
			activate_cell(h+1,k+1,h,k,angle);
			activate_cell(h+2,k+1,h,k,angle);
			activate_cell(h+2,k+2,h,k,angle);
			activate_cell(h+1,k+2,h,k,angle);
			
			break;
		case 4://Pulsar (period 3)
			pattern(1,h-3,k-6,0); pattern(1,h+3,k-6,0);
			pattern(1,h-3,k-1,0); pattern(1,h+3,k-1,0);
			pattern(1,h-3,k+1,0); pattern(1,h+3,k+1,0);
			pattern(1,h-3,k+6,0); pattern(1,h+3,k+6,0);
			
			pattern(1,h-6,k-3,90); pattern(1,h-6,k+3,90);
			pattern(1,h-1,k-3,90); pattern(1,h-1,k+3,90);
			pattern(1,h+1,k-3,90); pattern(1,h+1,k+3,90);
			pattern(1,h+6,k-3,90); pattern(1,h+6,k+3,90);
			
			break;
		case 5://pentadecathlon (period 15)
			activate_cell(h,k,h,k,angle);
			activate_cell(h-1,k,h,k,angle);
			activate_cell(h-2,k-1,h,k,angle);
			activate_cell(h-2,k+1,h,k,angle);
			activate_cell(h-3,k,h,k,angle);
			activate_cell(h-4,k,h,k,angle);
			activate_cell(h+1,k,h,k,angle);
			activate_cell(h+2,k,h,k,angle);
			activate_cell(h+3,k-1,h,k,angle);
			activate_cell(h+3,k+1,h,k,angle);
			activate_cell(h+4,k,h,k,angle);
			activate_cell(h+5,k,h,k,angle);
			
			break;
		case 6://Block (still life)
			activate_cell(h,k,h,k,angle);
			activate_cell(h+1,k,h,k,angle);
			activate_cell(h,k+1,h,k,angle);
			activate_cell(h+1,k+1,h,k,angle);
			
			break;
		case 7://Beehive (still life)
			//activate_cell(h,k,h,k,angle);
			activate_cell(h-1,k,h,k,angle);
			activate_cell(h+2,k,h,k,angle);
			activate_cell(h,k-1,h,k,angle);
			activate_cell(h,k+1,h,k,angle);
			activate_cell(h+1,k-1,h,k,angle);
			activate_cell(h+1,k+1,h,k,angle);
			
			break;
		case 8://loaf (still life)
			activate_cell(h-1,k,h,k,angle);
			activate_cell(h,k-1,h,k,angle);
			activate_cell(h+1,k-1,h,k,angle);
			activate_cell(h+2,k,h,k,angle);
			activate_cell(h,k+1,h,k,angle);
			activate_cell(h+2,k+1,h,k,angle);
			activate_cell(h+1,k+2,h,k,angle);
			
			break;
		case 9://boat (still life)
			activate_cell(h-1,k-1,h,k,angle);
			activate_cell(h-1,k,h,k,angle);
			activate_cell(h,k-1,h,k,angle);
			activate_cell(h,k+1,h,k,angle);
			activate_cell(h+1,k,h,k,angle);
			
			break;
		case 10://tub (still life)
			activate_cell(h-1,k,h,k,angle);
			activate_cell(h,k-1,h,k,angle);
			activate_cell(h,k+1,h,k,angle);
			activate_cell(h+1,k,h,k,angle);
			
			break;
		case 11://glider (still life)
			activate_cell(h,k,h,k,angle);
			activate_cell(h-1,k-1,h,k,angle);
			activate_cell(h-1,k+1,h,k,angle);
			activate_cell(h,k+1,h,k,angle);
			activate_cell(h+1,k,h,k,angle);
			
			break;
		case 12://light weight spaceship
			activate_cell(h-1,k-1,h,k,angle);
			activate_cell(h,k-1,h,k,angle);
			activate_cell(h+1,k-1,h,k,angle);
			activate_cell(h+2,k-1,h,k,angle);
			activate_cell(h-2,k,h,k,angle);
			activate_cell(h+2,k,h,k,angle);
			activate_cell(h+2,k+1,h,k,angle);
			activate_cell(h-2,k+2,h,k,angle);
			activate_cell(h+1,k+2,h,k,angle);
			
			break;
		case 13://middle weight spaceship
			activate_cell(h-2,k-1,h,k,angle);
			activate_cell(h-2,k+1,h,k,angle);
			activate_cell(h-1,k-2,h,k,angle);
			activate_cell(h,k-2,h,k,angle);
			activate_cell(h+1,k-2,h,k,angle);
			activate_cell(h+2,k-2,h,k,angle);
			activate_cell(h+3,k-2,h,k,angle);
			activate_cell(h+3,k-2,h,k,angle);
			activate_cell(h+3,k-1,h,k,angle);
			activate_cell(h+3,k,h,k,angle);
			activate_cell(h+2,k+1,h,k,angle);
			activate_cell(h,k+2,h,k,angle);
			
			break;
		case 14://heavy weight spaceship
			activate_cell(h-3,k-1,h,k,angle);
			activate_cell(h-3,k+1,h,k,angle);
			activate_cell(h-2,k-2,h,k,angle);
			activate_cell(h-1,k-2,h,k,angle);
			activate_cell(h,k-2,h,k,angle);
			activate_cell(h+1,k-2,h,k,angle);
			activate_cell(h+2,k-2,h,k,angle);
			activate_cell(h+3,k-2,h,k,angle);
			activate_cell(h+3,k-2,h,k,angle);
			activate_cell(h+3,k-1,h,k,angle);
			activate_cell(h+3,k,h,k,angle);
			activate_cell(h+2,k+1,h,k,angle);
			activate_cell(h,k+2,h,k,angle);
			activate_cell(h-1,k+2,h,k,angle);
			
			break;
		case 15://The R-pentomino
			activate_cell(h,k,h,k,angle);
			activate_cell(h,k-1,h,k,angle);
			activate_cell(h,k+1,h,k,angle);
			activate_cell(h-1,k,h,k,angle);
			activate_cell(h+1,k-1,h,k,angle);
			
			break;
		case 16://Diehard
			activate_cell(h-3,k,h,k,angle);
			activate_cell(h-2,k,h,k,angle);
			activate_cell(h+3,k-1,h,k,angle);
			activate_cell(h-2,k+1,h,k,angle);
			activate_cell(h+2,k+1,h,k,angle);
			activate_cell(h+3,k+1,h,k,angle);
			activate_cell(h+4,k+1,h,k,angle);
			
			break;
		case 17://Acorn
			activate_cell(h,k,h,k,angle);
			activate_cell(h-2,k-1,h,k,angle);
			activate_cell(h-3,k+1,h,k,angle);
			activate_cell(h-2,k+1,h,k,angle);
			activate_cell(h+1,k+1,h,k,angle);
			activate_cell(h+2,k+1,h,k,angle);
			activate_cell(h+3,k+1,h,k,angle);
			break;
		case 18://Gosper Glider Gun
			activate_cell(h,k+1,h,k,angle);
			activate_cell(h-17,k,h,k,angle);
			activate_cell(h-17,k+1,h,k,angle);
			activate_cell(h-16,k,h,k,angle);
			activate_cell(h-16,k+1,h,k,angle);
			activate_cell(h-7,k,h,k,angle);
			activate_cell(h-7,k+1,h,k,angle);
			activate_cell(h-7,k+2,h,k,angle);
			activate_cell(h-6,k-1,h,k,angle);
			activate_cell(h-6,k+3,h,k,angle);
			activate_cell(h-5,k-2,h,k,angle);
			activate_cell(h-5,k+4,h,k,angle);
			activate_cell(h-4,k-2,h,k,angle);
			activate_cell(h-4,k+4,h,k,angle);
			activate_cell(h-3,k+1,h,k,angle);
			activate_cell(h-2,k-1,h,k,angle);
			activate_cell(h-2,k+3,h,k,angle);
			activate_cell(h-1,k,h,k,angle);
			activate_cell(h-1,k+1,h,k,angle);
			activate_cell(h-1,k+2,h,k,angle);
			activate_cell(h+3,k-2,h,k,angle);
			activate_cell(h+3,k-1,h,k,angle);
			activate_cell(h+3,k,h,k,angle);
			activate_cell(h+4,k-2,h,k,angle);
			activate_cell(h+4,k-1,h,k,angle);
			activate_cell(h+4,k,h,k,angle);
			activate_cell(h+5,k-3,h,k,angle);
			activate_cell(h+5,k+1,h,k,angle);
			activate_cell(h+7,k-4,h,k,angle);
			activate_cell(h+7,k-3,h,k,angle);
			activate_cell(h+7,k+1,h,k,angle);
			activate_cell(h+7,k+2,h,k,angle);
			activate_cell(h+17,k-2,h,k,angle);
			activate_cell(h+17,k-1,h,k,angle);
			activate_cell(h+18,k-2,h,k,angle);
			activate_cell(h+18,k-1,h,k,angle);
			
			//pattern(19,h+22,k+21,angle);
			
			activate_cell(h+22,k+21,h,k,angle);
			activate_cell(h+22,k+21+1,h,k,angle);
			activate_cell(h+22+1,k+21,h,k,angle);
			activate_cell(h+22+2,k+21+1,h,k,angle);
			activate_cell(h+22+2,k+21+2,h,k,angle);
			activate_cell(h+22+2,k+21+3,h,k,angle);
			activate_cell(h+22+3,k+21+3,h,k,angle);
			break;
		case 19://Eater
			activate_cell(h,k,h,k,angle);
			activate_cell(h,k+1,h,k,angle);
			activate_cell(h+1,k,h,k,angle);
			activate_cell(h+2,k+1,h,k,angle);
			activate_cell(h+2,k+2,h,k,angle);
			activate_cell(h+2,k+3,h,k,angle);
			activate_cell(h+3,k+3,h,k,angle);
			break;
		case 0://random pattern
			randomPattern();
	}
	
}





