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
 * LIN Slave Timeout
 *
 * The enhanced LIN hardware capabilities can be used to define a timeout for a FSM state to a pre-
 * defined error state on exceeding this timeout and a Slave timeout message is displayed.
 */
struct VECTOR_ASC_EXPORT LinSlaveTimeout final : Event {
    LinSlaveTimeout() : Event(EventType::LinSlaveTimeout) {}

    /** @copydoc LinTime */
    LinTime time {0.0};

    /** @copydoc LinChannel */
    LinChannel channel {0};

    /** @copydoc LinSlaveId */
    LinSlaveId slaveId {0};

    /** @copydoc LinCurrentState */
    LinState currentState {0};

    /** @copydoc LinFollowingState */
    LinState followingState {0};

    /** @copydoc Event::read() */
    static LinSlaveTimeout * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
