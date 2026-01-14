#ifndef SAFETY_MANAGER_HPP
#define SAFETY_MANAGER_HPP

#include <iostream>
#include <stdexcept>

class SafetyManager {
public:
    SafetyManager(); // Constructor

    /** 
     * Updates the current sensor readings and evaluates the safety state.
     * @param currentLoad Current motor load in Amps.
     * @param temperature Current temperature in Celsius.
     */
    void updateSensors(double currentLoad, double temperature);

    /**
     * Checks for potential faults based on updated sensor readings.
     * Determines whether a shutdown is required.
     */
    void checkForFaults();

    /**
     * Immediately initiates shutdown procedures.
     */
    void initiateShutdown();

    /**
     * Returns the current shutdown state.
     * @return True if shutdown has been initiated, otherwise false.
     */
    bool isShuttingDown() const;

private:
    double currentLoad; // Current sensor reading
    double temperature; // Temperature sensor reading
    bool shuttingDown;  // Flag to indicate if shutdown is initiated

    /**
     * Logs an error message related to safety events.
     * @param errorMessage Description of the safety condition.
     */
    void logError(const std::string &errorMessage);

    /**
     * Validates sensor readings, ensuring appropriate values.
     * Throws an exception for invalid sensor data.
     */
    void validateSensorReadings() const;
};

#endif // SAFETY_MANAGER_HPP
