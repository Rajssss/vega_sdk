#-------------------------------------------------------------------- 
#Project Name		: MDP - Microprocessor Development Project
#Project Code		: HD083D
#Created		: 07-Jan-2020
#Filename		: Makefile
#Purpose		: Sample hello world program
#Description		: Sample hello program with uart print
#Author(s)		: Premjith A V
#Email			: premjith@cdac.in
#--------------------------------------------------------------------    
#See LICENSE for license details.
 
#-----------------------------------------
#           	Configurations            #
#-----------------------------------------
CONFIG_PATH=~/.config/mdp-tools/settings.mk
ifeq ("$(wildcard $(CONFIG_PATH))","")
$(error Please install [MDP SDK]/[MDP Tools] and setup the environment)
endif

include $(CONFIG_PATH)

ifeq ("$(wildcard $(MDP_TOOLCHAIN64_PATH))","")
$(error Please install [MDP Tools] and setup the environment)
endif

ifeq ("$(wildcard $(MDP_SDK))","")
$(error Please install [MDP SDK] and setup the environment)
endif
SDK_PATH=${MDP_SDK}
#-----------------------------------------
#           	Executable name           #
#-----------------------------------------
EXECUTABLE_NAME=uart_tx_rx

include $(SDK_PATH)/bsp/common/config.mk

