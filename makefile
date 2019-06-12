SRC_PATH = src/

CC			= g++
CFLAGS		= -Wall --std=c++17 -Wdeprecated -g -Wunused-variable -Wunused-function
LIBFLAGS	= -lglfw3 -lopengl32 -lgdi32
INCLUDE		= -IBuilds/Dependencies/include
LIBS		= -LBuilds/Dependencies/lib
OBJ			= Builds/obj/
EXE			= engine

RS_DIRS		= shaders

win:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) $(SRC_PATH)*.cpp $(SRC_PATH)*.c $(LIBFLAGS) -o Builds/$(EXE)

osx:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) $(SRC_PATH)*.cpp $(SRC_PATH)*.c $(LIBFLAGS) -o Builds/$(EXE) -framework OpenGl

run_win:
	./Builds/$(EXE).exe

run_osx:
	./Builds/$(EXE)
	
cp_resources:
	cp -r -f $(RS_DIRS) ./Builds/ 