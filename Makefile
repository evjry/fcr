c = clang++
d = -Os -march=native -o fcr

fcr: src/*.cc
	$(c) $^ $(d)