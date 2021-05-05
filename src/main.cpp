#include <graphics.h>
#include <stdio.h>
#include <math.h>
#define cellSize 10
typedef enum {LEFT,RIGHT,UP,DOWN} dir_t;

typedef struct
{
    int x;
    int y;
} snakeCoord_t;

typedef struct
{
    int     winX;
    int     winY;
    int     snakeLength;
    int     snakeCellSize;
    dir_t   snakeDir;
    int     snakeColor;
    int     foodColor;
    int     snakeBckColor;
    int     level, score, menuColor;
    snakeCoord_t snake[1000];
}snake_t;

typedef struct{
	int foodX;
	int foodY;
	int radius;
	int foodColor;
} food_t;



/*Kullanýlcak fonksiyonlar*/
void drawRectangle(int, int, int, int);
void drawCircle(int, int, int );
void drawSnake(snake_t*, int);//pointers takes "*"
void drawFood(food_t*);
void initSnake(snake_t*);
void initGame(snake_t*, snake_t*, food_t*);
void moveSnake(snake_t*);
int snakeHitsWall(snake_t*);
void gameOver(snake_t*);
void pause();
int snakeEatsFood(snake_t*,food_t*);
void yemekOlustur(snake_t*, food_t*);
void playGame(snake_t*, food_t*); //main'i eklemeye gerek yok.
void menu(snake_t*, food_t* ,int);
void outtextxy(int,int,char*);

void drawRectangle(int x0, int y0, int x1, int y1)
{
   rectangle(x0,y0,x1,y1);
}

void drawCircle(int x0, int y0, int x1)
{
   circle(x0,y0,x1);
}

void drawSnake(snake_t *mySnake, int color)
{
    int i;
    setcolor(color);
    for(i=0;i<mySnake->snakeLength;i++)
    {
        drawRectangle(mySnake->snake[i].x,mySnake->snake[i].y,mySnake->snake[i].x+mySnake->snakeCellSize,mySnake->snake[i].y+mySnake->snakeCellSize);
    }
   
}

void drawFood(food_t *food){
	
    int i;
    setcolor(food->foodColor);
    drawCircle(food->foodX,food->foodY,food->radius);
}



void initSnake(snake_t *mySnake)
{
    int i;
    mySnake->snakeColor = 15;
    mySnake->foodColor = 3;	
    mySnake->menuColor = 5;
    mySnake->snakeLength = 5;
    mySnake->snakeCellSize = 5;
    mySnake->snakeBckColor = 0;
    mySnake->snakeDir = LEFT;
    for(i=0;i<mySnake->snakeLength;i++)
    {
        mySnake->snake[i].x = 375 + (i*mySnake->snakeCellSize);
        mySnake->snake[i].y = 150;
    }


};



void menu(snake_t *s,food_t *food,int color){
	char c;

	while(1){

    drawRectangle(250,100,500,130);
    outtextxy(300, 110, "Easy for press e"); 

    drawRectangle(250,140,500,170);
    outtextxy(300, 150, "Medium for press m"); 

    drawRectangle(250,180,500,210);
    outtextxy(300, 190, "Hard for press h"); 
    
    drawRectangle(250,220,500,250);
    outtextxy(300, 230, "Help for press 1"); 
    
    drawRectangle(250,260,500,290);
    outtextxy(280, 270, "Quit Game for press ESC");
    
         if (kbhit())
            {
                c = getch();
                switch(c)
                {

                case 'e':
                case 'E':
                	s -> level = 1;
                	cleardevice();
                	playGame(s, food);
                    break;
                case 'm':
                case 'M':
                	s -> level = 2;
                	cleardevice();
                	playGame(s, food);
                    break;
                case 'h':
                case 'H':
                	s -> level = 3;
                	cleardevice();
                	playGame(s, food);
                    break;
                case 49: //ESC's ASCII code is 27
                   outtextxy(160, 20, "Hi, gamer! If you need help please send an e-mail to me."); 
                   outtextxy(250, 40, "zzeynepaltiparmak@gmail.com"); //I did'n use new line command. I prefer that.
                   break;
                
                case 27: //ESC's ASCII code is 27
                   gameOver(s);
                   break;
                }
            }
	}
            
}

void initGame(snake_t *sn,snake_t *s, food_t *food)
{
    sn->winX = 800;
    sn->winY = 600;
    s->level = 0;
    initwindow(sn->winX, sn->winY);
	cleardevice();
	menu(s,food,sn->menuColor);
	

}

void moveSnake(snake_t *s)
{
    int i;
    for(i=s->snakeLength;i>0;i--)
    {
        s->snake[i].x = s->snake[i-1].x;
        s->snake[i].y = s->snake[i-1].y;
    }
    switch(s->snakeDir)
    {
    case LEFT:	 
        s->snake[0].x -= s->snakeCellSize;
        break;
    case RIGHT:
        s->snake[0].x += s->snakeCellSize;
        break;
    case UP:
        s->snake[0].y -= s->snakeCellSize;
        break;
    case DOWN:
        s->snake[0].y += s->snakeCellSize;
        break;

    }

}

