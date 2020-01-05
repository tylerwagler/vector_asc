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
#include <sstream>

#include <Vector/ASC/FlexRayCommon.h>
#include <Vector/ASC/FlexRayMessage.h>
#include <Vector/ASC/FlexRaySymbolsRegEx.h>

namespace Vector {
namespace ASC {

FlexRayMessage * FlexRayMessage::readRmsg(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_FlexRay_Time REGEX_WS "Fr" REGEX_WS "RMSG"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS REGEX_FlexRay_Dir REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "([[:alnum:]_\\[\\|\\]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     "((" REGEX_WS "[[:xdigit:]]+){0,254})" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "([01])" REGEX_WS "([[:digit:]]+)"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * flexRayMessage = new FlexRayMessage;
        flexRayMessage->time = std::stod(match[1]);
        flexRayMessage->flexRayEventType = FlexRayEventType::RMSG;
        flexRayMessage->clusterNr = std::stoul(match[2]);
        flexRayMessage->clientId = std::stoul(match[3]);
        flexRayMessage->channelNr = std::stoul(match[4]);
        flexRayMessage->channelMask = std::stoul(match[5]);
        flexRayMessage->slotId = std::stoul(match[6]);
        flexRayMessage->cycleNo = std::stoul(match[7]);
        if (match[8] == "Rx")
            flexRayMessage->direction = Dir::Rx;
        else if (match[8] == "Tx")
            flexRayMessage->direction = Dir::Tx;
        else if (match[8] == "TxRq")
            flexRayMessage->direction = Dir::TxRq;
        flexRayMessage->appParam = std::stoul(match[9]);
        flexRayMessage->flags = std::stoul(match[10]);
        flexRayMessage->ccType = std::stoul(match[11]);
        flexRayMessage->ccData = std::stoul(match[12]);
        flexRayMessage->headerCrc = std::stoul(match[13]);
        flexRayMessage->name = match[14];
        flexRayMessage->payloadLength = std::stoul(match[15]);
        flexRayMessage->bufferLength = std::stoul(match[16]);
        std::istringstream iss(match[17]);
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            flexRayMessage->data.push_back(s);
        }
        flexRayMessage->frameCrc = std::stoul(match[19]);
        flexRayMessage->spyFlag = (match[20] == '1');
        flexRayMessage->frameLengthNs = std::stoul(match[21]);
        return flexRayMessage;
    }

    return nullptr;
}

FlexRayMessage * FlexRayMessage::readPdu(File & file, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_FlexRay_Time REGEX_WS "Fr" REGEX_WS "PDU"
                     REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS REGEX_FlexRay_Dir REGEX_WS "([[:digit:]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "([[:alnum:]_\\[\\|\\]]+)"
                     REGEX_WS "([[:xdigit:]]+)" REGEX_WS "([[:xdigit:]]+)"
                     "((" REGEX_WS "[[:xdigit:]]+){0,254})" REGEX_WS "([[:xdigit:]]+)"
                     REGEX_WS "([01])" REGEX_WS "([[:digit:]]+)" REGEX_WS "([[:digit:]]+)"
                     REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * flexRayMessage = new FlexRayMessage;
        flexRayMessage->time = std::stod(match[1]);
        flexRayMessage->flexRayEventType = FlexRayEventType::PDU;
        flexRayMessage->clusterNr = std::stoul(match[2]);
        flexRayMessage->clientId = std::stoul(match[3]);
        flexRayMessage->channelNr = std::stoul(match[4]);
        flexRayMessage->channelMask = std::stoul(match[5]);
        flexRayMessage->slotId = std::stoul(match[6], nullptr, file.base);
        flexRayMessage->cycleNo = std::stoul(match[7], nullptr, file.base);
        if (match[8] == "Rx")
            flexRayMessage->direction = Dir::Rx;
        else if (match[8] == "Tx")
            flexRayMessage->direction = Dir::Tx;
        else if (match[8] == "TxRq")
            flexRayMessage->direction = Dir::TxRq;
        flexRayMessage->appParam = std::stoul(match[9]);
        flexRayMessage->flags = std::stoul(match[10], nullptr, file.base);
        flexRayMessage->ccType = std::stoul(match[11], nullptr, file.base);
        flexRayMessage->ccData = std::stoul(match[12], nullptr, file.base);
        flexRayMessage->headerCrc = std::stoul(match[13], nullptr, file.base);
        flexRayMessage->name = match[14];
        flexRayMessage->payloadLength = std::stoul(match[15], nullptr, file.base);
        flexRayMessage->bufferLength = std::stoul(match[16], nullptr, file.base);
        std::istringstream iss(match[17]);
        switch (file.base) {
        case 10:
            iss >> std::dec;
            break;
        case 16:
            iss >> std::hex;
            break;
        }
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            flexRayMessage->data.push_back(s);
        }
        flexRayMessage->frameCrc = std::stoul(match[19], nullptr, file.base);
        flexRayMessage->spyFlag = (match[20] == '1');
        flexRayMessage->frameLengthNs = std::stoul(match[21]);
        flexRayMessage->pduOffset = std::stoul(match[22]);
        return flexRayMessage;
    }

    return nullptr;
}

