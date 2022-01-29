#!/bin/bash

# If the user didn't input 2 arguments
if [[ $# -ne 2 ]];
then
	echo 'Usage fixformat.sh <dirname> <opfile>'
 	exit 1

# If the directory the user input isn't valid
elif [[ ! -d $1 ]];
then
	echo "Error $1 is not a valid directory"
	exit 1

# If the two arguments are invoked correctly
else
	echo "User Email,Name (Original Name),Lab,Total Duration (Minutes)" > $2
	
	# Looping through each file
	for log in `find $1 -iname "lab-[abcdefi].csv"`;
	do
		# Getting the lab letter
		labLetter="`basename $log | cut -c5-5 | tr a-z A-Z`"

		# 1. Initializing each field
		# 2. Depending on the total number of field, defining each field
		# 3. If it isn't the first line of the log file, print the output in the outputfile 
		awk -v lab=$labLetter '
		BEGIN { OFS=","; FS=","; name=0; email=0; join=0; leave=0; duration=0; guest=0 }
		{ name=$1; email=$2;
		
		{ if (NF == 4) {duration=$3} }
		{ if (NF == 6) {duration=$5} } 

		{ if (NR > 1) { print email,name,lab,duration } } }' $log >> $2

	done
	exit 0
fi
