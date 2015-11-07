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

/** CAN Extended Message Event */
/* <Time> <Channel> <ID>x <Dir> d <DLC> <D0> <D1>...<D8> <MessageFlags> */
/* <Time> <Channel> <ID>x <Dir> d <DLC> <D0> <D1>...<D8> Length = <MessageDuration> BitCount = <MessageLength> <MessageFlags> */
/* <Time> <Channel> <ID>x <Dir> d <DLC> <D0> <D1>...<D8> Length = <MessageDuration> BitCount = <MessageLength> <MessageFlags> ID = <IDnum>x */
class CanExtendedMessageEvent : public Event
{
public:
    CanExtendedMessageEvent();
    virtual ~CanExtendedMessageEvent();

    /** Time */
    float time;

    /** Channel */
    unsigned int channel;

    /** ID */
    unsigned int id;

    /** Dir */
    enum class Dir {
        Rx,
        Tx
    };

    Dir dir;

    /** DLC */
    unsigned short dlc;

    /** Data */
    unsigned short data[8];

    /** Message Duration */
    unsigned int messageDuration;

    /** Message Length / Bit Count */
    unsigned int messageLength;

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
    static CanExtendedMessageEvent * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
