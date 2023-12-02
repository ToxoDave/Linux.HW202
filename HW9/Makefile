build:
	g++ init.cpp -o initbuild
	g++ destroy.cpp -o destroybuild
	g++ set.cpp -o setbuild
	g++ check.cpp -o checkbuild
init: initbuild
	./initbuild
destroy: destroybuild
	./destroybuild
set: setbuild
	./setbuild
check: checkbuild
	./checkbuild $(arg)
clean:
	rm -f initbuild destroybuild setbuild checkbuild
