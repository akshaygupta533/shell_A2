main: \
			main.o \
			commandtokenize.o \
			changedir.o \
			getreldir.o \
			semicolonsep.o \
			echofunc.o	\
			ls.o \
			print_details.o \
			pinfo.o	\
			historyfunc.o \
			exec.o \
			exitprocess.o \
			jobs.o \
			kjob.o \
			generateoj.o \
			overkill.o
	$(CC) -g -o main $^

clean:
	@rm -f *.o main

commandtokenize.o: header.h commandtokenize.c
	$(CC) -g -c commandtokenize.c

changedir.o: header.h changedir.c
	$(CC) -g -c changedir.c

getreldir.o: header.h getreldir.c
	$(CC) -g -c getreldir.c

semicolonsep.o: header.h semicolonsep.c
	$(CC) -g -c semicolonsep.c
	
echofunc.o: header.h echofunc.c
	$(CC) -g -c echofunc.c

ls.o: header.h ls.c
	$(CC) -g -c ls.c

print_details.o: header.h print_details.c
	$(CC) -g -c print_details.c

pinfo.o: header.h pinfo.c
	$(CC) -g -c pinfo.c

historyfunc.o: header.h historyfunc.c
	$(CC) -g -c historyfunc.c

exec.o: header.h exec.c
	$(CC) -g -c exec.c

jobs.o: header.h jobs.c
	$(CC) -g -c jobs.c

kjob.o: header.h kjob.c
	$(CC) -g -c kjob.c

generateoj.o: header.h generateoj.c
	$(CC) -g -c generateoj.c

overkill.o: header.h overkill.c
	$(CC) -g -c overkill.c

exitprocess.o: header.h exitprocess.c
	$(CC) -g -c exitprocess.c

main.o: header.h main.c
	$(CC) -g -c main.c