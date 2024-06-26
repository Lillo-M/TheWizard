#include "../include/Managers/GraphicManager.h"

Managers::GraphicManager::GraphicManager(): 
    window(sf::VideoMode(WIDTH, HEIGHT), "The Wizard++"), // incializa a janela
    view(window.getView()),
    LeftLimit(WIDTH / 2),
    RightLimit(WIDTH / 2),
    BottomLimit(HEIGHT / 2)
{
    settings.antialiasingLevel = 16;
}

Managers::GraphicManager::~GraphicManager()
{
    //std::cout << "GraphicManager Destructor" << std::endl;
    std::map<const char *, sf::Texture *>::iterator it;
    for (it = textureMap.begin(); it != textureMap.end(); it++)
    {
        if (it->second)
            delete it->second;
    }
    Instance = NULL;
}

Managers::GraphicManager *Managers::GraphicManager::getInstance()
{
    if (!Instance) // se não houver ainda uma instancia de gerenciador grafico
    {
        Instance = new GraphicManager; // ele cria uma
        if (!Instance)
        {
            std::cout << std::endl
                      << "ERROR: Failed to Allocate Memory" << std::endl;
            return NULL;
        }
    }
    return Instance; // e por fim retorna ela ou se já havia ele retorna direto.
}

void Managers::GraphicManager::Draw(sf::RectangleShape &hitbox)
{
    window.draw(hitbox); // literalmente só desenha na tela o hitbox que entrou como parametro
}

void Managers::GraphicManager::Draw(sf::Text &text)
{
    window.draw(text); // desenha texto
}
void Managers::GraphicManager::Display()
{
    window.display(); // mostra na tela tudo que foi desenhado até o momento
}

void Managers::GraphicManager::Clear()
{
    window.clear(); // limpa a janela
}

void Managers::GraphicManager::Close()
{
    window.close(); // fecha a janela
}

sf::RenderWindow *Managers::GraphicManager::getWindow() { return &window; } // retorna um ponteiro para a janela (usado no EventManager que depende da janela)

const bool Managers::GraphicManager::isWindowOpen() const { return window.isOpen(); } // retorna se a janela está aberta ou não

void Managers::GraphicManager::CenterView(sf::Vector2f pos)
{
    if (pos.y < BottomLimit)
        pos = sf::Vector2f(pos.x, BottomLimit - (BottomLimit - pos.y));
    else 
        pos = sf::Vector2f(pos.x, BottomLimit);
    if (pos.x < LeftLimit)
        pos = sf::Vector2f(LeftLimit, pos.y);
    if (pos.x > RightLimit)
        pos = sf::Vector2f(RightLimit, pos.y);
    /*  */
    
    view.setCenter(pos);
    window.setView(view);
}

void Managers::GraphicManager::updateDeltaTime()
{
    dt = static_cast<float>(clock.getElapsedTime().asSeconds());
    if (dt > 0.3f)
    {
        std::cout << std::endl
                  << "STUTTER DETECTED!" << std::endl;
        dt = 0;
    }
    clock.restart();
}

float Managers::GraphicManager::getDeltaTime()
{
    return dt;
}

sf::Vector2f Managers::GraphicManager::getViewCenter() const {return view.getCenter();}

sf::Texture *Managers::GraphicManager::loadTexture(const char *path)
{
    std::string texture_path = std::string(THE_WIZARD_PATH) + "/" + std::string(path);
    std::map<const char *, sf::Texture *>::iterator it;
    for (it = textureMap.begin(); it != textureMap.end(); it++)
    {
        if (!strcmp(it->first, path))
            return textureMap[path];
    }
    sf::Texture *texture = new sf::Texture;
    textureMap[path] = texture;
    try
    {
        textureMap[path]->loadFromFile(texture_path);
    }
    catch (int error)
    {
        if (!error)
        {
            std::cout << "ERROR: Failed to load Texture file" << std::endl;
            exit(1);
        }
    }

    return textureMap[path];
}

void Managers::GraphicManager::setLeftLimit(float limit)
{
    LeftLimit = limit;
}

void Managers::GraphicManager::setRightLimit(float limit)
{
    RightLimit = limit;
}

void Managers::GraphicManager::setBottomLimit(float limit)
{
    BottomLimit = limit;
}

Managers::GraphicManager *Managers::GraphicManager::Instance(NULL); // incializa o ponteiro estatico para a instancia de Gerenciador grafico
float Managers::GraphicManager::dt(0);
sf::Clock Managers::GraphicManager::clock;
