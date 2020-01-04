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
#include <Vector/ASC/MostSymbols.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/**
 * MOST Statistic Extended Event (CodingErrors and FrameCounter)
 *
 * Event transports some bus statistic information that was previously (until CA-
 * Noe/CANalyzerVersion 6.1) carried by the main bus statistic event but was not logged. Usually the
 * event is not visible in a Trace window.
 */
class VECTOR_ASC_EXPORT MostStatisticExtended final : public Event {
  public:
    MostStatisticExtended();

    /** @copydoc MostTime */
    MostTime time;

    /** @copydoc MostChannel */
    MostChannel channel;

    /** @copydoc CodingErrors */
    MostCodingErrors codingErrors;

    /** @copydoc FrameCounter */
    MostFrameCounter frameCounter;

    /** @copydoc Event::read() */
    static MostStatisticExtended * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
