#include "WireDriver.h"
#include "logging.h"

WireDriver *WireDriver::instance = NULL;

WireDriver::WireDriver(): SX12xxDriverCommon()
{
    instance = this;
}

bool WireDriver::Begin(uint32_t minimumFrequency, uint32_t maximumFrequency)
{
    // hal.init();
    // hal.IsrCallback_1 = &WireDriver::IsrCallback_1;
    // hal.IsrCallback_2 = &WireDriver::IsrCallback_2;

    // hal.reset();
    DBGLN("WireDriver Begin");

    return true;
}

void WireDriver::End()
{
    RemoveCallbacks();
}

void WireDriver::startCWTest(uint32_t freq, SX12XX_Radio_Number_t radioNumber)
{
}

void ICACHE_RAM_ATTR WireDriver::GetLastPacketStats()
{
//   SX12XX_Radio_Number_t radio[2] = {SX12XX_Radio_1, SX12XX_Radio_2};
//   bool gotRadio[2] = {false, false}; // one-radio default.
//   uint8_t processingRadioIdx = (instance->processingPacketRadio == SX12XX_Radio_1) ? 0 : 1;
//   uint8_t secondRadioIdx = !processingRadioIdx;

//   // processingRadio always passed the sanity check here
//   gotRadio[processingRadioIdx] = true;

//   // if it's a dual radio, and if it's the first IRQ
//   // (don't need this if it's the second IRQ, because we know the first IRQ is already failed)
//   if (instance->isFirstRxIrq && GPIO_PIN_NSS_2 != UNDEF_PIN)
//   {
//     bool isSecondRadioGotData = false;
//     uint16_t secondIrqStatus = instance->GetIrqFlags(radio[secondRadioIdx]);

//     if(secondIrqStatus & SX127X_CLEAR_IRQ_FLAG_RX_DONE)
//     {
//       WORD_ALIGNED_ATTR uint8_t RXdataBuffer_second[RXBuffSize];
//       uint8_t const FIFOaddr = hal.readRegister(SX127X_REG_FIFO_RX_CURRENT_ADDR, radio[secondRadioIdx]);
//       hal.writeRegister(SX127X_REG_FIFO_ADDR_PTR, FIFOaddr, radio[secondRadioIdx]);
//       hal.readRegister(SX127X_REG_FIFO, RXdataBuffer_second, PayloadLength, radio[secondRadioIdx]);

//       // if the second packet is same to the first, it's valid
//       if (memcmp(RXdataBuffer, RXdataBuffer_second, PayloadLength) == 0)
//       {
//         isSecondRadioGotData = true;
//       }
//     }

//     gotRadio[secondRadioIdx] = isSecondRadioGotData;
//     #if defined(DEBUG_RCVR_SIGNAL_STATS)
//     // second radio received the same packet to the processing radio
//     if(!isSecondRadioGotData)
//     {
//       instance->rxSignalStats[secondRadioIdx].fail_count++;
//     }
//     #endif
//   }

//   int8_t rssi[2];
//   int8_t snr[2];

//   for (uint8_t i = 0; i < 2; i++)
//   {
//     if (gotRadio[i])
//     {
//       rssi[i] = GetLastPacketRSSI(radio[i]);
//       snr[i] = GetLastPacketSNRRaw(radio[i]);
//       // https://www.mouser.com/datasheet/2/761/sx1276-1278113.pdf
//       // Section 3.5.5 (page 87)
//       int8_t negOffset = (snr[i] < 0) ? (snr[i] / RADIO_SNR_SCALE) : 0;
//       rssi[i] += negOffset;

//       // If radio # is 0, update LastPacketRSSI, otherwise LastPacketRSSI2
//       (i == 0) ? LastPacketRSSI = rssi[i] : LastPacketRSSI2 = rssi[i];
//       // Update whatever SNRs we have
//       LastPacketSNRRaw = snr[i];
//     }
//   }

//   // by default, set the last successful packet radio to be the current processing radio (which got a successful packet)
//   instance->lastSuccessfulPacketRadio = instance->processingPacketRadio;

//   // when both radio got the packet, use the better RSSI one
//   if (gotRadio[0] && gotRadio[1])
//   {
//     LastPacketSNRRaw = instance->fuzzy_snr(snr[0], snr[1], instance->FuzzySNRThreshold);
//     // Update the last successful packet radio to be the one with better signal strength
//     instance->lastSuccessfulPacketRadio = (rssi[0] > rssi[1]) ? radio[0] : radio[1];
//   }

// #if defined(DEBUG_RCVR_SIGNAL_STATS)
//   // stat updates
//   for (uint8_t i = 0; i < 2; i++)
//   {
//     if (gotRadio[i])
//     {
//       instance->rxSignalStats[i].irq_count++;
//       instance->rxSignalStats[i].rssi_sum += rssi[i];
//       instance->rxSignalStats[i].snr_sum += snr[i];
//       if (snr[i] > instance->rxSignalStats[i].snr_max)
//       {
//         instance->rxSignalStats[i].snr_max = snr[i];
//       }
//       LastPacketSNRRaw = snr[i];
//     }
//   }
//   if (gotRadio[0] || gotRadio[1])
//   {
//     instance->irq_count_or++;
//   }
//   if (gotRadio[0] && gotRadio[1])
//   {
//     instance->irq_count_both++;
//   }
// #endif
}

void WireDriver::Config(uint8_t bw, uint8_t sf, uint8_t cr, uint32_t freq, uint8_t preambleLen, bool InvertIQ, uint8_t _PayloadLength, uint32_t interval)
{
  // Config(bw, sf, cr, freq, preambleLen, currSyncWord, InvertIQ, _PayloadLength, interval);
}

