#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <memory>
#include <cstddef>

namespace utils
{

namespace priv
{

template<typename RetType, typename EventType, template<class,EventType> class Transitions>
class StateHolder;

template<typename RetType, typename EventType, template<class,EventType> class Transitions>
class StateMachine;


/// @brief the state interface.
template<typename RetType, typename EventType, template<class,EventType> class Transitions>
class IState
{
private:
    StateHolder<RetType, EventType, Transitions>& m_owner;

private:
    virtual RetType ExecuteStepImpl ( StateHolder<RetType, EventType, Transitions>& stateMachine ) = 0;

protected:
    IState ( StateHolder<RetType, EventType, Transitions>& stateHolder ) : m_owner ( stateHolder ) {};

public:
    RetType ExecuteStep ( StateHolder<RetType, EventType, Transitions>& stateMachine ) {
        return ExecuteStepImpl ( stateMachine );
    }

    virtual ~IState() {}
};


/// @brief the state holder class which keeps the current state of the state machine.
template<typename RetType, typename EventType, template<class,EventType> class Transitions >
class StateHolder
{
private:
    /// @brief the type of the state.
    typedef IState<RetType, EventType, Transitions> State;
    typedef RetType ReturnType;

private:
    template<class, bool> friend class Executor;
    std::unique_ptr< State > m_currentState;

public:
    template< typename StateCreator >
    StateHolder( StateCreator creator){
      m_currentState.reset( creator( *this ) );
    }

    ~StateHolder() {}

    /// @brief will set a new state to the state machine.
    /// @param newState instance of the new state.
    /// @return bool true is the given state is not NULL, false otherwise.
    template< class StateType, EventType event, typename... Args>
    void SendEvent ( Args... args ) {
        typedef typename Transitions<StateType, event>::NextState NextState;
        m_currentState.reset ( new NextState ( *this, args... ) );
    }
};


template<typename StateHolder, bool includeExecutor>
class Executor {};

template<typename StateHolder>
class Executor<StateHolder, false >
{
protected:
    StateHolder m_stateHolder;

protected:
    ~Executor() {}

public:
    template< typename StateCreator>
    Executor( StateCreator creator) : m_stateHolder( creator) {
    }
};


template<typename StateHolder>
class Executor<StateHolder, true> : public Executor<StateHolder, false>
{
protected:
    typedef typename StateHolder::ReturnType RetType;
    typedef Executor<StateHolder, false> NullExecutor;

protected:
    ~Executor() {}

public:
    template< typename StateCreator >
    Executor( StateCreator creator) : NullExecutor( creator) {
    }

    RetType ExecuteStep() {
        return Executor<StateHolder, false>::m_stateHolder.m_currentState->ExecuteStep ( NullExecutor::m_stateHolder );
    }
};

}


/// @brief Generic state machine implementation.
template<typename EventType, template<class,EventType> class Transitions, typename RetType = void, bool includeExecutor = false>
class StateMachine : public priv::Executor< priv::StateHolder<RetType, EventType, Transitions>, includeExecutor >
{
private:
    typedef priv::Executor< priv::StateHolder<RetType, EventType, Transitions>, includeExecutor > Executor;

public:
    typedef priv::IState<RetType, EventType, Transitions> State;
    typedef priv::StateHolder<RetType, EventType, Transitions> StateHolder;
    typedef RetType ReturnType;

public:
    /// @brief Constructor will initialize the object.
    /// @param creator the creator function for the first state.
    template< typename StateCreator>
    StateMachine(StateCreator creator) : Executor(creator) {}
    ~StateMachine() { }
};

}

#define DEFINE_TRANSITION( TRANSITION, EVENT )\
struct InvalidState{};\
template<class CurState, EVENT event>\
struct TRANSITION { typedef InvalidState NextState; };\
 
#define REGISTER_TRANSITION( TRANSITION, STATE, EVENT, NEXT_STATE)\
template<> struct TRANSITION<STATE, EVENT>{ typedef NEXT_STATE NextState; };\
 
#endif // STATEMACHINE_H


