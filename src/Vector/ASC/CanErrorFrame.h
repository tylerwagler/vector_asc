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
 * CAN Error Frame
 *
 * A CAN Error Frame received on a CAN channel.
 */
class CanErrorFrame : public Event
{
public:
    CanErrorFrame();
    virtual ~CanErrorFrame();

    /** @copydoc Time */
    Time time;

    /** @copydoc Channel */
    Channel channel;

    /**
     * Content of Philips SJA1000 Error Code Capture (ECC) register, or the Vector CAN-
     * Core error register
     *
     * @note CANcardXL, CANcaseXL, CANboardXL, and all other interfaces with SJA1000
     */
    uint8_t ecc;

    // Interfaces with CAN-Core:
    uint8_t flags;

    uint16_t codeExt;

    uint8_t code;

    /** @copydoc IdNum */
    IdNum id;

    /** @copydoc Dlc */
    Dlc dlc;

    uint8_t position;

    uint16_t length;

    /** @copydoc Event::parse() */
    static CanErrorFrame * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
