/* ASC Parser */

%skeleton "glr.cc"
%require "3.0"
%defines
%define api.namespace {Vector::ASC}
%define api.value.type union
%define parse.trace
%define parser_class_name {Parser}
%language "C++"
%locations

    // debug options
%verbose
%debug
%error-verbose

%code requires{
namespace Vector {
namespace ASC {
    class Driver;
    class Scanner;
}
}
#include "Types.h"
}

%parse-param { Vector::ASC::Scanner & scanner }
%parse-param { Vector::ASC::Driver & driver }

%code{
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "Driver.hpp"
#include "Event.h"
#include "File.h"
#include "Types.h"

/* CAN Events */
#include "CanMessageEvent.h"
#include "CanExtendedMessageEvent.h"
#include "CanRemoteFrameEvent.h"
#include "CanErrorFrame.h"
#include "CanBusStatisticsEvent.h"
#include "CanErrorEvent.h"
#include "CanOverloadFrameEvent.h"

/* CAN FD Events */
#include "CanFdMessageEvent.h"
#include "CanFdExtendedMessageEvent.h"
#include "CanFdErrorFrame.h"
// CAN FD Bus Statistics Event
// CAN FD Overload Frame

/* Log and Trigger Events */
#include "LogTriggerEvent.h"
#include "LogDirectStartEvent.h"
#include "LogDirectStopEvent.h"
#include "BeginTriggerblockEvent.h"
#include "EndTriggerblockEvent.h"

/* Environment Variables */
#include "EnvironmentVariablesEvent.h"

/* System Variables */
#include "SystemVariablesEvent.h"

/* Macros Signal Event */
#include "MacroSignalEvent.h"

/* GPS events */
#include "GpsEvent.h"

/* Comment events */
#include "CommentEvent.h"

/* Global market events */
#include "GlobalMarkerEvent.h"

/* Ethernet Events */
#include "EthernetPacket.h"
#include "EthernetStatus.h"
#include "EthernetRxError.h"

/* AFDX Events */
#include "AfdxPacket.h"

/* FlexRay Events (Old Format) */
#include "FlexRayOldMessageEvent.h"
#include "FlexRayOldStartCycleEvent.h"

/* FlexRay Events (New Format) */
#include "FlexRayMessageEvent.h"
#include "FlexRayStartCycleEvent.h"
#include "FlexRayStatusEvent.h"
#include "FlexRayErrorEvent.h"

/* K-Line Events */
#include "KLineByteEvent.h"
#include "KLineMessageEvent.h"

/* LIN Events */
#include "LinMessage.h"

/* LIN Error Events */
#include "LinTransmissionError.h"
#include "LinReceiveError.h"
#include "LinSyncError.h"
#include "LinChecksumError.h"
#include "LinSpikeEvent.h"
#include "LinDominantSignal.h"

/* LIN Info Events */
#include "LinBaudrate.h"
#include "LinDlcInfo.h"
#include "LinChecksumInfo.h"
#include "LinSchedulerModeChange.h"
#include "LinSlaveTimeout.h"
#include "LinEventTriggeredFrameInfo.h"
#include "LinStatisticInfo.h"
#include "LinShortOrSlowResponse.h"
#include "LinDisturbanceEvent.h"

/* LIN Sleep/Wakeup Events */
#include "LinSleepMode.h"
#include "LinWakeupFrame.h"
#include "LinUnexpectedWakeup.h"

/* MOST Events */
#include "Most25ControlMessageNodeMode.h"
#include "Most25ControlMessageSpyMode.h"
#include "Most25Packet.h"
#include "MostLightLockEvent.h"
#include "MostSpecialRegisterEvent.h"
#include "MostCommonRegisterEvent.h"
#include "MostHwModeEvent.h"
#include "MostNetStateEvent.h"
#include "MostDataLostEvent.h"
#include "MostTriggerEvent.h"
#include "MostStatisticEvent.h"
#include "MostStatisticExtendedEvent.h"
#include "MostTxLight.h"
#include "MostStressEvent.h"
#include "Most25AllocTable.h"
#include "Most150ControlMessage.h"
#include "Most150ControlMessageFragment.h"
#include "Most150Packet.h"
#include "Most150PacketFragment.h"
#include "MostEthernetPacket.h"
#include "MostEthernetPacketFragment.h"
#include "MostSystemEvent.h"
#include "Most150AllocTable.h"
#include "Most50ControlMessage.h"
#include "Most50Packet.h"
#include "MostEcl.h"

/* TP/Diagnostics Events */
#include "TpDiagPrefix.h"
#include "TpDiagSingleFrame.h"
#include "TpDiagFirstFrame.h"
#include "TpDiagConsecutiveFrame.h"
#include "TpDiagFlowControlFrame.h"
#include "TpDiagRequest.h"

#undef yylex
#define yylex scanner.yylex

}

/* file */
%token ENDL
%type <unsigned short> weekDay
%type <unsigned short> month
%type <unsigned short> amPm
%type <class Token *> fullTime
%type <class Token *> fileDate
%type <Vector::ASC::NumberBase> hexDec
%type <Vector::ASC::TimeStampMode> absoluteRelative
%type <class Token *> fileBaseTimestamps
%type <bool> fileInternalEventsLogged
%type <class Token *> fileVersion
%type <class Token *> fileSplitInformation
%type <std::string *> fileComment

/* CAN Events */
%type <Vector::ASC::Dir> dir
%type <Vector::ASC::MessageFlags> messageFlags
%type <class CanMessageEvent *> canMessageEvent
%type <class CanExtendedMessageEvent *> canExtendedMessageEvent
%type <class CanRemoteFrameEvent *> canRemoteFrameEvent
%type <class CanErrorFrame *> canErrorFrame
%type <class CanBusStatisticsEvent *> canBusStatisticsEvent
%type <class CanErrorEvent *> canErrorEvent
%type <class CanOverloadFrameEvent *> canOverloadFrameEvent

/* CAN FD Events */
%type <class CanFdMessageEvent *> canFdMessageEvent
%type <class CanFdExtendedMessageEvent *> canFdExtendedMessageEvent
%type <class CanFdErrorFrame *> canFdErrorFrame

/* Log and Trigger Events */
%type <class LogTriggerEvent *> logTriggerEvent
%type <class LogDirectStartEvent *> logDirectStartEvent
%type <class LogDirectStopEvent *> logDirectStopEvent
%type <class BeginTriggerblockEvent *> beginTriggerblockEvent
%type <class EndTriggerblockEvent *> endTriggerblockEvent

/* Environment Variables */
%type <class EnvironmentVariablesEvent *> environmentVariablesEvent

/* System Variables */
%type <class SystemVariablesEvent *> systemVariablesEvent

/* Macros Signal Events */
%type <class MacroSignalEvent *> macroSignalEvent

/* GPS events */
%type <class GpsEvent *> gpsEvent

/* Comment events */
%type <class CommentEvent *> commentEvent

/* Global marker events */
%type <class GlobalMarkerEvent *> globalMarkerEvent

/* Ethernet Events */
%type <class EthernetPacket *> ethernetPacket
%type <class EthernetStatus *> ethernetStatus
%type <class EthernetRxError *> ethernetRxError

/* AFDX Events */
%type <class AfdxPacket *> afdxPacket

/* FlexRay Events (Old Format) */
%type <class FlexRayOldMessageEvent *> flexRayOldMessageEvent
%type <class FlexRayOldStartCycleEvent *> flexRayOldStartCycleEvent

/* FlexRay Events (New Format) */
%type <class FlexRayMessageEvent *> flexRayMessageEvent
%type <class FlexRayStartCycleEvent *> flexRayStartCycleEvent
%type <class FlexRayStatusEvent *> flexRayStatusEvent
%type <class FlexRayErrorEvent *> flexRayErrorEvent

/* K-Line Events */
%type <class KLineByteEvent *> kLineByteEvent
%type <class KLineMessageEvent *> kLineMessageEvent

/* LIN Events */
%type <class LinMessage *> linMessage

/* LIN Error Events */
%type <class LinTransmissionError *> linTransmissionError
%type <class LinReceiveError *> linReceiveError
%type <class LinSyncError *> linSyncError
%type <class LinChecksumError *> linChecksumError
%type <class LinSpikeEvent *> linSpikeEvent
%type <class LinDominantSignal *> linDominantSignal

