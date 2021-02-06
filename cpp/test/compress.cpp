#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <fstream>
 
#include "cvmat_serialization.h"
 
BOOST_AUTO_TEST_CASE(record)
{
  namespace io = boost::iostreams;
 
  cv::Mat depths, colors;
 
  std::ofstream ofs("matrices.bin", std::ios::out | std::ios::binary);
 
  { // use scope to ensure archive and filtering stream buffer go out of scope before stream
    io::filtering_streambuf<io::output> out;
    out.push(io::zlib_compressor(io::zlib::best_speed));
    out.push(ofs);
 
    boost::archive::binary_oarchive oa(out);
 
    while (!_kbhit()) {
      // ... grab from sensor into depths and colors
      oa << depths << colors;
    }
  }
 
  ofs.close();
}