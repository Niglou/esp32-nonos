
SRC_DIR:=	components

OBJ_DIR:=	builds

LD_DIR:= ld

# Path of binaries, change if necessary
BIN:=	$(HOME)/esp/xtensa-esp32-elf/bin
CC:=	$(BIN)/xtensa-esp32-elf-g++
LD:=	$(BIN)/xtensa-esp32-elf-ld

DIR_SRC:= $(shell find $(SRC_DIR) -type d)
SRC:=	$(shell find $(SRC_DIR) -name '*.S' -o -name '*.c' -o -name '*.cpp')
OBJ:= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(shell basename -a $(SRC))))

LD_FILES= $(wildcard $(LD_DIR:=/*.ld))

CFLAG:= $(addprefix -I, $(DIR_SRC))
LDFLAGS:= $(addprefix -T, $(LD_FILES))

VPATH:= $(DIR_SRC)

COMMAND:= $(word 2, $(MAKECMDGOALS))

empty:=

ifeq ($(COMMAND),$(empty))
build : builds esp32_nonos

else
NAME:= $(shell basename -a $(COMMAND))
build : builds esp32_nonos $(COMMAND)/builds project
$(eval $(COMMAND):;@:)

endif

# Build esp32-nonos
esp32_nonos : $(OBJ)
	@echo 'esp32-nonos compiled !'

# Build project
ifneq ($(COMMAND),$(empty))

	$(eval DIR_SRC:= $(shell find $(COMMAND) -type d))
	$(eval SRC:=	$(shell find $(COMMAND) -name '*.S' -o -name '*.c' -o -name '*.cpp'))
	$(eval OBJ_DIR:= $(COMMAND)/$(OBJ_DIR))
	$(eval project:= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(shell basename -a $(SRC)))))
	$(eval CFLAG:= $(CFLAG) $(addprefix -I, $(DIR_SRC)))
	$(eval VPATH:= $(DIR_SRC))

project : $(project)
	@$(LD) $(LDFLAGS) $(OBJ) $(project) -o $(COMMAND)/$(NAME).elf
	@echo $(NAME) 'compiled !'

endif


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

$(COMMAND)/builds :
	@mkdir $(COMMAND)/$(OBJ_DIR)
	@echo $(NAME)' "$(OBJ_DIR)" folder created !'

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)
	@echo 'esp32-nonos "$(OBJ_DIR)" folder created !'
