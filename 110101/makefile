PARAMS=-std=c++0x -lm
TARGET=prog
TEST=test

# targets with shortcuts
compile c: src/main.cpp
	g++ src/main.cpp -o $(TARGET) $(PARAMS)

test t: src/test_main.cpp lib/extract_functions.sh
	sh lib/extract_functions.sh 
	g++ src/test_main.cpp -o $(TEST) -I lib/ $(PARAMS)
	./test

run r: lib/run.sh
	sh lib/run.sh

clean n:
	rm -f $(TARGET) output/* $(TEST) src/functions.cpp

.PHONY=all
all a: clean compile test run
