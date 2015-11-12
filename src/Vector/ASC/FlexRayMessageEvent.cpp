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
#include "FlexRayMessageEvent.h"

namespace Vector {
namespace ASC {

FlexRayMessageEvent::FlexRayMessageEvent() :
    Event(),
    time(0.0),
    flexRayEventType(),
    clusterNr(0),
    clientId(0),
    channelNr(0),
    channelMask(0),
    slotId(0),
    cycleNo(0),
    direction(),
    appParam(0),
    flags(0),
    ccType(0),
    ccData(0),
    headerCrc(0),
    name(),
    payloadLength(0),
    bufferLength(0),
    data(),
    frameCrc(0),
    spyFlag(0),
    frameLengthNs(0),
    pduOffset(0)
{
    eventType = EventType::FlexRayMessageEvent;
}

FlexRayMessageEvent::~FlexRayMessageEvent()
{
}

FlexRayMessageEvent * FlexRayMessageEvent::parseRmsg(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " Fr"
                " (RMSG)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " (Rx|Tx)"
                " ([[:digit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:alnum:]_\\[\\|\\]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                "(( [[:xdigit:]]+)*)"
                " ([[:xdigit:]]+)"
                " ([01])"
                " ([[:digit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        FlexRayMessageEvent * flexRayMessageEvent = new FlexRayMessageEvent;
        flexRayMessageEvent->time = std::stod(match[1]);
        flexRayMessageEvent->flexRayEventType = match[2];
        flexRayMessageEvent->clusterNr = std::stoul(match[3]);
        flexRayMessageEvent->clientId = std::stoul(match[4]);
        flexRayMessageEvent->channelNr = std::stoul(match[5]);
        flexRayMessageEvent->channelMask = std::stoul(match[6]);
        flexRayMessageEvent->slotId = std::stoul(match[7]);
        flexRayMessageEvent->cycleNo = std::stoul(match[8]);
        flexRayMessageEvent->direction = match[9];
        flexRayMessageEvent->appParam = std::stoul(match[10]);
        flexRayMessageEvent->flags = std::stoul(match[11]);
        flexRayMessageEvent->ccType = std::stoul(match[12]);
        flexRayMessageEvent->ccData = std::stoul(match[13]);
        flexRayMessageEvent->headerCrc = std::stoul(match[14]);
        flexRayMessageEvent->name = match[15];
        flexRayMessageEvent->payloadLength = std::stoul(match[16]);
        flexRayMessageEvent->bufferLength = std::stoul(match[17]);
        std::istringstream iss(match[18]);
        for (uint8_t i = 0; i < flexRayMessageEvent->bufferLength && i < 256; ++i) {
            unsigned short s;
            iss >> s;
            flexRayMessageEvent->data[i] = s;
        }
        flexRayMessageEvent->frameCrc = std::stoul(match[20]);
        flexRayMessageEvent->spyFlag = (match[21] == '1');
        flexRayMessageEvent->frameLengthNs = std::stoul(match[22]);
        return flexRayMessageEvent;
    }

    return nullptr;
}

FlexRayMessageEvent * FlexRayMessageEvent::parsePdu(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " Fr"
                " (PDU)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " (Rx|Tx)"
                " ([[:digit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                " ([[:alnum:]_\\[\\|\\]]+)"
                " ([[:xdigit:]]+)"
                " ([[:xdigit:]]+)"
                "(( [[:xdigit:]]+)*)"
                " ([[:xdigit:]]+)"
                " ([01])"
                " ([[:digit:]]+)"
                " ([[:digit:]]+)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        FlexRayMessageEvent * flexRayMessageEvent = new FlexRayMessageEvent;
        flexRayMessageEvent->time = std::stod(match[1]);
        flexRayMessageEvent->flexRayEventType = match[2];
        flexRayMessageEvent->clusterNr = std::stoul(match[3]);
        flexRayMessageEvent->clientId = std::stoul(match[4]);
        flexRayMessageEvent->channelNr = std::stoul(match[5]);
        flexRayMessageEvent->channelMask = std::stoul(match[6]);
        flexRayMessageEvent->slotId = std::stoul(match[7]);
        flexRayMessageEvent->cycleNo = std::stoul(match[8]);
        flexRayMessageEvent->direction = match[9];
        flexRayMessageEvent->appParam = std::stoul(match[10]);
        flexRayMessageEvent->flags = std::stoul(match[11]);
        flexRayMessageEvent->ccType = std::stoul(match[12]);
        flexRayMessageEvent->ccData = std::stoul(match[13]);
        flexRayMessageEvent->headerCrc = std::stoul(match[14]);
        flexRayMessageEvent->name = match[15];
        flexRayMessageEvent->payloadLength = std::stoul(match[16]);
        flexRayMessageEvent->bufferLength = std::stoul(match[17]);
        std::istringstream iss(match[18]);
        for (uint8_t i = 0; i < flexRayMessageEvent->bufferLength && i < 256; ++i) {
            unsigned short s;
            iss >> s;
            flexRayMessageEvent->data[i] = s;
        }
        flexRayMessageEvent->frameCrc = std::stoul(match[20]);
        flexRayMessageEvent->spyFlag = (match[21] == '1');
        flexRayMessageEvent->frameLengthNs = std::stoul(match[22]);
        flexRayMessageEvent->pduOffset = std::stoul(match[23]);
        return flexRayMessageEvent;
    }

    return nullptr;
}

FlexRayMessageEvent * FlexRayMessageEvent::parse(File & file, std::string & line)
{
    FlexRayMessageEvent * flexRayMessageEvent;

    flexRayMessageEvent = parseRmsg(file, line);
    if (flexRayMessageEvent != nullptr)
        return flexRayMessageEvent;

    flexRayMessageEvent = parsePdu(file, line);
    if (flexRayMessageEvent != nullptr)
        return flexRayMessageEvent;

    return nullptr;
}

void FlexRayMessageEvent::write(File & file, std::ostream & stream)
{
}

}
}
