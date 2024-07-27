# Compiler and flags
CXX = g++
CXXFLAGS = -ggdb -Wall -MMD -Wextra -std=c++17 -I. -Igame -Ipieces -Iobservers -Iplayers

# Directories
SRC_DIRS = . game pieces observers players
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = main.cc \
       game/controller.cc game/move.cc game/board.cc game/scoreboard.cc game/square.cc game/subject.cc \
       pieces/king.cc pieces/knight.cc pieces/pawn.cc pieces/piece.cc pieces/queen.cc pieces/rook.cc pieces/bishop.cc \
       observers/graphicsobserver.cc observers/textobserver.cc observers/window.cc \
       players/human.cc

# Object files
OBJECTS = $(patsubst %.cc, $(OBJ_DIR)/%.o, $(SRCS))
# Dependency files
DEPENDS = $(OBJECTS:.o=.d)
# Executable
EXEC = chess

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) -lX11

# Compile source files to object files
$(OBJ_DIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependency files
-include $(DEPENDS)

# Clean target
.PHONY: clean
clean:
	rm -f $(DEPENDS) $(OBJECTS) $(EXEC)
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rebuild target
rebuild: clean all
