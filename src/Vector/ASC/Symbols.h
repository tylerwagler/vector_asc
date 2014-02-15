#pragma once

#include <string>

namespace Vector {
namespace ASC {
namespace Symbol {

/**
 * absolute or relative time
 * in seconds
 *
 * Width in chars (dec): >= 9
 *
 * Example: 1234.5678
 *
 * Special: usually 4 decimal places
 */
typedef double Time;

/**
 * Number of the CAN
 * channel.
 *
 * Width in chars (dec): 2 - 10
 *
 * Range: [A-Za-z0-9]{2,10}
 *
 * Example: 1, CAN 1, CAN FD 1
 */
typedef std::string Channel;

/**
 * Numeric identifier
 *
 * Width in chars (hex): 15
 *
 * Width in chars (dec): 15
 *
 * Range: Normal mode: 0x0...0x7FF, Extended Mode: 0x0...0x1FFFF
 *
 * Special: In extended mode only a width of 14 characters,
 * because of 'x' at the end. CAN FD represents only in hex.
 */
typedef struct {
    unsigned int id;
    bool extended;
} NumericID;

/**
 * Symbol identifier
 *
 * Differences to numeric format:
 *
 * 1. Four spaces instead
 * of one after the Identifier
 *
 * 2. Length of <ID> is
 * >=32. For short symbolic
 * names (<32) the
 * remaining positions are
 * filled with spaces.
 *
 * Width in chars (hex): >= 32
 *
 * Width in chars (dec): >= 32
 */
typedef std::string SymbolicID;

/**
 * direction of transmission
 *
 * Width in chars (dec): 4
 *
 * Range: Rx, Tx, TxRq
 *
 * Example: Rx
 */
typedef enum class Dir : unsigned short{
    Rx, Tx, TxRq
} Dir;

/**
 * data length code
 *
 * Note: the DLC field is
 * written as one hex digit.
 * In case DLC is greater
 * 8, there are max. 8 data
 * bytes written/read in.
 *
 * Width in chars (hex): 1
 *
 * Width in chars (dec): 2
 *
 * Range: Hex: 0...F, Dec: 0...15
 *
 * Example: B, 12
 *
 * Special: CAN FD representation is always dec
 */
typedef unsigned short DLC;

/**
 * Some special message
 * flags that are written at
 * the end of a logging
 * line. Possible values
 * are:
 *
 * - "TE": Transmission
 * Error (NERR signal).
 * Indicates whether a line
 * has failed during a two-wire
 * operation. Especially
 * available on Single-Wire
 * mode.
 *
 * - "WU": Wake-Up.
 * Indicates whether a
 * message was transmitted
 * with overvoltage
 * with the purpose of
 * waking up the CAN
 * controller.
 *
 * - "XX": Both, "TE"
 * and "WU" occurred
 *
 * Width in chars (hex): 2
 *
 * Width in chars (dec): 2
 *
 * Range: TE, WU, XX
 *
 * Example: TE
 *
 */
typedef enum MessageFlags : unsigned short {
    TE = 1,
    WU = 2,
    XX = 4
} MessageFlags;

/**
 * the number of received
 * statistic events
 *
 * Width in chars (dec): 1-10
 *
 * Range: 0...4294967295
 *
 * Example: 1056
 */
typedef unsigned int StatNumber;

/**
 * the busload in percent
 *
 * Width in chars (dec): 3-6
 *
 * Range: 0.0 ... 100.0
 *
 * Example: 11.94
 */
typedef double StatPercent;

/**
 * the pre trigger time in
 * ms
 *
 * Width in chars (dec): 1-10
 *
 * Range: 0 ... 1316134911
 *
 * Example: 2000
 */
typedef unsigned int PreTrigger;

/**
 * the post trigger time in
 * ms
 *
 * Width in chars (dec): 1-10
 *
 * Range: 0 ... 1316134911
 *
 * Example: 2000
 */
typedef unsigned int PostTrigger;

/**
 * the error message of the
 * CAN error event
 *
 * Width in chars (dec): 0 - undefined
 *
 * Example: "rx queue overrun"
 */
typedef std::string Error;

/**
 * data byte x
 *
 * Width in chars (hex): 2
 *
 * Width in chars (dec): 3
 *
 * Range: 0...255
 *
 * Example: 1E
 *
 * Special: CAN FD only hex representation
 */
typedef unsigned short Dx;

/**
 * a string that represents a
 * day of the week
 *
 * Width in chars (hex): 3
 *
 * Width in chars (dec): 3
 *
 * Range: Mon, Tue, Wed, Thu, Fri, Sat, Sun
 *
 * Example: Mon
 *
 * Special: Different range in german version:
 * Mon, Die, Mit, Don, Fre, Sam, Son
 */
typedef enum class WeekDay : int {
    Unknown = -1,
    Mon = 1,
    Tue = 2,
    Wed = 3,
    Thu = 4,
    Fri = 5,
    Sat = 6,
    Sun = 0
} WeekDay;

/**
 * a string that represents a
 * month
 *
 * Width in chars (hex): 3
 *
 * Width in chars (dec): 3
 *
 * Range: Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
 *
 * Example: Nov
 *
 * Special: Different range in german version:
 * Jan, Feb, Mär, Apr, Mai, Jun, Jul, Aug, Sep, Okt, Nov, Dez
 */
typedef enum class Month : int {
    Unknown = -1,
    Jan = 0,
    Feb = 1,
    Mar = 2,
    Apr = 3,
    May = 4,
    Jun = 5,
    Jul = 6,
    Aug = 7,
    Sep = 8,
    Oct = 9,
    Nov = 10,
    Dec = 11
} Month;

/**
 * a number that represents
 * the date.
 *
 * Width in chars (hex): 1-2
 *
 * Width in chars (dec): 1-2
 *
 * Range: 1..31
 *
 * Example: 15
 */
typedef int Date;

/**
 * a string that represents a
 * time in the current format.
 *
 * hh:mm:ss am|pm
 *
 * Width in chars (hex): 11
 *
 * Width in chars (dec): 11
 *
 * Range: 00:00:00 ... 12:60:60
 *
 * Example: 01:13:17 pm
 *
 * Special: Different range in german version:
 * 00:00:00 ... 23:60:60
 * In german version 'am' and 'pm' are not used.
 * Therefore the width in chars is only 8.
 */
typedef struct {
    int h;   // am|pm. pm adds +12 to h
    int m;
    int s;
} FullTime;

/**
 * a string that represents a
 * year.
 *
 * Width in chars (hex): 4
 *
 * Width in chars (dec): 4
 *
 * Example: 1999
 */
typedef int Year;

/**
 * a number that represents
 * the variable data
 * type of system variable:
 * - 1 = Float
 * - 2 = Integer
 * - 3 = String
 * - 4 = Array of Floats
 * - 5 = Array of Integers
 *
 * Width in chars (hex): 1
 *
 * Width in chars (dec): 1
 *
 * Range 1...5
 *
 * Example: 2
 */
typedef unsigned short svtype;

/**
 * Message duration [in
 * nanoseconds]. Not
 * including 3 Interframe
 * Space bit times and by
 * Rx-messages also not
 * including 1 End-Of-Frame
 * bit time
 *
 * Example: 768000
 */
typedef unsigned int MessageDuration;

/**
 * Total number of bits of
 * the message including
 * EOF and Interframe
 * Space [in bits]
 *
 * Example: 67
 */
typedef unsigned int MessageLength;

/**
 * Bit rate switch flag for
 * CAN FD. Indicate bit
 * rate switch is enabled or
 * disabled.
 *
 * Width in chars (hex): 1
 *
 * Range: 0-1
 *
 * Example: 0
 */
typedef bool BRS;

/**
 * Error state indicator
 * flag for CAN FD. Indicate
 * a transceiver is in
 * error active or error
 * passive mode.
 *
 * Width in chars (hex): 1
 *
 * Range: 0-1
 *
 * Example: 0
 */
typedef bool ESI;

/**
 * Valid length of the
 * message in bytes.
 *
 * Width in chars (dec): 3
 *
 * Range: 0-64
 *
 * Example: 20
 */
typedef unsigned short DataLength;

/**
 * Bit timing information
 * for CAN-FD frames.
 *
 * Special: May be 0, if not supported by the CAN controller
 */
typedef unsigned int BitTimingConfArb;

/**
 * Bit timing information
 * for CAN-FD frames
 *
 * Special: May be 0, if not supported by the CAN controller
 */
typedef unsigned int BitTimingConfData;

}
}
}
