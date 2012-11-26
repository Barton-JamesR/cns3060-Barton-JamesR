all:  buildonly

parta: parta.c
	gcc -o parta parta.c -lpthread
	./parta

partb: partb.c
	gcc -o partb partb.c -lpthread
	./partb

partc: partc.c
	gcc -o partc partc.c -lpthread
	./partc

partd: partd.c
	gcc -o partd partd.c -lpthread
	./partd

buildonly:  parta.c partb.c partc.c partd.c
	gcc -o parta parta.c -lpthread
	gcc -o partb partb.c -lpthread
	gcc -o partc partc.c -lpthread
	gcc -o partd partd.c -lpthread

clean:
	rm parta
	rm partb
	rm partc
	rm partd
