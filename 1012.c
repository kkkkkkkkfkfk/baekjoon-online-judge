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

int graph[52][52];
int BFS_route[52][52];
int worm = 0;

void BFS(int start, int M)
{
  Queue q;
  initialize(&q, 2000);
  
  int count = 0;

  for(int i = 1; i < M + 1; i++)
  {
    if(graph[start][i] == 1 && BFS_route[start][i] == 0)
    {
      push_back(&q, start);
      push_back(&q, i);
      BFS_route[start][i] = 1;
      count++;
      break;
    }
  }

  int x;
  int y;

  while(q.num > 0)
  {
    pop_front(&q, &x);
    pop_front(&q, &y);

    if(graph[x - 1][y] == 1 && BFS_route[x - 1][y] == 0)
    {
      push_back(&q, x - 1);
      push_back(&q, y);
      BFS_route[x - 1][y] = 1;
    }

    if(graph[x][y - 1] == 1 && BFS_route[x][y - 1] == 0)
    {
      push_back(&q, x);
      push_back(&q, y - 1);
      BFS_route[x][y - 1] = 1;
    }

    if(graph[x + 1][y] == 1 && BFS_route[x + 1][y] == 0)
    {
      push_back(&q, x + 1);
      push_back(&q, y);
      BFS_route[x + 1][y] = 1;
    }

    if(graph[x][y + 1] == 1 && BFS_route[x][y + 1] == 0)
    {
      push_back(&q, x);
      push_back(&q, y + 1);
      BFS_route[x][y + 1] = 1;
    }
  }

  if(count > 0)
    worm++;

  if(q.queue != NULL)
    free(q.queue);
}

int main(void)
{
  int T;
  scanf("%d", &T);

  while(T > 0)
  {
    int M;
    int N;
    int K;
    
    int x;
    int y;

    scanf("%d %d %d", &M, &N, &K);

    for(int i = 0; i < K; i++)
    {
      scanf("%d %d", &x, &y);
      graph[y + 1][x + 1] = 1;
    }
    
    for(int j = 1; j < N + 1; j++)
    {
      for(int i = 0; i < M / 2 + 1; i++)
      {
        BFS(j, M);
      }
    }

    printf("%d\n", worm);

    for(int i = 1; i < N + 1; i++)
    {
      for(int j = 1; j < M + 1; j++)
      {
        graph[i][j] = 0;
        BFS_route[i][j] = 0;
      }
    }
    
    worm = 0;

    T--;
  }

  return 0;
}