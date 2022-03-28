#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define MAX_BUFFER 1024    // max line buffer
#define MAX_ARGS 64        // max # args
#define SEPARATORS " \t\n" // token sparators
#define README "readme"    // help file name

struct shellstatus_st
{
    int foreground;  // foreground execution flag
    char *infile;    // input redirection flag & file
    char *outfile;   // output redirection flag & file
    char *outmode;   // output redirection mode
    char *shellpath; // full pathname of shell
};
typedef struct shellstatus_st shellstatus;

extern char **environ;

void check4redirection(char **, shellstatus *); // check command line for i/o redirection
void errmsg(char *, char *);                    // error message printout
void execute(char **, shellstatus);             // execute command from arg array
char *getcwdstr(char *, int);                   // get current work directory string
FILE *redirected_op(shellstatus);               // return required o/p stream
char *stripath(char *);                         // strip path from filename
void syserrmsg(char *, char *);                 // system error message printout

/*******************************************************************/

int main(int argc, char **argv)
{
    FILE *ostream = stdout;   // (redirected) o/p stream
    FILE *instream = stdin;   // batch/keyboard input
    char linebuf[MAX_BUFFER]; // line buffer
    char cwdbuf[MAX_BUFFER];  // cwd buffer
    char *args[MAX_ARGS];     // pointers to arg strings
    char **arg;               // working pointer thru args
    char *prompt = "==>";     // shell prompt
    char *readmepath;         // readme pathname
    shellstatus status;       // status structure
    int execargs;             // execute command in args

    // parse command line for batch input
    switch (argc)
    {
    case 1:
    {
        // keyboard input
        // TODO
        // check if the shell name is correct
        if(strcmp(argv[0], "./myshell")) {
            errmsg("Unexpected shell name!", NULL);
            exit(-1);
        }
        break;
    }

    case 2:
    {
        // possible batch/script
        // TODO
        // Check if the shell name is correct
        if(strcmp(argv[0], "./myshell")) {
            errmsg("Unexpected shell name!", NULL);
            exit(-1);
        }

        // check the access to the batch file
        // existence
        if(access(argv[1], 0)) {
            errmsg("The batch file doesn't exist!", NULL);
            exit(-1);
        }
        // readable
        if(access(argv[1], 4)) {
            errmsg("Cannot read the batch file!", NULL);
            exit(-1);
        }
        // open
        instream = fopen(argv[1], "r");
        if(!instream) {
            syserrmsg("Cannot open the batch file!", NULL);
            exit(-1);
        }
        break;
    }
    default: // too many arguments
        fprintf(stderr, "%s command line error; max args exceeded\n"
                        "usage: %s [<scriptfile>]\n",
                stripath(argv[0]), stripath(argv[0]));
        exit(1);
    }

    // get starting cwd to add to readme pathname
    // TODO
    // malloc space for readme path
    readmepath = (char*) malloc(MAX_BUFFER);
    // don't forget initialization
    memset(cwdbuf, '\0', sizeof(cwdbuf));
    getcwd(cwdbuf, MAX_BUFFER);
    strcpy(readmepath, cwdbuf);
    // don't forget to add suffix
    strcat(readmepath, "/");
    strcat(readmepath, README);

    // get starting cwd to add to shell pathname
    // TODO
    // malloc space for shell path
    status.shellpath = (char*) malloc(MAX_BUFFER);
    strcpy(status.shellpath, cwdbuf);
    // don't forget to add suffix
    strcat(status.shellpath, "/");
    strcat(status.shellpath, "myshell");

    // set SHELL= environment variable, malloc and store in environment
    // TODO
    if(setenv("shell", status.shellpath, 1)) {
        syserrmsg("Cannot set environment variable: shell path!", NULL);
    }

    // prevent ctrl-C and zombie children
    signal(SIGINT, SIG_IGN);  // prevent ^C interrupt
    signal(SIGCHLD, SIG_IGN); // prevent Zombie children

    // keep reading input until "quit" command or eof of redirected input
    while (!feof(instream))
    {
        // do initialization
        for(int i = 0; i < MAX_ARGS; ++i) {
            args[i] = NULL;
        }
        memset(linebuf, '\0', sizeof(linebuf));
        memset(cwdbuf, '\0', sizeof(cwdbuf));
        getcwd(cwdbuf, MAX_BUFFER);
        
        // (re)initialise status structure
        status.foreground = TRUE;

        // set up prompt
        // TODO
        fputs(cwdbuf, stdout); // write working directory
        fputs(prompt, stdout); // write prompt
        fflush(stdout);

        // get command line from input
        if (fgets(linebuf, MAX_BUFFER, instream))
        {
            // read a line
            // tokenize the input into args array
            arg = args;
            *arg++ = strtok(linebuf, SEPARATORS); // tokenize input
            while ((*arg++ = strtok(NULL, SEPARATORS)))
                ;

            // last entry will be NULL
            if (args[0])
            {
                // check for i/o redirection
                check4redirection(args, &status);
                execargs = TRUE; // set default execute of args

                // check for internal/external commands
                // "cd" command
                if (!strcmp(args[0], "cd"))
                {
                    // TODO
                    ostream = redirected_op(status);
                    // no directory
                    if(!args[1]) {
                        //getcwd(cwdbuf, MAX_BUFFER);
                        fprintf(ostream, "%s\n", cwdbuf);
                    }
                    else {
                        if(chdir(args[1])) {
                            syserrmsg(NULL, NULL);
                        }
                        else {
                            // get new PWD and set
                            getcwd(cwdbuf, MAX_BUFFER);
                            if(setenv("PWD", cwdbuf, 1)) {
                                syserrmsg(NULL, NULL);
                            }
                        }
                    }
                    execargs = FALSE; // no need for further exec
                    
                }
                // "clr" command
                else if (!strcmp(args[0], "clr"))
                {
                    // TODO
                    args[0] = "clear";
                    args[1] = NULL;
                }
                // "dir" command
                else if (!strcmp(args[0], "dir"))
                {
                    // TODO
                    // no directory = current directory
                    if(!args[1]) {
                        args[2] = ".";
                    }
                    else args[2] = args[1];
                    args[0] = "ls";
                    args[1] = "-al";
                    args[3] = NULL;
                }
                // "echo" command
                else if (!strcmp(args[0], "echo"))
                {
                    // TODO
                    // malloc space for echo comment and initialization
                    char * comment = (char *) malloc(MAX_BUFFER);
                    memset(comment, '\0', MAX_BUFFER);
                    
                    // read input from file
                    if(status.infile != NULL) {
                        FILE * fp = fopen(status.infile, "r");
                        char * line = (char *) malloc(MAX_BUFFER);
                        while(fgets(line, MAX_BUFFER, fp)) {
                            strcat(comment, line);
                            memset(line, '\0', MAX_BUFFER);
                        }
                        fclose(fp);
                        free(line);
                    }
                    // read input from args
                    else {
                        int i = 0;
                        while(args[i]) {
                            // set actual end afer the last argument for execution
                            // can't include i/o redirection flag in execution arguments
                            if(!strcmp(args[i], "<") || !strcmp(args[i], ">") || !strcmp(args[i], ">>") || !strcmp(args[i], "&")) {
                                args[i] = NULL;
                                break;
                            }
                            //else printf("the current args is: %s\n", args[i]);
                            ++i;
                        }
                        // check if NULL input
                        if(args[1]) {
                            strcat(comment, args[1]);
                            int i = 2;
                            while(args[i]) {
                                strcat(comment, " ");
                                strcat(comment, args[i]);
                                ++i;
                            }
                        }
                    }

                    ostream = redirected_op(status); // decide ostream

                    if(fprintf(ostream, "%s\n", comment) < 0) {
                        errmsg("Echo command failed to write!", status.outfile);
                    }
                    execargs = FALSE; // no need for further exec
                    free(comment); // don't forget to free space
                    
                }
                // "environ" command
                else if (!strcmp(args[0], "environ"))
                {
                    // TODO
                    char **envstr = environ;
                    ostream = redirected_op(status);

                    while (*envstr)
                    { 
                        // print out environment
                        fprintf(ostream, "%s\n", *envstr);
                        envstr++;
                    }
                    execargs = FALSE;
                }
                // "help" command
                else if (!strcmp(args[0], "help"))
                {
                    args[0] = "more";
                    args[1] = readmepath;
                    args[2] = NULL;
                }
                // "pause" command - note use of getpass - this is a made to measure way of turning off
                //  keyboard echo and returning when enter/return is pressed
                else if (!strcmp(args[0], "pause"))
                {
                    // TODO
                    char * password;
                    password = (char *) malloc(MAX_BUFFER);
                    password = getpass("Press Enter to continue ...");
                    free(password);
                    continue; // go to new round
                }
                // "quit" command
                else if (!strcmp(args[0], "quit"))
                {
                    break;
                }
                // else pass command on to OS shell
                // TODO
                if(execargs) {
                    int i = 0;
                    while(args[i]) {
                        // set actual end afer the last argument for execution
                        // can't include i/o redirection flag in execution arguments
                        if(!strcmp(args[i], "<") || !strcmp(args[i], ">") || !strcmp(args[i], ">>") || !strcmp(args[i], "&")) {
                            args[i] = NULL;
                            break;
                        }
                        //else printf("the current args is: %s\n", args[i]);
                        ++i;
                    }
                    execute(args, status);
                }
            }
        }
    }
    // don't forget to free space
    free(readmepath);
    free(status.shellpath);
    
    return 0;
}

