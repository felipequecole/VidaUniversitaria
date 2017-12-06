#include "Game.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>


Game::Game(){
    // aqui tem as gambiarras
    gameover = false;
    pause = true; //para iniciar no menu
    especial = true;
    gameisover = false;
    over.reset();
    over.pause();
    temposcore.reset();
    temposcore.pause();
    minDist = 200;
    vidas = 5;
    onScreen = 0;
    AonScreen = -1;
    contador = 0;
    vel = 1;
    special = 1;
    CriaLista(Highscore);
    Fonte.loadFromFile("Resource/Fonts/breja.ttf");
    FonteSpecial.loadFromFile("Resource/Fonts/Oswald.ttf");
    FonteHUD.loadFromFile("Resource/Fonts/IndieFlower.ttf");
    if(!Soundtrack.openFromFile("Resource/Sound/fundo.ogg")) std::cout << "Nao abriu o audio";
    if(!Easter.openFromFile("Resource/Sound/Show.ogg")) std::cout << "Deu ruim";

    hitbuffer.loadFromFile("Resource/Sound/hit.ogg");
    hitsound.setBuffer(hitbuffer);
    hitsound.setVolume(200);

    vidabuffer.loadFromFile("Resource/Sound/vida.ogg");
    vidasound.setBuffer(vidabuffer);
    vidasound.setVolume(500);

    overbuffer.loadFromFile("Resource/Sound/over.ogg");
    oversound.setBuffer(overbuffer);
    oversound.setVolume(500);

    Soundtrack.setVolume(20);
    Easter.setVolume(100);
    HP[0].setString("NNNNN");
    HP[1].setString("NNNN ");
    HP[2].setString("NNN ");
    HP[3].setString("NN ");
    HP[4].setString("N ");
    for (int i = 0; i < 5; i++){
        HP[i].setFont(Fonte);
        HP[i].setColor(sf::Color::White);
        HP[i].setPosition(135, 10);
        HP[i].setCharacterSize(40);
}
    TextSpecial.setFont(FonteSpecial);
    TextSpecial.setColor(sf::Color::White);
    TextSpecial.setPosition(680,15);
    TextSpecial.setCharacterSize(50);

    TextHSpecial.setFont(FonteHUD);
    TextHSpecial.setColor(sf::Color::White);
    TextHSpecial.setPosition(670,65);
    TextHSpecial.setCharacterSize(20);
    TextHSpecial.setString("BIRL restante");

    TextHUD.setFont(FonteHUD);
    TextHUD.setColor(sf::Color::White);
    TextHUD.setPosition(15,22);
    TextHUD.setCharacterSize(25);
    TextHUD.setString("Vida Social: ");

    TextPontuacao.setFont(FonteHUD);
    TextPontuacao.setColor(sf::Color::White);
    TextPontuacao.setPosition(400,22);
    TextPontuacao.setCharacterSize(25);

    //fim das gambiarras

    //Source para manipulacao do personagem
    mL = 0;
    mR = 7;
    srand(time(NULL));
    //Criando a tela
    Window.create(sf::VideoMode(800,600),"Vida Universitaria",sf::Style::None);
    Window.setFramerateLimit(60);
    //carregando as imagens do personagem
    //Left
        for(int i = 0 ,j = 0; j<7;j++,i++){
            if(!PTexture[j].loadFromFile("Resource/Player.png",sf::IntRect(i*52,0,52,85))){
                printf("Erro no carregamento da PTexture 0--4");
            }
        }
    //right
        for(int i = 0,j = 7; j<14;j++,i++){
            if(!PTexture[j].loadFromFile("Resource/Player.png",sf::IntRect(i*52,85,52,85))){
            printf("Erro no carregamento da PTexture 5--9");
            }
        }


    //Imagem de fundo
    if(!FTexture.loadFromFile("Resource/cenario3.jpg")){
        printf("Erro no carregamento da imagem");
    }

    insTexture.loadFromFile("Resource/como.png");
    insSprite.setTexture (insTexture);

    //imagem dos objetos
    OTexture[0].loadFromFile("Resource/objetos/objeto1.png");
    OTexture[1].loadFromFile("Resource/objetos/objeto2.png");
    OTexture[2].loadFromFile("Resource/objetos/objeto3.png");
    OTexture[3].loadFromFile("Resource/objetos/objeto4.png");
    OTexture[4].loadFromFile("Resource/objetos/objeto5.png");
    OTexture[5].loadFromFile("Resource/objetos/objeto6.png");
    OTexture[6].loadFromFile("Resource/objetos/objeto7.png");
    OTexture[7].loadFromFile("Resource/objetos/objeto8.png");
    OTexture[8].loadFromFile("Resource/objetos/objeto9.png");
    OTexture[9].loadFromFile("Resource/objetos/objeto10.png");
    OTexture[10].loadFromFile("Resource/objetos/objeto11.png");

    overTexture[0].loadFromFile ("Resource/GameOver/over1.png");
    overTexture[1].loadFromFile ("Resource/GameOver/over2.png");
    overSprite.setTexture (overTexture[0]);

    for (int i = 0; i < nINIMIGOS; i++) {
            Object[i].Sprite.setTexture(OTexture[i]); //inicia todas as sprites
            int x = (rand()%81)*10;
            Object[i].Sprite.setPosition(x,-20); //inicia em  um x aleatorio e fora da tela
            Object[i].naTela = false;
            Object[i].vivo = true; //ele ainda não morreu
            Object[i].evil = true;
    }

    ATexture[0].loadFromFile("Resource/objetos/tusca.png");
    ATexture[1].loadFromFile("Resource/objetos/corote.png");

    for (int i = 0; i < nALIADOS; i++) {
            Aliados[i].Sprite.setTexture(ATexture[i]);
            int x = (rand()%81) * 10;
            Aliados[i].Sprite.setPosition(x,-20); //inicia em  um x aleatorio e fora da tela
            //Aliados[i].Sprite.setScale(30,30);
            Aliados[i].naTela = false;
            Aliados[i].vivo = true; //ele ainda não morreu
            Aliados[i].evil = false;
    }

    //carregando imagens do jogador
    PSprite.setTexture(PTexture[0]);
    PSprite.setPosition(400,500);

    FSprite.setTexture(FTexture);

    //Menu
    if(!MTexture[0].loadFromFile("Resource/Menu/Menu.png")){
        printf("Erro no carregamento da imagem");
    }

    if(!MTexture[1].loadFromFile("Resource/Menu/Menu-1.png")){
        printf("Erro no carregamento da imagem");
    }

    if(!MTexture[2].loadFromFile("Resource/Menu/Menu-2.png")){
        printf("Erro no carregamento da imagem");
    }

    if(!MTexture[3].loadFromFile("Resource/Menu/Menu-3.png")){
        printf("Erro no carregamento da imagem");
    }

    MSprite.setTexture(MTexture[0]);

}

