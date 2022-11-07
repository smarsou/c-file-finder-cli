make : 
	gcc ./src/ftc.c ./src/lsRec.h ./src/lsRec.c -o ftc
	chmod +x ftc
	sudo mv ftc /usr/bin/
	
clean : 
	rm -rf ./bin
