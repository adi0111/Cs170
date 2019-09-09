//  parser.c
//  Assignment5
//
//  Created by WangShunchang on 4/4/19.
//  Copyright © 2019 WangShunchang. All rights reserved.
//


#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
List globalEnv;

static char token[20];
int tab =0;


List createList(char* val){ //create a new cell with char parameter
    List list = (List)malloc(sizeof(struct Cell));
    if (list == NULL) {
        exit(1);
    }
    else {
        list->value = (char *) malloc(20*sizeof(char));
        if( val != NULL)
            strcpy( list -> value, val);
        list -> first = NULL;
        list -> rest  = NULL;
    }
    return list;
}

void initializeEnv ()
{
    globalEnv = createList("()");
}


List S_Expression () { // read the token and build the cell
    List local = (List)malloc(sizeof(struct Cell));
    List temp  = (List)malloc(sizeof(struct Cell));
    if (!(strcmp(token, "(")))
    {
        tab++;
        local = createList(NULL);
        strcpy(token, getToken());
        local -> first = S_Expression();
        temp = local;
        //S_Expression();
        while(strcmp(token, ")")){
            temp-> rest = createList(NULL);
            temp = temp -> rest;
            temp-> first = S_Expression();
        }
        tab--;
        temp-> rest = NULL;
        //if level of recursion is not zero
        if( tab != 0)
            strcpy(token, getToken());
    }
    else{// normal token
        local = createList(token);
        //if level of recursion is not zero
        if (tab != 0)
            strcpy(token, getToken());
    }
    return local;
}
//printList();
void printList(List list){
    // read cell structure
    if(list->value == NULL){
        printf("NULL");
    }
    else{
        if(list->first!= NULL){
            printf("(");
            while ( list != NULL){ // iterator
                if ( list -> first != NULL){
                    //list = list -> first;
                    printList(list->first);
                }
                list = list -> rest;
                //printList(list);
            }
            
            printf(")");
        }else {
            printf(" %s ", list->value);
        }
    }
}

List S_expr(List list){ //helper method to organize couples of method
    list =createList(NULL);
    startTokens(20);
    strcpy(token, getToken());
    list = S_Expression();
    return list;
}

List car(List list){
    list = list->first;
    return list;
}

List quote(List list){
    return list;
}

List cons(List list1, List list2){
    List list =createList(NULL);
    list->first = list1;
    list->rest = list2;
    if(list2->first== NULL && list2->rest== NULL)
        list->rest=NULL;
    else{
        list->rest = list2;
    }
    return list;
}

List cdr(List list){
    if (list -> rest == NULL)
        list->value = "#f";
    else
        list = list -> rest;
    return list;
}
List append(List list1, List list2){
    if(list1 == NULL){
        return list2;
    }else{
        list1 = cons(list1->first, append (list1->rest, list2));
        return list1;}
}
List symbol (List list){
    List newlist = createList(NULL);
    if(list->first == NULL)
        newlist->value = "#f";
    else
        newlist->value = "()";
    return newlist;
}
List null(List list){
    if( list == NULL)
        return createList("#t");
    else if((!strcmp(list->value, "#f" )) && (list->value != NULL))
        return createList("#t");
    else if((!strcmp(list->value, "()" )) && (list->value != NULL))
        return createList("#t");
    else if((!strcmp(list->value, "#t" )) && (list->value != NULL))
        return createList("#t");
    else
        return createList("#f");
}
List equalbase(List list1, List list2){
    // if ( (list1->first == NULL) != (list2->first == NULL) )
    if ( (list1== NULL) != (list2== NULL) )
        return createList("()");
    else if ( (list1== NULL) && (list2== NULL) )
        return createList("#t");
    else if ( strcmp(list1->value, list2-> value))
        return createList("()");
    else
        return createList("cont");
}
int convert(List list){
    if (!(strcmp(list->value, "#t")) && list ->first == NULL && list -> rest == NULL)
        return 1;
    else if (!(strcmp(list->value, "()")) && list ->first == NULL && list -> rest == NULL)
        return 0;
    else
        return -1;
}