/* LIN Info Events */
%type <class LinBaudrate *> linBaudrate
%type <class LinDlcInfo *> linDlcInfo
%type <class LinChecksumInfo *> linChecksumInfo
%type <class LinSchedulerModeChange *> linSchedulerModeChange
%type <class LinSlaveTimeout *> linSlaveTimeout
%type <class LinEventTriggeredFrameInfo *> linEventTriggeredFrameInfo
%type <class LinStatisticInfo *> linStatisticInfo
%type <class LinShortOrSlowResponse *> linShortOrSlowResponse
%type <class LinDisturbanceEvent *> linDisturbanceEvent

/* LIN Sleep/Wakeup Events */
%type <class LinSleepMode *> linSleepMode
%type <class LinWakeupFrame *> linWakeupFrame
%type <class LinUnexpectedWakeup *> linUnexpectedWakeup

/* MOST Events */
%type <class Most25ControlMessageNodeMode *> most25ControlMessageNodeMode
%type <class Most25ControlMessageSpyMode *> most25ControlMessageSpyMode
%type <class Most25Packet *> most25Packet
%type <class MostLightLockEvent *> mostLightLockEvent
%type <class MostSpecialRegisterEvent *> mostSpecialRegisterEvent
%type <class MostCommonRegisterEvent *> mostCommonRegisterEvent
%type <class MostHwModeEvent *> mostHwModeEvent
%type <class MostNetStateEvent *> mostNetStateEvent
%type <class MostDataLostEvent *> mostDataLostEvent
%type <class MostTriggerEvent *> mostTriggerEvent
%type <class MostStatisticEvent *> mostStatisticEvent
%type <class MostStatisticExtendedEvent *> mostStatisticExtendedEvent
%type <class MostTxLight *> mostTxLight
%type <class MostStressEvent *> mostStressEvent
%type <class Most25AllocTable *> most25AllocTable
%type <class Most150ControlMessage *> most150ControlMessage
%type <class Most150ControlMessageFragment *> most150ControlMessageFragment
%type <class Most150Packet *> most150Packet
%type <class Most150PacketFragment *> most150PacketFragment
%type <class MostEthernetPacket *> mostEthernetPacket
%type <class MostEthernetPacketFragment *> mostEthernetPacketFragment
%type <class MostSystemEvent *> mostSystemEvent
%type <class Most150AllocTable *> most150AllocTable
%type <class Most50ControlMessage *> most50ControlMessage
%type <class Most50Packet *> most50Packet
%type <class MostEcl *> mostEcl

/* TP/Diagnostics Events */
%type <class TpDiagPrefix *> tpDiagPrefix
%type <class TpDiagSingleFrame *> tpDiagSingleFrame
%type <class TpDiagFirstFrame *> tpDiagFirstFrame
%type <class TpDiagConsecutiveFrame *> tpDiagConsecutiveFrame
%type <class TpDiagFlowControlFrame *> tpDiagFlowControlFrame
%type <class TpDiagRequest *> tpDiagRequest

%%
    /* log file */
logFile
        : logFile logFileEntry
        | logFileEntry
        | %empty
        ;
logFileEntry
        : ENDL
        /* file */
        | fileDate ENDL
        | fileBaseTimestamps ENDL
        | fileInternalEventsLogged ENDL
        | fileVersion ENDL
        | fileSplitInformation ENDL
        | fileComment ENDL
        /* CAN Events */
        | canMessageEvent ENDL
        | canExtendedMessageEvent ENDL
        | canRemoteFrameEvent ENDL
        | canErrorFrame ENDL
        | canBusStatisticsEvent ENDL
        | canErrorEvent ENDL
        | canOverloadFrameEvent ENDL
        /* CAN FD Events */
        | canFdMessageEvent ENDL
        | canFdExtendedMessageEvent ENDL
        | canFdErrorFrame ENDL
        // @todo | canFdBusStatisticsEvent ENDL
        // @todo | canFdOverloadFrame ENDL
        /* Log and Trigger Events */
        | logTriggerEvent ENDL
        | logDirectStartEvent ENDL
        | logDirectStopEvent ENDL
        | beginTriggerblockEvent ENDL
        | endTriggerblockEvent ENDL
        /* Environment Variables */
        | environmentVariablesEvent ENDL
        /* System Variables */
        | systemVariablesEvent ENDL
        /* Macro Signal Event */
        | macroSignalEvent ENDL
        /* GPS events */
        | gpsEvent ENDL
        /* Comment events */
        | commentEvent ENDL
        /* Global marker events */
        | globalMarkerEvent ENDL
        /* Ethernet Events */
        | ethernetPacket ENDL
        | ethernetStatus ENDL
        | ethernetRxError ENDL
        /* AFDX Events */
        | afdxPacket ENDL
        /* FlexRay Events (Old Format) */
        | flexRayOldMessageEvent ENDL
        | flexRayOldStartCycleEvent ENDL
        /* FlexRay Events (New Format) */
        | flexRayMessageEvent ENDL
        | flexRayStartCycleEvent ENDL
        | flexRayStatusEvent ENDL
        | flexRayErrorEvent ENDL
        /* K-Line Events */
        | kLineByteEvent ENDL
        | kLineMessageEvent ENDL
        /* LIN Events */
        | linMessage ENDL
        /* LIN Error Events */
        | linTransmissionError ENDL
        | linReceiveError ENDL
        | linSyncError ENDL
        | linChecksumError ENDL
        | linSpikeEvent ENDL
        | linDominantSignal ENDL
        /* LIN Info Events */
        | linBaudrate ENDL
        | linDlcInfo ENDL
        | linChecksumInfo ENDL
        | linSchedulerModeChange ENDL
        | linSlaveTimeout ENDL
        | linEventTriggeredFrameInfo ENDL
        | linStatisticInfo ENDL
        | linShortOrSlowResponse ENDL
        | linDisturbanceEvent ENDL
        /* LIN Sleep/Wakeup Events */
        | linSleepMode ENDL
        | linWakeupFrame ENDL
        | linUnexpectedWakeup ENDL
        /* MOST Events */
        | most25ControlMessageNodeMode ENDL
        | most25ControlMessageNodeMode ENDL
        | most25ControlMessageSpyMode ENDL
        | most25Packet ENDL
        | mostLightLockEvent ENDL
        | mostSpecialRegisterEvent ENDL
        | mostCommonRegisterEvent ENDL
        | mostHwModeEvent ENDL
        | mostNetStateEvent ENDL
        | mostDataLostEvent ENDL
        | mostTriggerEvent ENDL
        | mostStatisticEvent ENDL
        | mostStatisticExtendedEvent ENDL
        | mostTxLight ENDL
        | mostStressEvent ENDL
        | most25AllocTable ENDL
        | most150ControlMessage ENDL
        | most150ControlMessageFragment ENDL
        | most150Packet ENDL
        | most150PacketFragment ENDL
        | mostEthernetPacket ENDL
        | mostEthernetPacketFragment ENDL
        | mostSystemEvent ENDL
        | most150AllocTable ENDL
        | most50ControlMessage ENDL
        | most50Packet ENDL
        | mostEcl ENDL
        /* TP/Diagnostics Events */
        | tpDiagPrefix ENDL
        | tpDiagSingleFrame ENDL
        | tpDiagFirstFrame ENDL
        | tpDiagConsecutiveFrame ENDL
        | tpDiagFlowControlFrame ENDL
        | tpDiagRequest ENDL
        ;

    /* common */
bindigit
        : '0' | '1'
        ;
bindigits
        : bindigits bindigit
        | bindigit
        ;
digit
        : '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
        ;
digits
        : digits digit
        | digit
        ;
hexdigit
        : '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
        | 'a' | 'b' | 'c' | 'd' | 'e' | 'f'
        | 'A' | 'B' | 'C' | 'D' | 'E' | 'F'
        ;
hexdigits
        : hexdigits hexdigit
        | hexdigit
        ;
hexArray
        : hexArray ' ' hexdigits
        | %empty
        ;
data
        : data ' ' hexdigit hexdigit
        | ' ' hexdigit hexdigit
        ;
data.opt
        : %empty
        | data
        ;
float
        : '-' digits '.' digits
        | digits '.' digits
        ;
floatArray
        : floatArray ' ' float
        | %empty
        ;
