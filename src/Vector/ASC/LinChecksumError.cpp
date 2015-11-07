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
#include "LinChecksumError.h"

namespace Vector {
namespace ASC {

LinChecksumError::LinChecksumError() :
    Event(),
    time(0.0),
    channel(),
    id(0),
    dir(Dir::Rx),
    dlc(0),
    data(),
    slaveId(0),
    state(0),
    checksum(0),
    headerTime(0),
    fullTime(0),
    startOfFrame(0.0),
    baudrate(0),
    syncBreak(0),
    syncDel(0),
    subId(0),
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
    checksumModel()
{
    eventType = EventType::LinChecksumError;
}

LinChecksumError::~LinChecksumError()
{
}

LinChecksumError * LinChecksumError::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " L([[:alnum:]]+)"
                " ([[:xdigit:]]+)"
                " CSErr"
                " (Rx|Tx)"
                " ([[:digit:]]+)"
                "(( [[:xdigit:]]+){0,8})?"
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
                "( CSM = (enhanced))?$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        LinChecksumError * linChecksumError = new LinChecksumError;
        linChecksumError->time = std::stof(match[1]);
        linChecksumError->channel = match[2];
        linChecksumError->id = std::stoul(match[3], nullptr, 16);
        if (match[4] == "Rx")
                linChecksumError->dir = Dir::Rx;
        if (match[4] == "Tx")
                linChecksumError->dir = Dir::Tx;
        linChecksumError->dlc = std::stoul(match[5]);
        std::istringstream iss1(match[6]);
        iss1 >> std::hex;
        for (uint8_t i = 0; i < linChecksumError->dlc && i < 8; ++i) {
            unsigned short s;
            iss1 >> s;
            linChecksumError->data[i] = s;
        }
        linChecksumError->checksum = std::stoul(match[9], nullptr, 16);
        linChecksumError->headerTime = std::stoul(match[11]);
        linChecksumError->fullTime = std::stoul(match[12]);
        linChecksumError->startOfFrame = std::stof(match[14]);
        linChecksumError->baudrate = std::stoul(match[16]);
        linChecksumError->syncBreak = std::stoul(match[18]);
        linChecksumError->syncDel = std::stoul(match[19]);
        linChecksumError->endOfHeader = std::stof(match[21]);
        std::istringstream iss2(match[23]);
        for (uint8_t i = 0; i < linChecksumError->dlc && i < 8; ++i) {
            float s;
            iss2 >> s;
            linChecksumError->endOfByte[i] = s;
        }
        linChecksumError->simulated = (match[26] == '1');
        linChecksumError->endOfFrame = std::stof(match[28]);
        linChecksumError->responseBaudrate = std::stoul(match[30]);
        linChecksumError->headerBaudrate = std::stof(match[32]);
        linChecksumError->stopBitOffsetInHeader = std::stoul(match[34]);
        linChecksumError->stopBitOffsetInResponse = std::stoul(match[36]);
        linChecksumError->checksumModel = match[38];
        return linChecksumError;
    }

    return nullptr;
}

void LinChecksumError::write(File & file, std::ostream & stream)
{
}

}
}
