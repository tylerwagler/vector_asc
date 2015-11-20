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

#pragma once

#include "Event.h"

namespace Vector {
namespace ASC {

/**
 * FlexRay Message Event ("RMSG / PDU")
 *
 * FlexRay Message received or transmitted on a FlexRay channel.
 */
class FlexRayMessageEvent : public Event
{
public:
    FlexRayMessageEvent();
    virtual ~FlexRayMessageEvent();

    /** Timestamp */
    double time;

    /** Event type */
    enum FlexRayEventType : uint8_t {
        RMSG,
        PDU
    };

    /** Event type */
    FlexRayEventType flexRayEventType;

    /** Clusternr. */
    uint32_t clusterNr;

    /** Client-ID */
    uint32_t clientId;

    /** Channelnr. */
    uint32_t channelNr;

    /** Channel mask */
    uint32_t channelMask;

    /** Slot ID */
    uint32_t slotId;

    /** Cycle no. */
    uint32_t cycleNo;

    /** Direction */
    std::string direction;

    /** App. param. */
    uint32_t appParam;

    /** Flags */
    uint32_t flags;

    /** CC-Type. */
    uint32_t ccType;

    /** CC-Data */
    uint32_t ccData;

    /** Header CRC */
    uint32_t headerCrc;

    /** Name */
    std::string name;

    /** Payload length */
    int32_t payloadLength;

    /** Buffer length */
    int32_t bufferLength;

    /** Data[n] */
    uint32_t data[254];

    /** Frame CRC */
    uint32_t frameCrc;

    /** Spy Flag */
    uint32_t spyFlag;

    /** Frame Length NS */
    uint32_t frameLengthNs;

    /** PDU Offset */
    int32_t pduOffset;

    /** @copydoc Event::parse() */
    static FlexRayMessageEvent * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);

private:
    static FlexRayMessageEvent * parseRmsg(File & file, std::string & line);
    static FlexRayMessageEvent * parsePdu(File & file, std::string & line);
};

}
}
