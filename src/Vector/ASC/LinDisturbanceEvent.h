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
#include "LinSymbols.h"

namespace Vector {
namespace ASC {

/**
 * LIN Disturbance event
 *
 * This event occurs if CANoe/CANalyzer explicitly caused to disturb one bit or a sequence of bits.
 *
 * IMPORTANT: This event is generated from CANoe/CANalyzer 7.5 only
 */
class LinDisturbanceEvent : public Event
{
public:
    LinDisturbanceEvent();
    virtual ~LinDisturbanceEvent();

    /** @copydoc LinTime */
    LinTime time;

    /** @copydoc LinChannel */
    LinChannel channel;

    /** @copydoc LinDisturbanceType */
    LinDisturbanceType disturbanceType;

    /** @copydoc LinByteIndex */
    LinByteIndex byteIndex;

    /** @copydoc LinBitIndex */
    LinBitIndex bitIndex;

    /** @copydoc LinBitOffsetInSixteenthBits */
    LinBitOffsetInSixteenthBits bitOffset;

    /** @copydoc LinDisturbanceLengthInSixteenthBits */
    LinDisturbanceLengthInSixteenthBits length;

    /** @copydoc LinIdOrFf */
    LinIdOrFf header;

    /** @copydoc LinIdOrFf */
    LinIdOrFf disturbingHeader;

    /** @copydoc Event::parse() */
    static LinDisturbanceEvent * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
