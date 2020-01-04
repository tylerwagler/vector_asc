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
#include <Vector/ASC/TpDiagSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/** Diagnostic request */
struct VECTOR_ASC_EXPORT DiagRequest final : Event {
    DiagRequest() : Event(EventType::DiagRequest) {}

    /** @copydoc TpDiagTimestamp */
    TpDiagTimestamp time {0.0};

    /** @copydoc TpDiagEcuQualifier */
    TpDiagEcuQualifier ecuQualifier {};

    /** Command */
    enum class Command {
        /** Close */
        Close,

        /** Open */
        Open,

        /** TPon */
        TpOn,

        /** TPoff */
        TpOff,

        /** byteSequence */
        ByteSequence
    };

    /** Command */
    Command command {Command::ByteSequence};

    /** @copydoc TpDiagByteSequence */
    std::vector<TpDiagByteSequence> byteSequence {};

    /** @copydoc Event::read() */
    static DiagRequest * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
