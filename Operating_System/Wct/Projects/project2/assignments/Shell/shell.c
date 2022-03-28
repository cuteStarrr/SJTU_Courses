#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_LINE 80 /* 80 chars per line, per command */
#define READ_END 0
#define WRITE_END 1

char *args[MAX_LINE/2 + 1]; /* command line (of 80) has max of 40 arguments */
char str[MAX_LINE/2 + 1][20];
char history_args[MAX_LINE/2 + 1][20];
char *pipe_args[MAX_LINE/2 + 1];
char *filename;
int should_run = 1; /* flag to determine when to exit program */
int len;
int history_len;
int pipe_len ;
char ch;
int history_flag = 0;
int wait_flag;
int redirection_flag; 
int pipe_flag;
int fd;
int pipe_fd[2];
pid_t pid;
pid_t pipe_pid;

int main(void)
{
    while (should_run) {
        printf("\nosh>");
        fflush(stdout);

        /* initialization */
        for (int i = 0; i < MAX_LINE/2 + 1; ++i) {
            args[i] = NULL;
            pipe_args[i] = NULL;
        }
        len = 0;
        pipe_len = 0;
        wait_flag = 1;
        redirection_flag = 0;
        pipe_flag = 0;
        
        /* read instructions */
        while (scanf("%s", str[len])) {
            args[len] = str[len]; /* str[] is to store the commands user input and args[] is the pointer */
            scanf("%c", &ch);
            ++len;
            if(ch == '\n')
                break;
        }

        /* exit */
        if (strcmp(args[0], "exit") == 0) {
            should_run = 0;
            continue;
        }
        
        /* history instructions */
        if (strcmp(args[0], "!!") != 0) {
            for (int i = 0; i < len; ++i) {
                strcpy(history_args[i], args[i]);
            }
            history_len = len;
        }
        else {
            if (!history_flag) {
                printf("NO commands in history.\n");
                fflush(stdout);
                continue;
            }
            else {
                for (int i = 0; i < history_len; ++i) {
                    args[i] = history_args[i];
                    printf("%s ", args[i]);
                }
                printf("\n");
                len = history_len;
            }
        }

        history_flag = 1;
        
        /* concurrent running */
        if (strcmp(args[len - 1], "&") == 0) {
            wait_flag = 0;
            --len;
            args[len] = NULL;
        }
        
        /* redirection */
        if (len >= 2 && strcmp(args[len-2],">") == 0) {
            redirection_flag = 1;
            filename = args[len - 1];
            --len;
            args[len] = NULL;
            --len;
            args[len] = NULL;
        }
        else if (len >= 2 && strcmp(args[len-2],"<")==0) {
            redirection_flag = 2;
            filename = args[len - 1];
            --len;
            args[len] = NULL;
            --len;
            args[len] = NULL;
        }
        
        /* pipe communication */
        for (int i = 0; i < len; ++i) {
            if (strcmp(args[i], "|") == 0) {
                pipe_flag = 1;
                args[i] = NULL; /* find the position of | */

                for (int j = i + 1; j < len; ++j) {
                    pipe_args[pipe_len] = args[j];
                    args[j] = NULL;
                    ++pipe_len;
                }
                len = i;
                break;
            }
        }
        
        /* child process */
        pid = fork();
        if (pid == 0) {
            if (redirection_flag == 1) {
                fd = open(filename,O_CREAT|O_RDWR, S_IRWXU);
                dup2(fd, STDOUT_FILENO);
            }
            else if (redirection_flag == 2) {
                fd = open(filename,O_CREAT|O_RDONLY, S_IRUSR);
                dup2(fd, STDIN_FILENO);
            }
            /* pipe process */
            if (pipe_flag) {
                if (pipe(pipe_fd) == -1) {
                    fprintf(stderr, "Pipe failed");
                    return 1;
                }
                pipe_pid = fork();
                if (pipe_pid < 0) {
                    fprintf(stderr, "Fork failed");
                    return 1;
                }
                else {
                    if (pipe_pid == 0) {
                        usleep(10000);
                        close(pipe_fd[WRITE_END]);
                        dup2(pipe_fd[READ_END], STDIN_FILENO);
                        execvp(pipe_args[0], pipe_args);
                        close(pipe_fd[READ_END]);
                        exit(0);
                    }
                    else {
                        close(pipe_fd[READ_END]);
                        dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
                        execvp(args[0], args);
                        close(pipe_fd[WRITE_END]);
                        wait(NULL);
                    }
                }
            }
            else {
                execvp(args[0], args);
            }
            if(redirection_flag) close(fd);

            exit(0);
        }
        else{
            if (wait_flag) {
                wait(NULL);
            }
            else {
                signal(SIGCHLD, SIG_IGN);
            }
        }
        
    }
 /**
 * After reading user input, the steps are:
 * (1) fork a child process
 * (2) the child process will invoke execvp()
 * (3) if command included &, parent will invoke wait()
 */
    
	return 0;
}