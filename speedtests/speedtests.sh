#!/bin/bash
# Date: 2022/01/31
# Description: Compile and run speed tests for ft_containers project

bin_folder="bin/"

if [ "$1" = "" ]; then
	echo "Usage: ./speed_tests.sh [name of cpp files]"
	echo "or ./speed_tests.sh clean"
	exit 1
elif [ "$1" = "clean" ]; then
	echo "Cleaning up..."
	rm -rf $bin_folder
	exit 0
fi

mkdir -p "$bin_folder"

for file in $@; do
	bin_suffix=${file%.cpp}
	clang++ -Wall -Wextra -Werror -std=c++98 -D IS_STD=1 -o "$bin_folder/std_$bin_suffix" $file > /dev/null
	clang++ -Wall -Wextra -Werror -std=c++98 -I../incs/ -o "$bin_folder/ft_$bin_suffix" $file > /dev/null
	printf "[std]: "
	time "./$bin_folder/std_$bin_suffix"
	printf "[ft ]: "
	time "./$bin_folder/ft_$bin_suffix"
done
