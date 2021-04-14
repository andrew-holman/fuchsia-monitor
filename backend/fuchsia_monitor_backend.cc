// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/*
* date_proc.c - remote procedures; called by server stub.
*/
#include <rpc/rpc.h>
#include <time.h>
#include <sys/types.h>
#include "date.h"
#include <linux/kernel.h>
#include <sys/sysinfo.h>
#include <malloc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pwd.h>
#include <iostream>

struct mallinfo mallinfo(void);
long get_phys_pages(void);
long get_avphys_pages(void);
int sysinfo(struct sysinfo *info);
int getpagesize(void);
struct passwd *fgetpwent(FILE *stream);

#define MAX_LEN 1000

int main()
{
  std::cout << "Hello, I'm the backend Fuchsia Monitor!\n";
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

/*
* Return the binary cpu usage data
*/
char **cpu_1(long *option)
{
  struct sysinfo info;
  static char *ptr; /* Return string */
  static char err[] = "Invalid Response \0";
  static char s[MAX_LEN];

  // Constants used for conversions:
  const long minute = 60;
  const long hour = minute * 60;
  const long day = hour * 24;
  const double megabyte = 1024 * 1024;

  switch (*option)
  {
  case 1:
    sysinfo(&info);
    sprintf(s, "System Uptime: %ld days, %ld hours, %02ld minutes, and %02ld seconds\n", info.uptime / day, (info.uptime % day) / hour, (info.uptime % hour) / minute, info.uptime % minute);
    ptr = s;
    break;
  case 2:;
    double load[3];
    getloadavg(load, 3);
    sprintf(s, "1 Minute Load Average: %.2lf\n 5 Minute Load Average: %.2lf\n 1 Minute Load Average: %.2lf\n", load[0], load[1], load[2]);
    ptr = s;
    break;
  case 3:
    sysinfo(&info);
    sprintf(s, "Total Ram: %ld\n Free Ram: %ld\n Shared Ram: %ld\n Buffer Ram: %ld\n", info.totalram, info.freeram, info.sharedram, info.bufferram);
    ptr = s;
    break;
  case 4:
    sysinfo(&info);
    sprintf(s, "Total Swap: %ld\n Free Swap: %ld\n", info.totalswap, info.freeswap);
    ptr = s;
    break;
  case 5:
    sysinfo(&info);
    sprintf(s, "NUM Processes: %d\n", info.procs);
    ptr = s;
    break;
  default:
    ptr = err;
    break;
  }
  return (&ptr);
}

/*
* Return the binary memory usage data.
*/
char **mem_1(long *option)
{
  static char *ptr; /* Return string */
  static char err[] = "Invalid Response \0";
  static char s[MAX_LEN];

  switch (*option)
  {
  case 1:;
    struct mallinfo mall_info = mallinfo();
    sprintf(s, "Non-mapped allocated spasce: %d\n NUM Free Chunks: %d\n NUM Free Fastbin Blocks: %d\n NUM Mmapped Regions: %d\n Space Allocated to Mmapped Regions: %d bytes\n Space of Freed Fastbin Blocks: %d bytes\n Total Allocated Space: %d bytes\n Total Free Space: %d bytes\n Top-most Releaseable Space: %d\n", mall_info.arena, mall_info.ordblks, mall_info.smblks, mall_info.hblks, mall_info.hblkhd, mall_info.fsmblks, mall_info.uordblks, mall_info.fordblks, mall_info.keepcost);
    ptr = s;
    break;
  case 2:;
    sprintf(s, "Page Size of Process: %ld bytes\n", getpagesize());
    ptr = s;
    break;
  case 3:;
    sprintf(s, "Total Pages of Physical Memory: %ld\n Available Pages of Physical Memory: %ld\n", get_phys_pages(), get_avphys_pages());
    ptr = s;
    break;
  default:
    ptr = err;
    break;
  }
  return (&ptr);
}

/*
* Return the binary about user reports
*/
char **report_1(long *option)
{
  static char *ptr; /* Return string */
  static char err[] = "Invalid Response \0";
  static char s[MAX_LEN];

  // Local variables that are used in multiple cases
  int fd1[2];
  pid_t pid;
  FILE *userFile;
  struct passwd *userInfo;

  switch (*option)
  {
  case 1:;
    sprintf(s, "");
    pid = fork();
    if (pid == 0)
    {
      close(fd1[0]);
      dup2(fd1[1], 1);
      execlp("iostat", "iostat", "-c", NULL);
    }
    else
    {
      close(fd1[1]);
      wait(NULL);
      read(fd1[0], s, MAX_LEN);
      close(fd1[0]);
      dup2(1, 1);
    }
    ptr = s;
    break;
  case 2:;
    sprintf(s, "");
    pid = fork();
    if (pid == 0)
    {
      close(fd1[0]);
      dup2(fd1[1], 1);
      execlp("iostat", "iostat", "-d", NULL);
    }
    else
    {
      close(fd1[1]);
      wait(NULL);
      read(fd1[0], s, MAX_LEN);
      close(fd1[0]);
      dup2(1, 1);
    }
    ptr = s;
    break;
  case 3:;
    sprintf(s, "");
    pid = fork();
    if (pid == 0)
    {
      close(fd1[0]);
      dup2(fd1[1], 1);
      execlp("iostat", "iostat", NULL);
    }
    else
    {
      close(fd1[1]);
      wait(NULL);
      read(fd1[0], s, MAX_LEN);
      close(fd1[0]);
      dup2(1, 1);
    }
    ptr = s;
    break;
  case 4:;
    userFile = fopen("/etc/passwd", "r");
    int count = 1;
    sprintf(s, "User Name List:\n");
    while (1)
    {
      userInfo = fgetpwent(userFile);
      if (userInfo == NULL)
      {
        break;
      }
      sprintf(s, "%s %d. %s\n", s, count, userInfo->pw_name);
      count++;
    }
    fclose(userFile);
    ptr = s;
    break;
  default:
    ptr = err;
    break;
  }
  return (&ptr);
}