# Имя программы
TARGET = rpn

# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra

# Исходные файлы
SRC = src/rpn.cpp

# Цель по умолчанию
all: $(TARGET)

# Как собрать программу
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Очистка мусора
clean:
	rm -f $(TARGET)

