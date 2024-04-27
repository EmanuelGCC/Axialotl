# Add -O3 for better optimization and making
# your code not suck as much

Debug := -DAXIA_DEBUG

Libs  := -g -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi \
		 -ldl -Wall -lm -lfreetype $(Debug)
Libsc := $(Libs) -c
Objs  := bin/math.o bin/window.o bin/input.o bin/render.o bin/shaders.o bin/drawables.o

main: bin/axia.o
	@gcc bin/axia.o src/main.c -o axialotl $(Libs) 
	@./axialotl

bin/axia.o: $(Objs) src/axialotl/axia.c src/axialotl/axia.h
	@gcc src/axialotl/axia.c $(Libsc) -o bin/deps.o
	@ld -r $(Objs) bin/deps.o -o bin/axia.o

bin/render.o: src/render/render.c src/render/render.h
	@gcc src/render/render.c $(Libsc) -o bin/render.o

bin/shaders.o: src/render/shaders/shaders.c src/render/shaders/shaders.h
	@gcc src/render/shaders/shaders.c $(Libsc) -o bin/shaders.o

bin/drawables.o: src/drawables/drawables.c src/drawables/texture.h src/drawables/geometry.h
	@gcc src/drawables/drawables.c $(Libsc) -o bin/drawables.o

test_window: $(win) tests/src/window/main.o
	@gcc tests/src/window/main.c $(win) bin/math.o -o 
	@./tests/bin/window

bin/window.o: src/window/window.c src/window/window.h
	@gcc src/window/window.c -o bin/window.o $(Libsc)

bin/input.o: src/window/input/input.c src/window/input/input.h
	@gcc src/window/input/input.c -o bin/input.o $(Libsc)

test_math: bin/math.o tests/src/math/main.c
	@gcc tests/src/math/main.c bin/math.o -o tests/bin/math $(Libs) 
	@./tests/bin/math

bin/math.o: src/math/math.c src/math/matrix.h src/math/vector.h
	@gcc src/math/math.c -o bin/math.o $(Libsc)
	
clear:
	@rm bin/*
