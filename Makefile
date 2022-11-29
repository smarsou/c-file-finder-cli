MEGAMIMEShPATH = ./lib/MegaMimes/src/MegaMimes.h
MEGAMIMEScPATH = ./lib/MegaMimes/src/MegaMimes.c

make :
	gcc $(MEGAMIMEShPATH) $(MEGAMIMEScPATH) ./src/ftc.c ./src/headers/lsRec.h ./src/lsRec.c ./src/headers/find.h ./src/find.c ./src/filter_date.c ./src/filter_name.c ./src/filter_mime.c ./src/filter_size.c ./src/filter.c ./src/headers/filter_date.h ./src/headers/filter_name.h ./src/headers/filter_mime.h ./src/headers/filter_size.h ./src/headers/filter.h -o ftc
	chmod +x ftc

clean :
	rm -rf ./bin
