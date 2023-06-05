#include "../include/Levels/Level1.h"

Levels::Level1::Level1(States::StateMachine* pSM, Managers::InputManager* pIM) : 
    Level(ID::level1, pSM, pIM)
{
    CreateMap();
    pCManager->setDList(DentitiesList.getTList());
    pCManager->setSList(SentitiesList);
    texture = pGM->loadTexture("Assets/Nature.png");
    background.setTexture(*texture);
    background.setScale(2.22f, 2.37);
    background.setOrigin(texture->getSize().x/(float)2, texture->getSize().y/(float)2);
}

Levels::Level1::~Level1()
{
}

void Levels::Level1::CreateMap()
{
    std::ifstream Map;
    std::string str;
    int j = 0;
    Map.open("Assets/Level1.txt");
    if (!Map.is_open())
    {
        std::cout << "ERROR: Failed to Open 'Level1.txt'" << std::endl;
        exit(1);
    }

    while (std::getline(Map, str))
    {
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] != ' ')
            {
                CreateEntity(str[i], sf::Vector2f(i, j));
            }
        }
        j++;
    }
    Map.close();
}

void Levels::Level1::Draw()
{
    Math::EntityTList::Iterator it;

    /* teste */
    background.setPosition(pGM->getViewCenter());
    pGM->getWindow()->draw(background);
    DentitiesList.DrawEntities();

    it = SentitiesList.begin();    
    for(it; it != SentitiesList.end(); it++)
    {
	    it->Draw();
    }
}