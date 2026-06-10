#include "esp32ModbusStatistics.h"
#include "Arduino.h"

esp32ModbusStatistics::Statistics::Statistics() {}

bool esp32ModbusStatistics::Statistics::begin()
{
    _startTime = millis();
    return true;
}

void esp32ModbusStatistics::Statistics::onPacketSent()
{
    _totalPackets++;
}

void esp32ModbusStatistics::Statistics::onSuccess()
{
    _successfulPackets++;
}

void esp32ModbusStatistics::Statistics::onQueueOverflow()
{
    _queueOverflow++;
    _totalErrors++;
}

void esp32ModbusStatistics::Statistics::onError(esp32Modbus::Error code)
{
    switch (code)
    {
    case esp32Modbus::Error::ILLEGAL_FUNCTION:
        onIllegalFunction();
        break;
    case esp32Modbus::Error::ILLEGAL_DATA_ADDRESS:
        onIllegalDataAddress();
        break;
    case esp32Modbus::Error::ILLEGAL_DATA_VALUE:
        onIllegalDataValue();
        break;
    case esp32Modbus::Error::SERVER_DEVICE_FAILURE:
        onServerDeviceFailure();
        break;
    case esp32Modbus::Error::ACKNOWLEDGE:
        onAcknowledge();
        break;
    case esp32Modbus::Error::SERVER_DEVICE_BUSY:
        onServerDeviceBusy();
        break;
    case esp32Modbus::Error::NEGATIVE_ACKNOWLEDGE:
        onNegativeAcknowledge();
        break;
    case esp32Modbus::Error::MEMORY_PARITY_ERROR:
        onMemoryParityError();
        break;
    case esp32Modbus::Error::TIMEOUT:
        onTimeout();
        break;
    case esp32Modbus::Error::INVALID_SLAVE:
        onInvalidSlave();
        break;
    case esp32Modbus::Error::INVALID_FUNCTION:
        onInvalidFunction();
        break;
    case esp32Modbus::Error::CRC_ERROR:
        onCRCError();
        break;
    case esp32Modbus::Error::COMM_ERROR:
        onCommError();
        break;
    }
}

void esp32ModbusStatistics::Statistics::onIllegalFunction()
{
    _illegalFunctions++;
    _totalErrors++;
}

void esp32ModbusStatistics::Statistics::onIllegalDataAddress()
{
    _illegalDataAddresses++;
    _totalErrors++;
}

void esp32ModbusStatistics::Statistics::onIllegalDataValue()
{
    _illegalDataValues++;
    _totalErrors++;
}

void esp32ModbusStatistics::Statistics::onServerDeviceFailure()
{
    _serverDeviceFailures++;
    _totalErrors++;
}

void esp32ModbusStatistics::Statistics::onAcknowledge()
{
    _acknowledges++;
    _totalErrors++;
}

void esp32ModbusStatistics::Statistics::onServerDeviceBusy()
{
    _serverDeviceBusyErrors++;
    _totalErrors++;
}

void esp32ModbusStatistics::Statistics::onNegativeAcknowledge()
{
    _negativeAcknowledges++;
    _totalErrors++;
}

void esp32ModbusStatistics::Statistics::onMemoryParityError()
{
    _memoryParityErrors++;
    _totalErrors++;
}

void esp32ModbusStatistics::Statistics::onTimeout()
{
    _timeouts++;
    _totalErrors++;
}

void esp32ModbusStatistics::Statistics::onInvalidSlave()
{
    _invalidSlaves++;
    _totalErrors++;
}

void esp32ModbusStatistics::Statistics::onInvalidFunction()
{
    _invalidFunctions++;
    _totalErrors++;
}

void esp32ModbusStatistics::Statistics::onCRCError()
{
    _crcErrors++;
    _totalErrors++;
}

void esp32ModbusStatistics::Statistics::onCommError()
{
    _commErrors++;
    _totalErrors++;
}

float esp32ModbusStatistics::Statistics::getRunningTime()
{
    return (millis() - _startTime) / 1000.0f;
};

uint32_t esp32ModbusStatistics::Statistics::getTotalPacketSent()
{
    return _totalPackets;
}

uint32_t esp32ModbusStatistics::Statistics::getSuccessfulPackets()
{
    return _successfulPackets;
}

uint32_t esp32ModbusStatistics::Statistics::getTotalErrors()
{
    return _totalErrors;
}

float esp32ModbusStatistics::Statistics::getPacketsPerSecond()
{
    float elapsedSecs = getRunningTime();
    if (elapsedSecs == 0)
    {
        return 0.0f;
    }
    return getTotalPacketSent() / elapsedSecs;
}

