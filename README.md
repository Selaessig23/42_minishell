# Project: 42-minishell

(...)

## This version of Minishell supports

(...)

## Architecture

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

### exit status

> The value returned by a command to its caller. The value is restricted to eight bits, so the maximum value is 255. 

### extra input

> Out program has a feature to open additional prompt in case of unclosed pipe.
> For instance, `echo hello |` waits for further user unput until the pipe is not in the end.
> There no additional prompt in invalid case. For instance, `||` or `echo hello ||`. Our program > does not handle `||` so far (Date 02.09.2024). 

### ft_dprintf
> Feature to display a message on standard error output.

### PIPELINE
> pipes typically create subshells (child processes)... This means any changes made by a command within a subshell (such as `cd` changing the directory) won’t affect the parent shell or subsequent commands in the pipeline.
