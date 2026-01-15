#include <gtest/gtest.h>
#include "motor_control.hpp"
#include "safety_manager.hpp"

class MotorControlTest : public ::testing::Test {
protected:
    MotorControl* motor;
    SafetyManager* safety;

    void SetUp() override {
        // Assume a maximum speed that is considered safe in tests e.g., 200
        motor = new MotorControl(200);
        safety = new SafetyManager();
    }

    void TearDown() override {
        // Clean up resources
        delete motor;
        delete safety;
    }
};

TEST_F(MotorControlTest, TestNormalOperation) {
    motor->setSpeed(100);
    EXPECT_EQ(motor->getSpeed(), 100);
    // Mocking safety check always true for normal operation test
    EXPECT_TRUE(safety->isSafeToOperate());
}

TEST_F(MotorControlTest, TestOverSpeed) {
    motor->setSpeed(250); // Exceeds max_speed
    EXPECT_EQ(motor->getSpeed(), 0); // System should halt motor due to out-of-range safety
}

TEST_F(MotorControlTest, TestInvalidSpeed) {
    EXPECT_THROW(motor->setSpeed(-10), std::out_of_range); // Negative speed should throw
}

TEST_F(MotorControlTest, TestSpeedRegulation) {
    motor->setSpeed(150);
    for (int i = 0; i < 10; ++i) {
        // Add inertia simulation with actual PID control call
        motor->controlLoop();
        EXPECT_LE(motor->getSpeed(), 155);
        EXPECT_GE(motor->getSpeed(), 145);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate control loop delay
    }
}

TEST_F(MotorControlTest, TestSafetyShutdown) {
    safety->triggerFault(); // Simulate a fault in safety check
    EXPECT_EQ(motor->getSpeed(), 0); // Motor should stop due to safety shutdown
    EXPECT_FALSE(safety->isSafeToOperate()); // Safety should indicate an unsafe state
}

TEST_F(MotorControlTest, TestCommandLineInterface) {
    std::string output;
    output = motor->command("run --start");
    EXPECT_EQ(output, "Motor started with safety checks.");

    output = motor->command("status");
    EXPECT_NE(output.find("Motor status:"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
