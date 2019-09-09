# CS170 Project 
This project is going to build the interpreter that recongize the user's input and store them into some , and then
build the functions thus user can call the functions and use the function for user's input. 

## Prerequisites
Install IntellJ and hereb is the link
https://www.jetbrains.com/idea/
### First Step
Write a recursive descent parser for the subset of Scheme defined by the following EBNF grammar:
 
<s_expression> ⟶ ( { <s_expression> } ) | #t | #f | <symbol> | ()

sample input and output like this:
```
scheme> (a b c)
S_Expression
(
  S_Expression
    a
  S_Expression
    b
  S_Expression
    c
)

scheme> (()()(()()))         
S_Expression
(
  S_Expression
    ()
  S_Expression
    ()
  S_Expression
  (
    S_Expression
      ()
    S_Expression
      ()
  )
)
```

### Second Step
begin the semantic analysis function of your interpreter. 
The first step is to represent the lists internally via a tree structure. 
And the next step is implement basic functions quote, car, cdr, cons, and symbol?

The structure is like: (a b c)

![Image of tree](https://mathcs.clarku.edu/~fgreen/courses/cs170/CS170HW/links.jpg)

Thus you can have some output like: 
```
scheme> (quote (a b c))
 ( a  b  c )

scheme> a
 a 

scheme> (car (quote (a b c)))
 a 

scheme> (cdr (quote (a b c)))
 ( b  c )

scheme> (car (cdr (quote (a b c))))
 b 

scheme> (cons (quote a) (quote (b c)))
 ( a  b  c )
 ```
###
Final Step

There is more advanced functions like append, null, equal, assoc and define 

The sample output will be like this: 

```
(append (quote (a b)) (quote (c d)))
scheme> ( a  b  c  d )
(append (quote (a b c)) (quote ()))
scheme> ( a  b  c )
(append (quote ()) (quote ()))
scheme>  ()
(null? ())
scheme>  #t
(null? #f)
scheme>  #t
(null? (cdr (quote (a))))
scheme>  #t
(equal? (quote a) (quote a))
scheme>  #t
(equal? (quote a) (quote b))
scheme>  ()
(equal? (quote (a b)) (quote (a b)))
scheme>  #t
(equal? (quote (a (b c) d)) (quote (a (b c) d)))
scheme>  #t
(equal? (quote (a (b c) d)) (quote (a (b c d) d)))
scheme>  ()
(assoc (quote joan) (quote ((john smith) (joan doe) (marcia law))))
scheme> ( joan  doe )
(assoc (quote john) (quote ((john smith) (joan doe) (marcia law))))
scheme> ( john  smith )
(assoc (quote jean) (quote ((john smith) (joan doe) (marcia law))))
scheme> ()
(define l1 (quote (a b c)))
(define l2 (quote (d e f)))
l1
scheme> ( a  b  c )
l2
scheme> ( d  e  f )
(append l1 l2)
scheme> ( a  b  c  d  e  f )
(cond ((null? (quote ())) (car (quote (a b))))
      (#t (cdr (quote (a b)))))
scheme>  a
(cond ((null? (quote (a))) (car (quote (a b))))
      (#t (cdr (quote (a b)))))
scheme> ( b )
```
