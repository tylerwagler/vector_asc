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

#include <fstream>

#include "vector_asc_export.h"

namespace Vector {
namespace ASC {

/* force Linux to use Windows line ending */
static const char endl[] = "\r\n";

/**
 * File
 *
 * This is similar to std::fstream for ASCs
 */
class VECTOR_ASC_EXPORT File
{
public:
    File();
    virtual ~File();

    /** enumeration for openMode */
    enum class OpenMode {
        /** Read */
        Read,

        /** Write */
        Write
    };

    /** open mode */
    OpenMode openMode;

    /**
     * open file
     *
     * @param filename file name
     */
    void open(const char * filename);

    /**
     * open file
     *
     * @param filename file name
     */
    void open(const std::string & filename);

    /**
     * is file open?
     *
     * @return true if file is open
     */
    bool is_open() const;

    /** close file */
    void close();

    /**
     * check for end-of-file
     *
     * @return true if end-of-file reached
     */
    bool eof();

    /**
     * read object from file
     *
     * @return read object or nullptr
     */
    class Event * read();

private:
    /** file */
    std::fstream file;
};

}
}