FlexRayMessage * FlexRayMessage::read(File & file, std::string & line) {
    FlexRayMessage * flexRayMessage;

    flexRayMessage = readRmsg(file, line);
    if (flexRayMessage != nullptr)
        return flexRayMessage;

    flexRayMessage = readPdu(file, line);
    if (flexRayMessage != nullptr)
        return flexRayMessage;

    return nullptr;
}

void FlexRayMessage::write(File & file, std::ostream & stream) {
    writeTime(file, stream, time);
    stream << " Fr ";

    switch (flexRayEventType) {
    case FlexRayEventType::RMSG:
        /* format: "RMSG " */
        stream << "RMSG ";
        break;
    case FlexRayEventType::PDU:
        /* format: "PDU  " */
        stream << "PDU  ";
        break;
    };

    stream
            << std::dec
            << clusterNr
            << ' ' << clientId
            << ' ' << channelNr
            << ' ' << channelMask;

    switch (file.base) {
    case 10:
        stream
                << ' ' << std::dec << slotId
                << ' ' << std::dec << cycleNo
                << ' ';
        writeDir(file, stream, direction);
        stream
                << ' ' << std::dec << appParam
                << ' ' << std::dec << flags
                << ' ' << std::dec << ccType
                << ' ' << std::dec << ccData
                << ' ' << std::dec << headerCrc
                << ' ' << name
                << ' ' << std::dec << payloadLength
                << ' ' << std::dec << bufferLength;
        writeData(file, stream, data);
        stream
                << ' ' << std::dec << frameCrc
                << ' ' << (spyFlag ? '1' : '0')
                << ' ' << std::dec << frameLengthNs;
        if (flexRayEventType == FlexRayEventType::PDU)
            stream << ' ' << std::dec << pduOffset;
        break;
    case 16:
        stream
                << ' ' << std::hex << slotId
                << ' ' << std::hex << cycleNo
                << ' ';
        writeDir(file, stream, direction);
        stream
                << ' ' << std::dec << appParam
                << ' ' << std::hex << flags
                << ' ' << std::hex << ccType
                << ' ' << std::hex << ccData
                << ' ' << std::hex << headerCrc
                << ' ' << name
                << ' ' << std::hex << payloadLength
                << ' ' << std::hex << bufferLength;
        writeData(file, stream, data);
        stream
                << ' ' << std::hex << frameCrc
                << ' ' << (spyFlag ? '1' : '0')
                << ' ' << std::dec << frameLengthNs;
        if (flexRayEventType == FlexRayEventType::PDU)
            stream << ' ' << std::dec << pduOffset;
        break;
    }

    stream << endl;
}

}
}