/***********************************************************************

void check4redirection(char ** args, shellstatus *sstatus);

check command line args for i/o redirection & background symbols
set flags etc in *sstatus as appropriate

***********************************************************************/

void check4redirection(char **args, shellstatus *sstatus)
{
    sstatus->infile = NULL; // set defaults
    sstatus->outfile = NULL;
    sstatus->outmode = NULL;

    while (*args)
    {
        // input redirection
        if (!strcmp(*args, "<"))
        {
            // TODO
            ++args; // get input file
            if(access(*args, 0)) {
                errmsg("The input file doesn't exist!", NULL);
                exit(-1);
            }
            else if(access(*args, 4)) {
                errmsg("Cannot read the input file!", NULL);
                exit(-1);
            }
            else sstatus -> infile = *args;
        }
        // output direction
        else if (!strcmp(*args, ">") || !strcmp(*args, ">>"))
        {
            // TODO
            int flag = !strcmp(*args, ">>"); // to decide mode
            ++args; // get output file
            if(access(*args, 0)) {
                // no that file, create a new one
                FILE * fp = fopen(*args, "w");
                fprintf(fp, "%s", "");
                fclose(fp);
            }
            if(flag) sstatus -> outmode = "a";
            else sstatus -> outmode = "w";
            sstatus -> outfile = *args;

        }
        else if (!strcmp(*args, "&"))
        {
            // TODO
            sstatus -> foreground = FALSE;
        }
        args++;
    }
}

