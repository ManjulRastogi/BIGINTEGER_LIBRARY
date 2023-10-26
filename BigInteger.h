#include<stdio.h>
#include<stdlib.h>
#ifndef BigInteger_h
#define BigInteger_h
struct node{
    int data;
    struct node* next;
};

struct BigInteger{
    struct node*head;
};

void insert_at_tail(struct node** head,int data);
void insert_at_head(struct node**head,int data);
struct BigInteger initialize(char *str);
struct node* reverse(struct node*head);
void display_rev(struct node*head);
void display(struct BigInteger list);
struct BigInteger add(struct BigInteger l1,struct BigInteger l2 );
struct BigInteger mul(struct BigInteger list1,struct BigInteger list2);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
int length(struct BigInteger l);
int compare(struct BigInteger a, struct BigInteger b);
struct BigInteger div1(struct BigInteger dividend,struct BigInteger divisor);
struct BigInteger mod(struct BigInteger dividend,struct BigInteger divisor);
# endif
