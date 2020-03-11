
SRC_DIR:=	components

OBJ_DIR:=	build

BIN:=	$(HOME)/esp/xtensa-esp32-elf/bin
CC:=	$(BIN)/xtensa-esp32-elf-g++
LD:=	$(BIN)/xtensa-esp32-elf-ld

# Get files path with extension : *.S, *.c and *.cpp
SRC:=	$(shell find $(SRC_DIR) -name '*.S' -o -name '*.c' -o -name '*.cpp')

build : builds
	cd builds; \
	$(CC) -I../components -I../components/include -c $(addprefix ../, $(SRC))

builds :
	@mkdir builds
