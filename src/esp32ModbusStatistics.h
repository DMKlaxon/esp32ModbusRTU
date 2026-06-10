
#pragma once
#include <stdint.h>
#include "esp32ModbusTypeDefs.h"

namespace esp32ModbusStatistics
{
    class Statistics
    {
    public:
        // constructor
        Statistics();

        bool begin();

        // setters
        void onPacketSent();
        void onSuccess(); // Valid response is received

        // error setters
        void onQueueOverflow();

        /**
         * @brief Increments the counter associated with ther error specified by @ref code
         * @param code The error code whose counter will be incremented
         */
        void onError(esp32Modbus::Error code);
        void onIllegalFunction();
        void onIllegalDataAddress();
        void onIllegalDataValue();
        void onServerDeviceFailure();
        void onAcknowledge();
        void onServerDeviceBusy();
        void onNegativeAcknowledge();
        void onMemoryParityError();
        void onTimeout();
        void onInvalidSlave();
        void onInvalidFunction();
        void onCRCError();
        void onCommError();

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
        uint32_t getAcknowledges();
        uint32_t getServerDeviceBusyErrors();
        uint32_t getNegativeAcknowledges();
        uint32_t getMemoryParityErrors();
        uint32_t getTimeouts();

        uint32_t getInvalidSlaveErrors();
        uint32_t getInvalidFunctionErrors();
        uint32_t getCRCErrors();
        uint32_t getCommErrors();

        // reset all counts and restart run time
        void reset();

    private:
        unsigned long _startTime;

        uint32_t _totalPackets = 0;

        // Error counters
        uint32_t _totalErrors = 0;
        uint32_t _queueOverflow = 0; // packets rejected due to queue being full
        uint32_t _illegalFunctions = 0;
        uint32_t _illegalDataAddresses = 0;
        uint32_t _illegalDataValues = 0;
        uint32_t _serverDeviceFailures = 0;
        uint32_t _acknowledges = 0;
        uint32_t _serverDeviceBusyErrors = 0;
        uint32_t _negativeAcknowledges = 0;
        uint32_t _memoryParityErrors = 0;
        uint32_t _timeouts = 0;
        uint32_t _invalidSlaves = 0;
        uint32_t _invalidFunctions = 0;
        uint32_t _crcErrors = 0;
        uint32_t _commErrors = 0;

        uint32_t _successfulPackets = 0;
    };
}