RUN=run.sh

DIR= bin logs deepthough

MAINS=srcs/map/tests srcs/vector/tests srcs/stack/tests

run:
	sh $(RUN)

clean:
	rm -rf $(DIR) $(MAINS)
