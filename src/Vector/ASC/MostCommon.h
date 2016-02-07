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

#include "platform.h"

#include <vector>

#include "CanCommon.h"
#include "File.h"
#include "MostSymbols.h"

namespace Vector {
namespace ASC {

void writeMostAckNack(File & file, std::ostream & stream, MostAckNack & mostAckNack);

// AllocTableSize handled in Most25AllocTable

void writeMostAt150EventModeFlags(File & file, std::ostream & stream, MostAt150EventModeFlags & mostAt150EventModeFlags);

void writeMostAt150Size(File & file, std::ostream & stream, MostAt150Size & mostAt150Size);

void writeMostCAck(File & file, std::ostream & stream, MostCAck & mostCAck);

void writeMostChannel(File & file, std::ostream & stream, MostChannel & mostChannel);

// CodingErrors handled in MostStatisticExtended

void writeMostCrc(File & file, std::ostream & stream, MostCrc & mostCrc);

void writeMostCrc2(File & file, std::ostream & stream, MostCrc2 & mostCrc2);

void writeMostCrc4(File & file, std::ostream & stream, MostCrc4 & mostCrc4);

void writeMostDestAdr(File & file, std::ostream & stream, MostDestAdr & mostDestAdr);

void writeMostDestMacAdr(File & file, std::ostream & stream, MostDestMacAdr & mostDestMacAdr);

void writeMostData(File & file, std::ostream & stream, std::vector<MostDx> & mostData);

void writeMostDir(File & file, std::ostream & stream, MostDir mostDir);

// DlAsync handled in MostDataLost

// DlCtrl handled in MostDataLost

// DlInfo handled in MostDataLost

// DlTime handled in MostDataLost

// EclMode handled in MostEcl

// EclState handled in MostEcl

void writeMostFirstDataLen(File & file, std::ostream & stream, MostFirstDataLen & mostFirstDataLen);

// FrameCounter handled in MostStatisticExtended

void writeMostFreeBytes(File & file, std::ostream & stream, MostFreeBytes & mostFreeBytes);

void writeMostFrgDataLen(File & file, std::ostream & stream, MostFrgDataLen & mostFrgDataLen);

void writeMostFrgDataLenAnnounced(File & file, std::ostream & stream, MostFrgDataLenAnnounced & mostFrgDataLenAnnounced);

void writeMostFrgMask(File & file, std::ostream & stream, MostFrgMask & mostFrgMask);

// HwMode handled in MostHwMode

// HwModeMask handled in MostHwMode

// LlState handled in MostLightLock

void writeMostMsg150Len(File & file, std::ostream & stream, MostMsg150Len & mostMsg150Len);

void writeMostMsg50Len(File & file, std::ostream & stream, MostMsg50Len & mostMsg50Len);

// NetStateNew handled in MostNetState

// NetStateOld handled in MostNetState

void writeMostPAck(File & file, std::ostream & stream, MostPAck & mostPAck);

void writeMostPIndex(File & file, std::ostream & stream, MostPIndex & mostPIndex);

void writeMostPkt150Len(File & file, std::ostream & stream, MostPkt150Len & mostPkt150Len);

// PktArbitr handled in Most25Packet

void writeMostPktEthLen(File & file, std::ostream & stream, MostPktEthLen & mostPktEthLen);

void writeMostPktLen(File & file, std::ostream & stream, MostPktLen & mostPktLen);

// PktPrio handled in Most25Packet

// PktState handled in Most25Packet

void writeMostPriority(File & file, std::ostream & stream, MostPriority & mostPriority);

// RegChip handled in MostCommonRegister

// RegDataLen handled in MostCommonRegister

// RegId handled in MostSpecialRegister

// RegOffset handled in MostCommonRegister

// RegSubType handled in MostSpecialRegister

// RegValue handled in MostSpecialRegister

void writeMostRsvdUc(File & file, std::ostream & stream, MostRsvdUc & mostRsvdUc);

void writeMostRsvdUl(File & file, std::ostream & stream, MostRsvdUl & mostRsvdUl);

void writeMostRType(File & file, std::ostream & stream, MostRType & mostRType);

void writeMostSourceAdr(File & file, std::ostream & stream, MostSourceAdr & mostSourceAdr);

void writeMostSourceMacAdr(File & file, std::ostream & stream, MostSourceMacAdr & mostSourceMacAdr);

void writeMostState(File & file, std::ostream & stream, MostState & mostState);

void writeMostState2(File & file, std::ostream & stream, MostState2 & mostState2);

// StatVal handled in MostStatistic

// StressMode handled in MostStress

// StressState handled in MostStress

// SysID handled in MostSystem

// SysValue handled in MostSystem

// SysValueOld handled in MostSystem

void writeMostTime(File & file, std::ostream & stream, MostTime & mostTime);

void writeMostTransferType(File & file, std::ostream & stream, MostTransferType & mostTransferType);

// TrigHw handled in MostTrigger

// TrigMode handled in MostTrigger

// TrigValue handled in MostTrigger

// TxLightState handled in MostTxLight

void writeMostWordData(File & file, std::ostream & stream, std::vector<MostWx> & mostWordData);

}
}
