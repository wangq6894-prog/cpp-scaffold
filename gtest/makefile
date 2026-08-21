ALL:simple global local
simple:simple.cc
	g++ -o simple simple.cc -lgtest
global:global.cc
	g++ -o global global.cc -lgtest
local:local.cc
	g++ -o local local.cc -lgtest
.PHONY:clean
clean:
	rm -f simple global 
	
