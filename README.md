# Project: 42-minishell

(...)

## This version of Minishell supports

(...)

## Architecture
Description of a all projects and structures we use.

### Set env Variables
(Our choice: ...)

### Token

A sequence of characters considered a single unit by the shell. It is either a word or an operator.
Our projects contains (number) of tokens.

### Redirections

Before a command is executed, its input and output may be redirected using a special notation interpreted by the shell. Redirection allows commands’ file handles to be duplicated, opened, closed, made to refer to different files, and can change the files the command reads from and writes to.

1. **`<` (Input Redirection):**

### The Builtins

> A command that is implemented internally by the shell itself, rather than by an executable program somewhere in the file system. 

1. **env, export, unset**

`env` - shows the current environmental variables.
`export` - environment variables, create new ones and replace old ones.
`unset` - use unset to remove some of environment variables.

### exit statu (exit code)

> The value returned by a command to its caller. The value is restricted to eight bits, so the maximum value is 255. 

> 126: The command is found but is not executable (e.g., lacks execute permissions or is a directory).

> 127: The command is not found (e.g., an invalid path or name).

### extra input

> Out program has a feature to open additional prompt in case of unclosed pipe.
> For instance, `echo hello |` waits for further user unput until the pipe is not in the end.
> There no additional prompt in invalid case. For instance, `||` or `echo hello ||`. Our program > does not handle `||` so far (Date 02.09.2024). 

### ft_dprintf
> Feature to display a message on standard error output.
> As alternative we use ft_putstr_fd with file descriptor 2 which stands for standard error.

### EXECUTION

> The name of command and its arguments are stored in "t_data" struct, in array of strings "char	**cmd". The pointer is assigned to this variable (where? in what function). Execution part is called only if the first string in array "cmd" is not a NULL.

Function "ft_executer"
{piece of code}
`t_data	*comm_info;`
(...)
`if (comm_info->cmd[0] != NULL)`

> checking directories...
> Markus uses Macro: int S_ISDIR in
`static int	check_binary_or_invalid_cmd(char **cmd_plus_args, char *env[])`.
I need to know more about it.
This macro returns non-zero if the file is a directory. 

### PIPELINE
> pipes typically create subshells (child processes)... This means any changes made by a command within a subshell (such as `cd` changing the directory) won’t affect the parent shell or subsequent commands in the pipeline.

> part of built-ins execute (?) only if there is no pipeline but only one command.
It is - export, unset, cd and exit. Hence the bash checks executes them in child processes and check for errors, although `exit [number]` always assigns an exit status number even in a pipeline, e.g. `cat | ls | exit 3`. We use `exe` bool variable in a "big" struct to define if we execute these built-ins or not.

> We assign true or false to `exe` in "ft_count_commands" function.

> We do not execute this part of built-ins in child processes at all. (Because ...)

### Pipeline flow

## Tracking file descriptors

> We close unused file descriptors (read/write ends of pipes) in each process.

> We use valgrind to check if all file descriptors were closed safely.

`valgrind --track-fds=yes ./minishell`

> There is a possible error "Process terminating with the default action of signal 13 (SIGPIPE)". It can occur in sertain cases.

> In the context of pipelines (cmd1 | cmd2 | cmd3), encountering SIGPIPE can be normal in some scenarios.
> When a process like cmd2 exits (e.g., grep finishes finding matches), the read end of the pipe closes. If cmd1 continues writing to the pipe after it has been closed, the system sends a SIGPIPE to cmd1.
> Example:

`yes | head -n 10`

> `yes` generates infinite "yes\n". `head` reads the first 10 lines and exits. `yes` receives SIGPIPE when it tries to write to a closed pipe.

This is normal behavior in a shell pipeline and is not considered a bug.
We set SIGPIPE to be ignored in the program.

> `signal(SIGPIPE, SIG_IGN)`

### Big files
"Writing more data than the pipe can hold"
We didn't implement this case. 

