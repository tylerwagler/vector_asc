/**
 * @brief Vector ASCII Reader
 *
 * The implementation is based on:
 * - CAN_LIN_TRIGGER_ASC_Format.pdf, Version 1.3.0, 2013-04-11
 * - Ethernet_ASC_Format.pdf, Version 1.2.0, 2013-04-23
 * - FlexRay_ASC_Format.pdf, Version 1.4.2, 2009-09-08
 * - KLine_ASC_Format.pdf, Version 1.0, 2011-02-02
 * - LIN_ASC_Format.pdf, Version 1.0.17, 2010-10-27
 * - MOST_ASC_Format.pdf, Version 1.8.7, 2013-03-20
 * - TPDiag_ASC_Format.pdf, Version 1.1, 2009-05-18
 */

#pragma once

#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "core/Driver.h"
#include "core/Time.h"
#include "ISO/ISO11898/Message.h"
#include "ISO/ISO11898/Statistics.h"
#include "Types.h"
#include "Vector/Version.h"

namespace Vector {
namespace ASC {

class Reader : public std::ifstream
{
public:
    Reader();
    ~Reader();

    FileHeader fileHeader;

    core::TimePoint triggerTime; //!< Trigger block timestamp
    core::TimePoint lastEventTime; //!< Last event timestamp

    /**
     * One driver for each channel number
     */
    std::map<Symbol::Channel, std::shared_ptr<core::Driver>> drivers;

    core::Event * readEvent();

private:
    std::string line;
    std::vector<std::string> elements;

    /* file header/trailer */
    bool readFileHeader();

    /* CAN Events */
    ISO::ISO11898::Message * canMessageEvent(); //!< CAN Message Event
    ISO::ISO11898::Message * canRemoteFrameEvent(); //!< CAN Remote Frame Event
    ISO::ISO11898::Message * canErrorFrame(); //!< CAN Error Frame
    ISO::ISO11898::Statistics * canBusStatisticsEvent(); //!< CAN Bus Statistics Event
    bool canErrorEvent(); //!< CAN Error Event
    bool canOverloadFrameEvent(); //!< CAN Overload Frame Event

    /* CAN FD Events */
    // CAN FD Message Event
    // CAN FD Extended Message Event
    // CAN FD Error Frame
    // CAN FD Bus Statistics Event
    // CAN FD Overload Frame

    /* Log and Trigger Events */
    bool logTriggerEvent(); //!< Log Trigger Event
    bool logDirectStartEvent(); //!< Log Direct Start Event
    bool logDirectStopEvent(); //!< Log Direct Stop Event
    bool beginTriggerblockEvent(); //!< Begin Triggerblock Event
    bool endTriggerblockEvent(); //!< End Triggerblock Event

    /* Environment Variables */

    /* System Variables */

    /* Macros: Signalevents */

    /* GPS events */

    /* Comment events */

    /* Global market events */

    /* Ethernet events */
    // Ethernet Packet
    // Ethernet Status
    // Ethernet Rx Error

    /* AFDX events */
    // AFDX Packet

    /* FlexRay events (Old Format) */
    // FlexRay Message Event
    // FlexRay Start Cycle Event

    /* FlexRay events (New Format) */
    // FlexRay Message Event ("RMSG/PDU")
    // FlexRay Start Cycle Event ("SCE")
    // FlexRay Status Event ("SE")
    // FlexRay Error Event ("EE")

    /* K-Line events */
    // Byte event
    // Message event

    /* LIN Events */
    // LIN Message

    /* LIN Error Events */
    // LIN Transmission Event
    // LIN Receive Error
    // LIN Sync Error
    // LIN Checksum Error
    // LIN Spike Error
    // LIN Dominant Signal

    /* LIN Info Events */
    // LIN Baudrate
    // LIN DLC Info
    // LIN Checksum Info
    // LIN Scheduler Mode Change
    // LIN Slave Timeout
    // LIN Event Triggered Frame Info
    // LIN Statistic Info
    // LIN Short or slow response
    // LIN Disturbance event

    /* LIN Sleep/Wakeup Events */
    // LIN Sleep Mode
    // LIN Wakeup Frame
    // LIN Unexpected wakeup

    /* MOST events */
    // MOST25 Control Message Node Mode
    // MOST25 Control Message Spy Mode
    // MOST25 Packet
    // MOST Light Lock Event
    // MOST Special Register Event
    // MOST Common Register Event
    // MOST HW Mode Event
    // MOST NetState Event
    // MOST Data Lost Event
    // MOST Trigger Event
    // MOST Statistic Event
    // MOST Statistic Extended Event (CodingErrors and FrameCounter)
    // MOST TxLight
    // MOST Stress Event
    // MOST25 Alloc Table
    // MOST150 Control Message
    // MOST50/150 Control Message Fragment
    // MOST150 Packet
    // MOST50/150 Packet Fragment
    // MOST Ethernet Packet
    // MOST Ethernet Packet Fragment
    // MOST System Event
    // MOST50/150 Allocation Table
    // MOST50 Control Message
    // MOST50 Packet
    // MOST ECL

    /* TP-Diag events */
    // Prefix
    // Single Frame
    // First Frame
    // Consecutive Frame
    // Flow Control Frame
    // Event format

    /* time reader */
    Symbol::WeekDay calcWeekDay(std::string & str);
    Symbol::Month calcMonth(std::string & str);
    core::TimePoint getTimePoint(Symbol::WeekDay & weekDay, Symbol::Month & month, Symbol::Date & date, Symbol::FullTime & fullTime, Symbol::Year & year);
    core::TimePoint getTimePoint(double & timeStamp);
    std::shared_ptr<core::Driver> getDriver(Symbol::Channel & channel);
};

}
}
