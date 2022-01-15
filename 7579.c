#include <stdio.h>
#include <stdlib.h>

typedef struct __queue
{
  int max;
  int num;
  int front;
  int rear;
  int* queue;
}Queue;

int initialize(Queue* q, int size)
{
  q->num = q->front = q->rear = 0;

  if((q->queue = calloc(size, sizeof(int))) == NULL)
  {
    q->max = 0;
    return -1;
  }

  q->max = size;
  return 1;
}

int push_back(Queue* q, int X)
{
  if(q->num < q->max)
  {
    if(q->rear == q->max)
      q->rear = 0;

    q->queue[q->rear++] = X;
    q->num++;

    return 1;
  }

  return -1;
}

int pop_front(Queue* q, int* X)
{
  if(q->num > 0)
  {
    if(q->front == q->max)
      q->front = 0;

    *X = q->queue[q->front++];
    q->num--;

    return 1;
  }

  return -1;
}

int M;
int N;
int H;
int tomato[101][101][101];
int tomato_route[101][101][101];
int route_sum = 0;
int min = 0;

void BFS()
{
  Queue q;
  initialize(&q, 3000001);

  for(int i = 1; i < H + 1; i++)
  {
    for(int j = 1; j < N + 1; j++)
    {
      for(int k = 1; k < M + 1; k++)
      {
        if(tomato[i][j][k] == 1 && tomato_route[i][j][k] == 0)
        {
          push_back(&q, i);
          push_back(&q, j);
          push_back(&q, k);
          tomato_route[i][j][k] = 1;
        }
      }
    }
  }

  int z;
  int y;
  int x;

  while(1)
  {
    int num = q.num;
    min++;
    
    if(num == 0)
      break;

    while(num > 0)
    {
      pop_front(&q, &z);
      pop_front(&q, &y);
      pop_front(&q, &x);

      if(z > 1 && tomato[z - 1][y][x] == 0 && tomato_route[z - 1][y][x] == 0)
      {
        push_back(&q, z - 1);
        push_back(&q, y);
        push_back(&q, x);
        route_sum++;
        tomato_route[z - 1][y][x] = 1;
        tomato[z - 1][y][x] = 1;
      }

      if(z < H && tomato[z + 1][y][x] == 0 && tomato_route[z + 1][y][x] == 0)
      {
        push_back(&q, z + 1);
        push_back(&q, y);
        push_back(&q, x);
        route_sum++;
        tomato_route[z + 1][y][x] = 1;
        tomato[z + 1][y][x] = 1;
      }

      if(y > 1 && tomato[z][y - 1][x] == 0 && tomato_route[z][y - 1][x] == 0)
      {
        push_back(&q, z);
        push_back(&q, y - 1);
        push_back(&q, x);
        route_sum++;
        tomato_route[z][y - 1][x] = 1;
        tomato[z][y - 1][x] = 1;
      }

      if(y < N && tomato[z][y + 1][x] == 0 && tomato_route[z][y + 1][x] == 0)
      {
        push_back(&q, z);
        push_back(&q, y + 1);
        push_back(&q, x);
        route_sum++;
        tomato_route[z][y + 1][x] = 1;
        tomato[z][y + 1][x] = 1;
      }

      if(x > 1 && tomato[z][y][x - 1] == 0 && tomato_route[z][y][x - 1] == 0)
      {
        push_back(&q, z);
        push_back(&q, y);
        push_back(&q, x - 1);
        route_sum++;
        tomato_route[z][y][x - 1] = 1;
        tomato[z][y][x - 1] = 1;
      }

      if(x < M && tomato[z][y][x + 1] == 0 && tomato_route[z][y][x + 1] == 0)
      {
        push_back(&q, z);
        push_back(&q, y);
        push_back(&q, x + 1);
        route_sum++;
        tomato_route[z][y][x + 1] = 1;
        tomato[z][y][x + 1] = 1;
      }

      num -= 3;
    }

    if(route_sum == H * N * M)
      break;
  }

  if(q.queue != NULL)
    free(q.queue);
}

int main(void)
{
  scanf("%d %d %d", &M, &N, &H);
  
  int sum = 0;

  for(int i = 1; i < H + 1; i++)
  {
    for(int j = 1; j < N + 1; j++)
    {
      for(int k = 1; k < M + 1; k++)
      {
        scanf("%d", &tomato[i][j][k]);

        if(tomato[i][j][k] != 0)
        {
          sum++;
          route_sum++;
        }

        if(tomato[i][j][k] == -1)
        {
          tomato_route[i][j][k] = 1;
        }
      }
    }
  }

  if(sum == H * N * M)
    printf("%d\n", 0);
  else
  {
    BFS();

    if(route_sum != H * N * M)
      printf("%d\n", -1);
    else
      printf("%d\n", min);
  }

  return 0;
}