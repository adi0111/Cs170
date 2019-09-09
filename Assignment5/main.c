//
//  main.c
//  Assignment5
//
//  Created by WangShunchang on 5/8/19.
//  Copyright © 2019 WangShunchang. All rights reserved.
//

#include <stdio.h>
#include "lexer.h"
#include "stdio.h"
#include "parser.h"


int main(){
    printf("A prototype evaluator for Scheme.\n");
    printf("Type Scheme expressions using quote,\n");
    printf("car, cdr, cons and symbol?.\n");
    printf("The function call (exit) quits.\n");
    initializeEnv();// initilize env list
    while(1){
        printf("scheme>");
        List list = (List) malloc(sizeof(List)); //innitalize a list
        list = S_expr(list);  // build the cell structure
        list = Eval(list);// remove the function token
        printList(list); // read the cell structure
        printf("\n");
    }
    
}
