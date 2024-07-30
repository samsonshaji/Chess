CXX = g++
CXXFLAGS = -ggdb -Wall -MMD -Wextra -std=c++17 -I. -Igame -Ipieces -Iobservers -Iplayers

SRC_DIRS = . game pieces observers players
OBJ_DIR = obj
BIN_DIR = bin

SRCS = main.cc \
       game/controller.cc game/move.cc game/board.cc game/scoreboard.cc game/square.cc game/subject.cc \
       pieces/king.cc pieces/knight.cc pieces/pawn.cc pieces/piece.cc pieces/queen.cc pieces/rook.cc pieces/bishop.cc \
       observers/graphicsobserver.cc observers/textobserver.cc observers/window.cc \
       players/human.cc \
	   players/robotLevelOne.cc \
	   players/robotLevelTwo.cc \
	   players/robot.cc \
	   players/player.cc \

OBJECTS = $(patsubst %.cc, $(OBJ_DIR)/%.o, $(SRCS))
DEPENDS = $(OBJECTS:.o=.d)
EXEC = chess

all: $(EXEC)

$(EXEC): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) -lX11

$(OBJ_DIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPENDS)

.PHONY: clean
clean:
	rm -f $(DEPENDS) $(OBJECTS) $(EXEC)
	rm -rf $(OBJ_DIR) $(BIN_DIR)

rebuild: clean all
