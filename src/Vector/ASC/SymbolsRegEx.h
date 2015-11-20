/*
 * Copyright (C) 2014-2015 Tobias Lorenz.
 * Contact: tobias.lorenz@gmx.net
 *
 * This file is part of Tobias Lorenz's Toolkit.
 *
 * Commercial License Usage
 * Licensees holding valid commercial licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and Tobias Lorenz.
 *
 * GNU General Public License 3.0 Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 */

#pragma once

namespace Vector {
namespace ASC {

    // Format Symbols
#define REGEX_STOL "^[[:blank:]]*"
#define REGEX_ENDL "\r?$"
#define REGEX_WS "[[:blank:]]+"
#define REGEX_ws "[[:blank:]]*"

    // CAN, Log & Trigger Symbols
#define REGEX_Time "([[:digit:].]{3,})"
#define REGEX_Channel "([[:digit:]]{1,5})"
#define REGEX_IDnum "([[:xdigit:]]{1,14})"
    // IDsym @todo
#define REGEX_ID REGEX_IDnum
#define REGEX_Dir "(Rx|Tx|TxRq)"
#define REGEX_DLC "([[:xdigit:]]{1,2})"
#define REGEX_MessageFlags "(TE|WU|XX)"
#define REGEX_StatNumber "([[:digit:]]{1,10})"
#define REGEX_StatPercent "([[:digit:].]{3,6})"
#define REGEX_PreTrigger "([[:digit:]]{1,10})"
#define REGEX_PostTrigger "([[:digit:]]{1,10})"
#define REGEX_Error "(.+?)"
#define REGEX_Dx "[[:xdigit:]]{1,3}"
#define REGEX_WeekDay "(Mon|Tue|Wed|Thu|Fri|Sat|Sun|Mon|Die|Mit|Don|Fre|Sam|Son)"
#define REGEX_Month "(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec|Jan|Feb|Mär|Apr|Mai|Jun|Jul|Aug|Sep|Okt|Nov|Dez)"
#define REGEX_Date "([[:digit:]]{1,2})"
#define REGEX_FullTime "([[:digit:]]{2}):([[:digit:]]{2}):([[:digit:]]{2})( am| pm)?"
#define REGEX_Year "([[:digit:]]{4})"
#define REGEX_svtype "([12345])"
#define REGEX_MessageDuration "([[:digit:]]+)"
#define REGEX_MessageLength "([[:digit:]]+)"
#define REGEX_BRS "([01])"
#define REGEX_ESI "([01])"
#define REGEX_DataLength "([[:digit:]]{1,3})"
#define REGEX_BitTimingConfArb "([[:xdigit:]]{8})"
#define REGEX_BitTimingConfData "([[:xdigit:]]{8})"

    // Ethernet Symbols
#define REGEX_Eth_Channel "([[:xdigit:]]{1,3})"
#define REGEX_Eth_Data "([[:xdigit:]]+)"
#define REGEX_Eth_DataLen "([[:xdigit:]]{1,4})"
#define REGEX_Eth_Dir "(Rx|Tx|TxRq)"
#define REGEX_Eth_Time "([[:digit:].]{3,})"
#define REGEX_Eth_ErrorCode "([[:xdigit:]]{1,2})"
#define REGEX_Eth_FrameChecksum "([[:xdigit:]]{8})"
#define REGEX_Afdx_BAG "([[:xdigit:]]+)"
#define REGEX_Afdx_Channel "([[:xdigit:]]{1,3})"
#define REGEX_Afdx_Data "([[:xdigit:]]+)"
#define REGEX_Afdx_DataLen "([[:xdigit:]]{1,4})"
#define REGEX_Afdx_Dir "(Rx|Tx|TxRq)"
#define REGEX_Afdx_EthChannel "([[:xdigit:]]{1,3})"
#define REGEX_Afdx_Flags "([[:xdigit:]]{1,5})"
#define REGEX_Afdx_Time "([[:digit:].]{3,})"

