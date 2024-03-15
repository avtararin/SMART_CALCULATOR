#include "calculator.h"

Node *initializeList() {
  Node *head = NULL;
  return head;
}

void push_to_stack(Node **plist, double value, int priority, types type) {
  Node *p = malloc(sizeof(Node));
  p->value = value;
  p->priority = priority;
  p->next = *plist;
  *plist = p;
  p->type = type;
}

int is_empty(Node *list) { return list == NULL; }

Node *pop(Node **plist) {
  Node *res = NULL;
  if (plist == NULL)
    res = NULL;
  else {
    //    Node *res = *plist;
    Node *p = *plist;
    *plist = p->next;
    free(p);
  }
  return res;
}

void reverse_node(Node* src, Node** dst) {
  Node* prev = NULL;
  Node* current = src;
  Node* next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  *dst = prev;
}
