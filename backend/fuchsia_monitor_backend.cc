// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/*
* date_proc.c - remote procedures; called by server stub.
*/
#include <time.h>
#include <sys/types.h>
#include <malloc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pwd.h>
#include <iostream>

#define MAX_LEN 1000

char **date_1(long *option);

int main()
{
  std::cout << "Hello, I'm the backend Fuchsia Monitor!\n";
  long option = 3;
  char* response = *date_1(&option);
  
  std::cout << "Option #" << option << ": " << response << "\n.";
  
  return 0;
}
/*
* Return the binary date and time.
*/
char **date_1(long *option)
{
  struct tm *timeptr; /* Pointer to time structure */
  time_t clock;       /* Clock value (in secs) */
  static char *ptr;   /* Return string */
  static char err[] = "Invalid Response \0";
  static char s[MAX_LEN];
  clock = time(0);
  timeptr = localtime(&clock);

  switch (*option)
  {
  case 1:
    strftime(s, MAX_LEN, "%A, %B %d, %Y", timeptr);
    ptr = s;
    break;
  case 2:
    strftime(s, MAX_LEN, "%T", timeptr);
    ptr = s;
    break;
  case 3:
    strftime(s, MAX_LEN, "%A, %B %d, %Y - %T", timeptr);
    ptr = s;
    break;
  default:
    ptr = err;
    break;
  }
  return (&ptr);
}

