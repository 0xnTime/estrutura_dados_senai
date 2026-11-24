#include <stdlib.h>
#include "structure.h"
#include "requisition.h"

struct Node
{
    Requisition* req;
    struct Node* next;
};

struct Structure
{
    int curr_size;
    Node* front;
    Node* rear;
};

Node* create_node(Requisition* new_request)
{
    Node* node = (Node*)malloc(sizeof(Node));
	if(node == NULL ) 
	{
		return NULL;
	}
    node->req = new_request;
    node->next = NULL;
    return node;
}

Structure* create_structure(void)
{
    Structure* s = (Structure*)malloc(sizeof(Structure));
	if(s == NULL) 
	{
		return NULL;
	}
    s->front = NULL;
    s->rear = NULL;
    s->curr_size= 0;
    return s;
}

int add(Structure *s, Requisition* new_request)
{
	if(s == NULL) 
	{
		return 1;
	}
	if(new_request == NULL) 
	{
		return 1;
	}

    Node* node = create_node(new_request);

	if(node == NULL) 
	{
		return 1;
	}

    if(is_empty(s)) {
        s->front = node;
        s->rear  = node;
    } else 
	{
		s->rear->next = node;
		s->rear = node;
	}

    s->curr_size++;

	return 0; 
}

Requisition* removal(Structure *s)
{
    if(s == NULL)
    {
        return NULL;
    }

	if(is_empty(s))
	{
		return NULL;
	}

    Node* tmp = s->front;
    Requisition* popped = tmp->req;
    s->front = s->front->next;

    if(s->front == NULL)
    {
        s->rear = NULL;
    }

    free(tmp);

    s->curr_size--;
    return popped;
}

int get_size(Structure *s)
{
	if(s == NULL)
	{
		return -1;
	}
    return s->curr_size;
}

void free_structure(Structure* s)
{
	if(s == NULL) {
		return;
	}
	Node* tmp;

	while(s->front != NULL) {
		tmp = s->front;
		s->front = tmp->next;
		free(tmp->req);
		free(tmp);
	}
	free(s);
}

int is_empty(Structure* s) 
{
	return s->curr_size == 0;
}
