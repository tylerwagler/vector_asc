%{
#include <iostream>
#include <string>
#include "Event.h"
%}

    // debug options
    // %option backup
%option debug
%option perf-report
    // %option trace
    // %option verbose
    // standard options
    // %option nodefault
%option nounput
%option noinput
%option interactive
    // %option yyclass="Vector::ASC::File"
%option prefix="asc"
%option noyywrap
%option c++

%%

    /* File */
^"date "[[:alpha:]]{3}" "[[:alpha:]]{3}" "[[:digit:]]{1,2}" "[[:digit:]]{1,2}":"[[:digit:]]{1,2}":"[[:digit:]]{1,2}(" "[ap]"m")?" "[[:digit:]]{4}\r?$ {
    return Vector::ASC::Event::EventType::FileDate; }
^"base "("hex"|"dec")"  timestamps "("absolute"|"relative")\r?$ {
    return Vector::ASC::Event::EventType::FileBaseTimestamps; }
^("no ")?"internal events logged"\r?$ {
    return Vector::ASC::Event::EventType::FileInternalEventsLogged; }
^"// version "[[:digit:]]{1,3}"."[[:digit:]]{1,3}"."[[:digit:]]{1,3}\r?$ {
    return Vector::ASC::Event::EventType::FileVersion; }
^"//  "[[:digit:].]+" previous log file: ".*\r?$ {
    return Vector::ASC::Event::EventType::FileSplitInformation; }
    /* comment must be non-greedy, so moved to the end */

    /* CAN Events */
^[[:digit:].]+" "[[:digit:]]{1,5}" "[[:xdigit:]]+" "("Rx"|"Tx")" d "[[:xdigit:]]{1,2}(" "[[:xdigit:]]{1,3}){0,8}(" Length = "[[:digit:]]+)?(" BitCount = "[[:digit:]]+)?(" "("TE"|"WU"|"XX"))?(" ID = "[[:xdigit:]]+)?\r?$ {
    return Vector::ASC::Event::EventType::CanMessageEvent; }
^[[:digit:].]+" "[[:digit:]]{1,5}" "[[:xdigit:]]+"x "("Rx"|"Tx")" d "[[:xdigit:]]{1,2}(" "[[:xdigit:]]{1,3}){0,8}(" Length = "[[:digit:]]+)?(" BitCount = "[[:digit:]]+)?(" "("TE"|"WU"|"XX"))?(" ID = "[[:xdigit:]]+"x")?\r?$ {
    return Vector::ASC::Event::EventType::CanExtendedMessageEvent; }
^[[:digit:].]+" "[[:digit:]]{1,5}" "[[:xdigit:]]+" "("Rx"|"Tx")" r"\r?$ {
    return Vector::ASC::Event::EventType::CanRemoteFrameEvent; }
^[[:digit:].]+" "[[:digit:]]{1,5}" ErrorFrame"(" ECC: "[01]+)?(" Flags = 0x"[[:xdigit:]]+)?(" CodeExt = 0x"[[:xdigit:]]+)?(" Code = 0x"[[:xdigit:]]+)?(" ID = "[[:digit:]]+)?(" DLC = "[[:xdigit:]]{1,2})?(" Position = "[[:digit:]]+)?(" Length = "[[:digit:]]+)?\r?$ {
    return Vector::ASC::Event::EventType::CanErrorFrame; }
^[[:digit:].]+" "[[:digit:]]{1,5}" Statistic: D "[[:digit:]]{1,10}" R "[[:digit:]]{1,10}" XD "[[:digit:]]{1,10}" XR "[[:digit:]]{1,10}" E "[[:digit:]]{1,10}" O "[[:digit:]]{1,10}" B "[[:digit:].]{3,6}"%"\r?$ {
    return Vector::ASC::Event::EventType::CanBusStatisticsEvent; }
^[[:digit:].]+" CAN "[[:digit:]]{1,5}" Status:".*\r?$ {
    return Vector::ASC::Event::EventType::CanErrorEvent; }
^[[:digit:].]+" "[[:digit:]]{1,5}" OverloadFrame"\r?$ {
    return Vector::ASC::Event::EventType::CanOverloadFrameEvent; }

    /* CAN FD Events */
