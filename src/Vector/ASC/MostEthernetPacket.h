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
 * MOST Ethernet Packet
 *
 * Message on MOST150 Ethernet Packet Channel.
 */
class MostEthernetPacket : public Event
{
public:
    MostEthernetPacket();

    /** @copydoc MostTime */
    MostTime time;

    /** @copydoc MostChannel */
    MostChannel channel;

    /** @copydoc MostDir */
    MostDir dir;

    /** @copydoc MostSourceMacAdr */
    MostSourceMacAdr sourceMacAdr;

    /** @copydoc MostDestMacAdr */
    MostDestMacAdr destMacAdr;

    /** @copydoc MostState */
    MostState state;

    /** @copydoc MostAckNack */
    MostAckNack ackNack;

    /** @copydoc MostTransferType */
    MostTransferType transferType;

    /** @copydoc MostPack */
    MostPAck pAck;

    /** @copydoc MostCrc4 */
    MostCrc4 crc4;

    /** @copydoc MostCack */
    MostCAck cAck;

    /** @copydoc MostRsvdUl */
    MostRsvdUl rsvdUl;

    /** @copydoc MostPktEthLen */
    MostPktEthLen pktEthLen;

    /** @copydoc MostDx */
    std::vector<MostDx> data;

    /** @copydoc Event::parse() */
    static MostEthernetPacket * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
