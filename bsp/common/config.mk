UTIL_PATH=${MDP_TOOLS}/utils
TOOLCHAIN_PATH=${MDP_TOOLCHAIN64_PATH}
CC=$(TOOLCHAIN_PATH)/riscv64-unknown-elf-gcc 
CFLAGS=-c -mcmodel=medany -march=rv64imafd -fno-builtin-printf -fdata-sections -ffunction-sections -fno-builtin-memcmp
LIB=
LDFLAGS= -mcmodel=medany -nostartfiles -nostdlib -std=gnu99 -Wl,--gc-sections


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
	@$(TOOLCHAIN_PATH)/riscv64-unknown-elf-objcopy -I elf64-littleriscv -O binary  $(BIN)/$(EXECUTABLE_NAME) $(BIN)/$(EXECUTABLE_NAME).bin
	@$(UTIL_PATH)/bin2hex --bit-width 128 $(BIN)/$(EXECUTABLE_NAME).bin $(BIN)/$(EXECUTABLE_NAME).hex
	@echo -n "ELF\t: $(EXECUTABLE_NAME)\nBinary\t: $(EXECUTABLE_NAME).bin\n"
	@echo -n "Hex\t: $(EXECUTABLE_NAME).hex\nDump\t: $(EXECUTABLE_NAME).dump\nFiles are generated in $(BIN) folder.\n"
	@echo -n "Size information\n"
	@$(TOOLCHAIN_PATH)/riscv64-unknown-elf-size $(BIN)/$(EXECUTABLE_NAME)


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
	
