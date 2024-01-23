CC = gcc
CCFLAGS = -Werror -Wall

NAM := rpi_neo-6mv2_reader
LIB := $(shell find ./lib/ -name '*.c') 
SRC := $(shell find ./src/ -name '*.c') 

all: cexec 

.PHONY: list
list:
	@LC_ALL=C $(MAKE) -pRrq -f $(firstword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/(^|\n)# Files(\n|$$)/,/(^|\n)# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | grep -E -v -e '^[^[:alnum:]]' -e '^$@$$'


debug: CCFLAGS += -g 
debug: cexec 

# debug and do not call the canary token 
cexec:
	@$(CC) $(CCFLAGS) -o $(NAM) $(SRC) $(LIB) $(LDFLAGS)

clean:
	@-rm $(NAM) ||:

