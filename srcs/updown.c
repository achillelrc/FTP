/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** updown
*/

#include "serv.h"

int	stor_err(t_cli *cli, char *arg, char *buf)
{
	if (!cli->logged) {
		dprintf(cli->fd, DECO);
		return (-1);
	}
	if (cli->transfd <= 0) {
		dprintf(cli->fd, LINK);
		return (-1);
	}
	if (!arg || !buf || !cli->curr[1]) {
		dprintf(cli->fd, MEMERR);
		return (-1);
	}
	dprintf(cli->fd, BINMOD);
	return (0);
}

void	stor(t_cli *cli)
{
	char *buf = getcwd(NULL, 1000);
	char *arg = malloc(10000);
	int filfd = stor_err(cli, arg, buf);
	char c = 0;

	sprintf(arg, "%s/%s", buf, cli->curr[1]);
	filfd = open(arg, O_CREAT | O_WRONLY);
	if (!arg || filfd < 0) {
		dprintf(cli->fd, FILERR);
		return;
	}
	while (read(cli->transfd, &c, 1) > 0)
		write(filfd, &c, 1);
	chmod(arg, 0644);
	free(buf);
	close(filfd);
	close(cli->transfd);
	dprintf(cli->fd, TROK);
	cli->transfd = 0;
}

int	retr_err(t_cli *cli, char *arg)
{
	if (!cli->logged) {
		dprintf(cli->fd, DECO);
		return (-1);
	}
	if (cli->transfd <= 0) {
		dprintf(cli->fd, LINK);
		return (-1);
	}
	if (!arg || !cli->curr[1]) {
		dprintf(cli->fd, MEMERR);
		return (-1);
	}
	dprintf(cli->fd, BINMOD);
	return (0);
}

char	*xcopy(t_cli *cli, char *arg, int *len)
{
	FILE *fil;
	char *buf;

	fil = fopen(arg, "r");
	if (!fil) {
		dprintf(cli->fd, FILERR);
		return (NULL);
	}
	fseek(fil, 0, SEEK_END);
	*len = ftell(fil);
	fseek(fil, 0, SEEK_SET);
	buf = malloc(*len + 1);
	fread(buf, *len, 1, fil);
	fclose(fil);
	return (buf);
}

void	retr(t_cli *cli)
{
	int len = 0;
	char *buf = NULL;
	char *arg = malloc(10000);

	if (retr_err(cli, arg))
		return;
	if (cli->curr[1][0] == '/')
	sprintf(arg, "%s%s", cli->root, cli->curr[1]);
	else
	sprintf(arg, "%s/%s", cli->dir ? cli->dir : cli->root, cli->curr[1]);
	buf = xcopy(cli, arg, &len);
	for (int i = 0; i < len; ++i)
		write(cli->transfd, &buf[i], 1);
	free(buf);
	close(cli->transfd);
	dprintf(cli->fd, TROK);
	cli->transfd = 0;
}