^[[:digit:].]+" CANFD "[[:digit:]]{1,5}" "("Rx"|"Tx")" "[[:xdigit:]]+(" "[[:alnum:]_]+)?" "[01]" "[01]" "[[:xdigit:]]+" "[[:digit:]]+(" "[[:xdigit:]]+){0,64}" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::EventType::CanFdMessageEvent; }
^[[:digit:].]+" CANFD "[[:digit:]]{1,5}" "("Rx"|"Tx")" "[[:xdigit:]]+"x"(" "[[:alnum:]_]+)?" "[01]" "[01]" "[[:xdigit:]]+" "[[:digit:]]+(" "[[:xdigit:]]+){0,64}" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::EventType::CanFdExtendedMessageEvent; }
^[[:digit:].]+" CANFD "[[:digit:]]{1,5}" "("Rx"|"Tx")" ErrorFrame Not Acknowledge error, dominant error flag "[[:xdigit:]]{4}" "[[:xdigit:]]{2}" "[[:xdigit:]]{4}" Data "[[:digit:]]+" "[[:xdigit:]]+" "[01]" "[01]" "[[:xdigit:]]+" "[[:digit:]]+(" "[[:xdigit:]]+){0,64}" "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::EventType::CanFdErrorFrame; }
    /* return Vector::ASC::Event::EventType::CanFdBusStatisticsEvent; }
    /* return Vector::ASC::Event::EventType::CanFdOverloadFrame; }

    /* Log and Trigger Events */
^[[:digit:].]+" log trigger event"\r?$ {
    return Vector::ASC::Event::EventType::LogTriggerEvent; }
^[[:digit:].]+" log direct start ("[[:digit:]]{1,10}"ms)"\r?$ {
    return Vector::ASC::Event::EventType::LogDirectStartEvent; }
^[[:digit:].]+" log direct stop ("[[:digit:]]{1,10}"ms)"\r?$ {
    return Vector::ASC::Event::EventType::LogDirectStopEvent; }
^"Begin Triggerblock "[[:alpha:]]{3}" "[[:alpha:]]{3}" "[[:digit:]]{1,2}" "[[:digit:]]{1,2}":"[[:digit:]]{1,2}":"[[:digit:]]{1,2}(" "[ap]"m")?" "[[:digit:]]{4}\r?$ {
    return Vector::ASC::Event::EventType::BeginTriggerblockEvent; }
^"End TriggerBlock"\r?$ {
    return Vector::ASC::Event::EventType::EndTriggerblockEvent; }

    /* Environment Variables */
^[[:digit:].]+" ".+" := ".+\r?$ {
    return Vector::ASC::Event::EventType::EnvironmentVariablesEvent; }

    /* System Variables */
^[[:digit:].]+" SV: "[12345]" 0 0 ".+" = ".+\r?$ {
    return Vector::ASC::Event::EventType::SystemVariablesEvent; }

    /* Macros Signal Events */
^[[:digit:].]+" "[LF]?[[:digit:]]+" ".+?"::".+?"::".+?" = ".*\r$ {
    return Vector::ASC::Event::EventType::MacroSignalEvent; }

    /* GPS events */
^[[:digit:].]+" GPS-Device: "[[:digit:]]+" La: "[[:digit:].]+" Lo: "[[:digit:].]+" Alt: "[[:digit:].]+" Sp: "[[:digit:].]+" Co: "[[:digit:].]+\r?$ {
    return Vector::ASC::Event::EventType::GpsEvent; }

    /* Comment events */
^[[:digit:].]+" Comment: "[[:digit:]]+" ".*\r?$ {
    return Vector::ASC::Event::EventType::CommentEvent; }

    /* Global market events */
^[[:digit:].]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[01]" GMGroup: ".*?" GMMarker: ".*?" GMDescription: ".*?\r?$ {
    return Vector::ASC::Event::EventType::GlobalMarkerEvent; }

    /* Ethernet Events */