void Game::MouseListener(){

    if((95<sf::Mouse::getPosition(Window).x && sf::Mouse::getPosition(Window).x<195)&&
       (215<sf::Mouse::getPosition(Window).y && sf::Mouse::getPosition(Window).y<255)){
        Tmenu = 1;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            opMenu = 1;
        }
    }else if((50<sf::Mouse::getPosition(Window).x && sf::Mouse::getPosition(Window).x<255)&&
       (315<sf::Mouse::getPosition(Window).y && sf::Mouse::getPosition(Window).y<350)){
        Tmenu = 2;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            opMenu = 2;
        }

    }else if((100<sf::Mouse::getPosition(Window).x && sf::Mouse::getPosition(Window).x<175)&&
       (415<sf::Mouse::getPosition(Window).y && sf::Mouse::getPosition(Window).y<450)){
        Tmenu = 3;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            opMenu = 3;
        }
    }else{
        Tmenu = 0;
    }


}
void Game::WindowListener(){
    while(Window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                Window.close();
                gameover = true;
            }
          }
}

void Game::KeyListener () {
          //Controle das teclas
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                //movimentacao do personagem
                y = 0;
                mR = 6;
                if(0<PSprite.getPosition().x){
                        frameCounter += frameSpeed*clock.restart().asSeconds();
                        if(frameCounter >= switchFrame){
                            frameCounter = 0;
                            PSprite.move(-15,0);
                            mL++;
                            if(mL > 6){
                                mL = 0;
                            }

                            }
                }


            }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                y = 1;
                mL = 0;

                if(PSprite.getPosition().x<750){
                        frameCounter += frameSpeed*clock.restart().asSeconds();
                        if(frameCounter >= switchFrame){
                            frameCounter = 0;
                            PSprite.move(15,0);
                            mR++;
                            if(mR > 13){
                                mR = 7;
                            }

                        }

                }

            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                opMenu = 0;
                pause = true;
                gameover = true;
            }

    }

