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
 * MOST50/150 Packet Fragment
 *
 * Partial transmitted message on MOST50 or MOST150 Packet Data Channel.
 */
struct VECTOR_ASC_EXPORT Most150PacketFragment final : Event {
    Most150PacketFragment() : Event(EventType::Most150PacketFragment) {}

    /** @copydoc MostTime */
    MostTime time {0.0};

    /** @copydoc MostChannel */
    MostChannel channel {0};

    /** @copydoc MostFrgMask */
    MostFrgMask frgMask {0};

    /** @copydoc MostSourceAdr */
    MostSourceAdr sourceAdr {0};

    /** @copydoc MostDestAdr */
    MostDestAdr destAdr {0};

    /** @copydoc MostAckNack */
    MostAckNack ackNack {0};

    /** @copydoc MostPack */
    MostPAck pAck {0};

    /** @copydoc MostRsvdUc */
    MostRsvdUc rsvdUc {0};

    /** @copydoc MostPindex */
    MostPIndex pIndex {0};

    /** @copydoc MostCrc2 */
    MostCrc2 crc2 {0};

    /** @copydoc MostCack */
    MostCAck cAck {0};

    /** @copydoc MostRsvdUl */
    MostRsvdUl rsvdUl {0};

    /** @copydoc MostFrgDataLen */
    MostFrgDataLen frgDataLen {0};

    /** @copydoc MostFrgDataLenAnnounced */
    MostFrgDataLenAnnounced frgDataLenAnnounced {0};

    /** @copydoc MostFirstDataLen */
    MostFirstDataLen firstDataLen {0};

    /** @copydoc MostDx */
    std::vector<MostDx> data {};

    /** @copydoc Event::read() */
    static Most150PacketFragment * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
