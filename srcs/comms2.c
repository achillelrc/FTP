/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** conncomm
*/

#include "serv.h"

void	list(t_cli *cli)
{
	FILE *ls;
	char *arg = malloc(10000);
	char *p = getcwd(NULL, 1000);

	if (!cli->logged || !arg || !p) {
		dprintf(cli->fd, DECO);
		return;
	}
	if (cli->transfd <= 0) {
		dprintf(cli->fd, LINK);
		return;
	}
	sprintf(arg, "/bin/ls -l %s", p);
	ls = popen(arg, "r");
	while (fgets(arg, 10000, ls))
		dprintf(cli->transfd, "%s", arg);
	pclose(ls);
	close(cli->transfd);
	dprintf(cli->fd, LSMSG);
	cli->transfd = 0;
}

int	port_connect(char *host, int port, int *sock)
{
	struct sockaddr_in addr;
	struct hostent *serv = gethostbyname(host);

	*sock = socket(AF_INET, SOCK_STREAM, 0);
	if (*sock < 0 || !serv)
		return (-1);
	memset((void *)&addr, 0, sizeof(addr));
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	memcpy((char *)&addr.sin_addr.s_addr,
	(char *)serv->h_addr, serv->h_length);
	if (connect(*sock, (struct sockaddr *) &addr, sizeof(addr)) < 0)
		return (-1);
	return (*sock);
}

void	port(t_cli *cli)
{
	int fd;
	char *ip = malloc(10000);
	char **ar = parse_com(cli->curr[1], ", ");

	if (!cli->logged || !cli->curr[1] || !ip || !atoi(ar[5])) {
		dprintf(cli->fd, DECO);
		return;
	}
	sprintf(ip, "%s.%s.%s.%s", ar[0], ar[1], ar[2], ar[3]);
	if (port_connect(ip, atoi(ar[4]) * 256 + atoi(ar[5]), &fd) < 0)
		dprintf(cli->fd, ERRT);
	cli->transfd = fd;
}

void	pasv(t_cli *cli)
{
	int sock;
	struct sockaddr_in claddr;
	unsigned int cllen = sizeof(claddr);

	if (!cli->logged) {
		dprintf(cli->fd, DECO);
		return;
	}
	if (init_socket(0, &sock, cli->root) < 0) {
		dprintf(cli->fd, SOCKERR);
		return;
	}
	pasv_showhost(sock, cli->fd);
	cli->transfd = accept(sock, (struct sockaddr *) &claddr, &cllen);
	if (cli->transfd == -1)
		dprintf(cli->fd, TIMEOUT);
}

void	pasv_showhost(int sock, int fd)
{
	int port;
	char *ip;
	struct sockaddr_in addr;
	socklen_t i = sizeof(addr);

	getsockname(sock, (struct sockaddr *)&addr, &i);
	port = ntohs(addr.sin_port);
	ip = inet_ntoa(addr.sin_addr);
	dprintf(fd, PASSV);
	i = 0;
	while (ip[i]) {
		dprintf(fd, "%c", ip[i] == '.' ? ',' : ip[i]);
		i++;
	}
	dprintf(fd, ",%d,%d).\n", port / 256, port % 256);
}