/***********************************************************************

  void execute(char ** args, shellstatus sstatus);

  fork and exec the program and command line arguments in args
  if foreground flag is TRUE, wait until pgm completes before
    returning

***********************************************************************/

void execute(char **args, shellstatus sstatus)
{
    int status;
    pid_t child_pid;

    child_pid = fork();

    // cannot create new process
    if(child_pid < 0) {
        syserrmsg("fork", NULL);
        exit(1);
    }
    else if(child_pid == 0) {
        // execution in child process
        // reset ctrl-C and child process signal trap
        signal(SIGINT, SIG_DFL);
        signal(SIGCHLD, SIG_DFL);

        // i/o redirection */
        // TODO
        if(sstatus.infile) freopen(sstatus.infile, "r", stdin);
        if(sstatus.outfile) freopen(sstatus.outfile, sstatus.outmode, stdout);

        // set PARENT = environment variable, malloc and put in nenvironment
        // TODO
        if(setenv("parent", sstatus.shellpath, 1)) {
            syserrmsg("Cannot set environment variable: parent path!", NULL);
        }

        // final exec of program
        execvp(args[0], args);
        syserrmsg("exec failed -", args[0]);
        exit(127);
    }
    else {
        // continued execution in parent process
        // TODO
        int option = 0;
        // execution foreground or background
        if(!sstatus.foreground) option = WNOHANG;
        waitpid(child_pid, &status, option);
        /*
        if(waitpid(child_pid, &status, option) == -1) {
            syserrmsg(NULL, NULL);
        }
        */
       // if child process exit abnormally
        /*
        if(!WIFEXITED(status)) {
            if(WIFSIGNALED(status)) printf("Child terminated abnormally, signal number = %d(%s)\n", WTERMSIG(status), strsignal(WTERMSIG(status)));
            if(WIFSTOPPED(status)) printf("Child terminated abnormally, stopped by signal: %d\n", WSTOPSIG(status));
        }
        */
    }

    return ;
}

/***********************************************************************

 char * getcwdstr(char * buffer, int size);

return start of buffer containing current working directory pathname

***********************************************************************/

char *getcwdstr(char *buffer, int size)
{
    // TODO
    getcwd(buffer, size);
    return buffer;
}

/***********************************************************************

FILE * redirected_op(shellstatus ststus)

  return o/p stream (redirected if necessary)

***********************************************************************/

FILE *redirected_op(shellstatus status)
{
    FILE *ostream = stdout;

    // TODO
    // if outfile != NULL, there is i/o direction
    if(status.outfile != NULL) {
        ostream = fopen(status.outfile, status.outmode);
    }

    return ostream;
}

/*******************************************************************

  char * stripath(char * pathname);

  strip path from file name

  pathname - file name, with or without leading path

  returns pointer to file name part of pathname
            if NULL or pathname is a directory ending in a '/'
                returns NULL
*******************************************************************/

char *stripath(char *pathname)
{
    char *filename = pathname;

    if (filename && *filename)
    {                                      // non-zero length string
        filename = strrchr(filename, '/'); // look for last '/'
        if (filename)                      // found it
            if (*(++filename))             //  AND file name exists
                return filename;
            else
                return NULL;
        else
            return pathname; // no '/' but non-zero length string
    }                        // original must be file name only
    return NULL;
}

/********************************************************************

void errmsg(char * msg1, char * msg2);

print an error message (or two) on stderr

if msg2 is NULL only msg1 is printed
if msg1 is NULL only "ERROR: " is printed
*******************************************************************/

void errmsg(char *msg1, char *msg2)
{
    fprintf(stderr, "ERROR: ");
    if (msg1)
        fprintf(stderr, "%s; ", msg1);
    if (msg2)
        fprintf(stderr, "%s; ", msg2);
    return;
    fprintf(stderr, "\n");
}

/********************************************************************

  void syserrmsg(char * msg1, char * msg2);

  print an error message (or two) on stderr followed by system error
  message.

  if msg2 is NULL only msg1 and system message is printed
  if msg1 is NULL only the system message is printed
 *******************************************************************/

void syserrmsg(char *msg1, char *msg2)
{
    errmsg(msg1, msg2);
    perror(NULL);
    return;
}
