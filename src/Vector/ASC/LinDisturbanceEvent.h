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

/** LIN Disturbance event */
/*  <Time> <Channel> DisturbanceEvent Type = <DisturbanceType> ByteIndex = <ByteIndex> BitIndex =
 * <BitIndex> BitOffset = <BitOffsetInSixteenthBits> Length = <DisturbanceLengthInSixteenthBits> Header
 * = <IDorFF> Disturbing header = <IDorFF> */
class LinDisturbanceEvent : public Event
{
public:
    LinDisturbanceEvent();
    virtual ~LinDisturbanceEvent();

    /** Time */
    float time;

    /** Channel */
    std::string channel;

    /** DisturbanceType */
    std::string disturbanceType;

    /** ByteIndex */
    uint16_t byteIndex;

    /** BitIndex */
    uint8_t bitIndex;

    /** BitOffset */
    uint8_t bitOffset;

    /** Length */
    uint16_t length;

    /** Header */
    uint8_t header;

    /** Disturbing header */
    uint8_t disturbingHeader;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static LinDisturbanceEvent * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
