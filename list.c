// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t));
  
  if (mylist == NULL){
    return NULL;
  }
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) {
  if (l == NULL){
    return;
  }
  node_t *curr = l->head;

  while (curr != NULL){
    node_t *next = curr->next;
    free(curr);
    curr = next;
  }
  free(l);
}

void list_print(list_t *l) {
  if(l == NULL){
    printf("NULL\n");
    return;
  }
  node_t *curr = l->head;
  while (curr != NULL){
    printf("%d->", curr->value);
    curr = curr->next;
  }
  printf("NULL\n");
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024);
  char tbuf[20];

  if (buf == NULL){
    return NULL;
  }

  buf[0] = '\0';

	node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) {
  if(l == NULL){
    return 0;
  }
  int length = 0;
  node_t *curr = l->head;
  while(curr !=NULL){
    length++;
    curr = curr->next;
  }
  return length; 
}

void list_add_to_back(list_t *l, elem value) {
  if (l == NULL){
    return;
  }
  node_t *new_node= getNode(value);
  if(new_node == NULL){
    return;
  }
  if (l->head == NULL){
    l->head = new_node;
    return;
  }
  node_t *curr = l->head;
  while(curr->next != NULL){
    curr = curr->next;
  }
  curr->next = new_node;
}

void list_add_to_front(list_t *l, elem value) {
  if (l == NULL){
    return;
  }
  /* Insert to front */
  node_t *cur_node = getNode(value);  
  // get head of list
  if(cur_node == NULL){
    return;
  }
  cur_node->next = l->head;
  l->head = cur_node;
}

node_t * getNode(elem value) {
  node_t *mynode;

  mynode = (node_t *) malloc(sizeof(node_t));
  if (mynode==NULL){
    return NULL;
  }
  mynode->value = value;
  mynode->next = NULL;

  return mynode;
}

void list_add_at_index(list_t *l, elem value, int index) {
  if (l == NULL || index < 1){
    return;
  }
  if (index == 1){
    list_add_to_front(l,value);
    return;
  }
  node_t *curr = l->head;

  int i = 1;
  while(curr != NULL && i < index - 1){
    curr = curr->next;
    i++;
  }
  if (curr == NULL){
    return;
  }
  node_t  *new_node = getNode(value);
  if (new_node == NULL){
    return;
  }
  new_node->next=curr->next;
  curr->next= new_node;
}



elem list_remove_from_back(list_t *l) {
  if (l == NULL || l->head == NULL) {
    return -1;
  }
  node_t *curr = l->head;
  if (curr->next == NULL) {
        elem value = curr->value;
        free(curr);
        l->head = NULL;
        return value;
    }
    while (curr->next->next != NULL) {
        curr = curr->next;
    }
    node_t *removed = curr->next;
    elem value = removed->value;

    curr->next = NULL;
    free(removed);

    return value;
}
elem list_remove_from_front(list_t *l) {
  if(l == NULL || l->head == NULL){
    return -1;
  }
  node_t *removed = l->head;
    elem value = removed->value;

    l->head = removed->next;

    free(removed);

    return value;
}
elem list_remove_at_index(list_t *l, int index) {
  if (l == NULL || l->head == NULL || index < 1){
    return -1;
  }
  if (index == 1){
    return list_remove_from_front(l);
  }
  node_t *curr = l->head;
    int i = 1;

    while (curr != NULL && curr->next != NULL && i < index - 1) {
        curr = curr->next;
        i++;
    }
    if (curr == NULL || curr->next == NULL) {
        return -1;
    }

    node_t *removed = curr->next;
    elem value = removed->value;

    curr->next = removed->next;

    free(removed);

    return value;
}

bool list_is_in(list_t *l, elem value) {
  if (l == NULL) {
    return false;
  }
  node_t *curr = l->head;
  while (curr != NULL) {
        if (curr->value == value) {
            return true;
        }

        curr = curr->next;
    }

    return false;
}
elem list_get_elem_at(list_t *l, int index) {
  if (l == NULL || index < 1){
    return -1;
  }
  node_t *curr = l->head;
    int i = 1;
    while (curr != NULL){
        if (i == index) {
            return curr->value;
        }
        curr = curr->next;
        i++;
    }
    return -1;
}
int list_get_index_of(list_t *l, elem value) {
  if (l == NULL){
    return -1;
  }
  node_t *curr = l->head;
    int index = 1;

    while (curr != NULL) {
        if (curr->value == value) {
            return index;
        }

        curr = curr->next;
        index++;
    }
    return -1;
}

