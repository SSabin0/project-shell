#include "main.h"

/**
 * print_prompt - prints the shell prompt to stdout
 */
void print_prompt(void)
{
	printf("($) ");
	fflush(stdout);
}

/**
 * trim_line - strip trailing newline and surrounding spaces
 * @line: input buffer (modified in place)
 *
 * Return: pointer to the first non-space character
 */
char *trim_line(char *line)
{
	int j;
	char *start;

	if (line == NULL)
		return (NULL);
	j = 0;
	while (line[j] != '\0')
		j++;
	j--;
	while (j >= 0 && (line[j] == ' ' || line[j] == '\n' || line[j] == '\t'))
	{
		line[j] = '\0';
		j--;
	}
	start = line;
	while (*start == ' ' || *start == '\t')
		start++;
	return (start);
}

/**
 * split_line - tokenize a line into argv on whitespace
 * @line: input line (modified by strtok)
 * @argv: caller-provided array of size MAX_ARGS
 *
 * Return: argv (NULL-terminated)
 */
char **split_line(char *line, char **argv)
{
	int i = 0;

	argv[i] = strtok(line, " \t");
	while (argv[i] != NULL && i < MAX_ARGS - 1)
	{
		i++;
		argv[i] = strtok(NULL, " \t");
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * print_error - print sh-style "not found" error to stderr
 * @prog: program name (argv[0] of the shell)
 * @line_no: command line number (1-based)
 * @cmd: command that was not found
 */
void print_error(char *prog, int line_no, char *cmd)
{
	fprintf(stderr, "%s: %d: %s: not found\n", prog, line_no, cmd);
}
