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

#include <vector>

#include "Event.h"
#include "LinSymbols.h"

namespace Vector {
namespace ASC {

/**
 * LIN Message
 *
 * LIN frame received or transmitted on a LIN channel.
 */
class LinMessage : public Event
{
public:
    LinMessage();

    /** @copydoc LinTime */
    LinTime time;

    /** @copydoc LinChannel */
    LinChannel channel;

    /** @copydoc LinId */
    LinId id;

    /** @copydoc LinDir */
    LinDir dir;

    /** @copydoc LinDlc */
    LinDlc dlc;

    /** @copydoc LinDx */
    std::vector<LinDx> data;

    /** @copydoc LinSlaveId */
    LinSlaveId slaveId;

    /** @copydoc LinState */
    LinState state;

    /** @copydoc LinChecksum */
    LinChecksum checksum;

    /** @copydoc LinHeaderTime */
    LinHeaderTime headerTime;

    /** @copydoc LinFullTime */
    LinFullTime fullTime;

    /** @copydoc LinStartOfFrame */
    LinStartOfFrame startOfFrame;

    /** @copydoc LinSyncBreakTime */
    LinSyncBreakTime syncBreakTime;

    /** @copydoc LinSyncDelimiterTime */
    LinSyncDelimiterTime syncDelimiterTime;

    /** @copydoc LinBaudrateType */
    LinBaudrateType baudrate;

    /** @copydoc LinSyncBreak */
    LinSyncBreak syncBreak;

    /** @copydoc LinSyncDel */
    LinSyncDel syncDel;

    /** @copydoc LinNad */
    LinNad nad;

    /** @copydoc LinMessageId */
    LinMessageId messageId;

    /** @copydoc LinSupplierId */
    LinSupplierId supplierId;

    /** @copydoc LinEndOfHeader */
    LinEndOfHeader endOfHeader;

    /** @copydoc LinT */
    std::vector<LinT> endOfByte;

    /** @copydoc LinSimulated */
    LinSimulated simulated;

    /** @copydoc LinEndOfFrame */
    LinEndOfFrame endOfFrame;

    /** @copydoc LinResponseBaudrate */
    LinResponseBaudrate responseBaudrate;

    /** @copydoc LinHeaderBaudrate */
    LinHeaderBaudrate headerBaudrate;

    /** @copydoc LinStopBitOffsetInHeader */
    LinStopBitOffsetInHeader stopBitOffsetInHeader;

    /** @copydoc LinStopBitOffsetInResponse */
    LinStopBitOffsetInResponse stopBitOffsetInResponse;

    /** @copydoc LinChecksumModel */
    LinChecksumModel checksumModel;

    /** @copydoc Event::parse() */
    static LinMessage * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
