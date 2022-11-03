make : 
	gcc ./src/ftc.c -o ftc
	chmod +x ftc
	sudo mv ftc /usr/bin/

	

clean : 
	rm -rf ./bin