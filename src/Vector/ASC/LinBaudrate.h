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
 * LIN Baudrate
 *
 * This info event is only displayed when an external Master is configured.
 * This info event is send by the LIN hardware at the start of a measurement and whenever the baud
 * rate changes by more than 0.5 % during a measurement. If this info event is displayed, then the
 *
 * LIN hardware is synchronized with the baud rate of the external Master.
 */
struct VECTOR_ASC_EXPORT LinBaudrate final : Event {
    LinBaudrate() : Event(EventType::LinBaudrate) {}

    /** @copydoc LinTime */
    LinTime time {0.0};

    /** @copydoc LinChannel */
    LinChannel channel {0};

    /** @copydoc LinBaudrateType */
    LinBaudrateType baudrate {0};

    /** @copydoc Event::read() */
    static LinBaudrate * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