^[[:digit:].]+" ETH "[[:xdigit:]]{1,3}" "("Rx"|"Tx")" "[[:xdigit:]]{1,4}:[[:xdigit:]]*\r?$ {
    return Vector::ASC::Event::EventType::EthernetPacket; }
^[[:digit:].]+" ETH "[[:xdigit:]]{1,3}" STAT Link:".*?" LinkSpeed:".*?" Physical:".*?" Duplex:".*?" MDI:".*?" Connector:".*?\r?$ {
    return Vector::ASC::Event::EventType::EthernetStatus; }
^[[:digit:].]+" ETH "[[:xdigit:]]{1,3}" RxEr "[[:xdigit:]]{1,2}" "[[:xdigit:]]{8}" "[[:xdigit:]]{1,4}":"[[:xdigit:]]*\r?$ {
    return Vector::ASC::Event::EventType::EthernetRxError; }

    /* AFDX Events */
^[[:digit:].]+" AFDX "[[:xdigit:]]{1,3}" "("Rx"|"Tx")" "[[:xdigit:]]{1,3}" "[[:xdigit:]]{1,5}" "[[:xdigit:]]+" "[[:xdigit:]]{1,4}":"[[:xdigit:]]*\r?$ {
    return Vector::ASC::Event::EventType::AfdxPacket; }

    /* FlexRay Events (Old Format) */
^[[:digit:].]+" Fr "[12*]" V9 "[[:digit:]]+" "[[:digit:]]+" "[01]" "[01]" "[[:digit:]]+" "[[:alnum:]_]+" "[[:digit:]]+(" "[[:xdigit:]]+){0,255}" "[[:xdigit:]]+" "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::FlexRayOldMessageEvent; }
^[[:digit:].]+" Fr "[12*]" StartCycleEvent NM Vector: "[[:digit:]]+(" "[[:xdigit:]]+){0,255}\r?$ {
    return Vector::ASC::Event::FlexRayOldStartCycleEvent; }

    /* FlexRay Events (New Format) */
^[[:digit:].]+" Fr RMSG "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "("Rx"|"Tx")" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:alnum:]_\[\|\]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*" "[[:xdigit:]]+" "[01]" "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::FlexRayMessageEvent; }
^[[:digit:].]+" Fr PDU "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "("Rx"|"Tx")" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:alnum:]_\[\|\]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*" "[[:xdigit:]]+" "[01]" "[[:digit:]]+" "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::FlexRayMessageEvent; }
^[[:digit:].]+" Fr SCE "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "("Rx"|"Tx")" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" NM_Vector: "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::FlexRayStartCycleEvent; }
^[[:digit:].]+" Fr SE "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "[[:digit:]]+" "[012]" "[[:xdigit:]]+" "[[:xdigit:]]+" "[01234]" "[[:digit:]]+" "[01]\r?$ {
    return Vector::ASC::Event::FlexRayStatusEvent; }
^[[:digit:].]+" Fr EE "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::FlexRayErrorEvent; }

    /* K-Line Events */
^[[:digit:].]+" "("COM"|"KL")[[:digit:]]" "("Rx"|"Tx")" "[[:digit:]]{1,6}" "[[:digit:]]{1,4}(" "[[:xdigit:]]{1,3})*\r?$ {
    return Vector::ASC::Event::EventType::KLineByteEvent; }
^"// K-Line: "[[:digit:].]+" "("COM"|"KL")[[:digit:]]" "("Rx"|"Tx")" "[[:digit:]]{1,6}" "[[:alnum:]]+" "[[:alnum:]]+" "[[:digit:]]{1,4}(" "[[:xdigit:]]{1,3})*\r?$ {
    return Vector::ASC::Event::EventType::KLineMessageEvent; }

    /* LIN Events */
