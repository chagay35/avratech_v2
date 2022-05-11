/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shop.h"

#define BUFF 100
#define BUFFER 1024

//=== global variables ===
struct Client *head = NULL;
bool (*chekArr[ARR]) (char[]);
enum columns { FIRST_NAME, LAST_NAME, ID_NUM, PHONE_NUM, DEBT_SUM, DATE_START };
//================================
int main (int argc, char *argv[])
{
  chekArr[FIRST_NAME] = badFirst;
  chekArr[LAST_NAME] = badLast;
  chekArr[ID_NUM] = badId;
  chekArr[PHONE_NUM] = badPhone;
  chekArr[DEBT_SUM] = badDebt;
  chekArr[DATE_START] = badDate;
  bool fileOk = readfile (argv[1]);	//path came from arguments' vector "Untitled1.csv.xlsx"
  bubbleSort (head);		//sorting the linked list we created
  printList (head);
  //=====================
  char order[MAX];
  char *buffer = NULL;
  size_t bufsize = BUFF;
  int i, j;
  while (fileOk)		//if file been read, until order to stop, taking orders from user
    {
      printf ("\n===>");
      getline (&buffer, &bufsize, stdin);
      for (i = 0; isspace (buffer[i]); i++);
      for (j = 0; isalnum (buffer[i]); i++, j++)
	order[j] = buffer[i];
      order[j] = '\0';
      if (strcmp (order, "quit") == 0 || strcmp (order, "quit\n") == 0)
	{
	  break;
	}
      else if (strcmp (order, "set") == 0 || strcmp (order, "set\n") == 0)
	{
	  set (head, buffer);
	  /*VERY IMPORTENT
	   * to insert new data  to create new client like this:
	   * set first name = John last name = Smith ID = 123456789 phone = 0548412345 debt =345.67 date = 12/12/2012
	   * the '=' mark the begining of value
	   * date seperadted by '/' ,year with 4 digits*/
	}
      else if (strcmp (order, "name") == 0 || strcmp (order, "name\n") == 0)
	{
	  searchByName (head, buffer);
	  /*VERY IMPORTENT
	   * the right way to insert input is like
	   * name = john
	   * the '=' mark the begining of value
	   * that will print client with that first name or last namr. case sensitive*/
	}
      else if (strcmp (order, "debt") == 0 || strcmp (order, "debt\n") == 0)
	{
	  searchByDebt (head, buffer);
	  /*VERY IMPORTENT
	   * the right way to insert input is like
	   * debt > 350.78
	   * or
	   * debt < 432.98
	   * or
	   * debt = 876.4
	   * the '=' or '<' or '>' mark the begining of value*/
	}
      else if (strcmp (order, "date") == 0 || strcmp (order, "date\n") == 0)
	{
	  searchByDate (head, buffer);
	  /* VERY IMPORTENT
	   * the right way to insert input is like
	   * date > 23/7/1986
	   * or
	   * date < 14/5/2020
	   * the '<' or '>' mark the begining of value*/
	}
      else if (strcmp (order, "print") == 0 || strcmp (order, "print\n") == 0)
	{
	  printList (head);	//print the list os clients
	}
    }
  free (buffer);
  quit (head, argv[1]);		//free all dynamic allocated memory
  //"Untitled1.csv.xlsx"
  return 0;
}

