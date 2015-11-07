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
#include "LinReceiveError.h"

namespace Vector {
namespace ASC {

LinReceiveError::LinReceiveError() :
    Event(),
    time(0.0),
    channel(),
    id(0),
    dlc(0),
    description(),
    offendingByte(0),
    slaveId(0),
    state(0),
    headerTime(0),
    fullTime(0),
    stateReason(0),
    isShortError(false),
    isDlcTimeout(false),
    hasDataBytes(false),
    data(),
    startOfFrame(0.0),
    baudrate(0),
    syncBreak(0),
    syncDel(0),
    subId(0),
    messageId(0),
    supplierId(0),
    endOfHeader(0.0),
    endOfByte(),
    responseBaudrate(0.0),
    headerBaudrate(0.0),
    stopBitOffsetInHeader(0),
    stopBitOffsetInResponse(0),
    checksumModel()
{
    eventType = EventType::LinReceiveError;
}

LinReceiveError::~LinReceiveError()
{
}

LinReceiveError * LinReceiveError::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:alnum:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:digit:]]+)"
                " RcvError: (.*?)"
                " StateReason = ([[:xdigit:]]+)"
                " ShortError = ([01])"
                " DlcTimeout = ([01])"
                " HasDatabytes = ([01])(( [[:xdigit:]]+){0,8})?"
                "( SOF = ([[:digit:].]+))?"
                "( BR = ([[:digit:]]+))?"
                "( break = ([[:digit:]]+) ([[:digit:]]+))?"
                "( EOH = ([[:digit:].]+))?"
                "( EOB =(( [[:digit:].]+){0,8}))?"
                "( RBR = ([[:digit:]]+))?"
                "( RSO = ([[:digit:]]+))?"
                "( HBR = ([[:digit:].]+))?"
                "( HSO = ([[:digit:]]+))?"
                "( CSM = (enhanced))?$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinReceiveError * linReceiveError = new LinReceiveError;
        linReceiveError->time = std::stof(match[1]);
        linReceiveError->channel = match[2];
        linReceiveError->id = std::stoul(match[3], nullptr, 16);
        linReceiveError->dlc = std::stoul(match[4]);
        linReceiveError->description = match[5];
        linReceiveError->stateReason = std::stoul(match[6], nullptr, 16);
        linReceiveError->isShortError = (match[7] == '1');
        linReceiveError->isDlcTimeout = (match[8] == '1');
        linReceiveError->hasDataBytes = (match[9] == '1');
        std::istringstream iss1(match[10]);
        iss1 >> std::hex;
        for (uint8_t i = 0; i < linReceiveError->dlc && i < 8; ++i) {
            unsigned short s;
            iss1 >> s;
            linReceiveError->data[i] = s;
        }
        linReceiveError->startOfFrame = std::stof(match[13]);
        linReceiveError->baudrate = std::stoul(match[15]);
        linReceiveError->syncBreak = std::stoul(match[17]);
        linReceiveError->syncDel = std::stoul(match[18]);
        linReceiveError->endOfHeader = std::stof(match[20]);
        std::istringstream iss2(match[22]);
        for (uint8_t i = 0; i < linReceiveError->dlc && i < 8; ++i) {
            float s;
            iss2 >> s;
            linReceiveError->endOfByte[i] = s;
        }
        linReceiveError->responseBaudrate = std::stoul(match[25]);
        linReceiveError->stopBitOffsetInResponse = std::stoul(match[27]);
        linReceiveError->headerBaudrate = std::stof(match[29]);
        linReceiveError->stopBitOffsetInHeader = std::stoul(match[31]);
        linReceiveError->checksumModel = match[33];
        return linReceiveError;
    }

    return nullptr;
}

void LinReceiveError::write(File & file, std::ostream & stream)
{
}

}
}