^[[:digit:].]+" L"[[:alnum:]]+" "[[:xdigit:]]+" "("Rx"|"Tx")" "[[:digit:]]+(" "[[:xdigit:]]+){0,8}(" checksum = "[[:digit:]]+)?(" header time = "[[:digit:]]+", full time = "[[:digit:]]+)?(" SOF = "[[:digit:].]+)?(" BR = "[[:digit:]]+)?(" break = "[[:digit:]]+" "[[:digit:]]+)?(" EOH = "[[:digit:].]+)?(" EOB ="(" "[[:digit:].]+){0,8})?(" sim = "[01])?(" EOF = "[[:digit:].]+)?(" RBR = "[[:digit:]]+)?(" HBR = "[[:digit:].]+)?(" HSO = "[[:digit:]]+)?(" RSO = "[[:digit:]]+)?(" CSM = enhanced")?\r?$ {
    return Vector::ASC::Event::EventType::LinMessage; }

    /* LIN Error Events */
^[[:digit:].]+" L"[[:alnum:]]+" "[[:xdigit:]]+" TransmErr header time = "[[:digit:]]+", full time = "[[:digit:]]+(" SOF = "[[:digit:].]+)?(" BR = "[[:digit:]]+)?(" break = "[[:digit:]]+" "[[:digit:]]+)?(" EOH = "[[:digit:].]+)?(" HBR = "[[:digit:].]+)?(" HSO = "[[:digit:]]+)?(" CSM = enhanced")?\r?$ {
    return Vector::ASC::Event::EventType::LinTransmissionError; }
^[[:digit:].]+" L"[[:alnum:]]+" "[[:xdigit:]]+" "[[:digit:]]+" RcvError: ".*?" StateReason = "[[:xdigit:]]+" ShortError = "[01]" DlcTimeout = "[01]" HasDatabytes = "[01](" "[[:xdigit:]]+){0,8}(" SOF = "[[:digit:].]+)?(" BR = "[[:digit:]]+)?(" break = "[[:digit:]]+" "[[:digit:]]+)?(" EOH = "[[:digit:].]+)?(" EOB ="(" "[[:digit:].]+){0,8})?(" RBR = "[[:digit:]]+)?(" RSO = "[[:digit:]]+)?(" HBR = "[[:digit:].]+)?(" HSO = "[[:digit:]]+)?(" CSM = enhanced")?\r?$ {
    return Vector::ASC::Event::EventType::LinReceiveError; }
^[[:digit:].]+" L"[[:digit:]]+" SyncError "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+(" SOF = "[[:digit:].]+)?(" BR = "[[:digit:]]+)?(" break = "[[:digit:]]+" "[[:digit:]]+)?\r?$ {
    return Vector::ASC::Event::EventType::LinSyncError; }
^[[:digit:].]+" L"[[:alnum:]]+" "[[:xdigit:]]+" CSErr "("Rx"|"Tx")" "[[:digit:]]+(" "[[:xdigit:]]+){0,8}(" checksum = "[[:digit:]]+)?(" header time = "[[:digit:]]+", full time = "[[:digit:]]+)?(" SOF = "[[:digit:].]+)?(" BR = "[[:digit:]]+)?(" break = "[[:digit:]]+" "[[:digit:]]+)?(" EOH = "[[:digit:].]+)?(" EOB ="(" "[[:digit:].]+){0,8})?(" sim = "[01])?(" EOF = "[[:digit:].]+)?(" RBR = "[[:digit:]]+)?(" HBR = "[[:digit:].]+)?(" HSO = "[[:digit:]]+)?(" RSO = "[[:digit:]]+)?(" CSM = enhanced")?\r?$ {
    return Vector::ASC::Event::EventType::LinChecksumError; }
^[[:digit:].]+" L"[[:digit:]]+" Spike "("Rx"|"Tx")" "[[:digit:]]+" microseconds"(" SOF = "[[:digit:].]+)?(" BR = "[[:digit:]]+)?\r?$ {
    return Vector::ASC::Event::EventType::LinSpikeEvent; }
^[[:digit:].]+" L"[[:alnum:]]+" Dominant signal "("detected"|"finished")" "[[:digit:]]+" microseconds"(" SOF = "[[:digit:].]+)?(" BR = "[[:digit:]]+)?\r?$ {
    return Vector::ASC::Event::EventType::LinDominantSignal; }

    /* LIN Info Events */
