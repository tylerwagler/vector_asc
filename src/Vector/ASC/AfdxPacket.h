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
#include <Vector/ASC/EthernetSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * AFDX Packet
 *
 * Receive or transmitted AFDX packet.
 */
struct VECTOR_ASC_EXPORT AfdxPacket final : Event {
    AfdxPacket() : Event(EventType::AfdxPacket) {}

    /** @copydoc AfdxTime */
    AfdxTime time {0.0};

    /** @copydoc AfdxChannel */
    AfdxChannel channel {0};

    /** @copydoc AfdxDir */
    AfdxDir dir {Dir::Rx};

    /** @copydoc AfdxEthChannel */
    AfdxEthChannel ethChannel {0};

    /** @copydoc AfdxFlags */
    AfdxFlags flags {0};

    /** @copydoc AfdxBag */
    AfdxBag bag {0};

    /** @copydoc AfdxDataLen */
    AfdxDataLen dataLen {0};

    /** @copydoc AfdxData */
    std::vector<AfdxData> data {};

    /** @copydoc Event::read() */
    static AfdxPacket * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