character
        : ' ' | '!' | '"' | '#' | '$' | '%' | '&' | '\'' | '(' | ')' | '*' | '+' | ',' | '-' | '.' | '/' | '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' | ':' | ';' | '<'  | '=' | '>' | '?'
        | '@' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G'  | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '[' | '\\' | ']' | '^' | '_'
        | '`' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g'  | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | '{' | '|'  | '}' | '~'
        ;
string
        : string character
        | character
        ;

    /* file */
DATE
        : 'd' 'a' 't' 'e'
        ;
weekDay
        : 'S' 'u' 'n' { $$ = 0; }
        | 'S' 'o' 'n' { $$ = 0; }
        | 'M' 'o' 'n' { $$ = 1; }
        | 'T' 'u' 'e' { $$ = 2; }
        | 'D' 'i' 'e' { $$ = 2; }
        | 'W' 'e' 'd' { $$ = 3; }
        | 'M' 'i' 't' { $$ = 3; }
        | 'T' 'h' 'u' { $$ = 4; }
        | 'D' 'o' 'n' { $$ = 4; }
        | 'F' 'r' 'i' { $$ = 5; }
        | 'F' 'r' 'e' { $$ = 5; }
        | 'S' 'a' 't' { $$ = 6; }
        | 'S' 'a' 'm' { $$ = 6; }
        ;
month
        : 'J' 'a' 'n' { $$ = 0; }
        | 'F' 'e' 'b' { $$ = 1; }
        | 'M' 'a' 'r' { $$ = 2; }
        | 'M' "ä" 'r' { $$ = 2; }
        | 'A' 'p' 'r' { $$ = 3; }
        | 'M' 'a' 'y' { $$ = 4; }
        | 'M' 'a' 'i' { $$ = 4; }
        | 'J' 'u' 'n' { $$ = 5; }
        | 'J' 'u' 'l' { $$ = 6; }
        | 'A' 'u' 'g' { $$ = 7; }
        | 'S' 'e' 'p' { $$ = 8; }
        | 'O' 'c' 't' { $$ = 9; }
        | 'O' 'k' 't' { $$ = 9; }
        | 'N' 'o' 'v' { $$ = 10; }
        | 'D' 'e' 'c' { $$ = 11; }
        | 'D' 'e' 'z' { $$ = 11; }
        ;
amPm
        : %empty
        | ' ' 'a' 'm' { $$ = 0; }
        | ' ' 'p' 'm' { $$ = 12; }
        ;
date
        : digit digit
        ;
fullTime
        : digit digit ':' digit digit ':' digit digit amPm
        ;
year
        : digit digit digit digit
        ;
fileDate
        : DATE ' ' weekDay ' ' month ' ' date ' ' fullTime ' ' year { std::cout << "fileDate" << std::endl; }
        ;
BASE
        : 'b' 'a' 's' 'e'
        ;
hexDec
        : 'h' 'e' 'x' { $$ = Vector::ASC::NumberBase::Hex; }
        | 'd' 'e' 'c' { $$ = Vector::ASC::NumberBase::Dec; }
        ;
TIMESTAMPS
        : 't' 'i' 'm' 'e' 's' 't' 'a' 'm' 'p' 's'
        ;
absoluteRelative
        : 'a' 'b' 's' 'o' 'l' 'u' 't' 'e' { $$ = Vector::ASC::TimeStampMode::Absolute; }
        | 'r' 'e' 'l' 'a' 't' 'i' 'v' 'e' { $$ = Vector::ASC::TimeStampMode::Relative; }
        ;
fileBaseTimestamps
        : BASE ' ' hexDec ' ' ' ' TIMESTAMPS ' ' absoluteRelative { std::cout << "fileBaseTimestamps" << std::endl; }
        ;
INTERNAL_EVENTS_LOGGED
        : 'i' 'n' 't' 'e' 'r' 'n' 'a' 'l' ' ' 'e' 'v' 'e' 'n' 't' 's' ' ' 'l' 'o' 'g' 'g' 'e' 'd'
        ;
fileInternalEventsLogged
        : INTERNAL_EVENTS_LOGGED { std::cout << "fileInternalEventsLogged" << std::endl; $$ = true; }
        | 'n' 'o' ' ' INTERNAL_EVENTS_LOGGED { std::cout << "fileInternalEventsLogged" << std::endl; $$ = false; }
        ;
fileVersion
        : '/' '/' ' ' 'v' 'e' 'r' 's' 'i' 'o' 'n' ' ' digits '.' digits '.' digits { std::cout << "fileVersion" << std::endl; }
        ;
PREVIOUS_LOG_FILE
        : 'p' 'r' 'e' 'v' 'i' 'o' 'u' 's' ' ' 'l' 'o' 'g' ' ' 'f' 'i' 'l' 'e' ':'
        ;
fileSplitInformation
        : '/' '/' ' ' ' ' float ' ' PREVIOUS_LOG_FILE ' ' string { std::cout << "fileSplitInformation" << std::endl; }
        ;
fileComment
        : '/' '/' ' ' string { std::cout << "fileComment" << std::endl; }
        ;

    /* CAN Events */
dir
        : 'R' 'x' { $$ = Vector::ASC::Dir::Rx; }
        | 'T' 'x' { $$ = Vector::ASC::Dir::Tx; }
        | 'T' 'x' 'R' 'q' { $$ = Vector::ASC::Dir::TxRq; }
        ;
messageFlags
        : 'T' 'E' { $$.te = true; }
        | 'W' 'U' { $$.wu = true; }
        | 'X' 'X' { $$.te = true; $$.wu = true; }
        ;
messageFlags.opt
        : %empty
        | ' ' messageFlags
        ;
LENGTH
        : 'L' 'e' 'n' 'g' 't' 'h' ' ' '=' ' '
        ;
BITCOUNT
        : 'B' 'i' 't' 'C' 'o' 'u' 'n' 't' ' ' '=' ' '
        ;
ID
        : 'I' 'D' ' ' '=' ' '
        ;
canMessageEvent
        : float ' ' digits ' ' hexdigits ' ' dir ' ' 'd' ' ' digits ' ' data.opt messageFlags.opt { std::cout << "canMessageEvent (up to v7.2)"; }
        | float ' ' digits ' ' hexdigits ' ' dir ' ' 'd' ' ' digits ' ' data.opt ' ' BITCOUNT digits messageFlags.opt { std::cout << "canMessageEvent (since v7.5)"; }
        | float ' ' digits ' ' hexdigits ' ' dir ' ' 'd' ' ' digits ' ' data.opt ' ' LENGTH digits ' ' BITCOUNT digits messageFlags.opt ' ' ID digits { std::cout << "canMessageEvent (since v8.0)"; }
        ;
canExtendedMessageEvent
        : float ' ' digits ' ' hexdigits 'x' ' ' dir ' ' 'd' ' ' digits ' ' data.opt messageFlags.opt { std::cout << "canExtendedMessageEvent (up to v7.2)"; }
        | float ' ' digits ' ' hexdigits 'x' ' ' dir ' ' 'd' ' ' digits ' ' data.opt ' ' BITCOUNT digits messageFlags.opt { std::cout << "canExtendedMessageEvent (since v7.5)"; }
        | float ' ' digits ' ' hexdigits 'x' ' ' dir ' ' 'd' ' ' digits ' ' data.opt ' ' LENGTH digits ' ' BITCOUNT digits messageFlags.opt ' ' ID digits { std::cout << "canExtendedMessageEvent (since v8.0)"; }
        ;
canRemoteFrameEvent
        : float ' ' digits ' ' hexdigits ' ' dir ' ' 'r' { std::cout << "canRemoteFrameEvent" << std::endl; }
        ;
ERRORFRAME
        : 'E' 'r' 'r' 'o' 'r' 'F' 'r' 'a' 'm' 'e'
        ;
ECC
        : 'E' 'C' 'C' ':' ' '
        ;
FLAGS
        : 'F' 'l' 'a' 'g' 's' ' ' '=' ' ' '0' 'x'
        ;
CODEEXT
        : 'C' 'o' 'd' 'e' 'E' 'x' 't' ' ' '=' ' ' '0' 'x'
        ;
CODE
        : 'C' 'o' 'd' 'e' ' ' '=' ' ' '0' 'x'
        ;
DLC
        : 'D' 'L' 'C' ' ' '=' ' '
        ;
POSITION
        : 'P' 'o' 's' 'i' 't' 'i' 'o' 'n' ' ' '=' ' '
        ;
