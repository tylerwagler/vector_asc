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
#include <Vector/ASC/MostSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * MOST25 Control Message Node Mode
 *
 * Message on MOST25 Control Channel received or transmitted in node mode.
 */
struct VECTOR_ASC_EXPORT Most25ControlMessageNodeMode final : Event {
    Most25ControlMessageNodeMode() : Event(EventType::Most25ControlMessageNodeMode) {}

    /** @copydoc MostTime */
    MostTime time {0.0};

    /** @copydoc MostChannel */
    MostChannel channel {0};

    /** @copydoc MostDir */
    MostDir dir {Dir::Rx};

    /** @copydoc MostSourceAdr */
    MostSourceAdr sourceAdr {0};

    /** @copydoc MostDestAdr */
    MostDestAdr destAdr {0};

    /** @copydoc MostRtype */
    MostRType rType {0};

    /** @copydoc MostDx */
    std::vector<MostDx> data {};

    /** @copydoc MostState2 */
    MostState2 state2 {0};

    /** @copydoc Event::read() */
    static Most25ControlMessageNodeMode * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