int snakeHitsWall(snake_t *s)
{
    if(s->snake[0].x>s->winX || s->snake[0].x<0 || s->snake[0].y>s->winY || s->snake[0].y<0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int snakeHitsTail(snake_t *s)
{
	int i;
	for(int i =1; i<=s->snakeLength; i++){
		 if(s->snake[0].x == s->snake[i].x && s->snake[0].y == s->snake[i].y)
    {
        return 1;
    }
    
}
           return 0;

}


void gameOver(snake_t *s)
{
	
	cleardevice();
	outtextxy(350, 230, "GAME OVER"); 
    printf("GAME OVER\n");
    char arr[50];
    sprintf(arr, "Your Score: %d", s->score );
    outtextxy(0, 550, arr); 
    printf("Score : %d\n",s->score);

    //file islemleri
    FILE *highscore = fopen("highscore.txt", "a"); //append
    fprintf(highscore,"%d\n", s->score);
    fclose(highscore);
    
    int highScore = s->score;
    
    highscore = fopen("highscore.txt", "r");//read

    while(!feof(highscore)){
     int file_score;
     fscanf(highscore, "%d", &file_score);
	 if(file_score>= highScore){
	 	highScore = file_score;
	 }
	}
	
    fclose(highscore);

    char array[50];
    sprintf(array, "High Score: %d", highScore );
    outtextxy(0, 530, array); 
    printf("Your Score : %d\n",highScore);
    system("PAUSE");
    exit(1);
}




int snakeEatsFood(snake_t *s,food_t *food){
	int dist = sqrt(pow((double)(s->snake[0].x - food->foodX),2.0) + pow((double)(s->snake[0].y - food->foodY),2.0));
	if(dist < 12){
		return 1;	
	}
	else{
		return 0;
	}
}

void yemekOlustur(snake_t *s, food_t *food){
	//random food position
    food->foodX  = rand() % 700;
	food->foodY = rand() % 500;
	food->radius = 3;
	food->foodColor = 15; 
	drawFood(food);
}

void playGame(snake_t *s, food_t *food)
{
    char c;
    s->score =0;
    initSnake(s);  
    yemekOlustur(s,food);
    drawFood(food);

    while(1)

        { 
            if(snakeHitsWall(s))
            {
                gameOver(s);
            }
            
            if(snakeHitsTail(s))
            {
                gameOver(s);
            }
       
            if (kbhit())
            {
                c = getch();
                switch(c)
                {

                case 'a':
                case 'A':
                    s->snakeDir = LEFT;
                    break;
                case 'd':
                case 'D':
                    s->snakeDir = RIGHT;
                    break;
                case 'w':
                case 'W':
                    s->snakeDir = UP;
                    break;
                case 's':
                case 'S':
                    s->snakeDir = DOWN;
                    break;
                case 27: //ESC's ASCII code is 27
                   gameOver(s);
                   break;
                
                }
            }
            else
            {
                drawSnake(s,s->snakeBckColor);
                moveSnake(s);
                drawSnake(s,s->snakeColor);
            }
            if(s->level == 1){
               delay(100);if(snakeEatsFood(s,food)){
			      	food->foodColor = 0;
			      	drawFood(food);
			      	yemekOlustur(s,food);
			      	s->snakeLength++;
			        s->score += 1;
			        char arr[50];
			        sprintf(arr, "score: %d", s->score );
		            outtextxy(0, 550, arr); 

			        printf("Score : %d\n",s->score);
		        }
			}
			else if(s->level == 2){
               delay(70);
               if(snakeEatsFood(s,food)){
			      	food->foodColor = 0;
			      	drawFood(food);
			      	yemekOlustur(s,food);
			      	s->snakeLength++;
			        s->score += 5;
			        char arr[50];
			        sprintf(arr, "score: %d", s->score );
		            outtextxy(0, 550, arr); 

			        printf("Score : %d\n",s->score);
		        }
			}
			else if(s->level == 3){
               delay(40);
               if(snakeEatsFood(s,food)){
			      	food->foodColor = 0;
			      	drawFood(food);
			      	yemekOlustur(s,food);
			      	s->snakeLength++;
			        s->score += 10;
			        char arr[50];
			        sprintf(arr, "score: %d", s->score );
		            outtextxy(0, 550, arr); 

			        printf("Score : %d\n",s->score);

		        }
             
			}
    }
}


main(int argc, char *argv[])
{
    snake_t snake;
	food_t food;
	
    initGame(&snake,&snake, &food);
    playGame(&snake, &food);

}
