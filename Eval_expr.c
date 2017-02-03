/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Eval_expr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 12:31:51 by cbarbier          #+#    #+#             */
/*   Updated: 2016/07/12 14:18:23 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_beta/libft.h"
#include "Eval_expr.h"

char	**ft_exprsplit(char *str, char c);

int	is_number(char *str)
{
	if (ft_strequ(str, "-"))
		return (0);
	if (*str == '-')
		str++;
	while (*str)
	{	
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

t_ope	*get_ope(char *str)
{
	int index;

	index = 0;
	while (index < NB_OPERATIONS 
		&& ft_strcmp(operations[index].sign, str))
		index ++;
	if (index == NB_OPERATIONS)
		return (NULL);
	return (&operations[index]);
}

void	pushback_output(t_list **aoutput, t_list **astack)
{
	t_list	*stack;
	t_list	*tmp;

	while(ft_strcmp((*astack)->content, "("))
	{
		stack = *astack;
		tmp = ft_lstnew(stack->content, ft_strlen(stack->content));
		ft_lstpushback(aoutput, tmp);
		*astack = stack->next;
		free(stack->content);
		free(stack);
	}
	stack = *astack;
	*astack = stack->next;
	free(stack->content);
	free(stack);
}

void	push_operator(t_ope *ope, t_list **aoutput, t_list **astack)
{
	t_list	*tmp;
	t_list	*stack;

	stack = *astack;
	if (!stack || !ft_strcmp(stack->content, "(") 
		|| ope->priority > get_ope(stack->content)->priority)
	{
 		if ((tmp = ft_lstnew((char *)ope->sign, ft_strlen(ope->sign))))
			ft_lstadd(astack, tmp);
		return ;
	}
	if ((tmp = ft_lstnew((char *)stack->content, ft_strlen(stack->content))))
		ft_lstpushback(aoutput, tmp);
	free(stack->content);
	stack->content = ft_strdup(ope->sign);
	stack->content_size = ft_strlen(ope->sign);
}

void	rev_stack_to_output(t_list **aoutput, t_list **astack)
{
	t_list *elm;

	elm = *aoutput;
	while (elm->next)
		elm = elm->next;
	elm->next = *astack;
	*astack = NULL;
}

t_list	*to_npi(char **tokens)
{
	t_list	*output;
	t_list	*stack;

	output = NULL;
	stack = NULL;
	while (*tokens)
	{
		if (is_number(*tokens))
			ft_lstpushback(&output, ft_lstnew(*tokens, ft_strlen(*tokens)));
		else if (!ft_strcmp(*tokens, "("))
			ft_lstadd(&stack, ft_lstnew(*tokens, ft_strlen(*tokens)));
		else if (!ft_strcmp(*tokens, ")"))
			pushback_output(&output, &stack);
		else
			push_operator(get_ope(*tokens), &output, &stack);
		tokens++;
	}
	rev_stack_to_output(&output, &stack);
	return (output);
}

void	ft_putlist(t_list *lst, const char sep)
{
	while (lst)
	{
		ft_putstr(lst->content);
		ft_putchar(sep);
		lst = lst->next;
	}
}

int	compute_output(t_list **aoutput)
{
	t_list	*l;
	t_ope	*ope;
	int	a;
	int	b;

	l = *aoutput;
	while (l && l->next && l->next->next)
	{
		if (is_number(l->content)
		&& is_number(l->next->content)
		&& (ope = get_ope(l->next->next->content)))
		{
			free(l->content);
			a = ft_atoi(l->content);
			b = ft_atoi(l->next->content);
			l->content = ft_itoa(ope->f(a, b));
			free(l->next->content);
			free(l->next->next->content);
			l->next = l->next->next->next;
			l = *aoutput;
		}
		else
			l = l->next;
	}
	return (ft_atoi(l->content));
}

int	main(int argc, char **argv)
{
	char **res;
	t_list *output;
	t_list *tmp;

	if (argc != 2)
		return (1);
	res = ft_exprsplit(argv[1], ' ');
	output = to_npi(res);
	ft_putnbr(compute_output(&output));
	ft_putchar('\n');
	while (output)
	{
		tmp = output;
		output = output->next;
		free(tmp->content);
		free(tmp);
	}
	return (0);
}
