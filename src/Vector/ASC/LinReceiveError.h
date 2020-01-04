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
 * LIN Receive Error
 *
 * A receive error event may have a wide variety of causes.
 * An external Master can cause a receive error event:
 *   - by transmitting sync break that is too short,
 *   - by not returning the correct value 0x55 in the sync field,
 *   - by assigning an incorrect parity to the frame identifier.
 *
 * A receive error event can also be caused:
 *   - by a Slave sending an illegal character during a Bus Idle phase (e.g. because it did not fin-
 *     ish transmission quickly enough and the checksum byte of the response was sent during
 *     the Bus Idle phase),
 *   - by a faulty (dominant) stop bit (i.e. framing error),
 *   - if the LIN hardware receives a character that is different from the character sent during
 *     transmission,
 *   - if the LIN hardware only receives part of a frame, at the start of a measurement (in a cor-
 *     rectly functioning system).
 */
struct VECTOR_ASC_EXPORT LinReceiveError final : Event {
    LinReceiveError() : Event(EventType::LinReceiveError) {}

    /** @copydoc LinTime */
    LinTime time {0.0};

    /** @copydoc LinChannel */
    LinChannel channel {0};

    /** @copydoc LinId */
    LinId id {};

    /** @copydoc LinDlc */
    LinDlc dlc {0};

    /** @copydoc LinDescription */
    LinDescription description {};

    /** @copydoc LinOffendingByte */
    LinOffendingByte offendingByte {0};

    /** @copydoc LinSlaveId */
    LinSlaveId slaveId {0};

    /** @copydoc LinState */
    LinState state {0};

    /** @copydoc LinStateReason */
    LinStateReason stateReason {0};

    /** @copydoc LinIsShortError */
    LinIsShortError isShortError {false};

    /** @copydoc LinIsDlcTimeout */
    LinIsDlcTimeout isDlcTimeout {false};

    /** @copydoc LinHasDatabytes */
    LinHasDatabytes hasDataBytes {false};

    /** @copydoc LinDx */
    std::vector<LinDx> data {};

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

    /** @copydoc LinResponseBaudrate */
    LinResponseBaudrate responseBaudrate {0};

    /** @copydoc LinHeaderBaudrate */
    LinHeaderBaudrate headerBaudrate {0.0};

    /** @copydoc LinStopBitOffsetInHeader */
    LinStopBitOffsetInHeader stopBitOffsetInHeader {0};

    /** @copydoc LinStopBitOffsetInResponse */
    LinStopBitOffsetInResponse stopBitOffsetInResponse {0};

    /** @copydoc LinChecksumModel */
    LinChecksumModel checksumModel {LinChecksumModel::Unknown};

    /** @copydoc Event::read() */
    static LinReceiveError * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
