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
#include <Vector/ASC/CanSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * CAN Error Frame
 *
 * A CAN Error Frame received on a CAN channel.
 */
struct VECTOR_ASC_EXPORT CanErrorFrame final : Event {
    CanErrorFrame() : Event(EventType::CanErrorFrame) {}

    /** @copydoc Time */
    Time time {0.0};

    /** @copydoc Channel */
    Channel channel {0};

    /**
     * Bit field defining the validity of the parameters Code, CodeExt, ID, DLC, Position, and
     * Length.
     *
     *   - Bit 0: SJA 1000 ECC is valid
     *   - Bit 1: Vector CAN Core Error Code is valid
     *   - Bit 2: Vector CAN Core Error Position is valid
     *   - Bit 3: Vector CAN Core Frame Length in ns is valid
     */
    uint8_t flags {0};

    /** Extended error flags */
    uint16_t codeExt {0};

    /**
     * Content of Philips SJA1000 Error Code Capture (ECC) register, or the Vector CAN-
     * Core error register
     *
     * @note CANcardXL, CANcaseXL, CANboardXL, and all other interfaces with SJA1000
     */
    uint8_t code {0};

    /** @copydoc IdNum */
    IdNum id {0};

    /** Extended ID */
    bool extendedId {false};

    /** @copydoc Dlc */
    Dlc dlc {0};

    /** Position */
    uint16_t position {0};

    /** Length */
    uint16_t length {0};

    /** @copydoc Event::read() */
    static CanErrorFrame * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
