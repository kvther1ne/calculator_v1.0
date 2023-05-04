CFLAGS = -Wall -Werror -Wextra -pedantic -std=c11
SOURCES = calc.c secondary.c
OBJECTS = $(SOURCES:.c=.o)
SOURCE_TEST = tests.c
LIB = calc.a

UNAME =  $(shell uname -s)
FLAGS = 
ifeq ($(UNAME), Linux)
	FLAGS += -lcheck_pic -lm -lsubunit -lrt -lpthread
else
	FLAGS += -lcheck -lm
endif

all: install

install: $(LIB)
	cmake ../qt/SmartCalc/ -B app
	cd app && make
	cd app/SmartCalc.app/Contents/MacOS && ./SmartCalc

uninstall:
	rm -rf app

dvi: 
	doxygen doxygen_file
	open ./Docs/html/index.html

dist: clean uninstall
	tar -cvzf calc.tgz .

test: $(LIB) $(SOURCE_TEST)
	gcc $(SOURCE_TEST) $(CFLAGS) ../qt/SmartCalc/libcalc.a -o testcalc $(FLAGS)
	./testcalc

calc.a: $(OBJECTS)
	ar rc $(LIB) $(OBJECTS)
	ranlib $(LIB)
	mv $(LIB) ../qt/SmartCalc/libcalc.a
	rm -rf *.o

calc.o: calc.c
	gcc $(CFLAGS) calc.c -c -o calc.o

secondary.o: secondary.c
	gcc $(CFLAGS) secondary.c -c -o secondary.o

valgrind: clean $(LIB)
	gcc $(SOURCE_TEST) $(CFLAGS) ../qt/SmartCalc/libcalc.a -o testvalg $(FLAGS)
	valgrind --leak-check=full --track-origins=yes --track-fds=yes ./testvalg
	# grep ERROR valgrind.log

gcov_report: $(LIB)
	gcc $(CFLAGS) $(SOURSE_TEST) -o testlcov --coverage $(SOURSES) $(FLAGS)
	./test
	lcov -t "a.out" -o test.info -c -d .
	genhtml -o report test.info
	open ../report/index.html
	rm -rf test *.o *.a *gcda *gcno *info

clean:
	rm -rf *.o ../qt/SmartCalc/*.a a.out *.dSYM testcalc testlcov testvalg *gcda report *gcno *info *.log Docs \
	build-qt-Desktop_x86_darwin_generic_mach_o_64bit-Debug *.tgz