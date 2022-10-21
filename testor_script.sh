#!/bin/bash

#PATH_CONTAINER=~/container_annihilation/testor/
SRC=srcs
CURRENT=includes.hpp
INCLUDES=includes.hpp
LOG=logs
INCLUDE_FT=../../../rvalton
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

#exec 2> /dev/null

generate_main()
{
	rm -rf $SRC/$DIR/$PATH_TESTS
	mkdir $SRC/$DIR/$PATH_TESTS
	cp $INCLUDES $SRC/$DIR/$PATH_TESTS
	cd $SRC/$DIR
	for i in *.hpp
	do
		NEW_NAME=$(echo $PATH_TESTS/"$i" | sed "s/.hpp/.cpp/g" | sed "s/fn_/test_/g")
		echo "new name = " $NEW_NAME
#		cp $PATH_TESTS/$INCLUDES $NEW_NAME #$PATH_TESTS/"$i"
#		echo -e "mv $PATH_TESTS/""$i"" $(echo $PATH_TESTS/""$i"" | sed 's/.hpp/.cpp/g')"
#		mv $PATH_TESTS/"$i" $(echo $PATH_TESTS/"$i" | sed 's/.hpp/.cpp/g')
#		mv $PATH_TESTS/"$i" $NEW_NAME
		echo '#include' '<utility>' >> $NEW_NAME
		echo '#include' '<string>' >> $NEW_NAME
		echo '#include' '<iostream>' >> $NEW_NAME
		echo '#include' '<deque>' >> $NEW_NAME
		echo '#if STD' >> $NEW_NAME
		echo '#include' '<stack>' >> $NEW_NAME
		echo '#include' '<map>' >> $NEW_NAME
		echo '#include' '<vector>' >> $NEW_NAME
		echo '#else' >> $NEW_NAME
		echo '#include' '"'$INCLUDE_FT'/stack.hpp''"' >> $NEW_NAME
		echo '#include' '"'$INCLUDE_FT'/pair.hpp''"' >> $NEW_NAME
		echo '#include' '"'$INCLUDE_FT'/vector.hpp''"' >> $NEW_NAME
		echo '#include' '"'$INCLUDE_FT'/map.hpp''"' >> $NEW_NAME
		echo '#endif' >> $NEW_NAME
		echo '#include' '"'"../""$i"'"' >> $NEW_NAME
		echo 'int main(void) {\n' >> $NEW_NAME
		echo '\t'"$i" | sed "s/.hpp/();/g" >> $NEW_NAME
		echo '\n\treturn 0;\n}' >> $NEW_NAME
	done
	cd ../..
}

test_diff()
{
	if ["$DIFF" == ""]
	then
		echo "$GREEN$UNDERLINE*Test $NBR :$ENDCOLOR$GREEN OK \U1F603"
		echo "\nDiff OK :D" >> $TRC
	else
		echo "$RED$UNDERLINE Test $NBR :$ENDCOLOR$RED KO \U1F620"
		echo ${DIFF} | cat -e >> $TRC
		echo "\nDiff KO :(" >> $TRC
	fi
}

compile_test()
{
	pwd
	$CC $SRC/$DIR/$PATH_TESTS/$CURRENT.cpp -o ./bin/$CURRENT.std && ./bin/$CURRENT.std | cat -e > $(echo $LOG/$CURRENT.std | sed 's/.std/.output.std/g')
}

compile_test_user()
{
	pwd
	$CC $SRC/$DIR/$PATH_TESTS/$CURRENT.cpp -o ./bin/$CURRENT.ft && ./bin/$CURRENT.ft | cat -e > $(echo $LOG/$CURRENT.ft | sed 's/.ft/.output.ft/g')
}

write_deepthough()
{
	echo "\n= ft_$TEST.c ================================================================" >> $TRC
	echo "\n$> $CC ft_$TEST.c main.c -o user_exe" >> $TRC
	echo "\n= Test $NBR ===================================================" >> $TRC
	echo "\n$> ./user_exe $NBR" >> $TRC
	echo "\ndiff -U 3 user_output_test$NBR test$NBR.output" >> $TRC
}

test_function()
{
	title

	compile_test
#	compile_test_user
#	DIFF=$(diff -U 3 $LOGS/$CURRENT.output.std $LOGS/$CURRENT.output.ft)
#	test_diff
}

title()
{
	echo "$CYAN$BOLD"
	echo " ____________________________________________________________________________"
	echo "|                               ft_$TEST                                   |"
	echo " ----------------------------------------------------------------------------"
	echo "$ENDCOLOR"
}

bash ./welcome.sh
echo "generating map tests"
DIR=map
generate_main
pwd
#test_folder() {
#for i in *
#do
	DIR=$i
	cd $DIR
	for j in *.cpp 
		CURRENT=$(echo $j # a sed de son .cpp
	do
	done
	cd ..
#done

CURRENT=test_empty
compile_test
pwd
ls
#ls $SRC/$DIR

#make all > $TRC
#make clean  > /dev/null

################################################################################

TEST=$CURRENT
test_function

