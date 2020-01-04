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
#include <Vector/ASC/LinSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

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
struct VECTOR_ASC_EXPORT LinShortOrSlowResponse final : Event {
    LinShortOrSlowResponse() : Event(EventType::LinShortOrSlowResponse) {}

    /** @copydoc LinTime */
    LinTime time {0.0};

    /** @copydoc LinChannel */
    LinChannel channel {0};

    /** @copydoc LinId */
    LinId id {};

    /** @copydoc LinDlc */
    LinDlc dlc {0};

    /** @copydoc LinNumberOfResponseBytes */
    LinNumberOfResponseBytes numberOfResponseBytes {0};

    /** @copydoc LinDx */
    std::vector<LinDx> data {};

    /** @copydoc LinIsSlowResponse */
    LinIsSlowResponse isSlowResponse {false};

    /** @copydoc LinResponseWasInterruptedByBreak */
    LinResponseWasInterruptedByBreak responseWasInterruptedByBreak {false};

    /** @copydoc LinStartOfFrame */
    LinStartOfFrame startOfFrame {0.0};

    /** @copydoc LinBaudrateType */
    LinBaudrateType baudrate {0};

    /** @copydoc LinSyncBreak */
    LinSyncBreak syncBreak {0};

    /** @copydoc LinSyncDel */
    LinSyncDel syncDel {0};

    /** @copydoc LinNad */
    LinNad nad {0};

    /** @copydoc LinMessageId */
    LinMessageId messageId {0};

    /** @copydoc LinSupplierId */
    LinSupplierId supplierId {0};

    /** @copydoc LinEndOfHeader */
    LinEndOfHeader endOfHeader {0.0};

    /** @copydoc LinT */
    std::vector<LinT> endOfByte {};

    /** @copydoc LinHeaderBaudrate */
    LinHeaderBaudrate headerBaudrate {0.0};

    /** @copydoc LinStopBitOffsetInHeader */
    LinStopBitOffsetInHeader stopBitOffsetInHeader {0};

    /** @copydoc LinChecksumModel */
    LinChecksumModel checksumModel {LinChecksumModel::Unknown};

    /** @copydoc Event::read() */
    static LinShortOrSlowResponse * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
