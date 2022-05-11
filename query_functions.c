#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shop.h"

extern struct Client *head;
extern bool (*chekArr[ARR]) (char[]);
extern int exist (struct Client *node, int id);
extern bool earlier (unsigned int t1[], unsigned int t2[]);
extern void swap (struct Client *a, struct Client *b);
extern void update (struct Client *node, int num, char first[], char last[],
		    char phone[], double debt, unsigned int tm[]);
extern bool badDate (char[]);
extern void bubbleSort (struct Client *start);
//================================
/* Given a node prev_node, insert a new node after the given prev_node */
void insertAfter (struct Client *prev_node, char first[], char last[],
	     unsigned int id, char phone[], double debt, unsigned int tm[])
{
  /*1. check if the given prev_node is NULL */
  if (prev_node == NULL)
    {
      printf ("the given previous node cannot be NULL");
      return;
    }

  /* 2. allocate new node */
  struct Client *new_node = (struct Client *) malloc (sizeof (struct Client));
  if (new_node == NULL)
    {
      printf ("malloc in append failed\n");
      return;
    }
  /* 3. put in the data  */
  //new_node->data  = new_data;
  strcpy (new_node->first, first);
  strcpy (new_node->last, last);
  new_node->ID = id;
  strcpy (new_node->phone, phone);
  new_node->debt = debt;
  new_node->date.day = tm[0];
  new_node->date.month = tm[1];
  new_node->date.year = tm[2];

  /* 4. Make next of new node as next of prev_node */
  new_node->next = prev_node->next;

  /* 5. move the next of prev_node as new_node */
  prev_node->next = new_node;
}

//================================
void check (struct Client *head, char data[][MAX])
{
  int i, allok = 0;
  bool ok;
  for (i = 0; i < ARR; i++)
    {
      ok = chekArr[i] (data[i]);	// check every field
      if (ok == false)
	allok++;
    }
  if (allok == ARR)
    {				//if every field is ok
      char *ptr, t[MAX];
      unsigned int data2 = atoi (data[2]), data5[3];
      double data4 = strtod (data[4], &ptr);
      strcpy (t, data[5]);
      data5[0] = atoi (strtok (t, "/"));
      for (i = 1; i < 3; i++)
	{
	  data5[i] = atoi (strtok (NULL, "/"));
	}
      int e = exist (head, data2);	//check if exist already
      if (e == -1)
	{			//if not, insert in the right place
	  while (head != NULL)
	    {
	      if (head->next == NULL)
		{		//if we reach almost the end, this means that the place is in the end
		  insertAfter (head, data[0], data[1], data2, data[3], data4,
			       data5);
		  printf ("client %s %s added\n", data[0], data[1]);
		  break;
		}
	      else if (data4 < head->debt)
		{		//if it is suppose to be the first
		  insertAfter (head, data[0], data[1], data2, data[3], data4,
			       data5);
		  swap (head, head->next);
		  printf ("client %s %s added\n", data[0], data[1]);
		  break;
		}
	      else if (head->debt < data4
		       && (data4 < head->next->debt || head->next == NULL))
		{		//if the place is in the middle
		  insertAfter (head, data[0], data[1], data2, data[3], data4,
			       data5);
		  printf ("client %s %s added\n", data[0], data[1]);
		  break;
		}
	      head = head->next;
	    }
	}
      else
	{			//if already exist just update
	  update (head, e, data[0], data[1], data[3], data4, data5);
	  bubbleSort (head);	// after we update the debt we need to sort again
	  printf ("client %s %s exist and updated\n", data[0], data[1]);
	}
    }
  else
    {
      printf
	("we can't add this client. some of the data is wrong, please try again\n");
    }
}

//================================
void set (struct Client *head, char line[])
{
  /*VERY IMPORTENT
   * to insert new data  to create new client like this:
   * set first name = John last name = Smith ID = 123456789 phone = 0548412345 debt =345.67 date = 12/12/2012
   * the '=' mark the begining of value
   * date seperadted by '/' ,year with 4 digits*/
  char data[ARR][MAX];
  int i, j, k;
  for (i = 0, k = 0; k < ARR; k++)
    {
      for (; line[i] != '='; i++);
      i++;
      for (; isspace (line[i]); i++);
      for (j = 0;
	   isalnum (line[i]) || line[i] == '.' || line[i] == '+'
	   || line[i] == '-' || line[i] == '/'; i++, j++)
	data[k][j] = line[i];	//here we separate the whole line to 6 different fields
      data[k][j] = '\0';
    }
  check (head, data);		//there is different function for the rest
}

