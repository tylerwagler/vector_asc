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
 * MOST ECL
 *
 * State change of the MOST Electrical Control Line.
 */
struct VECTOR_ASC_EXPORT MostEcl final : Event {
    MostEcl() : Event(EventType::MostEcl) {}

    /** @copydoc MostTime */
    MostTime time {0.0};

    /** @copydoc MostChannel */
    MostChannel channel {0};

    /** @copydoc MostEclMode */
    MostEclMode eclMode {MostEclMode::Discrete};

    /** @copydoc MostEclState */
    MostEclState eclState {MostEclState::LineLow};

    /** @copydoc Event::read() */
    static MostEcl * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
