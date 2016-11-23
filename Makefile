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

ifeq ($(shell uname), Darwin)
FOLDER	=	-I $(HDIR) -I./$(LIB_SDL)/include -I./$(LIB_SDL)/lib/ -I./$(PATH_SFML)/include/
else
FOLDER	=	-I $(HDIR) -I./$(LIB_SDL)/include -I./$(LIB_SDL)/lib/ -I./$(PATH_SFML)/usr/local/include/
endif

LIB_SDL 		= SDL
PATH_SDL 		= SDL2-2.0.5
PATH_SDL_IMG 	= SDL2_image-2.0.1
SDL 			= `./$(LIB_SDL)/bin/sdl2-config --cflags --libs` -lSDL2_image

LIB_SFML 	= SFML
PATH_SFML 	= SFML-2.4.0
SFML 		= -Xlinker -rpath -Xlinker ./$(PATH_SFML)/lib/ -L./$(PATH_SFML)/lib -lsfml-graphics -lsfml-window -lsfml-system

SRCA	=	$(shell cd $(SDIR) && ls -1 *.$(F_EXT))

SRCH	=	$(shell cd $(HDIR) && ls -1 *.$(H_EXT))

SRCO	=	$(SRCA:$(F_EXT)=.o)

SRC 	=	$(patsubst %.$(F_EXT), $(SDIR)%.$(F_EXT), $(SRCA))
HDR		=	$(patsubst %.$(H_EXT), $(HDIR)%.$(H_EXT), $(SRCH))
OBJ		=	$(patsubst %.$(F_EXT), $(ODIR)%.o, $(SRCA))

all: sfml sdl compil

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

sfml:
	@echo "\033[32mDownloading SFML ...\033[0m"
	@curl http://mirror2.sfml-dev.org/files/SFML-2.4.0-sources.zip -o $(PATH_SFML).zip
	@echo "\033[32mCompiling SFML...\033[0m"
	@unzip $(PATH_SFML).zip
	@cat patch_sfml > $(PATH_SFML)/src/SFML/Graphics/CMakeLists.txt
ifeq ($(shell uname), Darwin)
	@cd $(PATH_SFML) && cmake -DCMAKE_INSTALL_PREFIX=/Library/Frameworks/Mono.framework/Headers/freetype2/ . && make -j 8 && make -j 8 install DESTDIR=./
	@cp -r $(PATH_SFML)/Library/Frameworks $(PATH_SFML)
else
	@cd $(PATH_SFML) && cmake . && make -j 8 && make -j 8 install DESTDIR=./
endif
	@rm -rf $(PATH_SFML).zip


compil:
	@echo "\033[32m compiling $(NAME) >>> \c \033[0m"
	@mkdir -p $(ODIR)
	@make -j 99 $(NAME)
	@echo "\033[37m END $(NAME)\033[0m"

$(NAME): $(OBJ) $(SRC)
	@$(CC) -o $(NAME) $(OBJ) $(SDL) $(SFML)

$(ODIR)%.o: $(SDIR)%.$(F_EXT) $(HDR)
	@$(CC) -c $< -o $@ $(FLAGS) $(FOLDER)
	@echo "\033[32m ok \033[33m $@\033[0m"

clean:
	@rm -rf $(ODIR)
	@rm -rf the_leaks

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(PATH_SDL)
	@rm -rf $(PATH_SFML).zip
	@rm -rf $(PATH_SFML)

re: fclean all

run:
	@clear
	@make no
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
