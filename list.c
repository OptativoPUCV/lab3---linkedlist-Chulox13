#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
  List * list = (List *)malloc(sizeof(List));
  list->head = list->tail = list->current = NULL;
  return list;
  
}
  

void * firstList(List * list) 
{
  if (list == NULL || list->head == NULL)
  {
    return NULL;
  }
  list->current = list->head;
  return (void *)list->current->data;
  
}

void * nextList(List * list) 
{
  if (list == NULL || list->current == NULL || list->current->next == NULL)
    return NULL;

  list->current = list->current->next;
  return (void *)list->current->data;
  
}

void * lastList(List * list) 
{
  if (list == NULL || list->tail == NULL)
  {
    return NULL;
  }

  list->current = list->tail;
  return (void *)list->current->data;
  
  return NULL;
}

void * prevList(List * list) 
{  
  if (list == NULL || list->current == NULL || list->current->prev == NULL)
    return NULL;
  list->current = list->current->prev;
  return (void *)list->current->data;

}

void pushFront(List * list, void * data) 
{
  Node* nodo = createNode(data);
  
  
  nodo->next = list->head;
  nodo->prev = NULL;
  if (list->head) list->head->prev = nodo;
  list->head = nodo;
  if (list->tail == NULL) list->tail = nodo;
  
}

void pushBack(List * list, void * data) 
{
  Node* aux = list->head;
  while (aux->next != NULL)
    {
      aux = aux->next;
    }
  Node* nodo = createNode(data);
  aux->next = nodo;
  nodo->prev = aux;
  nodo->next = NULL;
  list->tail = nodo;
  
  
  
  
  list->current = list->tail;
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
  if (list == NULL || list->current == NULL)
  {
    return;
  }
  Node* nodo = createNode(data);
  nodo->next = list->current->next;
  nodo->prev = list->current;
  if (list->current->next) list->current->next->prev = nodo;
  list->current->next = nodo;
  if (list->current == list->tail) list->tail = nodo;
  
}

void * popFront(List * list) 
{
  if (list == NULL || list->head == NULL)
  {
    return NULL;
  }

  Node* aux = list->head;
  list->head = list->head->next;
  if (list->head) list->head->prev = NULL;
  
  free(aux);
  
  
  list->current = list->head;
  return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
  if (list == NULL || list->current == NULL)
    
  
  Node* toDelete = list->current;
  if (toDelete == list->head) {
      list->head = toDelete->next;
      if (list->head != NULL)
          list->head->prev = NULL;
  } else if (toDelete == list->tail) {
      list->tail = toDelete->prev;
      list->tail->next = NULL;
  } else {
      toDelete->prev->next = toDelete->next;
      toDelete->next->prev = toDelete->prev;
  }

  free(toDelete);
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}