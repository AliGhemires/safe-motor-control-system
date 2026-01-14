#include <gtest/gtest.h>
#include "cli_interface.hpp"
#include "motor_control.hpp"

// Test Suite for CLI Interface
class CLITest : public ::testing::Test {
protected:
    CLIInterface *cli;
    MotorControl motorControl;

    void SetUp() override {
        // Initialize the CLI interface or any necessary setup
        cli = new CLIInterface(motorControl);
    }

    void TearDown() override {
        // Cleanup after each test if necessary
        delete cli;
    }
};

// Test for starting the motor when it's already running
TEST_F(CLITest, StartMotorAlreadyRunning) {
    std::string command = "run --start";
    ASSERT_NO_THROW(cli->runCommand(command)); // Start the motor
    ASSERT_NO_THROW(cli->runCommand(command)); // Attempt to start again
    ASSERT_EQ(motorControl.isRunning(), true);
}

// Test for starting the motor
TEST_F(CLITest, StartMotorWithSafetyChecks) {
    std::string command = "run --start";
    ASSERT_NO_THROW(cli->runCommand(command));
    ASSERT_EQ(motorControl.isRunning(), true);
}

// Test for checking status
TEST_F(CLITest, CheckMotorStatus) {
    cli->runCommand("run --start");  // Ensure motor is started
    std::string command = "status";
    testing::internal::CaptureStdout();
    cli->runCommand(command);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_NE(output.find("Motor Status:"), std::string::npos);
}

// Test for executing all tests
TEST_F(CLITest, TestAllSafetyChecks) {
    std::string command = "test --all";
    ASSERT_NO_THROW(cli->runCommand(command));
    ASSERT_TRUE(motorControl.getTestResults()); // Expecting all tests to pass
}

// Test for invalid commands
TEST_F(CLITest, InvalidCommand) {
    std::string command = "invalid --command";
    ASSERT_THROW(cli->runCommand(command), std::invalid_argument);
}

// Test that help displays the correct commands
TEST_F(CLITest, ShowHelpCommand) {
    std::string command = "help";
    testing::internal::CaptureStdout();
    cli->runCommand(command);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_NE(output.find("Available commands:"), std::string::npos);
    ASSERT_NE(output.find("status : Display current motor status"), std::string::npos);
}

// Main function for running all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
