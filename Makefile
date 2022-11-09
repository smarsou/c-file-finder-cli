make : 
	gcc ./src/ftc.c ./src/lsRec.h ./src/lsRec.c -o ftc
	chmod +x ftc
	
clean : 
	rm -rf ./bin
