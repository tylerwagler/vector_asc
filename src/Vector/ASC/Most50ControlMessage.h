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
 * MOST50 Control Message
 *
 * Message on MOST50 Control Channel.
 */
class VECTOR_ASC_EXPORT Most50ControlMessage final : public Event {
  public:
    Most50ControlMessage();

    /** @copydoc MostTime */
    MostTime time;

    /** @copydoc MostChannel */
    MostChannel channel;

    /** @copydoc MostDir */
    MostDir dir;

    /** @copydoc MostSourceAdr */
    MostSourceAdr sourceAdr;

    /** @copydoc MostDestAdr */
    MostDestAdr destAdr;

    /** @copydoc MostState */
    MostState state;

    /** @copydoc MostAckNack */
    MostAckNack ackNack;

    /** @copydoc MostTransferType */
    MostTransferType transferType;

    /** @copydoc MostRsvdUc */
    MostRsvdUc rsvdUc1;

    /** @copydoc MostPriority */
    MostPriority priority;

    /** @copydoc MostRsvdUc */
    MostRsvdUc rsvdUc2;

    /** @copydoc MostCrc2 */
    MostCrc2 crc2;

    /** @copydoc MostRsvdUc */
    MostRsvdUc rsvdUc3;

    /** @copydoc MostRsvdUl */
    MostRsvdUl rsvdUl;

    /** @copydoc MostMsg50Len */
    MostMsg50Len msg50Len;

    /** @copydoc MostDx */
    std::vector<MostDx> data;

    /** @copydoc Event::read() */
    static Most50ControlMessage * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
