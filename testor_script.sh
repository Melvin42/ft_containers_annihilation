#!/bin/bash

#PATH_CONTAINER=~/container_annihilation/testor/
SRC=srcs
CURRENT=includes.hpp
INCLUDES=includes.hpp
LOG=logs
PATH_FT=./rvalton
PATH_TESTS=./tests
ERROR="There is an error. Stop."
CC="clang++ -Wall -Wextra -Werror"
TRC=./deepthough
RED="\033[31m"
GREEN="\033[32m"
CYAN="\033[36m"
UNDERLINE="\e[4m"
BOLD="\e[1m"
ENDCOLOR="\e[0m"

exec 2> /dev/null

generate_main()
{
	rm -rf $SRC/$PATH_TESTS
	mkdir $SRC/$PATH_TESTS
	cp $INCLUDES $SRC/$PATH_TESTS
	cd $SRC
	for i in *.hpp
	do
		NEW_NAME=$(echo $PATH_TESTS/"$i" | sed "s/.hpp/.cpp/g" | sed "s/fn_/test_/g")
		echo -e "new name = " $NEW_NAME
#		cp $PATH_TESTS/$INCLUDES $NEW_NAME #$PATH_TESTS/"$i"
#		echo -e "mv $PATH_TESTS/""$i"" $(echo $PATH_TESTS/""$i"" | sed 's/.hpp/.cpp/g')"
#		mv $PATH_TESTS/"$i" $(echo $PATH_TESTS/"$i" | sed 's/.hpp/.cpp/g')
#		mv $PATH_TESTS/"$i" $NEW_NAME
		echo -e '#include' '<utility>' >> $NEW_NAME
		echo -e '#include' '<string>' >> $NEW_NAME
		echo -e '#include' '<iostream>' >> $NEW_NAME
		echo -e '#include' '<deque>' >> $NEW_NAME
		echo -e '#if STD' >> $NEW_NAME
		echo -e '#include' '<stack>' >> $NEW_NAME
		echo -e '#include' '<map>' >> $NEW_NAME
		echo -e '#include' '<vector>' >> $NEW_NAME
		echo -e '#else' >> $NEW_NAME
		echo -e '#include' '"'$PATH_FT'/stack.hpp''"' >> $NEW_NAME
		echo -e '#include' '"'$PATH_FT'/pair.hpp''"' >> $NEW_NAME
		echo -e '#include' '"'$PATH_FT'/vector.hpp''"' >> $NEW_NAME
		echo -e '#include' '"'$PATH_FT'/map.hpp''"' >> $NEW_NAME
		echo -e '#endif' >> $NEW_NAME
		echo -e '#include' "../""$i" >> $NEW_NAME
		echo -e 'int main(void) {\n' >> $NEW_NAME
		echo -e '\t'"$i" | sed "s/.hpp/();/g" >> $NEW_NAME
		echo -e '\n\treturn 0;\n}' >> $NEW_NAME
	done
}

test_diff()
{
	if ["$DIFF" == ""]
	then
		echo -e "$GREEN$UNDERLINE*Test $NBR :$ENDCOLOR$GREEN OK \U1F603"
		echo -e "\nDiff OK :D" >> $TRC
	else
		echo -e "$RED$UNDERLINE Test $NBR :$ENDCOLOR$RED KO \U1F620"
		echo ${DIFF} | cat -e >> $TRC
		echo -e "\nDiff KO :(" >> $TRC
	fi
}

compile_test()
{
	$CC $PATH_TESTS/$CURRENT && ./a.out | cat -e > $(echo $PATH_TESTS/$LOG/$CURRENT | sed 's/.cpp/.output/g')
}

compile_test_user()
{
	$CC $PATH_FT/*.c $PATH_TESTS/ft_$TEST/test_ft_$TEST.c && $PATH_FT/a.out | cat -e > $PATH_TESTS/ft_$TEST/user_output_test$NBR
	rm $PATH_FT/a.out
}

write_deepthough()
{
	echo -e "\n= ft_$TEST.c ================================================================" >> $TRC
	echo -e "\n$> $CC ft_$TEST.c main.c -o user_exe" >> $TRC
	echo -e "\n= Test $NBR ===================================================" >> $TRC
	echo -e "\n$> ./user_exe $NBR" >> $TRC
	echo -e "\ndiff -U 3 user_output_test$NBR test$NBR.output" >> $TRC
}

test_function()
{
	title

	compile_test
	compile_test_user
	DIFF=$(diff -U 3 $PATH_TESTS/ft_$TEST/user_output_test$NBR $PATH_TESTS/ft_$TEST/test$NBR.output)
	test_diff
}

title()
{
	echo -e "$CYAN$BOLD"
	echo -e " ____________________________________________________________________________"
	echo -e "|                               ft_$TEST                                   |"
	echo -e " ----------------------------------------------------------------------------"
	echo -e "\e[0m"
}

bash ./welcome.sh
echo -e "generating map tests"
SRC=srcs/map
generate_main
echo -e "PWD"
pwd
echo -e "ls tests"
ls tests
echo -e "testing map.empty()"
CURRENT=test_empty.cpp
compile_test
echo -e "cat tests/ft_logs/test_empty.output"
cat tests/ft_logs/test_empty.ouput
compile_test
echo -e "cat tests/std_logs/test_empty.output"
cat tests/ft_logs/test_empty.ouput
ls $SRC/$DIR

make all > $TRC
make clean  > /dev/null

################################################################################

TEST="isalpha"
test_function

