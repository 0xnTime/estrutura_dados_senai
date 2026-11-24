#include <stdlib.h>
#include <string.h>

#include "requisition.h"

#define MAX_NAME 40
#define MAX_PROC 10

struct Requisition
{
    int registration;
    char name[MAX_NAME + 1 ];
    char procedure[MAX_PROC + 1];
};

Requisition* create_requisition(char* name, int registration, char* procedure)
{
	if(name == NULL || procedure == NULL) {
		return NULL;
	}

    Requisition* req = (Requisition*)malloc(sizeof(Requisition));

	if(req == NULL) {
		return NULL;
	}

	strncpy(req->name, name, MAX_NAME);
	req->name[MAX_NAME] = '\0';

	strncpy(req->procedure, procedure, MAX_PROC);
	req->procedure[MAX_PROC] = '\0';

	req->registration = registration;

    return req;
}

char* get_name(Requisition* req)
{
	if(req == NULL)
	{
		return NULL;
	}
	return req->name;
}

int get_registration(Requisition* req)
{
	if(req == NULL)
	{
		return -1;
	}
	return req->registration;
}

char* get_procedure(Requisition* req)
{
	if(req == NULL)
	{
		return NULL;
	}
	return req->procedure;
}
