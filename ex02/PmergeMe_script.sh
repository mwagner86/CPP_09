#!/bin/bash

echo '*** ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`'

./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
# For Mac: ./PmergeMe `jot -r 3000 1 1000 | tr '\n' ' '`

echo
echo "*** ./PmergeMe 3 5 9 7 4"

./PmergeMe 3 5 9 7 4

echo
echo "*** ./PmergeMe 1 252 15 37 29 134"

./PmergeMe 1 252 15 37 29 134

echo
echo "*** ./PmergeMe 7 5 3 2 3 4 5"
./PmergeMe 7 5 3 2 3 4 5

echo
echo '*** ./PmergeMe "-1" "2"'
./PmergeMe "-1" "2"