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

#include "Event.h"
#include "Symbols.h"

namespace Vector {
namespace ASC {

/**
 * CAN FD Error Frame
 *
 * An Error Frame received on a CAN-FD channel with a dominant EDL bit. In case of certain errors
 * (NACK Error, CRC Error) the hardware/driver may provide further information (ID, DLC, Data
 * ...) about the partial frame preceding the actual Error Frame, otherwise these values are 0.
 */
class CanFdErrorFrame : public Event
{
public:
    CanFdErrorFrame();
    virtual ~CanFdErrorFrame();

    /** @copydoc Time */
    Time time;

    /** @copydoc Channel */
    Channel channel;

    /** @copydoc Dir */
    Dir dir;

    /** Error Text */
    std::string errorText;

    /** flags */
    uint32_t flags1;

    /** code */
    uint32_t code;

    /** codeExt */
    uint32_t codeExt;

    /** Phase */
    enum class Phase {
        Data
    };

    /** Phase */
    Phase phase;

    /** Position */
    uint32_t position;

    /** @copydoc IdNum */
    IdNum id;

    /** @copydoc Brs */
    Brs brs;

    /** @copydoc Esi */
    Esi esi;

    /** @copydoc Dlc */
    uint8_t dlc;

    /** @copydoc DataLength */
    DataLength dataLength;

    /** @copydoc Dx */
    Dx data[64];

    /** @copydoc MessageDuration */
    MessageDuration messageDuration;

    /** Flags */
    uint32_t flags2;

    /** CRC */
    uint32_t crc;

    /** @copydoc BitTimingConfArb */
    BitTimingConfArb bitTimingConfArb;

    /** @copydoc BitTimingConfData */
    BitTimingConfData bitTimingConfData;

    /** @copydoc Event::parse() */
    static CanFdErrorFrame * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
