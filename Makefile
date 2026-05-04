CC=/usr/bin/gcc
WCC=/usr/bin/x86_64-w64-mingw32-gcc
SRC=main.c write.c
DEVFLAGS=-Wall -Wextra -Wpedantic -g
RELEASEFLAGS=-Wall -Wextra -Wpedantic -O3 -static -flto

TARGET = VMTranslator
WTARGET = VMTranslator.exe

all: $(TARGET)
	$(CC) $(DEVFLAGS) $(SRC) -o $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(DEVFLAGS) $(SRC) -o $(TARGET)

release:
	$(CC) $(RELEASEFLAGS) $(SRC) -o $(TARGET)
	$(WCC) $(RELEASEFLAGS) $(SRC) -o $(WTARGET)

clean:
	rm -rf $(TARGET) $(WTARGET)