^[[:digit:].]+" L"[[:alnum:]]+" Baudrate "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::LinBaudrate; }
^[[:digit:].]+" L"[[:alnum:]]+" "[[:digit:]]+" DlcInfo "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::LinDlcInfo; }
^[[:digit:].]+" L"[[:alnum:]]+" "[[:digit:]]+" CSInfo Using classic checksum"\r?$ {
    return Vector::ASC::Event::EventType::LinChecksumInfo; }
^[[:digit:].]+" L"[[:alnum:]]+" SchedModChng prior scheduler mode = "[[:digit:]]+", next scheduler mode = "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::LinSchedulerModeChange; }
^[[:digit:].]+" L"[[:alnum:]]+" SlaveTimeout slave-id = "[[:digit:]]+", current state = "[[:digit:]]+", following state = "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::LinSlaveTimeout; }
^[[:digit:].]+" L"[[:alnum:]]+" "[[:xdigit:]]+" EvTrigFrmInfo "[[:alnum:]_]+" "(.*)\r?$ {
    return Vector::ASC::Event::EventType::LinEventTriggeredFrameInfo; }
^[[:digit:].]+" L"[[:alnum:]]+" Statistic "[[:digit:]]+" "[[:digit:].]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::LinStatisticInfo; }
^[[:digit:].]+" L"[[:alnum:]]+" "[[:xdigit:]]+" "[[:digit:].]+" ShortOrSlowResponse: NumRespBytes = "[[:digit:]]+(" "[[:xdigit:]]+){0,9}" SlowResponse = "[01]" InterruptedByBreak = "[01](" SOF = "[[:digit:].]+)?(" BR = "[[:digit:]]+)?(" break = "[[:digit:]]+" "[[:digit:]]+)?(" EOH = "[[:digit:].]+)?(" EOB ="(" "[[:digit:].]+){0,8})?(" HBR = "[[:digit:].]+)?(" HSO = "[[:digit:]]+)?(" CSM = "("unknown"|"enhanced"))?\r?$ {
    return Vector::ASC::Event::EventType::LinShortOrSlowResponse; }
^[[:digit:].]+" L"[[:alnum:]]+" DisturbanceEvent Type = ".+" ByteIndex = "[[:digit:]]+" BitIndex = "[[:digit:]]+" BitOffset = "[[:digit:]]+" Length = "[[:digit:]]+" Header = "[[:xdigit:]]+" Disturbing header = "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::EventType::LinDisturbanceEvent; }

    /* LIN Sleep/Wakeup Events */
^[[:digit:].]+" L"[[:alnum:]]+" SleepModeEvent "[01]" ".*\r?$ {
    return Vector::ASC::Event::EventType::LinSleepMode; }
^[[:digit:].]+" L"[[:alnum:]]+" WakeupFrame "("Rx"|"Tx")" "[[:digit:]]+" SOF = "[[:digit:].]+" BR = "[[:digit:]]+" LengthCode = "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::LinWakeupFrame; }
^[[:digit:].]+" L"[[:alnum:]]+" Unexpected wakeup:"(" approx. "[[:digit:]]+" us")?(" Signal = "[[:digit:]]+)?" SOF = "[[:digit:].]+" BR = "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::LinUnexpectedWakeup; }

    /* MOST Events */
^[[:digit:].]+" M"[[:digit:]]+" "("Rx"|"Tx")" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+){17}" "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::EventType::Most25ControlMessageNodeMode; }
^[[:digit:].]+" M"[[:digit:]]+" Rx "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+){17}" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::EventType::Most25ControlMessageSpyMode; }
^[[:digit:].]+" M"[[:digit:]]+" Pkt: "("Rx"|"Tx")" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::EventType::Most25Packet; }
^[[:digit:].]+" M"[[:digit:]]+" LL: "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::MostLightLockEvent; }
^[[:digit:].]+" M"[[:digit:]]+" Register: "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::EventType::MostSpecialRegisterEvent; }
^[[:digit:].]+" M"[[:digit:]]+" RegData: "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::EventType::MostCommonRegisterEvent; }
^[[:digit:].]+" M"[[:digit:]]+" HWMode: "[[:xdigit:]]+" "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::EventType::MostHwModeEvent; }
^[[:digit:].]+" M"[[:digit:]]+" NetState: "[[:digit:]]+" "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::MostNetStateEvent; }
^[[:digit:].]+" M"[[:digit:]]+" DataLost: "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:digit:].]+" "[[:digit:].]+\r?$ {
    return Vector::ASC::Event::EventType::MostDataLostEvent; }
