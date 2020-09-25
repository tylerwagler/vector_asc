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

#include <Vector/ASC/platform.h>

#include <ostream>
#include <vector>

#include <Vector/ASC/CanCommon.h>
#include <Vector/ASC/File.h>
#include <Vector/ASC/MostSymbols.h>

namespace Vector {
namespace ASC {

void writeMostAckNack(const File & file, std::ostream & stream, const MostAckNack & mostAckNack);

// AllocTableSize handled in Most25AllocTable

void writeMostAt150EventModeFlags(const File & file, std::ostream & stream, const MostAt150EventModeFlags & mostAt150EventModeFlags);

void writeMostAt150Size(const File & file, std::ostream & stream, const MostAt150Size & mostAt150Size);

void writeMostCAck(const File & file, std::ostream & stream, const MostCAck & mostCAck);

void writeMostChannel(const File & file, std::ostream & stream, const MostChannel & mostChannel);

// CodingErrors handled in MostStatisticExtended

void writeMostCrc(const File & file, std::ostream & stream, const MostCrc & mostCrc);

void writeMostCrc2(const File & file, std::ostream & stream, const MostCrc2 & mostCrc2);

void writeMostCrc4(const File & file, std::ostream & stream, const MostCrc4 & mostCrc4);

void writeMostDestAdr(const File & file, std::ostream & stream, const MostDestAdr & mostDestAdr);

void writeMostDestMacAdr(const File & file, std::ostream & stream, const MostDestMacAdr & mostDestMacAdr);

void writeMostData(const File & file, std::ostream & stream, const std::vector<MostDx> & mostData);

void writeMostDir(const File & file, std::ostream & stream, const MostDir mostDir);

// DlAsync handled in MostDataLost

// DlCtrl handled in MostDataLost

// DlInfo handled in MostDataLost

// DlTime handled in MostDataLost

// EclMode handled in MostEcl

// EclState handled in MostEcl

void writeMostFirstDataLen(const File & file, std::ostream & stream, const MostFirstDataLen & mostFirstDataLen);

// FrameCounter handled in MostStatisticExtended

void writeMostFreeBytes(const File & file, std::ostream & stream, const MostFreeBytes & mostFreeBytes);

void writeMostFrgDataLen(const File & file, std::ostream & stream, const MostFrgDataLen & mostFrgDataLen);

void writeMostFrgDataLenAnnounced(const File & file, std::ostream & stream, const MostFrgDataLenAnnounced & mostFrgDataLenAnnounced);

void writeMostFrgMask(const File & file, std::ostream & stream, const MostFrgMask & mostFrgMask);

// HwMode handled in MostHwMode

// HwModeMask handled in MostHwMode

// LlState handled in MostLightLock

void writeMostMsg150Len(const File & file, std::ostream & stream, const MostMsg150Len & mostMsg150Len);

void writeMostMsg50Len(const File & file, std::ostream & stream, const MostMsg50Len & mostMsg50Len);

// NetStateNew handled in MostNetState

// NetStateOld handled in MostNetState

void writeMostPAck(const File & file, std::ostream & stream, const MostPAck & mostPAck);

void writeMostPIndex(const File & file, std::ostream & stream, const MostPIndex & mostPIndex);

void writeMostPkt150Len(const File & file, std::ostream & stream, const MostPkt150Len & mostPkt150Len);

// PktArbitr handled in Most25Packet

void writeMostPktEthLen(const File & file, std::ostream & stream, const MostPktEthLen & mostPktEthLen);

void writeMostPktLen(const File & file, std::ostream & stream, const MostPktLen & mostPktLen);

// PktPrio handled in Most25Packet

// PktState handled in Most25Packet

void writeMostPriority(const File & file, std::ostream & stream, const MostPriority & mostPriority);

// RegChip handled in MostCommonRegister

// RegDataLen handled in MostCommonRegister

// RegId handled in MostSpecialRegister

// RegOffset handled in MostCommonRegister

// RegSubType handled in MostSpecialRegister

// RegValue handled in MostSpecialRegister

void writeMostRsvdUc(const File & file, std::ostream & stream, const MostRsvdUc & mostRsvdUc);

void writeMostRsvdUl(const File & file, std::ostream & stream, const MostRsvdUl & mostRsvdUl);

void writeMostRType(const File & file, std::ostream & stream, const MostRType & mostRType);

void writeMostSourceAdr(const File & file, std::ostream & stream, const MostSourceAdr & mostSourceAdr);

void writeMostSourceMacAdr(const File & file, std::ostream & stream, const MostSourceMacAdr & mostSourceMacAdr);

void writeMostState(const File & file, std::ostream & stream, const MostState & mostState);

void writeMostState2(const File & file, std::ostream & stream, const MostState2 & mostState2);

// StatVal handled in MostStatistic

// StressMode handled in MostStress

// StressState handled in MostStress

// SysID handled in MostSystem

// SysValue handled in MostSystem

// SysValueOld handled in MostSystem

void writeMostTime(const File & file, std::ostream & stream, const MostTime & mostTime);

void writeMostTransferType(const File & file, std::ostream & stream, const MostTransferType & mostTransferType);

// TrigHw handled in MostTrigger

// TrigMode handled in MostTrigger

// TrigValue handled in MostTrigger

// TxLightState handled in MostTxLight

void writeMostWordData(const File & file, std::ostream & stream, const std::vector<MostWx> & mostWordData);

}
}
