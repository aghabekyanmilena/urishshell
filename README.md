# 🐚 URISHshell

A simple Unix shell implemented in C.
This project is part of the 42 school curriculum and mimics basic Bash behavior.

## Features

* Prompt display and input reading using `readline`
* Built-in commands:

  * `echo`
  * `cd`
  * `pwd`
  * `export`
  * `unset`
  * `env`
  * `exit`
* Command execution with support for:

* Pipes (`|`)
* Redirections (`<`, `>`, `>>`, `<<`)
* Single and double quotes
* Signal handling for `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
* Exit status management

## How to Compile

```bash
make
```

## How to Run

```bash
./minishell
```

You'll see a custom prompt (like `urishshell:`), and you can start typing commands.

## Example Usage

```bash
urishshell: echo Hello World
Hello World

urishshell: export NAME=Milena
urishshell: echo $NAME
Milena

urishshell: ls | grep .c > files.txt
```

## Notes

* Quoting, variable expansion, and redirections follow Bash-like rules.
* `ctrl+D` exits the shell.
* `ctrl+C` interrupts the current command.
* `ctrl+\` is ignored unless during heredoc or pipe execution.

This was team project and it was done with @atseruny (https://github.com/atseruny)

Why urishshell որովհետև մերը ուրիշա ։D
