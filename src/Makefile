CXX = g++
CXXFLAGS = -ggdb -Wall -MMD -Wextra
# TODO: change objects
OBJECTS = main.o bishop.o board.o controller.o graphicsdisplay.o \
		  human.o king.o knight.o move.o pawn.o piece.o queen.o \
		  rook.o square.o textdisplay.o view.o window.o player.o \
		  ai.o lvl1.o lvl2.o lvl3.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = pp9k

${EXEC} : ${OBJECTS}
	${CXX} -ggdb ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY : clean
clean :
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}

rebuild : clean ${EXEC}
