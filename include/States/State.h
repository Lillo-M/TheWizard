#pragma once
#include <stdlib.h>

namespace States
{
    class StateMachine;

    enum stateID
    {
        empty =        -1,
        mainMenu =      0,
        alaska =        1,
        gameOverState = 2,
        pauseMenu =     3,
        loadGameState = 4,
        newGameMenu  =  5,
        leaderBoard   = 6,
        vulcano =        7
    };

    class State
    {
    public:
        State(StateMachine* pSMachine = NULL, States::stateID id = empty);
        virtual ~State();
        void setStateMachine(StateMachine* pSMachine);
        void changeState(States::stateID sID);
        const States::stateID getStateID() const;
        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual void Reset();
        const bool getIsRunning() const;
    protected:
        bool isRunning;
        StateMachine* pSMachine;
        stateID id;
        static State* previousState;
    };
}