#include "motor_control.hpp"
#include <iostream>
#include <chrono>
#include <thread>

// PID control variables
double kp = 1.0; // proportional gain
double ki = 0.1; // integral gain
double kd = 0.05; // derivative gain
double setpoint = 0.0; // desired speed
double lastError = 0.0; // last error signal
double integral = 0.0; // integral error

// Motor speed variable
double motorSpeed = 0.0;

// Edge case checks
constexpr double MAX_SPEED = 100.0; // Max motor speed
constexpr double MIN_SPEED = 0.0; // Min motor speed

// Function to initialize the motor control system
void MotorControl::initMotor() {
    motorSpeed = 0.0;
    lastError = 0.0;
    integral = 0.0;
    std::cout << "Motor system initialized. Speed set to " << motorSpeed << std::endl;
}

// Function to set the desired motor speed
void MotorControl::setSpeed(double speed) {
    // Validate and clamp speed within allowed range
    if (speed > MAX_SPEED || speed < MIN_SPEED) {
        std::cout << "Error: Desired speed " << speed << " out of range. Setting to closest boundary." << std::endl;
        setpoint = (speed > MAX_SPEED) ? MAX_SPEED : MIN_SPEED;
    } else {
        setpoint = speed;
    }
    std::cout << "Desired speed set to: " << setpoint << std::endl;
}

// Function to simulate motor control loop
void MotorControl::controlLoop() {
    while(true) {
        // Simulate reading current speed from the motor
        double currentSpeed = readCurrentSpeed();
        // Calculate error
        double error = setpoint - currentSpeed;
        // Calculate integral and derivative
        integral += error;
        double derivative = error - lastError;
        // Calculate control output
        double output = kp * error + ki * integral + kd * derivative;
        
        // Simulate applying output to motor and limit speed changes
        motorSpeed = std::clamp(motorSpeed + output, MIN_SPEED, MAX_SPEED);
        
        // Edge case for when integral component becomes too large
        integral = std::clamp(integral, -MAX_SPEED, MAX_SPEED);

        // Update last error
        lastError = error;
        // Output current state
        std::cout << "Current Speed: " << currentSpeed << " Motor Speed: " << motorSpeed << std::endl;

        // Simulate delay for control loop timing
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Function to read current motor speed (stub implementation)
double MotorControl::readCurrentSpeed() {
    // In a real implementation, this function would read from sensors
    // Here we simulate with the motorSpeed variable
    return motorSpeed;
}
