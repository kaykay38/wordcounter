build:
	mkdir -p bin
	cc src/wordcounter.c -o bin/wordcounter

clean:
	rm -rf bin
	rm -f /usr/local/bin/wordcounter

install:
	chmod 755 bin/wordcounter
	cp -f bin/wordcounter /usr/local/bin/