//================================
bool readfile (char path[])
{
  char tempfirst[MAX], data[ARR][MAX];
  char templast[MAX], t[MAX];
  unsigned int tempID, td[3];
  char tempPhone[MAX];
  double tempDebt;
  int tempok;

  FILE *fp;

  if (!(fp = fopen (path, "r")))
    {
      printf ("Can't open file to read\n");
      return false;
    }

  else
    {
      // Here we have taken size of
      // array 1024 you can modify it
      char buffer[BUFFER];

      int row = 0;
      int column = 0;

      while (fgets (buffer, BUFFER, fp))
	{
	  column = 0;
	  row++;
	  // To avoid printing of column names in file can be changed according to need
	  //if (row == 1)
	  //    continue;

	  // Splitting the data
	  char *value = strtok (buffer, ", ");
	  tempok = 0;
	  while (value)
	    {

	      switch (column)
		{
		  // Column 1
		case FIRST_NAME:
		  {
		    bool wrong = chekArr[column] (value);
		    if (wrong == false)
		      {
			strcpy (tempfirst, value);
			strcpy (data[column], value);
			tempok++;
		      }
		    break;
		  }
		  // Column 2
		case LAST_NAME:
		  {
		    bool wrong = chekArr[column] (value);
		    if (wrong == false)
		      {
			strcpy (templast, value);
			strcpy (data[column], value);
			tempok++;
		      }
		    break;
		  }
		  // Column 3
		case ID_NUM:
		  {
		    bool wrong = chekArr[column] (value);
		    if (wrong == false)
		      {
			tempID = atoi (value);
			strcpy (data[column], value);
			tempok++;
		      }
		    break;
		  }
		  // Column 4
		case PHONE_NUM:
		  {
		    bool wrong = chekArr[column] (value);
		    if (wrong == false)
		      {
			strcpy (tempPhone, value);
			strcpy (data[column], value);
			tempok++;
		      }
		    break;
		  }
		  // Column 5
		case DEBT_SUM:
		  {
		    bool wrong = chekArr[column] (value);
		    char *ptr;
		    if (wrong == false)
		      {
			tempDebt = strtod (value, &ptr);
			strcpy (data[column], value);
			tempok++;
		      }
		    break;
		  }
		  // Column 6
		case DATE_START:
		  {
		    int i;
		    bool wrong = chekArr[column] (value);
		    if (wrong == false)
		      {
			strcpy (t, value);
			td[0] = atoi (strtok (t, "/"));
			for (i = 1; i < 3; i++)
			  {
			    td[i] = atoi (strtok (NULL, "/"));
			  }
			strcpy (data[column], value);
			tempok++;
		      }
		    break;
		  }
		default:
		  break;
		}
	      value = strtok (NULL, ", ");
	      column++;
	    }
	  if (tempok == ARR)
	    {			//if all columns in this row are ok then:
	      int e = exist (head, tempID);	//check if ID already exist in the list
	      if (e == -1)
		{		//if not - append to list
		  append (&head, tempfirst, templast, tempID, tempPhone,
			  tempDebt, td);
		}
	      else		//if this ID already, just update this node
		update (head, e, tempfirst, templast, tempPhone, tempDebt,
			td);
	    }
	}

      // Close the file
      fclose (fp);
    }
  return true;
}

//================================
int exist (struct Client *node, int id)
{
  int i = 0;
  while (node != NULL)		//Traverse on the list to check for the id. if exist return its location,else -1
    {
      if (node->ID == id)
	return i;
      node = node->next;
      i++;
    }
  return -1;
}

//================================
void append (struct Client **head_ref, char first[], char last[], unsigned int id,
	char phone[], double debt, unsigned int tm[])
{
  /* 1. allocate node */
  struct Client *new_node = (struct Client *) malloc (sizeof (struct Client));
  if (new_node == NULL)
    {
      printf ("malloc in append failed\n");
      return;
    }
  struct Client *lastNode = *head_ref;	/* used in step 5 */

  /* 2. put in the data  */
  //new_node->data  = new_data;
  strcpy (new_node->first, first);
  strcpy (new_node->last, last);
  new_node->ID = id;
  strcpy (new_node->phone, phone);
  new_node->debt = debt;
  new_node->date.day = tm[0];
  new_node->date.month = tm[1];
  new_node->date.year = tm[2];

  /* 3. This new node is going to be the last node, so make next of it as NULL */
  new_node->next = NULL;

  /* 4. If the Linked List is empty, then make the new node as head */
  if (*head_ref == NULL)
    {
      *head_ref = new_node;
      return;
    }

  /* 5. Else traverse till the last node */
  while (lastNode->next != NULL)
    lastNode = lastNode->next;

  /* 6. Change the next of last node */
  lastNode->next = new_node;
  return;
}

