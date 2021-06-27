#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user
{
  char username[100];
  int id;
  int register_year;
};

struct user server[] =
{
    "jesse", 2312, 2021,
    "annk", 4331, 2021,
    "oroboros", 3952, 2017,
    "dokuro", 4316, 2019,
    "kkjus", 5332, 2011,
    "marvest", 9912, 2010,
    "eillek", 1092, 2020,
    "tuomas", 1292, 2015,
    "marko", 4131, 2016,
    "tarja", 1314, 2014
};

/*
  TODO
  @function compare_username
  @desc     compares username of two user records.
*/
int compare_username(const void *a, const void *b)
{
  char i[100];                             //declarar variables
  strcpy(i, ((struct user *)a)->username); //casteamos a
  char j[100];
  strcpy(j, ((struct user *)b)->username); //(void* es una caja negra y (struct user* para decir que es un struct tipo user))
  //strcpy para guardar
  int result = strcmp(i, j); //es lo mismo que un strcmp
                             //-1 si el primero es >
                             //0 =
                             //1 si el segundo >
  return result;             // return result porque tiene el valor del resultado
}

/*
  TODO
  @function compare_id
  @desc     compares id of two user records.
*/
int compare_id(const void *a, const void *b)
{
  int i = (((struct user *)a)->id);
  int j = (((struct user *)b)->id);
  if (i > j)
  {
    return 1;
  }
  if (i == j)
  {
    return 0;
  }

  return -1;
}

/*
  TODO
  @function compare_register_year
  @desc     compares register date of two user records.
*/
int compare_register_year(const void *a, const void *b)
{
  int i = (((struct user *)a)->register_year);
  int j = (((struct user *)b)->register_year);
  if (i > j)
    return 1;
  else if (i == j)
    return 0;
  return -1;
}

/* 
  @function printrec
  @desc     prints user record
*/
void printrec(void *prec, void *arg)
{
  struct user *pstud = (struct user *)prec;
  printf("%-20s %d %d\n", pstud->username, pstud->id, pstud->register_year);
}

/*!
  @function apply
  @desc     applies
 */
void apply(struct user *sarr, int nrec, void (*fp)(void *prec, void *arg), void *arg)
{
  int i = 0;
  for (i = 0; i < nrec; i++)
  {
    /*callback*/
    fp(&sarr[i], arg);
  }
}

/* 
  @function isolder
  @desc     prints user record only if the user register is older than *((int*)arg)
*/
void isolder(void *prec, void *arg)
{
  struct user *pstud = (struct user *)prec;
  int age = *(int*)arg;
  if((2021 - pstud->register_year) > age)
  {
    printf("%-20s %d %d\n", pstud->username, pstud->id, pstud->register_year);
  }
}

int main()
{
  int nusers = sizeof(server) / sizeof(struct user);
  int age;//se agrega age
  char term; // Used to read the \n in scanf()
  puts("-------------------------------");
  puts("All user records:");
  puts("-------------------------------");
  apply(server, nusers, printrec, NULL);

  /*sort based on username*/
  puts("-------------------------------");
  puts("Sorted by username:");
  puts("-------------------------------");
  qsort(server, nusers, sizeof(struct user), compare_username);
  apply(server, nusers, printrec, NULL);

  /*sort based on ID*/
  puts("-------------------------------");
  puts("Sorted by ID:");
  puts("-------------------------------");
  qsort(server, nusers, sizeof(struct user), compare_id);
  apply(server, nusers, printrec, NULL);

  /*sort based on register date */
  puts("-------------------------------");
  puts("Sorted by register date:");
  puts("-------------------------------");
  qsort(server, nusers, sizeof(struct user), compare_register_year);
  apply(server, nusers, printrec, NULL);

  /*print people older than n*/
  puts("-------------------------------");
  puts("People older than n:");
  // TODO: request user input
  puts("-------------------------------");
  printf("Enter the number of years since the user is active: ");
  if(scanf("%d%c", &age, &term) != 2 || term != '\n')
  {
    printf("Value entered not valid. Exiting program.\n");
    exit(0);
  }
  else
  {
    apply(server, nusers, isolder, &age);
  }
  puts("-------------------------------");
  return 0;
}
