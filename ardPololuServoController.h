#pragma once
#include "ardPololuServoControllerDefines.h"
#include <Arduino.h>
//#include <SoftwareSerial.h>

/*
 * https://www.pololu.com/docs/0J40/5.e
 *
 * Compact protocol
 * commandbyte channel_number low_bits high_bits
 */

template<class SerialType>
class ardPololuServoController
{
public:
    static String getVersionString()
    {
        return 
            String(ARDPOLOLUSERVOCONTROLLER_MAJOR_VERSION) +
            String(ARDPOLOLUSERVOCONTROLLER_MINOR_VERSION) +
            String(ARDPOLOLUSERVOCONTROLLER_PATCH_VERSION);
    }
    ardPololuServoController(SerialType* serialPtr, unsigned int baudRate = 9600)
    {
        _serialPtr = serialPtr;
        _serialPtr->begin(baudRate);
    }

    ardPololuServoController* setPosition(unsigned short int servo, unsigned short int position = 0)
    {
         //Maestro uses quarter microseconds so convert accordingly
        position = position * 4;
        // command number
        _serialPtr->write(0x84);
        // servo number
        _serialPtr->write(servo);
        // target low bits
        _serialPtr->write(position & 0x7F);
        // target high bits
        _serialPtr->write((position >> 7) & 0x7F);  
        return this;
    }

    ardPololuServoController* setSpeed(unsigned short int servo, unsigned short int speed = 0)
    {
        // command number 
        _serialPtr->write(0x87);
        // servo number
        _serialPtr->write(servo);
        // target low bits
        _serialPtr->write(speed & 0x7F);
        // target high bits
        _serialPtr->write((speed >> 7) & 0x7F);
        return this;
    }

    ardPololuServoController* setAcceleration(unsigned short int servo, unsigned short int acceleration = 0)
    {
        // command number
        _serialPtr->write(0x89);
        // servo number
        _serialPtr->write(servo);
        // target low bits
        _serialPtr->write(acceleration & 0x7F);
        // target high bits
        _serialPtr->write((acceleration >> 7) & 0x7F); 
        return this;
    }

protected:
private:
    SerialType* _serialPtr;
};

//typedef ardPololuServoController<HardwareSerial> ardPololuHardwareSerialServoController;
//typedef ardPololuServoController<SoftwareSerial> ardPololuSoftwareSerialServoController;
