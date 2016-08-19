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
class VECTOR_ASC_EXPORT EthernetStatus final : public Event
{
public:
    EthernetStatus();

    /** @copydoc EthTime */
    EthTime time;

    /** @copydoc EthChannel */
    EthChannel channel;

    /** Link */
    enum class Link {
        /** Unknown */
        Unknown = 0,

        /** Link_up */
        Up,

        /** Link_error */
        Error,

        /** Negotiate_link */
        Negotiate,

        /** Link_down */
        Down
    };

    /** Link */
    Link link;

    /** LinkSpeed in Mbit/s */
    uint32_t linkSpeed;

    /** Physical */
    enum class Physical {
        /** Unknown */
        Unknown = 0,

        /** IEEE802.3 */
        Ieee802_3,

        /** BroadR-Reach */
        BroadR_Reach
    };

    /** Physical */
    Physical physical;

    /** Duplex */
    enum class Duplex {
        /** Unknown */
        Unknown = 0,

        /** Full */
        Full,

        /** Half */
        Half
    };

    /** Duplex */
    Duplex duplex;

    /** MDI */
    enum class Mdi {
        /** Unknown */
        Unknown = 0,

        /** Crossover */
        Crossover,

        /** Direct */
        Direct
    };

    /** MDI */
    Mdi mdi;

    /** Connector */
    enum class Connector {
        /** Unknown */
        Unknown = 0,

        /** RJ45 */
        Rj45,

        /** D-Sub */
        DSub
    };

    /** Connector */
    Connector connector;

    /** BRClockMode */
    enum class BRClockMode {
        /** Unknown */
        Unknown = 0,

        /** Master */
        Master,

        /** Slave */
        Slave
    };

    /** BRClockMode */
    BRClockMode brClockMode;

    /** BRPairs */
    enum class BRPairs {
        /** Unknown */
        Unknown = 0,

        /** 1-pair */
        BR1Pair,

        /** 2-pair */
        BR2Pair,

        /** 4-pair */
        BR4Pair
    };

    /** BrPairs */
    BRPairs brPairs;

    /** @copydoc Event::read() */
    static EthernetStatus * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
