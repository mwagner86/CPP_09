#!/bin/sh

# Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White
# Reset
Color_Off='\033[0m'       # Text Reset

# -------------------------------------------------------------

printf "${BGreen} Making program...\n${Color_Off}"
make re

# -------------------------------------------------------------

printf "${BRed} Run without arguments... \n${Color_Off}"
./btc

# -------------------------------------------------------------

printf "${BRed} Empty file... \n${Color_Off}"
touch empty.txt
./btc empty.txt
printf "${BRed} Wrong file name... \n${Color_Off}"
./btc wrong.txt
rm -f empty.txt

# -------------------------------------------------------------

printf "${BYellow} Negative number... \n${Color_Off}"
touch negative_numbers.txt
echo "date | value
2017-02-19 | -2
2017-02-22 | -130.01
2017-02-25 | -10.37
2017-02-28 | -999" > negative_numbers.txt
./btc negative_numbers.txt
rm -f negative_numbers.txt

# -------------------------------------------------------------

printf "${BYellow} Numbers larger than 1000... \n${Color_Off}"
touch too_large.txt
echo "date | value
2017-02-19 | 1050.87
2017-02-22 | 1130.01
2017-02-25 | 1150.37
2017-02-28 | 1190.89" > too_large.txt
./btc too_large.txt
rm -f too_large.txt

# -------------------------------------------------------------

printf "${BYellow} Invalid date... \n${Color_Off}"
touch invalid_date.txt
echo "date | value
2017-13-19 | 50.87
2017-02-29 | 130.01
2017-06-31 | 150.37
2017-55-55 | 190.89" > invalid_date.txt
./btc invalid_date.txt
rm -f invalid_date.txt

# -------------------------------------------------------------

printf "${BBlue} Subject input.txt... \n${Color_Off}"
touch input.txt
echo "date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1
2011-01-03 | 1.2
2011-01-09 | 1
2012-01-11 | -1
2001-42-42
2012-01-11 | 1
2012-01-11 | 2147483648" > input.txt
./btc input.txt
rm -f input.txt

# -------------------------------------------------------------

printf "${BBlue} Test inputs... \n${Color_Off}"
touch input.txt
echo "date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1
2011-01-03 | 1.2
2011-01-09 | 1
2012-01-11 | -1
2001-42-42
2012-01-11 | 1
2012-01-11 | 2147483648
2012-03-01 | 2
2013-03-01 | 2
12312312 || 12312412
| 2010-05-01 2
|||||||||||||||||
|
1
5555555555555555555555555555555555555555555555555555555
55555555555555555555555555 | 55555555555555555555555555555
55555555555555555555555555 | j
2010-05-01 | d
2011-01-32 | 1
2012-02-29 | 1
2013-02-29 | 1
2011-01-09 |1
2011-01-09| 1
2-011-01-09 | 1
2-01101-09 | 1
2011-1.3-09 | 1
2011-12-0t | 1
2011-12-00 | 1
2011-00-05 | 1
0000-12-05 | 1
2012-20-05 | 1
2040-12-05 | 1
0010-12-05 | 1
0001-01-01 | 1
2012-12-05 | 1000.0
2012-12-05 | 1001
2012-12-05 | 1000.1
2012-12-05 | 10.00.1" > input.txt
./btc input.txt
rm -f input.txt

# -------------------------------------------------------------

make fclean