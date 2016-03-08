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
#include "CanSymbols.h"

#include "vector_asc_export.h"

namespace Vector {
namespace ASC {

/**
 * CAN FD Extended Message Event
 *
 * An Overload Frame received on a CAN channel.
 */
class VECTOR_ASC_EXPORT CanFdExtendedMessage : public Event
{
public:
    CanFdExtendedMessage();

    /** @copydoc Time */
    Time time;

    /** @copydoc Channel */
    Channel channel;

    /** @copydoc Dir */
    Dir dir;

    /** @copydoc IdNum */
    IdNum id;

    /** SymbolicName */
    std::string symbolicName;

    /** @copydoc Brs */
    Brs brs;

    /** @copydoc Esi */
    Esi esi;

    /** @copydoc Dlc */
    Dlc dlc;

    /** @copydoc DataLength */
    DataLength dataLength;

    /** Data */
    std::vector<Dx> data;

    /** @copydoc MessageDuration */
    MessageDuration messageDuration;

    /** @copydoc MessageLength */
    MessageLength messageLength;

    /** Flags */
    uint32_t flags;

    /** CRC */
    uint32_t crc;

    /** @copydoc BitTimingConfArb */
    BitTimingConfArb bitTimingConfArb;

    /** @copydoc BitTimingConfData */
    BitTimingConfData bitTimingConfData;

    /** @copydoc Event::read() */
    static CanFdExtendedMessage * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
