#include "main.h"

/**
 * builtin_env - print the current environment, one variable per line
 *
 * Return: 0 on success
 */
static int builtin_env(void)
{
	int i;

	if (environ == NULL)
		return (0);
	for (i = 0; environ[i] != NULL; i++)
		printf("%s\n", environ[i]);
	return (0);
}

/**
 * handle_builtin - run a builtin if argv[0] matches one
 * @argv: parsed argument vector
 * @line: current input buffer (freed before exit)
 * @last_status: status of the previous command (used by `exit`)
 *
 * Return: -1 if not a builtin, otherwise the builtin's status.
 *         The `exit` builtin does not return.
 */
int handle_builtin(char **argv, char *line, int last_status)
{
	if (argv == NULL || argv[0] == NULL)
		return (-1);
	if (strcmp(argv[0], "exit") == 0)
	{
		free(line);
		exit(last_status);
	}
	if (strcmp(argv[0], "env") == 0)
		return (builtin_env());
	return (-1);
}
