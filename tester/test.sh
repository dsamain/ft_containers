seed=$RANDOM
printf "Seed: $seed\n"

printf "\033[1;94m		VECTOR\n\033[0m"
./test_one.sh vector constructor
./test_one.sh vector basic
./test_one.sh vector iterator

printf "\033[1;94m\n		STACK\n\033[0m"
./test_one.sh stack stack

printf "\033[1;94m\n	VECTOR SPEED TEST\n\033[0m"
printf "\033[1;36mft: \n\033[0m"
g++ -std=c++98 -Wall -Wextra -Werror speed/vector.cpp utils.cpp ; ./a.out $seed ; rm a.out
printf "\033[1;36m\nstd: \n\033[0m"
g++ -std=c++98 -Wall -Wextra -Werror -D STD speed/vector.cpp utils.cpp ; ./a.out $seed ; rm a.out

printf "\033[1;94m\n	MAP SPEED TEST\n\033[0m"
printf "\033[1;36mft: \n\033[0m"
g++ -std=c++98 -Wall -Wextra -Werror speed/map.cpp utils.cpp ; ./a.out $seed ; rm a.out
printf "\033[1;36m\nstd: \n\033[0m"
g++ -std=c++98 -Wall -Wextra -Werror -D STD speed/map.cpp utils.cpp ; ./a.out $seed ; rm a.out

printf "\033[1;94m\n	SET SPEED TEST\n\033[0m"
printf "\033[1;36mft: \n\033[0m"
g++ -std=c++98 -Wall -Wextra -Werror -D STD speed/set.cpp utils.cpp ; ./a.out $seed ; rm a.out
printf "\033[1;36m\nstd: \n\033[0m"
g++ -std=c++98 -Wall -Wextra -Werror speed/set.cpp utils.cpp ; ./a.out $seed ; rm a.out

printf "\033[1;94m\n	RED BLACK TREE\n\033[0m"
g++ -std=c++98 -Wall -Wextra -Werror -D DEBUG redblacktree.cpp utils.cpp ; ./a.out $seed ; rm a.out