//================================
void update (struct Client *node, int num, char first[], char last[], char phone[],
	double debt, unsigned int tm[])
{
  //if already exist client with this ID we traverse to its location and update the data
  int i;
  bool c;
  unsigned int t[3];
  for (int i = 0; i < num; i++)
    {				//traverse
      node = node->next;
    }
  strcpy (node->first, first);
  strcpy (node->last, last);
  strcpy (node->phone, phone);
  node->debt += debt;		//add debt
  t[0] = node->date.day;
  t[1] = node->date.month;
  t[2] = node->date.year;
  c = earlier (tm, t);		//set the earlier date
  if (c == true)
    {
      node->date.day = tm[0];
      node->date.month = tm[1];
      node->date.year = tm[2];
    }
}

//================================
bool earlier (unsigned int t1[], unsigned int t2[])
{
  /* if year is earlier no need to check month
   * if month is earlier no need to check day
   * if day is earlier - t1 is earlier the t2
   * */
  int i;
  for (i = 2; i >= 0; i--)
    {
      if (t1[i] < t2[i])
	return true;
      if (t1[i] > t2[i])
	return false;
    }
  return false;
}

//================================
/* Bubble sort the given linked list */
void bubbleSort (struct Client *start)
{
  int swapped, i;
  struct Client *ptr1;
  struct Client *lptr = NULL;

  /* Checking for empty list */
  if (start == NULL)
    return;

  do
    {
      swapped = 0;
      ptr1 = start;

      while (ptr1->next != lptr)
	{
	  if (ptr1->debt > ptr1->next->debt)
	    {
	      swap (ptr1, ptr1->next);
	      swapped = 1;
	    }
	  ptr1 = ptr1->next;
	}
      lptr = ptr1;
    }
  while (swapped);
}

//=====================================
/* function to swap data of two nodes a and b*/
void swap (struct Client *a, struct Client *b)
{
  //int temp = a->data;
  char tempfirst[MAX];
  char templast[MAX], t[MAX];
  unsigned int tempID = a->ID, d = a->date.day, m = a->date.month, y =
    a->date.year;
  char tempPhone[MAX];
  double tempDebt = a->debt;
  strcpy (tempfirst, a->first);
  strcpy (templast, a->last);
  strcpy (tempPhone, a->phone);

  //a->data = b->data;
  strcpy (a->first, b->first);
  strcpy (a->last, b->last);
  a->ID = b->ID;
  strcpy (a->phone, b->phone);
  a->debt = b->debt;
  a->date.day = b->date.day;
  a->date.month = b->date.month;
  a->date.year = b->date.year;

  //b->data = temp;
  strcpy (b->first, tempfirst);
  strcpy (b->last, templast);
  b->ID = tempID;
  strcpy (b->phone, tempPhone);
  b->debt = tempDebt;
  b->date.day = d;
  b->date.month = m;
  b->date.year = y;
}

//================================
void quit (struct Client *node, char path[])	//to close the program nicely
{
  FILE *fp;
  if (!(fp = fopen (path, "w")))
    {
      // Error in file opening
      printf ("Can't open file to write\n");
      return;
    }
  while (node != NULL)		//write back to file
    {
      fprintf (fp, "%s, %s, %d, %s, %f, %d/%d/%d\n", node->first, node->last,
	       node->ID, node->phone, node->debt, node->date.day,
	       node->date.month, node->date.year);
      node = node->next;
    }
  fclose (fp);
  deleteList (&node);
  printf ("\n\tgoodbye");
  exit (0);
}

//================================
/* Function to delete the entire linked list */
void deleteList (struct Client **head_ref)
{
  /* deref head_ref to get the real head */
  struct Client *current = *head_ref;
  struct Client *next;

  while (current != NULL)
    {
      next = current->next;
      free (current);
      current = next;
    }

  /* deref head_ref to affect the real head back in the caller. */
  *head_ref = NULL;
}
