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

#include <iomanip>
#include <regex>
#include <sstream>

#include <Vector/ASC/LinCommon.h>
#include <Vector/ASC/LinShortOrSlowResponse.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinShortOrSlowResponse * LinShortOrSlowResponse::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS REGEX_LIN_ID REGEX_WS REGEX_LIN_DLC
                     REGEX_WS "ShortOrSlowResponse:" REGEX_ws "NumRespBytes" REGEX_ws "=" REGEX_ws REGEX_LIN_NumberOfResponseBytes "((" REGEX_WS "[[:xdigit:]]+){0,9})"
                     REGEX_WS "SlowResponse" REGEX_ws "=" REGEX_ws REGEX_LIN_IsSlowResponse
                     REGEX_WS "InterruptedByBreak" REGEX_ws "=" REGEX_ws  REGEX_LIN_ResponseWasInterruptedByBreak
                     REGEX_WS "SOF" REGEX_ws "=" REGEX_ws REGEX_LIN_startOfFrame
                     REGEX_WS "BR" REGEX_ws "=" REGEX_ws REGEX_LIN_baudrate
                     REGEX_WS "break" REGEX_ws "=" REGEX_ws REGEX_LIN_SyncBreak REGEX_WS REGEX_LIN_SyncDel
                     "(subId" REGEX_ws "=" REGEX_ws REGEX_LIN_NAD REGEX_WS REGEX_LIN_MessageId REGEX_WS REGEX_LIN_SupplierId ")?"
                     REGEX_WS "EOH" REGEX_ws "=" REGEX_ws REGEX_LIN_endOfHeader
                     REGEX_WS "EOB" REGEX_ws "=((" REGEX_WS REGEX_LIN_T "){0,8})"
                     REGEX_WS "HBR" REGEX_ws "=" REGEX_ws REGEX_LIN_headerBaudrate
                     REGEX_WS "HSO" REGEX_ws "=" REGEX_ws REGEX_LIN_stopBitOffsetInHeader
                     REGEX_WS "CSM" REGEX_ws "=" REGEX_ws REGEX_LIN_checksumModel REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linShortOrSlowResponse = new LinShortOrSlowResponse;
        linShortOrSlowResponse->time = std::stod(match[1]);
        linShortOrSlowResponse->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linShortOrSlowResponse->id = match[3];
        linShortOrSlowResponse->dlc = std::stoul(match[4]);
        linShortOrSlowResponse->numberOfResponseBytes = std::stoul(match[5]);
        std::istringstream iss1(match[6]);
        iss1 >> std::hex;
        while (!iss1.eof()) {
            unsigned short s;
            iss1 >> s;
            linShortOrSlowResponse->data.push_back(s);
        }
        linShortOrSlowResponse->isSlowResponse = (match[8] == '1');
        linShortOrSlowResponse->responseWasInterruptedByBreak = (match[9] == '1');
        linShortOrSlowResponse->startOfFrame = std::stod(match[10]);
        linShortOrSlowResponse->baudrate = std::stoul(match[11]);
        linShortOrSlowResponse->syncBreak = std::stoul(match[12]);
        linShortOrSlowResponse->syncDel = std::stoul(match[13]);
        if (match[14] != "") {
            linShortOrSlowResponse->nad = std::stoul(match[15]);
            linShortOrSlowResponse->messageId = std::stoul(match[16]);
            linShortOrSlowResponse->supplierId = std::stoul(match[17]);
        }
        linShortOrSlowResponse->endOfHeader = std::stod(match[18]);
        std::istringstream iss2(match[19]);
        while (!iss2.eof()) {
            double s;
            iss2 >> s;
            linShortOrSlowResponse->endOfByte.push_back(s);
        }
        linShortOrSlowResponse->headerBaudrate = std::stod(match[21]);
        linShortOrSlowResponse->stopBitOffsetInHeader = std::stoul(match[22]);
        if (match[23] == "unknown")
            linShortOrSlowResponse->checksumModel = LinChecksumModel::Unknown;
        else if (match[23] == "classic")
            linShortOrSlowResponse->checksumModel = LinChecksumModel::Classic;
        else if (match[23] == "enhanced")
            linShortOrSlowResponse->checksumModel = LinChecksumModel::Enhanced;
        else if (match[23] == "error")
            linShortOrSlowResponse->checksumModel = LinChecksumModel::Error;
        return linShortOrSlowResponse;
    }

    return nullptr;
}

void LinShortOrSlowResponse::write(File & file, std::ostream & stream) {
    if (file.version < File::Version::Ver_7_5)
        return;

    writeLinTime(file, stream, time);
    stream << ' ';
    writeLinChannel(file, stream, channel);
    stream << ' ';

    /* format: "%s %d ShortOrSlowResponse: " */
    /* format: "%-12.1d %d ShortOrSlowResponse: " */
    /* format: "%-12.1x %d ShortOrSlowResponse: " */
    stream
            << std::left << std::setw(12) << id
            << ' '
            << std::right << std::dec << (uint16_t) dlc
            << " ShortOrSlowResponse: ";

    /* format: "NumRespBytes = %d  " */
    stream << "NumRespBytes = " << std::dec << (uint16_t) numberOfResponseBytes << "  ";

    writeLinData(file, stream, data);

    /* format: " SlowResponse = %d InterruptedByBreak = %d" */
    stream
            << " SlowResponse = " << (isSlowResponse ? '1' : '0')
            << " InterruptedByBreak = " << (responseWasInterruptedByBreak ? '1' : '0');

    writeLinStartOfFrame(file, stream, startOfFrame);
    writeLinBaudrate(file, stream, baudrate);
    writeLinSyncBreak(file, stream, syncBreak);
    writeLinSyncDel(file, stream, syncDel);
    if ((nad != 0) || (messageId != 0) || (supplierId != 0))
        writeLinSubId(file, stream, nad, messageId, supplierId);
    writeLinEndOfHeader(file, stream, endOfHeader);
    writeLinEndOfByte(file, stream, endOfByte, dlc);
    writeLinHeaderBaudrate(file, stream, headerBaudrate);
    writeLinStopBitOffsetInHeader(file, stream, stopBitOffsetInHeader);
    writeLinChecksumModel(file, stream, checksumModel);

    stream << endl;
}

}
}
