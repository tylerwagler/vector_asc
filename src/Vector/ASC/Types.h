#pragma once

#include <string>
#include <vector>

#include "core/Time.h"
#include "Vector/Version.h"
#include "Symbols.h"

namespace Vector {
namespace ASC {

/**
 * Events can either be recorder in
 * hexadecimal ("base hex") or decimal mode ("base dec").
 */
typedef enum class : unsigned short {
    Hex = 16, //!< hexadecimal mode
    Dec = 10  //!< decimal mode
} NumberBase;

/**
 * Timestamps are written absolute ("timestamps absolute") or
 * relative to the preceding event ("timestamps relative").
 */
typedef enum class {
    Absolute, //!< timestamps absolute
    Relative  //!< timestamps relative
} TimeStampMode;

/**
 * File Header
 */
typedef struct FileHeader {
    /* date Die Dez 21 11:29:01 2004 */
    core::TimePoint date = std::chrono::system_clock::now(); //!< File header timestamp

    /* base hex  timestamps absolute */
    NumberBase numberBase = NumberBase::Hex; //!< Hexadecimal or decimal mode
    TimeStampMode timeStampMode = TimeStampMode::Absolute; //!< Absolute or relative timestamps

    /* internal events logged */
    bool internalEventsLogged = false; //!< Internal events logged

    /* // version 7.0.0 */
    Vector::Version version = Vector::Version::Ver_unknown; //!< Vector version

    /* Split information */
    core::TimePoint splitTime = std::chrono::system_clock::now(); //!< Split time

    /* Previous Log File Name */
    std::string previousLogFileName = "";
} FileHeader;

/**
 * CAN Message Event
 */
typedef struct CanMessageEvent {
    Symbol::Time time;
    Symbol::Channel channel;
    Symbol::NumericID id;
    Symbol::Dir dir;
    Symbol::DLC dlc;
    std::vector<unsigned short> data;

    Symbol::MessageDuration messageDuration;
    Symbol::MessageLength messageLength;
    Symbol::MessageFlags messageFlags;
} CanMessageEvent;

/**
 * CAN Remote Frame Event
 */
typedef struct CanRemoteFrameEvent {
    Symbol::Time time;
    Symbol::Channel channel;
    Symbol::NumericID id;
    Symbol::Dir dir;
} CanRemoteFrameEvent;

/**
 * CAN Error Frame
 */
typedef struct CanErrorFrame {
    Symbol::Time time;
    Symbol::Channel channel;

    bool sja1000;
    unsigned short ecc;

    bool canCore;
    unsigned short flags;
    unsigned short codeExt;
    unsigned short code;
    Symbol::NumericID id;
    Symbol::DLC dlc;
    unsigned int position;
    unsigned int length;
} CanErrorFrame;

/**
 * CAN Bus Statistics Event
 */
typedef struct CanBusStatisticsEvent {
    Symbol::Time time;
    Symbol::Channel channel;
    Symbol::StatNumber d; //!< CAN Data Frames
    Symbol::StatNumber r; //!< CAN Remote Frame
    Symbol::StatNumber xd; //!< CAN Extended Data Frames
    Symbol::StatNumber xr; //!< CAN Extended Remote Frames
    Symbol::StatNumber e; //!< Error Frames
    Symbol::StatNumber o; //!< Overload Frames
    Symbol::StatPercent b; //!< Busload
} CanBusStatisticsEvent;

/**
 * CAN Error Event
 */
typedef struct CanErrorEvent {
    Symbol::Time time;
    Symbol::Channel channel;
    Symbol::Error error;
} CanErrorEvent;

/**
 * CAN Overload Frame Event
 */
typedef struct CanOverloadFrameEvent {
    Symbol::Time time;
    Symbol::Channel channel;
} CanOverloadFrameEvent;

/**
 * Log Trigger Event
 */
typedef struct LogTriggerEvent {
    Symbol::Time time;
} LogTriggerEvent;

/**
 * Log Direct Start Event
 */
typedef struct LogDirectStartEvent {
    Symbol::Time time;
    Symbol::PreTrigger preTrigger;
} LogDirectStartEvent;

/**
 * Log Direct Stop Event
 */
typedef struct LogDirectStopEvent {
    Symbol::Time time;
    Symbol::PostTrigger postTrigger;
} LogDirectStopEvent;

/**
 * Begin Triggerblock Event
 */
typedef struct BeginTriggerblockEvent {
    Symbol::WeekDay weekDay;
    Symbol::Month month;
    Symbol::Date date;
    Symbol::FullTime fullTime;
    Symbol::Year year;
} BeginTriggerblockEvent;

/**
 * End Triggerblock Event
 */
typedef struct EndTriggerblockEvent {
} EndTriggerblockEvent;

/**
 * Generic Event type
 */
typedef struct Event {
    /**
     * input line
     */
    std::string line;

    /**
     * event type
     */
    typedef enum class EventType {
        Unknown = 0,

        /* CAN Events */
        CanMessageEvent,
        CanRemoteFrameEvent,
        CanErrorFrame,
        CanBusStatisticsEvent,
        CanErrorEvent,
        CanOverloadFrameEvent,

        /* Log and Trigger Events */
        LogTriggerEvent,
        LogDirectStartEvent,
        LogDirectStopEvent,
        BeginTriggerblockEvent,
        EndTriggerblockEvent
    } eventType;

    /**
     * event data
     */
    union {
        /* CAN Events */
        CanMessageEvent         canMessageEvent;
        CanRemoteFrameEvent     canRemoteFrameEvent;
        CanErrorFrame           canErrorFrame;
        CanBusStatisticsEvent   canBusStatisticsEvent;
        CanErrorEvent           canErrorEvent;
        CanOverloadFrameEvent   canOverloadFrameEvent;

        /* CAN FD Events */
        // CAN FD Message Event
        // CAN FD Extended Message Event
        // CAN FD Error Frame
        // CAN FD Bus Statistics Event
        // CAN FD Overload Frame

        /* Log and Trigger Events */
        LogTriggerEvent         logTriggerEvent;
        LogDirectStartEvent     logDirectStartEvent;
        LogDirectStopEvent      logDirectStopEvent;
        BeginTriggerblockEvent  beginTriggerblockEvent;
        EndTriggerblockEvent    endTriggerblockEvent;

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
    };
} Event;

}
}
