#include "main.h"

/**
 * execute_command - resolve and execute a single command
 * @argv: parsed argument vector (NULL-terminated)
 * @prog: shell program name (argv[0] of main)
 * @line_no: 1-based command line number for error messages
 *
 * Return: exit status of the command (127 if not found)
 */
int execute_command(char **argv, char *prog, int line_no)
{
	pid_t pid;
	int status = 0;
	char *path;
	int allocated;

	path = find_path(argv[0]);
	if (path == NULL)
	{
		print_error(prog, line_no, argv[0]);
		return (127);
	}
	allocated = (path != argv[0]);
	pid = fork();
	if (pid == -1)
	{
		perror(prog);
		if (allocated)
			free(path);
		return (1);
	}
	if (pid == 0)
	{
		execve(path, argv, environ);
		perror(prog);
		_exit(127);
	}
	waitpid(pid, &status, 0);
	if (allocated)
		free(path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/**
 * main - entry point of the simple shell
 * @ac: argument count (unused)
 * @av: argument vector; av[0] is used in error messages
 *
 * Return: exit status of the last command run
 */
int main(int ac, char **av)
{
	char *line = NULL, *start;
	size_t len = 0;
	ssize_t nread;
	char *argv[MAX_ARGS];
	int line_no = 0, status = 0, builtin;

	(void)ac;
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_prompt();
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			exit(status);
		}
		line_no++;
		start = trim_line(line);
		if (*start == '\0')
			continue;
		split_line(start, argv);
		if (argv[0] == NULL)
			continue;
		builtin = handle_builtin(argv, line, status);
		if (builtin != -1)
		{
			status = builtin;
			continue;
		}
		status = execute_command(argv, av[0], line_no);
	}
	free(line);
	return (status);
}
