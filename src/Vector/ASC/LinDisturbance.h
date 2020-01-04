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
#include <Vector/ASC/LinSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * LIN Disturbance event
 *
 * This event occurs if CANoe/CANalyzer explicitly caused to disturb one bit or a sequence of bits.
 *
 * IMPORTANT: This event is generated from CANoe/CANalyzer 7.5 only
 */
struct VECTOR_ASC_EXPORT LinDisturbance final : Event {
    LinDisturbance() : Event(EventType::LinDisturbance) {}

    /** @copydoc LinTime */
    LinTime time {0.0};

    /** @copydoc LinChannel */
    LinChannel channel {0};

    /** @copydoc LinDisturbanceType */
    LinDisturbanceType disturbanceType {};

    /** @copydoc LinByteIndex */
    LinByteIndex byteIndex {0};

    /** @copydoc LinBitIndex */
    LinBitIndex bitIndex {0};

    /** @copydoc LinBitOffsetInSixteenthBits */
    LinBitOffsetInSixteenthBits bitOffset {0};

    /** @copydoc LinDisturbanceLengthInSixteenthBits */
    LinDisturbanceLengthInSixteenthBits length {0};

    /** @copydoc LinIdOrFf */
    LinIdOrFf header {0};

    /** @copydoc LinIdOrFf */
    LinIdOrFf disturbingHeader {0};

    /** @copydoc Event::read() */
    static LinDisturbance * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
