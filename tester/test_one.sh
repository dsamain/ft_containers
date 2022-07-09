c++ -std=c++98 -Wall -Wextra -Werror $1.cpp -o ft.out 2> log
c++ -std=c++98 -Wall -Wextra -Werror -D STD $1.cpp -o std.out 2> log
if [ $? -eq 1 ]; then
	echo "Compilation KO ❌"
else
	./ft.out > ft
	./std.out > std
	diff ft std
	comp_value=$?

	if [ $comp_value -eq 0 ]
	then
		echo "diff OK ✅"
	else
		echo "diff KO ❌"
	fi

fi

rm ft.out std.out ft std 2>> log
#rm log
