/* listIteratorG.c ... Generic List Iterator implementation
   Written by Dean Hou

   iterator cursor by default is behind the node
   add 20 gives
   20 ^
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorG.h"

typedef struct Node {
  void *value;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct IteratorGRep {
  Node *head;
  Node *current;
  Node *tail;
  Node *delete;
  int nitems;
  int front;

  ElmCompareFp cmpElm;
  ElmNewFp copyElm;
  ElmFreeFp freeElm;
} IteratorGRep;

IteratorG IteratorGNew(ElmCompareFp cmp, ElmNewFp copy, ElmFreeFp free) {
  IteratorG new = malloc(sizeof(struct IteratorGRep));
  if (new == NULL) {
    printf("Error, new list failed\n");
    exit(1);
  }
  new->head = NULL;
  new->current = NULL;
  new->tail = NULL;
  new->delete = NULL;
  new->nitems = 0;
  new->front = 0;

  new->cmpElm = cmp;
  new->copyElm = copy;
  new->freeElm = free;
  return new;
}

int add(IteratorG it, void *vp) {
  assert(it != NULL);
  Node *new = malloc(sizeof(struct Node));
  if (new == NULL) {
    return 0;
  }
  new->value = it->copyElm(vp);
  new->prev = NULL;
  new->next = NULL;
  if (it->head == NULL) { //list is empty ^ -> 25 ^
    it->head = new;
    it->current = new;
    it->tail = new;
    it->nitems++;
    //printf("1\n");
    return 1;
  } else if (it->current == it->tail) { // tail 25 ^ -> 25 11 ^
    it->current->next = new;
    new->prev = it->current;
    it->current = new;
    it->tail = new;
    it->nitems++;
    //printf("2\n");
    return 1;
  } else if (it->front == 1) { // head ^ 25 -> 11 ^ 25
    it->current->prev = new;
    new->next = it->current;
    it->head = new;
    it->current = new;
    it->nitems++;
    it->front = 0;
    //printf("3\n");
    return 1;
  } else if (it->head != it->tail) {
    new->next = it->current->next;
    new->prev = it->current;
    it->current->next->prev = new;
    it->current->next = new;
    it->current = new;
    it->nitems++;
    //printf("4\n");
    return 1;
  }
  return 0;
}

int hasNext(IteratorG it) {
  assert(it != NULL);
  if (next(it) != NULL) {
    previous(it);
    return 1;
  } else {
    return 0;
  }
}

int hasPrevious(IteratorG it) {
  assert(it != NULL);
  if (previous(it) != NULL) {
    next(it);
    return 1;
  } else {
    return 0;
  }
}

void *next(IteratorG it) {
  assert(it != NULL);
  if (it->current == NULL || (it->current->next == NULL && it->current != it->head)) {
    return NULL;
  }
  if (it->front != 1) {
    it->current = it->current->next;
    it->delete = it->current;
    return it->current->value;
  } else {
    it->front = 0;
    it->delete = it->current;
    return it->current->value;
  }
}

void *previous(IteratorG it) {
  assert(it != NULL);
  if (it->current == NULL) {
    return NULL;
  }
  if (it->current != it->head) {
    it->current = it->current->prev;
    it->delete = it->current->next;
    return it->current->next->value;
  } else if (it->front == 0) {
    it->front = 1;
    it->delete = it->current;
    return it->current->value;
  } else {
    return NULL;
  }
}

void *findNext(IteratorG it, void * vp) {
  assert(it != NULL);
  if (it->current->next == NULL) {
    return NULL;
  }
  Node *temp;
  if (it->front == 1) {
    temp = it->head;
  } else {
    temp = it->current->next;
  } 
  while (temp != NULL) {
    if (it->cmpElm(temp->value, vp) == 0) {
      it->current = temp;
      it->delete = temp;
      if (temp == it->head) {
        it->front = 0;
      }
      return it->current->value;
    }
    temp = temp->next;
  }
  return NULL;
}

void *findPrevious(IteratorG it, void * vp) {
  assert(it != NULL);
  if (it->current->prev == NULL) {
    return NULL;
  }
  Node *temp;
  temp = it->current;
  while (temp != NULL) {
    if (it->cmpElm(temp->value, vp) == 0) {
      if (temp->prev != NULL) {
        it->current = temp->prev;
        it->delete = temp;
      } else {
        it->current = it->head;
        it->front = 1;
        it->delete = it->current;
      }
      return it->current->next->value;
    }
    temp = temp->prev;
  }
  return NULL;
}

int delete(IteratorG it) {
  assert(it != NULL);
  if (it->delete == NULL) {
    return 0;
  }

  Node *curr = it->delete;
  if (it->head == it->tail) { // one value
    // printf("1\n");
    it->current = NULL;
    it->head = NULL;
    it->tail = NULL;
    it->front = 0;
    it->freeElm(curr->value);
    free(curr);
    it->nitems--;
    it->delete = NULL;
    return 1;
  } else if (it->delete == it->head) { // first value
    it->head = it->head->next;
    it->current = it->head;
    it->head->prev = NULL;
    if (it->front != 1) {
      it->front = 1;
    }
    it->freeElm(curr->value);
    free(curr);
    it->delete = NULL;
    it->nitems--;
    return 1;
  } else if (it->delete == it->tail) {
    it->current = it->delete->prev;
    it->tail = it->delete->prev;
    it->tail->next = NULL;
    it->freeElm(curr->value);
    free(curr);
    it->delete = NULL;
    it->nitems--;
    return 1;
  } else if (it->current->prev != NULL && it->current == it->delete) {
    //printf("1\n");
    it->current = it->current->prev;
    it->current->next = it->current->next->next;
    it->delete->next->prev = it->current;
    it->freeElm(curr->value);
    free(curr);
    it->delete = NULL;
    it->nitems--;
    return 1;
  } else {
    //printf("2\n");
    it->current->next = it->delete->next;
    it->delete->next->prev=it->current;
    it->freeElm(curr->value);
    free(curr);
    it->delete = NULL;
    it->nitems--;
    return 1;
  }
  printf("Fail\n");
  return 0;
}

int set(IteratorG it, void * vp) {
  assert(it != NULL);
  if (it->delete == NULL) {
    return 0;
  }
  if (it->delete != NULL) {
    it->delete->value = it->copyElm(vp);
    return 1;
  }
  return 0;
}

void reset(IteratorG it) {
  assert(it != NULL);
  if (it->current == NULL) {
    return;
  }
  Node *curr = it->current;
  while (curr->prev != NULL) {
    curr = curr->prev;
  }
  it->current = curr;
  it->front = 1;
}

void freeIt(IteratorG it) {
  assert(it != NULL);
  it->nitems = 0;
  if (it->head == NULL) {
    return;
  }
  if (it->head == it->tail) {
    free(it->current);
    return;
  }
  Node *curr = it->head;
  Node *temp;
  while (curr != NULL) {
    temp = curr->next;
    it->freeElm(curr->value);
    free(curr);
    curr = temp;
  }
  free(it);
}

void printList(IteratorG it, int mode) {
  if (it->head == NULL) {
    printf("list = \n^ \n");
    return;
  }
  printf("list = \n");
  Node *curr = it->head;
  int v;
  char *st;
  while (curr != NULL) {
    if (it->front != 1) {
      //printf("Head 0\n");
      if (mode == 0) {
        v = *(int *) curr->value;
        printf("%d ", v);
      } else {
        st = (char *) curr->value;
        printf("%s ", st);
      }
      if (curr == it->current) {
        printf("^ ");
      }
    } else {
      //printf("Head 1\n");
      if (curr == it->head) {
        printf("^ ");
      }
      if (mode == 0) {
        v = *(int *) curr->value;
        printf("%d ", v);
      } else {
        st = (char *) curr->value;
        printf("%s ", st);
      }
    }
    curr = curr->next;
  }
  printf("\n");
}





