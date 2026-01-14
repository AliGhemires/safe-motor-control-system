#include <iostream>
#include <string>
#include <iomanip>
#include "cli_interface.hpp"

CLIInterface::CLIInterface(MotorControl& motorControl)
    : motorControl(motorControl) {}

void CLIInterface::showHelp() {
    std::cout << "Available commands:\n";
    std::cout << "run --start : Start motor with safety checks enabled.\n";
    std::cout << "status : Display current motor status and operational metrics.\n";
    std::cout << "test --all : Execute all defined safety tests on the motor system.\n";
    std::cout << "exit : Exit the command line interface.\n";
    std::cout << "help : Show available commands.\n";
}

void CLIInterface::runCommand(const std::string& command) {
    if (command == "run --start") {
        if (motorControl.isRunning()) {
            std::cout << "Motor is already running.\n";
        } else {
            motorControl.start();
            std::cout << "Motor started with safety checks enabled.\n";
        }
    } else if (command == "status") {
        auto status = motorControl.getStatus();
        std::cout << "Motor Status: " << status << std::endl;
    } else if (command == "test --all") {
        bool allTestsPassed = motorControl.runAllTests();
        std::cout << (allTestsPassed ? "All tests passed successfully." : "Some tests failed.") << std::endl;
    } else if (command == "help") {
        showHelp();
    } else {
        std::cout << "Unknown command. Type 'help' for available commands.\n";
    }
}

void CLIInterface::start() {
    std::string input;
    showHelp();
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, input);
        if (input == "exit") {
            std::cout << "Exiting CLI.\n";
            break;
        }
        runCommand(input);
    }
}
