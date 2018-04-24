/*
** EPITECH PROJECT, 2018
** start
** File description:
** serv
*/

#ifndef SERV_H_
# define SERV_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct s_cli
{
	int fd;
	int logged;
	char *root;
	char *dir;
	char **curr;
	struct sockaddr_in addr;
	int transfd;
} t_cli;

typedef struct s_coms
{
	const char *name;
	void (*com)(t_cli *);
} t_coms;

char	*getnextline(int);
void	pasv_showhost(int, int);
int	init_socket(int, int *, char *);
char	**parse_com(char *, const char *);

/* commands */
void	conct(t_cli *);
void	pasv(t_cli *);
void	port(t_cli *);
void	list(t_cli *);
void	retr(t_cli *);
void	stor(t_cli *);
void	deco(t_cli *);
void	help(t_cli *);
void	cdup(t_cli *);
void	noop(t_cli *);
void	pwd(t_cli *);
void	cwd(t_cli *);
void	del(t_cli *);

/* error codes */
#define USAGE "USAGE: %s port path\n\tport is the port number \
on which the server socket listens\n\tpath is the path to the \
home directory for the Anonymous user\n"
#define HELP "214 The following commands are recognized.\
\n CDUP CWD DELE HELP LIST NOOP PASS\n PASV PORT PWD QUIT \
RETR STOR USER\n214 Help OK.\n"
#define DECO "530 Please login with USER and PASS.\n"
#define LSMSG "150 Here comes the directory listing.\n226 Directory send OK.\n"
#define LINK "425 Use PORT or PASV first.\n"
#define ERRT "421 Connect error or timeout.\n"
#define TIMEOUT "421 Timeout.\n"
#define PASSV "227 Entering Passive Mode ("
#define SOCKERR "421 Error creating soket.\n"
#define TROK "226 Transfer complete.\n"
#define FILERR "550 Failed to open file\n"
#define MEMERR "550 Memory error.\n"
#define BINMOD "150 Opening BINARY mode data connection for /fil (8 bytes).\n"
#define NOOP "200 NOOP ok.\n"
#define QUIT "221 Goodbye.\n"
#define DELT "250 File deleted.\n"
#define BADC "530 Bad creditentials.\n"
#define LOGD "230 Login successful.\n")
#define IPASS "331 Please specify the password.\n"
#define GUESTU "530 Can't change from guest user.\n"
#define ALOGD "230 Already logged in.\n"
#define DIRERR "550 Failed to change directory.\n"
#define DIROK "250 Directory successfully changed.\n"
#define CURDIR "257 \"/\" is the current directory\n"
#define CURDIRA "257 \"%s\" is the current directory\n"
#define UNKN "500 Unknown command.\n"
#define WELCOME "220 (aFTP v0.1)\n"

#endif /* !SERV_H_ */
