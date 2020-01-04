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

#include <Vector/ASC/platform.h>

#include <Vector/ASC/Event.h>
#include <Vector/ASC/EthernetSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * Ethernet Status
 *
 * Ethernet link status.
 */
struct VECTOR_ASC_EXPORT EthernetStatus final : Event {
    EthernetStatus() : Event(EventType::EthernetStatus) {}

    /** @copydoc EthTime */
    EthTime time {0.0};

    /** @copydoc EthChannel */
    EthChannel channel {0};

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
    Link link {Link::Unknown};

    /** LinkSpeed in Mbit/s */
    uint32_t linkSpeed {0};

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
    Physical physical {Physical::Unknown};

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
    Duplex duplex {Duplex::Unknown};

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
    Mdi mdi {Mdi::Unknown};

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
    Connector connector {Connector::Unknown};

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
    BRClockMode brClockMode {BRClockMode::Unknown};

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
    BRPairs brPairs {BRPairs::Unknown};

    /** @copydoc Event::read() */
    static EthernetStatus * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