void Game::renderJogo() {
       Window.clear();
       Window.draw(FSprite);  //renderiza fundo

       if(y == 0){
            PSprite.setTexture(PTexture[mL]);
        }else if (y == 1){
            PSprite.setTexture(PTexture[mR]);
        }

       for (int i = 0; i < nINIMIGOS; i++){
            if (Object[i].naTela && Object[i].vivo) Window.draw(Object[i].Sprite);
       }

       for (int i = 0; i < nALIADOS; i++) {
            if (Aliados[i].naTela && Aliados[i].vivo) Window.draw(Aliados[i].Sprite);
       }

       {//vidas
       if (vidas > 0) Window.draw(HP[5-vidas]);
       //fim do indicador de vidas
       }

        //especial
        sprintf(c_especial, "%.2f", 15.0 - tespecial.getElapsedTime().asSeconds() > 0 ? 15.0 - tespecial.getElapsedTime().asSeconds() : 0.0);
        std::string t_especial(c_especial);
        TextSpecial.setString(t_especial);
        Window.draw(TextSpecial);
       //fim especial

       //pontuacao
       sprintf(pontuacao, "%d", get_score());
       std::string spontuacao(pontuacao);
       std::string tpontuacao = "Score: " + spontuacao;
       TextPontuacao.setString(tpontuacao);
       Window.draw(TextPontuacao);
       score = get_score();
       //fim da pontuacao

        //HUD
        Window.draw(TextHUD);
        Window.draw(TextHSpecial);
        //fim do HUD


        Window.draw(PSprite);
        Window.display();

}


void Game::renderMenu() {
    Window.clear();
    Soundtrack.setVolume(20);

    //inicio do Ranking
    //Insere(Highscore, get_score(), ok);

    const int zero = 0;
    char h1[100], h2[100], h3[100];
    if (!Vazia(Highscore)) {
        sprintf(h1, "%d", Highscore->info);
        sprintf(h2, "%d", Highscore->next != NULL ? Highscore->next->info : 0);
        if (Highscore->next != NULL) sprintf(h3, "%d", Highscore->next->next != NULL ? Highscore->next->next->info : 0);
        else sprintf(h3, "%d", zero);
    }
    else {
        std::cout << "Entrou no else" << std::endl;
        sprintf(h1, "%d", zero);
        sprintf(h2, "%d", zero);
        sprintf(h3, "%d", zero);
    }

    std::string sh1(h1);
    std::string sh2(h2);
    std::string sh3(h3);
    sh1 = "1. " + sh1;
    sh2 = "2. " + sh2;
    sh3 = "3. " + sh3;

    TextHighscore[0].setString (sh1);
    TextHighscore[1].setString (sh2);
    TextHighscore[2].setString (sh3);
    TextHighscore[3].setString ("Ranking: ");

    for (int i = 0; i < 3; i++) {
        TextHighscore[i].setFont(FonteSpecial);
        TextHighscore[i].setPosition (700,(150+(40*i)));
        TextHighscore[i].setCharacterSize(30);
    }
    TextHighscore[3].setPosition(660, 95);
    TextHighscore[3].setFont(FonteHUD);
    TextHighscore[3].setCharacterSize(35);

    //fim do ranking

    MSprite.setTexture(MTexture[Tmenu]);
    Window.draw(MSprite);
    Window.draw(TextPontuacao);
    for (int i = 0; i < 4; i++) {
        Window.draw(TextHighscore[i]);
    }

    Window.display();
}

void Game::renderIntrucoes(){
    Window.clear();
    Window.draw(insSprite);
    Window.display();
}

