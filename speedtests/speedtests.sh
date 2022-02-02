#!/bin/bash
# Date: 2022/01/31
# Description: Compile and run speed tests for ft_containers project

bin_folder="bin/"

if [ "$1" = "" ]; then
	echo "Usage: ./speed_tests.sh [name of cpp files]"
	echo "or ./speed_tests.sh clean"
	exit 1
fi

mkdir -p "$bin_folder"

for file in $@; do
	bin_suffix=${file%.cpp}
	clang++ -Wall -Wextra -Werror -std=c++98 -D IS_STD=1 -o "$bin_folder/std_$bin_suffix" $file
	clang++ -Wall -Wextra -Werror -std=c++98 -o "$bin_folder/ft_$bin_suffix" $file
done
