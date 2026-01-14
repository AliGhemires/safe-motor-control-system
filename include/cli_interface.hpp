#ifndef CLI_INTERFACE_HPP
#define CLI_INTERFACE_HPP

#include <string>
#include <iostream>

class CLIInterface {
public:
    CLIInterface();
    // Function to run any command provided by the user
    void runCommand(const std::string& command);
    
    // Function to display the current motor status
    void displayStatus();
    
    // Function to safely start the motor after performing safety checks
    void startMotor();
    
    // Function to test all safety mechanisms
    void testAll();
    
private:
    // Processes the command provided to the CLI
    void processCommand(const std::string& command);
};

#endif // CLI_INTERFACE_HPP
