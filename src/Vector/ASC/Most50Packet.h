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
 * MOST50 Packet
 *
 * Message on MOST50 Packet Data Channel.
 */
class Most50Packet : public Event
{
public:
    Most50Packet();
    virtual ~Most50Packet();

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

    /** @copydoc MostRsvdUc */
    MostRsvdUc rsvdUc1;

    /** @copydoc MostRsvdUc */
    MostRsvdUc rsvdUc2;

    /** @copydoc MostRsvdUc */
    MostRsvdUc rsvdUc3;

    /** @copydoc MostCrc2 */
    MostCrc2 crc2;

    /** @copydoc MostRsvdUc */
    MostRsvdUc rsvdUc4;

    /** @copydoc MostRsvdUl */
    MostRsvdUl rsvdUl;

    /** @copydoc MostPktLen */
    MostPktLen pktLen;

    /** @copydoc MostDx */
    MostDx data[1024];

    /** @copydoc Event::parse() */
    static Most50Packet * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
