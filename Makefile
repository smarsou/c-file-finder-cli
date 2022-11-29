MEGAMIMEShPATH = ./lib/MegaMimes/src/MegaMimes.h
MEGAMIMEScPATH = ./lib/MegaMimes/src/MegaMimes.c

make : 
	gcc $(MEGAMIMEShPATH) $(MEGAMIMEScPATH) ./src/ftc.c ./src/lsRec.h ./src/lsRec.c ./src/find.h ./src/find.c -o ftc
	chmod +x ftc
	
clean : 
	rm -rf ./bin
