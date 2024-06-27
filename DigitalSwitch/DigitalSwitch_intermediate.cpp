#include <iostream>
#include <map>

// Enumeration for switch states
enum class SwitchState {
    OFF,
    LOW,
    MODERATE,
    HIGH
};

// Context interface
class IContext {
public:
    virtual void setState(SwitchState nextState) = 0;
};

// State handler interface
class IStateHandler {
public:
    virtual void handleState(IContext* context) = 0;
};

// State handler factory interface
class IStateHandlerFactory {
public:
    virtual IStateHandler* create(SwitchState state) = 0;
};

// Off state handler
class OffStateHandler : public IStateHandler {
public:
    void handleState(IContext* context) override {
        std::cout << "OffStateHandler: Handling state transition from OFF to LOW" << std::endl;
        context->setState(SwitchState::LOW);
    }
};

// Low state handler
class LowStateHandler : public IStateHandler {
public:
    void handleState(IContext* context) override {
        std::cout << "LowStateHandler: Handling state transition from LOW to MODERATE" << std::endl;
        context->setState(SwitchState::MODERATE);
    }
};

// Moderate state handler
class ModerateStateHandler : public IStateHandler {
public:
    void handleState(IContext* context) override {
        std::cout << "ModerateStateHandler: Handling state transition from MODERATE to HIGH" << std::endl;
        context->setState(SwitchState::HIGH);
    }
};

// High state handler
class HighStateHandler : public IStateHandler {
public:
    void handleState(IContext* context) override {
        std::cout << "HighStateHandler: Handling state transition from HIGH to OFF" << std::endl;
        context->setState(SwitchState::OFF);
    }
};
// State handler factory
class StateHandlerFactory : public IStateHandlerFactory {
public:
    std::map<SwitchState, IStateHandler*> MapOfStateAndHandler;

    StateHandlerFactory() {
        std::cout << "StateHandlerFactory: Initializing" << std::endl;
        // Initialize the map with handlers
        MapOfStateAndHandler[SwitchState::OFF] = new OffStateHandler();
        MapOfStateAndHandler[SwitchState::LOW] = new LowStateHandler();
        MapOfStateAndHandler[SwitchState::MODERATE] = new ModerateStateHandler();
        MapOfStateAndHandler[SwitchState::HIGH] = new HighStateHandler();
    }

    IStateHandler* create(SwitchState state) override {
        std::cout << "StateHandlerFactory: Creating handler for state " << static_cast<int>(state) << std::endl;
        return MapOfStateAndHandler[state];
    }

    ~StateHandlerFactory() {
        std::cout << "StateHandlerFactory: Cleaning up handlers" << std::endl;
        // Clean up dynamically allocated handlers
        for (auto& pair : MapOfStateAndHandler) {
            delete pair.second;
        }
    }
};

// Digital switch class implementing IContext
class DigitalSwitch : public IContext {
private:
    SwitchState currentState;
    IStateHandler* currentStateHandler;
    IStateHandlerFactory* stateHandlerFactory;

public:
    DigitalSwitch(SwitchState initState, IStateHandlerFactory* factory) 
        : currentState(initState), stateHandlerFactory(factory) {
        std::cout << "DigitalSwitch: Initializing with state " << static_cast<int>(initState) << std::endl;
        currentStateHandler = stateHandlerFactory->create(currentState);
    }

    SwitchState getState() {
        std::cout << "DigitalSwitch: Getting current state " << static_cast<int>(currentState) << std::endl;
        return currentState;
    }

    void setState(SwitchState nextState) override {
        std::cout << "DigitalSwitch: Setting state from " << static_cast<int>(currentState) 
                  << " to " << static_cast<int>(nextState) << std::endl;
        currentState = nextState;
        currentStateHandler = stateHandlerFactory->create(currentState);
    }

    void press() {
        std::cout << "DigitalSwitch: Pressing switch in state " << static_cast<int>(currentState) << std::endl;
        currentStateHandler->handleState(this);
    }
};
int main() {
    std::cout << "Main: Creating StateHandlerFactory" << std::endl;
    StateHandlerFactory factory;
    
    std::cout << "Main: Creating DigitalSwitch with initial state OFF" << std::endl;
    DigitalSwitch mySwitch(SwitchState::OFF, &factory);

    mySwitch.press(); // Off -> Low
    mySwitch.press(); // Low -> Moderate
    mySwitch.press(); // Moderate -> High
    mySwitch.press(); // High -> Off

    return 0;
}
