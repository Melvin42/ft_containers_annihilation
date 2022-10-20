#!/bin/bash

#PATH_CONTAINER=~/container_annihilation/testor/
PATH_FT=./container
PATH_TESTS=./tests
ERROR="There is an error. Stop."
CC="clang++ -Wall -Wextra -Werror"
TRC=.~/deepthough
RED="\033[31m"
GREEN="\033[32m"
CYAN="\033[36m"
UNDERLINE="\e[4m"
BOLD="\e[1m"
ENDCOLOR="\e[0m"

exec 2> /dev/null

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
	$CC $PATH_TESTS/ft_$TEST/test_true_$TEST.c && ./a.out | cat -e > $PATH_TESTS/ft_$TEST/test$NBR.output
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

echo "" > ./deepthought
cd $PATH_CONTAINER

make all > $TRC
make clean  > /dev/null

################################################################################

TEST="isalpha"
test_function

################################################################################

TEST="isdigit"
test_function

################################################################################

TEST="isalnum"
test_function

################################################################################

TEST="isascii"
test_function

################################################################################

TEST="isprint"
test_function

################################################################################

TEST="toupper"
test_function

################################################################################

TEST="tolower"
test_function

################################################################################

TEST="strlen"
test_function
