#!/bin/bash

#PATH_CONTAINER=~/container_annihilation/testor/
SRC=srcs
CURRENT=includes.hpp
INCLUDES=includes.hpp
LOG=log
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

generate_main()
{
	rm -rf $SRC/$PATH_TESTS
	mkdir $SRC/$PATH_TESTS
	cp $INCLUDES $SRC/$PATH_TESTS
	cd $SRC
	for i in *.cpp
	do
		cp $PATH_TESTS/$INCLUDES $PATH_TESTS/"$i"
		mv $PATH_TESTS/"$i" $(echo $PATH_TESTS/"$i" | sed 's/.hpp/.cpp/g')
		echo -e '#include' "$i" >> $PATH_TESTS/"$i"
		echo -e 'int main(void) {\n' >> $PATH_TESTS/"$i"
		echo -e '\t'"$i" | sed "s/.cpp/();/g" >> $PATH_TESTS/"$i"
		echo -e '\n\treturn 0;\n' >> $PATH_TESTS/"$i"
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
	$CC $PATH_TESTS/$CURRENT && ./a.out | cat -e > $PATH_TESTS/$LOG/$CURRENT.output
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
echo -e "testing map.empty()"
CURRENT=empty.cpp
compile_test
ls $SRC/$DIR

make all > $TRC
make clean  > /dev/null

################################################################################

TEST="isalpha"
test_function

