#include<stdio.h>
#include<conio.h>

void push(int);
void pop();
void display();
#define SIZE 100
int stack[SIZE], top = -1;

void main()
{
   int value, choice;
   while(1){
      printf("MENU\n");
      printf("1. Push\n2. Pop\n3. Display\n4. Exit");
      printf("\nEnter your choice: ");
      scanf("%d",&choice);
      switch(choice){

	 case 1:
         printf("Enter the value to be insert: ");
		 scanf("%d",&value);
		 push(value);
		 break;

	 case 2: pop();
		 break;

	 case 3: display();
		 break;

	 case 4: exit(0);

	 default: printf("\nWrong selection");
      }
   }
}

void push(int value){
   if(top == SIZE-1)
      printf("\nStack is Full");
   else{
      top++;
      stack[top] = value;
      printf("\nInsertion success!!!\n");
   }
}
void pop(){
   if(top == -1)
      printf("\nStack is Empty");
   else{
      printf("\nDeleted : %d", stack[top]);
      top--;
   }
}
void display(){
   if(top == -1)
      printf("\nStack is Empty");
   else{
      int i;
      printf("\nStack elements are:\n");
      for(i=top; i>=0; i--)
	 printf("%d\n",stack[i]);
   }
}
