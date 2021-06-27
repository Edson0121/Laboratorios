CC = gcc # Compilador
CFLAGS = -Wall -Werror # Warning flags
LDFLAGS = # Linking flags
OBJFILES = colas.o # Object files //callback.o
TARGET = output

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
#gcc -Wall -Werror -o output ejercicio3.o

clean:
	rm - f $(OBJFILES) $(TARGET) *~