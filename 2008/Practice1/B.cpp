#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define GRID_ADD 10


const char mazeChars[] = "0123456789abcdef";

char path1[11000], path2[11000];

// direction: 0-north, 1-south, 2-west, 3-east
int gridX, gridY, width, height, x, y, direction;



int diff[][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

int * grid;



int turn(int dir, char where) {
  switch (dir) {
  case 0:
    return where == 'R' ? 3 : 2;
  case 1:
    return where == 'R' ? 2 : 3;
  case 2:
    return where == 'R' ? 0 : 1;
  case 3:
    return where == 'R' ? 1 : 0;
  }
}


void extendGrid(int newGridX, int newGridY, int newWidth, int newHeight) {
  int * newGrid = new int[newWidth * newHeight];
  memset(newGrid, 0, newWidth * newHeight * sizeof(int));
  
  for(int j=0;j<height;j++) {
    memcpy(newGrid + (gridX - newGridX) + (gridY - newGridY + j) * newWidth,
      grid + j * width, width * sizeof(int));
  }
  
  delete [] grid;
  grid = newGrid;  
  gridX = newGridX;
  gridY = newGridY;
  width = newWidth;
  height = newHeight;
}

void setWall(int nx, int ny, int direction) {
  if (nx < gridX) extendGrid(gridX - GRID_ADD, gridY, width + GRID_ADD, height);
  if (nx >= gridX + width) extendGrid(gridX, gridY, width + GRID_ADD, height);
  if (ny < gridY) extendGrid(gridX, gridY - GRID_ADD, width, height + GRID_ADD);
  if (ny >= gridY + height) extendGrid(gridX, gridY, width, height + GRID_ADD);
  
  grid[nx - gridX + (ny - gridY) * width] |= (1 << direction);
}

void processPath(char * path) {
  int length = strlen(path);
  char turned = 0;
  
  // ignore the first step, it just enters the maze
  for(int i=1;i<length;i++) {
    switch (path[i]) {
    case 'W':
      // if not turned, then there is a wall on the left
      if (!turned) {
        int leftDirection = turn(direction, 'L');
        setWall(x, y, leftDirection);
        setWall(x + diff[leftDirection][0], y + diff[leftDirection][1], turn(direction, 'R'));
      } else
        turned = 0;
        
      x += diff[direction][0];
      y += diff[direction][1];
      break;
    
    case 'L':
      // turn left, we don't know anything
      direction = turn(direction, 'L');
      turned = 1;
      break;
    
    case 'R':
      // turn right - set the wall on the left and in front
      int leftDirection = turn(direction, 'L');
      setWall(x, y, leftDirection);
      setWall(x + diff[leftDirection][0], y + diff[leftDirection][1], turn(direction, 'R'));
      
      // and in front
      setWall(x, y, direction);
      setWall(x + diff[direction][0], y + diff[direction][1], turn(leftDirection, 'L'));
             
      direction = turn(direction, 'R');
      turned = 1;
    }
  }
}



void printResult() {
  int startY = 0, startX = 0, endY = height - 1, endX = width - 1;

  // remove empty fields
  for(int i=0;i<height;i++) {
    char empty = 1;
    for(int j=0;j<width;j++) {
      if ((grid[j + i * width] & (~2)) != 0) {
         empty = 0;
         startY = i;
         break;
      }
    }
    if (!empty) break;
  }
  
  for(int i=height-1;i>=0;i--) {
    char empty = 1;
    for(int j=0;j<width;j++) {
      if ((grid[j + i * width] & (~1)) != 0) {
         endY = i;
         empty = 0;
         break;
      }
    }
    if (!empty) break;
  }
  
  for(int j=0;j<width;j++) {
    char empty = 1;
    for(int i=0;i<height;i++) {
      if ((grid[j + i * width] & (~8)) != 0) {
         empty = 0;
         startX = j;
         break;
      }
    }
    if (!empty) break;
  }      
  
  for(int j=width-1;j>=0;j--) {
    char empty = 1;
    for(int i=0;i<height;i++) {
      if ((grid[j + i * width] & (~4)) != 0) {
         empty = 0;
         endX = j;
         break;
      }
    }
    if (!empty) break;
  }      
  
  for(int i=startY;i<=endY;i++) {
    for(int j=startX;j<=endX;j++)
      printf("%c", mazeChars[grid[j + i * width]^15]);
    printf("\n");
  }
}
     

int main(void) {
  int cases;
  scanf("%d", &cases);
  
  for(int c=0;c<cases;c++) {
    scanf("%s %s", path1, path2);
    gridX = gridY = x = y = 0;
    width = height = 1;
    direction = 1;
    grid = new int[1];
    
    processPath(path1);
    
    // now turn back
    direction = turn(direction, 'R');
    direction = turn(direction, 'R');
    
    // make one step
    x += diff[direction][0];
    y += diff[direction][1];
    
    // and go back    
    processPath(path2);
    
    // and print the maze
    printf("Case #%d:\n", c + 1);
    printResult();
    delete [] grid;
  }
}
