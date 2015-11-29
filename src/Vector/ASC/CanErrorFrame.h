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
#include "CanSymbols.h"

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
     * Bit field defining the validity of the parameters Code, CodeExt, ID, DLC, Position, and
     * Length.
     *
     *   - Bit 0: SJA 1000 ECC is valid
     *   - Bit 1: Vector CAN Core Error Code is valid
     *   - Bit 2: Vector CAN Core Error Position is valid
     *   - Bit 3: Vector CAN Core Frame Length in ns is valid
     */
    uint8_t flags;

    /** Extended error flags */
    uint16_t codeExt;

    /**
     * Content of Philips SJA1000 Error Code Capture (ECC) register, or the Vector CAN-
     * Core error register
     *
     * @note CANcardXL, CANcaseXL, CANboardXL, and all other interfaces with SJA1000
     */
    uint8_t code;

    /** @copydoc IdNum */
    IdNum id;

    /** Extended ID */
    bool extendedId;

    /** @copydoc Dlc */
    Dlc dlc;

    /** Position */
    uint16_t position;

    /** Length */
    uint16_t length;

    /** @copydoc Event::parse() */
    static CanErrorFrame * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
