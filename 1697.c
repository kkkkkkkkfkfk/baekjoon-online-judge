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

int N;
int K;
int subin_route[100001];
int min = 0;

void BFS()
{
  Queue q;
  initialize(&q, 100001);

  push_back(&q, N);
  subin_route[N] = 1;
  
  int X;

  while(1)
  {
    int num = q.num;

    if(num == 0)
      break;

    while(num > 0)
    {
      pop_front(&q, &X);
      
      if(X == K)
        goto Top;

      if(X > 0 && subin_route[X - 1] == 0)
      {
        push_back(&q, X - 1);
        subin_route[X - 1] = 1;
      }

      if(X < 100000 && subin_route[X + 1] == 0)
      {
        push_back(&q, X + 1);
        subin_route[X + 1] = 1;
      }

      if(X < 50001 && subin_route[X * 2] == 0)
      {
        push_back(&q, X * 2);
        subin_route[X * 2] = 1;
      }

      num -= 1;
    }

    min++;
  }
  Top:

  if(q.queue != NULL)
    free(q.queue);
}

int main(void)
{
  scanf("%d %d", &N, &K);

  if(N == K)
    printf("%d\n", 0);
  else
  {
    BFS();
    printf("%d\n", min);
  }

  return 0;
}