//================================
void searchByName (struct Client *node, char line[])
{
  /*VERY IMPORTENT
   * the right way to insert input is like
   * name = john
   * the '=' mark the begining of value
   * that will print client with that first name or last namr. case sensitive*/
  char name[MAX];
  int i, j;
  for (i = 0; line[i] != '='; i++);
  i++;
  for (; isspace (line[i]); i++);
  for (j = 0; isalpha (line[i]); i++, j++)
    name[j] = line[i];
  name[j] = '\0';		//extract the name from the string
  while (node != NULL)
    {
      if (strcmp (name, node->first) == 0 || strcmp (name, node->last) == 0)
	printf (" %10s | %10s | %d | %10s | %f | %d/%d/%d \n", node->first,
		node->last, node->ID, node->phone, node->debt, node->date.day,
		node->date.month, node->date.year);
      node = node->next;
    }
}

//=====================================
void searchByDebt (struct Client *node, char line[])
{
  /*VERY IMPORTENT
   * the right way to insert input is like
   * debt > 350.78
   * or
   * debt < 432.98
   * or
   * debt = 876.4
   * the '=' or '<' or '>' mark the begining of value*/
  char sign, debt[MAX];
  char *ptr;
  int i, j;
  for (i = 0; line[i] != '<' && line[i] != '>' && line[i] != '='; i++);
  sign = line[i++];
  for (; isspace (line[i]); i++);
  for (j = 0; isdigit (line[i]); i++, j++)
    debt[j] = line[i];
  debt[j] = '\0';
  double d = strtod (debt, &ptr);	//extract the debt from the string
  while (node != NULL)
    {
      if (sign == '<' && node->debt < d)	//print only what below
	printf (" %10s | %10s | %d | %10s | %f | %d/%d/%d \n", node->first,
		node->last, node->ID, node->phone, node->debt, node->date.day,
		node->date.month, node->date.year);
      if (sign == '>' && node->debt > d)	//print only what above
	printf (" %10s | %10s | %d | %10s | %f | %d/%d/%d \n", node->first,
		node->last, node->ID, node->phone, node->debt, node->date.day,
		node->date.month, node->date.year);
      if (sign == '=' && node->debt == d)	//print only what equal
	printf (" %10s | %10s | %d | %10s | %f | %d/%d/%d \n", node->first,
		node->last, node->ID, node->phone, node->debt, node->date.day,
		node->date.month, node->date.year);

      node = node->next;
    }
}

//=====================================
void searchByDate (struct Client *node, char line[])
{
  /* VERY IMPORTENT
   * the right way to insert input is like
   * date > 23/7/1986
   * or
   * date < 14/5/2020
   * the '<' or '>' mark the begining of value*/
  char sign, date[MAX];
  char *ptr;
  int i, j, ok;
  unsigned int d1[3], d2[3];
  for (i = 0; line[i] != '<' && line[i] != '>'; i++);
  sign = line[i++];
  for (; isspace (line[i]); i++);
  for (j = 0; isdigit (line[i]) || line[i] == '/'; i++, j++)
    date[j] = line[i];
  date[j] = '\0';
  ok = badDate (date);		//check if date ok
  if (ok == 1)
    {
      printf ("Illegal date\n");
      return;
    }
  else
    {
      d1[0] = atoi (strtok (date, "/"));
      for (i = 1; i < 3; i++)
	{
	  d1[i] = atoi (strtok (NULL, "/"));	//extract the date from the string
	}
      while (node != NULL)
	{
	  d2[0] = node->date.day;
	  d2[1] = node->date.month;
	  d2[2] = node->date.year;	//extract the date from the node
	  if (sign == '<' && earlier (d2, d1))	//print only what before
	    printf (" %10s | %10s | %d | %10s | %f | %d/%d/%d \n",
		    node->first, node->last, node->ID, node->phone,
		    node->debt, node->date.day, node->date.month,
		    node->date.year);
	  if (sign == '>' && earlier (d1, d2))	//print only what after 
	    printf (" %10s | %10s | %d | %10s | %f | %d/%d/%d \n",
		    node->first, node->last, node->ID, node->phone,
		    node->debt, node->date.day, node->date.month,
		    node->date.year);
	  node = node->next;
	}
    }
}

//================================
void printList (struct Client *node)
{
  while (node != NULL)		//Traverse on the list and print it
    {
      printf (" %10s | %10s | %d | %10s | %f | %d/%d/%d \n", node->first,
	      node->last, node->ID, node->phone, node->debt, node->date.day,
	      node->date.month, node->date.year);
      node = node->next;
    }
}
