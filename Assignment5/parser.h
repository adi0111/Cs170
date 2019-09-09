//
//  parser.h
//  Assignment5
//
//  Created by WangShunchang on 4/4/19.
//  Copyright © 2019 WangShunchang. All rights reserved.
//

#ifndef parser_h
#define parser_h

#include "lexer.h"

#include <stdio.h>
struct Cell {
    char* value;
    struct Cell* first;
    struct Cell* rest;
};
typedef struct Cell *List;


/****************************************************************
 Function: S_expr(List)
 ------------------------------------
 Initialize a list that read token and build the sturcture with value, first and rest.
 
 Call this function to read the token and build the structure.
 
 it recusive call the token and put in the token in one of method call s_experssion and run it with the
 algorith to make the cell sturcture. s_expersion follow the structure give on class and create list will
 build the new cell with value parameter
 */

List S_expr (List);
/****************************************************************
 Function: printList(List)
 ------------------------------------
 call a List parameter and read the cell sturcture and build it with normal way.
 if read (a b) cell sturcture, it can read and print ( a b ).
 */

void printList(List);
/****************************************************************
 Function: List Eval(List)
 ------------------------------------
 call a List parameter and read the cell sturcture and compare to the function build in the parser.c, and if the functions in the cfile and the name of token is equal to the funtion, it excutes the funtions.
 */
List Eval(List);
/****************************************************************
 Function: void initializeEnv(void)
 ------------------------------------
 initialize the environment and assign the env as empty list to start.
 */
void initializeEnv (void);

#endif /* parser_h */
