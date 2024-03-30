# Statement Programming Language

A small Programming Language made in C++

## Grammar

## Rules:
- (\*) - repeat production
- (|) - OR
- (?) - optional production

```

program -> statement* EOF;

statement -> decl | assign | print | input | cond;

decl -> "var" NAME ("=" expression)? ";" ;
assign -> NAME "=" expression ";" ;
print -> "print" expression ";" ;
input -> "input" NAME ";" ;
cond -> "if" expression LABEL (else LABEL)?

expression -> equality

equality -> comparison (("==" | "!=") comparison)* ;
comparison -> term ((">" | "<" | "<=" | ">=") term)* ;
term -> factor (("+" | "-") factor)* ;
factor -> primary (("*" | "/") primary)* ;
primary -> NAME | STRING | NUMBER | "true" | "false" | "none" | "(" expression ")" ;

```

## Features

## Sample program

```

# A program to square a number

var n;
input n;

print n*n;

```

## References

https://craftinginterpreters.com

https://github.com/munificent/jasic/blob/master/com/stuffwithstuff/Jasic.java