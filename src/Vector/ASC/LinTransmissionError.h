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
 * LIN Transmission Error
 *
 * FlexRay Error event transmitted by the FlexRay hardware.
 */
struct VECTOR_ASC_EXPORT LinTransmissionError final : Event {
    LinTransmissionError() : Event(EventType::LinTransmissionError) {}

    /** @copydoc LinTime */
    LinTime time {0.0};

    /** @copydoc LinChannel */
    LinChannel channel {0};

    /** @copydoc LinId */
    LinId id {};

    /** @copydoc LinSlaveId */
    LinSlaveId slaveId {0};

    /** @copydoc LinState */
    LinState state {0};

    /** @copydoc LinHeaderTime */
    LinHeaderTime headerTime {0};

    /** @copydoc LinFullTime */
    LinFullTime fullTime {0};

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

    /** @copydoc LinHeaderBaudrate */
    LinHeaderBaudrate headerBaudrate {0.0};

    /** @copydoc LinStopBitOffsetInHeader */
    LinStopBitOffsetInHeader stopBitOffsetInHeader {0};

    /** @copydoc LinChecksumModel */
    LinChecksumModel checksumModel {LinChecksumModel::Unknown};

    /** @copydoc Event::read() */
    static LinTransmissionError * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
