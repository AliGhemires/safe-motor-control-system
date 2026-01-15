#include <gtest/gtest.h>
#include "motor_control.hpp"
#include "safety_manager.hpp"

class MotorControlTest : public ::testing::Test {
protected:
    MotorControl motor_control;
    SafetyManager safety_manager;

    virtual void SetUp() {
        // Setup necessary preconditions for the tests
        motor_control.initialize();
        safety_manager.initialize();
    }

    virtual void TearDown() {
        // Cleanup if necessary
        motor_control.shutdown();
    }
};

TEST_F(MotorControlTest, TestNormalOperation) {
    motor_control.setSpeed(0.5);
    EXPECT_EQ(motor_control.getCurrentSpeed(), 0.5);
}

TEST_F(MotorControlTest, TestOvercurrentDetection) {
    // Simulate an overcurrent situation
    motor_control.setSpeed(1.5); // Assume this exceeds limits
    safety_manager.checkForFaults();
    EXPECT_TRUE(safety_manager.isFaultDetected());
}

TEST_F(MotorControlTest, TestSpeedRegulation) {
    motor_control.setSpeed(0.3);
    motor_control.update(); // Update the motor control system
    EXPECT_NEAR(motor_control.getCurrentSpeed(), 0.3, 0.01);
}

TEST_F(MotorControlTest, TestFaultRecovery) {
    motor_control.setSpeed(1.5);
    safety_manager.checkForFaults();
    if (safety_manager.isFaultDetected()) {
        motor_control.recoverFromFault();
    }
    EXPECT_EQ(motor_control.getCurrentSpeed(), 0.0);
}

TEST_F(MotorControlTest, TestCLIIntegration) {
    // Assuming CLI can be tested via interface
    std::string output = motor_control.runCLI("status");
    EXPECT_THAT(output, testing::HasSubstr("current speed"));
}

TEST_F(MotorControlTest, TestBoundarySpeedValueHandling) {
    motor_control.setSpeed(-0.1); // Test lower boundary
    EXPECT_GE(motor_control.getCurrentSpeed(), 0.0); // Minimum speed is 0
    motor_control.setSpeed(1.1); // Test upper boundary assuming max speed is 1
    EXPECT_LE(motor_control.getCurrentSpeed(), 1.0); // Maximum speed is 1
}

TEST_F(MotorControlTest, TestGradualAcceleration) {
    double initial_speed = 0.0;
    double target_speed = 1.0;
    double increment = 0.1; // Simulate gradual acceleration
    while (initial_speed < target_speed) {
        initial_speed += increment;
        motor_control.setSpeed(initial_speed);
        motor_control.update();
        EXPECT_NEAR(motor_control.getCurrentSpeed(), initial_speed, 0.01);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
