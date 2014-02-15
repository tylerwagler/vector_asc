/**
 * @brief Vector ASCII Writer
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
#include <string>
#include <vector>

#include "core/Driver.h"
#include "core/Event.h"
#include "core/Time.h"
#include "ISO/ISO11898/Message.h"
#include "ISO/ISO11898/Statistics.h"
#include "Types.h"
#include "Vector/Version.h"

namespace Vector {
namespace ASC {

class Writer : public std::ofstream
{
public:
    Writer();
    ~Writer();

    NumberBase numberBase; //!< Hexadecimal or decimal mode
    TimeStampMode timeStampMode; //!< Absolute or relative timestamps
    bool internalEventsLogged; //!< Internal events logged
    Vector::Version version; //!< Vector version

    core::TimePoint triggerTime; //!< Trigger block timestamp
    core::TimePoint lastEventTime; //!< Last event timestamp

    /**
     * Drivers which are defined as Tx nodes
     */
    std::vector<std::weak_ptr<core::Driver>> txDrivers;

    void writeEvent(core::Event * event);

    /* file header/trailer */
    void fileHeader(core::TimePoint & fileTime);
    void fileSplitInformation(core::Duration lastTime, std::string & lastFilename);

private:
    /* CAN Events */
    void canMessageEvent(ISO::ISO11898::Message * message);
    void canMessageEvent(core::TimePoint & eventTime, std::string & channel, unsigned int id, bool extended, bool dirTx, unsigned short dlc, std::vector<unsigned short> & data, unsigned int length, unsigned int bitCount, std::string & messageFlags);
    void canRemoteFrameEvent(ISO::ISO11898::Message * message);
    void canRemoteFrameEvent(core::TimePoint & eventTime, std::string & channel, unsigned int id, bool extended, bool dirTx);
    void canErrorFrame(ISO::ISO11898::Message * message);
    void canErrorFrame(core::TimePoint & eventTime, std::string & channel, bool sja1000 = false, unsigned short ecc = 0, bool canCore = false, unsigned int flags = 0, unsigned int codeExt = 0, unsigned int code = 0, unsigned int id = 0, bool extended = false, unsigned int dlc = 0, unsigned int position = 0, unsigned int length = 0);
    void canBusStatisticsEvent(ISO::ISO11898::Statistics * statistics);
    void canBusStatisticsEvent(core::TimePoint & eventTime, std::string & channel, unsigned int d, unsigned int r, unsigned int xd, unsigned int xr, unsigned int e, unsigned int o, double b);
    void canErrorEvent(core::TimePoint & eventTime, std::string & channel, std::string & status);
    void canOverloadFrameEvent(core::TimePoint & eventTime, std::string & channel);

    /* CAN FD Events */
    // CAN FD Message Event
    // CAN FD Extended Message Event
    // CAN FD Error Frame
    // CAN FD Bus Statistics Event
    // CAN FD Overload Frame

    /* Log and Trigger Events */
    void logTriggerEvent(core::TimePoint & eventTime);
    void logDirectStartEvent(core::TimePoint & eventTime, unsigned int preTrigger);
    void logDirectStopEvent(core::TimePoint & eventTime, unsigned int postTrigger);
    void beginTriggerblockEvent(core::TimePoint & eventTime);
    void endTriggerblockEvent();

    /* Environment Variables */
    void environmentVariablesEvent(core::TimePoint & eventTime, std::string & evname, std::string & value);

    /* System Variables */
    void systemVariablesEvent(core::TimePoint & eventTime, unsigned int svtype, unsigned int flag1, unsigned int flag2, std::string & path, std::string & value);

    /* Macros: Signalevents */
    void macroSignalEvent(core::TimePoint & eventTime, std::string & bussystem, std::string & channel, std::string & node, std::string & message, std::string & signal, std::string & value);

    /* GPS events */
    void gpsEvent(core::TimePoint & eventTime, std::string & channel, double latitude, double longitude, double altitude, double speed, double course);

    /* Comment events */
    void commentEvent(core::TimePoint & eventTime, std::string & type, std::string & commentText);

    /* Global marker events */

    /* Ethernet events */
    void ethernetPacket(core::TimePoint & eventTime, std::string & channel, bool dirTx, unsigned int dataLen, std::vector<unsigned short> & data);
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

private:
    double getTimeStamp(core::TimePoint & timePoint);
    std::string getChannel(core::Event * event);
    bool isTx(core::Event * event);
};

}
}
