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

#include "Event.h"
#include "LinSymbols.h"

namespace Vector {
namespace ASC {

/**
 * LIN Short or slow response
 *
 * This event occurs if a set of receive errors could be a valid header followed by a short or slow re-
 * sponse.
 *
 * IMPORTANT: This event is generated from CANoe/CANalyzer 7.5 only
 */
class LinShortOrSlowResponse : public Event
{
public:
    LinShortOrSlowResponse();
    virtual ~LinShortOrSlowResponse();

    /** @copydoc LinTime */
    LinTime time;

    /** @copydoc LinChannel */
    LinChannel channel;

    /** @copydoc LinId */
    LinId id;

    /** @copydoc LinDlc */
    LinDlc dlc;

    /** @copydoc LinNumberOfResponseBytes */
    LinNumberOfResponseBytes numberOfResponseBytes;

    /** @copydoc LinDx */
    LinDx data[9];

    /** @copydoc LinIsSlowResponse */
    LinIsSlowResponse isSlowResponse;

    /** @copydoc LinResponseWasInterruptedByBreak */
    LinResponseWasInterruptedByBreak responseWasInterruptedByBreak;

    /** @copydoc LinStartOfFrame */
    LinStartOfFrame startOfFrame;

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
    LinT endOfByte[8];

    /** @copydoc LinHeaderBaudrate */
    LinHeaderBaudrate headerBaudrate;

    /** @copydoc LinStopBitOffsetInHeader */
    LinStopBitOffsetInHeader stopBitOffsetInHeader;

    /** @copydoc LinChecksumModel */
    LinChecksumModel checksumModel;

    /** @copydoc Event::parse() */
    static LinShortOrSlowResponse * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);
};

}
}
