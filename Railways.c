// Railway reservation using linked lists and Queues.

// If the reservation is full, prompt reservation full!! Put them in waiting list (queue) and give a waiting list number.
// If a passenger wishes to cancel his ticket, he may cancel. Then the passenger in waiting list is booked automatically.
// Display all the contents of reserved passengers.


#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define size 5
# define MAX_SIZE 20

typedef struct NODE
{
	int reg_no;
	int age;
	char name[MAX_SIZE];
	struct NODE *next;
} node;

node* deq();
void create();
int reserve();
int cancel(int);
void enq(node*);
void display();


node *start;
node *front;
node *rear;
int count=0;
int num=0;

void create()
{
	start=(node *)malloc(sizeof(node));
	start->reg_no = 1;

	printf("Name: ");
	scanf("%s",start->name);
	printf("Age : ");
	scanf("%d", &start->age);
	
	start->next=NULL;
	num++;
	
}

int reserve()
{
	
	if(start == NULL)
	{
		create();
		return 1;
	}

	else 
	{
		node *temp, *new_node, *prev;

		new_node=(node *)malloc(sizeof(node));
		
		printf("Name: ");
		scanf("%s",new_node->name);
		printf("Age : ");
		scanf("%d", &(new_node->age));

		new_node->next=NULL;
		
		temp=start;
		int i=1;
		if(temp->reg_no == 0)
		{
			temp->reg_no = 1;
			strcpy(temp->name,new_node->name);
			temp->age = new_node->age;
			num++;
			return 1;
		}
		while(temp->next != NULL)
		{
			if(temp->reg_no != i++)
				break;

			prev = temp;
			temp=temp->next;
		}	

		if(num<size)
		{
			num++;
			i++;
			if(temp->reg_no == (prev->reg_no+1) || i == 2) // If all gaps were filled
			{
				new_node->reg_no = i;
				temp->next = new_node;
				return i;
			}
			else	// Filling the gaps
			{
				new_node->next = temp;
				prev->next = new_node;
				new_node->reg_no = (temp->reg_no) - 1;
				printf("reg = %d\n",new_node->reg_no);
				return new_node->reg_no;
			}
			
		}

		else
		{
			enq(new_node);
			return 0;
		}
	}
}


int cancel(int reg)
{
	node *ptr, *preptr, *new;
	ptr=start;
	preptr=NULL;
	if(start==NULL)
	return -1;
	
	if(ptr->next==NULL && ptr->reg_no==reg)	// If only 1 person in reservation
	{
		start=NULL;
		num--;
		free(ptr);
		return 1;
	}
		
	else
	{	if(reg == 1)
		{
			ptr->reg_no = 0;
			new=deq(reg);
			if(new != NULL)
			{
				ptr->reg_no = 1;
				strcpy(ptr->name,new->name);
				ptr->age = new->age;
				num++;
				return 1;
			}
		}	

		else
		{
			while(ptr->reg_no != reg && ptr->next!=NULL)
			{
				preptr=ptr;
				ptr=ptr->next;
			}

			if(ptr->next == NULL && ptr->reg_no != reg)
				return -1;
			else
				preptr->next = ptr->next;

			free(ptr);
			new=deq(reg);
			num--;
			if(new != NULL)
			{
				node *waiting = start;
				while(waiting->reg_no != (new->reg_no - 1))
					waiting = waiting->next;

				new->next = waiting->next;
				waiting->next = new;
				num++;
			}
			return 1;
		}
	}
}

void enq(node *new_node)
{
	if(rear==NULL)
	{
		rear=new_node;
		rear->next=NULL;
		front=rear;
	}
	else
	{
		node *temp;
		temp=new_node;
		rear->next=temp;
		temp->next=NULL;
		rear=temp;
	}
	count++;
}

node* deq(int reg)
{
	node *front1;
	front1 = front;
	if(front==NULL)
		return NULL;
	else
	{
	    count-- ;
		if(front->next != NULL)
		{
			front=front->next;
			front1->next=NULL;
			front1->reg_no = reg;
			return front1;
		}
		else
		{
			front=NULL;
			rear=NULL;
			front1->reg_no = reg;
			return front1;
		}
	}		
}


void display()
{
	node *temp;
	temp = start;
	while(temp!=NULL)
	{
		if(temp->reg_no != 0)
		{
			printf("\nRegistration Number: %d\n", temp->reg_no);
			printf("Name : %s\n", temp->name);
			printf("Age : %d\n\n",temp->age);
		}
		temp=temp->next;
    }
    
}

int main()
{
	int choice, status=0,canc=0, reg=0;
	start=NULL;

	rear=NULL;
	front=NULL;
	
	
	
	printf("\t\t\t***RAILWAY RESERVATION***\t\t\t\t\n");
	int ch =0;
	while(ch!=4)
	{
	printf("\n\nDo you want to - \n 1. Reserve a ticket? \n 2. Cancel Booking \n 3. Display passenger details \n 4. exit\n\n");
	scanf("%d", &choice); 
	switch(choice)
	{	
		case 1 :  status = reserve();
	              if(status==0)
	                printf("\nBooking Full!! \nYou are added to waiting list. Waiting list number %d", count);
	              else
	                printf("\nBooking Successful!!! Enjoy your journey! Your Reg No. is %d\n", status);
	                
	              break;
	        
	    case 2:   printf("\nGive the Registration number to be cancelled : ");
	              scanf("%d", &reg);
	              if(reg>num)
	              	printf("Registration number invalid !!");
	              else
	              	{
	              		canc=cancel(reg);
	              		if(canc==-1)
	              			printf("Registration number invalid !!");
	              		else
	              			printf("Registration cancelled successfully");
	              	}
	              break;
	              
	    case 3: display();
	    break;
	    case 4: exit(0);   
	    break;
	    default: printf("\nWrong choice!\n");       		          
	
	}
	
}

}

