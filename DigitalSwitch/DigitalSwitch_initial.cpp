#include <iostream>
 
class DigitalSwitch {
private:
    enum State { OFF, LOW, MODERATE, HIGH }; // State enumeration
 
    State currentState; // Current state of the switch
 
public:
    DigitalSwitch() : currentState(OFF) {} // Constructor initializes state to OFF
 
    void press(); // Method to simulate pressing the switch
};
 
void DigitalSwitch::press() {
    // Update the state based on the current state
    switch (currentState) {
        case OFF:
            std::cout << "Switching from OFF to LOW" << std::endl;
            currentState = LOW;
            break;
        case LOW:
            std::cout << "Switching from LOW to MODERATE" << std::endl;
            currentState = MODERATE;
            break;
        case MODERATE:
            std::cout << "Switching from MODERATE to HIGH" << std::endl;
            currentState = HIGH;
            break;
        case HIGH:
            std::cout << "Switching from HIGH to OFF" << std::endl;
            currentState = OFF;
            break;
        default:
            std::cerr << "Invalid state" << std::endl;
            break;
    }
}
 
int main() {
    DigitalSwitch dsobj;
 
    // Simulate pressing the switch multiple times
    dsobj.press();
    dsobj.press();
    dsobj.press();
    dsobj.press();
 
    return 0;
}
