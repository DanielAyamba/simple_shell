#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 *Function to execute a command with arguments.
 *Parameters:
 *command: The command to execute.
 *args: An array of arguments for the command.
*Return: Always 0
*/
void execute_command(char *command, char *args[])
{
pid_t pid, wpid;
int status;

pid = fork();
if (pid == 0)
{
if (execvp(command, args) == -1)
{
perror("shell");
}
exit(EXIT_FAILURE);
}
else if (pid < 0)

{
perror("shell");
}
else
{

{
wpid = waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
}

int main(void)
{
char input[MAX_INPUT_SIZE];

char *args[MAX_ARG_SIZE];
int arg_count;

while (1)
{
write(STDOUT_FILENO, "Shell> ", 7);

if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)

{
perror("shell");
exit(EXIT_FAILURE);
}

input[strcspn(input, "\n")] = '\0';

if (strcmp(input, "exit") == 0)

{
break;
}

arg_count = 0;
args[arg_count++] = strtok(input, " ");
while ((args[arg_count] = strtok(NULL, " ")) != NULL)
{
arg_count++;
}

execute_command(args[0], args);
}

return (0);
}