void ICACHE_RAM_ATTR WireDriver::SetFrequencyReg(uint32_t regfreq, SX12XX_Radio_Number_t radioNumber)
{
}

bool ICACHE_RAM_ATTR WireDriver::GetFrequencyErrorbool()
{
    return false;
}

void ICACHE_RAM_ATTR WireDriver::IsrCallback_1()
{
    instance->IsrCallback(SX12XX_Radio_1);
}

void ICACHE_RAM_ATTR WireDriver::IsrCallback_2()
{
    instance->IsrCallback(SX12XX_Radio_2);
}

void ICACHE_RAM_ATTR WireDriver::IsrCallback(SX12XX_Radio_Number_t radioNumber)
{
    instance->processingPacketRadio = radioNumber;
//     SX12XX_Radio_Number_t irqClearRadio = radioNumber;

//     uint8_t irqStatus = instance->GetIrqFlags(radioNumber);
//     if (irqStatus & SX127X_CLEAR_IRQ_FLAG_TX_DONE)
//     {
//         RFAMP.TXRXdisable();
//         instance->TXnbISR();
//         irqClearRadio = SX12XX_Radio_All;
//     }
//     else if (irqStatus & SX127X_CLEAR_IRQ_FLAG_RX_DONE)
//     {
//         if (instance->RXnbISR(radioNumber))
//         {
//             irqClearRadio = SX12XX_Radio_All;
//         }
// #if defined(DEBUG_RCVR_SIGNAL_STATS)
//         else
//         {
//             instance->rxSignalStats[(radioNumber == SX12XX_Radio_1) ? 0 : 1].fail_count++;
//         }
// #endif
//         instance->isFirstRxIrq = false;   // RX isr is already fired in this period. (reset to true in tock)
//     }
//     else if (irqStatus == SX127X_CLEAR_IRQ_FLAG_NONE)
//     {
//         return;
//     }

    // instance->ClearIrqFlags(irqClearRadio);
}

/////////////////////////////////////TX functions/////////////////////////////////////////

void ICACHE_RAM_ATTR WireDriver::TXnbISR()
{
  // currOpmode = SX127x_OPMODE_STANDBY; //goes into standby after transmission
  //TXdoneMicros = micros();
  // The power level must be changed when in SX127x_OPMODE_STANDBY, so this lags power
  // changes by at most 1 packet, but does not interrupt any pending RX/TX
  // CommitOutputPower();
  TXdoneCallback();
}

void ICACHE_RAM_ATTR WireDriver::TXnb(uint8_t * data, uint8_t size, SX12XX_Radio_Number_t radioNumber)
{
//   transmittingRadio = radioNumber;

//   SetMode(SX127x_OPMODE_STANDBY, SX12XX_Radio_All);

//   if (radioNumber == SX12XX_Radio_NONE)
//   {
//       return;
//   }

// #if defined(DEBUG_RCVR_SIGNAL_STATS)
//     if (radioNumber == SX12XX_Radio_All || radioNumber == SX12XX_Radio_1)
//     {
//         instance->rxSignalStats[0].telem_count++;
//     }
//     if (radioNumber == SX12XX_Radio_All || radioNumber == SX12XX_Radio_2)
//     {
//         instance->rxSignalStats[1].telem_count++;
//     }
// #endif

//   RFAMP.TXenable(radioNumber);
//   hal.writeRegister(SX127X_REG_FIFO_ADDR_PTR, SX127X_FIFO_TX_BASE_ADDR_MAX, radioNumber);
//   hal.writeRegister(SX127X_REG_FIFO, data, size, radioNumber);

//   SetMode(SX127x_OPMODE_TX, radioNumber);
}

///////////////////////////////////RX Functions Non-Blocking///////////////////////////////////////////

bool ICACHE_RAM_ATTR WireDriver::RXnbISR(SX12XX_Radio_Number_t radioNumber)
{
  // uint8_t const FIFOaddr = hal.readRegister(SX127X_REG_FIFO_RX_CURRENT_ADDR, radioNumber);
  // hal.writeRegister(SX127X_REG_FIFO_ADDR_PTR, FIFOaddr, radioNumber);
  // hal.readRegister(SX127X_REG_FIFO, RXdataBuffer, PayloadLength, radioNumber);

  // if (timeoutSymbols)
  // {
  //   // From page 42 of the datasheet rev 7
  //   // In Rx Single mode, the device will return to Standby mode as soon as the interrupt occurs
  //   currOpmode = SX127x_OPMODE_STANDBY;
  // }

  return RXdoneCallback(SX12XX_RX_OK);
}

void ICACHE_RAM_ATTR WireDriver::RXnb()
{
  // RFAMP.RXenable();

  // if (timeoutSymbols)
  // {
  //   SetMode(SX127x_OPMODE_RXSINGLE, SX12XX_Radio_All);
  // }
  // else
  // {
  //   SetMode(SX127x_OPMODE_RXCONTINUOUS, SX12XX_Radio_All);
  // }
}

/***
 * @brief: Schedule an output power change after the next transmit
 * The radio must be in SX127x_OPMODE_STANDBY to change the power
 ***/
void WireDriver::SetOutputPower(uint8_t Power)
{
  // uint8_t pwrNew;
  // Power &= SX127X_PA_POWER_MASK;

  // if (OPT_USE_SX1276_RFO_HF)
  // {
  //   pwrNew = SX127X_PA_SELECT_RFO | Power;
  // }
  // else
  // {
  //   pwrNew = SX127X_PA_SELECT_BOOST | Power;
  // }

  // if ((pwrPending == PWRPENDING_NONE && pwrCurrent != pwrNew) || pwrPending != pwrNew)
  // {
  //   pwrPending = pwrNew;
  // }
}
