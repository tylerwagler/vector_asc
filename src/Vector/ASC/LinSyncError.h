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

#include <array>

#include <Vector/ASC/Event.h>
#include <Vector/ASC/LinSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * LIN Sync Error
 *
 * This error event can only occur when an external Master is used.
 *
 * Synchronization errors occur if the LIN hardware cannot synchronize with an external Master.
 * This might happen if the baud rate actually used by the Master deviates by more than 15 % from
 * the baud rate specified by the LIN hardware. In this case the baud rate value should be modified.
 *
 * This error event may also occur if the Master transmits an invalid or corrupted Sync field. The
 * synchronization error messages displays 4 time intervals (in microseconds) detected between the
 * falling signal edges of the Sync field. The expected time interval between consecutive falling sig-
 * nal edges is 2 bit times. After the first failure interval has been seen the rest of array elements are
 * initialized to 0.
 */
struct VECTOR_ASC_EXPORT LinSyncError final : Event {
    LinSyncError() : Event(EventType::LinSyncError) {}

    /** @copydoc LinTime */
    LinTime time {0.0};

    /** @copydoc LinChannel */
    LinChannel channel {0};

    /** @copydoc LinTimeInterval */
    std::array<LinTimeInterval, 4> timeInterval {};

    /** @copydoc LinStartOfFrame */
    LinStartOfFrame startOfFrame {0.0};

    /** @copydoc LinBaudrateType */
    LinBaudrateType baudrate {0};

    /** @copydoc LinSyncBreak */
    LinSyncBreak syncBreak {0};

    /** @copydoc LinSyncDel */
    LinSyncDel syncDel {0};

    /** @copydoc Event::read() */
    static LinSyncError * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
