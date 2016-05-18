rpnJason: rpn.cpp fraction.hpp linkedlist.hpp stack.hpp
	g++ -o rpnJason rpn.cpp

tar: rpn.cpp fraction.hpp linkedlist.hpp stack.hpp makefile
	tar -cvf rpnJason.gz rpn.cpp fraction.hpp linkedlist.hpp stack.hpp makefile

clean:
	rm *.o