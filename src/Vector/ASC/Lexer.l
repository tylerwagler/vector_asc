%{
#include <Vector/ASC/Event.h>
%}

    // Options Affecting Scanner Behavior
%option yylineno
%option noyywrap

    // Code-Level And API Options
%option c++
%option prefix="asc"

    // Debugging Options
%option warn

    // Format Symbols
STOL ^[[:blank:]]*
ENDL [[:blank:]]*[\r\n]*$
WS [[:blank:]]+
ws [[:blank:]]*

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
Error .+?
Dx [[:xdigit:]]{1,3}
WeekDay ("Mon"|"Tue"|"Wed"|"Thu"|"Fri"|"Sat"|"Sun"|"Mon"|"Die"|"Mit"|"Don"|"Fre"|"Sam"|"Son")
Month ("Jan"|"Feb"|"Mar"|"Apr"|"May"|"Jun"|"Jul"|"Aug"|"Sep"|"Oct"|"Nov"|"Dec"|"Jan"|"Feb"|"M\xE4r"|"Apr"|"Mai"|"Jun"|"Jul"|"Aug"|"Sep"|"Okt"|"Nov"|"Dez")
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
FlexRayOld_Channel "Fr "[12*]
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
LIN_Dx [[:xdigit:]]{1,3}
LIN_description .+?
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
LIN_syncBreakTime [[:digit:]]+{ws}"us"{ws}"("[[:digit:].]+{ws}"bits)"
LIN_syncDelimiterTime [[:digit:]]+{ws}"us"{ws}"("[[:digit:].]+{ws}"bits)"
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
TPDiag_transportedBytes ({WS}[[:xdigit:]]+)*
TPDiag_SN [[:xdigit:]]{1,4}
TPDiag_FCType ("CTS"|"WT"|"OVFLW")
TPDiag_BS [[:xdigit:]]{1,4}
TPDiag_STmin [[:xdigit:]]{1,4}
TPDiag_timestamp [[:digit:].]{3,}
TPDiag_ECUQualifier [[:alnum:]_]+
TPDiag_byteSequence ({WS}[[:xdigit:]]+)*

