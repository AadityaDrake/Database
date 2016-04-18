#include <stdio.h>
#include <stdlib.h>
#include "db.h"
#include <string.h>

attend_rec db[100],ar;
int db_size = 0;

/* reset the database for testing */
int clear_db()
{
  db_size = 0;
  return TRUE;
}

/*
  Story 1: As a teacher, I want a user interface for my database.
*/

int is_whitespace(char c) {
  return (' ' == c || '\t' == c || '\n' == c);
}

char get_first_non_white(char *s) {
  for (int i = 0; '\0' != s[i] && i < 80; i++) {
    if (!is_whitespace(s[i])) {
      return(s[i]);
    }
  }
  return('\0');
}

char get_command()
{
  char buffer[80];
  
  printf("Enter operator> ");
  scanf("%80s", buffer);
  return get_first_non_white(buffer);
}

// Returns FALSE when 'x' enter; TRUE otherwise
int execute_command(char c)
{
  int sno;
  attend_rec ar;
  
  switch (c) {
  case 'a':
    scanf_attend(&ar);
    add(ar);
    printf_attend(ar);
    return TRUE;
  case 'l':
    list();
    return TRUE;
  case 'i':
    initialize_db();
    return TRUE;
  case 'f':
    sno = get_sno();
    ar = find(sno);
    if (ar.sno == -1) {
      printf("Student %d not found\n", sno);
    } else {
      printf_attend(ar);
    }
    return TRUE;
  case 'm':
    scanf_attend(&ar);
    modify(ar);
    return TRUE;
  case 'd':
    sno = get_sno();
    delete(sno);
    return TRUE;
  case 'x':
    return FALSE;
  default:
    printf("Invalid command\n");
    return TRUE;
  }
}

/*
  Story 2: As a teacher, I want to add a student to my database, so I
  can track his or her record.
*/

void scanf_attend(attend_rec *r)
{
	printf("Enter S.No> ");
	scanf("%d",&r->sno);
	printf("Enter Name >");
	scanf("%s",r->name);
	printf("Enter Attendance >");
	scanf("%d",&r->present);
}

void printf_attend(attend_rec r)
{
	char *y;
	y=(r.present==1?"present":"absent");
	printf("Sno\tName\tAttendance\t\n");
	printf("%d\t",r.sno);
	printf("%s\t %s\t",r.name,y);
	printf("\n");
}

int add(attend_rec r)
{
	db[db_size++]=r;
	return TRUE;
}

/*
  Story 3: As a teacher, I want to be see all of the students in my
  class, so I can see who is present and absent.
 */

void list()
{
	printf("Sno.\tName\tAttendance\n");
	for(int o=0;o<db_size;o++)
	{
		printf("%d\t",db[o].sno);
		printf("%s\t",db[o].name);
		if(db[o].present==1)
			printf("present\t\n");
		else
			printf("absent\t\n");
	}
	printf("\n");
}

/* 
   Story 4: As a programmer, I want to add a set of records to my
   database for testing purposes.
*/

void initialize_db()
{
	attend_rec ar;
	int i;
	db_size=0;
	for(i=0;i<10;i++)
	{
		ar.sno = i;
      		strcpy(ar.name,"student");
		ar.present=1;
		add(ar);
	}
}

/*
  Story 5: As a teacher, I want to be find a student's record so I can
  see whether a student was present or absent for a class.
*/

// We need a special record to return when the one we are looking for
// is not found
attend_rec not_found = {.sno = -1,
			.name = "none",
			.present = -1};

// Prompt the user for a serial number and read from keyboard
int get_sno()
{
	int a;
	printf("Enter an integer>\n");
	scanf("%d",&a);
	return a;
}

attend_rec find(int sno)
{
	int i;
	for(i=0;i<db_size;i++)
	{
		if(sno==db[i].sno)
			return db[i];
	}
	return not_found;
}

/*
  Story 6: As a teacher, I want to modify a student's record, so I can
  correct mistakes.
*/

int modify(attend_rec r)
{
	int i;
	for(i=0;i<db_size;i++)
	{
		if(r.sno==db[i].sno)
		{
			strcpy(db[i].name,r.name);
			db[i].present=r.present;
			return TRUE;
		}
	}
	return FALSE;
}

/*
  Story 7: As a teacher, I want to delete a student's record, so I can
  drop a student from the class.
*/

int find_index(int sno)
{
	for(int i=0;i<db_size;i++)
	{
		if(sno==db[i].sno)
			return i;
	}
	return -1;
}

int delete(int sno)
{
	int i=0;
	i=find_index(sno);
	if(i<0)
		return FALSE;
	for(;i<db_size-1;i++)
		db[i]=db[i+1];
	db_size--;
	return TRUE;
}
