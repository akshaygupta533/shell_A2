run `make` in shell directory for compliation

- The main.c file contains all the main logic for the shell and calls all other functions.
- commandtokenize.c and semicolon.c are used for parsing input from prompt
- getreldir.c gets the relative path from the directory where the shell was invoked.
- All other .c files are implementations of builtin and other commands.