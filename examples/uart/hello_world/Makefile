######################################################################
 #
 #				File Name: Makefile
 #
 #####################################################################
 #
 # Project Name		: MDP - Microprocessor Development Project
 #
 # Project Code		: HD083D
 #
 # Created			: 07-Nov-2019
 #
 # Purpose			: MDP Bootloader
 #
 # Description		: First satge bootloader for MDP project
 #
 # Author(s)		: Premjith A V
 #
 # Version No		: 1.0.0
 #
 # Revisions		:
 #
 # Remarks			: For Single core and Dual core ASIC
 #
 # Copyright		: 2019, C-DAC, Trivandrum
 ######################################################################
 
#-----------------------------------------
#           	Flags	                 #
#-----------------------------------------
TOOLCHAIN_PATH=${MDP_TOOLCHAIN64_PATH}
SDK_PATH=${MDP_SDK}
CC=$(TOOLCHAIN_PATH)/riscv64-unknown-elf-gcc 
CFLAGS=-c -mcmodel=medany -march=rv64imafd -fno-builtin-printf 
LIB=
LDFLAGS= -mcmodel=medany -nostartfiles -nostdlib -std=gnu99 

EXECUTABLE_NAME=hello
INC=-I$(SDK_PATH)/bsp/include

# Folders
BIN=build

#-----------------------------------------
# 				Rules 		      		 #
#-----------------------------------------
LINK_OPTS ?=  -T $(SDK_PATH)/bsp/common/mbl.lds
EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(BIN)/%)

OBJECT_FILES_C   = $(patsubst %.c, $(BIN)/%.o,  $(wildcard *.c))
OBJECT_FILES_S   = $(patsubst %.S, $(BIN)/%.o,  $(wildcard *.S))

BSP_FILES = $(shell find $(SDK_PATH)/bsp -type f -name '*.c')
BSP_FILES += $(shell find $(SDK_PATH)/bsp -type f -name '*.S')

COPY_FILES := $(patsubst $(SDK_PATH)/bsp/%,$(BIN)/%,$(BSP_FILES))

all:   $(EXECUTABLE_FILES) 

clean:
	rm -r -f $(BIN)	
mrproper:
	rm -r -f $(BIN)	
.PHONY: build clean



$(EXECUTABLE_FILES): $(COPY_FILES) $(OBJECT_FILES_C) $(OBJECT_FILES_S) 
	@$(CC) $(LDFLAGS) -o $@ $^ $(LIB) $(INC) $(LINK_OPTS)	
	@echo "Build successful!"
	@$(TOOLCHAIN_PATH)/riscv64-unknown-elf-objdump -d $(BIN)/$(EXECUTABLE_NAME) > $(BIN)/$(EXECUTABLE_NAME).dump



$(OBJECT_FILES_C): $(BIN)/%.o: %.c
	@echo Compiling $<
	@mkdir -p $(@D)	
	@$(CC) $(CFLAGS) $(INC) -o $@ $<

$(OBJECT_FILES_S): $(BIN)/%.o: %.S
	@echo Compiling $<	
	@mkdir -p $(@D)	
	@$(CC) $(CFLAGS) $(INC) -o $@ $<	

	
$(COPY_FILES): $(BIN)/%: $(SDK_PATH)/bsp/%
	@mkdir -p $(@D)
	@cp -rf $< $@ 

