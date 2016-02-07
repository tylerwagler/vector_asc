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

#include "platform.h"

#include <vector>

#include "Event.h"
#include "MostSymbols.h"

namespace Vector {
namespace ASC {

/**
 * MOST25 Packet
 *
 * Message on MOST25 Packet Data Channel.
 */
class Most25Packet : public Event
{
public:
    Most25Packet();

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

    /** @copydoc MostPktState */
    MostPktState pktState;

    /** @copydoc MostTransferType */
    MostTransferType transferType;

    /** @copydoc MostPktPrio */
    MostPktPrio pktPrio;

    /** @copydoc MostPktArbitr */
    MostPktArbitr pktArbitr;

    /** @copydoc MostCrc2 */
    MostCrc2 crc2;

    /** @copydoc MostPktLen */
    MostPktLen pktLen;

    /** @copydoc MostDx */
    std::vector<MostDx> data;

    /** @copydoc Event::parse() */
    static Most25Packet * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
