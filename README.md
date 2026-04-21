### Description
This project is a group project done for Holberton School to build a simple UNIX command interpreter (`hsh`).

### Features
- Interactive prompt (`($) `) only when stdin is a TTY
- Non-interactive mode (reads from a pipe / redirected file)
- `$PATH` resolution — `ls` works as well as `/bin/ls`
- Skips `fork` entirely when the command is not found
- `sh`-style errors: `./hsh: 1: qwerty: not found` (exit status 127)
- Built-ins: `exit` (returns status of last command) and `env`
- Ctrl-C (SIGINT) cancels the line instead of killing the shell
- No memory leaks — `PATH` lookups and `getline` buffer are freed
- Five files, each with at most 5 functions; header is include-guarded

### Files
| File | Purpose |
| --- | --- |
| `main.h` | Prototypes, includes, `environ` declaration, `MAX_ARGS` |
| `main.c` | Entry point, REPL, fork/wait, `execute_command` |
| `shell.c` | `print_prompt`, line trimming, tokenizer, error printer |
| `path.c` | `get_env`, `find_path` (PATH walker) |
| `builtins.c` | `exit` and `env` built-ins |

### How to compile
Compiled on Ubuntu 20.04 LTS with gcc using `-Wall -Werror -Wextra -pedantic -std=gnu89`:

```sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

### Usage
Interactive:
```
$ ./hsh
($) /bin/ls
main.c main.h path.c shell.c builtins.c hsh README.md
($) ls -l /tmp
...
($) exit
$
```

Non-interactive:
```
$ echo "/bin/ls" | ./hsh
$ cat commands.txt | ./hsh
```

### Allowed functions
Only the functions/system calls permitted by the project spec are used:
`access`, `execve`, `fork`, `wait`/`waitpid`, `getline`, `malloc`, `free`,
`strdup`, `signal`, `isatty`, `fflush`, `printf`/`fprintf`, `perror`,
`sprintf`, `strtok`, `strcmp`/`strncmp`/`strlen`/`strchr`, `_exit`, `exit`.
