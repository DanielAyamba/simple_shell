#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
write(STDOUT_FILENO, "$ ", 2);
}

/**
 * execute_command - Execute the given command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
pid_t pid = fork();

if (pid == -1)
{
perror("fork");
}
else if (pid == 0)
{
execlp(command, command, NULL);

write(STDERR_FILENO, "Error: Command not found\n", 25);
exit(EXIT_FAILURE);
}
else
{
int status;
waitpid(pid, &status, 0);

if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
{
write(STDERR_FILENO, "Error: Command execution failed\n", 32);
}
}
}

/**
 * main - Entry point of the simple shell program.
 * Return: Always 0.
 */
int main(void)
{
while (1)
{
char command_line[MAX_COMMAND_LENGTH];
display_prompt();

ssize_t bytes_read = read(STDIN_FILENO, command_line, MAX_COMMAND_LENGTH);

if (bytes_read == 0)
{
write(STDOUT_FILENO, "\nExiting shell.\n", 17);
break;
}

command_line[bytes_read - 1] = '\0';

execute_command(command_line);
}

return (0);
}