void Game::renderOver() {
    Window.clear();

    Soundtrack.setVolume(0);
    hitsound.stop();
    over.resume();
    Window.draw(overSprite);
    TextOver.setFont(FonteHUD);
    TextOver.setCharacterSize(40);
    TextOver.setPosition (510,340);
    TextOver.setColor(sf::Color::White);
    std::string anos;

    sf::Text recurso;
        recurso.setCharacterSize(30);
        recurso.setFont(FonteHUD);
        recurso.setPosition(420,380);
        recurso.setString("(com recurso)");

    if (get_score() < 50)
        anos = "4";
    else if (get_score() < 100)
        anos = "5";
    else if (get_score() < 150)
        anos = "6";
    else if (get_score() < 250)
        anos = "7";
    else {
        anos = "8";
    }

    if (over.getElapsedTime().asSeconds() > 3.4) {
        overSprite.setTexture(overTexture[1]);
        gameover = true;
        TextOver.setString(anos);
        Window.draw(TextOver);
        if (get_score()>=250) Window.draw(recurso);
        KeyListener();
        WindowListener();
    }
    Window.display();
}

bool Game::collision (bool &isEvil) {

    for (int i = 0; i  < nINIMIGOS; i++) {
        if(Object[i].naTela && Object[i].vivo){
            OBox = Object[i].Sprite.getGlobalBounds();
            PBox = PSprite.getGlobalBounds();
            if (PBox.intersects(OBox)) {
                isEvil = true;
                Object[i].vivo = false;
                Object[i].naTela = false;
                return true;
            }
        }
    }

    for (int i = 0; i < nALIADOS; i++) {
        if (Aliados[i].naTela && Aliados[i].vivo) {
            ABox = Aliados[i].Sprite.getGlobalBounds();
            PBox = PSprite.getGlobalBounds();
            if (PBox.intersects(ABox)) {
                isEvil = false;
                Aliados[i].vivo = false;
                Aliados[i].naTela = false;
                if (i==1) vidas = 5;
                return true;
            }
        }
    }

    return false;

}

void Game::logic() { //logica de "lançamento" dos inimigos
    bool isEvil;
    bool PodeSoltar = true;
    if (contador%11 == 0 && AonScreen < nALIADOS) AonScreen = 0;
    else if (contador%37 == 0 && AonScreen < nALIADOS) AonScreen = 1;
    else AonScreen = -1;
    if (!pause){
        for (int i = 0; i <= nINIMIGOS; i++) { //ele "chama" o proximo objeto para tela
            if (Object[i].Sprite.getPosition().y < minDist && Object[i].naTela)    {
                    PodeSoltar = false;
                    //onScreen = (onScreen+1)%11; //se ele atinge essa posicao, outro começa a cair
                    //contador++;
            }
            //Object[onScreen].naTela = true;
        }
        if (PodeSoltar) {
            onScreen = (onScreen+1)%11; //se ele atinge essa posicao, outro começa a cair
            contador++;
            Object[onScreen].naTela = true;
        }

        for (int i = 0; i <= nINIMIGOS; i++) {
                 //movement.reset();
                 //movement.resume();
            if (Object[i].naTela) { //só move quem está na tel
                        Object[i].Sprite.move(0,((3.0*vel)/(float)special));
            }

            if (Object[i].Sprite.getPosition().y > 550) { //se saiu da tela, para de se mover (vai para o reset)
                Object[i].naTela  = false;
                Object[i].vivo = false;
            }
            else if (collision(isEvil)) { //se foi um hit
                if (isEvil) {
                    vidas-=1;
                    hitsound.play();
                }
                else {
                    if (vidas < 5) vidas+=1;
                    vidasound.play();
                }
            }
        }

        for (int i = 0; i <= AonScreen; i++) {
            Aliados[i].naTela = true;
        }

        for (int i = 0; i < nALIADOS; i++) {
            if (Aliados[i].naTela) {

               if (i==0) Aliados[i].Sprite.move(0,1);
               else Aliados[i].Sprite.move(0,1);

                if (Aliados[i].Sprite.getPosition().y > 550) {
                Aliados[i].naTela  = false;
                Aliados[i].vivo = false;
            }
            }
        }

        switch (contador) {
        case 10:
            minDist = 150;
            vel = 1.1;
            break;
        case 20:
            minDist = 125;
            vel = 1.2;
            break;
        case 30:
            minDist = 100;
            vel = 1.3;
            break;
        case 40:
            minDist = 50;
            vel = 1.5;
            break;
        case 50:
            minDist = 30;
            vel = 2;
        }

        if (vidas <= 0) {
            bool ok;
            InsereRec(Highscore, get_score(), ok);
            if (ok) std::cout << "inseriu" << std::endl;
            oversound.play();
            gameisover = true;
            pause = true;
            gameover = true;
        }

        for (int i = 0; i < nINIMIGOS; i++) { //mantem o jogo infinito
            if (!Object[i].vivo) {
                int x = (rand()%81)*10;
                Object[i].Sprite.setPosition(x,-20); //inicia em  um x aleatorio e fora da tela
                Object[i].naTela = false;
                Object[i].vivo = true; //REBORN!
            }
        }

        for (int i = 0; i < nALIADOS; i++) {
            if (!Aliados[i].vivo) {
                int x = (rand()%81)*10;
                Aliados[i].Sprite.setPosition(x,-20); //inicia em  um x aleatorio e fora da tela
                Aliados[i].naTela = false;
                Aliados[i].vivo = true; //REBORN!
            }
        }

    }
}




