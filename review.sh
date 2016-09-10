#!/bin/bash

#Store current directory
DIR=$(pwd)
#If we were given a directory
if [[ $1 ]]
then
	# Go to it
	cd $1
fi

# Source the README file, break things formatted like ``this`` into lines
# Pipe the contents of the file to grep, grep returns all matches of two backticks followed by anything without whitespace that is also followed by two backticks
FILES=$(cat README.rst | grep -o "\`\`[^ ]*\`\`")

# Simple for loop
for FILE in $FILES
do
	# Take off the backticks (create a substring two in from the left and two in from the right
	NOTICK=${FILE:2:-2}
	# Do a test run of highlight to see if it can understand the file extension
	# (better than using the file command)
	         # Execute command                 dump stdout  route stderr to stdout so that it will be stored in ERROR
	ERROR=$((highlight -O ansi $NOTICK > /dev/null) 2>&1)
	# If ERROR is empty
	if [[ -z $ERROR ]]
	then
		# Pretty print code, pipe to nl for line numbers
		highlight -O ansi $NOTICK | nl
		# wait for user ENTER
		read whocares
		clear
	fi
done

# return user to directory at start of script
# Use double quotes to handle paths with whitespace in them
cd "$DIR"
