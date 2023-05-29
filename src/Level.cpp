#include "../include/Levels/Level.h"

Levels::Level::Level(const ID id, States::StateMachine* pSM, Managers::InputManager* pIM) : 
    State(pSM, States::stateID::level1),
    Being(id),
    pIM(pIM),
    pPlayer(NULL),
    pPlayer2(NULL)
{
    try{
        pCManager = new Managers::CollisionManager;
    }
    catch (int error){
        if(!error){
            std::cout << std::endl
                  << "ERROR: Failed to Allocate Memory" << std::endl;
            exit(1);
        }
    }
    try{
        pPIM = new Observers::PlayerInputManager(NULL, NULL, static_cast<States::State*>(this));
    }
    catch (int error){
        if(!error){
            std::cout << std::endl
                  << "ERROR: Failed to Allocate Memory" << std::endl;
            exit(1);
        }
    }
    this->pIM->addObserver(static_cast<Observers::Observer*>(pPIM));
}

Levels::Level::~Level()
{
    this->pIM->removeObserver(static_cast<Observers::Observer*>(pPIM));
    if(pPIM)
        delete pPIM;
    pPIM = NULL;
    /*for (int i = 0; i < DentitiesList.getSize(); i++)
    {
        if (DentitiesList[i])
            delete DentitiesList[i];
    }
    DentitiesList.clear();
    /* teste  */
    DentitiesList.DeleteEntities();
    /*  */
    for (int i = 0; i < SentitiesList.getSize(); i++)
    {
        if (SentitiesList[i])
            delete SentitiesList[i];
    }
    SentitiesList.clear();   
    if(pCManager)
        delete pCManager;
    pCManager = NULL;
}

void Levels::Level::CreatePlayer(const sf::Vector2f pos)
{
    Entities::Characters::Player *pAux = new Entities::Characters::Player(pos);
    if (!pAux)
    {
        std::cout << std::endl
                  << "ERROR: Failed to Allocate Memory" << std::endl;
        exit(1);
    }
    if(!pPlayer)
    {
        pPlayer = pAux;
        pPIM->setpPlayer(pAux);
    }
    else
    {
        pPlayer2 = pAux;
        pPIM->setpPlayer2(pAux);
    }

    std::vector<Entities::Projectile*>::iterator it;

    for(it = pAux->getShots()->begin(); it != pAux->getShots()->end(); it++)
    {
	    DentitiesList.Push_FrontEntity(static_cast<Entities::Entity *>(*it));
    }

    DentitiesList.Push_FrontEntity(static_cast<Entities::Entity *>(pAux));
}

void Levels::Level::CreateWarrior(const sf::Vector2f pos)
{
    Entities::Characters::Enemies::Warrior *pAux = new Entities::Characters::Enemies::Warrior(pos);
    if (!pAux)
    {
        std::cout << std::endl
                  << "ERROR: Failed to Allocate Memory" << std::endl;
        exit(1);
    }
    DentitiesList.Push_BackEntity(static_cast<Entities::Entity *>(pAux));
}

void Levels::Level::CreateGround(const sf::Vector2f pos)
{
    Entities::Obstacles::Ground *pAux = new Entities::Obstacles::Ground(pos);
    if (!pAux)
    {
        std::cout << std::endl
                  << "ERROR: Failed to Allocate Memory" << std::endl;
        exit(1);
    }
    SentitiesList.insert_back(static_cast<Entities::Entity *>(pAux));
}


void Levels::Level::CreateEntity(char id, sf::Vector2f pos)
{
    pos = sf::Vector2f( 64 + pos.x * 64, pos.y * 64);
    switch (id)
    {
    case 'P':
        CreatePlayer(pos);
        break;
    case 'W':
        CreateWarrior(pos);
        break;
    case 'G':
        CreateGround(pos);
        break;
    }
}

void Levels::Level::Update()
{
    isRunning = true;
    //std::cout << pPlayer->getPosition().y << "pos" << std::endl;
    //std::cout << pPlayer->getAlive() << std::endl;
    Math::EntityTList::Iterator it;
    DentitiesList.UpdateEntities();

    for (it = SentitiesList.begin(); it != SentitiesList.end(); it++)
    {
        it->Update();
    }

    Entities::Entity::updateDeltaTime(Managers::GraphicManager::getDeltaTime());
    Managers::GraphicManager::updateDeltaTime();
    pCManager->Manage();
    pGM->CenterView(pPlayer->getPosition());
}

void Levels::Level::Draw()
{
    Math::EntityTList::Iterator it;

    DentitiesList.DrawEntities();

    it = SentitiesList.begin();    
    for(it; it != SentitiesList.end(); it++)
    {
	    it->Draw();
    }

}

void Levels::Level::SaveLevel()
{
    std::ofstream savefile("Assets/savefile.txt", std::ofstream::binary);
	std::string line;
	savefile << this->getID() << std::endl;
    if(pPlayer2)
    {
        savefile << 1 << std::endl;
    }
    else
        savefile << 0 << std::endl;
    DentitiesList.Save(savefile);
    savefile << "end" << std::endl;
    savefile.close();
}

void Levels::Level::LoadLevel()
{
    int iread;
    float x;
    float y;
    std::ifstream savefile("Assets/savefile.txt", std::ifstream::binary);
    std::string line; // Brincando com persistencia de objetos . . . 
    savefile >> iread;
    savefile >> iread;
    savefile >> iread;
    Math::EntityTList::Iterator it = DentitiesList.getTList().begin();

    if(static_cast<bool>(iread) == true)
    {
        std::cout << "2 players" << std::endl;
        for(int i = 0; i < 2; i++)
        {
            savefile >> iread;
            static_cast<Entities::Characters::Player*>(*it)->setLives(iread);
            savefile >> iread;
            static_cast<Entities::Characters::Player*>(*it)->setAlive(static_cast<bool>(iread));
            savefile >> x;
            savefile >> y;
            std::cout << x << "," << y <<std::endl;
            it->setPosition(x,y);
            savefile >> x;
            savefile >> y;
            it->setVelocity(x,y);
            for(int j = 0; j < 10; j++)
            {
                static_cast<Entities::Characters::Player*>(*it)->getShots()->operator[](j)->Load(savefile);
            }
            it++;
        }
    }
    else
    {
        savefile >> iread;
        static_cast<Entities::Characters::Player*>(*it)->setLives(iread);
        savefile >> iread;
        static_cast<Entities::Characters::Player*>(*it)->setAlive(static_cast<bool>(iread));
        savefile >> x;
        savefile >> y;
        it->setPosition(x,y);
        savefile >> x;
        savefile >> y;
        it->setVelocity(x,y);
        for(int j = 0; j < 10; j++)
        {
            static_cast<Entities::Characters::Player*>(*it)->getShots()->operator[](j)->Load(savefile);
        }
        it++;
    }
    for(it; it != DentitiesList.getTList().end(); it++)
    {
        if(it->getID() == ID::projectile)
            continue;
        static_cast<Entities::Characters::Enemies::Warrior*>(*it)->Load(savefile);
    }
    savefile.close();
    /*  */
}



Observers::PlayerInputManager* Levels::Level::getPlayerInputManager() const { return pPIM;}
