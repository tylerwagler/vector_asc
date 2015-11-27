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
#include "MostSymbols.h"

namespace Vector {
namespace ASC {

/**
 * MOST150 Control Message
 *
 * Message on MOST150 Control Channel.
 */
class Most150ControlMessage : public Event
{
public:
    Most150ControlMessage();
    virtual ~Most150ControlMessage();

    /** @copydoc MostTime */
    MostTime time;

    /** @copydoc MostChannel */
    MostChannel channel;

    /** @copydoc MostDir */
    MostDir dir;

    /** @copydoc MostSourceAdr */
    MostSourceAdr sourceAdr;

    /** @copydoc MostDestAdr */
    MostDestAdr destAdr;

    /** @copydoc MostState */
    MostState state;

    /** @copydoc MostAckNack */
    MostAckNack ackNack;

    /** @copydoc MostTransferType */
    MostTransferType transferType;

    /** @copydoc MostPack */
    MostPack pack;

    /** @copydoc MostPriority */
    MostPriority priority;

    /** @copydoc MostPindex */
    MostPindex pIndex;

    /** @copydoc MostCrc2 */
    MostCrc2 crc2;

    /** @copydoc MostCack */
    MostCack cAck;

    /** @copydoc MostRsvdUl */
    MostRsvdUl rsvdUl;

    /** @copydoc MostMsg150Len */
    MostMsg150Len msg150Len;

    /** @copydoc MostDx */
    MostDx data[1024];

    /** @copydoc Event::parse() */
    static Most150ControlMessage * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
