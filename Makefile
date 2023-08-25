a.out: main.cc card_class.h 
	g++ -g -Og main.cc -lcurl -lncurses
	
clean:
	 rm -rf a.out core *.o 
