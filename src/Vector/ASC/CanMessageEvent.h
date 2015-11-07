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

#include <string>
#include "Event.h"

namespace Vector {
namespace ASC {

/** CAN Message Event */
/* <Time> <Channel> <ID> <Dir> d <DLC> <D0> <D1>...<D8> <MessageFlags> */
/* <Time> <Channel> <ID> <Dir> d <DLC> <D0> <D1>...<D8> Length = <MessageDuration> BitCount = <MessageLength> <MessageFlags> */
/* <Time> <Channel> <ID> <Dir> d <DLC> <D0> <D1>...<D8> Length = <MessageDuration> BitCount = <MessageLength> ID = <IDnum> <MessageFlags> */
class CanMessageEvent : public Event
{
public:
    CanMessageEvent();
    virtual ~CanMessageEvent();

    /** Time */
    float time;

    /** Channel */
    uint16_t channel;

    /** ID */
    uint32_t id;

    /** Dir */
    enum class Dir {
        Rx,
        Tx
    };

    Dir dir;

    /** DLC */
    uint8_t dlc;

    /** Data */
    uint8_t data[8];

    /** Message Duration */
    uint32_t messageDuration;

    /** Message Length / Bit Count */
    uint8_t messageLength;

    /** Message ID */
    uint32_t messageId;

    /** Some special message flags that are written at the end of a logging line. */
    typedef struct {
        /**
         * "Transmission Error (NERR signal).
         * Indicates whether a line has failed during a two-wire operation.
         * Especially available on Single-Wire mode.
         */
        bool te;

        /**
         * "Wake-Up.
         * Indicates whether a message transmitted with overvoltage
         * with the purpose of waking up the CAN controller.
         */
        bool wu;
    } MessageFlags;

    /** Message Flags */
    MessageFlags messageFlags;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static CanMessageEvent * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
