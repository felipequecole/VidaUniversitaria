PROGS=Lista.cpp Game.cpp main.cpp
SAIDA=VidaUniversitaria
LIBS=-L lib/SFML-2.4.2 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OPTS=-Wno-deprecated-declarations -o
all: compile

compile: $(PROGS)
	@echo "Compilando arquivos"
	@g++ $(PROGS) $(OPTS) $(SAIDA) $(LIBS)
	@echo "Fim da Compilação"
