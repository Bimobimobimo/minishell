# 42 Minishell

## Description
The goal of the  Minishell project is to recreate a functional shell with a limited set of system functions in C. The project focuses on mimicking a shell while providing a smooth user interface for command execution.

## Features
- Execution of built-in commands (e.g., cd, exit).
- Execution of external commands using execve().
- Input/output redirection (`>`, `<`, `>>`).
- Pipe management (`|`).
- Usage of fork() and wait() to manage processes.
- Command history with readline().
- Signal handling with signal().

## Prerequisites
- 42Lib: Certain functions from the 42 library should be used to handle string manipulations, memory management, etc.
- C Compiler: The project should be compiled with gcc and the default flags (e.g., -Wall -Wextra -Werror).
- External Libraries: The project uses readline for command history management and input reading.

## Installation
Clone the repository:
```bash
git clone https://github.com/your-username/minishell.git
```
Navigate to the project directory:
```bash
cd minishell
```
Compile the project using make:
```bash
make
```

## Usage
Run your shell by executing the compiled program:

```bash
./minishell
```
You can then enter commands as in a regular shell. For example:

```bash
$ ls
$ echo "Hello, world!"
$ cd /path/to/directory
$ exit
```

## Supported Commands
- `exit`: Exits the shell.
- `cd <path>`: Changes the current directory.
- `echo <string>`: Prints the given string.
- External commands: Commands like `ls`, `cat`, `grep` can be executed by their names, just like in a regular shell.

## Additional Features

### Redirection:
- `command > file` : Redirects the output to a file.
- `command < file` : Redirects the input from a file.
- `command >> file` : Appends to the output of a file.

### Pipes:
- `command1 | command2` : Executes command1 and passes its output to command2.