canErrorFrame
        : float ' ' digits ' ' ERRORFRAME { std::cout << "canErrorFrame (up to v7.2)" << std::endl; }
        | float ' ' digits ' ' ERRORFRAME ' ' ECC bindigits { std::cout << "canErrorFrame (from v7.5 with SJA1000)" << std::endl; }
        | float ' ' digits ' ' ERRORFRAME ' ' FLAGS hexdigits ' ' CODEEXT hexdigits ' ' CODE hexdigits ' ' ID digits ' ' DLC digits ' ' POSITION digits ' ' LENGTH digits { std::cout << "canErrorFrame  (from v7.5 with CAN-Core)" << std::endl; }
        ;
STATISTIC
        : 'S' 't' 'a' 't' 'i' 's' 't' 'i' 'c'
        ;
canBusStatisticsEvent
        : float ' ' digits ' ' STATISTIC ':' ' ' 'D' ' ' digits ' ' 'R' ' ' digits ' ' 'X' 'D' ' ' digits ' ' 'X' 'R' ' ' digits ' ' 'E' ' ' digits ' ' 'O' ' ' digits ' ' 'B' ' ' float '%' { std::cout << "canBusStatisticEvent" << std::endl; }
        ;
CAN
        : 'C' 'A' 'N'
        ;
STATUS
        : 'S' 't' 'a' 't' 'u' 's' ':'
        ;
canErrorEvent
        : float ' ' CAN ' ' digits ' ' STATUS string { std::cout << "canErrorEvent" << std::endl; }
        ;
OVERLOADFRAME
        : 'O' 'v' 'e' 'r' 'l' 'o' 'a' 'd' 'F' 'r' 'a' 'm' 'e'
        ;
canOverloadFrameEvent
        : float ' ' digits ' ' OVERLOADFRAME { std::cout << "canOverloadFrameEvent" << std::endl; }
        ;

    /* CAN FD Events */
CANFD
        : 'C' 'A' 'N' 'F' 'D'
        ;
symbolicName.opt
        : %empty
        | ' ' string
canFdMessageEvent
        : float ' ' CANFD ' ' hexdigits ' ' dir ' ' hexdigits symbolicName.opt ' ' bindigit ' ' bindigit ' ' hexdigits ' ' digits data ' ' digits ' ' digits ' ' digits ' ' hexdigits ' ' hexdigits ' ' hexdigits { std::cout << "canFdMessageEvent (since v8.1)" << std::endl; }
        ;
canFdExtendedMessageEvent
        : float ' ' CANFD ' ' hexdigits 'x' ' ' dir ' ' hexdigits symbolicName.opt ' ' bindigit ' ' bindigit ' ' hexdigits ' ' digits data ' ' digits ' ' digits ' ' digits ' ' hexdigits ' ' hexdigits ' ' hexdigits { std::cout << "canFdExtendedMessageEvent (since v8.1)" << std::endl; }
        ;
canFdErrorFrame
        : float ' ' CANFD ' ' digits ' ' dir ' ' ERRORFRAME ' ' string ' ' hexdigits ' ' hexdigits { std::cout << "canFdErrorFrame" << std::endl; }
        ;
// @todo canFdBusStatisticsEvent
// @todo canFdOverloadFrame

    /* Log and Trigger Events */
LOG_TRIGGER_EVENT
        : 'l' 'o' 'g' ' ' 't' 'r' 'i' 'g' 'g' 'e' 'r' ' ' 'e' 'v' 'e' 'n' 't'
        ;
logTriggerEvent
        : float ' ' LOG_TRIGGER_EVENT { std::cout << "logTriggerEvent" << std::endl; }
        ;
LOG_DIRECT_START
        : 'l' 'o' 'g' ' ' 'd' 'i' 'r' 'e' 'c' 't' ' ' 's' 't' 'a' 'r' 't'
        ;
logDirectStartEvent
        : float ' ' LOG_DIRECT_START ' ' '(' digits 'm' 's' ')' { std::cout << "logDirectStartEvent" << std::endl; }
        ;
LOG_DIRECT_STOP
        : 'l' 'o' 'g' ' ' 'd' 'i' 'r' 'e' 'c' 't' ' ' 's' 't' 'o' 'p'
        ;
logDirectStopEvent
        : float ' ' LOG_DIRECT_STOP ' ' '(' digits 'm' 's' ')' { std::cout << "logDirectStopEvent" << std::endl; }
        ;
BEGIN_TRIGGERBLOCK
        : 'B' 'e' 'g' 'i' 'n' ' ' 'T' 'r' 'i' 'g' 'g' 'e' 'r' 'b' 'l' 'o' 'c' 'k'
        ;
beginTriggerblockEvent
        : BEGIN_TRIGGERBLOCK ' ' weekDay ' ' month ' ' digits ' ' fullTime ' ' year { std::cout << "beginTriggerblockEvent" << std::endl; }
        ;
END_TRIGGERBLOCK
        : 'E' 'n' 'd' ' ' 'T' 'r' 'i' 'g' 'g' 'e' 'r' 'B' 'l' 'o' 'c' 'k'
        ;
endTriggerblockEvent
        : END_TRIGGERBLOCK { std::cout << "endTriggerblockEvent" << std::endl; }
        ;

    /* Environment Variables */
environmentVariablesEvent
        : float ' ' 'I' 'n' 't' '_' 'E' 'v' ' ' ':' '=' ' ' digits { std::cout << "environmentVariablesEvent (Int)" << std::endl; }
        | float ' ' 'F' 'l' 'o' 'a' 't' '_' 'E' 'v' ' ' ':' '=' ' ' float { std::cout << "environmentVariablesEvent (Float)" << std::endl; }
        | float ' ' 'S' 't' 'r' 'i' 'n' 'g' '_' 'E' 'v' ' ' ':' '=' ' ' '"' string '"' { std::cout << "environmentVariablesEvent (String)" << std::endl; }
        | float ' ' 'D' 'a' 't' 'a' '_' 'E' 'v' ' ' ':' '=' ' ' '[' data.opt ' ' ']' { std::cout << "environmentVariablesEvent (Data)" << std::endl; }
        ;

    /* System Variables */
SV
        : 'S' 'V' ':'
        ;
systemVariablesEvent
        : float ' ' SV ' ' digits ' ' digits ' ' digits ' ' string ':' ':' 'I' 'n' 't' 'V' 'a' 'r' ' ' '=' ' ' digits { std::cout << "systemVariablesEvent IntVar" << std::endl; }
        | float ' ' SV ' ' digits ' ' digits ' ' digits ' ' string ':' ':' 'F' 'l' 'o' 'a' 't' 'V' 'a' 'r' ' ' '=' ' ' float { std::cout << "systemVariablesEvent FloatVar" << std::endl; }
        | float ' ' SV ' ' digits ' ' digits ' ' digits ' ' string ':' ':' 'S' 't' 'r' 'i' 'n' 'g' 'V' 'a' 'r' ' ' '=' ' ' '"' string '"' { std::cout << "systemVariablesEvent StringVar" << std::endl; }
        | float ' ' SV ' ' digits ' ' digits ' ' digits ' ' string ':' ':' 'I' 'n' 't' 'A' 'r' 'r' 'a' 'y' ' ' '=' 'A' digits hexArray { std::cout << "systemVariablesEvent IntArray" << std::endl; }
        | float ' ' SV ' ' digits ' ' digits ' ' digits ' ' string ':' ':' 'F' 'l' 'o' 'a' 't' 'A' 'r' 'r' 'a' 'y' ' ' '=' 'D' digits floatArray { std::cout << "systemVariablesEvent FloatArray" << std::endl; }
        ;

    /* Macros Signal Events */
macroSignalEvent
        : float digits digits "=" digits { std::cout << "macroSignalEvent" << std::endl; }
        | float digits digits "=" digits { std::cout << "macroSignalEvent" << std::endl; }
        ;

    /* GPS events */
GPS_DEVICE
        : 'G' 'P' 'S' '-' 'D' 'e' 'v' 'i' 'c' 'e' ':' ' '
        ;
LA
        : 'L' 'a' ':' ' '
        ;
LO
        : 'L' 'o' ':' ' '
        ;
ALT
        : 'A' 'l' 't' ':' ' '
        ;
SP
        : 'S' 'p' ':' ' '
        ;
