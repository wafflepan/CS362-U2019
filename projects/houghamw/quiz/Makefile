CFLAGS= -Wall -fpic -coverage -lm -std=c99


testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS)

#tester: tester.c
#	gcc -o tester -g tester.c $(CLFAGS)

runtest: testme
	echo "-----BEGIN TEST-----" > testresults.out
	-./testme >> testresults.out
	echo "-----COVERAGE ANALYSIS-----" >> testresults.out
	gcov testme.c -f -b >> testresults.out
	echo "-----END TEST-----" >> testresults.out
	cat testresults.out

all: testme

clean:
	rm -f *.o tester.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe testme
