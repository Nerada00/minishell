SRCS = 	main.c \
		init.c \
		builtins/builtin.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/env_utils.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/export.c \
		builtins/pwd.c \
		builtins/unset.c \
		token/quotes.c\
		token/validate_user_input.c\
		token/token.c\
		token/word.c\
		token/add_command_info_node.c\
		libft/ft_calloc.c\
		libft/ft_memset.c\
		libft/ft_putchar_fd.c\
		libft/ft_putstr_fd.c\
		libft/ft_split.c\
		libft/ft_strjoin.c\
		libft/ft_free_elem.c\
		libft/ft_strlcpy.c\
		libft/ft_strncmp.c\
		libft/ft_strcmp.c\
		libft/ft_substr.c\
		libft/ft_strchr.c\
		libft/ft_strdup.c\
		libft/ft_isalnum.c\
		libft/ft_strlen.c\
		libft/ft_putendl_fd.c\
		libft/ft_isalpha.c\
		libft/ft_bzero.c\
		libft/ft_isdigit.c\
		libft/ft_itoa.c\
		libft/ft_isspace.c\
		libft/ft_copy_tab.c\
		libft/ft_dup_tab.c\
		libft/ft_free_tab.c\
		libft/ft_free_tab_with_len.c\
		libft/ft_tab_len.c\
		libft/ft_is_in.c\
		libft/ft_memcpy.c\
		libft/ft_strjoin_tab_len.c\
		lib/init_dynamic_arr.c \
		lib/dynamic_arr.c \
		lib/clear_dynamic_arr.c \
		lib/print_dynamic_arr.c \
		secure/free.c\
		secure/free_with_status.c\
		signal/heredoc_signal.c\
		signal/fork_signal.c\
		signal/signal.c\
		print/print_msg.c\
		print/print_error_and_set_exit_status.c\
		heredoc/heredoc.c\
		heredoc/heredoc_fork.c\
		exec/exec.c\
		exec/fd.c\
		exec/close_fd.c\
		exec/check.c\
		exec/dup.c\


OBJS = $(SRCS:.c=.o)

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -I.
RM = rm -f

all: $(NAME)

	
$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME) -lreadline -lhistory

##############   barre de chargement    ##############

	@echo -n "\033[33m [EXECUTION] : \e[38;5;221m Compiling Minishell... "
	@total_iterations=30; \
	i=0; \
	while [ $$i -lt $$total_iterations ]; do \
		sleep 0.01; \
		printf "\e[38;5;212m▇\033[0m"; \
		i=$$((i + 1)); \
	done
	
#header nom du programme

	@echo
	@echo
	@echo "\e[38;5;219m =========== Compilation completed successfully.=========== \033[0m"
	@echo 
	@echo "\e[38;5;214m ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \033[0m"     
	@echo "\e[38;5;215m ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║      \033[0m"
	@echo "\e[38;5;216m ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║       \033[0m"   
	@echo "\e[38;5;217m ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║        \033[0m"  
	@echo "\e[38;5;218m ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗    \033[0m" 
	@echo "\e[38;5;219m ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝	 \033[0m"

	@echo


$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@$(RM) $(OBJS)

#header du clean
	@echo
	@echo "\033[33;5m	  =========== OBJ was removed.=========== \033[0m"
	@echo
	@echo "\e[38;5;220m ██████╗ ███████╗███╗   ███╗ ██████╗ ██╗   ██╗███████╗██████╗ \033[0m"
	@echo "\e[38;5;221m ██╔══██╗██╔════╝████╗ ████║██╔═══██╗██║   ██║██╔════╝██╔══██╗ \033[0m"
	@echo "\e[38;5;222m ██████╔╝█████╗  ██╔████╔██║██║   ██║██║   ██║█████╗  ██║  ██║ \033[0m"
	@echo "\e[38;5;223m ██╔══██╗██╔══╝  ██║╚██╔╝██║██║   ██║╚██╗ ██╔╝██╔══╝  ██║  ██║ \033[0m"
	@echo "\e[38;5;224m ██║  ██║███████╗██║ ╚═╝ ██║╚██████╔╝ ╚████╔╝ ███████╗██████╔╝ \033[0m"
	@echo "\e[38;5;225m ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝   ╚═══╝  ╚══════╝╚═════╝  \033[0m"
	@echo

fclean:
	@$(RM) $(OBJS)
	@$(RM) $(NAME)

#header du fclean
	@echo
	@echo "\033[32;5m 	  =========== All was removed.=========== \033[0m"
	@echo
	@echo "\e[38;5;410m ██████╗ ███████╗███╗   ███╗ ██████╗ ██╗   ██╗███████╗██████╗ \033[0m"
	@echo "\e[38;5;411m ██╔══██╗██╔════╝████╗ ████║██╔═══██╗██║   ██║██╔════╝██╔══██╗ \033[0m"
	@echo "\e[38;5;412m ██████╔╝█████╗  ██╔████╔██║██║   ██║██║   ██║█████╗  ██║  ██║ \033[0m"
	@echo "\e[38;5;413m ██╔══██╗██╔══╝  ██║╚██╔╝██║██║   ██║╚██╗ ██╔╝██╔══╝  ██║  ██║ \033[0m"
	@echo "\e[38;5;414m ██║  ██║███████╗██║ ╚═╝ ██║╚██████╔╝ ╚████╔╝ ███████╗██████╔╝ \033[0m"
	@echo "\e[38;5;415m ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝   ╚═══╝  ╚══════╝╚═════╝  \033[0m"
	@echo

re: fclean all

.PHONY: clean fclean all re                                   
