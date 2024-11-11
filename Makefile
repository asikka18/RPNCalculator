###
### Makefile for CalcYouLater Project
###
### Author:  Armaan Sikka (asikka01)

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

CalcYouLater: main.o parser.o RPNCalc.o DatumStack.o Datum.o
	${CXX} ${CXXFLAGS} -o CalcYouLater main.o parser.o RPNCalc.o DatumStack.o Datum.o

main.o: parser.h parser.cpp main.cpp RPNCalc.h Datum.h DatumStack.h
	${CXX} ${CXXFLAGS} main.cpp -c

RPNCalc.o: Datum.h DatumStack.h parser.h RPNCalc.h RPNCalc.cpp 
	${CXX} ${CXXFLAGS} RPNCalc.cpp -c

DatumStack.o: DatumStack.h DatumStack.cpp Datum.h
	$(CXX) $(CXXFLAGS) DatumStack.cpp -c

parser.o: parser.cpp parser.h
	$(CXX) $(CXXFLAGS) parser.cpp -c

unit_test: unit_test_driver.o DatumStack.o Datum.o RPNCalc.o Parser.o
	$(CXX) $(CXXFLAGS) unit_test_driver.o DatumStack.o Datum.o RPNCalc.o Parser.o


## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

##
## Here is a special rule that removes all .o files besides the provided one
## (Datum.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
	-name '*.o' ! -name 'Datum.o' \
	\) -exec rm -f {} \;
	@rm -f *~ a.out

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
