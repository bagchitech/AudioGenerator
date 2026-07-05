audiogen: src/main.c src/audiogenerator.c include/audiogenerator.h
	gcc src/main.c src/audiogenerator.c -o audiogen -I include -lm