/*
** EPITECH PROJECT, 2018
** serv part
** File description:
** server
*/

#include "serv.h"

t_coms coms[14] = {
	{"USER", conct},
	{"PASS", conct},
	{"PASV", pasv},
	{"PORT", port},
	{"STOR", stor},
	{"RETR", retr},
	{"LIST", list},
	{"HELP", help},
	{"QUIT", deco},
	{"NOOP", noop},
	{"CDUP", cdup},
	{"DELE", del},
	{"CWD", cwd},
	{"PWD", pwd}
};

int	init_socket(int port, int *sock, char *path)
{
	int tmp = 1;
	struct sockaddr_in addr;

	*sock = socket(AF_INET, SOCK_STREAM, 0);
	memset((void *)&addr, 0, sizeof(addr));
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	if (*sock < 0 ||
	setsockopt(*sock, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int)) < 0)
		return (-1);
	if (bind(*sock, (struct sockaddr *) &addr, sizeof(addr)) < 0 ||
	listen(*sock, 5) < 0)
		return (-1);
	if (access(path, F_OK))
		return (-1);
	return (*sock);
}

char	**parse_com(char *com, const char *delim)
{
	int cnt = 0;
	char *buf = strtok(com, delim);
	char **tab = malloc(sizeof(char *));

	if (!com || !buf)
		return (NULL);
	while (buf) {
		tab[cnt] = strdup(buf);
		tab = realloc(tab, sizeof(char *) * (++cnt + 1));
		buf = strtok(NULL, delim);
	}
	tab[cnt] = NULL;
	return (tab);
}

int	handle_cli(struct sockaddr_in claddr, char *path, int clfd)
{
	t_cli cli;
	int i = 0;
	char *buf = NULL;

	chdir(path);
	memset(&cli, 0, sizeof(cli));
	cli.root = getcwd(NULL, 1000);
	cli.addr = claddr;
	cli.fd = clfd;
	while ((buf = getnextline(cli.fd)) && cli.root) {
		i = 0;
		cli.curr = parse_com(buf, " \n\r");
		while (cli.curr && i < 14 && strcmp(coms[i].name, cli.curr[0]))
			i++;
		if (cli.curr && i < 14)
			(coms[i].com)(&cli);
		else
			dprintf(cli.fd, "%s", cli.logged ? UNKN : DECO);
	}
	return (-1);
}

int	handle_co(int sock, char *path)
{
	int pid;
	int clfd = 42;
	struct sockaddr_in claddr;
	unsigned int cllen = sizeof(claddr);

	while (clfd > 0) {
		clfd = accept(sock, (struct sockaddr *) &claddr, &cllen);
		if (clfd < 0)
			return (84);
		pid = fork();
		if (pid) {
			close(clfd);
			continue;
		}
		dprintf(clfd, WELCOME);
		if (handle_cli(claddr, path, clfd))
			return (84);
		close(clfd);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int fd;

	if (ac != 3 || atoi(av[1]) > 65535 || atoi(av[1]) < 1) {
		fprintf(stderr, USAGE, av[0]);
		return (84);
	}
	if (init_socket(atoi(av[1]), &fd, av[2]) < 0)
		return (84);
	return (handle_co(fd, av[2]));
}