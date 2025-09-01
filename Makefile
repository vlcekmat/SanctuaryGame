CC = g++
CXXFLAGS = -std=c++17 -Wall -pedantic -fsanitize=address
LDFLAGS =
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# --- Detect OS ---
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    CXXFLAGS += -I/usr/include
    LDFLAGS  += -L/usr/lib
endif

ifeq ($(UNAME_S),Darwin) # macOS
    CXXFLAGS += -I/opt/homebrew/include
    LDFLAGS  += -L/opt/homebrew/lib
endif

SRCF = ./src
TARGET = ./vlcekm15

OBJS = ./src/main.o \
       ./src/JsonParser/JsonParser.o \
       ./src/Building/Building.o \
       ./src/Commands/Commands.o \
       ./src/CommandHandler/CommandHandler.o \
       ./src/Effect/Effect.o \
       ./src/GlobalEvents/GlobalEvents.o \
       ./src/GameState/GameState.o \
       ./src/GameWorld/GameWorld.o \
       ./src/EventHandler/EventHandler.o \
       ./src/EffectHandler/EffectHandler.o \
       ./src/AI/AI.o \
       ./src/AI/DecisionTree.o \
       ./src/AI/AIState.o \
       ./src/AI/Settlement.o \
       ./src/WinConditions/WinConditions.o \
       ./src/Action/Action.o \
       ./src/Combat/Combat.o \
       ./src/UI/Drawable.o \
       ./src/UI/Clickable.o \
        ./src/UI/UIHandler.o

LIBS = ./libs/json.hpp

# --- Rules ---

$(TARGET): $(OBJS)
	rm -f $(TARGET) 2>/dev/null || true
	$(CC) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

./src/%.o: ./src/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

# --- Convenience rules ---

all: clean $(TARGET)

compile: $(TARGET)

run: $(TARGET)
	./$(TARGET)

compile_run: compile run

doc: ./Doxyfile/dox_config ./src/* ./src/*/*
	doxygen ./Doxyfile/dox_config

clean:
	rm -f $(TARGET) $(OBJS)
	rm -rf ./vlcekm15/* 2>/dev/null || true

.PHONY: clean all compile run compile_run doc

