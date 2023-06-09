#include "../include/States/LoadGameState.h"



States::LoadGameState::LoadGameState(States::StateMachine* pSMachine):
    State(pSMachine, States::stateID::loadGameState)
{
}

States::LoadGameState::~LoadGameState()
{
}

void States::LoadGameState::Update()
{
    std::ifstream savefile("Assets/levelSave.txt", std::ifstream::binary);
    int read;
    savefile >> read;
    
    if(savefile.eof())
    {
        std::cout << "ERROR: No Savefile Founded" << std::endl;
        changeState(States::stateID::mainMenu);
        return;
    }

    Levels::Level* pAux = NULL;

    std::list<Levels::Level*>::iterator it = levels.begin();
    while(it != levels.end())
    {
        if((*it)->getID() == read)
        {
            pAux = *it;
        }
        (*it)->Reset();
        it++;
    }

    savefile.close();
    pAux->LoadLevel();
    changeState(pAux->getStateID());
    pAux = NULL;
    /*  */
}

void States::LoadGameState::Draw()
{
}

void States::LoadGameState::PushLevel(Levels::Level* level)
{
    levels.push_back(level);
}