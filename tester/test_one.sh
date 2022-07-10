#!/bin/zsh
c++ -std=c++98 -Wall -Wextra -Werror $1/$2.cpp utils.cpp -o ft.out 2>> ./log/$1/log
c++ -std=c++98 -Wall -Wextra -Werror -D STD $1/$2.cpp utils.cpp -o std.out 2>> ./log/$1/log
printf "$2 : \n"
echo -n " Compilation "
if [ $? -eq 1 ]; then
	echo -n "KO ❌ "
else
	echo -n "OK ✅ "
	./ft.out > log/$1/$2.ft
	./std.out > log/$1/$2.std
	diff log/$1/$2.ft log/$1/$2.std > log/$1/$2.diff
	comp_value=$?

	echo -n "| diff "
	if [ $comp_value -eq 0 ]
	then
		echo "OK ✅"
	else
		echo  "KO ❌"
	fi

fi

rm ft.out std.out 2>> ./log/$1/log
#rm log