    // FlexRay Symbols
#define REGEX_FlexRayOld_Time "([[:digit:].]{3,})"
#define REGEX_FlexRayOld_Channel "Fr ([12*])"
    // REGEX_FlexRay_Typ (V9|StartCycleEvent|ErrorFrame)
#define REGEX_FlexRayOld_ID "([[:xdigit:]]{1,4})"
#define REGEX_FlexRayOld_Cycle "([[:digit:]]{1,2})"
#define REGEX_FlexRayOld_NM "([01])"
#define REGEX_FlexRayOld_Sync "([01])"
#define REGEX_FlexRayOld_HeaderCRC "([[:xdigit:]]{1,4})"
#define REGEX_FlexRayOld_SymbolicName "([[:alnum:]_]+)"
#define REGEX_FlexRayOld_DLC "([[:xdigit:]]{1,3})"
#define REGEX_FlexRayOld_Dx "[[:xdigit:]]{1,3}"
#define REGEX_FlexRayOld_FrameState "([[:xdigit:]]{1,5})"
#define REGEX_FlexRayOld_HeaderBitMask "([[:xdigit:]]{1,3})"
#define REGEX_FlexRay_Time "([[:digit:].]{3,})"
#define REGEX_FlexRay_Dir "(Rx|Tx|TxRq)"

    // K-Line Symbols
#define REGEX_KLine_time "([[:digit:].]{3,})"
#define REGEX_KLine_port "((COM|KL)[[:digit:]]{1,3})"
#define REGEX_KLine_direction "(Tx|Rx)"
#define REGEX_KLine_baudrate "([[:digit:]]{1,6})"
#define REGEX_KLine_source "([[:alnum:]]+)"
#define REGEX_KLine_destination "([[:alnum:]]+)"
#define REGEX_KLine_length "([[:digit:]]{1,4})"
#define REGEX_KLine_data "[[:xdigit:]]{1,3}"

    // LIN Symbols
#define REGEX_LIN_baudrate "([[:digit:]]{1,5})"
#define REGEX_LIN_Channel "L([[:xdigit:]i*]{1,4})"
#define REGEX_LIN_checksum "([[:xdigit:]]{1,3})"
#define REGEX_LIN_checksumModel "(unknown|classic|enhanced|error)"
#define REGEX_LIN_checksumModelInfo "Using (enhanced|classic) checksum"
#define REGEX_LIN_Dir "(Rx|Tx|TxRq)"
#define REGEX_LIN_DLC "([-[:digit:]]{1,2})"
#define REGEX_LIN_NumberOfResponseBytes "([[:digit:]])"
#define REGEX_LIN_Dx "[[:xdigit:]]{1,3}"
#define REGEX_LIN_description "(.+?)"
#define REGEX_LIN_DomSigState "(detected|continuing|finished)"
#define REGEX_LIN_DomSigLength "([[:digit:]]{1,8})"
#define REGEX_LIN_endOfFrame "([[:digit:].]{3,})"
#define REGEX_LIN_ETFName "([[:alnum:]_]+)"
#define REGEX_LIN_endOfHeader "([[:digit:].]{3,})"
#define REGEX_LIN_FullTime "([[:digit:]]+)"
#define REGEX_LIN_fullTime REGEX_LIN_FullTime
#define REGEX_LIN_HasDatabytes "([01])"
#define REGEX_LIN_HeaderTime "([[:digit:]]+)"
#define REGEX_LIN_headerTime REGEX_LIN_HeaderTime
#define REGEX_LIN_headerBaudrate "([[:digit:].]{3,12})"
#define REGEX_LIN_ID "([[:alnum:]_]+)"
#define REGEX_LIN_IsDLCTimeout "([01])"
#define REGEX_LIN_IsShortError "([01])"
#define REGEX_LIN_MessageId "([[:xdigit:]]{1,5})"
#define REGEX_LIN_NAD "([[:xdigit:]]{1,3})"
#define REGEX_LIN_offendingByte "([[:xdigit:]]{1,3})"
#define REGEX_LIN_responseBaudrate "([[:digit:]]{1,5})"
#define REGEX_LIN_simulated "([01])"
#define REGEX_LIN_scheduleTableIndex "([[:digit:]]+)"
#define REGEX_LIN_slaveId "([[:digit:]]{1,2})"
#define REGEX_LIN_SpikeLength "([[:digit:]]{1,6})"
#define REGEX_LIN_startOfFrame "([[:digit:].]{3,})"
#define REGEX_LIN_state "([[:digit:]]{1,3})"
#define REGEX_LIN_StateReason "([[:xdigit:]]{1,3})"
#define REGEX_LIN_stopBitOffsetInHeader "([[:digit:]]{1,8})"
#define REGEX_LIN_stopBitOffsetInResponse "([[:digit:]]{1,8})"
#define REGEX_LIN_SupplierId "([[:xdigit:]]{1,5})"
#define REGEX_LIN_SyncBreak "([[:digit:]]{1,6})"
#define REGEX_LIN_SyncDel "([[:digit:]]{1,6})"
#define REGEX_LIN_syncBreakTime "([[:digit:]]+)" REGEX_ws "us" REGEX_ws "\\(([[:digit:].]+)" REGEX_ws "bits\\)"
#define REGEX_LIN_syncDelimiterTime "([[:digit:]]+)" REGEX_ws "us" REGEX_ws "\\(([[:digit:].]+)" REGEX_ws "bits\\)"
#define REGEX_LIN_T "[[:digit:].]{3,}"
#define REGEX_LIN_Time "([[:digit:].]{3,})"
#define REGEX_LIN_TimeInterval "[[:digit:]]{1,5}"
#define REGEX_LIN_WakeupByte "([[:xdigit:]]{1,3})"
#define REGEX_LIN_WakeupLengthInfo "([012])"
#define REGEX_LIN_IsSlowResponse "([[:digit:]])"
#define REGEX_LIN_ResponseWasInterruptedByBreak "([[:digit:]])"
#define REGEX_LIN_Width "([[:digit:]]{3,4})"
#define REGEX_LIN_DisturbanceType "(dominant|recessive|header|bitstream|variableBitstream)"
#define REGEX_LIN_ByteIndex "([[:digit:]])"
#define REGEX_LIN_BitIndex "([[:digit:]]{1,3})"
#define REGEX_LIN_BitOffsetInSixteenthBits "([[:digit:]]{1,2})"
#define REGEX_LIN_DisturbanceLengthInSixteenthBits "([[:digit:]]{1,2})"
#define REGEX_LIN_IDorFF "([[:xdigit:]]{1,3})"

