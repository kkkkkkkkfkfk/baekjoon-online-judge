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
int tomato[1001][1001];
int tomato_route[1001][1001];
int min = 0;
int route_sum = 0;

void BFS()
{
  Queue q;
  initialize(&q, 2000003);

  for(int i = 1; i < N + 1; i++)
  {
    for(int j = 1; j < M + 1; j++)
    {
      if(tomato[i][j] == 1 && tomato_route[i][j] == 0)
      {
        push_back(&q, i);
        push_back(&q, j);
        tomato_route[i][j] = 1;
      }
    }
  }
  
  int x;
  int y;

  while(1)
  {
    int num = q.num;

    min++;

    if(num == 0)
      break;

    while(num > 0)
    {
      pop_front(&q, &x);
      pop_front(&q, &y);
      
      if(tomato[x - 1][y] == 0 && tomato_route[x - 1][y] == 0 && x > 1)
      {
        push_back(&q, x - 1);
        push_back(&q, y);
        tomato_route[x - 1][y] = 1;
        tomato[x - 1][y] = 1;
        route_sum++;
      }

      if(tomato[x][y - 1] == 0 && tomato_route[x][y - 1] == 0 && y > 1)
      {
        push_back(&q, x);
        push_back(&q, y - 1);
        tomato_route[x][y - 1] = 1;
        tomato[x][y - 1] = 1;
        route_sum++;
      }

      if(tomato[x + 1][y] == 0 && tomato_route[x + 1][y] == 0 && x < N)
      {
        push_back(&q, x + 1);
        push_back(&q, y);
        tomato_route[x + 1][y] = 1;
        tomato[x + 1][y] = 1;
        route_sum++;
      }

      if(tomato[x][y + 1] == 0 && tomato_route[x][y + 1] == 0 && y < M)
      {
        push_back(&q, x);
        push_back(&q, y + 1);
        tomato_route[x][y + 1] = 1;
        tomato[x][y + 1] = 1;
        route_sum++;
      }

      num -= 2;
    }

    if(route_sum == N * M)
      break;
  }

  if(q.queue != NULL)
    free(q.queue);
}

int main(void)
{
  scanf("%d %d", &M, &N);
  
  int sum = 0;
  int failed_count = 0;

  for(int i = 1; i < N + 1; i++)
  {
    for(int j = 1; j < M + 1; j++)
    {
      scanf("%d", &tomato[i][j]);
      if(tomato[i][j] != 0)
      {
        sum++;
        route_sum++;  
      }

      if(tomato[i][j] == -1)
      {
        tomato_route[i][j] = -1;
      }
    }
  }

  if(sum == N * M)
    printf("%d\n", 0);
  else
  {
    BFS();

    for(int i = 1; i < N + 1; i++)
    {
      for(int j = 1; j < M + 1; j++)
      {
        if(tomato[i][j] == 0)
        {
          failed_count++;
          goto Top;
        }
      }
    }
    Top:

    if(failed_count > 0)
      printf("%d\n", -1);
    else
      printf("%d\n", min);
  }

  return 0;
}