^[[:digit:].]+" M"[[:digit:]]+" Trigger: "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::EventType::MostTriggerEvent; }
^[[:digit:].]+" M"[[:digit:]]+" MostStatistic: Fr: "[[:digit:]]+" Lt: "[[:digit:]]+" Bl: "[[:digit:]]+" Pk: "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::MostStatisticEvent; }
^[[:digit:].]+" M"[[:digit:]]+" StatEx: "[[:xdigit:]]+" "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::EventType::MostStatisticExtendedEvent; }
^[[:digit:].]+" M"[[:digit:]]+" TxLight: "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::MostTxLight; }
^[[:digit:].]+" M"[[:digit:]]+" Stress: "[[:digit:]]+" "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::MostStressEvent; }
^[[:digit:].]+" M"[[:digit:]]+" AllocTab: "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::EventType::Most25AllocTable; }
^[[:digit:].]+" M"[[:digit:]]+" Msg150: "("Rx"|"Tx")" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::EventType::Most150ControlMessage; }
^[[:digit:].]+" M"[[:digit:]]+" Msg150Frg: "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::EventType::Most150ControlMessageFragment; }
^[[:digit:].]+" M"[[:digit:]]+" Pkt150: "("Rx"|"Tx")" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::EventType::Most150Packet; }
^[[:digit:].]+" M"[[:digit:]]+" Pkt150Frg: "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::EventType::Most150PacketFragment; }
^[[:digit:].]+" M"[[:digit:]]+" PktEth: "("Rx"|"Tx")" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::EventType::MostEthernetPacket; }
^[[:digit:].]+" M"[[:digit:]]+" PktEthFrg: "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::EventType::MostEthernetPacketFragment; }
^[[:digit:].]+" M"[[:digit:]]+" System: "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::EventType::MostSystemEvent; }
^[[:digit:].]+" M"[[:digit:]]+" AT150: "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::EventType::Most150AllocTable; }
^[[:digit:].]+" M"[[:digit:]]+" Msg50: "("Rx"|"Tx")" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::EventType::Most50ControlMessage; }
^[[:digit:].]+" M"[[:digit:]]+" Pkt50: "("Rx"|"Tx")" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::EventType::Most50Packet; }
^[[:digit:].]+" M"[[:digit:]]+" Ecl: "[[:digit:]]+" "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::MostEcl; }

    /* TP/Diagnostics Events */
^"// "[[:digit:]]+" OTP("[[:xdigit:]]+") "("Info"|"Warn"|"Error"|"Atom"|"Data")" ".+?"->".+?":"\r?$ {
    return Vector::ASC::Event::EventType::TpDiagPrefix; }
^"SF Length: "[[:xdigit:]]+" ["(" "[[:xdigit:]]+)*" ]"\r?$ {
    return Vector::ASC::Event::EventType::TpDiagSingleFrame; }
^"FF Length: "[[:xdigit:]]+" ["(" "[[:xdigit:]]+)*" ]"\r?$ {
    return Vector::ASC::Event::EventType::TpDiagFirstFrame; }
^"CF Seq.Nr.: "[[:digit:]]+" ["(" "[[:xdigit:]]+)*" ]"\r?$ {
    return Vector::ASC::Event::EventType::TpDiagConsecutiveFrame; }
^"FC."("CTS"|"WT"|"OVFLW")": BSmax: 0x"[[:xdigit:]]+", STmin: 0x"[[:xdigit:]]+" ms"\r?$ {
    return Vector::ASC::Event::EventType::TpDiagFlowControlFrame; }
^[[:digit:].]+" DiagRequest[".+?"]"(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::EventType::TpDiagRequest; }

    /* Comment */
^"// ".*\r?$ {
    return Vector::ASC::Event::EventType::FileComment; }

    /* remaining characters */
^.*\r?$ { return Vector::ASC::Event::EventType::Default; }

%%

