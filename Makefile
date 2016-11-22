# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/15 18:31:49 by pilespin          #+#    #+#              #
#    Updated: 2016/05/16 17:17:36 by pilespin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all compil clean fclean re run leaks allleaks coffee want
	
NAME	=	mod

CC		=	g++ -std=c++11 -g
FLAGS	=	-Wall -Wextra -Werror -Wfatal-errors

SDIR	=	src/
HDIR	=	includes/
ODIR	=	obj/
F_EXT	=	cpp
H_EXT	=	hpp
FOLDER	=	-I $(HDIR) -I./$(LIB_SDL)/include -I./$(LIB_SDL)/lib/

LIB_SDL 		= SDL
PATH_SDL 		= SDL2-2.0.5
PATH_SDL_IMG 	= SDL2_image-2.0.1
SDL 			= `./$(LIB_SDL)/bin/sdl2-config --cflags --libs` -lSDL2_image

SRCA	=	$(shell cd $(SDIR) && ls -1 *.$(F_EXT))

SRCH	=	$(shell cd $(HDIR) && ls -1 *.$(H_EXT))

SRCO	=	$(SRCA:$(F_EXT)=.o)

SRC 	=	$(patsubst %.$(F_EXT), $(SDIR)%.$(F_EXT), $(SRCA))
HDR		=	$(patsubst %.$(H_EXT), $(HDIR)%.$(H_EXT), $(SRCH))
OBJ		=	$(patsubst %.$(F_EXT), $(ODIR)%.o, $(SRCA))

all: sdl compil

no: compil

sdl:
	@echo "\033[32mDownloading SDL ...\033[0m"
	@curl https://www.libsdl.org/release/SDL2-2.0.5.tar.gz -o $(PATH_SDL).tar.gz
	@curl https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.1.tar.gz -o $(PATH_SDL_IMG).tar.gz
	@echo "\033[32mCompiling SDL ...\033[0m"
	@mkdir -p $(LIB_SDL)
	@tar -xf $(PATH_SDL).tar.gz
	@tar -xf $(PATH_SDL_IMG).tar.gz
	@cd $(PATH_SDL) && ./configure --prefix=`cd ../$(LIB_SDL) && pwd` && make -j 8 && make -j 8 install
	@cd $(PATH_SDL_IMG) && ./configure --prefix=`cd ../$(LIB_SDL) && pwd` && make -j 8 && make -j 8 install
	@rm -rf $(PATH_SDL)
	@rm -rf $(PATH_SDL_IMG)
	@rm -rf $(PATH_SDL_IMG).tar.gz
	@rm -rf $(PATH_SDL).tar.gz

compil:
	@echo "\033[32m compiling $(NAME) >>> \c \033[0m"
	@mkdir -p $(ODIR)
	@make -j 99 $(NAME)
	@echo "\033[37m END $(NAME)\033[0m"

$(NAME): $(OBJ) $(SRC)
	@$(CC) -o $(NAME) $(OBJ) $(SDL)

$(ODIR)%.o: $(SDIR)%.$(F_EXT) $(HDR)
	@$(CC) -c $< -o $@ $(FLAGS) $(FOLDER)
	@echo "\033[32m ok \033[33m $@\033[0m"

clean:
	@rm -rf $(ODIR)
	@rm -rf the_leaks

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(PATH_SDL)

re: fclean all

run:
	@clear
	@make
	@./$(NAME)

leaks:
	@zsh -c "while ((1)) {sleep 1 ; leaks $(NAME) | grep -A 1 Leak > the_leaks ; clear && cat the_leaks}"

allleaks:
	@zsh -c "while ((1)) {sleep 1 ; leaks $(NAME) > the_leaks ; clear && cat the_leaks}"

coffee:
	@zsh -c "while ((1)) {make want}"


want:
	@clear
	@echo "                        \`:.      				"
	@echo "                          \`:.      				"
	@echo "                  .:'     ,::      				"
	@echo "                 .:'      ;:'      				"
	@echo "                 ::      ;:'      				"
	@echo "                  :    .:'      					"
	@echo "                   \`.  :.      					"
	@echo "          _________________________      		"
	@echo "         : _ _ _ _ _ _ _ _ _ _ _ _ :      		"
	@echo "     ,---:\".\".\".\".\".\".\".\".\".\".\".\".\":"
	@echo "    : ,'\"\`::.:.:.:.:.:.:.:.:.:.:.::'      		"
	@echo "    \`.\`.  \`:-===-===-===-===-===-:'      		"
	@echo "      \`.\`-._:                   :      		"
	@echo "        \`-.__\`.               ,'      			"
	@echo "    ,--------\`\"\`-------------'--------.      	"
	@echo "     \`\"--.__                   __.--\"'   	   	"
	@echo "            \`\"\"-------------\"\"'    			"
	@echo "    											  	"
	@sleep 0.5
	@clear
	@echo "                       \`:.      				"
	@echo "                          \`:.      				"
	@echo "                   .:'     ,::      				"
	@echo "                .:'        ;:'      				"
	@echo "                ::        ;:'      				"
	@echo "                 :      .:'      				"
	@echo "                  \`.    :.      				"
	@echo "          _________________________      		"
	@echo "         : _ _ _ _ _ _ _ _ _ _ _ _ :      		"
	@echo "     ,---:\".\".\".\".\".\".\".\".\".\".\".\".\":"
	@echo "    : ,'\"\`::.:.:.:.:.:.:.:.:.:.:.::'      		"
	@echo "    \`.\`.  \`:-===-===-===-===-===-:'      		"
	@echo "      \`.\`-._:                   :      		"
	@echo "        \`-.__\`.               ,'      			"
	@echo "    ,--------\`\"\`-------------'--------.      	"
	@echo "     \`\"--.__                   __.--\"'   	   	"
	@echo "            \`\"\"-------------\"\"'    			"
	@sleep 0.5
