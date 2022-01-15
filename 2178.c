#include <stdio.h>
#include <stdlib.h>

typedef struct __queue
{
  int max;
  int num;
  int front;
  int rear;
  int *queue;
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

int pop_front(Queue* q, int *X)
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

char num[101];
int graph[102][102];
int BFS_route[102][102];
int min = 0;
int failed_count = 0;

int N;
int M;

void BFS(int start)
{
  Queue q;
  initialize(&q, 8000);

  push_back(&q, start);
  push_back(&q, start);
  BFS_route[start][start] = start;

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
      
      if(x == N && y == M)
      {
        failed_count++;
        break;
      }

      if(graph[x - 1][y] == '1' && BFS_route[x - 1][y] == 0)
      {
        push_back(&q, x - 1);
        push_back(&q, y);
        BFS_route[x - 1][y] = 1;
      }

      if(graph[x][y - 1] == '1' && BFS_route[x][y - 1] == 0)
      {
        push_back(&q, x);
        push_back(&q, y - 1);
        BFS_route[x][y - 1] = 1;
      }

      if(graph[x + 1][y] == '1' && BFS_route[x + 1][y] == 0)
      {
        push_back(&q, x + 1);
        push_back(&q, y);
        BFS_route[x + 1][y] = 1;
      }

      if(graph[x][y + 1] == '1' && BFS_route[x][y + 1] == 0)
      {
        push_back(&q, x);
        push_back(&q, y + 1);
        BFS_route[x][y + 1] = 1;
      }
      
      num -= 2;
    }

    if(failed_count > 0)
      break;
  }

  if(q.queue != NULL)
    free(q.queue);
}

int main(void)
{
  scanf("%d %d", &N, &M);
  
  for(int i = 1; i < N + 1; i++)
  {
    scanf("%s", num);
    for(int j = 1; j < M + 1; j++)
    {
      graph[i][j] = num[j - 1];
    }
  }

  BFS(1);

  printf("%d\n", min);

  return 0;
}