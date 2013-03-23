#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <memory>

namespace sm {

namespace Private
{
template<typename RetType, typename ArgType>
class TStateHolder;


template<typename RetType, typename ArgType>
class StateMachine;

/// \brief state interface
template<typename RetType, typename ArgType >
class TState {
public:
    virtual RetType ExecuteStep(TStateHolder<RetType, ArgType>* stateMachine, ArgType argument ) = 0;
    virtual ~TState() {}
};

/// \brief specialization of the state interface without arguments
template<typename RetType>
class TState< RetType, void > {
public:
    virtual RetType ExecuteStep(TStateHolder<RetType, void>* stateMachine) = 0;
    virtual ~TState() {}
};

/// @brief the state holder class which keeps the current state of the state machine.
template< class RetType, class ArgType >
class TStateHolder {
private:
    /// @brief the type of the state.
    typedef TState< RetType, ArgType> State;

private:
    /// The executor is a friend of the StateHolder becuase he need the access to the state variable.
    template<class A, class B> friend class Executor;
    std::auto_ptr< State > m_currentState;

public:
    /// @brief will set a new state to the state machine.
    /// @param newState instance of the new state.
    /// @return bool true is the given state is not NULL, false otherwise.
    bool SetNewState( std::auto_ptr<State> newState ) {
        bool result = false;
        if( newState.get() != NULL ) {
            m_currentState =  newState;
            result = true;
        }

        return result;
    }

private:
    TStateHolder(std::auto_ptr<State> firstState) : m_currentState( firstState ) {}
    ~TStateHolder() {}
};


/// @brief the executor. Is a state execution algorithm.
/// @brief this class is needed in order to define different template specializations.
template<class RetType, class ArgType>
class Executor {
private:
    typedef TStateHolder<RetType, ArgType> StateHolder;

private:
    StateHolder m_stateHolder;

public:
    Executor( std::auto_ptr< TState<RetType, ArgType> > firstState ):m_stateHolder( firstState ) { }

    RetType ExecuteStep(ArgType argument) {
        RetType result;
        if(m_stateHolder.m_currentState.get() != NULL ) {
            result =  m_stateHolder.m_currentState->ExecuteStep(&m_stateHolder, argument );
        }

        return result;
    }

protected:
    virtual ~Executor() {}
};


template<class ArgType>
class Executor<void, ArgType> {
private:
    typedef TStateHolder<void, ArgType> StateHolder;

private:
    StateHolder m_stateHolder;

public:
    Executor( std::auto_ptr< TState<void, ArgType> > firstState ):m_stateHolder( firstState ) {}

    void ExecuteStep(ArgType argument) {
        if(m_stateHolder.m_currentState.get() != NULL ) {
            m_stateHolder.m_currentState->ExecuteStep( &m_stateHolder, argument );
        }
    }

    virtual ~Executor() {}
};


template<>
class Executor<void, void> {
private:
    typedef TStateHolder<void, void> StateHolder;

private:
    StateHolder m_stateHolder;

public:
    Executor( std::auto_ptr< TState<void, void> > firstState ):m_stateHolder( firstState ) {}

    void ExecuteStep() {
        if(m_stateHolder.m_currentState.get() != NULL ) {
            m_stateHolder.m_currentState->ExecuteStep( &m_stateHolder );
        }
    }

    virtual ~Executor() {}
};


template<class RetType>
class Executor<RetType, void> {
private:
    typedef TStateHolder<RetType, void> StateHolder;

private:
    StateHolder m_stateHolder;

public:
    Executor( std::auto_ptr< TState<RetType, void> > firstState ):m_stateHolder( firstState ) {}

    RetType ExecuteStep() {
        RetType result;
        if(m_stateHolder.m_currentState.get() != NULL ) {
            result =  m_stateHolder.m_currentState->ExecuteStep( &m_stateHolder );
        }

        return result;
    }

    virtual ~Executor() {}
};

}

/// @brief Generic state machine implementation.
template< class RetType, class ArgType >
class StateMachine : public Private::Executor<RetType, ArgType>
{
public:
    /// The base abstract state for the state machine.
    /// Needed in order to implement the states.
    typedef Private::TState< RetType, ArgType> BaseState;
    
    /// The return type of the executeStep method.
    typedef RetType ReturnType;
    
    /// The argument type of the executeStep method.
    typedef ArgType ArgumentType;
    
    /// The state holders type. Needed in order to walk through the states.
    typedef Private::TStateHolder<RetType, ArgType> StateHolder;
    
    /// Type of the state object.
    typedef std::auto_ptr<BaseState> StateObject;

public:
    /// @brief Constructor will initialize the object.
    /// @param firstState the initial state of the statemachine.
    StateMachine( StateObject firstState ) : Private::Executor<RetType, ArgType>( firstState ) {}
    virtual ~StateMachine() { }
};

}
#endif // STATEMACHINE_H

