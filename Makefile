c = clang++
d = -Wall -Os -march=native

.PHONY: all clean install i

all: fcr install clean

fcr: src/*.cc src/include/*.cc src/include/*.h
	$(c) $^ $(d)
	mv a.out $@

clean:
	rm -f fcr
	rm -f src/include/*.pch

i: install

install: fcr
	install -Dm755 fcr /usr/local/bin/fcr
	install -Dm644 man/fcr.1 /usr/local/share/man/man1/fcr.1