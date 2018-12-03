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
class VECTOR_ASC_EXPORT AfdxPacket final : public Event
{
public:
    AfdxPacket();

    /** @copydoc AfdxTime */
    AfdxTime time;

    /** @copydoc AfdxChannel */
    AfdxChannel channel;

    /** @copydoc AfdxDir */
    AfdxDir dir;

    /** @copydoc AfdxEthChannel */
    AfdxEthChannel ethChannel;

    /** @copydoc AfdxFlags */
    AfdxFlags flags;

    /** @copydoc AfdxBag */
    AfdxBag bag;

    /** @copydoc AfdxDataLen */
    AfdxDataLen dataLen;

    /** @copydoc AfdxData */
    std::vector<AfdxData> data;

    /** @copydoc Event::read() */
    static AfdxPacket * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
