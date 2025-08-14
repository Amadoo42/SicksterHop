test:
	g++ -Ofast -fomit-frame-pointer main.cpp nnue.cpp misc.cpp -o main -DUSE_SSE41 -msse4.1 -DUSE_SSSE3 -mssse3 -DUSE_SSE2 -msse2 -DUSE_SSE -msse

debug:
	g++ -Ofast main.cpp nnue.cpp misc.cpp -o main
	.\main