SDir = ./src
HDir = ./include
BDir = ./Build
AppName = DMEngine
Flags = -std=c++11
Lib=\
	-lglfw\
	-lGL\
	-lGLEW
Objects = \
	$(BDir)/Main.o\
	$(BDir)/MasterEngine.o

build: App-$(AppName)

App-$(AppName): $(BDir)/__DMEngine__.o $(Objects)
	$(CXX) $(BDir)/__DMEngine__.o $(Objects) -o App-$(AppName) $(Flags) $(Lib)

$(BDir)/__DMEngine__.o: $(SDir)/__DMEngine__.cpp
	$(CXX) -c $< -o $@ $(Flags)

$(BDir)/%.o: $(SDir)/%.cpp
	$(CXX) -c $< -o $@ $(Flags) -I$(HDir) -include$(HDir)/__DMEngine__.h

clean:
	rm $(BDir)/* *.log App-$(AppName) -f

rebuild: clean build