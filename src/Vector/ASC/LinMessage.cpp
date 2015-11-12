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
#include "LinMessage.h"

namespace Vector {
namespace ASC {

LinMessage::LinMessage() :
    Event(),
    time(0.0),
    channel(0),
    id(),
    dir(Dir::Rx),
    dlc(0),
    data(),
    slaveId(0),
    state(0),
    checksum(0),
    headerTime(0),
    fullTime(0),
    startOfFrame(0.0),
    syncBreakTime(),
    syncDelimiterTime(),
    baudrate(0),
    syncBreak(0),
    syncDel(0),
    nad(0),
    messageId(0),
    supplierId(0),
    endOfHeader(0.0),
    endOfByte(),
    simulated(false),
    endOfFrame(0.0),
    responseBaudrate(0),
    headerBaudrate(0.0),
    stopBitOffsetInHeader(0),
    stopBitOffsetInResponse(0),
    checksumModel(LinChecksumModel::Unknown)
{
    eventType = EventType::LinMessage;
}

LinMessage::~LinMessage()
{
}

LinMessage * LinMessage::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:alnum:]]+)"
                " ([[:xdigit:]]+)"
                " (Rx|Tx)"
                " ([[:digit:]]+)(( [[:xdigit:]]+){0,8})?"
                "( checksum = ([[:digit:]]+))?"
                "( header time = ([[:digit:]]+), full time = ([[:digit:]]+))?"
                "( SOF = ([[:digit:].]+))?"
                "( BR = ([[:digit:]]+))?"
                "( break = ([[:digit:]]+) ([[:digit:]]+))?"
                "( EOH = ([[:digit:].]+))?"
                "( EOB =(( [[:digit:].]+){0,8}))?"
                "( sim = ([01]))?"
                "( EOF = ([[:digit:].]+))?"
                "( RBR = ([[:digit:]]+))?"
                "( HBR = ([[:digit:].]+))?"
                "( HSO = ([[:digit:]]+))?"
                "( RSO = ([[:digit:]]+))?"
                "( CSM = (unknown|classic|enhanced|error))?$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinMessage * linMessage = new LinMessage;
        linMessage->time = std::stod(match[1]);
        linMessage->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linMessage->id = match[3];
        if (match[4] == "Rx")
                linMessage->dir = Dir::Rx;
        else
        if (match[4] == "Tx")
                linMessage->dir = Dir::Tx;
        linMessage->dlc = std::stoul(match[5]);
        std::istringstream iss1(match[6]);
        iss1 >> std::hex;
        for (uint8_t i = 0; i < linMessage->dlc && i < 8; ++i) {
            unsigned short s;
            iss1 >> s;
            linMessage->data[i] = s;
        }
        linMessage->checksum = std::stoul(match[9]);
        linMessage->headerTime = std::stoul(match[11]);
        linMessage->fullTime = std::stoul(match[12]);
        linMessage->startOfFrame = std::stod(match[14]);
        linMessage->baudrate = std::stoul(match[16]);
        linMessage->syncBreak = std::stoul(match[18]);
        linMessage->syncDel = std::stoul(match[19]);
        linMessage->endOfHeader = std::stod(match[21]);
        std::istringstream iss2(match[23]);
        for (uint8_t i = 0; i < linMessage->dlc && i < 8; ++i) {
            double s;
            iss2 >> s;
            linMessage->endOfByte[i] = s;
        }
        linMessage->simulated = (match[26] == '1');
        linMessage->endOfFrame = std::stod(match[28]);
        linMessage->responseBaudrate = std::stoul(match[30]);
        linMessage->headerBaudrate = std::stod(match[32]);
        linMessage->stopBitOffsetInHeader = std::stoul(match[34]);
        linMessage->stopBitOffsetInResponse = std::stoul(match[36]);
        if (match[38] == "unknown")
            linMessage->checksumModel = LinChecksumModel::Unknown;
        else
        if (match[38] == "classic")
            linMessage->checksumModel = LinChecksumModel::Classic;
        else
        if (match[38] == "enhanced")
            linMessage->checksumModel = LinChecksumModel::Enhanced;
        else
        if (match[38] == "error")
            linMessage->checksumModel = LinChecksumModel::Error;
        return linMessage;
    }

    return nullptr;
}

void LinMessage::write(File & file, std::ostream & stream)
{
}

}
}
