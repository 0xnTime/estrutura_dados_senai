#include "structure.h"
#include <stdlib.h>
#include <string.h>

#define BY_NAME_LEN 101
#define BY_DISTRICT_LEN 101
#define BY_PEOPLE_LEN 5
#define BY_CHILDREN_LEN 2
#define BY_INCOME_LEN 4

struct Structure_ {
  List *by_name[BY_NAME_LEN];
  List *by_district[BY_DISTRICT_LEN];
  List *by_people[BY_PEOPLE_LEN];
  List *by_children[BY_CHILDREN_LEN];
  List *by_income[BY_INCOME_LEN];
};

Structure *create_structure() {
  Structure *structure = (Structure *)calloc(1, sizeof(Structure));

  if (structure == NULL) {
    return NULL;
  }

  return structure;
}

static unsigned int hash_string(char *key, int size) {
  unsigned int sum = 0;
  int i = 0;

  while (key[i] != '\0') {
    // avoid some issues with naems like joão
    unsigned char ukey = key[i];
    sum = sum * 31 + ukey;

    i++;
  }

  return sum % size;
}

static int income_range(double income) {
  if (income <= 1999.99)
    return 0;
  if (income <= 3000.00)
    return 1;
  if (income <= 5000.00)
    return 2;
  return 3;
}

static int insert_into(List **slot, Customer *customer)
{
    if(*slot == NULL){
        *slot = create_list();
        if(*slot == NULL)
            return 1;
    }
    return add_list(*slot, customer);
}

int add_customer(Structure *structure, int criteria, Customer *customer) {
  if (structure == NULL || customer == NULL) {
    return 1;
  }
  switch (criteria) {
  case 1: {
    int bucket_index = hash_string(get_name(customer), BY_NAME_LEN);

    return insert_into(&structure->by_name[bucket_index], customer);

  }

  case 2: {
    int bucket_index = hash_string(get_district(customer), BY_DISTRICT_LEN);

    return insert_into(&structure->by_district[bucket_index], customer);
  }
  case 3: {
    int bucket_index = get_n_people(customer);

    if (bucket_index < 1)
      return 1;
    if (bucket_index > 5)
      bucket_index = 5;

    bucket_index -= 1;

    return insert_into(&structure->by_people[bucket_index], customer);
  }

  case 4: {
    int bucket_index = get_children(customer);

    if (bucket_index < 0 || bucket_index > 1) return 1;

    return insert_into(&structure->by_children[bucket_index], customer);
  }

  case 5: {
    int bucket_index = income_range(get_income(customer));

    return insert_into(&structure->by_income[bucket_index], customer);
  }

  default:
    return 1;
  }
}

List *retrieve_customer(Structure *structure, int criteria, int complement,
                        char *search) {
  if (structure == NULL) {
    return NULL;
  }

  switch (criteria) {
  case 1: {
    if (search == NULL)
      return NULL;
    int bucket_index = hash_string(search, BY_NAME_LEN);
    return structure->by_name[bucket_index];
  }
  case 2: {
    if (search == NULL)
      return NULL;
    int bucket_index = hash_string(search, BY_DISTRICT_LEN);
    return structure->by_district[bucket_index];
  }
  case 3:
    if (complement < 1 || complement > 5)
      return NULL;
    return structure->by_people[complement - 1];
  case 4:
    if (complement < 0 || complement > 1)
      return NULL;
    return structure->by_children[complement];
  case 5:
    if (complement < 1 || complement > 4)
      return NULL;
    return structure->by_income[complement - 1];

  default:
    return NULL;
  }
}

static void free_customers_in(List *list) {
  if (list == NULL)
    return;
  Node *curr = get_begin(list);
  while (curr != NULL) {
    Node *next = get_next(curr);
    free_customer(get_data(curr));
    curr = next;
  }
}

static void free_table(List **table, int len) {
  for (int i = 0; i < len; i++) {
    free_list(table[i]);
  }
}

void free_structure(Structure *structure) {
  if (structure == NULL)
    return;

  // free only this one so I dont get a double free
  for (int i = 0; i < BY_CHILDREN_LEN; i++) {
    free_customers_in(structure->by_children[i]);
  }

  free_table(structure->by_name, BY_NAME_LEN);
  free_table(structure->by_district, BY_DISTRICT_LEN);
  free_table(structure->by_children, BY_CHILDREN_LEN);
  free_table(structure->by_income, BY_INCOME_LEN);
  free_table(structure->by_people, BY_PEOPLE_LEN);

  free(structure);
}
