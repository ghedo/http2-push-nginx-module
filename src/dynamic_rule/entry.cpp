#include "entry.hpp"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

void entry_t::clear() {
    s_entry.clear();
    i_entry = 0;
    n_ptr = NULL;
}

objectTypeEnum get_object_type(const std::string &type_str) {
    static std::string JSON("json");
    static std::string XML("xml");
    static std::string HTML("html");
    if ( type_str == JSON ) {
        return typeJson;
    } else if ( type_str == XML ) {
        return typeXml;
    } else if ( type_str == HTML ) {
        return typeHtml;
    } else {
        return typeUnknown;
    }
}

void split_string(const std::string& s, std::vector<std::string>& v, const std::string& c) {
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(std::string::npos != pos2)
  {
    v.push_back(s.substr(pos1, pos2-pos1));
 
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}

cJSON *walk_through_json(cJSON *json, std::vector<std::string> &paths) {
    cJSON *ret = json;
    for(std::vector<std::string>::iterator path_iter = paths.begin(); path_iter != paths.end(); ++path_iter) {
        ret = cJSON_GetObjectItem(ret , path_iter->c_str());
    }
    return ret;
    
}

std::string int2string(int i) {
    std::ostringstream stream;
    stream<<i;
    return stream.str();
}
