/*
  testListIteratorG.c ... client to test Generic List Iterator 
*/ 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listIteratorG.h"
#include "positiveIntType.h"
#include "stringType.h" 
#include <ctype.h>

#define MAXARRAY 5
#define POSITIVEINTTYPE 0
#define STRINGTYPE 1
#define MAX_LINE 4096

int main(int argc, char *argv[]) {
// - - - - - - -testing - - - - - - //
  /* =======================================
     --------- positiveIntType List Iterator ----------
  */
  
/*
  IteratorG it1 = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
  
  int a[MAXARRAY] = { 25, 12, 6, 82 , 11};
  
  int i;
  int result;
  for(i=0; i<MAXARRAY; i++){
    result = add(it1 , &a[i]); 
    printf("Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
    printList(it1, POSITIVEINTTYPE);
  }

  printList(it1, POSITIVEINTTYPE);
  int *v0 = (int *) next(it1);
  if (v0 == NULL) {
    printf("Next value is: NULL \n");     // should print "Next value is: 82" 
  }
  printList(it1, POSITIVEINTTYPE);
  int *v1 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v1 );  // should print "Previous value is: 11" 
  printList(it1, POSITIVEINTTYPE);
  int *v2 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v2 );  // should print "Previous value is: 82" 
  printList(it1, POSITIVEINTTYPE);
  int *v3 = (int *) next(it1);
  printf("Next value is: %d \n", *v3 );     // should print "Next value is: 82" 
  printList(it1, POSITIVEINTTYPE);
  result = add(it1 , &a[0]); 
  printf("Inserting %d: %s \n", a[0], (result==1 ? "Success" : "Failed") );
  printList(it1, POSITIVEINTTYPE);
  int *v4 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v4 );  // should print "Previous value is: 25
  printList(it1, POSITIVEINTTYPE);
  int *v5 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v5 );  // should print "Previous value is: 82
  printList(it1, POSITIVEINTTYPE);
  int *v6 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v6 );  // should print "Previous value is: 6
  printList(it1, POSITIVEINTTYPE);
  int *v7 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v7 );  // should print "Previous value is: 12
  printList(it1, POSITIVEINTTYPE);
  int *v8 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v8 );  // should print "Previous value is: 25
  printList(it1, POSITIVEINTTYPE);
  int *v9 = (int *) previous(it1);
  if (v9 == NULL) {
    printf("Previous value is: NULL \n");
  }
  printList(it1, POSITIVEINTTYPE);
  result = add(it1 , &a[2]); 
  printf("Inserting %d: %s \n", a[2], (result==1 ? "Success" : "Failed") );
  printList(it1, POSITIVEINTTYPE);

  printf("FindNext and FindPrevious\n");
  findNext(it1, &a[0]);
  printList(it1, POSITIVEINTTYPE);
  findNext(it1, &a[0]);
  printList(it1, POSITIVEINTTYPE);
  findPrevious(it1, &a[0]);
  printList(it1, POSITIVEINTTYPE);
  findPrevious(it1, &a[0]);
  printList(it1, POSITIVEINTTYPE);

  printf("Delete\n");

  printf("Set\n");

  printf("Reset\n");
  findNext(it1, &a[0]);
  findNext(it1, &a[0]);
  reset(it1);
  printList(it1, POSITIVEINTTYPE);
  freeIt(it1);
  printList(it1, POSITIVEINTTYPE);

  printf("----log----\n");
  IteratorG itTest = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
  int value;
  value = 20;
  result = add(itTest, &value);
  printList(itTest, POSITIVEINTTYPE);
  value = 12;
  result = add(itTest, &value);
  printList(itTest, POSITIVEINTTYPE);
  value = 33;
  result = add(itTest, &value);
  printList(itTest, POSITIVEINTTYPE);
  value = 25;
  result = add(itTest, &value);
  printList(itTest, POSITIVEINTTYPE);
  previous(itTest);
  printList(itTest, POSITIVEINTTYPE);
  previous(itTest);
  printList(itTest, POSITIVEINTTYPE);
  next(itTest);
  printList(itTest, POSITIVEINTTYPE);
  result = delete(itTest);
  printList(itTest, POSITIVEINTTYPE);
  previous(itTest);
  printList(itTest, POSITIVEINTTYPE);
  result = delete(itTest);
  printList(itTest, POSITIVEINTTYPE);
  previous(itTest);
  printList(itTest, POSITIVEINTTYPE);
  result = delete(itTest);
  printList(itTest, POSITIVEINTTYPE);
  next(itTest);
  printList(itTest, POSITIVEINTTYPE);
  result = delete(itTest);
  printList(itTest, POSITIVEINTTYPE);
  value = 55;
  result = add(itTest, &value);
  printList(itTest, POSITIVEINTTYPE);
  value = 29;
  result = add(itTest, &value);
  printList(itTest, POSITIVEINTTYPE);
  reset(itTest);
  printList(itTest, POSITIVEINTTYPE);
  next(itTest);
  printList(itTest, POSITIVEINTTYPE);
  value = 62;
  result = add(itTest, &value);
  printList(itTest, POSITIVEINTTYPE);
  value = 44;
  result = add(itTest, &value);
  printList(itTest, POSITIVEINTTYPE);
  previous(itTest);
  printList(itTest, POSITIVEINTTYPE);
  next(itTest);
  printList(itTest, POSITIVEINTTYPE);
  result = delete(itTest);
  printList(itTest, POSITIVEINTTYPE);
  previous(itTest);
  printList(itTest, POSITIVEINTTYPE);
  next(itTest);
  printList(itTest, POSITIVEINTTYPE);
  result = delete(itTest);
  printList(itTest, POSITIVEINTTYPE);
  result = delete(itTest);
  printList(itTest, POSITIVEINTTYPE);
  next(itTest);
  printList(itTest, POSITIVEINTTYPE);
  result = delete(itTest);
  printList(itTest, POSITIVEINTTYPE);
  previous(itTest);
  printList(itTest, POSITIVEINTTYPE);
  result = delete(itTest);
  printList(itTest, POSITIVEINTTYPE);
  freeIt(itTest);
  printf("-----log complete------\n");*/
  /* =======================================
     --------- stringType List Iterator ----------
  */
  
/*
  IteratorG it2 = IteratorGNew(stringCompare, stringNew, stringFree);
  
  char *strA[MAXARRAY];
  strA[0] = strdup("john");
  strA[1] = strdup("rita");
  strA[2] = strdup("john");
  strA[3] = strdup("abby"); 
  
  int j;
  for(j=0; j<4; j++){
    int result = add(it2 , strA[j]); 
    printf("Inserting %s: %s \n", strA[j], (result==1 ? "Success" : "Failed") );
    printList(it2, STRINGTYPE);
  }

  char *v100 = (char *) previous(it2);
  printf("Previous value is: %s \n", v100 );  // should print: "Previous value is: abby"
  printList(it2, STRINGTYPE);
  char *v101 = (char *) previous(it2);
  printf("Previous value is: %s \n", v101 );  // should print: "Previous value is: john"
  printList(it2, STRINGTYPE);
  char *v102 = (char *) next(it2);
  printf("Next value is: %s \n", v102 );      // should print: "Next value is: john"
  printList(it2, STRINGTYPE);
  findNext(it2, strA[3]);
  printList(it2, STRINGTYPE);
  findPrevious(it2, strA[0]);
  printList(it2, STRINGTYPE);*/
  // - - - - -- - -- - - - - -tests end - - - - - - - - - -//
  char line[MAX_LINE];
  int result;
  int mode = POSITIVEINTTYPE;
  /*printf("Enter 0 for positive integer type list iterator or 1 for string type list iterator: \n");
  scanf("%d", &mode);*/
  
  if (mode == POSITIVEINTTYPE) {
    IteratorG intList = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
    while (1) {
      printf("type help for commands\n");
      printList(intList, POSITIVEINTTYPE);
      printf("> ");

      if (fgets(line, MAX_LINE, stdin) == NULL) {
        return 0;
      }
      int i = 0;
      while (isalpha(line[i]) || line[i] == '_') {
        i++;
      }
      int argument = atoi(&line[i]);
      line[i] = '\0';
      if (strcmp(line, "quit") == 0) {
        return 0;
      } else if (strcmp(line, "add") == 0) {
        result = add(intList, &argument);
      } else if (strcmp(line, "next") == 0) {
        next(intList);
      } else if (strcmp(line, "prev") == 0) {
        previous(intList);
      } else if (strcmp(line, "hasnnext") == 0) {
        result = hasNext(intList);
        printf("Return %d\n", result);
      } else if (strcmp(line, "hasprev") == 0) {
        result = hasPrevious(intList);
        printf("Return %d\n", result);
      } else if (strcmp(line, "findnext") == 0) {
        findNext(intList, &argument);
      } else if (strcmp(line, "findprev") == 0) {
        findPrevious(intList, &argument);
      } else if (strcmp(line, "delete") == 0) {
        delete(intList);
      } else if (strcmp(line, "set") == 0) {
        set(intList, &argument);
      } else if (strcmp(line, "reset") == 0) {
        reset(intList);
      } else if (strcmp(line, "free") == 0) {
        free(intList);
        return 0;
      } else if (strcmp(line, "help") == 0) {
        printf("Commands: \n");
        printf("add %%      - add a given value\n"); // add
        printf("next       - move cursor one position right\n"); // next
        printf("prev       - move cursor one position left\n"); // prev
        printf("hasnext    - check if there are positions to move right, returns 1 if true, 0 otherwise\n"); // has>
        printf("hasprev    - check if there are positions to move left, returns 1 if true, 0 otherwise\n"); // has<
        printf("findnext %% - find value on left of cursor\n"); // findn
        printf("findprev %% - find value on right of cursor\n"); // findp
        printf("delete     - delete last value of next, prev, findnext or findprev\n"); // delete
        printf("set %%      - replace last value of next, prev, findnext or findprev\n"); // set
        printf("reset      - set cursor position to start\n"); // reset
        printf("free       - delete list (exit program follows)\n"); // free
        printf("quit       - quit program\n"); // quit
      } else if (strcmp(line, "") != 0) {
        printf("Unknown command: '%s'\n", line);
      }
    }
  }/* else {
    IteratorG stringList = IteratorGNew(stringCompare, stringNew, stringFree);
    while (1) {
      printf("type help for commands\n");
      printList(stringList, STRINGTYPE);
      printf("> ");

      if (fgets(line, MAX_LINE, stdin) == NULL) {
        return 0;
      }
      int i = 0;
      while (isalpha(line[i]) || line[i] == '_' ) {
        i++;
      }

      char *argument = &line[i];
      line[i] = '\0';
      if (strcmp(line, "quit") == 0) {
        return 0;
      } else if (strcmp(line, "add") == 0) {
        result = add(stringList, &argument);
      } else if (strcmp(line, "next") == 0) {
        next(stringList);
      } else if (strcmp(line, "prev") == 0) {
        previous(stringList);
      } else if (strcmp(line, "hasnnext") == 0) {
        result = hasNext(stringList);
        printf("Return %d\n", result);
      } else if (strcmp(line, "hasprev") == 0) {
        result = hasPrevious(stringList);
        printf("Return %d\n", result);
      } else if (strcmp(line, "findnext") == 0) {
        findNext(stringList, &argument);
      } else if (strcmp(line, "findprev") == 0) {
        findPrevious(stringList, &argument);
      } else if (strcmp(line, "delete") == 0) {
        delete(stringList);
      } else if (strcmp(line, "set") == 0) {
        set(stringList, &argument);
      } else if (strcmp(line, "reset") == 0) {
        reset(stringList);
      } else if (strcmp(line, "free") == 0) {
        free(stringList);
        return 0;
      } else if (strcmp(line, "help") == 0) {
        printf("Commands: \n");
        printf("add %%      - add a given value\n"); // add
        printf("next       - move cursor one position right\n"); // next
        printf("prev       - move cursor one position left\n"); // prev
        printf("hasnext    - check if there are positions to move right\n"); // has>
        printf("hasprev    - check if there are positions to move left\n"); // has<
        printf("findnext %% - find value on left of cursor\n"); // findn
        printf("findprev %% - find value on right of cursor\n"); // findp
        printf("delete     - delete last value of next, prev, findnext or findprev\n"); // delete
        printf("set %%      - replace last value of next, prev, findnext or findprev\n"); // set
        printf("reset      - set cursor position to start\n"); // reset
        printf("free       - delete list (exit program follows)\n"); // free
        printf("quit       - quit program\n"); // quit
      } else if (strcmp(line, "") != 0) {
        printf("Unknown command: '%s'\n", line);
      }
    }
  }*/
  return EXIT_SUCCESS;
  
}
