CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EIGENFLAGS = -I eigen/ 
EXEC = main
OBJECTS = main.o sqrt.o fraction.o complex.o
DEPENDS = ${OBJECTS:.o=.d}

matrix.o: 
	${CXX} ${CXXFLAGS} ${EIGENFLAGS} -c matrix.cc

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} matrix.o -o ${EXEC}


-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
