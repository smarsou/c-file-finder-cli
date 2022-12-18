MEGAMIMEShPATH = ./libs/MegaMimes/src/MegaMimes.h
MEGAMIMEScPATH = ./libs/MegaMimes/src/MegaMimes.c

make :
	gcc -Wall -Wextra -pedantic -Wno-sign-compare -Wno-discarded-qualifiers $(MEGAMIMEShPATH) $(MEGAMIMEScPATH) ./src/ftc.c ./src/headers/lsRec.h ./src/lsRec.c ./src/headers/filter_ctc.h ./src/filter_ctc.c ./src/headers/find.h ./src/find.c ./src/filter_date.c ./src/filter_perm.c ./src/filter_name.c ./src/filter_mime.c ./src/filter_size.c ./src/filter.c ./src/headers/filter_date.h ./src/headers/filter_perm.h ./src/headers/filter_name.h ./src/headers/filter_mime.h ./src/headers/filter_size.h ./src/headers/filter.h -o ftc
	chmod +x ftc

clean :
	rm -rf ./bin