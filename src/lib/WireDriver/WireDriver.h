#pragma once

#include "targets.h"
#include "SX12xxDriverCommon.h"

#ifdef PLATFORM_ESP8266
#include <cstdint>
#endif

#define RADIO_SNR_SCALE 4
#define FREQ_STEP 100

class WireDriver: public SX12xxDriverCommon
{

public:
    static WireDriver *instance;

    ///////////Radio Variables////////

    ///////////////////////////////////

    ////////////////Configuration Functions/////////////
    WireDriver();
    bool Begin(uint32_t minimumFrequency, uint32_t maximumFrequency);
    void End();
    void Config(uint8_t bw, uint8_t sf, uint8_t cr, uint32_t freq, uint8_t preambleLen, bool InvertIQ, uint8_t _PayloadLength, uint32_t interval);
    // void SetMode(SX127x_RadioOPmodes mode, SX12XX_Radio_Number_t radioNumber);
    void SetTxIdleMode() {} // { SetMode(SX127x_OPMODE_STANDBY, SX12XX_Radio_All); } // set Idle mode used when switching from RX to TX
    // void SetTxIdleMode() { SetMode(LR1121_MODE_FS, SX12XX_Radio_All); }; // set Idle mode used when switching from RX to TX

    void startCWTest(uint32_t freq, SX12XX_Radio_Number_t radioNumber);
    void SetOutputPower(uint8_t Power);
    // void SetRxTimeoutUs(uint32_t interval);

    // void SetFrequencyHz(uint32_t freq, SX12XX_Radio_Number_t radioNumber);
    void SetFrequencyReg(uint32_t freq, SX12XX_Radio_Number_t radioNumber = SX12XX_Radio_All);
    bool GetFrequencyErrorbool();
    bool FrequencyErrorAvailable() const { return true; }

    ////////////////////////////////////////////////////

    /////////////////Utility Funcitons//////////////////

    //////////////RX related Functions/////////////////
    void GetLastPacketStats();

    ////////////Non-blocking TX related Functions/////////////////
    void TXnb(uint8_t * data, uint8_t size, SX12XX_Radio_Number_t radioNumber);
    /////////////Non-blocking RX related Functions///////////////
    void RXnb();

private:
    // constant used for no power change pending
    // must not be a valid power register value
    static const int16_t PWRPENDING_NONE = -1;

    // void SetMode(lr11xx_RadioOperatingModes_t OPmode, SX12XX_Radio_Number_t radioNumber);

    static void IsrCallback_1();
    static void IsrCallback_2();
    static void IsrCallback(SX12XX_Radio_Number_t radioNumber);
    bool RXnbISR(SX12XX_Radio_Number_t radioNumber); // ISR for non-blocking RX routine
    void TXnbISR(); // ISR for non-blocking TX routine
    // void CommitOutputPower();
};
