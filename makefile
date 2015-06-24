CC = g++
SDir = ./src
HDir = ./include
BDir = ./build
AppName = App-DMEngine
Flags = -std=c++11
Includes = -include $(HDir)/__DMEngine__.h
Objects = \
	$(BDir)/__DMEngine__.o\
	$(BDir)/Main.o\
	$(BDir)/MasterEngine.o\

build: $(AppName)

$(AppName): $(Objects)
	$(CC) $(Objects) -o $(AppName) $(Flags) -lglfw -lGL -lGLEW

$(BDir)/__DMEngine__.o: $(SDir)/__DMEngine__.cpp
	$(CC) -c $< -o $@ $(Flags) #-include $(HDir)/__DMEngine__.h

$(BDir)/%.o: $(SDir)/%.cpp
	$(CC) -c $< -o $@ -I $(HDir) $(Flags) $(Includes)

clean:
	rm $(BDir)/*.o $(AppName) -f

rebuild: clean build