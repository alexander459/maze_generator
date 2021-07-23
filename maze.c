#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

struct maze{
  char** grid;
  int rows;
  int columns;
};

typedef struct maze* maze_T;

maze_T init_maze(int rows, int columns);
void print_maze(maze_T maze);
void create_maze(maze_T maze, int po_r, int po_c);
int* check_moves(maze_T maze, int po_r, int po_c);
int can_move(int* moves);

int main(){
  maze_T maze;
  int rows, columns;
  srand(time(0));
  printf("IDEAL DIMENSIONS FOR A MAXIMIZED TERMINAL: ~37, ~71\n");
  printf("give number of rows\n");
  scanf("%d", &rows);
  printf("give number of columns\n");
  scanf("%d", &columns);

  /*initialize the maze*/
  maze=init_maze(rows, columns);
  /*create a random maze*/
  create_maze(maze, 1, 1);    /*start digging from position 1,1*/
  /*print the maze*/
  print_maze(maze);
  return 0;
}

/*takes a maze grid and a current position and creates a random maze*/
void create_maze(maze_T maze, int po_r, int po_c){
  int *moves, index;
  
  /*fill the moves array qwith the available moves*/
  moves=check_moves(maze, po_r, po_c);
  
  if(!can_move(moves)){                /*there are no available moves, free the array and return*/
    free(moves);
    return;
  }else{
    do{                                /*choose a valid random direction to dig*/
      index=rand()%4;
    }while(moves[index]==0);
    
    switch(index){
    case 0:                            /*move up*/
      maze->grid[po_r-1][po_c]=' ';
      maze->grid[po_r-2][po_c]=' ';
      po_r=po_r-2;
      break;
    case 1:                            /*move right*/
      maze->grid[po_r][po_c+1]=' ';
      maze->grid[po_r][po_c+2]=' ';
      po_c=po_c+2;
      break;
    case 2:                            /*move down*/
      maze->grid[po_r+1][po_c]=' ';
      maze->grid[po_r+2][po_c]=' ';
      po_r=po_r+2;
    break;
    case 3:                            /*move left*/
      maze->grid[po_r][po_c-1]=' ';
      maze->grid[po_r][po_c-2]=' ';
      po_c=po_c-2;
      break;
    }
  }
  create_maze(maze, po_r, po_c);
  create_maze(maze, po_r, po_c);
}

/*takes a maze and a current position in it and returns an array with the available moves
  moves[0]->can go up
  moves[1]->can go right
  moves[2]->can go down
  moves[3]->can go left*/
int* check_moves(maze_T maze, int po_r, int po_c){
  int *moves=(int*)malloc(4*sizeof(int));
  assert(moves!=NULL);
  moves[0]=0;
  moves[1]=0;
  moves[2]=0;
  moves[3]=0;
  
  /*find the available directions (if they exist)*/
  /*check if can go up*/
  if(po_r-2>0){                              /*there is no wall to this direction. We must NOT dig a wall*/
    if(maze->grid[po_r-1][po_c]=='X')        /*the block above is X*/
      if(maze->grid[po_r-2][po_c]=='X')      /*the 2nd block above is X too*/
	moves[0]=1;                           /*so you can go up*/
  }
  /*check if can go right*/
  if(po_c+2<maze->columns-1){                /*there is no wall to this direction. We must NOT dig a wall*/
    if(maze->grid[po_r][po_c+1]=='X')        /*the block on the right is X*/
      if(maze->grid[po_r][po_c+2]=='X')      /*the second block on the right is X too*/
	moves[1]=1;                           /*so you can go right*/
  }
  /*check if can go down*/
  if(po_r+2<maze->rows-1){                   /*the is no wall to this direction. We must NOT dig a wall*/
    if(maze->grid[po_r+1][po_c]=='X')        /*the block below is X*/
      if(maze->grid[po_r+2][po_c]=='X')      /*the second block below is X too*/
	moves[2]=1;                           /*can go down*/
  }
  /*check if can go left*/
  if(po_c-2>0){                              /*there is no wall to this direction. We must NOT dig a wall*/
    if(maze->grid[po_r][po_c-1]=='X')        /*the block on the left is X*/
      if(maze->grid[po_r][po_c-2]=='X')      /*the second block on the left is X too*/
	moves[3]=1;                           /*so you can go left*/
  }
  return moves;
}

/*takes an array with the available moves
  returns 1 if there is at least one available move
  returns 0 if there are no available moves*/
int can_move(int* moves){
  if(moves[0]+moves[1]+moves[2]+moves[3]==0)
    return 0;
  return 1;
}

/*creates a maze and initializes the grid with X*/
maze_T init_maze(int rows, int columns){
  int i, j;
  maze_T new_maze;
  new_maze=(maze_T)malloc(sizeof(struct maze));
  assert(new_maze!=NULL);
  
  new_maze->grid=(char**)malloc(sizeof(char*)*rows);
  assert(new_maze->grid!=NULL);
  
  for(i=0; i<rows; i++){
    new_maze->grid[i]=(char*)malloc(columns);
    assert(new_maze->grid[i]!=NULL);
  }
  
  for(i=0; i<rows; i++)
    for(j=0; j<columns; j++)
      new_maze->grid[i][j]='X';
  new_maze->grid[0][1]=' ';
  new_maze->grid[1][1]=' ';
  new_maze->rows=rows;
  new_maze->columns=columns;
  return new_maze;
}

/*prints the grid of the maze*/
void print_maze(maze_T maze){
  int i, j;
  assert(maze!=NULL);
  for(i=0; i<maze->rows; i++){
    for(j=0; j<maze->columns; j++)
      printf("%c ", maze->grid[i][j]);
    printf("\n");
  }
  return;
}
