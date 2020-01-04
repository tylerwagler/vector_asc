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
#include <Vector/ASC/CanSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * CAN FD Message Event
 *
 * An Overload Frame received on a CAN channel.
 */
struct VECTOR_ASC_EXPORT CanFdMessage final : Event {
    CanFdMessage() : Event(EventType::CanFdMessage) {}

    /** @copydoc Time */
    Time time {0.0};

    /** @copydoc Channel */
    Channel channel {0};

    /** @copydoc Dir */
    Dir dir {Dir::Rx};

    /** @copydoc IdNum */
    IdNum id {0};

    /** SymbolicName */
    std::string symbolicName {};

    /** @copydoc Brs */
    Brs brs {false};

    /** @copydoc Esi */
    Esi esi {false};

    /** @copydoc Dlc */
    Dlc dlc {0};

    /** @copydoc DataLength */
    DataLength dataLength {0};

    /** @copydoc Dx */
    std::vector<Dx> data {};

    /** @copydoc MessageDuration */
    MessageDuration messageDuration {0};

    /** @copydoc MessageLength */
    MessageLength messageLength {0};

    /** Flags */
    uint32_t flags {0};

    /** CRC */
    uint32_t crc {0};

    /** @copydoc BitTimingConfArb */
    BitTimingConfArb bitTimingConfArb {0};

    /** @copydoc BitTimingConfData */
    BitTimingConfData bitTimingConfData {0};

    /** @copydoc Event::read() */
    static CanFdMessage * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