CO
        : 'C' 'o' ':' ' '
        ;

gpsEvent
        : float ' ' GPS_DEVICE digits ' ' LA float ' ' LO float ' ' ALT float ' ' SP float ' ' CO float { std::cout << "gpsEvent" << std::endl; }
        ;

    /* Comment events */
COMMENT
        : 'C' 'o' 'm' 'm' 'e' 'n' 't' ':'
        ;
commentEvent
        : float ' ' COMMENT ' ' digits ' ' string { std::cout << "commentEvent" << std::endl; }
        ;

    /* Global marker events */
GMGROUP
        : 'G' 'M' 'G' 'r' 'o' 'u' 'p' ':' ' '
        ;
GMMARKER
        : 'G' 'M' 'M' 'a' 'r' 'k' 'e' 'r' ':' ' '
        ;
GMDESCRIPTION
        : 'G' 'M' 'D' 'e' 's' 'c' 'r' 'i' 'p' 't' 'i' 'o' 'n' ':' ' '
        ;
globalMarkerEvent
        : float ' ' digits ' ' digits ' ' digits ' ' digits ' ' GMGROUP string ' ' GMMARKER string ' ' GMDESCRIPTION string { std::cout << "globalMarkerEvent" << std::endl; }
        ;

    /* Ethernet events */
ETH
        : 'E' 'T' 'H'
        ;
STAT
        : 'S' 'T' 'A' 'T'
        ;
LINK
        : 'L' 'i' 'n' 'k' ':'
        ;
LINKSPEED
        : 'L' 'i' 'n' 'k' 'S' 'p' 'e' 'e' 'd' ':'
        ;
PHYSICAL
        : 'P' 'h' 'y' 's' 'i' 'c' 'a' 'l' ':'
        ;
DUPLEX
        : 'D' 'u' 'p' 'l' 'e' 'x' ':'
        ;
MDI
        : 'M' 'D' 'I' ':'
        ;
CONNECTOR
        : 'C' 'o' 'n' 'n' 'e' 'c' 't' 'o' 'r' ':'
        ;
RXER
        : 'R' 'x' 'E' 'r'
        ;
ethernetPacket
        : float ' ' ETH ' ' digits ' ' dir ' ' hexdigits ':' hexdigits { std::cout << "ethernetPacket" << std::endl; }
        ;
ethernetStatus
        : float ' ' ETH ' ' digits ' ' STAT ' ' LINK string ' ' LINKSPEED string ' ' PHYSICAL string ' ' DUPLEX string ' ' MDI string ' ' CONNECTOR string { std::cout << "ethernetStatus" << std::endl; }
        ;
ethernetRxError
        : float ' ' ETH ' ' digits ' ' RXER ' ' digits ' ' digits ' ' hexdigits ':' hexdigits { std::cout << "ethernetRxError" << std::endl; }
        ;

    /* AFDX events */
AFDX
        : 'A' 'F' 'D' 'X'
        ;
afdxPacket
        : float ' ' AFDX ' ' digits ' ' dir ' ' digits ' ' digits ' ' digits ' ' hexdigits ':' hexdigits { std::cout << "afdxPacket" << std::endl; }
        ;

    /* FlexRay events (Old Format) */
FR
        : 'F' 'r'
        ;
flexRayChannel
        : '*'
        | digits
        ;
flexRayTyp
        : 'V' '9'
        | 'S' 't' 'a' 'r' 't' 'C' 'y' 'c' 'l' 'e' 'E' 'v' 'e' 'n' 't'
        | 'E' 'r' 'r' 'o' 'r' 'F' 'r' 'a' 'm' 'e'
        ;
flexRayOldMessageEvent
        : float ' ' FR ' ' flexRayChannel ' ' flexRayTyp ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' string ' ' digits data.opt ' ' 'x' ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits { std::cout << "flexRayMessageEvent" << std::endl; }
        ;
NM_VECTOR
        : 'N' 'M' ' ' 'V' 'e' 'c' 't' 'o' 'r' ':' ' '
        ;
flexRayOldStartCycleEvent
        : float ' ' FR ' ' flexRayChannel ' ' flexRayTyp ' ' NM_VECTOR digits data.opt { std::cout << "flexRayOldStartCycleEvent" << std::endl; }
        ;

    /* FlexRay events (New Format) */
RMSG
        : 'R' 'M' 'S' 'G'
        ;
PDU
        : 'P' 'D' 'U'
        ;
flexRayMessageEvent
        : float ' ' FR ' ' RMSG ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' dir ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' string ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits { std::cout << "flexRayMessageEvent (RMSG)" << std::endl; }
        | float ' ' FR ' ' PDU ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' dir ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' string ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits { std::cout << "flexRayMessageEvent (PDU)" << std::endl; }
        ;
SCE
        : 'S' 'C' 'E'
        ;
NM_VECTOR
        : 'N' 'M' '_' 'V' 'e' 'c' 't' 'o' 'r' ':' ' '
        ;
flexRayStartCycleEvent
        : float ' ' FR ' ' SCE ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' dir ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' NM_VECTOR digits { std::cout << "flexRayStartCycleEvent (SCE)" << std::endl; }
        ;
SE
        : 'S' 'E'
        ;
flexRayStatusEvent
        : float ' ' FR ' ' SE ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' { std::cout << "flexRayStatusEvent (SE)" << std::endl; }
        ;
EE
        : 'E' 'E'
        ;
flexRayErrorEvent
        : float ' ' FR ' ' EE ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits { std::cout << "flexRayErrorEvent (EE)" << std::endl; }
        ;

    /* K-Line events */
COM
        : 'C' 'O' 'M'
        ;
kLineByteEvent
        : float ' ' COM digits ' ' dir ' ' digits ' ' digits data.opt { std::cout << "kLineByteEvent" << std::endl; }
        ;
KLINE
        : '/' '/' ' ' 'K' '-' 'L' 'i' 'n' 'e' ':' ' '
        ;
kLineMessageEvent
        : KLINE float ' ' COM digits ' ' dir ' ' digits ' ' digits ' ' digits ' ' digits data.opt { std::cout << "kLineMessageEvent" << std::endl; }
        ;

    /* LIN Events */
LI
        : 'L' 'i'
        ;
CHECKSUM
        : 'c' 'h' 'e' 'c' 'k' 's' 'u' 'm' ' ' '=' ' '
        ;
HEADER_TIME
        : 'h' 'e' 'a' 'd' 'e' 'r' ' ' 't' 'i' 'm' 'e' ' ' '=' ' '
        ;
FULL_TIME
        : 'f' 'u' 'l' 'l' ' ' 't' 'i' 'm' 'e' ' ' '=' ' '
        ;
SOF
        : 'S' 'O' 'F' ' ' '=' ' '
        ;
BR
        : 'B' 'R' ' ' '=' ' '
        ;
BREAK
        : 'b' 'r' 'e' 'a' 'k' ' ' '=' ' '
        ;
EOH
        : 'E' 'O' 'H' ' ' '=' ' '
        ;
EOB
        : 'E' 'O' 'B' ' ' '=' ' '
        ;
SIM
        : 's' 'i' 'm' ' ' '=' ' '
        ;
EOF
        : 'E' 'O' 'F' ' ' '=' ' '
        ;
RBR
        : 'R' 'B' 'R' ' ' '=' ' '
        ;
HBR
        : 'H' 'B' 'R' ' ' '=' ' '
        ;
HSO
        : 'H' 'S' 'O' ' ' '=' ' '
        ;
RSO
        : 'R' 'S' 'O' ' ' '=' ' '
        ;
CSM
        : 'C' 'S' 'M' ' ' '=' ' '
        ;
csm
        : 'u' 'n' 'k' 'n' 'o' 'w' 'n'
        | 'c' 'l' 'a' 's' 's' 'i' 'c'
        | 'e' 'n' 'h' 'a' 'n' 'c' 'e' 'd'
        | 'e' 'r' 'r' 'o' 'r'
        ;
linMessage
        : float ' ' LI ' ' hexdigits ' ' dir ' ' digits data.opt ' ' CHECKSUM digits ' ' HEADER_TIME digits ',' ' ' FULL_TIME digits ' ' SOF float ' ' BR digits ' 'BREAK digits ' 'digits ' ' EOH float ' ' EOB float ' ' float ' ' float ' ' float ' ' float ' ' float ' ' float ' ' float ' ' SIM bindigit ' ' EOF float ' ' RBR digits ' ' HBR float ' ' HSO digits ' ' RSO digits ' ' CSM csm { std::cout << "linMessage" << std::endl; }
        ;

    /* LIN Error Events */
