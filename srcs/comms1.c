/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** comms1
*/

#include "serv.h"

char	*getnextline(int clfd)
{
	char *buf = malloc(1);
	int cnt = 0;
	char c = 0;

	do {
		if (!buf || read(clfd, &c, 1) <= 0)
			return (NULL);
		if (!cnt && c == '\n') {
			c = -1;
			continue;
		}
		buf[cnt] = c;
		buf = realloc(buf, ++cnt + 1);
	}
	while (c && c != '\n');
	buf[cnt] = 0;
	return (!c ? NULL : buf);
}

void	help(t_cli *cli)
{
	if (!cli->logged) {
		dprintf(cli->fd, DECO);
		return;
	}
	dprintf(cli->fd, HELP);
}

void	cdup(t_cli *cli)
{
	if (cli->dir) {
		if (chdir("..")) {
			dprintf(cli->fd, DIRERR);
			return;
		}
		cli->dir = (getcwd(NULL, 1000)) + strlen(cli->root);
		if (strlen(cli->dir) < 3)
			cli->dir = NULL;
	}
	dprintf(cli->fd, DIROK);
}

void	cwd(t_cli *cli)
{
	if (!cli->logged) {
		dprintf(cli->fd, DECO);
		return;
	}
	if (!cli->curr[1]) {
		dprintf(cli->fd, DIRERR);
		return;
	}
	if (!cli->dir && cli->curr[1][0] == '.' && cli->curr[1][1] == '.') {
		dprintf(cli->fd, DIROK);
		return;
	}
	if (chdir(cli->curr[1])) {
		dprintf(cli->fd, DIRERR);
		return;
	}
	cli->dir = (getcwd(NULL, 1000)) + strlen(cli->root);
	if (strlen(cli->dir) < 3)
		cli->dir = NULL;
	dprintf(cli->fd, DIROK);
}

void	pwd(t_cli *cli)
{
	if (!cli->logged) {
		dprintf(cli->fd, DECO);
		return;
	}
	if (!cli->dir)
		dprintf(cli->fd, CURDIR);
	else
		dprintf(cli->fd, CURDIRA, cli->dir);
}
