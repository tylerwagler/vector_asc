#define BOOST_TEST_MODULE Date
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <sstream>

#include "Vector/ASC/CanCommon.h"

BOOST_AUTO_TEST_CASE(ReadDates) {
    std::string hour;
    std::string amFm;
    Vector::ASC::File::Language language;
    struct tm date;

    /* midnight */
    hour = "12";
    amFm = " am";
    Vector::ASC::readDate("Sun", "Jan", "0", hour, "0", "0", amFm, "1980", language, date);
    BOOST_CHECK_EQUAL(date.tm_hour, 0);

    /* am */
    hour = "1";
    amFm = " am";
    Vector::ASC::readDate("Sun", "Jan", "0", hour, "0", "0", amFm, "1980", language, date);
    BOOST_CHECK_EQUAL(date.tm_hour, 1);

    /* am */
    hour = "11";
    amFm = " am";
    Vector::ASC::readDate("Sun", "Jan", "0", hour, "0", "0", amFm, "1980", language, date);
    BOOST_CHECK_EQUAL(date.tm_hour, 11);

    /* noon */
    hour = "12";
    amFm = " pm";
    Vector::ASC::readDate("Sun", "Jan", "0", hour, "0", "0", amFm, "1980", language, date);
    BOOST_CHECK_EQUAL(date.tm_hour, 12);

    /* pm */
    hour = "01";
    amFm = " pm";
    Vector::ASC::readDate("Sun", "Jan", "0", hour, "0", "0", amFm, "1980", language, date);
    BOOST_CHECK_EQUAL(date.tm_hour, 13);

    /* pm */
    hour = "11";
    amFm = " pm";
    Vector::ASC::readDate("Sun", "Jan", "0", hour, "0", "0", amFm, "1980", language, date);
    BOOST_CHECK_EQUAL(date.tm_hour, 23);
}

BOOST_AUTO_TEST_CASE(WriteDates) {
    Vector::ASC::File file;
    std::ostringstream ss;
    struct tm date;

    /* init variables */
    file.language = Vector::ASC::File::Language::En;
    memset(&date, 0, sizeof(date));

    /* midnight */
    ss.str("");
    date.tm_hour = 0;
    Vector::ASC::writeDate(file, ss, date);
    BOOST_CHECK_EQUAL(ss.str(), "Sun Jan 0 12:00:00 am 1900");

    /* am */
    ss.str("");
    date.tm_hour = 1;
    Vector::ASC::writeDate(file, ss, date);
    BOOST_CHECK_EQUAL(ss.str(), "Sun Jan 0 01:00:00 am 1900");

    /* am */
    ss.str("");
    date.tm_hour = 11;
    Vector::ASC::writeDate(file, ss, date);
    BOOST_CHECK_EQUAL(ss.str(), "Sun Jan 0 11:00:00 am 1900");

    /* noon */
    ss.str("");
    date.tm_hour = 12;
    Vector::ASC::writeDate(file, ss, date);
    BOOST_CHECK_EQUAL(ss.str(), "Sun Jan 0 12:00:00 pm 1900");

    /* pm */
    ss.str("");
    date.tm_hour = 13;
    Vector::ASC::writeDate(file, ss, date);
    BOOST_CHECK_EQUAL(ss.str(), "Sun Jan 0 01:00:00 pm 1900");

    /* pm */
    ss.str("");
    date.tm_hour = 23;
    Vector::ASC::writeDate(file, ss, date);
    BOOST_CHECK_EQUAL(ss.str(), "Sun Jan 0 11:00:00 pm 1900");
}
