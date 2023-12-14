#include "shell.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * _write_str - Write a string to standard output.
 * @str: The string to write.
 */
void _write_str(char *str)
{
	while (*str)
	{
	write(1, str, 1);
	str++;
	}
}

/**
 * main - Entry point of the shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *message = "Hello, Betty!\n";

	_write_str(message);

	return (0);
}
