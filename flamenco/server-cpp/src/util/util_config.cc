// Copyright (c) 2015 farm-proto authors.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#include "util/util_config.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "util/util_string.h"

namespace Farm {

config::config() {
}

config::config(const string& file_name) {
  parse_file(file_name);
}

bool config::has_value(const string& key) {
  return values_.find(key) != values_.end();
}

config::value_type config::get_value(const string& key,
                                     value_type default_value) {
  map<string, value_type>::iterator it = values_.find(key);
  if (it == values_.end()) {
    return default_value;
  } else {
    return it->second;
  }
}

config::value_type config::set_value(const string& key,
                                     value_type value) {
  values_[key] = value;
  return value;
}

bool config::parse_file(const string& file_name) {
  using std::getline;
  std::ifstream ifs(file_name);
  string line;
  if (ifs.good()) {
    while (getline(ifs, line)) {
      std::istringstream is_line(line);
      string key;
      /* getline will consume the string until the delimiter (defaults to \n). */
      if (getline(is_line, key, '=')) {
        string value;
        if (getline(is_line, value))
          values_[key] = value;
      }
    }
    ifs.close();
  }
  return true;
}

}  /* namespace Farm */
