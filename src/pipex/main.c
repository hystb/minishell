/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:21:13 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/30 13:47:21 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int main(int argc, char **args, char **env)
{

	char *cmds[10] = { "< 1", "cat -e", NULL};
	// do_input("1");
	do_commands(cmds, env);
	// printf("bonjour\n");
}


/* launch command pipex without here_doc */
// void	do_pipex(char **argv, int argc, char **env)
// {
// 	int		cases;
// 	int		wstatus;
// 	pid_t	gpid;
// 	int		fd;

// 	cases = 0;
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		argv++;
// 		cases++;
// 		perror("");
// 	}
// 	else
// 	{
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// 	redirect(argv + 2, argc - 3 - cases, env, &fd, &gpid);
// 	waitpid(gpid, &wstatus, 0);
// 	write_infile(fd, argv[argc - 1 - cases], 0);
// 	if (WIFEXITED(wstatus))
// 		exit(WEXITSTATUS(wstatus));
// }

// int	main(int argc, char **argv, char **env)
// {
// 	if (argc < 5)
// 		write_error("Usage ./pipex file1 cmd1 cmd2 ... file2\n");
// 	else
// 	{
// 		if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
// 			do_pipex(argv, argc, env);
// 	}
// 	return (0);
// }

/* revoir les bonus du here_doc + faire les bonnes editions niveau droit 
* -> faire les here_doc dans un pipe
* 
perror pour ouverture fichier
*/

/* faire les espaces entre << > < tout le bordel */
// tester le heredoc qui wait.