TRANSMERR
        : 'T' 'r' 'a' 'n' 's' 'm' 'E' 'r' 'r'
        ;
linTransmissionError
        : float ' ' LI ' ' hexdigits ' ' TRANSMERR ' ' HEADER_TIME digits ',' ' ' FULL_TIME digits ' ' SOF float ' ' BR digits ' ' BREAK digits ' ' digits ' ' EOH float ' ' HBR float ' ' HSO digits ' ' CSM ' ' csm { std::cout << "linTransmissionError" << std::endl; }
        ;
RCVERROR
        : 'R' 'c' 'v' 'E' 'r' 'r' 'o' 'r' ':' ' '
        ;
STATEREASON
        : 'S' 't' 'a' 't' 'e' 'R' 'e' 'a' 's' 'o' 'n' ' ' '=' ' '
        ;
SHORTERROR
        : 'S' 'h' 'o' 'r' 't' 'E' 'r' 'r' 'o' 'r' ' ' '=' ' '
        ;
DLCTIMEOUT
        : 'D' 'l' 'c' 'T' 'i' 'm' 'e' 'o' 'u' 't' ' ' '=' ' '
        ;
HASDATABYTES
        : 'H' 'a' 's' 'D' 'a' 't' 'a' 'b' 'y' 't' 'e' 's' ' ' '=' ' '
        ;
linReceiveError
        : float ' ' LI ' ' hexdigits ' ' digits ' ' RCVERROR string ' ' STATEREASON hexdigits ' ' SHORTERROR digits ' ' DLCTIMEOUT digits ' ' HASDATABYTES bindigit data.opt ' ' SOF float ' ' BR digits ' ' BREAK digits ' ' digits EOH float ' ' EOB float ' ' float ' ' float ' ' float ' ' float ' ' float ' ' float ' ' float ' ' RBR digits ' ' RSO digits ' ' HBR float ' ' HSO digits ' ' CSM csm { std::cout << "linReceiveError" << std::endl; }
        ;
SYNCERROR
        : 'S' 'y' 'n' 'c' 'E' 'r' 'r' 'o' 'r'
        ;
linSyncError
        : float ' ' 'L' digits ' ' SYNCERROR ' ' digits ' ' digits ' ' digits ' ' digits ' ' SOF float ' ' BR digits ' ' BREAK digits ' ' digits { std::cout << "linSyncError" << std::endl; }
        ;
CSERR
        : 'C' 'S' 'E' 'r' 'r'
        ;
linChecksumError
        : float ' ' LI ' ' digits ' ' CSERR ' ' dir ' ' digits data.opt ' ' CHECKSUM digits ' ' HEADER_TIME digits ',' ' ' FULL_TIME digits ' ' SOF float ' ' BR digits ' ' BREAK digits ' ' digits ' ' EOH float ' ' EOB float ' ' float ' ' float ' ' float ' ' float ' ' float ' ' float ' ' float ' ' SIM bindigit ' ' EOF float ' ' RBR digits ' ' HBR float ' ' HSO digits ' ' RSO digits ' ' CSM csm { std::cout << "linChecksumError" << std::endl; }
        ;
SPIKE
        : 'S' 'p' 'i' 'k' 'e'
        ;
MICROSECONDS
        : 'm' 'i' 'c' 'r' 'o' 's' 'e' 'c' 'o' 'n' 'd' 's'
        ;
linSpikeEvent
        : float ' ' 'L' digits ' ' SPIKE ' ' dir ' ' digits ' ' MICROSECONDS { std::cout << "linSpikeEvent (up to v6.0)" << std::endl; }
        | float ' ' 'L' digits ' ' SPIKE ' ' dir ' ' digits ' ' MICROSECONDS ' ' SOF float ' ' BR digits { std::cout << "linSpikeEvent (from v6.1)" << std::endl; }
        ;
DOMINANT_SIGNAL
        : 'D' 'o' 'm' 'i' 'n' 'a' 'n' 't' ' ' 's' 'i' 'g' 'n' 'a' 'l'
        ;
domSigState
        : DOMINANT_SIGNAL ' ' 'd' 'e' 't' 'e' 'c' 't' 'e' 'd'
        | DOMINANT_SIGNAL ' ' 'f' 'i' 'n' 'i' 's' 'h' 'e' 'd'
        ;
linDominantSignal
        : float ' ' LI ' ' domSigState ' ' digits ' ' MICROSECONDS { std::cout << "linDominantSignal (up to v6.0)" << std::endl; }
        | float ' ' LI ' ' domSigState ' ' digits ' ' MICROSECONDS ' ' SOF float ' ' BR digits { std::cout << "linDominantSignal (from v6.1)" << std::endl; }
        ;

    /* LIN Info Events */
BAUDRATE
        : 'B' 'a' 'u' 'd' 'r' 'a' 't' 'e' ' '
        ;
linBaudrate
        : float ' ' LI ' ' BAUDRATE digits { std::cout << "linBaudrate" << std::endl; }
        ;
DLCINFO
        : 'D' 'l' 'c' 'I' 'n' 'f' 'o' ' '
        ;
linDlcInfo
        : float ' ' LI ' ' digits ' ' DLCINFO digits { std::cout << "linDlcInfo" << std::endl; }
        ;
CSINFO
        : 'C' 'S' 'I' 'n' 'f' 'o'
        ;
usingClassicEnhancedChecksum
        : 'U' 's' 'i' 'n' 'g' ' ' 'c' 'l' 'a' 's' 's' 'i' 'c' ' ' 'c' 'h' 'e' 'c' 'k' 's' 'u' 'm'
        | 'U' 's' 'i' 'n' 'g' ' ' 'e' 'n' 'h' 'a' 'n' 'c' 'e' 'd' ' ' 'c' 'h' 'e' 'c' 'k' 's' 'u' 'm'
        ;
linChecksumInfo
        : float ' ' LI ' ' digits ' ' CSINFO ' ' usingClassicEnhancedChecksum { std::cout << "linDominantSignal" << std::endl; }
        ;
SCHEDMODCHNG
        : 'S' 'c' 'h' 'e' 'd' 'M' 'o' 'd' 'C' 'h' 'n' 'g'
        ;
PRIOR_SCHEDULER_MODE
        : 'p' 'r' 'i' 'o' 'r' ' ' 's' 'c' 'h' 'e' 'd' 'u' 'l' 'e' 'r' ' ' 'm' 'o' 'd' 'e' ' ' '=' ' '
        ;
NEXT_SCHEDULER_MODE
        : 'n' 'e' 'x' 't' ' ' 's' 'c' 'h' 'e' 'd' 'u' 'l' 'e' 'r' ' ' 'm' 'o' 'd' 'e' ' ' '=' ' '
        ;
linSchedulerModeChange
        : float ' ' LI ' ' SCHEDMODCHNG ' ' PRIOR_SCHEDULER_MODE digits ',' ' ' NEXT_SCHEDULER_MODE digits { std::cout << "linSchedulerModeChange" << std::endl; }
        ;
SLAVETIMEOUT
        : 'S' 'l' 'a' 'v' 'e' 'T' 'i' 'm' 'e' 'o' 'u' 't'
        ;
SLAVE_ID
        : 's' 'l' 'a' 'v' 'e' '-' 'i' 'd' ' ' '=' ' '
        ;
CURRENT_STATE
        : 'c' 'u' 'r' 'r' 'e' 'n' 't' ' ' 's' 't' 'a' 't' 'e' ' ' '=' ' '
        ;
FOLLOWING_STATE
        : 'f' 'o' 'l' 'l' 'o' 'w' 'i' 'n' 'g' ' ' 's' 't' 'a' 't' 'e' ' ' '=' ' '
        ;
linSlaveTimeout
        : float ' ' LI ' ' SLAVETIMEOUT ' ' SLAVE_ID digits ',' ' ' CURRENT_STATE digits ',' ' ' FOLLOWING_STATE digits { std::cout << "linSlaveTimeout" << std::endl; }
        ;
EVTRIGFRMINFO
        : 'E' 'v' 'T' 'r' 'g' 'F' 'r' 'm' 'I' 'n' 'f' 'o'
        ;
