#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}DequeType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}

int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}

int is_full(DequeType* q)
{
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}


element get_front(DequeType* q)
{
	if (is_empty(q))
	{
		error("큐가 공백상태입니다.");
	}
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("큐가 포화상태입니다.");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}

element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	return q->data[q->rear];
}


void deque_print(DequeType* q)
{
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

int main(void)
{


	while (1)
	{
		char str[100];
		char tmp[100];
		printf("Enter a string(or input 'exit') : ");
		DequeType q;

		gets_s(str, 100);
		strcpy_s(tmp, strlen(str) + 1, str);
		init_deque(&q);
		if (!strcmp(str, "exit"))
		{
			exit(1);
		}
		for (int i = 0; i <= strlen(str); i++)
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
			{
				str[i] = str[i] + 32;
				add_rear(&q, str[i]);
			}
			else if (str[i] >= 'a' && str[i] <= 'z')
			{
				add_rear(&q, str[i]);
			}
		}

		for (int i = 0; i < strlen(str); i++)
		{
			if (get_front(&q) == get_rear(&q))
			{
				delete_rear(&q);
				delete_front(&q);
			}

			if (get_front(&q) != get_rear(&q))
			{
				printf("%s is not a palidrome.\n", tmp);
				break;
			}
			else
			{
				printf("%s is a palidrome\n", tmp);
				break;
			}

		}
	}
}