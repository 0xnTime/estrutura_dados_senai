#include "customer.h"

#include <stdlib.h>
#include <string.h>

#define MAX_NAME 40
#define MAX_DISTRICT 40

struct Customer_ {
  char name[MAX_NAME + 1];
  char district[MAX_DISTRICT + 1];
  int n_people;
  int children;
  double income;
};

Customer *create_customer(char *name, char *district, int n_people,
                          int children, double income) {

  if (name == NULL || district == NULL)
    return NULL;

  Customer *customer = (Customer *)malloc(sizeof(Customer));

  if (customer == NULL)
    return NULL;

  strncpy(customer->name, name, MAX_NAME);
  customer->name[MAX_NAME] = '\0';

  strncpy(customer->district, district, MAX_DISTRICT);
  customer->district[MAX_DISTRICT] = '\0';

  customer->n_people = n_people;
  customer->children = children;
  customer->income = income;

  return customer;
}

char *get_name(Customer *customer) {
  if (customer == NULL)
    return NULL;
  return customer->name;
}

char *get_district(Customer *customer) {
  if (customer == NULL)
    return NULL;
  return customer->district;
}

int get_n_people(Customer *customer) {
  if (customer == NULL)
    return -1;
  return customer->n_people;
}
int get_children(Customer *customer) {
  if (customer == NULL)
    return -1;
  return customer->children;
}
double get_income(Customer *customer) {
  if (customer == NULL)
    return -1;
  return customer->income;
}

void free_customer(Customer *customer) {
  if (customer == NULL)
    return;
  free(customer);
}
