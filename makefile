# Nom de l'exécutable
TARGET = TheGarden

# Compilateur C++
CC = g++

# Options de compilation
CFLAGS = -std=c++11 -Wall

# Bibliothèques SFML
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Répertoire des fichiers d'en-tête
INCLUDES = -I/home/antoninlarvor/Bureau/TheGarden/include

# Répertoire des fichiers source
SRC_DIR = src

# Fichiers source
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Répertoire de sortie pour les fichiers objets
OBJ_DIR = obj

# Fichiers objets générés
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(SFML_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean

