%{
#include <iostream>
#include <string>
#include "Event.h"
%}

%option prefix="asc"
%option noyywrap
%option c++

    // CAN, Log & Trigger Symbols
Time [[:digit:].]{3,}
Channel [[:digit:]]{1,5}
IDnum [[:xdigit:]]{1,14}
    // IDsym @todo
ID {IDnum}
Dir ("Rx"|"Tx"|"TxRq")
DLC [[:xdigit:]]{1,2}
MessageFlags ("TE"|"WU"|"XX")
StatNumber [[:digit:]]{1,10}
StatPercent [[:digit:].]{3,6}
PreTrigger [[:digit:]]{1,10}
PostTrigger [[:digit:]]{1,10}
Error .+
Dx [[:xdigit:]]{1,3}
WeekDay ("Mon"|"Tue"|"Wed"|"Thu"|"Fri"|"Sat"|"Sun"|"Mon"|"Die"|"Mit"|"Don"|"Fre"|"Sam"|"Son")
Month ("Jan"|"Feb"|"Mar"|"Apr"|"May"|"Jun"|"Jul"|"Aug"|"Sep"|"Oct"|"Nov"|"Dec"|"Jan"|"Feb"|"Mär"|"Apr"|"Mai"|"Jun"|"Jul"|"Aug"|"Sep"|"Okt"|"Nov"|"Dez")
Date [[:digit:]]{1,2}
FullTime [[:digit:]]{2}":"[[:digit:]]{2}":"[[:digit:]]{2}(" am"|" pm")?
Year [[:digit:]]{4}
svtype [12345]
MessageDuration [[:digit:]]+
MessageLength [[:digit:]]+
BRS [01]
ESI [01]
DataLength [[:digit:]]{1,3}
BitTimingConfArb [[:xdigit:]]{8}
BitTimingConfData [[:xdigit:]]{8}

    // Ethernet Symbols
Eth_Channel [[:xdigit:]]{1,3}
Eth_Data [[:xdigit:]]+
Eth_DataLen [[:xdigit:]]{1,4}
Eth_Dir ("Rx"|"Tx"|"TxRq")
Eth_Time [[:digit:].]{3,}
Eth_ErrorCode [[:xdigit:]]{1,2}
Eth_FrameChecksum [[:xdigit:]]{8}
Afdx_BAG [[:xdigit:]]+
Afdx_Channel [[:xdigit:]]{1,3}
Afdx_Data [[:xdigit:]]+
Afdx_DataLen [[:xdigit:]]{1,4}
Afdx_Dir ("Rx"|"Tx"|"TxRq")
Afdx_EthChannel [[:xdigit:]]{1,3}
Afdx_Flags [[:xdigit:]]{1,5}
Afdx_Time [[:digit:].]{3,}

    // FlexRay Symbols
FlexRayOld_Time [[:digit:].]{3,}
FlexRayOld_Channel ("Fr 1"|"Fr 2"|"Fr *")
    // FlexRay_Typ ("V9"|"StartCycleEvent"|"ErrorFrame")
FlexRayOld_ID [[:xdigit:]]{1,4}
FlexRayOld_Cycle [[:digit:]]{1,2}
FlexRayOld_NM [01]
FlexRayOld_Sync [01]
FlexRayOld_HeaderCRC [[:xdigit:]]{1,4}
FlexRayOld_SymbolicName [[:alnum:]_]+
FlexRayOld_DLC [[:xdigit:]]{1,3}
FlexRayOld_Dx [[:xdigit:]]{1,3}
FlexRayOld_FrameState [[:xdigit:]]{1,5}
FlexRayOld_HeaderBitMask [[:xdigit:]]{1,3}
FlexRay_Time [[:digit:].]{3,}
FlexRay_Dir ("Rx"|"Tx"|"TxRq")

    // K-Line Symbols
KLine_time [[:digit:].]{3,}
KLine_port ("COM"|"KL")[[:digit:]]{1,3}
KLine_direction ("Tx"|"Rx")
KLine_baudrate [[:digit:]]{1,6}
KLine_source [[:alnum:]]+
KLine_destination [[:alnum:]]+
KLine_length [[:digit:]]{1,4}
KLine_data [[:xdigit:]]{1,3}

    // LIN Symbols
LIN_baudrate [[:digit:]]{1,5}
LIN_Channel "L"[[:xdigit:]i*]{1,4}
LIN_checksum [[:xdigit:]]{1,3}
LIN_checksumModel ("unknown"|"classic"|"enhanced"|"error")
LIN_checksumModelInfo "Using "("enhanced"|"classic")" checksum"
LIN_Dir ("Rx"|"Tx"|"TxRq")
LIN_DLC [-[:digit:]]{1,2}
LIN_NumberOfResponseBytes [[:digit:]]
LIN_Dx [[:xdigit:]]{2,3}
LIN_description .+
LIN_DomSigState ("detected"|"continuing"|"finished")
LIN_DomSigLength [[:digit:]]{1,8}
LIN_endOfFrame [[:digit:].]{3,}
LIN_ETFName [[:alnum:]_]+
LIN_endOfHeader [[:digit:].]{3,}
LIN_FullTime [[:digit:]]+
LIN_fullTime {LIN_FullTime}
LIN_HasDatabytes [01]
LIN_HeaderTime [[:digit:]]+
LIN_headerTime {LIN_HeaderTime}
LIN_headerBaudrate [[:digit:].]{3,12}
LIN_ID [[:alnum:]_]+
LIN_IsDLCTimeout [01]
LIN_IsShortError [01]
LIN_MessageId [[:xdigit:]]{1,5}
LIN_NAD [[:xdigit:]]{1,3}
LIN_offendingByte [[:xdigit:]]{1,3}
LIN_responseBaudrate [[:digit:]]{1,5}
LIN_simulated [01]
LIN_scheduleTableIndex [[:digit:]]+
LIN_slaveId [[:digit:]]{1,2}
LIN_SpikeLength [[:digit:]]{1,6}
LIN_startOfFrame [[:digit:].]{3,}
LIN_state [[:digit:]]{1,3}
LIN_StateReason [[:xdigit:]]{1,3}
LIN_stopBitOffsetInHeader [[:digit:]]{1,8}
LIN_stopBitOffsetInResponse [[:digit:]]{1,8}
LIN_SupplierId [[:xdigit:]]{1,5}
LIN_SyncBreak [[:digit:]]{1,6}
LIN_SyncDel [[:digit:]]{1,6}
LIN_syncBreakTime [[:digit:]]+" us ("[[:digit:].]+" bits)"
LIN_syncDelimiterTime [[:digit:]]+" us ("[[:digit:].]+" bits)"
LIN_T [[:digit:].]{3,}
LIN_Time [[:digit:].]{3,}
LIN_TimeInterval [[:digit:]]{1,5}
LIN_WakeupByte [[:xdigit:]]{1,3}
LIN_WakeupLengthInfo [012]
LIN_IsSlowResponse [[:digit:]]
LIN_ResponseWasInterruptedByBreak [[:digit:]]
LIN_Width [[:digit:]]{3,4}
LIN_DisturbanceType ("dominant"|"recessive"|"header"|"bitstream"|"variableBitstream")
LIN_ByteIndex [[:digit:]]
LIN_BitIndex [[:digit:]]{1,3}
LIN_BitOffsetInSixteenthBits [[:digit:]]{1,2}
LIN_DisturbanceLengthInSixteenthBits [[:digit:]]{1,2}
LIN_IDorFF [[:xdigit:]]{1,3}

    // MOST Symbols
MOST_AckNack [[:xdigit:]]{2,3}
MOST_AllocTableSize [[:xdigit:]]{4}
MOST_AT150EventModeFlags [[:xdigit:]]{2}
MOST_AT150Size [[:xdigit:]]{4}
MOST_CAck [[:xdigit:]]{2}
MOST_Cack {MOST_CAck}
MOST_Channel "M"[[:xdigit:]]{1,2}
MOST_CodingErrors [[:xdigit:]]{6}
MOST_CRC [[:xdigit:]]{1,5}
MOST_CRC2 [[:xdigit:]]{4}
MOST_CRC4 [[:xdigit:]]{8}
MOST_DxAT [[:xdigit:]]{2}
MOST_DestAdr [[:xdigit:]]{1,5}
MOST_DestMacAdr [[:xdigit:]]{12}
MOST_Dir ("Rx"|"Tx"|"TxRq")
MOST_DLAsync [[:xdigit:]]{1,4}
MOST_DLCtrl [[:xdigit:]]{1,4}
MOST_DLInfo [[:xdigit:]]{8}
MOST_DLTime [[:digit:].]{3,}
MOST_Dx [[:xdigit:]]{1,3}
MOST_EclMode [01]
MOST_EclState [01]
MOST_FirstDataLen [[:xdigit:]]{1,4}
MOST_FrameCounter [[:xdigit:]]{6}
MOST_FreeBytes [[:xdigit:]]{4}
MOST_FrgDataLen [[:xdigit:]]{4,8}
MOST_FrgDataLenAnnounced [[:xdigit:]]{4,8}
MOST_FrgMask [[:xdigit:]]{8}
MOST_HWMode [[:xdigit:]]{2}
MOST_HWModeMask [[:xdigit:]]{2}
MOST_LLState [[:xdigit:]]{1,2}
MOST_Msg150Len [[:xdigit:]]{1,3}
MOST_Msg50Len [[:xdigit:]]{1,3}
MOST_NetStateNew [[:xdigit:]]
MOST_NetStateOld [[:xdigit:]]
MOST_PAck [[:xdigit:]]{2}
MOST_Pack {MOST_PAck}
MOST_Pindex [[:xdigit:]]{2}
MOST_Pkt150Len [[:xdigit:]]{1,4}
MOST_PktArbitr [[:xdigit:]]{2}
MOST_PktEthLen [[:xdigit:]]{1,4}
MOST_PktLen [[:xdigit:]]{1,4}
MOST_PktPrio [[:xdigit:]]
MOST_PktState [[:xdigit:]]{2}
MOST_Priority [[:xdigit:]]{2}
MOST_RegChip [[:xdigit:]]{2}
MOST_RegDataLen [[:xdigit:]]{2}
MOST_RegID [[:xdigit:]]{2}
MOST_RegOffset [[:xdigit:]]{4}
MOST_RegSubType [[:xdigit:]]
MOST_RegValue [[:xdigit:]]{4}
MOST_RsvdUC [[:xdigit:]]{2}
MOST_RsvdUL [[:xdigit:]]{2}
MOST_Rtype [[:xdigit:]]{1,3}
MOST_RType {MOST_Rtype}
MOST_SourceAdr [[:xdigit:]]{1,5}
MOST_SourceMacAdr [[:xdigit:]]{12}
MOST_State [[:xdigit:]]{1,3}
MOST_State2 [[:xdigit:]]{1,5}
MOST_StatVal [[:digit:]]{1,5}
MOST_StressMode [[:xdigit:]]
MOST_StressState [01]
MOST_SysID [[:xdigit:]]{2}
MOST_SysValue [[:xdigit:]]{4}
MOST_SysValueOld [[:xdigit:]]{4}
MOST_Time [[:digit:].]{3,}
MOST_TransferType [[:xdigit:]]{2}
MOST_TrigHW [[:xdigit:]]
MOST_TrigMode [012]
MOST_TrigValue [[:xdigit:]]{8}
MOST_TxLightState [012]
MOST_Wx [[:xdigit:]]{4}

    // TP/Diagnostics Symbols
TPDiag_CANChannel [[:digit:]]{1,2}
TPDiag_connectionId [[:xdigit:]]{2}
TPDiag_type ("Info"|"Warn"|"Error"|"Atom"|"Data")
TPDiag_source [[:alnum:]_<>]+
TPDiag_destination [[:alnum:]_<>]+
TPDiag_length [[:xdigit:]]{2,4}
TPDiag_transportedBytes (" "[[:xdigit:]]+)*
TPDiag_SN [[:xdigit:]]{1,4}
TPDiag_FCType ("CTS"|"WT"|"OVFLW")
TPDiag_BS [[:xdigit:]]{1,4}
TPDiag_STmin [[:xdigit:]]{1,4}
TPDiag_timestamp [[:digit:].]{3,}
TPDiag_ECUQualifier [[:alnum:]_]+
TPDiag_byteSequence (" "[[:xdigit:]]+)*

%%

    /* File */
^"date "{WeekDay}" "{Month}" "{Date}" "{FullTime}" "{Year}\r?$ {
    return Vector::ASC::Event::EventType::FileDate; }
^"base "("hex"|"dec")"  timestamps "("absolute"|"relative")\r?$ {
    return Vector::ASC::Event::EventType::FileBaseTimestamps; }
^("no ")?"internal events logged"\r?$ {
    return Vector::ASC::Event::EventType::FileInternalEventsLogged; }
^"// version "[[:digit:]]{1,3}"."[[:digit:]]{1,3}"."[[:digit:]]{1,3}\r?$ {
    return Vector::ASC::Event::EventType::FileVersion; }
^"//  "{Time}" previous log file: ".*\r?$ {
    return Vector::ASC::Event::EventType::FileSplitInformation; }
    /* comment must be non-greedy, so moved to the end */

    /* CAN Events */
^{Time}" "{Channel}" "{ID}" "{Dir}" d "{DLC}(" "{Dx}){0,8}(" Length = "{MessageDuration})?(" BitCount = "{MessageLength})?(" "{MessageFlags})?(" ID = "{IDnum})?\r?$ {
    return Vector::ASC::Event::EventType::CanMessageEvent; }
^{Time}" "{Channel}" "{ID}"x "{Dir}" d "{DLC}(" "{Dx}){0,8}(" Length = "{MessageDuration})?(" BitCount = "{MessageLength})?(" "{MessageFlags})?(" ID = "{IDnum}"x")?\r?$ {
    return Vector::ASC::Event::EventType::CanExtendedMessageEvent; }
^{Time}" "{Channel}" "{ID}" "{Dir}" r"\r?$ {
    return Vector::ASC::Event::EventType::CanRemoteFrameEvent; }
^{Time}" "{Channel}" ErrorFrame"(" ECC: "[01]+)?(" Flags = 0x"[[:xdigit:]]+)?(" CodeExt = 0x"[[:xdigit:]]+)?(" Code = 0x"[[:xdigit:]]+)?(" ID = "[[:digit:]]+)?(" DLC = "[[:xdigit:]]{1,2})?(" Position = "[[:digit:]]+)?(" Length = "[[:digit:]]+)?\r?$ {
    return Vector::ASC::Event::EventType::CanErrorFrame; }
^{Time}" "{Channel}" Statistic: D "{StatNumber}" R "{StatNumber}" XD "{StatNumber}" XR "{StatNumber}" E "{StatNumber}" O "{StatNumber}" B "{StatPercent}"%"\r?$ {
    return Vector::ASC::Event::EventType::CanBusStatisticsEvent; }
^{Time}" CAN "{Channel}" Status:"{Error}\r?$ {
    return Vector::ASC::Event::EventType::CanErrorEvent; }
^{Time}" "{Channel}" OverloadFrame"\r?$ {
    return Vector::ASC::Event::EventType::CanOverloadFrameEvent; }

    /* CAN FD Events */
^{Time}" CANFD "{Channel}" "{Dir}" "{ID}(" "[[:alnum:]_]+)?" "{BRS}" "{ESI}" "{DLC}" "{DataLength}(" "{Dx}){0,64}" "{MessageDuration}" "{MessageLength}" "[[:digit:]]+" "[[:xdigit:]]+" "{BitTimingConfArb}" "{BitTimingConfData}\r?$ {
    return Vector::ASC::Event::EventType::CanFdMessageEvent; }
^{Time}" CANFD "{Channel}" "{Dir}" "{ID}"x"(" "[[:alnum:]_]+)?" "{BRS}" "{ESI}" "{DLC}" "{DataLength}(" "{Dx}){0,64}" "{MessageDuration}" "{MessageLength}" "[[:digit:]]+" "[[:xdigit:]]+" "{BitTimingConfArb}" "{BitTimingConfData}\r?$ {
    return Vector::ASC::Event::EventType::CanFdExtendedMessageEvent; }
^{Time}" CANFD "{Channel}" "{Dir}" ErrorFrame Not Acknowledge error, dominant error flag "[[:xdigit:]]{4}" "[[:xdigit:]]{2}" "[[:xdigit:]]{4}" Data "[[:digit:]]+" "{ID}" "{BRS}" "{ESI}" "{DLC}" "{DataLength}(" "{Dx}){0,64}" "{MessageDuration}" "[[:digit:]]+" "[[:xdigit:]]+" "{BitTimingConfArb}" "{BitTimingConfData}\r?$ {
    return Vector::ASC::Event::EventType::CanFdErrorFrame; }
    /* return Vector::ASC::Event::EventType::CanFdBusStatisticsEvent; }
    /* return Vector::ASC::Event::EventType::CanFdOverloadFrame; }

    /* Log and Trigger Events */
^{Time}" log trigger event"\r?$ {
    return Vector::ASC::Event::EventType::LogTriggerEvent; }
^{Time}" log direct start ("{PreTrigger}"ms)"\r?$ {
    return Vector::ASC::Event::EventType::LogDirectStartEvent; }
^{Time}" log direct stop ("{PostTrigger}"ms)"\r?$ {
    return Vector::ASC::Event::EventType::LogDirectStopEvent; }
^"Begin Triggerblock "{WeekDay}" "{Month}" "{Date}" "{FullTime}" "{Year}\r?$ {
    return Vector::ASC::Event::EventType::BeginTriggerblockEvent; }
^"End TriggerBlock"\r?$ {
    return Vector::ASC::Event::EventType::EndTriggerblockEvent; }

    /* Environment Variables */
^{Time}" ".+" := ".+\r?$ {
    return Vector::ASC::Event::EventType::EnvironmentVariablesEvent; }

    /* System Variables */
^{Time}" SV: "{svtype}" 0 0 ".+" = ".+\r?$ {
    return Vector::ASC::Event::EventType::SystemVariablesEvent; }

    /* Macros Signal Events */
^{Time}" "[LF]?[[:digit:]]+" ".+?"::".+?"::".+?" = ".*\r$ {
    return Vector::ASC::Event::EventType::MacroSignalEvent; }

    /* GPS events */
^{Time}" GPS-Device: "[[:digit:]]+" La: "[[:digit:].]+" Lo: "[[:digit:].]+" Alt: "[[:digit:].]+" Sp: "[[:digit:].]+" Co: "[[:digit:].]+\r?$ {
    return Vector::ASC::Event::EventType::GpsEvent; }

    /* Comment events */
^{Time}" Comment: "[[:digit:]]+" ".*\r?$ {
    return Vector::ASC::Event::EventType::CommentEvent; }

    /* Global market events */
^{Time}" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[01]" GMGroup: ".*?" GMMarker: ".*?" GMDescription: ".*?\r?$ {
    return Vector::ASC::Event::EventType::GlobalMarkerEvent; }

    /* Ethernet Events */
^{Eth_Time}" ETH "{Eth_Channel}" "{Eth_Dir}" "{Eth_DataLen}":"{Eth_Data}\r?$ {
    return Vector::ASC::Event::EventType::EthernetPacket; }
^{Eth_Time}" ETH "{Eth_Channel}" STAT Link:".+" LinkSpeed:".+" Physical:".+" Duplex:".+" MDI:".+" Connector:".+\r?$ {
    return Vector::ASC::Event::EventType::EthernetStatus; }
^{Eth_Time}" ETH "{Eth_Channel}" RxEr "{Eth_ErrorCode}" "{Eth_FrameChecksum}" "{Eth_DataLen}":"{Eth_Data}\r?$ {
    return Vector::ASC::Event::EventType::EthernetRxError; }

    /* AFDX Events */
^{Afdx_Time}" AFDX "{Afdx_Channel}" "{Afdx_Dir}" "{Afdx_EthChannel}" "{Afdx_Flags}" "{Afdx_BAG}" "{Afdx_DataLen}":"{Afdx_Data}\r?$ {
    return Vector::ASC::Event::EventType::AfdxPacket; }

    /* FlexRay Events (Old Format) */
^{FlexRayOld_Time}" "{FlexRayOld_Channel}" V9 "{FlexRayOld_ID}" "{FlexRayOld_Cycle}" "{FlexRayOld_NM}" "{FlexRayOld_Sync}" "{FlexRayOld_HeaderCRC}" "{FlexRayOld_SymbolicName}" "{FlexRayOld_DLC}(" "{FlexRayOld_Dx}){0,255}" "{FlexRayOld_FrameState}" "{FlexRayOld_HeaderBitMask}\r?$ {
    return Vector::ASC::Event::FlexRayOldMessageEvent; }
^{FlexRayOld_Time}" "{FlexRayOld_Channel}" StartCycleEvent NM Vector: "{FlexRayOld_DLC}(" "{FlexRayOld_Dx}){0,255}\r?$ {
    return Vector::ASC::Event::FlexRayOldStartCycleEvent; }
    /* FlexRayOldErrorFrameEvent */

    /* FlexRay Events (New Format) */
^{FlexRay_Time}" Fr RMSG "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "{FlexRay_Dir}" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:alnum:]_\[\|\]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*" "[[:xdigit:]]+" "[01]" "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::FlexRayMessageEvent; }
^{FlexRay_Time}" Fr PDU "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "{FlexRay_Dir}" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:alnum:]_\[\|\]]+" "[[:xdigit:]]+" "[[:xdigit:]]+(" "[[:xdigit:]]+)*" "[[:xdigit:]]+" "[01]" "[[:digit:]]+" "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::FlexRayMessageEvent; }
^{FlexRay_Time}" Fr SCE "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "{FlexRay_Dir}" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" NM_Vector: "[[:xdigit:]]+(" "[[:xdigit:]]+)*\r?$ {
    return Vector::ASC::Event::FlexRayStartCycleEvent; }
^{FlexRay_Time}" Fr SE "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "[[:digit:]]+" "[012]" "[[:xdigit:]]+" "[[:xdigit:]]+" "[01234]" "[[:digit:]]+" "[01]\r?$ {
    return Vector::ASC::Event::FlexRayStatusEvent; }
^{FlexRay_Time}" Fr EE "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+" "[[:xdigit:]]+\r?$ {
    return Vector::ASC::Event::FlexRayErrorEvent; }

    /* K-Line Events */
^{KLine_time}" "{KLine_port}" "{KLine_direction}" "{KLine_baudrate}" "{KLine_length}(" "{KLine_data})*\r?$ {
    return Vector::ASC::Event::EventType::KLineByteEvent; }
^"// K-Line: "{KLine_time}" "{KLine_port}" "{KLine_direction}" "{KLine_baudrate}" "{KLine_source}" "{KLine_destination}" "{KLine_length}(" "{KLine_data})*\r?$ {
    return Vector::ASC::Event::EventType::KLineMessageEvent; }

    /* LIN Events */
^{LIN_Time}" "{LIN_Channel}" "{LIN_ID}" "{LIN_Dir}" "{LIN_DLC}(" "{LIN_Dx}){0,8}(" slave = "{LIN_slaveId}", state = "{LIN_state})?" checksum = "{LIN_checksum}" header time = "{LIN_headerTime}", full time = "{LIN_fullTime}((" start of frame = "{LIN_startOfFrame}", sync break = "{LIN_syncBreakTime}", sync delimiter = "{LIN_syncDelimiterTime})|(" SOF = "{LIN_startOfFrame}" BR = "{LIN_baudrate}" break = "{LIN_SyncBreak}" "{LIN_SyncDel}(" subId = "{LIN_NAD}" "{LIN_MessageId}" "{LIN_SupplierId})?" EOH = "{LIN_endOfHeader}" EOB ="(" "{LIN_T}){0,8}" sim = "{LIN_simulated}(" EOF = "{LIN_endOfFrame}(" RBR = "{LIN_responseBaudrate}(" HBR = "{LIN_headerBaudrate}" HSO = "{LIN_stopBitOffsetInHeader}" RSO = "{LIN_stopBitOffsetInResponse}(" CSM = "{LIN_checksumModel})?)?)?)?))\r?$ {
    return Vector::ASC::Event::EventType::LinMessage; }

    /* LIN Error Events */
^{LIN_Time}" "{LIN_Channel}" "{LIN_ID}" TransmErr"(" slave = "{LIN_slaveId}", state = "{LIN_state})?" header time = "{LIN_headerTime}", full time = "{LIN_fullTime}(" SOF = "{LIN_startOfFrame}" BR = "{LIN_baudrate}" break = "{LIN_SyncBreak}" "{LIN_SyncDel}("subId = "{LIN_NAD}" "{LIN_MessageId}" "{LIN_SupplierId})?" EOH = "{LIN_endOfHeader}(" HBR = "{LIN_headerBaudrate}" HSO = "{LIN_stopBitOffsetInHeader}(" CSM = "{LIN_checksumModel})?)?)?\r?$ {
    return Vector::ASC::Event::EventType::LinTransmissionError; }
^{LIN_Time}" "{LIN_Channel}(" "{LIN_ID}" "{LIN_DLC})?" RcvError: "{LIN_description}(" char = "{LIN_offendingByte})?(" slave = "{LIN_slaveId}", state = "{LIN_state})?(" StateReason = "{LIN_StateReason}" ShortError = "{LIN_IsShortError}" DlcTimeout = "{LIN_IsDLCTimeout}" HasDatabytes = "{LIN_HasDatabytes}(" "{LIN_Dx}){0,8}" SOF = "{LIN_startOfFrame}" BR = "{LIN_baudrate}" break = "{LIN_SyncBreak}" "{LIN_SyncDel}(" subId = "{LIN_NAD}" "{LIN_MessageId}" "{LIN_SupplierId})?(" EOH = "{LIN_endOfHeader})?(" EOB = "(" "{LIN_T}){0,8})?(" RBR = "{LIN_responseBaudrate}(" HBR = "{LIN_headerBaudrate}" HSO = "{LIN_stopBitOffsetInHeader}" RSO = "{LIN_stopBitOffsetInResponse}(" CSM = "{LIN_checksumModel})?)?)?)?\r?$ {
    return Vector::ASC::Event::EventType::LinReceiveError; }
^{LIN_Time}" "{LIN_Channel}" SyncError"(" "{LIN_TimeInterval}){4}(" SOF = "{LIN_startOfFrame}" BR = "{LIN_baudrate}" break = "{LIN_SyncBreak}" "{LIN_SyncDel})?\r?$ {
    return Vector::ASC::Event::EventType::LinSyncError; }
^{LIN_Time}" "{LIN_Channel}" "{LIN_ID}" CSErr "{LIN_Dir}" "{LIN_DLC}(" "[[:xdigit:]]+){0,8}(" slave = "{LIN_slaveId}", state = "{LIN_state})?" checksum = "{LIN_checksum}" header time = "{LIN_headerTime}", full time = "{LIN_fullTime}(" SOF = "{LIN_startOfFrame}" BR = "{LIN_baudrate}" break = "{LIN_SyncBreak}" "{LIN_SyncDel}(" subId = "{LIN_NAD}" "{LIN_MessageId}" "{LIN_SupplierId})?" EOH = "{LIN_endOfFrame}" EOB ="(" "{LIN_T}){0,8}" sim = "{LIN_simulated}(" EOF = "{LIN_endOfFrame}(" RBR = "{LIN_responseBaudrate}(" HBR = "{LIN_headerBaudrate}" HSO = "{LIN_stopBitOffsetInHeader}" RSO = "{LIN_stopBitOffsetInResponse}(" CSM = "{LIN_checksumModel})?)?)?)?)?\r?$ {
    return Vector::ASC::Event::EventType::LinChecksumError; }
^{LIN_Time}" "{LIN_Channel}" Spike "{LIN_Dir}" "{LIN_SpikeLength}" microseconds"(" SOF = "{LIN_startOfFrame}" BR = "{LIN_baudrate})?\r?$ {
    return Vector::ASC::Event::EventType::LinSpikeEvent; }
^{LIN_Time}" "{LIN_Channel}" Dominant signal "{LIN_DomSigState}" "{LIN_DomSigLength}" microseconds"(" SOF = "{LIN_startOfFrame}" BR = "{LIN_baudrate})?\r?$ {
    return Vector::ASC::Event::EventType::LinDominantSignal; }

    /* LIN Info Events */
^{LIN_Time}" "{LIN_Channel}" Baudrate "{LIN_baudrate}\r?$ {
    return Vector::ASC::Event::EventType::LinBaudrate; }
^{LIN_Time}" "{LIN_Channel}" "{LIN_ID}" DlcInfo "{LIN_DLC}\r?$ {
    return Vector::ASC::Event::EventType::LinDlcInfo; }
^{LIN_Time}" "{LIN_Channel}" "{LIN_ID}" CSInfo "{LIN_checksumModelInfo}\r?$ {
    return Vector::ASC::Event::EventType::LinChecksumInfo; }
^{LIN_Time}" "{LIN_Channel}" SchedModChng prior scheduler mode = "{LIN_scheduleTableIndex}", next scheduler mode = "{LIN_scheduleTableIndex}\r?$ {
    return Vector::ASC::Event::EventType::LinSchedulerModeChange; }
^{LIN_Time}" "{LIN_Channel}" SlaveTimeout slave-id = "{LIN_slaveId}", current state = "{LIN_state}", following state = "{LIN_state}\r?$ {
    return Vector::ASC::Event::EventType::LinSlaveTimeout; }
^{LIN_Time}" "{LIN_Channel}" "{LIN_ID}" EvTrigFrmInfo "{LIN_ETFName}" "{LIN_description}\r?$ {
    return Vector::ASC::Event::EventType::LinEventTriggeredFrameInfo; }
^{LIN_Time}" "{LIN_Channel}" Statistic "[[:digit:]]+" "[[:digit:].]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+" "[[:digit:]]+\r?$ {
    return Vector::ASC::Event::EventType::LinStatisticInfo; }
^{LIN_Time}" "{LIN_Channel}" "{LIN_ID}" "{LIN_DLC}" ShortOrSlowResponse: NumRespBytes = "{LIN_NumberOfResponseBytes}(" "[[:xdigit:]]+){0,9}" SlowResponse = "{LIN_IsSlowResponse}" InterruptedByBreak = "{LIN_ResponseWasInterruptedByBreak}" SOF = "{LIN_startOfFrame}" BR = "{LIN_baudrate}" break = "{LIN_SyncBreak}" "{LIN_SyncDel}("subId = "{LIN_NAD}" "{LIN_MessageId}" "{LIN_SupplierId})?" EOH = "{LIN_endOfHeader}" EOB ="(" "{LIN_T}){0,8}" HBR = "{LIN_headerBaudrate}" HSO = "{LIN_stopBitOffsetInHeader}" CSM = "{LIN_checksumModel}\r?$ {
    return Vector::ASC::Event::EventType::LinShortOrSlowResponse; }
^{LIN_Time}" "{LIN_Channel}" DisturbanceEvent Type = "{LIN_DisturbanceType}" ByteIndex = "{LIN_ByteIndex}" BitIndex = "{LIN_BitIndex}" BitOffset = "{LIN_BitOffsetInSixteenthBits}" Length = "{LIN_DisturbanceLengthInSixteenthBits}" Header = "{LIN_IDorFF}" Disturbing header = "{LIN_IDorFF}\r?$ {
    return Vector::ASC::Event::EventType::LinDisturbanceEvent; }

    /* LIN Sleep/Wakeup Events */
^{LIN_Time}" "{LIN_Channel}" SleepModeEvent "{LIN_simulated}" "{LIN_description}\r?$ {
    return Vector::ASC::Event::EventType::LinSleepMode; }
^{LIN_Time}" "{LIN_Channel}" WakeupFrame "{LIN_Dir}" "{LIN_WakeupByte}(" SOF = "{LIN_startOfFrame}" BR = "{LIN_baudrate}" LengthCode = "{LIN_WakeupLengthInfo})?\r?$ {
    return Vector::ASC::Event::EventType::LinWakeupFrame; }
^{LIN_Time}" "{LIN_Channel}" Unexpected wakeup:"((" approx. "{LIN_Width}" us")|(" Signal = "{LIN_WakeupByte}))" SOF = "{LIN_startOfFrame}" BR = "{LIN_baudrate}\r?$ {
    return Vector::ASC::Event::EventType::LinUnexpectedWakeup; }

    /* MOST Events */
^{MOST_Time}" "{MOST_Channel}" "{MOST_Dir}" "{MOST_SourceAdr}" "{MOST_DestAdr}" "{MOST_RType}(" "{MOST_Dx}){17}" "{MOST_State2}\r?$ {
    return Vector::ASC::Event::EventType::Most25ControlMessageNodeMode; }
^{MOST_Time}" "{MOST_Channel}" Rx "{MOST_SourceAdr}" "{MOST_DestAdr}" "{MOST_RType}(" "{MOST_Dx}){17}" "{MOST_State}" "{MOST_AckNack}" "{MOST_CRC}\r?$ {
    return Vector::ASC::Event::EventType::Most25ControlMessageSpyMode; }
^{MOST_Time}" "{MOST_Channel}" Pkt: "{MOST_Dir}" "{MOST_SourceAdr}" "{MOST_DestAdr}" "{MOST_PktState}" "{MOST_TransferType}" "{MOST_PktPrio}" "{MOST_PktArbitr}" "{MOST_CRC2}" "{MOST_PktLen}(" "{MOST_Dx})+\r?$ {
    return Vector::ASC::Event::EventType::Most25Packet; }
^{MOST_Time}" "{MOST_Channel}" LL: "{MOST_LLState}\r?$ {
    return Vector::ASC::Event::EventType::MostLightLockEvent; }
^{MOST_Time}" "{MOST_Channel}" Register: "{MOST_RegSubType}" "{MOST_RegID}" "{MOST_RegValue}\r?$ {
    return Vector::ASC::Event::EventType::MostSpecialRegisterEvent; }
^{MOST_Time}" "{MOST_Channel}" RegData: "{MOST_RegSubType}" "{MOST_RegChip}" "{MOST_RegOffset}" "{MOST_RegDataLen}(" "{MOST_Dx})*\r?$ {
    return Vector::ASC::Event::EventType::MostCommonRegisterEvent; }
^{MOST_Time}" "{MOST_Channel}" HWMode: "{MOST_HWMode}" "{MOST_HWModeMask}\r?$ {
    return Vector::ASC::Event::EventType::MostHwModeEvent; }
^{MOST_Time}" "{MOST_Channel}" NetState: "{MOST_NetStateOld}" "{MOST_NetStateNew}\r?$ {
    return Vector::ASC::Event::EventType::MostNetStateEvent; }
^{MOST_Time}" "{MOST_Channel}" DataLost: "{MOST_DLInfo}" "{MOST_DLCtrl}" "{MOST_DLAsync}" "{MOST_DLTime}" "{MOST_DLTime}\r?$ {
    return Vector::ASC::Event::EventType::MostDataLostEvent; }
^{MOST_Time}" "{MOST_Channel}" Trigger: "{MOST_TrigMode}" "{MOST_TrigHW}" "{MOST_TrigValue}" "{MOST_TrigValue}\r?$ {
    return Vector::ASC::Event::EventType::MostTriggerEvent; }
^{MOST_Time}" "{MOST_Channel}" MostStatistic: Fr: "{MOST_StatVal}" Lt: "{MOST_StatVal}" Bl: "{MOST_StatVal}" Pk: "{MOST_StatVal}\r?$ {
    return Vector::ASC::Event::EventType::MostStatisticEvent; }
^{MOST_Time}" "{MOST_Channel}" StatEx: "{MOST_CodingErrors}" "{MOST_FrameCounter}\r?$ {
    return Vector::ASC::Event::EventType::MostStatisticExtendedEvent; }
^{MOST_Time}" "{MOST_Channel}" TxLight: "{MOST_TxLightState}\r?$ {
    return Vector::ASC::Event::EventType::MostTxLight; }
^{MOST_Time}" "{MOST_Channel}" Stress: "{MOST_StressMode}" "{MOST_StressState}\r?$ {
    return Vector::ASC::Event::EventType::MostStressEvent; }
^{MOST_Time}" "{MOST_Channel}" AllocTab: "{MOST_AllocTableSize}(" "{MOST_DxAT})*\r?$ {
    return Vector::ASC::Event::EventType::Most25AllocTable; }
^{MOST_Time}" "{MOST_Channel}" Msg150: "{MOST_Dir}" "{MOST_SourceAdr}" "{MOST_DestAdr}" "{MOST_State}" "{MOST_AckNack}" "{MOST_TransferType}" "{MOST_Pack}" "{MOST_Priority}" "{MOST_Pindex}" "{MOST_CRC2}" "{MOST_Cack}" "{MOST_RsvdUL}" "{MOST_Msg150Len}(" "{MOST_Dx})+\r?$ {
    return Vector::ASC::Event::EventType::Most150ControlMessage; }
^{MOST_Time}" "{MOST_Channel}" Msg150Frg: "{MOST_FrgMask}" "{MOST_SourceAdr}" "{MOST_DestAdr}" "{MOST_AckNack}" "{MOST_PAck}" "{MOST_Priority}" "{MOST_Pindex}" "{MOST_CRC2}" "{MOST_Cack}" "{MOST_RsvdUL}" "{MOST_FrgDataLen}" "{MOST_FrgDataLenAnnounced}" "{MOST_FirstDataLen}(" "{MOST_Dx})+\r?$ {
    return Vector::ASC::Event::EventType::Most150ControlMessageFragment; }
^{MOST_Time}" "{MOST_Channel}" Pkt150: "{MOST_Dir}" "{MOST_SourceAdr}" "{MOST_DestAdr}" "{MOST_State}" "{MOST_AckNack}" "{MOST_TransferType}" "{MOST_Pack}" "{MOST_RsvdUC}" "{MOST_Pindex}" "{MOST_CRC2}" "{MOST_Cack}" "{MOST_RsvdUL}" "{MOST_Pkt150Len}(" "{MOST_Dx})+\r?$ {
    return Vector::ASC::Event::EventType::Most150Packet; }
^{MOST_Time}" "{MOST_Channel}" Pkt150Frg: "{MOST_FrgMask}" "{MOST_SourceAdr}" "{MOST_DestAdr}" "{MOST_AckNack}" "{MOST_PAck}" "{MOST_RsvdUC}" "{MOST_Pindex}" "{MOST_CRC2}" "{MOST_Cack}" "{MOST_RsvdUL}" "{MOST_FrgDataLen}" "{MOST_FrgDataLenAnnounced}" "{MOST_FirstDataLen}(" "{MOST_Dx})+\r?$ {
    return Vector::ASC::Event::EventType::Most150PacketFragment; }
^{MOST_Time}" "{MOST_Channel}" PktEth: "{MOST_Dir}" "{MOST_SourceMacAdr}" "{MOST_DestMacAdr}" "{MOST_State}" "{MOST_AckNack}" "{MOST_TransferType}" "{MOST_Pack}" "{MOST_CRC4}" "{MOST_Cack}" "{MOST_RsvdUL}" "{MOST_PktEthLen}(" "{MOST_Dx})+\r?$ {
    return Vector::ASC::Event::EventType::MostEthernetPacket; }
^{MOST_Time}" "{MOST_Channel}" PktEthFrg: "{MOST_FrgMask}" "{MOST_SourceMacAdr}" "{MOST_DestMacAdr}" "{MOST_AckNack}" "{MOST_Pack}" "{MOST_CRC4}" "{MOST_Cack}" "{MOST_RsvdUL}" "{MOST_FrgDataLen}" "{MOST_FrgDataLenAnnounced}" "{MOST_FirstDataLen}(" "{MOST_Dx})+\r?$ {
    return Vector::ASC::Event::EventType::MostEthernetPacketFragment; }
^{MOST_Time}" "{MOST_Channel}" System: "{MOST_SysID}" "{MOST_SysValue}" "{MOST_SysValueOld}\r?$ {
    return Vector::ASC::Event::EventType::MostSystemEvent; }
^{MOST_Time}" "{MOST_Channel}" AT150: "{MOST_AT150EventModeFlags}" "{MOST_FreeBytes}" "{MOST_AT150Size}(" "{MOST_Wx})*\r?$ {
    return Vector::ASC::Event::EventType::Most150AllocTable; }
^{MOST_Time}" "{MOST_Channel}" Msg50: "{MOST_Dir}" "{MOST_SourceAdr}" "{MOST_DestAdr}" "{MOST_State}" "{MOST_AckNack}" "{MOST_TransferType}" "{MOST_RsvdUC}" "{MOST_Priority}" "{MOST_RsvdUC}" "{MOST_CRC2}" "{MOST_RsvdUC}" "{MOST_RsvdUL}" "{MOST_Msg50Len}(" "{MOST_Dx})+\r?$ {
    return Vector::ASC::Event::EventType::Most50ControlMessage; }
^{MOST_Time}" "{MOST_Channel}" Pkt50: "{MOST_Dir}" "{MOST_SourceAdr}" "{MOST_DestAdr}" "{MOST_State}" "{MOST_AckNack}" "{MOST_TransferType}" "{MOST_RsvdUC}" "{MOST_RsvdUC}" "{MOST_RsvdUC}" "{MOST_CRC2}" "{MOST_RsvdUC}" "{MOST_RsvdUL}" "{MOST_PktLen}(" "{MOST_Dx})+\r?$ {
    return Vector::ASC::Event::EventType::Most50Packet; }
^{MOST_Time}" "{MOST_Channel}" Ecl: "{MOST_EclMode}" "{MOST_EclState}\r?$ {
    return Vector::ASC::Event::EventType::MostEcl; }

    /* TP/Diagnostics Events */
^"// "{TPDiag_CANChannel}" OTP("{TPDiag_connectionId}") "{TPDiag_type}" "{TPDiag_source}"->"{TPDiag_destination}":"\r?$ {
    return Vector::ASC::Event::EventType::TpDiagPrefix; }
^"SF Length: "{TPDiag_length}" ["{TPDiag_transportedBytes}" ]"\r?$ {
    return Vector::ASC::Event::EventType::TpDiagSingleFrame; }
^"FF Length: "{TPDiag_length}" ["{TPDiag_transportedBytes}" ]"\r?$ {
    return Vector::ASC::Event::EventType::TpDiagFirstFrame; }
^"CF Seq.Nr.: "{TPDiag_SN}" ["{TPDiag_transportedBytes}" ]"\r?$ {
    return Vector::ASC::Event::EventType::TpDiagConsecutiveFrame; }
^"FC."{TPDiag_FCType}": BSmax: 0x"{TPDiag_BS}", STmin: 0x"{TPDiag_STmin}" ms"\r?$ {
    return Vector::ASC::Event::EventType::TpDiagFlowControlFrame; }
^{TPDiag_timestamp}" DiagRequest["{TPDiag_ECUQualifier}"]"{TPDiag_byteSequence}\r?$ {
    return Vector::ASC::Event::EventType::TpDiagRequest; }

    /* Comment */
^"// ".*\r?$ {
    return Vector::ASC::Event::EventType::FileComment; }

    /* remaining characters */
^.*\r? { return Vector::ASC::Event::EventType::Unknown; }

%%

