#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"

void insert_at_tail(struct node**head,int data)
{
   
    struct node*newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->next=NULL;
    if(!newnode)
    {
        printf("NO MEMORY ALLOCATED \n");
        exit(1);
    }
    if(*head==NULL)
    {
        *head=newnode;
    }
    else{
        struct node* temp =*head;
        while( temp ->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newnode;
    }
}



void insert_at_head(struct node**head,int data)
{
    struct node*newnode=(struct node*)malloc(sizeof(struct node));
    if(newnode==NULL)
    {
        printf("MEMORY ALLOCATION FAILED ");
        exit(1);
    }
    newnode->data=data;
    newnode->next=*head;
    *head=newnode;
}
struct BigInteger initialize(char *str)
{
   struct BigInteger list;
   list.head=NULL;
   int i=0;
   while(str[i]!='\0')
   {
       int num=str[i]-'0';
       insert_at_head(&(list.head),num);
       i++;
   }
   return list;
}
struct node* reverse(struct node*head)
{
    struct node*current=head;
    struct node*next=NULL;
    struct node*prev=NULL;
    while(current!=NULL)
    {
        next=current->next;
        current->next=prev;
        prev=current;
        current=next;
    }
    head=prev;
    return head;
}

void display_rev(struct node*head)
{
  if(head==NULL)return;
  display_rev(head->next);
  printf("%d",head->data);
}

void display(struct BigInteger list)
{
    struct node*head=list.head;
    if(list.head==NULL)
    {
        printf("0");
        return;
    }
    display_rev(head);
}
struct BigInteger add(struct BigInteger l1,struct BigInteger l2 )
{
    int carry=0;
    struct node*list1=l1.head,*list2=l2.head;
    struct BigInteger sum1;
    sum1.head=NULL;
    while(list1!=NULL && list2!=NULL )
    {
        int sum=(list1)->data + (list2)->data +carry;
        int digit=sum%10;
        carry=sum/10;
        
        insert_at_tail(&(sum1.head),digit);
        list1= (list1)->next;
        list2= (list2)->next;

    }
    while(list1!=NULL)
    {
        int sum=(list1)->data +  +carry;
        int digit=sum%10;
        carry=sum/10;
        
        insert_at_tail(&(sum1.head),digit);
         list1= (list1)->next;
    }
     while(list2!=NULL)
    {
        int sum=(list2)->data +  +carry;
        int digit=sum%10;
        carry=sum/10;
        
        insert_at_tail(&(sum1.head),digit);
        list2= (list2)->next;
    }
    if (carry > 0)
    {
        insert_at_tail(&(sum1.head),carry);
    }
    return sum1;
}
struct BigInteger mul(struct BigInteger list1,struct BigInteger list2)
{
    struct BigInteger mul1,btw;
    mul1.head=NULL;
    struct node*n1=list1.head,*n2=list2.head;
    int carry=0,product=0,i=0;
    while(n2!=NULL)
    {
        struct node*n1=list1.head;
        carry=0;
        btw.head=NULL;
        for(int j=0;j<i;j++)
        {
            insert_at_tail(&(btw.head),0);
        }
        while(n1!=NULL)
        {
            product=(n1->data)*(n2->data)+carry;
            insert_at_tail(&(btw.head),product%10);
            carry=product/10;
            n1=n1->next;
        }
     
        if(carry>0)
        {
             insert_at_tail(&(btw.head),carry);
        }
    
        mul1=add(btw,mul1);
        n2=n2->next;
        i++;
    }
    
    return mul1;
}



 struct BigInteger sub(struct BigInteger a, struct BigInteger b) {
    struct BigInteger result;
    result.head = NULL;
    
    struct node* l1 = a.head;
    struct node* l2 = b.head;
    int borrow = 0;

    while (l1 != NULL || l2 != NULL) {
        int val1 = (l1 != NULL) ? l1->data : 0;
        int val2 = (l2 != NULL) ? l2->data : 0;

        int diff = val1 - val2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        insert_at_tail(&(result.head), diff);

        if (l1 != NULL) {
            l1 = l1->next;
        }
        if (l2 != NULL) {
            l2 = l2->next;
        }
    }
    result.head=reverse(result.head);
    while (result.head != NULL && result.head->data == 0) {
        struct node* temp = result.head;
        result.head = result.head->next;
        free(temp);
    }
    result.head=reverse(result.head);

    return result;
}

int length(struct BigInteger l)
{
    struct node*ptr=l.head;
    if(ptr==NULL)return 0;
    int cnt=0;
    while(ptr!=NULL)
    {
        ptr=ptr->next;
        cnt++;
    }
    return cnt;
}


int compare(struct BigInteger a, struct BigInteger b) {
    int l1 = length(a);
    int l2 = length(b);
    if (l1 > l2)
        return 1;
    if (l1 < l2)
        return -1;

    if (l1 == l2) {
        struct node* ptr1 = a.head;
        struct node* ptr2 = b.head;

        while (l1 == l2 && l1 > 0) {
            if (ptr1->data > ptr2->data) {
                
                return 1;
            } else if (ptr1->data < ptr2->data) {
                return -1;
            }

            l1--;l2--;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }

    return 0;
}

struct BigInteger div1(struct BigInteger dividend,struct BigInteger divisor)
{
   struct BigInteger quo;
   quo.head=NULL;
   struct BigInteger one;
   one=initialize("1");
    struct BigInteger remainder;
    remainder.head=NULL;
    
    struct node*temp2=dividend.head;
    while(temp2!=NULL)
    {
        insert_at_tail(&(remainder.head),temp2->data);
        temp2=temp2->next;
    }

while(compare(divisor,remainder)!=1)
{
    remainder=sub(remainder,divisor);
    quo=add(quo,one);
}
return quo;
}

struct BigInteger mod(struct BigInteger dividend,struct BigInteger divisor)
{
   struct BigInteger quo;
   quo.head=NULL;
   struct BigInteger one;
   one=initialize("1");
    struct BigInteger remainder;
    remainder.head=NULL;
    
    struct node*temp2=dividend.head;
    while(temp2!=NULL)
    {
        insert_at_tail(&(remainder.head),temp2->data);
        temp2=temp2->next;
    }

while(compare(divisor,remainder)!=1)
{
    remainder=sub(remainder,divisor);
    quo=add(quo,one);
}
return remainder;

}

