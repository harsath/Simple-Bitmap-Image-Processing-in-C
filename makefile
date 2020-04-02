LOGGER_OUT:=logger.o
BMP_PROCESS:=bmp
LOGGER_SRC:=logger.c
BMP_SRC:=bmp_process1.c
LOGGER_HEADER:=logger.h

$(LOGGER_OUT):	$(LOGGER_SRC)
		gcc -c $(LOGGER_SRC)

$(BMP_PROCESS):	$(BMP_SRC) $(LOGGER_OUT) $(LOGGER_HEADER)
		gcc -Wall -o $(BMP_PROCESS) $(BMP_SRC) $(LOGGER_OUT)

clean:
	rm $(LOGGER_OUT) $(BMP_PROCESS)
