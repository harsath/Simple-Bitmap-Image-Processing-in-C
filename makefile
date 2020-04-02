LOGGER_OUT:="logger.o"
BMP_PROCESS:="bmp"
LOGGER_SRC:="logger.c"
BMP_SRC:="bmp_process1.c"

logger:	$(LOGGER_SRC)
		gcc -c $(LOGGER_OUT)

bmp:	$(BMP_SRC)
		gcc -Wall -o $(BMP_PROCESS) $(BMP_SRC) $(LOGGER_OUT)

clean:
	rm $(LOGGER_OUT) $(BMP_PROCESS)