float esp32ModbusStatistics::Statistics::getErrorRate()
{
    uint32_t totPackets = getTotalPacketSent();
    if (totPackets == 0)
    {
        return 0.0f;
    }
    return (float)getTotalErrors() / totPackets;
}

float esp32ModbusStatistics::Statistics::getSuccessRate()
{
    uint32_t successPackets = getSuccessfulPackets();
    uint32_t totalPacketsSent = getTotalPacketSent();
    if (totalPacketsSent == 0)
    {
        return 0.0f;
    }
    return (float)successPackets / totalPacketsSent;
}

uint32_t esp32ModbusStatistics::Statistics::getQueueOverflows()
{
    return _queueOverflow;
}

uint32_t esp32ModbusStatistics::Statistics::getErrorCount(esp32Modbus::Error code)
{
    switch (code)
    {
    case esp32Modbus::Error::ILLEGAL_FUNCTION:
        return getIllegalFunctionErrors();
        break;
    case esp32Modbus::Error::ILLEGAL_DATA_ADDRESS:
        return getIllegalDataAddressErrors();
        break;
    case esp32Modbus::Error::ILLEGAL_DATA_VALUE:
        return getIllegalDataValueErrors();
        break;
    case esp32Modbus::Error::SERVER_DEVICE_FAILURE:
        return getServerDeviceFailures();
        break;
    case esp32Modbus::Error::ACKNOWLEDGE:
        return getAcknowledges();
        break;
    case esp32Modbus::Error::SERVER_DEVICE_BUSY:
        return getServerDeviceBusyErrors();
        break;
    case esp32Modbus::Error::NEGATIVE_ACKNOWLEDGE:
        return getNegativeAcknowledges();
        break;
    case esp32Modbus::Error::MEMORY_PARITY_ERROR:
        return getMemoryParityErrors();
        break;
    case esp32Modbus::Error::TIMEOUT:
        return getTimeouts();
        break;
    case esp32Modbus::Error::INVALID_SLAVE:
        return getInvalidSlaveErrors();
        break;
    case esp32Modbus::Error::INVALID_FUNCTION:
        return getInvalidFunctionErrors();
        break;
    case esp32Modbus::Error::CRC_ERROR:
        return getCRCErrors();
        break;
    case esp32Modbus::Error::COMM_ERROR:
        return getCommErrors();
        break;
    default:
        return 0;
        break;
    }
}

uint32_t esp32ModbusStatistics::Statistics::getIllegalFunctionErrors()
{
    return _illegalFunctions;
}

uint32_t esp32ModbusStatistics::Statistics::getIllegalDataAddressErrors()
{
    return _illegalDataAddresses;
}

uint32_t esp32ModbusStatistics::Statistics::getIllegalDataValueErrors()
{
    return _illegalDataValues;
}

uint32_t esp32ModbusStatistics::Statistics::getServerDeviceFailures()
{
    return _serverDeviceFailures;
}

uint32_t esp32ModbusStatistics::Statistics::getAcknowledges()
{
    return _acknowledges;
}

uint32_t esp32ModbusStatistics::Statistics::getServerDeviceBusyErrors()
{
    return _serverDeviceBusyErrors;
}

uint32_t esp32ModbusStatistics::Statistics::getNegativeAcknowledges()
{
    return _negativeAcknowledges;
}

uint32_t esp32ModbusStatistics::Statistics::getMemoryParityErrors()
{
    return _memoryParityErrors;
}

uint32_t esp32ModbusStatistics::Statistics::getTimeouts()
{
    return _timeouts;
}

uint32_t esp32ModbusStatistics::Statistics::getInvalidSlaveErrors()
{
    return _invalidSlaves;
}

uint32_t esp32ModbusStatistics::Statistics::getInvalidFunctionErrors()
{
    return _invalidFunctions;
}

uint32_t esp32ModbusStatistics::Statistics::getCRCErrors()
{
    return _crcErrors;
}

uint32_t esp32ModbusStatistics::Statistics::getCommErrors()
{
    return _commErrors;
}

void esp32ModbusStatistics::Statistics::reset()
{
    _startTime = millis();
    _totalPackets = 0;
    _totalErrors = 0;
    _queueOverflow = 0;
    _illegalFunctions = 0;
    _illegalDataAddresses = 0;
    _illegalDataValues = 0;
    _serverDeviceFailures = 0;
    _acknowledges = 0;
    _serverDeviceBusyErrors = 0;
    _negativeAcknowledges = 0;
    _memoryParityErrors = 0;
    _timeouts = 0;
    _invalidSlaves = 0;
    _invalidFunctions = 0;
    _crcErrors = 0;
    _commErrors = 0;
    _successfulPackets = 0;
}