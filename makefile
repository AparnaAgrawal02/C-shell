main:
	gcc -g main.c prompt.c echo.c pwd.c history.c cd.c ls.c fg.c bg.c sig.c systemCommands.c pinfo.c repeat.c signals.c execute.c jobs.c replay.c -Wextra -Wall -Wshadow
