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
#include "CanCommon.h"
#include "CanFdErrorFrame.h"
#include "CanSymbolsRegEx.h"

namespace Vector {
namespace ASC {

CanFdErrorFrame::CanFdErrorFrame() :
    Event(),
    time(0.0),
    channel(0),
    dir(Dir::Rx),
    errorText(),
    flags1(0),
    code(0),
    codeExt(0),
    phase(Phase::Data),
    position(0),
    id(0),
    brs(false),
    esi(false),
    dlc(0),
    dataLength(0),
    data(),
    messageDuration(0),
    flags2(0),
    crc(0),
    bitTimingConfArb(0),
    bitTimingConfData(0)
{
    eventType = EventType::CanFdErrorFrame;
}

CanFdErrorFrame::~CanFdErrorFrame()
{
}

CanFdErrorFrame * CanFdErrorFrame::parse(File & file, std::string & line)
{
    std::regex regex(REGEX_STOL REGEX_Time REGEX_WS "CANFD" REGEX_WS REGEX_Channel REGEX_WS REGEX_Dir REGEX_WS "ErrorFrame"
                     REGEX_WS "(Not Acknowledge error, dominant error flag)"
                     REGEX_WS "([[:xdigit:]]{4})" REGEX_WS "([[:xdigit:]]{2})" REGEX_WS "([[:xdigit:]]{4})"
                     REGEX_WS "(Data)"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS REGEX_ID REGEX_WS REGEX_BRS REGEX_WS REGEX_ESI REGEX_WS REGEX_DLC
                     REGEX_WS REGEX_DataLength "((" REGEX_WS REGEX_Dx "){0,64})"
                     REGEX_WS REGEX_MessageDuration REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS REGEX_BitTimingConfArb REGEX_WS REGEX_BitTimingConfData REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        CanFdErrorFrame * canFdErrorFrame = new CanFdErrorFrame;
        canFdErrorFrame->time = std::stod(match[1]);
        canFdErrorFrame->channel = std::stoul(match[2]);
        if (match[3] == "Rx")
                canFdErrorFrame->dir = Dir::Rx;
        else
        if (match[3] == "Tx")
                canFdErrorFrame->dir = Dir::Tx;
        canFdErrorFrame->errorText = match[4];
        canFdErrorFrame->flags1 = std::stoul(match[5], nullptr, 16);
        canFdErrorFrame->code = std::stoul(match[6], nullptr, 16);
        canFdErrorFrame->codeExt = std::stoul(match[7], nullptr, 16);
        if (match[8] == "Data")
            canFdErrorFrame->phase = Phase::Data;
        canFdErrorFrame->position = std::stoul(match[9]);
        canFdErrorFrame->id = std::stoul(match[10], nullptr, 16);
        canFdErrorFrame->brs = (match[11] == '1');
        canFdErrorFrame->esi = (match[12] == '1');
        canFdErrorFrame->dlc = std::stoul(match[13], nullptr, 16);
        canFdErrorFrame->dataLength = std::stoul(match[14]);
        std::istringstream iss(match[15]);
        iss >> std::hex;
        for (uint8_t i = 0; i < canFdErrorFrame->dataLength && i < 64; ++i) {
            unsigned short s;
            iss >> s;
            canFdErrorFrame->data[i] = s;
        }
        canFdErrorFrame->messageDuration = std::stoul(match[17]);
        canFdErrorFrame->flags2 = std::stoul(match[18]);
        canFdErrorFrame->crc = std::stoul(match[19], nullptr, 16);
        canFdErrorFrame->bitTimingConfArb = std::stoul(match[20], nullptr, 16);
        canFdErrorFrame->bitTimingConfData = std::stoul(match[21], nullptr, 16);
        return canFdErrorFrame;
    }

    return nullptr;
}

void CanFdErrorFrame::write(File & file, std::ostream & stream)
{
    writeTime(file, stream, time);

    stream << endl;
}

}
}
