/* 
 * This is a Clock which works in Real Time 
 * Made for the Project in CO222
 * Author - E18118
 * Date of Submission : 05/09/2021
 */

#include<stdio.h>
#include<time.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>
#include<ctype.h>

//For Hiding user inputs when program is running
#define Shide "\
#/bin/bash \n\
stty -echo \n\
"
#define Sshow "\
#/bin/bash \n\
stty echo \n\
"

//Signatures

void getTime(int);

void setColor(int);
void box(int);

void moveDown(int);
void moveUp(int);
void moveRight(int);
void moveLeft(int);

void clearScreen(void);
void curhide(void);
void pos(int,int);
void text_col(int);
void enter_alt(void);
void exit_alt(void);

void one(int);
void two(int);
void three(int);
void four(int);
void five(int); 
void six(int);
void seven(int);
void eight(int);
void nine(int);
void zero(int);

int pickColor(char arr[]);

void numPick(char val,int c);

int main(int argc,char ** argv){
	int c ;//,key;
	system(Shide);

	printf("\x1b[=19");
	curhide();
	c=47;
	char color[10];	
	int i,condition1=0,condition2=0,conditionh=0,condition3=0,condition4=0,condition5=0,conditionh2=0,condition6=0,condition7=0;
	
	if(argc>1){

		if(pickColor(argv[argc-1])==-1)
                        condition2=1; // Does the Last term have a color?

		for(i=1;(i<argc-1);i++){
			if(!strcmp(argv[i],"-c")){
		       		if(pickColor(argv[i+1])==-1){
					condition1=0;
					strcpy(color,argv[i+1]);
					condition4=1; //is there a term after -c
					if((i+1)==argc-1)
						condition5=1;//Is this is the last term?
					if(!strcmp(argv[i+1],"-h") && (i+1)==argc-1)
						conditionh=1;
					i=i+1;
				}
				else{
				condition1=1;//Is there a color after -c?
				i=i+1;
				}
			}
			else if(!strcmp(argv[i],"-h"))
				condition3=1; // is there a -h term independent of -c?

			else if(pickColor(argv[i])==-1){
				if(!strcmp(argv[i+1],"-h")){
					conditionh2=1; // is there a -h after -somevalue?
					i=i+1;
				}
				else if(pickColor(argv[i+1])==-1){
					condition6=1;// is there a pattern like -s -s?
				}
				else
					condition7=1; //is there a color after -s like term?
			}
			
				//i=i+1;
			//	condition8=1; // Is this a color written independently
			
		}  //Error Handling
		
		if(((condition6==0 && conditionh2==0) && (conditionh==0 && condition3==0)&& (condition7==0 && !strcmp(argv[(argc-1)],"-h"))) || (condition3==1&& condition7==0 && conditionh2==0)){
			printf("usage : clock -h                quick help on cmd\n");
			printf("usage : clock -c <color>        print clock with a color\n");
			printf("<color-black|red|green|yellow|blue|magenta|cyan> supported colors\n");
		
		}
		else if((condition2==1 && condition5==0) || conditionh2==1 || condition6==1 || condition7==1){
			printf("Invalid use of arguments.\n");
			printf("usage : clock -h                quick help on cmd\n");
                	printf("usage : clock -c <color>        print clock with a color\n");
		}
		else if((condition3 ==0)&&(condition4==1)&&(condition1==0)){
			printf("%s :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan\n",color);
		}

		else{
			system("clear");
			enter_alt();
			if(strcmp(argv[argc-2],"-c")==0 && argc>1)
				c=pickColor(argv[argc-1]);
			
			while(1){
				getTime(c);
			}
		}
	}	
	else{
		system("clear");
                        enter_alt();

                        while(1){
                                getTime(c);
                        }
	}
	system(Sshow);
	return 0;
		
}

//Getting time and positioning numbers on screen
void getTime(int c){
	 time_t rawTime;
         struct tm * currentTime;
         char sec[100];
         char min[100];
         char hour[100];
         char day[100];
         char mon[100];
         char year[100];

         rawTime=time(NULL);
         currentTime = localtime(&rawTime);
         strftime(sec,100,"%S",currentTime);
         strftime(min,100,"%M",currentTime);
         strftime(hour,100,"%H",currentTime);
         strftime(day,100,"%d",currentTime);
         strftime(mon,100,"%m",currentTime);
         strftime(year,100,"%Y",currentTime);


         //First Digit
         pos(2,2);
         numPick(hour[0],c);
         //Second Digit
         pos(2,9);
         numPick(hour[1],c);

         //Colon
         pos(3,17);
         box(c);
         pos(5,17);
         box(c);
         //Third Digit
         pos(2,21);
         numPick(min[0],c);
         //Forth Digit
         pos(2,28);
         numPick(min[1],c);
         //Colon
         pos(3,36);
         box(c);
         pos(5,36);
         box(c);
         //Fifth digit
         pos(2,40);
         numPick(sec[0],c);
         //Sixth Digit
         pos(2,47);
         numPick(sec[1],c);
	 //D-M-Y
         pos(8,23);
         text_col(0);
         text_col(c-10);
         printf("%s-%s-%s",year,mon,day);


}
//Colouring
void setColor(int c){ //To print a colored 1x1 box
	printf("\x1b[%dm \x1b[%dm",c,c);
}
void box(int c){ //Two create a 1x2 box
	setColor(c);
	setColor(c);
}
void text_col(int c){ //To change color
	printf("\x1b[%dm",c);
} 