void Game::run() {
    Soundtrack.setLoop(true);
    Easter.setLoop(false);
    Soundtrack.play();
   while (Window.isOpen()) {

            sf::Vector2f Local;
            Local.x = 400;
            Local.y = 22;
            if (opMenu == 0) TextPontuacao.setPosition(260,550);
            else TextPontuacao.setPosition(Local);

            if(opMenu == 0){
            WindowListener();
            MouseListener();
            renderMenu();
        }else if(opMenu == 1 ){
            WindowListener();
            pause = false;
            if (vidas > 0) gameover = false;
            else reset();
            while (!gameover && !gameisover) {
                temposcore.resume();
                logic();
                KeyListener();
                WindowListener();
                renderJogo();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && tespecial.getElapsedTime().asSeconds() < 15.0) {
                    Easter.play();
                    special = 2;
                    tespecial.resume();
                    std::cout << tespecial.getElapsedTime().asSeconds() << std::endl;
                    //std::cout << tespecial.getElapsedTime().asSeconds() << std::endl;
                }
                else {
                    tespecial.pause();
                    special = 1;
                }

            }
            if (!gameisover ) {
                opMenu = 0;
                renderMenu();
                temposcore.pause();
            }
            else {
                opMenu = 4;
            }

        }else if (opMenu == 2){
            WindowListener();
            KeyListener();
            renderIntrucoes();
        }else if (opMenu == 3){
            Window.close();
        }else if (opMenu == 4) {
            renderOver();
        }
        }
    //tratando score


    //fim do score
}

void Game::reset() { //reinicia o jogo (mantem ele infinito)
    vidas = 5;
    onScreen = 0;
    AonScreen = -1;
    tespecial.reset();
    gameisover = false;
    over.reset();
    over.pause();
    temposcore.reset();
    temposcore.pause();
    vel = 1.0;
    minDist = 200;
    contador = 0;
    overSprite.setTexture(overTexture[0]);

    for (int i = 0; i < nINIMIGOS; i++) { //reinicia os obstaculos
            int x = (rand()%81)*10;
            Object[i].Sprite.setPosition(x,-20); //inicia em  um x aleatorio e fora da tela
            Object[i].naTela = false;
            Object[i].vivo = true; //ele ainda não morreu
    }

    for (int i = 0; i < nALIADOS; i++) { //reinicia os buffs
        int x = (rand()%81) * 10;
        Aliados[i].Sprite.setPosition(x,-20); //inicia em  um x aleatorio e fora da tela
        Aliados[i].naTela = false;
        Aliados[i].vivo = true; //ele ainda não morreu
    }

}

int Game::get_score() {
    int score = (int)temposcore.getElapsedTime().asSeconds();
    return score;
}
