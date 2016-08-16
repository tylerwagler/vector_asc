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

#include "platform.h"

#include "Event.h"
#include "LinSymbols.h"

#include "vector_asc_export.h"

namespace Vector {
namespace ASC {

/**
 * LIN DLC Info
 *
 * This info event is only displayed when an external Master is configured and the LIN hardware
 * successfully detected the DLC of an unknown frame. This DLC value is set as the expected DLC
 * value for this frame. An error is displayed if the same frame is received with a different DLC.
 *
 * If the master mode of LIN hardware is activated and a frame’s DLC is not specified, then the DLC
 * is determined using the frame’s identifier.
 */
class VECTOR_ASC_EXPORT LinDlcInfo final : public Event
{
public:
    LinDlcInfo();

    /** @copydoc LinTime */
    LinTime time;

    /** @copydoc LinChannel */
    LinChannel channel;

    /** @copydoc LinId */
    LinId id;

    /** @copydoc LinDlc */
    LinDlc dlc;

    /** @copydoc Event::read() */
    static LinDlcInfo * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
