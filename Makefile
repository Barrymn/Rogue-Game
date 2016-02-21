CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = cc3k
OBJECTS = main.o floor.o 3p.o 7e.o cell.o chamber.o character.o dtreasure.o enemy.o item.o ntreasure.o object.o pc.o potion.o stair.o textdisplay.o treasure.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

.PHONY: clean