    // MOST Symbols
#define REGEX_MOST_AckNack "([[:xdigit:]]{2,3})"
#define REGEX_MOST_AllocTableSize "([[:xdigit:]]{4})"
#define REGEX_MOST_AT150EventModeFlags "([[:xdigit:]]{2})"
#define REGEX_MOST_AT150Size "([[:xdigit:]]{4})"
#define REGEX_MOST_CAck "([[:xdigit:]]{2})"
#define REGEX_MOST_Cack REGEX_MOST_CAck
#define REGEX_MOST_Channel "M([[:xdigit:]]{1,2})"
#define REGEX_MOST_CodingErrors "([[:xdigit:]]{6})"
#define REGEX_MOST_CRC "([[:xdigit:]]{1,5})"
#define REGEX_MOST_CRC2 "([[:xdigit:]]{4})"
#define REGEX_MOST_CRC4 "([[:xdigit:]]{8})"
#define REGEX_MOST_DxAT "[[:xdigit:]]{2}"
#define REGEX_MOST_DestAdr "([[:xdigit:]]{1,5})"
#define REGEX_MOST_DestMacAdr "([[:xdigit:]]{12})"
#define REGEX_MOST_Dir "(Rx|Tx|TxRq)"
#define REGEX_MOST_DLAsync "([[:xdigit:]]{1,4})"
#define REGEX_MOST_DLCtrl "([[:xdigit:]]{1,4})"
#define REGEX_MOST_DLInfo "([[:xdigit:]]{8})"
#define REGEX_MOST_DLTime "([[:digit:].]{3,})"
#define REGEX_MOST_Dx "[[:xdigit:]]{1,3}"
#define REGEX_MOST_EclMode "([01])"
#define REGEX_MOST_EclState "([01])"
#define REGEX_MOST_FirstDataLen "([[:xdigit:]]{1,4})"
#define REGEX_MOST_FrameCounter "([[:xdigit:]]{6})"
#define REGEX_MOST_FreeBytes "([[:xdigit:]]{4})"
#define REGEX_MOST_FrgDataLen "([[:xdigit:]]{4,8})"
#define REGEX_MOST_FrgDataLenAnnounced "([[:xdigit:]]{4,8})"
#define REGEX_MOST_FrgMask "([[:xdigit:]]{8})"
#define REGEX_MOST_HWMode "([[:xdigit:]]{2})"
#define REGEX_MOST_HWModeMask "([[:xdigit:]]{2})"
#define REGEX_MOST_LLState "([[:xdigit:]]{1,2})"
#define REGEX_MOST_Msg150Len "([[:xdigit:]]{1,3})"
#define REGEX_MOST_Msg50Len "([[:xdigit:]]{1,3})"
#define REGEX_MOST_NetStateNew "([[:xdigit:]])"
#define REGEX_MOST_NetStateOld "([[:xdigit:]])"
#define REGEX_MOST_PAck "([[:xdigit:]]{2})"
#define REGEX_MOST_Pack REGEX_MOST_PAck
#define REGEX_MOST_Pindex "([[:xdigit:]]{2})"
#define REGEX_MOST_Pkt150Len "([[:xdigit:]]{1,4})"
#define REGEX_MOST_PktArbitr "([[:xdigit:]]{2})"
#define REGEX_MOST_PktEthLen "([[:xdigit:]]{1,4})"
#define REGEX_MOST_PktLen "([[:xdigit:]]{1,4})"
#define REGEX_MOST_PktPrio "([[:xdigit:]])"
#define REGEX_MOST_PktState "([[:xdigit:]]{2})"
#define REGEX_MOST_Priority "([[:xdigit:]]{2})"
#define REGEX_MOST_RegChip "([[:xdigit:]]{2})"
#define REGEX_MOST_RegDataLen "([[:xdigit:]]{2})"
#define REGEX_MOST_RegID "([[:xdigit:]]{2})"
#define REGEX_MOST_RegOffset "([[:xdigit:]]{4})"
#define REGEX_MOST_RegSubType "([[:xdigit:]])"
#define REGEX_MOST_RegValue "([[:xdigit:]]{4})"
#define REGEX_MOST_RsvdUC "([[:xdigit:]]{2})"
#define REGEX_MOST_RsvdUL "([[:xdigit:]]{2})"
#define REGEX_MOST_Rtype "([[:xdigit:]]{1,3})"
#define REGEX_MOST_RType REGEX_MOST_Rtype
#define REGEX_MOST_SourceAdr "([[:xdigit:]]{1,5})"
#define REGEX_MOST_SourceMacAdr "([[:xdigit:]]{12})"
#define REGEX_MOST_State "([[:xdigit:]]{1,3})"
#define REGEX_MOST_State2 "([[:xdigit:]]{1,5})"
#define REGEX_MOST_StatVal "([[:digit:]]{1,5})"
#define REGEX_MOST_StressMode "([[:xdigit:]])"
#define REGEX_MOST_StressState "([01])"
#define REGEX_MOST_SysID "([[:xdigit:]]{2})"
#define REGEX_MOST_SysValue "([[:xdigit:]]{4})"
#define REGEX_MOST_SysValueOld "([[:xdigit:]]{4})"
#define REGEX_MOST_Time "([[:digit:].]{3,})"
#define REGEX_MOST_TransferType "([[:xdigit:]]{2})"
#define REGEX_MOST_TrigHW "([[:xdigit:]])"
#define REGEX_MOST_TrigMode "([012])"
#define REGEX_MOST_TrigValue "([[:xdigit:]]{8})"
#define REGEX_MOST_TxLightState "([012])"
#define REGEX_MOST_Wx "([[:xdigit:]]{4})"

    // TP/Diagnostics Symbols
#define REGEX_TPDiag_CANChannel "([[:digit:]]{1,2})"
#define REGEX_TPDiag_connectionId "([[:xdigit:]]{2})"
#define REGEX_TPDiag_type "(Info|Warn|Error|Atom|Data)"
#define REGEX_TPDiag_source "([[:alnum:]_<>]+)"
#define REGEX_TPDiag_destination "([[:alnum:]_<>]+)"
#define REGEX_TPDiag_length "([[:xdigit:]]{2,4})"
#define REGEX_TPDiag_transportedBytes "((" REGEX_WS "[[:xdigit:]]+)*)"
#define REGEX_TPDiag_SN "([[:xdigit:]]{1,4})"
#define REGEX_TPDiag_FCType "(CTS|WT|OVFLW)"
#define REGEX_TPDiag_BS "([[:xdigit:]]{1,4})"
#define REGEX_TPDiag_STmin "([[:xdigit:]]{1,4})"
#define REGEX_TPDiag_timestamp "([[:digit:].]{3,})"
#define REGEX_TPDiag_ECUQualifier "([[:alnum:]_]+)"
#define REGEX_TPDiag_byteSequence "((" REGEX_WS "[[:xdigit:]]+)*)"

}
}
