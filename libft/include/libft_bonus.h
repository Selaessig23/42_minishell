/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:32:22 by mpeshko           #+#    #+#             */
/*   Updated: 2024/08/06 10:28:10 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_BONUS_H
# define LIBFT_BONUS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
// # include "../../include/minishell.h"

typedef enum e_tokentype {
	WORD = 1,
	D_QUOTED = 2, 
	S_QUOTED = 3, 
	PIPE = 4,
	HEREDOC = 5,
	REDIRECT_INPUT = 6,
	REDIRECT_OUTPUT = 7,
	D_QUOTED_F = 8, 
	S_QUOTED_F = 9, 
	Q_WORD = 10,
}	t_tokentype;

// commented out as it was redefined for minishell.h
typedef struct s_list{
	void			*content;
	t_tokentype		token;
	struct s_list	*next;
}			t_list;

/*
// linked list for lexer analysis -> token system, redefined from libft_bonus.h
typedef struct s_list{
	void			*content;
	t_tokentype		token;
	struct s_list	*next;
}				t_list;
*/

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
