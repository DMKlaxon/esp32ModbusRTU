#include "esp32ModbusStatistics.h"

esp32ModbusStatistics::Statistics::Statistics() : _status(ModbusStatus::OK) {}

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
    _updateStatus(true);
}

void esp32ModbusStatistics::Statistics::onModbusError(ModbusError code)
{
    _updateStatus(false);
    switch (code)
    {
    case ModbusError::ILLEGAL_FUNCTION:
        _illegalFunctions++;
        break;
    case ModbusError::ILLEGAL_DATA_ADDRESS:
        _illegalDataAddresses++;
        break;
    case ModbusError::ILLEGAL_DATA_VALUE:
        _illegalDataValues++;
        break;
    case ModbusError::SERVER_DEVICE_FAILURE:
        _serverDeviceFailures++;
        break;
    case ModbusError::ACKNOWLEDGE:
        _acks++;
        break;
    case ModbusError::SERVER_DEVICE_BUSY:
        _serverDeviceBusyErrors++;
        break;
    case ModbusError::NEGATIVE_ACKNOWLEDGE:
        _negativeAcks++;
        break;
    case ModbusError::MEMORY_PARITY_ERROR:
        _memoryParityErrors++;
        break;
    case ModbusError::TIMEOUT:
        _timeouts++;
        break;
    case ModbusError::INVALID_SLAVE:
        _invalidSlaves++;
        break;
    case ModbusError::INVALID_FUNCTION:
        _invalidFunctions++;
        break;
    case ModbusError::CRC_ERROR:
        _crcErrors++;
        break;
    case ModbusError::COMM_ERROR:
        _commErrors++;
        break;
    case ModbusError::QUEUE_OVERFLOW:
        _queueOverflow++;
    default:
        break;
    }
}

void esp32ModbusStatistics::Statistics::onEsp32ModbusError(esp32Modbus::Error code)
{
    switch (code)
    {
    case esp32Modbus::Error::ILLEGAL_FUNCTION:
        onModbusError(ModbusError::ILLEGAL_FUNCTION);
        break;
    case esp32Modbus::Error::ILLEGAL_DATA_ADDRESS:
        onModbusError(ModbusError::ILLEGAL_DATA_ADDRESS);
        break;
    case esp32Modbus::Error::ILLEGAL_DATA_VALUE:
        onModbusError(ModbusError::ILLEGAL_DATA_VALUE);
        break;
    case esp32Modbus::Error::SERVER_DEVICE_FAILURE:
        onModbusError(ModbusError::SERVER_DEVICE_FAILURE);
        break;
    case esp32Modbus::Error::ACKNOWLEDGE:
        onModbusError(ModbusError::ACKNOWLEDGE);
        break;
    case esp32Modbus::Error::SERVER_DEVICE_BUSY:
        onModbusError(ModbusError::SERVER_DEVICE_BUSY);
        break;
    case esp32Modbus::Error::NEGATIVE_ACKNOWLEDGE:
        onModbusError(ModbusError::NEGATIVE_ACKNOWLEDGE);
        break;
    case esp32Modbus::Error::MEMORY_PARITY_ERROR:
        onModbusError(ModbusError::MEMORY_PARITY_ERROR);
        break;
    case esp32Modbus::Error::TIMEOUT:
        onModbusError(ModbusError::TIMEOUT);
        break;
    case esp32Modbus::Error::INVALID_SLAVE:
        onModbusError(ModbusError::INVALID_SLAVE);
        break;
    case esp32Modbus::Error::INVALID_FUNCTION:
        onModbusError(ModbusError::INVALID_FUNCTION);
        break;
    case esp32Modbus::Error::CRC_ERROR:
        onModbusError(ModbusError::CRC_ERROR);
        break;
    case esp32Modbus::Error::COMM_ERROR:
        onModbusError(ModbusError::COMM_ERROR);
        break;
    }
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
    return _totalSuccessfulPackets;
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
        return getAcks();
        break;
    case esp32Modbus::Error::SERVER_DEVICE_BUSY:
        return getServerDeviceBusyErrors();
        break;
    case esp32Modbus::Error::NEGATIVE_ACKNOWLEDGE:
        return getNegativeAcks();
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

uint32_t esp32ModbusStatistics::Statistics::getAcks()
{
    return _acks;
}

uint32_t esp32ModbusStatistics::Statistics::getServerDeviceBusyErrors()
{
    return _serverDeviceBusyErrors;
}

uint32_t esp32ModbusStatistics::Statistics::getNegativeAcks()
{
    return _negativeAcks;
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

uint16_t esp32ModbusStatistics::Statistics::getErrorCounter()
{
    return _errorCounter;
}

esp32ModbusStatistics::ModbusStatus esp32ModbusStatistics::Statistics::getStatus()
{
    return _status;
}

String esp32ModbusStatistics::Statistics::printStatus()
{
    switch (_status)
    {
    case esp32ModbusStatistics::ModbusStatus::OK:
        return "OK";
        break;
    case esp32ModbusStatistics::ModbusStatus::WARNING:
        return "WARNING";
        break;
    case esp32ModbusStatistics::ModbusStatus::ALARM:
        return "ALARM";
        break;
    }
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
    _acks = 0;
    _serverDeviceBusyErrors = 0;
    _negativeAcks = 0;
    _memoryParityErrors = 0;
    _timeouts = 0;
    _invalidSlaves = 0;
    _invalidFunctions = 0;
    _crcErrors = 0;
    _commErrors = 0;
    _totalSuccessfulPackets = 0;
    _errorCounter = 0;
    _status = esp32ModbusStatistics::ModbusStatus::OK;
}

void esp32ModbusStatistics::Statistics::_updateStatus(bool sendSuccess)
{
    if (sendSuccess)
    {
        _totalSuccessfulPackets++;
        if (_errorCounter > 0)
        {
            _errorCounter--;
        }
    }
    else
    {
        _totalErrors++;
        _errorCounter += ERROR_WEIGHT;
    }

    if (_errorCounter < WARNING_THRESHOLD)
    {
        _status = esp32ModbusStatistics::ModbusStatus::OK;
    }
    else if (_errorCounter < ALARM_THRESHOLD)
    {
        _status = esp32ModbusStatistics::ModbusStatus::WARNING;
    }
    else
    {
        _status = esp32ModbusStatistics::ModbusStatus::ALARM;
    }
}