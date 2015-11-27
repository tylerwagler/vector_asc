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

#include <regex>
#include "LinCommon.h"
#include "LinDisturbanceEvent.h"
#include "LinSymbolsRegEx.h"

namespace Vector {
namespace ASC {

LinDisturbanceEvent::LinDisturbanceEvent() :
    Event(),
    time(0.0),
    channel(0),
    disturbanceType(),
    byteIndex(0),
    bitIndex(0),
    bitOffset(0),
    length(0),
    header(0),
    disturbingHeader(0)
{
    eventType = EventType::LinDisturbanceEvent;
}

LinDisturbanceEvent::~LinDisturbanceEvent()
{
}

LinDisturbanceEvent * LinDisturbanceEvent::parse(File & file, std::string & line)
{
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
        LinDisturbanceEvent * linDisturbanceEvent = new LinDisturbanceEvent;
        linDisturbanceEvent->time = std::stod(match[1]);
        linDisturbanceEvent->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        if (match[3] == "dominant")
            linDisturbanceEvent->disturbanceType = LinDisturbanceType::Dominant;
        else
        if (match[3] == "recessive")
            linDisturbanceEvent->disturbanceType = LinDisturbanceType::Recessive;
        else
        if (match[3] == "header")
            linDisturbanceEvent->disturbanceType = LinDisturbanceType::Header;
        else
        if (match[3] == "bitstream")
            linDisturbanceEvent->disturbanceType = LinDisturbanceType::Bitstream;
        else
        if (match[3] == "variableBitstream")
            linDisturbanceEvent->disturbanceType = LinDisturbanceType::VariableBitstream;
        linDisturbanceEvent->byteIndex = std::stoul(match[4]);
        linDisturbanceEvent->bitIndex = std::stoul(match[5]);
        linDisturbanceEvent->bitOffset = std::stoul(match[6]);
        linDisturbanceEvent->length = std::stoul(match[7]);
        linDisturbanceEvent->header = std::stoul(match[8], nullptr, 16);
        linDisturbanceEvent->disturbingHeader = std::stoul(match[9], nullptr, 16);
        return linDisturbanceEvent;
    }

    return nullptr;
}

void LinDisturbanceEvent::write(File & file, std::ostream & stream)
{
    writeLinTime(file, stream, time);
    stream << ' ';

    /* format: "%s DisturbanceEvent Type = %s ByteIndex = %d BitIndex = %d BitOffset = %d Length = %d " */
    writeLinChannel(file, stream, channel);
    stream
            << " DisturbanceEvent"
            << " Type = " /* << disturbanceType */
            << " ByteIndex = " << std::dec << (int16_t) byteIndex
            << " BitIndex = " << std::dec << (int16_t) bitIndex
            << " BitOffset = " << std::dec << (int16_t) bitOffset
            << " Length = " << std::dec << (int16_t) length
            << ' ';

    /* format: "Header = %02X Disturbing header = %02X" */
    stream
            << "Header = " /* << %02X */
            << " Disturbing header = "; /* << %02X */

    /* format: "Header = %3d Disturbing header = %3d" */
    stream
            << "Header = " /* << %3d */
            << " Disturbing header = "; /* << %3d */

    stream << endl;
}

}
}
