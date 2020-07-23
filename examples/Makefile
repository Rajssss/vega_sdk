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

EXAMPLES=$(shell find . -mindepth 2 -name 'Makefile'|xargs dirname)

.PHONY: default
default: all 

.PHONY: clean
clean: $(EXAMPLES)
	for file in $^ ; do \
	$(MAKE) -C $${file} clean ; \
        done
        
.PHONY: all
all: $(EXAMPLES)
	for file in $^ ; do \
	$(MAKE) -C $${file} ; \
        done
