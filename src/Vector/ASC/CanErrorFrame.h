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

/** CAN Error Frame */
/* <Time> <Channel> ErrorFrame */
/* <Time> <Channel> ErrorFrame ECC:<ECC> */
/* <Time> <Channel> ErrorFrame Flags = <flags> CodeExt = <codeExt> Code = <code> ID = <ID> DLC = <DLC> Position = <Position> Length = <Length> */
class CanErrorFrame : public Event
{
public:
    CanErrorFrame();
    virtual ~CanErrorFrame();

    /** Time */
    float time;

    /** Channel */
    uint16_t channel;

    // CANcardXL, CANcaseXL, CANboardXL, and all other interfaces with SJA1000:
    uint8_t ecc;

    // Interfaces with CAN-Core:
    uint8_t flags;
    uint16_t codeExt;
    uint8_t code;
    uint32_t id;
    uint8_t dlc;
    uint8_t position;
    uint16_t length;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static CanErrorFrame * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
