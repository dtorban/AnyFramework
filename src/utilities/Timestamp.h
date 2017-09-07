/*
 * Copyright Regents of the University of Minnesota, 2016.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Seth Johnson (joh08230)
 */

#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_
#include <map>
#include <climits>

namespace IVGFX {
  typedef  unsigned long long Timestamp;

  const Timestamp TIMESTAMP_MAX = ULLONG_MAX;

  class TimestampManager {
  public:

    TimestampManager() : m_currentTimestamp(0){}
    Timestamp m_currentTimestamp;

    std::map<void *, Timestamp> m_log;

    void updateTimestamp(void* object){
      if (object == NULL) {
        return;
      }
      m_log[object] = ++m_currentTimestamp;
    }

    Timestamp getTimestamp(void* object) {
      // Esentially return m_log[object], but including error checking
      if (!object) {
        return 0;
      }
      std::map<void *, Timestamp>::iterator stamp = m_log.find(object);
      if (stamp == m_log.end()) {
        return 0;
      }
      return stamp->second;
    }

    bool isNewerThan(void* object1, void* object2 ){
      return m_log[object1] > m_log[object2];
    }
    
  };


} /* namespace IVGFX */



#endif /* TIMESTAMP_H_ */
