CC=gcc
SRC_FILES=\
	./DIYWolf3D/SDL_Draw/*.c \
	./DIYWolf3D/*.cpp \
	../external/imgui/*.cpp
	 
INCLUDE_DIR=\
	-I/usr/include/SDL2 \
	-I./DIYWolf3D/SDL_Draw \
	-I../external/imgui

LINKER_FLAGS=\
	-ggdb \
	-lstdc++\
	-lm \
	-lSDL2main \
	-lSDL2 \
	-lSDL2_image

OUTPUT_FLAG=-o
EXE_DIR=../external/workdir/bin/
EXE_FILE=DIYWolf3D

build:
	mkdir -p $(EXE_DIR) 
	$(CC) -w $(SRC_FILES) $(LINKER_FLAGS) $(INCLUDE_DIR) $(OUTPUT_FLAG) $(EXE_DIR)$(EXE_FILE) 

clean:
	rm -f $(EXE_DIR)$(EXE_FILE)
