make : 
	gcc ./src/ftc.c -o ftc
	chmod +x ftc
	sudo mv ftc /usr/bin/

ls:
	gcc ./src/lsRec.c -o lsrec
	chmod +x lsrec

clean : 
	rm -rf ./bin