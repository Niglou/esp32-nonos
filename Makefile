
SRC_DIR:=	components

OBJ_DIR:=	builds

# Path of binaries, change if necessary
BIN:=	$(HOME)/esp/xtensa-esp32-elf/bin
CC:=	$(BIN)/xtensa-esp32-elf-g++
LD:=	$(BIN)/xtensa-esp32-elf-ld

DIR_SRC:= $(shell find $(SRC_DIR) -type d)
SRC:=	$(shell find $(SRC_DIR) -name '*.S' -o -name '*.c' -o -name '*.cpp')
OBJ:= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(shell basename -a $(SRC))))

CFLAG:= $(addprefix -I, $(DIR_SRC))

VPATH:= $(DIR_SRC)

# Build esp32-nonos
build : builds $(OBJ)
	@echo 'esp32-nonos compiled !'

# Build project


# Rules for each type of sources
$(OBJ_DIR)/%.c.o : %.c
	@$(CC) $(CFLAG) -o $@ -c $<

$(OBJ_DIR)/%.cpp.o : %.cpp
	@$(CC) $(CFLAG) -o $@ -c $<

$(OBJ_DIR)/%.S.o : %.S
	@$(CC) $(CFLAG) -o $@ -c $<


builds :
	@mkdir builds
	@echo '"builds" folder created !'
