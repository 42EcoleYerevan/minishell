#include "minishell.h"

void ft_validator_test(t_shell *shell, char *str, int answer);

void	ft_validator_run_test(t_shell *shell)
{
	fprintf(stderr, "\n\033[31mVALIDATOR TESTING\033[0m\n");

	// quotes
	fprintf(stderr, "\nquotes testing ...\n");
	ft_validator_test(shell, "\"", 1);
	ft_validator_test(shell, "\"\"", 0);
	ft_validator_test(shell, "\"a\"", 0);
	ft_validator_test(shell, "\'\'", 0);
	ft_validator_test(shell, "\'a\'", 0);
	ft_validator_test(shell, "\'\"", 1);
	ft_validator_test(shell, "\"\'", 1);
	ft_validator_test(shell, "\"\"\'\'", 0);
	ft_validator_test(shell, "echo leha \"", 1);
	ft_validator_test(shell, "echo leha \"\"", 0);
	ft_validator_test(shell, "echo leha \"asdf\"", 0);
	ft_validator_test(shell, "echo leha \"$PATH\"", 0);
	ft_validator_test(shell, "echo leha \'$PATH\'", 0);
	ft_validator_test(shell, "'echo leha \'$PATH\'leha'", 0);
	ft_validator_test(shell, "'echo leha \'$PATH\'leha|'", 0);

	// redirects
	fprintf(stderr, "\redirect testing ...\n");
	ft_validator_test(shell, "echo <", 258);
	ft_validator_test(shell, "echo < test", 1);
	ft_validator_test(shell, "echo < minishell.h", 0);
	ft_validator_test(shell, "< minishell.h", 0);
	ft_validator_test(shell, "<\">\"", 1);

	// pipes
	fprintf(stderr, "\npipes testing ...\n");
	ft_validator_test(shell, "|", 258);
	ft_validator_test(shell, "| echo", 258);
	ft_validator_test(shell, "echo |", 258);
	ft_validator_test(shell, "    |          ", 258);
	ft_validator_test(shell, "leha | <", 258);
	ft_validator_test(shell, "cat < file.txt | <", 258);
	ft_validator_test(shell, "echo | echo", 0);
}

void ft_validator_test(t_shell *shell, char *str, int answer)
{
	t_mlist *list = ft_parser(shell, str);
	exit_status = ft_is_valid_linked_list(list);
	if (answer == exit_status)
		fprintf(stderr, "\033[32mOK %d\033[0m\n", exit_status);
	else
		fprintf(stderr, "\033[31mKO %d\033[0m\n", exit_status);
}
