#ifndef REQUISITION_H
#define REQUISITION_H

typedef struct Requisition Requisition;

Requisition* create_requisition(char* name, int registration, char* procedure);

char*        get_name(Requisition* req);
int          get_registration(Requisition* req);
char*	     get_procedure(Requisition* req);

#endif
