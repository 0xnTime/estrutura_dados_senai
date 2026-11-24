#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "requisition.h"

typedef struct Structure Structure;
typedef struct Node Node;

Node* 		 create_node(Requisition* new_request);
Structure*   create_structure(void);

int          add(Structure* s, Requisition* new_request);
Requisition* removal(Structure* s);
int          get_size(Structure* s);
void         free_structure(Structure* s);
int 	     is_empty(Structure* s);

#endif 
