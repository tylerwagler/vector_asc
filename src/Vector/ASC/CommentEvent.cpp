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

#include <regex>
#include "CommentEvent.h"

namespace Vector {
namespace ASC {

CommentEvent::CommentEvent() :
    Event(),
    time(0.0),
    type(0),
    commentText()
{
    eventType = EventType::CommentEvent;
}

CommentEvent::~CommentEvent()
{
}

CommentEvent * CommentEvent::parse(File & file, std::string & line)
{
    std::regex regex(
                "^([[:digit:].]+)"
                " Comment:"
                " ([[:digit:]]+)"
                " (.*)$");
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        CommentEvent * commentEvent = new CommentEvent;
        commentEvent->time = std::stod(match[1]);
        commentEvent->type = std::stod(match[2]);
        commentEvent->commentText = match[3];
        return commentEvent;
    }

    return nullptr;
}

void CommentEvent::write(File & file, std::ostream & stream)
{
    stream
            << std::fixed << time
            << " Comment:"
            << std::dec << type
            << ' '
            << commentText
            << endl;
}

}
}
