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
 * Macro Signal Event: CAN, LIN and FlexRay
 *
 * An event that is written if the user change a signal value with a panel control, and the macro recording is on.
 */
struct VECTOR_ASC_EXPORT MacroSignal final : Event {
    MacroSignal() : Event(EventType::MacroSignal) {}

    /** @Time */
    Time time {0.0};

    /** F = FlexRay / L = Lin / nothing = CAN */
    enum class Bussystem : char {
        /** FlexRay */
        FlexRay = 'F',

        /** LIN */
        Lin = 'L',

        /** CAN */
        Can = ' '
    };

    /** F = FlexRay / L = Lin / nothing = CAN */
    Bussystem bussystem {Bussystem::Can};

    /** the number of the CAN/LIN/FlexRay channel */
    uint16_t channel {0};

    /** a string which contains the node name of the signal */
    std::string node {};

    /** a string which contains the message name of the signal */
    std::string message {};

    /** a string which contains the signal name */
    std::string signal {};

    /** the signal value as number OR a string from the value description table (if exists) */
    std::string value {};

    /** @copydoc Event::read() */
    static MacroSignal * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
