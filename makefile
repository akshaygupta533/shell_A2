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
			overkill.o \
			setenv.o \
			unsetenv.o \
			fg.o \
			bg.o \
			ctrl_c.o \
			handle.o \
			redirect.o \
			redirect2.o \
			checkPiping.o \
			checkRedirect.o \
			handlepipesandredirection.o \
			handlepipes.o
	$(CC) -g -o main $^

clean:
	@rm -f *.o main

commandtokenize.o: header.h commandtokenize.c
	$(CC) -g -c commandtokenize.c

changedir.o: header.h changedir.c
	$(CC) -g -c changedir.c

ctrl_c.o: header.h ctrl_c.c
	$(CC) -g -c ctrl_c.c

handle.o: header.h handle.c
	$(CC) -g -c handle.c

getreldir.o: header.h getreldir.c
	$(CC) -g -c getreldir.c

semicolonsep.o: header.h semicolonsep.c
	$(CC) -g -c semicolonsep.c
	
echofunc.o: header.h echofunc.c
	$(CC) -g -c echofunc.c

ls.o: header.h ls.c
	$(CC) -g -c ls.c

fg.o: header.h fg.c
	$(CC) -g -c fg.c

bg.o: header.h bg.c
	$(CC) -g -c bg.c

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

setenv.o: header.h setenv.c
	$(CC) -g -c setenv.c

unsetenv.o: header.h unsetenv.c
	$(CC) -g -c unsetenv.c

redirect.o: header.h redirect.c
	$(CC) -g -c redirect.c

checkRedirect.o: header.h checkRedirect.c
	$(CC) -g -c checkRedirect.c

checkPiping.o: header.h checkPiping.c
	$(CC) -g -c checkPiping.c

redirect2.o: header.h redirect2.c
	$(CC) -g -c redirect2.c

handlepipesandredirection.o: header.h handlepipesandredirection.c
	$(CC) -g -c handlepipesandredirection.c

handlepipes.o: header.h handlepipes.c
	$(CC) -g -c handlepipes.c


main.o: header.h main.c
	$(CC) -g -c main.c