%%

    /* File */
{STOL}"date"{WS}{WeekDay}{WS}{Month}{WS}{Date}{WS}{FullTime}{WS}{Year}{ENDL} {
    return Vector::ASC::Event::EventType::FileDate; }
{STOL}"base"{WS}("hex"|"dec"){WS}"timestamps"{WS}("absolute"|"relative"){ENDL} {
    return Vector::ASC::Event::EventType::FileBaseTimestamps; }
{STOL}("no ")?"internal events logged"{ENDL} {
    return Vector::ASC::Event::EventType::FileInternalEventsLogged; }
{STOL}"//"{ws}"version"{WS}[[:digit:]]{1,3}"."[[:digit:]]{1,3}"."[[:digit:]]{1,3}{ENDL} {
    return Vector::ASC::Event::EventType::FileVersion; }
{STOL}"//"{ws}{Time}{WS}"previous log file:"{ws}.+?{ENDL} {
    return Vector::ASC::Event::EventType::FileSplitInformation; }
    /* comment must be non-greedy, so moved to the end */

    /* CAN Events */
{STOL}{Time}{WS}{Channel}{WS}{ID}{WS}{Dir}{WS}"d"{WS}{DLC}({WS}{Dx}){0,8}({WS}"Length"{ws}"="{ws}{MessageDuration})?({WS}"BitCount"{ws}"="{ws}{MessageLength})?({WS}{MessageFlags})?({WS}"ID"{ws}"="{ws}{IDnum})?{ENDL} {
    return Vector::ASC::Event::EventType::CanMessage; }
{STOL}{Time}{WS}{Channel}{WS}{ID}"x"{WS}{Dir}{WS}"d"{WS}{DLC}({WS}{Dx}){0,8}({WS}"Length"{ws}"="{ws}{MessageDuration})?({WS}"BitCount"{ws}"="{ws}{MessageLength})?({WS}{MessageFlags})?({WS}"ID"{ws}"="{ws}{IDnum}"x")?{ENDL} {
    return Vector::ASC::Event::EventType::CanExtendedMessage; }
{STOL}{Time}{WS}{Channel}{WS}{ID}{WS}{Dir}{WS}"r"{ENDL} {
    return Vector::ASC::Event::EventType::CanRemoteFrame; }
{STOL}{Time}{WS}{Channel}{WS}"ErrorFrame"({WS}"ECC:"{ws}[01]+)?({WS}"Flags"{ws}"="{ws}"0x"[[:xdigit:]]+)?({WS}"CodeExt"{ws}"="{ws}"0x"[[:xdigit:]]+)?({WS}"Code"{ws}"="{ws}"0x"[[:xdigit:]]+)?({WS}"ID"{ws}"="{ws}[[:digit:]]+)?({WS}"DLC"{ws}"="{ws}[[:xdigit:]]{1,2})?({WS}"Position"{ws}"="{ws}[[:digit:]]+)?({WS}"Length"{ws}"="{ws}[[:digit:]]+)?{ENDL} {
    return Vector::ASC::Event::EventType::CanErrorFrame; }
{STOL}{Time}{WS}{Channel}{WS}"Statistic:"{WS}"D"{WS}{StatNumber}{WS}"R"{WS}{StatNumber}{WS}"XD"{WS}{StatNumber}{WS}"XR"{WS}{StatNumber}{WS}"E"{WS}{StatNumber}{WS}"O"{WS}{StatNumber}{WS}"B"{WS}{StatPercent}"%"{ENDL} {
    return Vector::ASC::Event::EventType::CanBusStatistics; }
{STOL}{Time}{WS}"CAN"{WS}{Channel}{WS}"Status:"{ws}{Error}{ENDL} {
    return Vector::ASC::Event::EventType::CanError; }
{STOL}{Time}{WS}{Channel}{WS}"OverloadFrame"{ENDL} {
    return Vector::ASC::Event::EventType::CanOverloadFrame; }

    /* CAN FD Events */
{STOL}{Time}{WS}"CANFD"{WS}{Channel}{WS}{Dir}{WS}{ID}({WS}[[:alnum:]_]+)?{WS}{BRS}{WS}{ESI}{WS}{DLC}{WS}{DataLength}({WS}{Dx}){0,64}{WS}{MessageDuration}{WS}{MessageLength}{WS}[[:digit:]]+{WS}[[:xdigit:]]+{WS}{BitTimingConfArb}{WS}{BitTimingConfData}{ENDL} {
    return Vector::ASC::Event::EventType::CanFdMessage; }
{STOL}{Time}{WS}"CANFD"{WS}{Channel}{WS}{Dir}{WS}{ID}"x"({WS}[[:alnum:]_]+)?{WS}{BRS}{WS}{ESI}{WS}{DLC}{WS}{DataLength}({WS}{Dx}){0,64}{WS}{MessageDuration}{WS}{MessageLength}{WS}[[:digit:]]+{WS}[[:xdigit:]]+{WS}{BitTimingConfArb}{WS}{BitTimingConfData}{ENDL} {
    return Vector::ASC::Event::EventType::CanFdExtendedMessage; }
{STOL}{Time}{WS}"CANFD"{WS}{Channel}{WS}{Dir}{WS}"ErrorFrame"{WS}"Not Acknowledge error, dominant error flag"{WS}[[:xdigit:]]{4}{WS}[[:xdigit:]]{2}{WS}[[:xdigit:]]{4}{WS}"Data"{WS}[[:digit:]]+{WS}{ID}{WS}{BRS}{WS}{ESI}{WS}{DLC}{WS}{DataLength}({WS}{Dx}){0,64}{WS}{MessageDuration}{WS}[[:digit:]]+{WS}[[:xdigit:]]+{WS}{BitTimingConfArb}{WS}{BitTimingConfData}{ENDL} {
    return Vector::ASC::Event::EventType::CanFdErrorFrame; }
    /* return Vector::ASC::Event::EventType::CanFdBusStatistics; }
    /* return Vector::ASC::Event::EventType::CanFdOverloadFrame; }

    /* Log and Trigger Events */
{STOL}{Time}{WS}"log trigger event"{ws}.+?{ENDL} {
    return Vector::ASC::Event::EventType::LogTrigger; }
{STOL}{Time}{WS}"log direct start"{ws}"("{PreTrigger}"ms)"{ENDL} {
    return Vector::ASC::Event::EventType::LogDirectStart; }
{STOL}{Time}{WS}"log direct stop"{ws}"("{PostTrigger}"ms)"{ENDL} {
    return Vector::ASC::Event::EventType::LogDirectStop; }
{STOL}"Begin Triggerblock"{WS}{WeekDay}{WS}{Month}{WS}{Date}{WS}{FullTime}{WS}{Year}{ENDL} {
    return Vector::ASC::Event::EventType::BeginTriggerblock; }
{STOL}"End TriggerBlock"{ENDL} {
    return Vector::ASC::Event::EventType::EndTriggerblock; }

    /* Environment Variables */
{STOL}{Time}{WS}.+?{ws}":="{ws}.+?{ENDL} {
    return Vector::ASC::Event::EventType::EnvironmentVariables; }

    /* System Variables */
{STOL}{Time}{WS}"SV:"{ws}{svtype}{WS}"0"{WS}"0"{WS}.+?{ws}"="{ws}.+?{ENDL} {
    return Vector::ASC::Event::EventType::SystemVariables; }

    /* Macros Signal Events */
{STOL}{Time}{WS}[LF]?[[:digit:]]+{WS}.+?"::".+?"::".+?{ws}"="{ws}.+?{ENDL} {
    return Vector::ASC::Event::EventType::MacroSignal; }

    /* GPS events */
{STOL}{Time}{WS}"GPS-Device:"{ws}[[:digit:]]+{WS}"La:"{ws}[[:digit:].]+{WS}"Lo:"{ws}[[:digit:].]+{WS}"Alt:"{ws}[[:digit:].]+{WS}"Sp:"{ws}[[:digit:].]+{WS}"Co:"{ws}[[:digit:].]+{ENDL} {
    return Vector::ASC::Event::EventType::Gps; }

    /* Comment events */
{STOL}{Time}{WS}"Comment:"{ws}[[:digit:]]+{WS}.+?{ENDL} {
    return Vector::ASC::Event::EventType::Comment; }

    /* Global market events */
{STOL}{Time}{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[01]{WS}"GMGroup:"{ws}.+?{WS}"GMMarker:"{ws}.+?{WS}"GMDescription:"{ws}.+?{ENDL} {
    return Vector::ASC::Event::EventType::GlobalMarker; }

    /* Ethernet Events */
{STOL}{Eth_Time}{WS}"ETH"{WS}{Eth_Channel}{WS}{Eth_Dir}{WS}{Eth_DataLen}":"{Eth_Data}{ENDL} {
    return Vector::ASC::Event::EventType::EthernetPacket; }
{STOL}{Eth_Time}{WS}"ETH"{WS}{Eth_Channel}{WS}"STAT"{WS}"Link:"{ws}.+?{WS}"LinkSpeed:"{ws}.+?{WS}"Physical:"{ws}.+?{WS}"Duplex:"{ws}.+?{WS}"MDI:"{ws}.+?{WS}"Connector:"{ws}.+?{ENDL} {
    return Vector::ASC::Event::EventType::EthernetStatus; }
{STOL}{Eth_Time}{WS}"ETH"{WS}{Eth_Channel}{WS}"RxEr"{WS}{Eth_ErrorCode}{WS}{Eth_FrameChecksum}{WS}{Eth_DataLen}":"{Eth_Data}{ENDL} {
    return Vector::ASC::Event::EventType::EthernetRxError; }

    /* AFDX Events */
{STOL}{Afdx_Time}{WS}"AFDX"{WS}{Afdx_Channel}{WS}{Afdx_Dir}{WS}{Afdx_EthChannel}{WS}{Afdx_Flags}{WS}{Afdx_BAG}{WS}{Afdx_DataLen}":"{Afdx_Data}{ENDL} {
    return Vector::ASC::Event::EventType::AfdxPacket; }

    /* FlexRay Events (Old Format) */
{STOL}{FlexRayOld_Time}{WS}{FlexRayOld_Channel}{WS}"V9"{WS}{FlexRayOld_ID}{WS}{FlexRayOld_Cycle}{WS}{FlexRayOld_NM}{WS}{FlexRayOld_Sync}{WS}{FlexRayOld_HeaderCRC}{WS}{FlexRayOld_SymbolicName}{WS}{FlexRayOld_DLC}({WS}{FlexRayOld_Dx}){0,255}{WS}{FlexRayOld_FrameState}{WS}{FlexRayOld_HeaderBitMask}{ENDL} {
    return Vector::ASC::Event::FlexRayOldMessage; }
{STOL}{FlexRayOld_Time}{WS}{FlexRayOld_Channel}{WS}"StartCycleEvent"{WS}"NM Vector:"{ws}{FlexRayOld_DLC}({WS}{FlexRayOld_Dx}){0,255}{ENDL} {
    return Vector::ASC::Event::FlexRayOldStartCycle; }
    /* FlexRayOldErrorFrameEvent */

    /* FlexRay Events (New Format) */
{STOL}{FlexRay_Time}{WS}"Fr"{WS}"RMSG"{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}{FlexRay_Dir}{WS}[[:digit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[[:alnum:]_\[\|\]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+({WS}[[:xdigit:]]+){0,254}{WS}[[:xdigit:]]+{WS}[01]{WS}[[:digit:]]+{ENDL} {
    return Vector::ASC::Event::FlexRayMessage; }
{STOL}{FlexRay_Time}{WS}"Fr"{WS}"PDU"{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}{FlexRay_Dir}{WS}[[:digit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[[:alnum:]_\[\|\]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+({WS}[[:xdigit:]]+){0,254}{WS}[[:xdigit:]]+{WS}[01]{WS}[[:digit:]]+{WS}[[:digit:]]+{ENDL} {
    return Vector::ASC::Event::FlexRayMessage; }
{STOL}{FlexRay_Time}{WS}"Fr"{WS}"SCE"{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:xdigit:]]+{WS}{FlexRay_Dir}{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}"NM_Vector:"{ws}[[:xdigit:]]+({WS}[[:xdigit:]]+){0,12}{ENDL} {
    return Vector::ASC::Event::FlexRayStartCycle; }
{STOL}{FlexRay_Time}{WS}"Fr"{WS}"SE"{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:xdigit:]]+{WS}[[:digit:]]+{WS}[012]{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[01234]{WS}[[:digit:]]+{WS}[01]{ENDL} {
    return Vector::ASC::Event::FlexRayStatus; }
{STOL}{FlexRay_Time}{WS}"Fr"{WS}"EE"{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{WS}[[:xdigit:]]+{ENDL} {
    return Vector::ASC::Event::FlexRayError; }

    /* K-Line Events */
{STOL}{KLine_time}{WS}{KLine_port}{WS}{KLine_direction}{WS}{KLine_baudrate}{WS}{KLine_length}({WS}{KLine_data})*{ENDL} {
    return Vector::ASC::Event::EventType::KLineByte; }
{STOL}"//"{ws}"K-Line:"{ws}{KLine_time}{WS}{KLine_port}{WS}{KLine_direction}{WS}{KLine_baudrate}{WS}{KLine_source}{WS}{KLine_destination}{WS}{KLine_length}({WS}{KLine_data})*{ENDL} {
    return Vector::ASC::Event::EventType::KLineMessage; }

    /* LIN Events */
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}{LIN_ID}{WS}{LIN_Dir}{WS}{LIN_DLC}({WS}{LIN_Dx}){0,8}({WS}"slave"{ws}"="{ws}{LIN_slaveId}","{ws}"state"{ws}"="{ws}{LIN_state})?{WS}"checksum"{ws}"="{ws}{LIN_checksum}{WS}"header time"{ws}"="{ws}{LIN_headerTime}","{ws}"full time"{ws}"="{ws}{LIN_fullTime}(({WS}"start of frame"{ws}"="{ws}{LIN_startOfFrame}","{ws}"sync break"{ws}"="{ws}{LIN_syncBreakTime}","{ws}"sync delimiter"{ws}"="{ws}{LIN_syncDelimiterTime})|({WS}"SOF"{ws}"="{ws}{LIN_startOfFrame}{WS}"BR"{ws}"="{ws}{LIN_baudrate}{WS}"break"{ws}"="{ws}{LIN_SyncBreak}{WS}{LIN_SyncDel}({WS}"subId"{ws}"="{ws}{LIN_NAD}{WS}{LIN_MessageId}{WS}{LIN_SupplierId})?{WS}"EOH"{ws}"="{ws}{LIN_endOfHeader}{WS}"EOB"{ws}"="({ws}{LIN_T}){0,8}{WS}"sim"{ws}"="{ws}{LIN_simulated}({WS}"EOF"{ws}"="{ws}{LIN_endOfFrame}({WS}"RBR"{ws}"="{ws}{LIN_responseBaudrate}({WS}"HBR"{ws}"="{ws}{LIN_headerBaudrate}{WS}"HSO"{ws}"="{ws}{LIN_stopBitOffsetInHeader}{WS}"RSO"{ws}"="{ws}{LIN_stopBitOffsetInResponse}({WS}"CSM"{ws}"="{ws}{LIN_checksumModel})?)?)?)?)){ENDL} {
    return Vector::ASC::Event::EventType::LinMessage; }

    /* LIN Error Events */
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}{LIN_ID}{WS}"TransmErr"({WS}"slave"{ws}"="{ws}{LIN_slaveId}","{ws}"state"{ws}"="{ws}{LIN_state})?{WS}"header time"{ws}"="{ws}{LIN_headerTime}","{ws}"full time"{ws}"="{ws}{LIN_fullTime}({WS}"SOF"{ws}"="{ws}{LIN_startOfFrame}{WS}"BR"{ws}"="{ws}{LIN_baudrate}{WS}"break"{ws}"="{ws}{LIN_SyncBreak}{WS}{LIN_SyncDel}("subId"{ws}"="{ws}{LIN_NAD}{WS}{LIN_MessageId}{WS}{LIN_SupplierId})?{WS}"EOH"{ws}"="{ws}{LIN_endOfHeader}({WS}"HBR"{ws}"="{ws}{LIN_headerBaudrate}{WS}"HSO"{ws}"="{ws}{LIN_stopBitOffsetInHeader}({WS}"CSM"{ws}"="{ws}{LIN_checksumModel})?)?)?{ENDL} {
    return Vector::ASC::Event::EventType::LinTransmissionError; }
{STOL}{LIN_Time}{WS}{LIN_Channel}({WS}{LIN_ID}{WS}{LIN_DLC})?{WS}"RcvError:"{ws}{LIN_description}({WS}"char"{ws}"="{ws}{LIN_offendingByte})?({WS}"slave"{ws}"="{ws}{LIN_slaveId}","{ws}"state"{ws}"="{ws}{LIN_state})?({WS}"StateReason"{ws}"="{ws}{LIN_StateReason}{WS}"ShortError"{ws}"="{ws}{LIN_IsShortError}{WS}"DlcTimeout"{ws}"="{ws}{LIN_IsDLCTimeout}{WS}"HasDatabytes"{ws}"="{ws}{LIN_HasDatabytes}({WS}{LIN_Dx}){0,8}{WS}"SOF"{ws}"="{ws}{LIN_startOfFrame}{WS}"BR"{ws}"="{ws}{LIN_baudrate}{WS}"break"{ws}"="{ws}{LIN_SyncBreak}{WS}{LIN_SyncDel}({WS}"subId"{ws}"="{ws}{LIN_NAD}{WS}{LIN_MessageId}{WS}{LIN_SupplierId})?({WS}"EOH"{ws}"="{ws}{LIN_endOfHeader})?({WS}"EOB"{ws}"="{ws}({WS}{LIN_T}){0,8})?({WS}"RBR"{ws}"="{ws}{LIN_responseBaudrate}({WS}"HBR"{ws}"="{ws}{LIN_headerBaudrate}{WS}"HSO"{ws}"="{ws}{LIN_stopBitOffsetInHeader}{WS}"RSO"{ws}"="{ws}{LIN_stopBitOffsetInResponse}({WS}"CSM"{ws}"="{ws}{LIN_checksumModel})?)?)?)?{ENDL} {
    return Vector::ASC::Event::EventType::LinReceiveError; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}"SyncError"({WS}{LIN_TimeInterval}){4}({WS}"SOF"{ws}"="{ws}{LIN_startOfFrame}{WS}"BR"{ws}"="{ws}{LIN_baudrate}{WS}"break"{ws}"="{ws}{LIN_SyncBreak}{WS}{LIN_SyncDel})?{ENDL} {
    return Vector::ASC::Event::EventType::LinSyncError; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}{LIN_ID}{WS}"CSErr"{WS}{LIN_Dir}{WS}{LIN_DLC}({WS}[[:xdigit:]]+){0,8}({WS}"slave"{ws}"="{ws}{LIN_slaveId}","{ws}"state"{ws}"="{ws}{LIN_state})?{WS}"checksum"{ws}"="{ws}{LIN_checksum}{WS}"header time"{ws}"="{ws}{LIN_headerTime}","{ws}"full time"{ws}"="{ws}{LIN_fullTime}({WS}"SOF"{ws}"="{ws}{LIN_startOfFrame}{WS}"BR"{ws}"="{ws}{LIN_baudrate}{WS}"break"{ws}"="{ws}{LIN_SyncBreak}{WS}{LIN_SyncDel}({WS}"subId"{ws}"="{ws}{LIN_NAD}{WS}{LIN_MessageId}{WS}{LIN_SupplierId})?{WS}"EOH"{ws}"="{ws}{LIN_endOfFrame}{WS}"EOB"{ws}"="({WS}{LIN_T}){0,8}{WS}"sim"{ws}"="{ws}{LIN_simulated}({WS}"EOF"{ws}"="{ws}{LIN_endOfFrame}({WS}"RBR"{ws}"="{ws}{LIN_responseBaudrate}({WS}"HBR"{ws}"="{ws}{LIN_headerBaudrate}{WS}"HSO"{ws}"="{ws}{LIN_stopBitOffsetInHeader}{WS}"RSO"{ws}"="{ws}{LIN_stopBitOffsetInResponse}({WS}"CSM"{ws}"="{ws}{LIN_checksumModel})?)?)?)?)?{ENDL} {
    return Vector::ASC::Event::EventType::LinChecksumError; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}"Spike"{WS}{LIN_Dir}{WS}{LIN_SpikeLength}{WS}"microseconds"({WS}"SOF"{ws}"="{ws}{LIN_startOfFrame}{WS}"BR"{ws}"="{ws}{LIN_baudrate}{ws})?{ENDL} {
    return Vector::ASC::Event::EventType::LinSpike; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}"Dominant signal"{WS}{LIN_DomSigState}{WS}{LIN_DomSigLength}{WS}"microseconds"({WS}"SOF"{ws}"="{ws}{LIN_startOfFrame}{WS}"BR"{ws}"="{ws}{LIN_baudrate}{ws})?{ENDL} {
    return Vector::ASC::Event::EventType::LinDominantSignal; }

    /* LIN Info Events */
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}"Baudrate"{WS}{LIN_baudrate}{ENDL} {
    return Vector::ASC::Event::EventType::LinBaudrate; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}{LIN_ID}{WS}"DlcInfo"{WS}{LIN_DLC}{ENDL} {
    return Vector::ASC::Event::EventType::LinDlcInfo; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}{LIN_ID}{WS}"CSInfo"{WS}{LIN_checksumModelInfo}{ENDL} {
    return Vector::ASC::Event::EventType::LinChecksumInfo; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}"SchedModChng"{WS}"prior scheduler mode"{ws}"="{ws}{LIN_scheduleTableIndex}","{ws}"next scheduler mode"{ws}"="{ws}{LIN_scheduleTableIndex}{ENDL} {
    return Vector::ASC::Event::EventType::LinSchedulerModeChange; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}"SlaveTimeout"{WS}"slave-id"{ws}"="{ws}{LIN_slaveId}","{ws}"current state"{ws}"="{ws}{LIN_state}","{ws}"following state"{ws}"="{ws}{LIN_state}{ENDL} {
    return Vector::ASC::Event::EventType::LinSlaveTimeout; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}{LIN_ID}{WS}"EvTrigFrmInfo"{WS}{LIN_ETFName}{WS}{LIN_description}{ENDL} {
    return Vector::ASC::Event::EventType::LinEventTriggeredFrameInfo; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}"Statistic"{WS}[[:digit:]]+{WS}[[:digit:].]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{WS}[[:digit:]]+{ENDL} {
    return Vector::ASC::Event::EventType::LinStatisticInfo; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}{LIN_ID}{WS}{LIN_DLC}{WS}"ShortOrSlowResponse:"{ws}"NumRespBytes"{ws}"="{ws}{LIN_NumberOfResponseBytes}({WS}[[:xdigit:]]+){0,9}{WS}"SlowResponse"{ws}"="{ws}{LIN_IsSlowResponse}{WS}"InterruptedByBreak"{ws}"="{ws}{LIN_ResponseWasInterruptedByBreak}{WS}"SOF"{ws}"="{ws}{LIN_startOfFrame}{WS}"BR"{ws}"="{ws}{LIN_baudrate}{WS}"break"{ws}"="{ws}{LIN_SyncBreak}{WS}{LIN_SyncDel}("subId"{ws}"="{ws}{LIN_NAD}{WS}{LIN_MessageId}{WS}{LIN_SupplierId})?{WS}"EOH"{ws}"="{ws}{LIN_endOfHeader}{WS}"EOB"{ws}"="({WS}{LIN_T}){0,8}{WS}"HBR"{ws}"="{ws}{LIN_headerBaudrate}{WS}"HSO"{ws}"="{ws}{LIN_stopBitOffsetInHeader}{WS}"CSM"{ws}"="{ws}{LIN_checksumModel}{ENDL} {
    return Vector::ASC::Event::EventType::LinShortOrSlowResponse; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}"DisturbanceEvent"{WS}"Type"{ws}"="{ws}{LIN_DisturbanceType}{WS}"ByteIndex"{ws}"="{ws}{LIN_ByteIndex}{WS}"BitIndex"{ws}"="{ws}{LIN_BitIndex}{WS}"BitOffset"{ws}"="{ws}{LIN_BitOffsetInSixteenthBits}{WS}"Length"{ws}"="{ws}{LIN_DisturbanceLengthInSixteenthBits}{WS}"Header"{ws}"="{ws}{LIN_IDorFF}{WS}"Disturbing header"{ws}"="{ws}{LIN_IDorFF}{ENDL} {
    return Vector::ASC::Event::EventType::LinDisturbance; }

    /* LIN Sleep/Wakeup Events */
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}"SleepModeEvent"{WS}{LIN_simulated}{WS}{LIN_description}{ENDL} {
    return Vector::ASC::Event::EventType::LinSleepMode; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}"WakeupFrame"{WS}{LIN_Dir}{WS}{LIN_WakeupByte}({WS}"SOF"{ws}"="{ws}{LIN_startOfFrame}{WS}"BR"{ws}"="{ws}{LIN_baudrate}{WS}"LengthCode"{ws}"="{ws}{LIN_WakeupLengthInfo})?{ENDL} {
    return Vector::ASC::Event::EventType::LinWakeupFrame; }
{STOL}{LIN_Time}{WS}{LIN_Channel}{WS}"Unexpected wakeup:"(({ws}"approx\."{ws}{LIN_Width}{ws}"us")|({ws}"Signal"{ws}"="{ws}{LIN_WakeupByte})){WS}"SOF"{ws}"="{ws}{LIN_startOfFrame}{WS}"BR"{ws}"="{ws}{LIN_baudrate}{ENDL} {
    return Vector::ASC::Event::EventType::LinUnexpectedWakeup; }

    /* MOST Events */
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}{MOST_Dir}{WS}{MOST_SourceAdr}{WS}{MOST_DestAdr}{WS}{MOST_RType}({WS}{MOST_Dx}){17}{WS}{MOST_State2}{ENDL} {
    return Vector::ASC::Event::EventType::Most25ControlMessageNodeMode; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"Rx"{WS}{MOST_SourceAdr}{WS}{MOST_DestAdr}{WS}{MOST_RType}({WS}{MOST_Dx}){17}{WS}{MOST_State}{WS}{MOST_AckNack}{WS}{MOST_CRC}{ENDL} {
    return Vector::ASC::Event::EventType::Most25ControlMessageSpyMode; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"Pkt:"{ws}{MOST_Dir}{WS}{MOST_SourceAdr}{WS}{MOST_DestAdr}{WS}{MOST_PktState}{WS}{MOST_TransferType}{WS}{MOST_PktPrio}{WS}{MOST_PktArbitr}{WS}{MOST_CRC2}{WS}{MOST_PktLen}({WS}{MOST_Dx})+{ENDL} {
    return Vector::ASC::Event::EventType::Most25Packet; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"LL:"{ws}{MOST_LLState}{ENDL} {
    return Vector::ASC::Event::EventType::MostLightLock; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"Register:"{ws}{MOST_RegSubType}{WS}{MOST_RegID}{WS}{MOST_RegValue}{ENDL} {
    return Vector::ASC::Event::EventType::MostSpecialRegister; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"RegData:"{ws}{MOST_RegSubType}{WS}{MOST_RegChip}{WS}{MOST_RegOffset}{WS}{MOST_RegDataLen}({WS}{MOST_Dx})*{ENDL} {
    return Vector::ASC::Event::EventType::MostCommonRegister; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"HWMode:"{ws}{MOST_HWMode}{WS}{MOST_HWModeMask}{ENDL} {
    return Vector::ASC::Event::EventType::MostHwMode; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"NetState:"{ws}{MOST_NetStateOld}{WS}{MOST_NetStateNew}{ENDL} {
    return Vector::ASC::Event::EventType::MostNetState; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"DataLost:"{ws}{MOST_DLInfo}{WS}{MOST_DLCtrl}{WS}{MOST_DLAsync}{WS}{MOST_DLTime}{WS}{MOST_DLTime}{ENDL} {
    return Vector::ASC::Event::EventType::MostDataLost; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"Trigger:"{ws}{MOST_TrigMode}{WS}{MOST_TrigHW}{WS}{MOST_TrigValue}{WS}{MOST_TrigValue}{ENDL} {
    return Vector::ASC::Event::EventType::MostTrigger; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"MostStatistic:"{ws}"Fr:"{ws}{MOST_StatVal}{WS}"Lt:"{ws}{MOST_StatVal}{WS}"Bl:"{ws}{MOST_StatVal}{WS}"Pk:"{ws}{MOST_StatVal}{ENDL} {
    return Vector::ASC::Event::EventType::MostStatistic; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"StatEx:"{ws}{MOST_CodingErrors}{WS}{MOST_FrameCounter}{ENDL} {
    return Vector::ASC::Event::EventType::MostStatisticExtended; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"TxLight:"{ws}{MOST_TxLightState}{ENDL} {
    return Vector::ASC::Event::EventType::MostTxLight; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"Stress:"{ws}{MOST_StressMode}{WS}{MOST_StressState}{ENDL} {
    return Vector::ASC::Event::EventType::MostStress; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"AllocTab:"{ws}{MOST_AllocTableSize}({WS}{MOST_DxAT})*{ENDL} {
    return Vector::ASC::Event::EventType::Most25AllocTable; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"Msg150:"{ws}{MOST_Dir}{WS}{MOST_SourceAdr}{WS}{MOST_DestAdr}{WS}{MOST_State}{WS}{MOST_AckNack}{WS}{MOST_TransferType}{WS}{MOST_Pack}{WS}{MOST_Priority}{WS}{MOST_Pindex}{WS}{MOST_CRC2}{WS}{MOST_Cack}{WS}{MOST_RsvdUL}{WS}{MOST_Msg150Len}({WS}{MOST_Dx})+{ENDL} {
    return Vector::ASC::Event::EventType::Most150ControlMessage; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"Msg150Frg:"{ws}{MOST_FrgMask}{WS}{MOST_SourceAdr}{WS}{MOST_DestAdr}{WS}{MOST_AckNack}{WS}{MOST_PAck}{WS}{MOST_Priority}{WS}{MOST_Pindex}{WS}{MOST_CRC2}{WS}{MOST_Cack}{WS}{MOST_RsvdUL}{WS}{MOST_FrgDataLen}{WS}{MOST_FrgDataLenAnnounced}{WS}{MOST_FirstDataLen}({WS}{MOST_Dx})+{ENDL} {
    return Vector::ASC::Event::EventType::Most150ControlMessageFragment; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"Pkt150:"{ws}{MOST_Dir}{WS}{MOST_SourceAdr}{WS}{MOST_DestAdr}{WS}{MOST_State}{WS}{MOST_AckNack}{WS}{MOST_TransferType}{WS}{MOST_Pack}{WS}{MOST_RsvdUC}{WS}{MOST_Pindex}{WS}{MOST_CRC2}{WS}{MOST_Cack}{WS}{MOST_RsvdUL}{WS}{MOST_Pkt150Len}({WS}{MOST_Dx})+{ENDL} {
    return Vector::ASC::Event::EventType::Most150Packet; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"Pkt150Frg:"{ws}{MOST_FrgMask}{WS}{MOST_SourceAdr}{WS}{MOST_DestAdr}{WS}{MOST_AckNack}{WS}{MOST_PAck}{WS}{MOST_RsvdUC}{WS}{MOST_Pindex}{WS}{MOST_CRC2}{WS}{MOST_Cack}{WS}{MOST_RsvdUL}{WS}{MOST_FrgDataLen}{WS}{MOST_FrgDataLenAnnounced}{WS}{MOST_FirstDataLen}({WS}{MOST_Dx})+{ENDL} {
    return Vector::ASC::Event::EventType::Most150PacketFragment; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"PktEth:"{ws}{MOST_Dir}{WS}{MOST_SourceMacAdr}{WS}{MOST_DestMacAdr}{WS}{MOST_State}{WS}{MOST_AckNack}{WS}{MOST_TransferType}{WS}{MOST_Pack}{WS}{MOST_CRC4}{WS}{MOST_Cack}{WS}{MOST_RsvdUL}{WS}{MOST_PktEthLen}({WS}{MOST_Dx})+{ENDL} {
    return Vector::ASC::Event::EventType::MostEthernetPacket; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"PktEthFrg:"{ws}{MOST_FrgMask}{WS}{MOST_SourceMacAdr}{WS}{MOST_DestMacAdr}{WS}{MOST_AckNack}{WS}{MOST_Pack}{WS}{MOST_CRC4}{WS}{MOST_Cack}{WS}{MOST_RsvdUL}{WS}{MOST_FrgDataLen}{WS}{MOST_FrgDataLenAnnounced}{WS}{MOST_FirstDataLen}({WS}{MOST_Dx})+{ENDL} {
    return Vector::ASC::Event::EventType::MostEthernetPacketFragment; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"System:"{ws}{MOST_SysID}{WS}{MOST_SysValue}{WS}{MOST_SysValueOld}{ENDL} {
    return Vector::ASC::Event::EventType::MostSystem; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"AT150:"{ws}{MOST_AT150EventModeFlags}{WS}{MOST_FreeBytes}{WS}{MOST_AT150Size}({WS}{MOST_Wx})*{ENDL} {
    return Vector::ASC::Event::EventType::Most150AllocTable; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"Msg50:"{ws}{MOST_Dir}{WS}{MOST_SourceAdr}{WS}{MOST_DestAdr}{WS}{MOST_State}{WS}{MOST_AckNack}{WS}{MOST_TransferType}{WS}{MOST_RsvdUC}{WS}{MOST_Priority}{WS}{MOST_RsvdUC}{WS}{MOST_CRC2}{WS}{MOST_RsvdUC}{WS}{MOST_RsvdUL}{WS}{MOST_Msg50Len}({WS}{MOST_Dx})+{ENDL} {
    return Vector::ASC::Event::EventType::Most50ControlMessage; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"Pkt50:"{ws}{MOST_Dir}{WS}{MOST_SourceAdr}{WS}{MOST_DestAdr}{WS}{MOST_State}{WS}{MOST_AckNack}{WS}{MOST_TransferType}{WS}{MOST_RsvdUC}{WS}{MOST_RsvdUC}{WS}{MOST_RsvdUC}{WS}{MOST_CRC2}{WS}{MOST_RsvdUC}{WS}{MOST_RsvdUL}{WS}{MOST_PktLen}({WS}{MOST_Dx})+{ENDL} {
    return Vector::ASC::Event::EventType::Most50Packet; }
{STOL}{MOST_Time}{WS}{MOST_Channel}{WS}"Ecl:"{ws}{MOST_EclMode}{WS}{MOST_EclState}{ENDL} {
    return Vector::ASC::Event::EventType::MostEcl; }

    /* TP/Diagnostics Events */
{STOL}"//"{ws}{TPDiag_CANChannel}{WS}"OTP("{TPDiag_connectionId}")"{WS}{TPDiag_type}{WS}{TPDiag_source}"->"{TPDiag_destination}":"{ws}"SF"{WS}"Length:"{ws}{TPDiag_length}{ws}"["{TPDiag_transportedBytes}{WS}"]"{ENDL} {
    return Vector::ASC::Event::EventType::TpSingleFrame; }
{STOL}"//"{ws}{TPDiag_CANChannel}{WS}"OTP("{TPDiag_connectionId}")"{WS}{TPDiag_type}{WS}{TPDiag_source}"->"{TPDiag_destination}":"{ws}"FF"{WS}"Length:"{ws}{TPDiag_length}{ws}"["{TPDiag_transportedBytes}{WS}"]"{ENDL} {
    return Vector::ASC::Event::EventType::TpFirstFrame; }
{STOL}"//"{ws}{TPDiag_CANChannel}{WS}"OTP("{TPDiag_connectionId}")"{WS}{TPDiag_type}{WS}{TPDiag_source}"->"{TPDiag_destination}":"{ws}"CF"{WS}"Seq.Nr.:"{ws}{TPDiag_SN}{ws}"["{TPDiag_transportedBytes}{WS}"]"{ENDL} {
    return Vector::ASC::Event::EventType::TpConsecutiveFrame; }
{STOL}"//"{ws}{TPDiag_CANChannel}{WS}"OTP("{TPDiag_connectionId}")"{WS}{TPDiag_type}{WS}{TPDiag_source}"->"{TPDiag_destination}":"{ws}"FC."{TPDiag_FCType}":"{ws}"BSmax:"{ws}"0x"{TPDiag_BS}","{ws}"STmin:"{ws}"0x"{TPDiag_STmin}{ws}"ms"{ENDL} {
    return Vector::ASC::Event::EventType::TpFlowControlFrame; }
{STOL}{TPDiag_timestamp}{WS}"DiagRequest"{ws}"["{TPDiag_ECUQualifier}"]"{ws}("Close"|"Open"|"TPon"|"TPoff"|{TPDiag_byteSequence}){ENDL} {
    return Vector::ASC::Event::EventType::DiagRequest; }

    /* Comment */
{STOL}"//".+?{ENDL} {
    return Vector::ASC::Event::EventType::FileComment; }

    /* undocumented events */
{STOL}{Time}{WS}("Start of measurement"|"Start der Messung"){ENDL} {
    return Vector::ASC::Event::EventType::StartOfMeasurement; }

    /* remaining characters */
{STOL}.+?{ENDL} { return Vector::ASC::Event::EventType::Unknown; }
%%

