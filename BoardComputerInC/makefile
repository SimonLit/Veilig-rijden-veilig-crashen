LIBS=libs/serversocket libs/file_handeling libs/response libs/handshake libs/serial
INCLUDE_PATH=libs/

boardcomputer_exec: libraries
	gcc cli/boardcomputer.c $(wildcard libraries/*) -I$(INCLUDE_PATH) -o boardcomputer

libraries:
	mkdir libraries/
	for dir in $(LIBS); do \
		cd $$dir; \
		gcc -c *.c -I../; \
		mv *.o ../../libraries; \
		cd -; \
	done

clean:
	rm -rf libraries/

remove:
	rm boardcomputer