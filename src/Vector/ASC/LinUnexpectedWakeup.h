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
 * LIN Unexpected wakeup
 *
 * This event occurs if an unexpected byte received in bus idle phase of wake mode could be a
 * wakeup frame.
 *
 * IMPORTANT: This event is generated from CANoe/CANalyzer 7.5 only
 */
struct VECTOR_ASC_EXPORT LinUnexpectedWakeup final : Event {
    LinUnexpectedWakeup() : Event(EventType::LinUnexpectedWakeup) {}

    /** @copydoc LinTime */
    LinTime time {0.0};

    /** @copydoc LinChannel */
    LinChannel channel {0};

    /** @copydoc LinWidth */
    LinWidth width {0};

    /** @copydoc LinWakeupByte */
    LinWakeupByte wakeupByte {0};

    /** @copydoc LinStartOfFrame */
    LinStartOfFrame startOfFrame {0};

    /** @copydoc LinBaudrateType */
    LinBaudrateType baudrate {0};

    /** @copydoc Event::read() */
    static LinUnexpectedWakeup * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
