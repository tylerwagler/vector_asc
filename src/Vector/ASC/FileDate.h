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

#include <time.h>
#include "Event.h"

namespace Vector {
namespace ASC {

/** File Date */
class FileDate : public Event
{
public:
    FileDate();
    virtual ~FileDate();

    /** date/time */
    struct tm date;

    /** language */
    File::Language language;

    /** @copydoc Event::parse() */
    static FileDate * parse(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream);

private:
    /**
     * parse week day
     *
     * @param wday[in] week day string
     */
    void parseWday(std::string wday);

    /**
     * parse month
     *
     * @param mon[in] month string
     */
    void parseMon(std::string mon);
};

}
}
