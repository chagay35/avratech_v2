#define MAX 12
#define ARR 6

struct Date
{
  unsigned int day;
  unsigned int month;
  unsigned int year;
};

struct Client
{
  char first[MAX];
  char last[MAX];
  unsigned int ID;
  char phone[MAX];
  double debt;
  struct Date date;
  struct Client *next;
};

//=== vaidation functions, in vaidation_functions.c ===
bool badFirst (char value[]);
bool badLast (char value[]);
bool badId (char value[]);
bool badPhone (char value[]);
bool badDebt (char value[]);
bool badDate (char[]);
//=== query functions, in query_functions.c ===
void set (struct Client *head, char line[]);
void check (struct Client *head, char data[][MAX]);
void insertAfter (struct Client *prev_node, char first[], char last[],
		  unsigned int id, char phone[], double debt,
		  unsigned int tm[]);
void searchByName (struct Client *node, char line[]);
void searchByDebt (struct Client *node, char line[]);
void searchByDate (struct Client *node, char line[]);
void printList (struct Client *node);
//=== prototypes of all other functions, in main.c ===
bool readfile (char path[]);
int exist (struct Client *node, int id);
void append (struct Client **head_ref, char first[], char last[],
	     unsigned int id, char phone[], double debt, unsigned int tm[]);
void update (struct Client *node, int num, char first[], char last[],
	     char phone[], double debt, unsigned int tm[]);
bool earlier (unsigned int t1[], unsigned int t2[]);
void bubbleSort (struct Client *start);
void swap (struct Client *a, struct Client *b);
void quit (struct Client *node, char path[]);
void deleteList (struct Client **head_ref);
