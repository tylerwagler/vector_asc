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
 * CAN Overload Frame Event
 *
 * An Overload Frame received on a CAN channel.
 */
struct VECTOR_ASC_EXPORT CanOverloadFrame final : Event {
    CanOverloadFrame() : Event(EventType::CanOverloadFrame) {}

    /** absolute or relative time in seconds */
    Time time {0.0};

    /** Number of CAN channel. */
    Channel channel {0};

    /* "State/Error:", "chip status bus off", "Tx Error Count:", "Rx Error Count:" */

    /** @copydoc Event::read() */
    static CanOverloadFrame * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
