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

#include "Event.h"
#include "EthernetSymbols.h"

#include "vector_asc_export.h"

namespace Vector {
namespace ASC {

/**
 * Ethernet Status
 *
 * Ethernet link status.
 */
class VECTOR_ASC_EXPORT EthernetStatus : public Event
{
public:
    EthernetStatus();

    /** @copydoc EthTime */
    EthTime time;

    /** @copydoc EthChannel */
    EthChannel channel;

    /** Link */
    std::string link;
    /* "Link_up", "Link_error", "Negotiate_link", "Link_down" */

    /** LinkSpeed */
    std::string linkSpeed;
    /* "Mbit/s" */

    /** Physical */
    std::string physical;
    /* "IEEE802.3", "BroadR-Reach" */

    /** Duplex */
    std::string duplex;
    /* "Full", "Half" */

    /** MDI */
    std::string mdi;
    /* "Crossover", "Direct" */

    /** Connector */
    std::string connector;
    /* "RJ45", "D-Sub" */

    /** BRClockMode */
    std::string brClockMode;
    /* "Master", "Slave" */

    /** BrPairs */
    std::string brPairs;
    /* "1-pair", "2-pair", "4-pair" */

    /** @copydoc Event::read() */
    static EthernetStatus * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
