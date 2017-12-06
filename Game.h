#pragma once
#define nINIMIGOS 11
#define nALIADOS 2
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "sftools/Chronometer.hpp"
//#include "Lista.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include "Lista.h"

typedef struct Objeto {
    sf::Sprite Sprite;
    bool naTela;
    bool vivo;
    bool evil; ///evil is the standard
} Objeto;

class Game{
    public:
        Game();
        void run();
    private:
        int vidas;
        int contador;
        bool gameover;
        bool especial;
        bool pause;
        bool gameisover;
        int onScreen;
        int AonScreen;
        int minDist;
        int vel;
        int special;
        std::string t_especial;
        std::string spontuacao;
        char c_especial[100], pontuacao[100];
        sf::Music Soundtrack;
        sf::Music Easter;
        sf::SoundBuffer hitbuffer, vidabuffer, overbuffer;
        sf::Sound hitsound, vidasound, oversound;
        sf::Font Fonte, FonteSpecial, FonteHUD;
        sf::Text HP[5], TextSpecial, TextHUD, TextHSpecial, TextPontuacao, TextHighscore[4], TextOver;
        //fim das gambiarras (ou nao)
        sf::RenderWindow Window;
        sf::Event event;
        sf::Texture PTexture[14],FTexture,OTexture[nINIMIGOS],MTexture[4], ATexture[2], overTexture[2], insTexture;
        sf::Sprite PSprite,FSprite,MSprite,overSprite, insSprite;
        Objeto Object[nINIMIGOS];
        Objeto Aliados[nALIADOS];
        sf::FloatRect PBox, OBox, ABox;
        sf::Clock clock;
        sf::Clock clockdiv;
        sftools::Chronometer tespecial;
        sftools::Chronometer temposcore;
        sf::Time timeSinceLastUpdate;
        sf::Time TimePerFrame;
        int mL,mR,y,opMenu = 0,Tmenu = 0;
        float frameCounter = 0, switchFrame = 100, frameSpeed = 2500;
        bool collision(bool &isEvil);

        void WindowListener();
        void KeyListener();
        float delta;
        void MouseListener();

        int get_score ();
        int score;
        Lista Highscore;
        //ofstream saida_score;
        //ifstream entrada_score;

        void renderMenu();
        void renderJogo();
        void renderIntrucoes();
        void renderOver();
        sftools::Chronometer over;

        void logic();
        void reset();
        float frameRate;


};
