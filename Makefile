
include Header.mk


CC:=	$(XTENSA)/bin/xtensa-esp32-elf-gcc

DIR_SRC:= $(shell find -type d -not -path './.*')
SRC:=	$(shell find $(SRC_DIR) -name '*.S' -o -name '*.c' -o -name '*.cpp')
OBJ:= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(shell basename -a $(SRC))))

CFLAG:= $(addprefix -I, $(DIR_SRC))

VPATH:= $(DIR_SRC)

build : builds esp32_nonos

# Build esp32-nonos
esp32_nonos : $(OBJ)
	@echo
	@echo 'ESP32-NONOS compiled !'
	@echo

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)
	@echo
	@echo 'esp32-nonos "$(OBJ_DIR)" folder created !'
	@echo

# Rules for each type of sources
$(OBJ_DIR)/%.c.o : %.c
	@$(CC) $(CFLAG) -o $@ -c $<
	@echo $< '-->' $@

$(OBJ_DIR)/%.cpp.o : %.cpp
	@$(CC) $(CFLAG) -o $@ -c $<
	@echo $< '-->' $@

$(OBJ_DIR)/%.S.o : %.S
	@$(CC) $(CFLAG) -o $@ -c $<
	@echo $< '-->' $@
