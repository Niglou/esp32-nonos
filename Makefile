
SRC_DIR:=	components

OBJ_DIR:=	builds

LD_DIR:= ld

# Path of binaries, change if necessary
XTENSA:=	$(HOME)/esp/xtensa-esp32-elf
CC:=	$(XTENSA)/bin/xtensa-esp32-elf-g++
LD:=	$(XTENSA)/bin/xtensa-esp32-elf-ld

DIR_SRC:= $(shell find $(SRC_DIR) -type d -not -path './.*')
SRC:=	$(shell find $(SRC_DIR) -name '*.S' -o -name '*.c' -o -name '*.cpp')
OBJ:= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(shell basename -a $(SRC))))

LD_FILES= $(wildcard $(LD_DIR:=/*.ld))

CFLAG:= $(addprefix -I, $(DIR_SRC))
LDFLAGS:= $(addprefix -T, $(LD_FILES)) -L$(XTENSA)/xtensa-esp32-elf/lib -L$(XTENSA)/lib/gcc/xtensa-esp32-elf/8.2.0

COMMAND:= $(word 2, $(MAKECMDGOALS))
empty:=


ifeq ($(COMMAND),$(empty))

VPATH:= $(DIR_SRC)

build : builds esp32_nonos

else
P_NAME:= $(shell basename -a $(COMMAND))
P_DIR_SRC:= $(shell find $(COMMAND) -type d -not -path $(COMMAND)'/.*')
P_SRC:=	$(shell find $(COMMAND) -name '*.S' -o -name '*.c' -o -name '*.cpp')
P_OBJ_DIR:= $(COMMAND)/$(OBJ_DIR)
P_OBJ:= $(addprefix $(P_OBJ_DIR)/, $(addsuffix .o, $(shell basename -a $(P_SRC))))
P_CFLAG:= $(CFLAG) $(addprefix -I, $(P_DIR_SRC))
VPATH:= $(P_DIR_SRC) $(DIR_SRC)

build : $(OBJ_DIR) esp32_nonos $(COMMAND)/$(OBJ_DIR) project

$(eval $(COMMAND):;@:)

endif

# Build esp32-nonos
esp32_nonos : $(OBJ)
	@echo
	@echo 'esp32-nonos compiled !'
	@echo

# Build project
ifneq ($(COMMAND),$(empty))

project : $(P_OBJ)
	@$(LD) $(LDFLAGS) $(OBJ) $(P_OBJ) -o $(COMMAND)/$(P_NAME).elf -lm -lgcc
	@echo
	@echo $(P_NAME) 'compiled !'
	@echo

$(P_OBJ_DIR) :
	@mkdir $(P_OBJ_DIR)
	@echo $(P_NAME)' "$(OBJ_DIR)" folder created !'

# Rules for each type of sources
$(P_OBJ_DIR)/%.c.o : %.c
	@$(CC) $(P_CFLAG) -o $@ -c $<
	@echo $< '-->' $@

$(P_OBJ_DIR)/%.cpp.o : %.cpp
	@$(CC) $(P_CFLAG) -o $@ -c $<
	@echo $< '-->' $@

$(P_OBJ_DIR)/%.S.o : %.S
	@$(CC) $(P_CFLAG) -o $@ -c $<
	@echo $< '-->' $@

endif


$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)
	@echo 'esp32-nonos "$(OBJ_DIR)" folder created !'

# Rules for each type of sources
%.c.o : %.c
	@$(CC) $(CFLAG) -o $@ -c $<
	@echo $< '-->' $@

%.cpp.o : %.cpp
	@$(CC) $(CFLAG) -o $@ -c $<
	@echo $< '-->' $@

%.S.o : %.S
	@$(CC) $(CFLAG) -o $@ -c $<
	@echo $< '-->' $@