//Cursor Operatios
void moveDown(int down){ //Movedown cursor by one step
	printf("\x1b[%dB",down);
}
void moveUp(int up){ //Move up curson by 1 step
	printf("\x1b[%dA",up);
}
void moveRight(int right){ //Move right cursor by 1 step
	printf("\x1b[%dC",right);
}
void moveLeft(int left){ //Move left cursor by one step
	printf("\x1b[%dD",left);
}
void clearScreen(void){ //Clear the whoe screen
	printf("\x1B[2J");
}
void curhide(void){ // Hiding the cursor
	printf("\e[?25l");
}
void pos(int X,int Y){ //To position cursor giving X and Y cordinates
	printf("\x1b[%d;%dH",X,Y);
}
void enter_alt(void){
	printf("\x1b[?1047h");
}
void exit_alt(void){
        printf("\x1b[?1047l");
}

//Numbers
void one(int c){
	int row,col;
	for(row=0;row<5;row++){
		for(col=0;col<3;col++){
			if(col==2)
				box(c);
			else
				box(0);
		}
		moveDown(1);
		moveLeft(6);	
	}
	box(0);
	
}
void two(int c){
	int row,col;
	for(row=0;row<5;row++){
		for(col=0;col<3;col++){
			if(row==0 || row==2 || row==4)
				box(c);
			else if(row==1 && col==2)
				box(c);
			else if(row==3 && col==0)
				box(c);
			else
				box(0);
		}
		moveLeft(6);
		moveDown(1);
		
	}
	box(0);
}
void three(int c){
        int row,col;
        for(row=0;row<5;row++){
                for(col=0;col<3;col++){
                        if(row==0 || row==2 || row==4)
                                box(c);
                        else if((row==1 || row ==3) && col==2)
                                box(c);
			else
				box(0);
                }
                moveLeft(6);
                moveDown(1);

        }
        box(0);
}
void four(int c){
        int row,col;
        for(row=0;row<5;row++){
                for(col=0;col<3;col++){
                        if((row==0 || row==1) && col!=1)
                                box(c);
			else if((row==0 || row==1) && col==1)
				box(0);
                        else if(row==2)
                                box(c);
			else if(col==2)
				box(c);
			else
				box(0);
                }
                moveLeft(6);
                moveDown(1);

        }
        box(0);
}
void five(int c){
        int row,col;
        for(row=0;row<5;row++){
                for(col=0;col<3;col++){
                        if(row==0 || row==2 || row==4)
                                box(c);
                        else if(row==1 && col==0)
                                box(c);
			else if(row==3 && col==2)
				box(c);
			else
				box(0);
                }
                moveLeft(6);
                moveDown(1);

        }
        box(0);
}
void six(int c){
        int row,col;
        for(row=0;row<5;row++){
                for(col=0;col<3;col++){
                        if(row==0 || row==2 || row==4)
                                box(c);
                        else if(row==3 && (col==0||col==2))
                                box(c);
                        else if(row==3 && col==1)
                                box(0);
                        else if(col==0)
                                box(c);
			else
				box(0);
                }
                moveLeft(6);
                moveDown(1);

        }
        box(0);
}
void seven(int c){
        int row,col;
        for(row=0;row<5;row++){
		for(col=0;col<3;col++){
			if(row==0)
				box(c);
			else if(col==2)
				box(c);
			else
				box(0);
			}
		moveLeft(6);
		moveDown(1);
        }
        box(0);

}
void eight(int c){
        int row,col;
        for(row=0;row<5;row++){
                for(col=0;col<3;col++){
                        if(row==0 || row==2 || row==4)
                                box(c);
                        else if(row==3 && (col==0||col==2))
                                box(c);
                        else if(row==3 && col==1)
                                box(0);
                        else if(col==0 || col==2)
                                box(c);
                        else
                                box(0);
                }
                moveLeft(6);
                moveDown(1);

        }
        box(0);
}
void nine(int c){
        int row,col;
        for(row=0;row<5;row++){
                for(col=0;col<3;col++){
                        if(row==0 || row==2 || row==4)
                                box(c);
                        else if(row==3 && col==2)
                                box(c);
                        else if(row==1 && (col==0 || col==2))
                                box(c);
			else 
                                box(0);
                }
                moveLeft(6);
                moveDown(1);

        }
        box(0);
}
void zero(int c){
        int row,col;
        for(row=0;row<5;row++){
                for(col=0;col<3;col++){
                        if(row==0 || row==4)
                                box(c);
                        else if(row==3 && (col==0||col==2))
                                box(c);
                        else if(row==3 && col==1)
                                box(0);
                        else if(col==0 || col==2)
                                box(c);
                        else
                                box(0);
                }
                moveLeft(6);
                moveDown(1);

        }
        box(0);
}
//Function to pick the color according to the user input
int pickColor(char arr[]){
	int i=0;
	char arr2[20];
	for(i=0;arr[i] != '\0';i++){
		arr2[i]=tolower(arr[i]);
	}
	arr2[i]='\0';

	if(strcmp(arr2,"black")==0)
		return 40;
	else if(strcmp(arr2,"red")==0)
		return 41;
	else if(strcmp(arr2,"green")==0)
		return 42;
	else if(strcmp(arr2,"yellow")==0)
		return 43;
	else if(strcmp(arr2,"blue")==0)
		return 44;
	else if(strcmp(arr2,"magenta")==0)
		return 45;
	else if(strcmp(arr2,"cyan")==0)
		return 46;
	else
		return -1;
}
//Function to call the fuctions writted to each numbers according to the input digits
void numPick(char val,int c){
	if(val=='0')
		zero(c);
	else if(val=='1')
		one(c);
	else if(val=='2')
		two(c);
	else if(val=='3')
		three(c);
	else if(val=='4')
		four(c);
	else if(val=='5')
		five(c);
	else if(val=='6')
		six(c);
	else if(val=='7')
		seven(c);
	else if(val=='8')
		eight(c);
	else if(val=='9')
		nine(c);
}

