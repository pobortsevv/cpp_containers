NAME = differ

VECTOR_DIRECTORY = testing/vector
MAP_DIRECTORY = testing/map
STACK_DIRECTORY = testing/stack

SCRIPT = test.sh
LEAKS = leaks.sh

VECTOR_LOGS = testing/vector/logs/*
MAP_LOGS = testing/map/logs/*
STACK_LOGS = testing/stack/logs/*

LOG_DIRS = testing/*/logs

RM = rm -rf
SH = /bin/zsh

all:
	$(MAKE) $(NAME) -j4

$(NAME):
	$(SH) $(VECTOR_SCRIPT) $(MAP_SCRIPT) $(STACK_SCRIPT)

vector:
	cd $(VECTOR_DIRECTORY) && $(SH) $(SCRIPT)

vector_leaks:
	cd $(VECTOR_DIRECTORY) && $(SH) $(LEAKS)

map:
	cd $(MAP_DIRECTORY) && $(SH) $(SCRIPT)

map_leaks:
	cd $(MAP_DIRECTORY) && $(SH) $(LEAKS)

stack:
	cd $(STACK_DIRECTORY) && $(SH) $(SCRIPT)

stack_leaks:
	cd $(STACK_DIRECTORY) && $(SH) $(LEAKS)

clean:
	@$(RM) $(VECTOR_LOGS) $(MAP_LOGS) $(STACK_LOGS) $(LOG_DIRS)
	@echo clean logs

re:	clean $(NAME)
