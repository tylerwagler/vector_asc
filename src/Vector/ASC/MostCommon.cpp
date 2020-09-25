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

#include <Vector/ASC/MostCommon.h>

namespace Vector {
namespace ASC {

void writeMostAckNack(const File & /*file*/, std::ostream & stream, const MostAckNack & mostAckNack) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostAckNack << ' ';
}

void writeMostAt150EventModeFlags(const File & /*file*/, std::ostream & stream, const MostAt150EventModeFlags & mostAt150EventModeFlags) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostAt150EventModeFlags << ' ';
}

void writeMostAt150Size(const File & /*file*/, std::ostream & stream, const MostAt150Size & mostAt150Size) {
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostAt150Size << ' ';
}

void writeMostCAck(const File & /*file*/, std::ostream & stream, const MostCAck & mostCAck) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostCAck << ' ';
}

void writeMostChannel(const File & /*file*/, std::ostream & stream, const MostChannel & mostChannel) {
    /* format: "M%u " */
    stream << 'M' << std::dec << (uint16_t) mostChannel << ' ';
}

void writeMostCrc(const File & /*file*/, std::ostream & stream, const MostCrc & mostCrc) {
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostCrc << ' ';
}

void writeMostCrc2(const File & /*file*/, std::ostream & stream, const MostCrc2 & mostCrc2) {
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostCrc2 << ' ';
}

void writeMostCrc4(const File & /*file*/, std::ostream & stream, const MostCrc4 & mostCrc4) {
    /* format: "%08X " */
    stream << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << mostCrc4 << ' ';
}

void writeMostDestAdr(const File & /*file*/, std::ostream & stream, const MostDestAdr & mostDestAdr) {
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostDestAdr << ' ';
}

void writeMostDestMacAdr(const File & /*file*/, std::ostream & stream, const MostDestMacAdr & mostDestMacAdr) {
    /* format: "%012X " */
    stream << std::setfill('0') << std::setw(12) << std::uppercase << std::hex << mostDestMacAdr << ' ';
}

void writeMostData(const File & /*file*/, std::ostream & stream, const std::vector<MostDx> & mostData) {
    for (MostDx d : mostData)
        stream << std::right
               << std::setfill('0') << std::setw(2)
               << std::uppercase << std::hex << (uint16_t) d
               << ' ';
}

void writeMostDir(const File & /*file*/, std::ostream & stream, const MostDir mostDir) {
    switch (mostDir) {
    case MostDir::Rx:
        /* format: "Rx   " */
        stream << "Rx   ";
        break;
    case MostDir::Tx:
        /* format: "Tx   " */
        stream << "Tx   ";
        break;
    case MostDir::TxRq:
        /* format: "TxRq " */
        stream << "TxRq ";
        break;
    }
}

void writeMostFirstDataLen(const File & /*file*/, std::ostream & stream, const MostFirstDataLen & mostFirstDataLen) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostFirstDataLen << ' ';
}

void writeMostFreeBytes(const File & /*file*/, std::ostream & stream, const MostFreeBytes & mostFreeBytes) {
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostFreeBytes << ' ';
}

void writeMostFrgDataLen(const File & /*file*/, std::ostream & stream, const MostFrgDataLen & mostFrgDataLen) {
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostFrgDataLen << ' ';
}

void writeMostFrgDataLenAnnounced(const File & /*file*/, std::ostream & stream, const MostFrgDataLenAnnounced & mostFrgDataLenAnnounced) {
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostFrgDataLenAnnounced << ' ';
}

void writeMostFrgMask(const File & /*file*/, std::ostream & stream, const MostFrgMask & mostFrgMask) {
    /* format: "%08X " */
    stream << std::setfill('0') << std::setw(8) << std::uppercase << std::hex << mostFrgMask << ' ';
}

void writeMostMsg150Len(const File & /*file*/, std::ostream & stream, const MostMsg150Len & mostMsg150Len) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostMsg150Len << ' ';
}

void writeMostMsg50Len(const File & /*file*/, std::ostream & stream, const MostMsg50Len & mostMsg50Len) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostMsg50Len << ' ';
}

void writeMostPAck(const File & /*file*/, std::ostream & stream, const MostPAck & mostPAck) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostPAck << ' ';
}

void writeMostPIndex(const File & /*file*/, std::ostream & stream, const MostPIndex & mostPIndex) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostPIndex << ' ';
}

void writeMostPkt150Len(const File & /*file*/, std::ostream & stream, const MostPkt150Len & mostPkt150Len) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << mostPkt150Len << ' ';
}

void writeMostPktEthLen(const File & /*file*/, std::ostream & stream, const MostPktEthLen & mostPktEthLen) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << mostPktEthLen << ' ';
}

void writeMostPktLen(const File & /*file*/, std::ostream & stream, const MostPktLen & mostPktLen) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << mostPktLen << ' ';
}

void writeMostPriority(const File & /*file*/, std::ostream & stream, const MostPriority & mostPriority) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostPriority << ' ';
}

void writeMostRsvdUc(const File & /*file*/, std::ostream & stream, const MostRsvdUc & mostRsvdUc) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostRsvdUc << ' ';
}

void writeMostRsvdUl(const File & /*file*/, std::ostream & stream, const MostRsvdUl & mostRvdUl) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << mostRvdUl << ' ';
}

void writeMostRType(const File & /*file*/, std::ostream & stream, const MostRType & mostRType) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostRType << ' ';
}

void writeMostSourceAdr(const File & /*file*/, std::ostream & stream, const MostSourceAdr & mostSourceAdr) {
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostSourceAdr << ' ';
}

void writeMostSourceMacAdr(const File & /*file*/, std::ostream & stream, const MostSourceMacAdr & mostSourceMacAdr) {
    /* format: "%012X " */
    stream << std::setfill('0') << std::setw(12) << std::uppercase << std::hex << mostSourceMacAdr << ' ';
}

void writeMostState(const File & /*file*/, std::ostream & stream, const MostState & mostState) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostState << ' ';
}

void writeMostState2(const File & /*file*/, std::ostream & stream, const MostState2 & mostState2) {
    /* format: "%04X " */
    stream << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << mostState2 << ' ';
}

void writeMostTime(const File & /*file*/, std::ostream & stream, const MostTime & mostTime) {
    stream
            << std::right << std::setfill(' ')
            << std::setw(11) << std::setprecision(6)
            << std::fixed << mostTime
            << ' ';
}

void writeMostTransferType(const File & /*file*/, std::ostream & stream, const MostTransferType & mostTransferType) {
    /* format: "%02X " */
    stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) mostTransferType << ' ';
}

void writeMostWordData(const File & /*file*/, std::ostream & stream, const std::vector<MostWx> & mostWordData) {
    for (MostWx w : mostWordData)
        stream << std::right
               << std::setfill('0') << std::setw(4)
               << std::uppercase << std::hex << w
               << ' ';
}

}
}
