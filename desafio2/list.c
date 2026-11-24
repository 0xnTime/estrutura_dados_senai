#include "list.h"
#include <stdlib.h>
#include <string.h>

struct List_ {
  Node *head;
  int size;
};

List *create_list() {
  List *list = (List *)malloc(sizeof(List));

  if (list == NULL)
    return NULL;

  list->head = NULL;
  list->size = 0;

  return list;
}

int get_quantity(List *list) {
  if (list == NULL)
    return -1;
  return list->size;
}

Node *get_begin(List *list) {
  if (list == NULL)
    return NULL;
  return list->head;
}

int add_list(List *list, Customer *customer) {
  if (list == NULL)
    return 1;
  if (customer == NULL)
    return 1;

  Node *cn = create_node(customer);
  if (cn == NULL)
    return 1;

  Node *tmp = list->head;
  list->head = cn;
  set_next(cn, tmp);
  list->size++;

  return 0;
}

void free_list(List *list) {
  if (list == NULL)
    return;
  Node *curr = list->head;

  while (curr != NULL) {
    Node *next = get_next(curr);
    free(curr);
    curr = next;
  }

  free(list);
}
