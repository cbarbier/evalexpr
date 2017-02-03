/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Eval_expr.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 12:31:51 by cbarbier          #+#    #+#             */
/*   Updated: 2016/07/12 14:18:23 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_EXPR_H
# define EVAL_EXPR_H
# define NB_OPERATIONS 5

typedef struct s_ope
{
	char	*sign;
	int	priority;
	int	(*f)(int, int);
} t_ope;
int	Eval_expr(char *str);
int	addition(int a, int b);
int	substraction(int a, int b);
int	division(int a, int b);
int	multiplication(int a, int b);
int	modulo(int a, int b);
t_ope	operations[NB_OPERATIONS] = 
	{{"+", 1, &addition},
	{"-", 1, &substraction},
	{"/", 2, &division},
	{"*", 2, &multiplication},
	{"%", 2, &modulo}};
#endif
