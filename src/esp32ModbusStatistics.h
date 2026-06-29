
#pragma once
#include <stdint.h>
#include <HardwareSerial.h>
#include "Arduino.h"
#include "esp32ModbusTypeDefs.h"

#define ERROR_WEIGHT 10
#define WARNING_THRESHOLD 50
#define ALARM_THRESHOLD 100

namespace esp32ModbusStatistics
{
    enum class ModbusStatus
    {
        OK,
        WARNING,
        ALARM
    };

    enum class ModbusError
    {
        ILLEGAL_FUNCTION,
        ILLEGAL_DATA_ADDRESS,
        ILLEGAL_DATA_VALUE,
        SERVER_DEVICE_FAILURE,
        ACKNOWLEDGE,
        SERVER_DEVICE_BUSY,
        NEGATIVE_ACKNOWLEDGE,
        MEMORY_PARITY_ERROR,
        TIMEOUT,
        INVALID_SLAVE,
        INVALID_FUNCTION,
        CRC_ERROR,
        COMM_ERROR,
        QUEUE_OVERFLOW
    };

    class Statistics
    {
    public:
        // constructor
        Statistics();

        bool begin();

        // setters
        void onPacketSent();
        void onSuccess(); // Valid response is received

        // error setter
        void onModbusError(ModbusError code);

        /**
         * @brief Increments the counter associated with ther error specified by @ref code (this is done by calling the corresponding helper function)
         * @note OBSERVE: this function can only update the errors associated with @ref esp32Modbus::Error members
         * @param code The error code whose counter will be incremented
         */
        void onEsp32ModbusError(esp32Modbus::Error code);

        // getters
        float getRunningTime(); // in seconds
        uint32_t getTotalPacketSent();
        uint32_t getSuccessfulPackets();
        uint32_t getTotalErrors();

        /**
         * @brief Mean packet transmission rate over the execution period (starting from @ref begin())
         * @param msg The message buffer
         * @return Packets per seconds (float)
         */
        float getPacketsPerSecond();
        float getErrorRate();
        float getSuccessRate();

        uint32_t getQueueOverflows();
        uint32_t getErrorCount(esp32Modbus::Error code);
        uint32_t getIllegalFunctionErrors();
        uint32_t getIllegalDataAddressErrors();
        uint32_t getIllegalDataValueErrors();
        uint32_t getServerDeviceFailures();
        uint32_t getAcks();
        uint32_t getServerDeviceBusyErrors();
        uint32_t getNegativeAcks();
        uint32_t getMemoryParityErrors();
        uint32_t getTimeouts();

        uint32_t getInvalidSlaveErrors();
        uint32_t getInvalidFunctionErrors();
        uint32_t getCRCErrors();
        uint32_t getCommErrors();

        uint16_t getErrorCounter();

        ModbusStatus getStatus();
        String printStatus();


        // reset all counts and restart run time
        void reset();

    private:
        void _updateStatus(bool sendSuccess);

        unsigned long _startTime;

        uint32_t _totalPackets = 0;

        // Error counters
        uint32_t _totalErrors = 0;
        uint32_t _queueOverflow = 0; // packets rejected due to queue being full
        uint32_t _illegalFunctions = 0;
        uint32_t _illegalDataAddresses = 0;
        uint32_t _illegalDataValues = 0;
        uint32_t _serverDeviceFailures = 0;
        uint32_t _acks = 0;
        uint32_t _serverDeviceBusyErrors = 0;
        uint32_t _negativeAcks = 0;
        uint32_t _memoryParityErrors = 0;
        uint32_t _timeouts = 0;
        uint32_t _invalidSlaves = 0;
        uint32_t _invalidFunctions = 0;
        uint32_t _crcErrors = 0;
        uint32_t _commErrors = 0;

        uint32_t _totalSuccessfulPackets = 0;

        uint16_t _errorCounter = 0;

        ModbusStatus _status;
    };

}