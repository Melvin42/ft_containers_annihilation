all: main_vector.cpp main_map.cpp
	rm -f ft_exec_vector std_exec_vector ft_exec_map std_exec_map debug_exec_vector debug_exec_map
	clang++ -Wall -Wextra -Werror -std=c++98 main_vector.cpp -o ft_exec_vector
	clang++ -Wall -Wextra -Werror -std=c++98 main_map.cpp -o ft_exec_map

vector: main_vector.cpp
	rm -f ft_exec_vector
	clang++ -Wall -Wextra -Werror main_vector.cpp -o ft_exec_vector
	#clang++ -Wall -Wextra -Werror -std=c++98 main_vector.cpp -o ft_exec_vector

map: main_map.cpp
	rm -f ft_exec_map
	clang++ -Wall -Wextra -Werror main_map.cpp -o ft_exec_map
	#clang++ -Wall -Wextra -Werror -std=c++98 main_map.cpp -o ft_exec_map

std-vector: main_vector.cpp
	rm -f std_exec_vector
	clang++ -Wall -Wextra -Werror -D STD -std=c++11 main_vector.cpp -o std_exec_vector

std-map: main_map.cpp
	rm -f std_exec_map
	clang++ -Wall -Wextra -Werror -D STD -std=c++11 main_map.cpp -o std_exec_map

debug-vector: main_vector.cpp
	rm -f debug_exec_vector
	c++ -Wall -Wextra -Werror -g3 -std=c++98 main_vector.cpp -o debug_exec_vector

debug-map: main_map.cpp
	rm -f debug_exec_map
	clang++ -Wall -Wextra -Werror -g3 main_map.cpp -o debug_exec_map
#	c++ -Wall -Wextra -Werror -g3 -std=c++98 main_map.cpp -o debug_exec_map

clean:
	rm -f *.o

fclean: clean
	rm -f ft_exec_vector std_exec_vector ft_exec_map std_exec_map debug_exec_vector debug_exec_map

re: fclean all

.PHONY: all ft-vector ft-map std-vector std-map debug-vector debug-map clean fclean re
