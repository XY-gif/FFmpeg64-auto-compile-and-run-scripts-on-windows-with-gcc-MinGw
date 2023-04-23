CC = gcc
IncludeDirFlag = -I"D:\Program Files\ffmpeg-shared\include"
LinkDirFlag = -L"D:\Program Files\ffmpeg-shared\bin" 
LinkFlag = -lavcodec-60 -lavdevice-60 -lavfilter-9 -lavformat-60 -lavutil-58 -lswresample-4 -lswscale-7 -lm -lpthread
FLAG = -std=c11 -m64 -D__STDC_FORMAT_MACROS -mconsole #-Wall


main.exe:main.o
	$(CC) $(LinkDirFlag) $(LinkFlag) $(FLAG)  main.o -o main.exe


main.o:main.c
	$(CC) $(IncludeDirFlag) $(LinkFlag) $(FLAG) -c main.c -o main.o


clean:
	rm -rf main.exe main.o