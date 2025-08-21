CC = g++
CFLAGS = -std=c++17 -Wall -pedantic -fsanitize=address
SRCF = ./src
TARGET = ./vlcekm15
OBJS = ./src/main.o ./src/JsonParser/JsonParser.o ./src/Building/Building.o ./src/Commands/Commands.o ./src/CommandHandler/CommandHandler.o ./src/Effect/Effect.o ./src/GlobalEvents/GlobalEvents.o ./src/GameState/GameState.o ./src/GameWorld/GameWorld.o ./src/EventHandler/EventHandler.o ./src/EffectHandler/EffectHandler.o ./src/AI/AI.o ./src/AI/DecisionTree.o ./src/AI/AIState.o ./src/AI/Settlement.o ./src/WinConditions/WinConditions.o ./src/Action/Action.o ./src/Combat/Combat.o
LIBS = ./libs/json.hpp

$(TARGET): $(OBJS)
	rm ./vlcekm15 2>/dev/null || true
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(SRCF)/main.o: $(SRCF)/main.cpp
	$(CC) $(CFLAGS) -c $(SRCF)/main.cpp -o $(SRCF)/main.o

$(SRCF)/JsonParser/JsonParser.o: $(SRCF)/JsonParser/JsonParser.cpp $(SRCF)/JsonParser/JsonParser.h
	$(CC) $(CFLAGS) -c $(SRCF)/JsonParser/JsonParser.cpp -o $(SRCF)/JsonParser/JsonParser.o

$(SRCF)/Building/Building.o: $(SRCF)/Building/Building.cpp $(SRCF)/Building/Building.h
	$(CC) $(CFLAGS) -c $(SRCF)/Building/Building.cpp -o $(SRCF)/Building/Building.o

$(SRCF)/Commands/Commands.o: $(SRCF)/Commands/Commands.cpp $(SRCF)/Commands/Commands.h
	$(CC) $(CFLAGS) -c $(SRCF)/Commands/Commands.cpp -o $(SRCF)/Commands/Commands.o

$(SRCF)/CommandHandler/CommandHandler.o: $(SRCF)/CommandHandler/CommandHandler.cpp $(SRCF)/CommandHandler/CommandHandler.h
	$(CC) $(CFLAGS) -c $(SRCF)/CommandHandler/CommandHandler.cpp -o $(SRCF)/CommandHandler/CommandHandler.o

$(SRCF)/Effect/Effect.o: $(SRCF)/Effect/Effect.cpp $(SRCF)/Effect/Effect.h
	$(CC) $(CFLAGS) -c $(SRCF)/Effect/Effect.cpp -o $(SRCF)/Effect/Effect.o

$(SRCF)/GlobalEvents/GlobalEvents.o: $(SRCF)/GlobalEvents/GlobalEvents.cpp $(SRCF)/GlobalEvents/GlobalEvents.h
	$(CC) $(CFLAGS) -c $(SRCF)/GlobalEvents/GlobalEvents.cpp -o $(SRCF)/GlobalEvents/GlobalEvents.o

$(SRCF)/EventHandler/EventHandler.o: $(SRCF)/EventHandler/EventHandler.cpp $(SRCF)/EventHandler/EventHandler.h
	$(CC) $(CFLAGS) -c $(SRCF)/EventHandler/EventHandler.cpp -o $(SRCF)/EventHandler/EventHandler.o

$(SRCF)/GameState/GameState.o: $(SRCF)/GameState/GameState.cpp $(SRCF)/GameState/GameState.h
	$(CC) $(CFLAGS) -c $(SRCF)/GameState/GameState.cpp -o $(SRCF)/GameState/GameState.o

$(SRCF)/GameWorld/GameWorld.o: $(SRCF)/GameWorld/GameWorld.cpp $(SRCF)/GameWorld/GameWorld.h
	$(CC) $(CFLAGS) -c $(SRCF)/GameWorld/GameWorld.cpp -o $(SRCF)/GameWorld/GameWorld.o

$(SRCF)/EffectHandler/EffectHandler.o: $(SRCF)/EffectHandler/EffectHandler.cpp $(SRCF)/EffectHandler/EffectHandler.h
	$(CC) $(CFLAGS) -c $(SRCF)/EffectHandler/EffectHandler.cpp -o $(SRCF)/EffectHandler/EffectHandler.o

$(SRCF)/AI/AI.o: $(SRCF)/AI/AI.cpp $(SRCF)/AI/AI.h
	$(CC) $(CFLAGS) -c $(SRCF)/AI/AI.cpp -o $(SRCF)/AI/AI.o

$(SRCF)/AI/DecisionTree.o: $(SRCF)/AI/DecisionTree.cpp $(SRCF)/AI/DecisionTree.h
	$(CC) $(CFLAGS) -c $(SRCF)/AI/DecisionTree.cpp -o $(SRCF)/AI/DecisionTree.o

$(SRCF)/AI/AIState.o: $(SRCF)/AI/AIState.cpp $(SRCF)/AI/AIState.h
	$(CC) $(CFLAGS) -c $(SRCF)/AI/AIState.cpp -o $(SRCF)/AI/AIState.o

$(SRCF)/AI/Settlement.o: $(SRCF)/AI/Settlement.cpp $(SRCF)/AI/Settlement.h
	$(CC) $(CFLAGS) -c $(SRCF)/AI/Settlement.cpp -o $(SRCF)/AI/Settlement.o

$(SRCF)/WinConditions/WinConditions.o: $(SRCF)/WinConditions/WinConditions.cpp $(SRCF)/WinConditions/WinConditions.h
	$(CC) $(CFLAGS) -c $(SRCF)/WinConditions/WinConditions.cpp -o $(SRCF)/WinConditions/WinConditions.o

$(SRCF)/Action/Action.o: $(SRCF)/Action/Action.cpp $(SRCF)/Action/Action.h
	$(CC) $(CFLAGS) -c $(SRCF)/Action/Action.cpp -o $(SRCF)/Action/Action.o

$(SRCF)/Combat/Combat.o: $(SRCF)/Combat/Combat.cpp $(SRCF)/Combat/Combat.h
	$(CC) $(CFLAGS) -c $(SRCF)/Combat/Combat.cpp -o $(SRCF)/Combat/Combat.o

all:
	make clean
	make

compile:
	make

run:
	./$(TARGET)

compile_run:
	make compile
	make run

doc:	./Doxyfile/dox_config ./src/* ./src/*/* 
	doxygen ./Doxyfile/dox_config

clean:
	touch ./$(TARGET)
	rm $(TARGET) 2>/dev/null || true
	rm $(OBJS) 2>/dev/null || true
	rm -rf ./vlcekm15/* 2>/dev/null || true


# Magicke volani, ktere rika, ze pravidlo clean neprodukuje soubor.
.PHONY: clean