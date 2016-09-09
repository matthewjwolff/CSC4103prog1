
source '/usr/lib/smartlog/smartlog.sh'

prompt "Filename"
if check_var "reply" "$REPLY"
then
        if check_file "given" "$REPLY"
        then
                fileext=${REPLY##*.}
                if [ $fileext == 'java' ]
                then
                        log "Pretty printing Java code"
                        highlight -O ansi $REPLY
                        ok
                        log "Compiling..."
                        if javac $REPLY 2> comp > /dev/null
                        then
                                ok
                                java ${REPLY%.*}
                        else
                                fail
                                cat comp
                                rm comp
                        fi
                else
                        if [ $fileext == 'c' ]
                        then
                                log "Pretty printing C code"
                                highlight -O ansi $REPLY
                                ok
                                log "Compiling..."
                                if gcc $REPLY -o ${REPLY%.*} 2> comp > /dev/null
                                then
                                        ok
                                        chmod +x ${REPLY%.*}
                                        ./${REPLY%.*}
                                else
                                        fail
                                        cat comp
                                        rm comp
                                fi
                        else
                                fail "Bad extension"
                        fi
                fi
        else
                fail "That file was not found"
        fi
fi

