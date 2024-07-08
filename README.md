# Minishell

## Description

Minishell is a simplified reproduction of a Unix shell, aiming to provide a deep understanding of shell operations. This project implements several essential features, including built-in commands and handling of redirections and pipes.

## Features
### Built-in Commands

```bash
cd: Changes the current directory.
echo: Displays a line of text, supports the -n option to omit the trailing newline.
pwd: Displays the current working directory.
env: Displays environment variables.
unset: Removes environment variables.
export: Sets environment variables.
exit: Exits the shell.
```

### Redirections and Pipes

```bash
>: Redirects standard output to a file (overwrite).
<: Redirects standard input from a file.
>>: Redirects standard output to a file (append).
<<: Here-document, allows multi-line input as standard input.
|: Pipe, allows chaining multiple commands by using the output of one as the input of the next.
```
### Environment Variable Handling

Expansion: Environment variables are expanded with $ followed by the variable name.

### Quotes

" (double quotes): Expands environment variables inside.

'  (single quotes): No expansion of environment variables inside.

### Error Handling

Syntax: Detection and handling of syntax errors to ensure robust shell operation.

## Installation

```bash
git clone https://github.com/Nerada00/minishell.git
cd minishell
make
./minishell
```
## Usage

Run ./minishell to start your custom shell. Use commands and redirections as in a classic Unix shell.

## Licence

This project is licensed under the MIT License. See the LICENSE file for more information.
