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

namespace Vector {
namespace ASC {

/** MOST Common Register Event*/
/* <Time> <Channel> RegData: <RegSubType> <RegChip> <RegOffset> <RegDataLen> <D0>...<D(RegDataLen-1)> */
class MostCommonRegisterEvent : public Event
{
public:
    MostCommonRegisterEvent();
    virtual ~MostCommonRegisterEvent();

    /** Time */
    float time;

    /** Channel */
    unsigned short channel;

    /** RegSubType */
    unsigned short regSubType;

    /** RegChip */
    unsigned short regChip;

    /** RegOffset */
    unsigned short regOffset;

    /** RegDataLen */
    unsigned short regDataLen;

    /** Data */
    unsigned short data[1024];

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static MostCommonRegisterEvent * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
