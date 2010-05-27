

LB = C:\MinGW\lib\libwinmm.a C:\MinGW\lib\libgdi32.a C:\MinGW\lib\libm.a


OBJECT = hookbot.o window.o message.o analyser.o
HEADER = src\def.h src\window.h src\message.h src\analyser.h


target: hookbot.exe dice.dll sign.dll clean

hookbot.exe: $(OBJECT)
	g++ temp\hookbot.o temp\window.o temp\message.o temp\analyser.o $(LB) -o release\hookbot.exe

hookbot.o: src\hookbot.cpp $(HEADER)
	g++ -O3 -c src\$*.cpp -o temp\$*.o
window.o: src\window.cpp $(HEADER)
	g++ -O3 -c src\$*.cpp -o temp\$*.o
message.o: src\message.cpp $(HEADER)
	g++ -O3 -c src\$*.cpp -o temp\$*.o
analyser.o: src\analyser.cpp  $(HEADER)
	g++ -O3 -c src\$*.cpp -o temp\$*.o


dice.dll: dice.o eval_r.o parse.o
	g++ temp\dice.o temp\eval_r.o temp\parse.o -Wall -shared -o release\plugin\dice.dll
dice.o: plugin\dice\dice.cpp
	g++ -O3 -c plugin\dice\$*.cpp -o temp\$*.o
eval_r.o: plugin\dice\eval_r.cpp plugin\dice\eval_r.h
	g++ -O3 -c plugin\dice\$*.cpp -o temp\$*.o
parse.o: plugin\dice\parse.cpp plugin\dice\parse.h
	g++ -O3 -c plugin\dice\$*.cpp -o temp\$*.o


sign.dll: sign.o 
	g++ temp\sign.o -Wall -shared -o release\plugin\sign.dll
sign.o: plugin\sign\sign.cpp
	g++ -O3 -c plugin\sign\$*.cpp -o temp\$*.o



clean:
	del temp\*.o /Q



