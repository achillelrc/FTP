/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** conncomm
*/

#include "serv.h"

void	conct(t_cli *cli)
{
	static int username = 0;

	if (cli->logged) {
		dprintf(cli->fd, "%s",
		!strcmp(cli->curr[0], "PASS") ? ALOGD : GUESTU);
		return;
	}
	if (!username && cli->curr[1] && !strcmp(cli->curr[0], "USER") &&
	!strcmp(cli->curr[1], "Anonymous")) {
		username = 1;
		dprintf(cli->fd, IPASS);
	}
	else if (username && !cli->curr[1] && !strcmp(cli->curr[0], "PASS")) {
		cli->logged = 1;
		dprintf(cli->fd, LOGD;
	}
	else {
		username = 0;
		dprintf(cli->fd, BADC);
	}
}

void	del(t_cli *cli)
{
	char *buf = NULL;

	if (!cli->logged) {
		dprintf(cli->fd, DECO);
		return;
	}
	if (!cli->curr[1]) {
		dprintf(cli->fd, FILERR);
		return;
	}
	buf = getcwd(NULL, 1000);
	buf = strcat(strcat(buf, "/"), cli->curr[1]);
	if (unlink(buf)) {
		dprintf(cli->fd, FILERR);
		return;
	}
	dprintf(cli->fd, DELT);
}

void	deco(t_cli *cli)
{
	cli->root = NULL;
	dprintf(cli->fd, QUIT);
}

void	noop(t_cli *cli)
{
	if (!cli->logged) {
		dprintf(cli->fd, DECO);
		return;
	}
	dprintf(cli->fd, NOOP);
}
