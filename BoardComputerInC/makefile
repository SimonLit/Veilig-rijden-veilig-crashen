LIBS=libs/serversocket 
INCLUDE_PATH=libs/

cli_exec: libraries
	gcc cli/boardcomputer.c $(wildcard libraries/*) -I$(INCLUDE_PATH) -o cli_exec

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