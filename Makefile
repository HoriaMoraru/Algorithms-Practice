CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

.PHONY: build clean

build: p1 p2 p3 p4 p5

run-p1:
	./p1
run-p2:
	./p2
run-p3:
	./p3
run-p4:
	./p4
run-p5:
	./p5

p1: feribot.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p2: nostory.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p3: sushi.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p4: semnale.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p5: badgpt.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

# Vom șterge executabilele.
clean:
	rm -f p1 p2 p3 p4 p5
