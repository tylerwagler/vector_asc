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

#include <vector>

#include <Vector/ASC/Event.h>
#include <Vector/ASC/MostSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * MOST50 Packet
 *
 * Message on MOST50 Packet Data Channel.
 */
struct VECTOR_ASC_EXPORT Most50Packet final : Event {
    Most50Packet() : Event(EventType::Most50Packet) {}

    /** @copydoc MostTime */
    MostTime time {0.0};

    /** @copydoc MostChannel */
    MostChannel channel {0};

    /** @copydoc MostDir */
    MostDir dir {Dir::Rx};

    /** @copydoc MostSourceAdr */
    MostSourceAdr sourceAdr {0};

    /** @copydoc MostDestAdr */
    MostDestAdr destAdr {0};

    /** @copydoc MostState */
    MostState state {0};

    /** @copydoc MostAckNack */
    MostAckNack ackNack {0};

    /** @copydoc MostTransferType */
    MostTransferType transferType {MostTransferType::Node};

    /** @copydoc MostRsvdUc */
    MostRsvdUc rsvdUc1 {0};

    /** @copydoc MostRsvdUc */
    MostRsvdUc rsvdUc2 {0};

    /** @copydoc MostRsvdUc */
    MostRsvdUc rsvdUc3 {0};

    /** @copydoc MostCrc2 */
    MostCrc2 crc2 {0};

    /** @copydoc MostRsvdUc */
    MostRsvdUc rsvdUc4 {0};

    /** @copydoc MostRsvdUl */
    MostRsvdUl rsvdUl {0};

    /** @copydoc MostPktLen */
    MostPktLen pktLen {0};

    /** @copydoc MostDx */
    std::vector<MostDx> data {};

    /** @copydoc Event::read() */
    static Most50Packet * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
