/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:21:13 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/23 13:54:16 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

/* do the loop that execute and pipe the command, then return the fd filled */
void	redirect(char **cmds, int argc, char **env, int *fd, pid_t *gpid)
{
	int		tube[2];
	pid_t	pid;

	if (pipe(tube) == -1)
		exit_error();
	pid = fork();
	if (pid == -1)
		exit_error();
	if (pid == 0)
		do_child(tube, cmds, env);
	else
	{
		close(tube[1]);
		if (argc > 1)
		{
			dup2(tube[0], STDIN_FILENO);
			close(tube[0]);
			redirect(++cmds, argc - 1, env, fd, gpid);
		}
		else
		{
			*fd = tube[0];
			*gpid = pid;
		}
	}
}

/* write in a file (create it if does not exist) 
*	if mode == 1 -> append mode
*	else -> overwrite mode
*/
void	write_infile(int fd_in, char *out, int mode)
{
	char	buff[1];
	int		fd_out;

	if (mode == 1)
		fd_out = open(out, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd_out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
		exit_error();
	while (read(fd_in, buff, 1))
		write(fd_out, buff, 1);
	close(fd_in);
	close(fd_out);
}

/* launch command pipex without here_doc */
void	do_pipex(char **argv, int argc, char **env)
{
	int		cases;
	int		wstatus;
	pid_t	gpid;
	int		fd;

	cases = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		argv++;
		cases++;
		perror("");
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	redirect(argv + 2, argc - 3 - cases, env, &fd, &gpid);
	waitpid(gpid, &wstatus, 0);
	write_infile(fd, argv[argc - 1 - cases], 0);
	if (WIFEXITED(wstatus))
		exit(WEXITSTATUS(wstatus));
}

int	main(int argc, char **argv, char **env)
{
	if (argc < 5)
		write_error("Usage ./pipex file1 cmd1 cmd2 ... file2\n");
	else
	{
		if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
			do_pipex(argv, argc, env);
	}
	return (0);
}


/* revoir les bonus du here_doc + faire les bonnes editions niveau droit 
* -> faire les here_doc dans un pipe
* 
perror pour ouverture fichier
*/