linEventTriggeredFrameInfo
        : float ' ' LI ' ' EVTRIGFRMINFO ' ' string ' ' string { std::cout << "linEventTriggeredFrameInfo" << std::endl; }
        ;
linStatisticInfo
        : float ' ' LI ' ' STATISTIC ' ' digits ' ' float ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits { std::cout << "linStatisticInfo" << std::endl; }
        ;
SHORTORSLOWRESPONSE
        : 'S' 'h' 'o' 'r' 't' 'O' 'r' 'S' 'l' 'o' 'w' 'R' 'e' 's' 'p' 'o' 'n' 's' 'e' ':'
        ;
NUMRESPBYTES
        : 'N' 'u' 'm' 'R' 'e' 's' 'p' 'B' 'y' 't' 'e' 's' ' ' '=' ' '
        ;
SLOWRESPONSE
        : 'S' 'l' 'o' 'w' 'R' 'e' 's' 'p' 'o' 'n' 's' 'e' ' ' '=' ' '
        ;
INTERRUPTEDBYBREAK
        : 'I' 'n' 't' 'e' 'r' 'r' 'u' 'p' 't' 'e' 'd' 'B' 'y' 'B' 'r' 'e' 'a' 'k' ' ' '=' ' '
        ;
linShortOrSlowResponse
        : float ' ' LI ' ' digits ' ' SHORTORSLOWRESPONSE ' ' NUMRESPBYTES digits data.opt ' ' SLOWRESPONSE bindigit ' ' INTERRUPTEDBYBREAK bindigit ' ' SOF float ' ' BR ' ' digits ' ' BREAK digits ' ' digits ' ' EOH float ' ' EOB float ' ' float ' ' float ' ' float ' ' float ' ' float ' ' float ' ' float ' ' HBR float ' ' HSO digits ' ' CSM csm { std::cout << "linShortOrSlowResponse" << std::endl; }
        ;
DISTURBANCEEVENT
        : 'D' 'i' 's' 't' 'u' 'r' 'b' 'a' 'n' 'c' 'e' 'E' 'v' 'e' 'n' 't'
        ;
TYPE
        : 'T' 'y' 'p' 'e' ' ' '=' ' '
        ;
type
        : 'd' 'o' 'm' 'i' 'n' 'a' 'n' 't'
        ;
BYTEINDEX
        : 'B' 'y' 't' 'e' 'I' 'n' 'd' 'e' 'x' ' ' '=' ' '
        ;
BITINDEX
        : 'B' 'i' 't' 'I' 'n' 'd' 'e' 'x' ' ' '=' ' '
        ;
BITOFFSET
        : 'B' 'i' 't' 'O' 'f' 'f' 's' 'e' 't' ' ' '=' ' '
        ;
HEADER
        : 'H' 'e' 'a' 'd' 'e' 'r' ' ' '=' ' '
        ;
DISTURBING_HEADER
        : 'D' 'i' 's' 't' 'u' 'r' 'b' 'i' 'n' 'g' ' ' 'h' 'e' 'a' 'd' 'e' 'r' ' ' '=' ' '
        ;
linDisturbanceEvent
        : float ' ' LI ' ' DISTURBANCEEVENT ' ' TYPE type ' ' BYTEINDEX digits ' ' BITINDEX digits ' ' BITOFFSET digits ' ' LENGTH digits ' ' HEADER hexdigits ' ' DISTURBING_HEADER hexdigits { std::cout << "linDisturbanceEvent" << std::endl; }
        ;

    /* LIN Sleep/Wakeup Events */
SLEEPMODEEVENT
        : 'S' 'l' 'e' 'e' 'p' 'M' 'o' 'd' 'e' 'E' 'v' 'e' 'n' 't'
        ;
linSleepMode
        : float ' ' LI ' ' SLEEPMODEEVENT ' ' bindigits ' ' string { std::cout << "linSleepMode" << std::endl; }
        ;
WAKEUPFRAME
        : 'W' 'a' 'k' 'e' 'u' 'p' 'F' 'r' 'a' 'm' 'e'
        ;
LENGTHCODE
        : 'L' 'e' 'n' 'g' 't' 'h' 'C' 'o' 'd' 'e' ' ' '=' ' '
        ;
linWakeupFrame
        : float ' ' LI ' ' WAKEUPFRAME ' ' dir ' ' digits { std::cout << "linWakeupFrame (up to v6.0)" << std::endl; }
        | float ' ' LI ' ' WAKEUPFRAME ' ' dir ' ' digits ' ' SOF digits ' ' BR digits ' ' LENGTHCODE digits { std::cout << "linWakeupFrame (from v6.1)" << std::endl; }
        ;
UNEXPECTED_WAKEUP
        : 'U' 'n' 'e' 'x' 'p' 'e' 'c' 't' 'e' 'd' ' ' 'w' 'a' 'k' 'e' 'u' 'p' ':'
        ;
SIGNAL
        : 'S' 'i' 'g' 'n' 'a' 'l' ' ' '=' ' '
        ;
APPROX
        : 'a' 'p' 'p' 'r' 'o' 'x' '.'
        ;
US
        : 'u' 's'
        ;
linUnexpectedWakeup
        : float ' ' LI ' ' UNEXPECTED_WAKEUP ' ' SIGNAL digits ' ' SOF float ' ' BR digits { std::cout << "linUnexpectedWakeup (for LIN 2.x)" << std::endl; }
        | float ' ' LI ' ' UNEXPECTED_WAKEUP ' ' APPROX ' ' digits ' ' US ' ' SOF float ' ' BR digits { std::cout << "linUnexpectedWakeup (for LIN 1.x)" << std::endl; }
        ;

    /* MOST Events */
most25ControlMessageNodeMode
        : float ' ' 'M' digits ' ' dir ' ' digits ' ' digits ' ' digits data ' ' digits { std::cout << "most25ControlMessageNodeMode" << std::endl; }
        ;
most25ControlMessageSpyMode
        : float ' ' 'M' digits ' ' dir ' ' digits ' ' digits ' ' digits data ' ' digits ' ' digits ' ' hexdigits { std::cout << "most25ControlMessageSpyMode" << std::endl; }
        ;
PKT
        : 'P' 'k' 't' ':'
most25Packet
        : float ' ' 'M' digits ' ' PKT ' ' dir ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' hexdigits data { std::cout << "most25Packet" << std::endl; }
        ;
LL
        : 'L' 'L' ':'
        ;
mostLightLockEvent
        : float ' ' 'M' digits ' ' LL ' ' bindigit { std::cout << "mostLightLockEvent" << std::endl; }
        ;
REGISTER
        : 'R' 'e' 'g' 'i' 's' 't' 'e' 'r' ':'
        ;
mostSpecialRegisterEvent
        : float ' ' 'M' digits ' ' REGISTER ' ' digits ' ' hexdigits ' ' hexdigits { std::cout << "mostSpecialRegisterEvent" << std::endl; }
        ;
REGDATA
        : 'R' 'e' 'g' 'D' 'a' 't' 'a' ':'
        ;
mostCommonRegisterEvent
        : float ' ' 'M' digits ' ' REGDATA ' ' digits ' ' digits ' ' digits ' ' digits data { std::cout << "mostCommonRegisterEvent" << std::endl; }
        ;
HWMODE
        : 'H' 'W' 'M' 'o' 'd' 'e' ':'
mostHwModeEvent
        : float ' ' 'M' digits ' ' HWMODE ' ' digits ' ' digits { std::cout << "mostHwModeEvent" << std::endl; }
        ;
NETSTATE
        : 'N' 'e' 't' 'S' 't' 'a' 't' 'e' ':'
        ;
mostNetStateEvent
        : float ' ' 'M' digits ' ' NETSTATE ' ' digits ' ' digits { std::cout << "mostNetStateEvent" << std::endl; }
        ;
DATALOST
        : 'D' 'a' 't' 'a' 'L' 'o' 's' 't' ':'
        ;
mostDataLostEvent
        : float ' ' 'M' digits ' ' DATALOST ' ' digits ' ' hexdigits ' ' hexdigits ' ' float ' ' float { std::cout << "mostDataLostEvent" << std::endl; }
        ;
TRIGGER
        : 'T' 'r' 'i' 'g' 'g' 'e' 'r' ':'
        ;
