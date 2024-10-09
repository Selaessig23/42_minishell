void	child_process(char *argv, char **env, child_return **ch)
{
	pid_t		pid;
	int			fd[2];
	t_id_list	*node;

	if (pipe(fd) == -1)
		w_errpipe_close((*ch)->fd_to_read);
	pid = fork();
	if (pid == -1)
		w_errfork_close((*ch)->fd_to_read, fd);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (!*argv)
			exit(EXIT_FAILURE);
		call_cmd(argv, env);
	}
	node = node_birth(pid);
	list_birth(&(*ch)->list, node);
	close(fd[1]);
	dup2((*ch)->fd_to_read, STDIN_FILENO);
	close((*ch)->fd_to_read);
	(*ch)->fd_to_read = fd[0];
}