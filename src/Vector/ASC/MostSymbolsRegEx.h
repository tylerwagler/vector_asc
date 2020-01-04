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

/** MOST Symbols */

#pragma once

#include <Vector/ASC/platform.h>

#include <Vector/ASC/CanSymbolsRegEx.h>

namespace Vector {
namespace ASC {

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

}
}