mostTriggerEvent
        : float ' ' 'M' digits ' ' TRIGGER ' ' digits ' ' digits ' ' digits ' ' digits { std::cout << "mostTriggerEvent" << std::endl; }
        ;
MOSTSTATISTIC
        : 'M' 'o' 's' 't' 'S' 't' 'a' 't' 'i' 's' 't' 'i' 'c' ':'
        ;
FR
        : 'F' 'r' ':' ' '
        ;
LT
        : 'L' 't' ':' ' '
        ;
BL
        : 'B' 'l' ':' ' '
        ;
PK
        : 'P' 'k' ':' ' '
        ;
mostStatisticEvent
        : float ' ' 'M' digits ' ' MOSTSTATISTIC ' ' FR digits ' ' LT digits ' ' BL digits ' ' PK digits { std::cout << "mostStatisticEvent" << std::endl; }
        ;
STATEX
        : 'S' 't' 'a' 't' 'E' 'x' ':'
        ;
mostStatisticExtendedEvent
        : float ' ' 'M' digits ' ' STATEX ' ' hexdigits ' ' hexdigits { std::cout << "mostStatisticExtendedEvent" << std::endl; }
        ;
TXLIGHT
        : 'T' 'x' 'L' 'i' 'g' 'h' 't' ':'
        ;
mostTxLight
        : float ' ' 'M' digits ' ' TXLIGHT ' ' bindigit { std::cout << "mostTxLight" << std::endl; }
        ;
STRESS
        : 'S' 't' 'r' 'e' 's' 's' ':'
        ;
mostStressEvent
        : float ' ' 'M' digits ' ' STRESS ' ' digits ' ' digits { std::cout << "mostStressEvent" << std::endl; }
        ;
ALLOCTAB
        : 'A' 'l' 'l' 'o' 'c' 'T' 'a' 'b' ':'
        ;
most25AllocTable
        : float ' ' 'M' digits ' ' ALLOCTAB ' ' digits data.opt { std::cout << "most25AllocTable" << std::endl; }
        ;
MSG150
        : 'M' 's' 'g' '1' '5' '0' ':'
        ;
most150ControlMessage
        : float ' ' 'M' digits ' ' MSG150 ' ' dir ' ' hexdigits ' ' hexdigits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' hexdigits ' ' digits ' ' digits ' ' digits data.opt { std::cout << "most150ControlMessage" << std::endl; }
        ;
MSG150FRG
        : 'M' 's' 'g' '1' '5' '0' 'F' 'r' 'g' ':'
        ;
most150ControlMessageFragment
        : float ' ' 'M' digits ' ' MSG150FRG ' ' dir ' ' hexdigits ' ' hexdigits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' hexdigits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits data { std::cout << "most150ControlMessageFragment" << std::endl; }
        ;
PKT150
        : 'P' 'k' 't' '1' '5' '0' ':'
        ;
most150Packet
        : float ' ' 'M' digits ' ' PKT150 ' ' dir ' ' hexdigits ' ' hexdigits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' hexdigits ' ' digits ' ' digits ' ' digits data { std::cout << "most150Packet" << std::endl; }
        ;
PKT150FRG
        : 'P' 'k' 't' '1' '5' '0' 'F' 'r' 'g' ':'
        ;
most150PacketFragment
        : float ' ' 'M' digits ' ' PKT150FRG ' ' dir ' ' digits ' ' hexdigits ' ' hexdigits ' ' digits ' ' digits ' ' digits ' ' digits ' ' hexdigits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits data { std::cout << "most150PacketFragment" << std::endl; }
        ;
PKTETH
        : 'P' 'k' 't' 'E' 't' 'h' ':'
        ;
mostEthernetPacket
        : float ' ' 'M' digits ' ' PKTETH ' ' dir ' ' hexdigits ' ' hexdigits ' ' digits ' ' digits ' ' digits ' ' digits ' ' hexdigits ' ' digits ' ' digits ' ' digits ' ' data { std::cout << "mostEthernetPacket" << std::endl; }
        ;
PKTETHFRG
        : 'P' 'k' 't' 'E' 't' 'h' 'F' 'r' 'g' ':'
        ;
mostEthernetPacketFragment
        : float ' ' 'M' digits ' ' PKTETHFRG ' 'digits ' ' hexdigits ' ' hexdigits ' ' digits ' ' digits ' ' hexdigits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits data { std::cout << "mostEthernetPacketFragment" << std::endl; }
        ;
SYSTEM
        : 'S' 'y' 's' 't' 'e' 'm' ':'
        ;
mostSystemEvent
        : float ' ' 'M' digits ' ' SYSTEM ' ' digits ' ' digits ' ' digits { std::cout << "mostSystemEvent" << std::endl; }
        ;
AT150
        : 'A' 'T' '1' '5' '0' ':'
        ;
most150AllocTable
        : float ' ' 'M' digits ' ' AT150 ' ' digits ' ' hexdigits ' ' hexdigits data.opt { std::cout << "most150AllocTable" << std::endl; }
        ;
MSG50
        : 'M' 's' 'g' '5' '0' ':'
        ;
most50ControlMessage
        : float ' ' 'M' digits ' ' MSG50 ' ' dir ' ' hexdigits ' ' hexdigits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' hexdigits ' ' digits ' ' digits ' ' digits data { std::cout << "most50ControlMessage" << std::endl; }
        ;
PKT50
        : 'P' 'k' 't' '5' '0' ':'
        ;
most50Packet
        : float ' ' 'M' digits ' ' PKT50 ' ' dir ' ' hexdigits ' ' hexdigits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' digits ' ' hexdigits ' ' digits ' ' digits ' ' digits data { std::cout << "most50Packet" << std::endl; }
        ;
ECL
        : 'E' 'c' 'l' ':'
        ;
mostEcl
        : float ' ' 'M' digits ' ' ECL ' ' bindigit ' ' bindigit { std::cout << "mostEcl" << std::endl; }
        ;

    /* TP/Diagnostics events */
tpDiagPrefix
        : '/' '/' ' ' digits ' ' 'O' 'T' 'P' '(' digits ')' ' ' string ' ' string '-' '>' digits ':' { std::cout << "tpDiagPrefix" << std::endl; }
        ;
SF_LENGTH
        : 'S' 'F' ' ' 'L' 'e' 'n' 'g' 't' 'h' ':'
        ;
tpDiagSingleFrame
        : SF_LENGTH ' ' hexdigits ' ' '[' data.opt ' ' ']' { std::cout << "tpDiagSingleFrame" << std::endl; }
        ;
FF_LENGTH
        : 'F' 'F' ' ' 'L' 'e' 'n' 'g' 't' 'h' ':'
        ;
tpDiagFirstFrame
        : FF_LENGTH ' ' hexdigits ' ' '[' data.opt ' ' ']' { std::cout << "tpDiagFirstFrame" << std::endl; }
        ;
CF_SEQ_NR
        : 'C' 'F' ' ' 'S' 'e' 'q' '.' 'N' 'r' '.' ':'
        ;
tpDiagConsecutiveFrame
        : CF_SEQ_NR ' ' hexdigits ' ' '[' data.opt ' ' ']' { std::cout << "tpDiagConsecutiveFrame" << std::endl; }
        ;
FC_CTS
        : 'F' 'C' '.' 'C' 'T' 'S' ':'
        ;
BSMAX
        : 'B' 'S' 'm' 'a' 'x' ':' ' ' '0' 'x'
        ;
STMIN
        : 'S' 'T' 'm' 'i' 'n' ':' ' ' '0' 'x'
        ;
MS
        : 'm' 's'
        ;
tpDiagFlowControlFrame
        : FC_CTS ' ' BSMAX hexdigits ',' ' ' STMIN hexdigits ' ' MS { std::cout << "tpDiagFlowControlFrame" << std::endl; }
        ;
DIAGREQUEST
        : 'D' 'i' 'a' 'g' 'R' 'e' 'q' 'u' 'e' 's' 't'
        ;
tpDiagRequest
        : float ' ' DIAGREQUEST '[' string ']' data { std::cout << "tpDiagRequest" << std::endl; }
        ;

%%

void Vector::ASC::Parser::error(const location_type & location, const std::string & message)
{
    std::cout
        // << "Error at "
        // << location.begin.line << "." << location.begin.column << "-"
        // << location.end.line << "." << location.end.column << ": "
        << message << std::endl;
}
