OPTIMIZE = -O0

CC = gcc
CFLAGS = $(OPTIMIZE) -g -Wextra -Wno-unused -pthread
DIST_SOURCES = adder.c Makefile sortedList.c SortedList.h addList.c answers.txt graphs.pdf
DISTDIR = lab4-ZacharyBordofskyChrisZhu

default: add

add: adder.c
	$(CC) $(CFLAGS) adder.c -o $@ -lrt
	
list: addList.c sortedList.c
	$(CC) $(CFLAGS) -w sortedList.c addList.c -o $@ -lrt
	
clean: 
	rm -f *.tmp *~ *.o *.tar.gz add list
	
tarball: $(DISTDIR).tar.gz

$(DISTDIR).tar.gz: $(DIST_SOURCES) 
		rm -fr $(DISTDIR)
		tar -czf $@.tmp --transform='s,^,$(DISTDIR)/,' $(DIST_SOURCES)
		mv $@.tmp $@