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
#include <regex>

#include <Vector/ASC/LinCommon.h>
#include <Vector/ASC/LinDisturbance.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinDisturbance * LinDisturbance::read(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS "DisturbanceEvent"
                     REGEX_WS "Type" REGEX_ws "=" REGEX_ws REGEX_LIN_DisturbanceType
                     REGEX_WS "ByteIndex" REGEX_ws "=" REGEX_ws REGEX_LIN_ByteIndex
                     REGEX_WS "BitIndex" REGEX_ws "=" REGEX_ws REGEX_LIN_BitIndex
                     REGEX_WS "BitOffset" REGEX_ws "=" REGEX_ws REGEX_LIN_BitOffsetInSixteenthBits
                     REGEX_WS "Length" REGEX_ws "=" REGEX_ws REGEX_LIN_DisturbanceLengthInSixteenthBits
                     REGEX_WS "Header" REGEX_ws "=" REGEX_ws REGEX_LIN_IDorFF
                     REGEX_WS "Disturbing header" REGEX_ws "=" REGEX_ws REGEX_LIN_IDorFF REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linDisturbance = new LinDisturbance;
        linDisturbance->time = std::stod(match[1]);
        linDisturbance->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        if (match[3] == "dominant")
            linDisturbance->disturbanceType = LinDisturbanceType::Dominant;
        else if (match[3] == "recessive")
            linDisturbance->disturbanceType = LinDisturbanceType::Recessive;
        else if (match[3] == "header")
            linDisturbance->disturbanceType = LinDisturbanceType::Header;
        else if (match[3] == "bitstream")
            linDisturbance->disturbanceType = LinDisturbanceType::Bitstream;
        else if (match[3] == "variableBitstream")
            linDisturbance->disturbanceType = LinDisturbanceType::VariableBitstream;
        linDisturbance->byteIndex = std::stoul(match[4]);
        linDisturbance->bitIndex = std::stoul(match[5]);
        linDisturbance->bitOffset = std::stoul(match[6]);
        linDisturbance->length = std::stoul(match[7]);
        linDisturbance->header = std::stoul(match[8], nullptr, file.base);
        linDisturbance->disturbingHeader = std::stoul(match[9], nullptr, file.base);
        return linDisturbance;
    }

    return nullptr;
}

void LinDisturbance::write(File & file, std::ostream & stream) {
    if (file.version < File::Version::Ver_7_5)
        return;

    writeLinTime(file, stream, time);
    stream << ' ';

    /* format: "%s DisturbanceEvent Type = %s ByteIndex = %d BitIndex = %d BitOffset = %d Length = %d " */
    writeLinChannel(file, stream, channel);
    stream
            << " DisturbanceEvent"
            << " Type = ";
    switch (disturbanceType) {
    case LinDisturbanceType::Dominant:
        stream << "dominant";
        break;
    case LinDisturbanceType::Recessive:
        stream << "recessive";
        break;
    case LinDisturbanceType::Header:
        stream << "header";
        break;
    case LinDisturbanceType::Bitstream:
        stream << "bitstream";
        break;
    case LinDisturbanceType::VariableBitstream:
        stream << "variableBitstream";
        break;
    }
    stream
            << " ByteIndex = " << std::dec << (int16_t) byteIndex
            << " BitIndex = " << std::dec << (int16_t) bitIndex
            << " BitOffset = " << std::dec << (int16_t) bitOffset
            << " Length = " << std::dec << (int16_t) length
            << ' ';

    switch (file.base) {
    case 10:
        /* format: "Header = %3d Disturbing header = %3d" */
        stream
                << "Header = "
                << std::setw(3) << std::dec << (uint16_t) header
                << " Disturbing header = "
                << std::setw(3) << std::dec << (uint16_t) disturbingHeader;
        break;

    case 16:
        /* format: "Header = %02X Disturbing header = %02X" */
        stream
                << "Header = "
                << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) header
                << " Disturbing header = "
                << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (uint16_t) disturbingHeader;
        break;
    }

    stream << endl;
}

}
}
