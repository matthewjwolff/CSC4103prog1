#!/bin/bash

source '/usr/lib/smartlog/smartlog.sh'

prompt "Filename"
if check_var "reply" "$REPLY"
then
	if check_file "given" "$REPLY"
	then
		# Pretty print
		highlight -O ansi $REPLY
		fileext=${REPLY##*.}
		if [ fileext == '.java' ]
		then
			log "Compiling..."
			if javac $REPLY 2> /dev/null > /dev/null
			then
				ok
			else
				fail
			fi
		else
			if [ fileext == '.c' ]
			then
				log "Compiling..."
				if gcc $REPLY 2> /dev/null > /dev/null
				then
					ok
				else
					fail
				fi
			else fail "Bad extension"
			fi
		fi
	else
		fail "That file was not found"
	fi
fi

