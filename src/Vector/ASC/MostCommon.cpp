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

#include <iomanip>
#include "MostCommon.h"

namespace Vector {
namespace ASC {

void writeMostAckNack(File & file, std::ostream & stream, MostAckNack & mostAckNack)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostAckNack << ' ';
}

void writeMostAt150EventModeFlags(File & file, std::ostream & stream, MostAt150EventModeFlags & mostAt150EventModeFlags)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostAt150EventModeFlags << ' ';
}

void writeMostAt150Size(File & file, std::ostream & stream, MostAt150Size & mostAt150Size)
{
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostAt150Size << ' ';
}

void writeMostCAck(File & file, std::ostream & stream, MostCAck & mostCAck)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostCAck << ' ';
}

void writeMostChannel(File & file, std::ostream & stream, MostChannel & mostChannel)
{
    /* format: "M%u " */
    stream << 'M' << std::dec << (uint16_t) mostChannel << ' ';
}

void writeMostCrc(File & file, std::ostream & stream, MostCrc & mostCrc)
{
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostCrc << ' ';
}

void writeMostCrc2(File & file, std::ostream & stream, MostCrc2 & mostCrc2)
{
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostCrc2 << ' ';
}

void writeMostCrc4(File & file, std::ostream & stream, MostCrc4 & mostCrc4)
{
    /* format: "%08X " */
    stream << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << mostCrc4 << ' ';
}

void writeMostDestAdr(File & file, std::ostream & stream, MostDestAdr & mostDestAdr)
{
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostDestAdr << ' ';
}

void writeMostDestMacAdr(File & file, std::ostream & stream, MostDestMacAdr & mostDestMacAdr)
{
    /* format: "%012X " */
    stream << std::setfill('0') << std::setw(12) << std::uppercase << std::hex << mostDestMacAdr << ' ';
}

void writeMostData(File & file, std::ostream & stream, std::vector<MostDx> & mostData)
{
    for(MostDx d: mostData)
        stream << std::right
               << std::setfill('0') << std::setw(2)
               << std::uppercase << std::hex << (uint16_t) d
               << ' ';
}

void writeMostDir(File & file, std::ostream & stream, MostDir mostDir)
{
    switch(mostDir) {
    case Dir::Rx:
        /* format: "Rx   " */
        stream << "Rx   ";
        break;
    case Dir::Tx:
        /* format: "Tx   " */
        stream << "Tx   ";
        break;
    case Dir::TxRq:
        /* format: "TxRq " */
        stream << "TxRq ";
        break;
    }
}

void writeMostFirstDataLen(File & file, std::ostream & stream, MostFirstDataLen & mostFirstDataLen)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostFirstDataLen << ' ';
}

void writeMostFreeBytes(File & file, std::ostream & stream, MostFreeBytes & mostFreeBytes)
{
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostFreeBytes << ' ';
}

void writeMostFrgDataLen(File & file, std::ostream & stream, MostFrgDataLen & mostFrgDataLen)
{
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostFrgDataLen << ' ';
}

void writeMostFrgDataLenAnnounced(File & file, std::ostream & stream, MostFrgDataLenAnnounced & mostFrgDataLenAnnounced)
{
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostFrgDataLenAnnounced << ' ';
}

void writeMostFrgMask(File & file, std::ostream & stream, MostFrgMask & mostFrgMask)
{
    /* format: "%08X " */
    stream << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << mostFrgMask << ' ';
}

void writeMostMsg150Len(File & file, std::ostream & stream, MostMsg150Len & mostMsg150Len)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostMsg150Len << ' ';
}

void writeMostMsg50Len(File & file, std::ostream & stream, MostMsg50Len & mostMsg50Len)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostMsg50Len << ' ';
}

void writeMostPAck(File & file, std::ostream & stream, MostPAck & mostPAck)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostPAck << ' ';
}

void writeMostPIndex(File & file, std::ostream & stream, MostPIndex & mostPIndex)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostPIndex << ' ';
}

void writeMostPkt150Len(File & file, std::ostream & stream, MostPkt150Len & mostPkt150Len)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostPkt150Len << ' ';
}

void writeMostPktEthLen(File & file, std::ostream & stream, MostPktEthLen & mostPktEthLen)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostPktEthLen << ' ';
}

void writeMostPktLen(File & file, std::ostream & stream, MostPktLen & mostPktLen)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostPktLen << ' ';
}

void writeMostPriority(File & file, std::ostream & stream, MostPriority & mostPriority)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostPriority << ' ';
}

void writeMostRsvdUc(File & file, std::ostream & stream, MostRsvdUc & mostRsvdUc)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostRsvdUc << ' ';
}

void writeMostRsvdUl(File & file, std::ostream & stream, MostRsvdUl & mostRvdUl)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << mostRvdUl << ' ';
}

void writeMostRType(File & file, std::ostream & stream, MostRType & mostRType)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostRType << ' ';
}

void writeMostSourceAdr(File & file, std::ostream & stream, MostSourceAdr & mostSourceAdr)
{
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostSourceAdr << ' ';
}

void writeMostSourceMacAdr(File & file, std::ostream & stream, MostSourceMacAdr & mostSourceMacAdr)
{
    /* format: "%012X " */
    stream << std::setfill('0') << std::setw(12) << std::uppercase << std::hex << mostSourceMacAdr << ' ';
}

void writeMostState(File & file, std::ostream & stream, MostState & mostState)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostState << ' ';
}

void writeMostState2(File & file, std::ostream & stream, MostState2 & mostState2)
{
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << (uint16_t) mostState2 << ' ';
}

void writeMostTime(File & file, std::ostream & stream, MostTime & mostTime)
{
    stream
            << std::right << std::setfill(' ')
            << std::setw(11) << std::setprecision(6)
            << std::fixed << mostTime
            << ' ';
}

void writeMostTransferType(File & file, std::ostream & stream, MostTransferType & mostTransferType)
{
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostTransferType << ' ';
}

void writeMostWordData(File & file, std::ostream & stream, std::vector<MostWx> & mostWordData)
{
    for(MostWx w: mostWordData)
        stream << std::right
               << std::setfill('0') << std::setw(4)
               << std::uppercase << std::hex << w
               << ' ';
}

}
}