List equal(List list1, List list2){
    List base = equalbase(list1, list2);
    if(!strcmp(base->value, "()")){ // check the structure base cases
        return createList("()");}
    else if(!strcmp(base->value, "#t"))
        return createList("#t");
    else if(!strcmp(base->value, "cont"))
        if (convert(equal(list1->first, list2->first)) && convert(equal(list1->rest, list2->rest)))
            return createList("#t");
        else
            return createList("()");
        else
            return createList("()");
}
// define( assoc s al)
// (cond (null? al) #f)
//  ((equal? s (car (car(al)))
//  (car al))
//      #t (assoc s (cdr (al)))))
List assoc(List list1, List list2){
    if ( list2 == NULL || !strcmp(list2->value, "()"))
        return createList ("()");
    if (!strcmp( (equal(list1, list2->first->first))->value, "#t"))
        return list2 ->first;
    else
        return assoc(list1, list2->rest);
}
List cond(List list, List env){
    List newlist = Eval(list->first->first);
    if( (newlist->value != NULL) && ( !strcmp(newlist->value, "#t")|!strcmp(newlist->value, "else"))){
        return Eval(list->first->rest->first);
    }   else{
        return (cond(list->rest, env));
    }
    
}
List define(List name, List value)
{
    List newlist = createList(NULL);
    newlist->first = name;
    newlist->rest = createList(NULL);
    newlist->rest->first = value;
    globalEnv = cons(newlist,globalEnv);
    return newlist;
}
List userdefine ( List function, List parameter, List sexpr)
{
    List newlist = createList(NULL);
    newlist -> first = function;
    newlist -> rest = createList(NULL);
    newlist -> rest ->first = createList("define");
    newlist -> rest ->first ->rest =createList(NULL);
    newlist -> rest -> first ->rest ->first = function;
    newlist -> rest -> first ->rest ->first ->rest = parameter;
    newlist -> rest -> first ->rest ->rest = sexpr;
    globalEnv = cons(newlist, globalEnv);
    return newlist;
}


List EvalHelper (List list, List env){
    List newlist;
    if(list->first == NULL){
        if (!strcmp( assoc(list, env)->value, "()") ){
            return list;
        }else{
            return assoc(list, env)->rest->first;
        }
    }
    else if (!strcmp(list->first->value, "assoc")){
        newlist = assoc(EvalHelper(list->rest->first,env), EvalHelper(list->rest->rest->first,env));
        return newlist;
    }
    else if (!strcmp(list->first->value, "define")){
        if(list->rest->first->first == NULL){
        newlist = define(EvalHelper(list->rest->first,env), EvalHelper(list->rest->rest->first,env) );
        globalEnv =  cons(newlist, env);
            return newlist->first;}
        else {
            newlist = userdefine(EvalHelper(list->rest->first,env), EvalHelper(list->rest->first->rest,env), list->rest->rest->first);
                globalEnv =  cons(newlist, env);
            return newlist->first;}
    }
    else if(!strcmp(list->first->value, "environment")){
        return env;
    }
    else if(!strcmp(list->first->value, "quote")){
        newlist = quote(EvalHelper(list->rest->first,env));
        return newlist;
    }
    else if( !strcmp(list->first->value, "car")){
        newlist = car(EvalHelper(list->rest->first,env));
        return newlist;
    }
    else if( !strcmp(list->first->value, "cdr")){
        newlist = cdr(EvalHelper(list->rest->first,env));
        return newlist;
    }
    else if(! strcmp(list->first->value, "cons")){
        newlist = cons(EvalHelper(list->rest->first,env), EvalHelper(list->rest->rest->first,env));
        return newlist;
    } else if(! strcmp(list->first->value, "symbol")){
        newlist = symbol(EvalHelper(list->rest->first,env));
        return newlist;
    }
    else if(! strcmp(list->first->value, "append")){
        newlist = append(EvalHelper(list->rest->first,env), EvalHelper(list->rest->rest->first,env));
        return newlist;
    } else if(! strcmp(list->first->value, "null?")){
        newlist = null(EvalHelper(list->rest->first, env));
        return newlist;}
    else if(! strcmp(list->first->value, "equal?")){
        newlist = equal(EvalHelper(list->rest->first,env), EvalHelper(list->rest->rest->first,env));
        return newlist;}
    else if(! strcmp(list->first->value, "cond")){
        newlist = cond(EvalHelper(list->rest, env), env);
        return newlist;}
    else if(!strcmp(list->first->value, "exit")){
        printf("have a nice day!");
        exit(0);
    }
    else
    {
        return list;
    }
}

List Eval (List list)
{
    //globalEnv = createList("()");
    return EvalHelper(list, globalEnv);
}



/*int printSpace(char* string, int max){
 for(int i =0; i < max; i++)
 {
 printf(" ");
 }
 printf("%s\n",string);
 return 0;
 }
 */

